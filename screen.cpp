#include "screen.h"

Screen::Screen() :
    m_window(NULL), m_renderer(NULL), m_texture(NULL), m_boardTexture(NULL) {
    memset(m_images, 0, sizeof(m_images));
    memset(m_textures, 0, sizeof(m_textures));
}

bool Screen::init() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        LOG("[ERROR]: SDL init failed.");
        return false;
    }

    if (TTF_Init() == -1) {
        LOG("[ERROR]: SDL_ttf init failed.");
        return false;
    }

    //load in font
    m_font = TTF_OpenFont("src/fonts/LiberationSansBold.ttf", 24); // Adjust the font size as needed
    if (m_font == NULL) {
        LOG("[ERROR]: Failed to load font! SDL_ttf Error: " << TTF_GetError());
        return false;
    }

    m_window = SDL_CreateWindow("Chess",
        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH,
        SCREEN_WIDTH, SDL_WINDOW_SHOWN);

    if (m_window == NULL) {
        LOG("[ERROR]: Could not create window.");
        SDL_Quit();
        return false;
    }

    m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (m_renderer == NULL) {
        LOG("[ERROR]: Could not create renderer.");
        SDL_DestroyWindow(m_window);
        SDL_Quit();
        return false;
    }

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "2");

    // Set the blend mode
    SDL_SetRenderDrawBlendMode(m_renderer, SDL_BLENDMODE_BLEND);

    m_rect.w = SCREEN_WIDTH / 8;
    m_rect.h = SCREEN_WIDTH / 8;

    precomputeBoard();
    loadImages();
    createTextures();

    return true;
}


void Screen::renderText(const std::string &message) {
    SDL_Color textColor = {255, 0, 0, 255};
    SDL_Surface* textSurface = TTF_RenderText_Solid(m_font, message.c_str(), textColor);
    if (textSurface == NULL) {
        LOG("[ERROR]: Unable to render text surface! SDL_ttf Error: " << TTF_GetError());
        return;
    }

    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(m_renderer, textSurface);
    if (textTexture == NULL) {
        LOG("[ERROR]: Unable to create texture from rendered text! SDL Error: " << SDL_GetError());
        SDL_FreeSurface(textSurface);
        return;
    }

    SDL_Rect renderQuad = {SCREEN_WIDTH/4, SCREEN_WIDTH/2, textSurface->w, textSurface->h};
    SDL_RenderCopy(m_renderer, textTexture, NULL, &renderQuad);
    SDL_FreeSurface(textSurface);
    SDL_DestroyTexture(textTexture);
    SDL_RenderPresent(m_renderer);
}


void Screen::precomputeBoard() {
    m_boardTexture = SDL_CreateTexture(m_renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, SCREEN_WIDTH, SCREEN_WIDTH);
    if (!m_boardTexture) {
        LOG("[ERROR]: Failed to create board texture! SDL_Error.");
        return;
    }

    SDL_SetRenderTarget(m_renderer, m_boardTexture);

    bool toggle_color = 0;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            m_rect.x = j * SCREEN_WIDTH / 8;
            m_rect.y = i * SCREEN_WIDTH / 8;
            if (toggle_color)
                SDL_SetRenderDrawColor(m_renderer, 90, 90, 90, 255);
            else
                SDL_SetRenderDrawColor(m_renderer, 190, 190, 190, 255);
            SDL_RenderFillRect(m_renderer, &m_rect);
            if (j != 7) //needed for chess color pattern
                toggle_color = !toggle_color;
        }
    }

    SDL_SetRenderTarget(m_renderer, nullptr);
}

void Screen::draw_board() {
    SDL_RenderCopy(m_renderer, m_boardTexture, nullptr, nullptr);
}

void Screen::loadImages() {
    m_images[0] = IMG_Load("src/images/bR.png");
    m_images[1] = IMG_Load("src/images/bN.png");
    m_images[2] = IMG_Load("src/images/bB.png");
    m_images[3] = IMG_Load("src/images/bQ.png");
    m_images[4] = IMG_Load("src/images/bK.png");
    m_images[5] = IMG_Load("src/images/bP.png");

    m_images[6] = IMG_Load("src/images/wR.png");
    m_images[7] = IMG_Load("src/images/wN.png");
    m_images[8] = IMG_Load("src/images/wB.png");
    m_images[9] = IMG_Load("src/images/wQ.png");
    m_images[10] = IMG_Load("src/images/wK.png");
    m_images[11] = IMG_Load("src/images/wP.png");
}

void Screen::createTextures() {
    for (int i = 0; i < 12; i++) {
        if (m_images[i]) {
            m_textures[i] = SDL_CreateTextureFromSurface(m_renderer, m_images[i]);
            SDL_FreeSurface(m_images[i]);
            if (!m_textures[i]) {
                LOG("[ERROR]: Failed to create texture for piece " << i << "!");
                std::cerr << "" << SDL_GetError() << std::endl;
            }
        }
    }
}

void Screen::drawPieces(const GameState &gamestate) {
    for (int rank = 0; rank < 8; rank++) {
        for (int file = 0; file < 8; file++) {
            int piece = gamestate.m_chessBoard[rank][file];
            if (piece != 0) {
                m_rect.x = file * SCREEN_WIDTH / 8;
                m_rect.y = rank * SCREEN_WIDTH / 8;
                SDL_RenderCopy(m_renderer, m_textures[m_pieceToImageIndex[piece]], NULL, &m_rect);
            }
        }
    }
}

void Screen::drawHighlights(const std::vector<Move> &legalMoves, int x, int y) {
    SDL_SetRenderDrawColor(m_renderer, 255, 255, 0, 128);
    for (const Move &move : legalMoves) {
        if (move.m_start_x == x && move.m_start_y == y) {
            m_rect.x = move.m_end_x * SCREEN_WIDTH / 8;
            m_rect.y = move.m_end_y * SCREEN_WIDTH / 8;
            SDL_RenderFillRect(m_renderer, &m_rect);
        }
    }
}


void Screen::drawChecksandPins(const GameState &gamestate) {
    //set up color red
    SDL_SetRenderDrawColor(m_renderer, 255, 128, 128, 128);
    //draw checks
    for (const std::vector<int> &check : gamestate.m_checks) {
            m_rect.x = check[0] * SCREEN_WIDTH / 8;
            m_rect.y = check[1] * SCREEN_WIDTH / 8;
            SDL_RenderFillRect(m_renderer, &m_rect);
    }
    //set up color color
    SDL_SetRenderDrawColor(m_renderer, 173, 216, 230, 128);
    //draw pins
    for (const std::vector<int> &pin : gamestate.m_pins) {
            m_rect.x = pin[0] * SCREEN_WIDTH / 8;
            m_rect.y = pin[1] * SCREEN_WIDTH / 8;
            SDL_RenderFillRect(m_renderer, &m_rect);
    }
}

void Screen::update(const GameState &gamestate, const std::vector<Move> &legalMoves, int x, int y, bool b_drawHighlights) {
    SDL_RenderClear(m_renderer);
    draw_board();

    if(b_drawHighlights)
        drawHighlights(legalMoves, x, y);

    drawChecksandPins(gamestate);
    drawPieces(gamestate);
    SDL_RenderPresent(m_renderer);
}

void Screen::close() {
    LOG("[LOG]: Closing the game.");
    for (int i = 0; i < 12; i++) {
        if (m_textures[i]) {
            SDL_DestroyTexture(m_textures[i]);
        }
    }

    // Cleanup text font
    if (m_font) {
        TTF_CloseFont(m_font);
        m_font = NULL;
    }

    TTF_Quit();
    IMG_Quit();
    SDL_DestroyRenderer(m_renderer);
    SDL_DestroyTexture(m_texture);
    SDL_DestroyTexture(m_boardTexture);
    SDL_DestroyWindow(m_window);
    SDL_Quit();
}
