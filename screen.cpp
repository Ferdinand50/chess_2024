#include "screen.h"


Screen::Screen() :
    m_window(NULL),m_renderer(NULL),m_texture(NULL),m_images{NULL}{
}

bool Screen::init(){

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		cout << "SDL init failed." << endl;
		return false;
	}

	m_window = SDL_CreateWindow("Chess",
	SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH,
			SCREEN_WIDTH, SDL_WINDOW_SHOWN);


	if (m_window == NULL) {
		SDL_Quit();
		return false;
	}

	m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	m_texture = SDL_CreateTexture(m_renderer, SDL_PIXELFORMAT_RGBA8888,
							SDL_TEXTUREACCESS_STATIC, SCREEN_WIDTH, SCREEN_WIDTH);

	if(m_renderer == NULL) {
		cout << "Could not create renderer" <<endl;
		SDL_DestroyWindow(m_window);
		SDL_Quit();
		return false;
	}

	if(m_texture == NULL) {
		cout << "Could not create texture" <<endl;
		SDL_DestroyRenderer(m_renderer);
		SDL_DestroyWindow(m_window);
		SDL_Quit();
		return false;
	}

    //enables transparency for drawHighlights
    SDL_SetRenderDrawBlendMode(m_renderer, SDL_BLENDMODE_BLEND);

    //setup width and height of squares used for drawing
    m_rect.w = SCREEN_WIDTH / 8;
    m_rect.h = SCREEN_WIDTH / 8;

    //precompute 8x8 board
    precomputeBoard();

    //load Images
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

    return true;
}


void Screen::precomputeBoard(){
    m_boardTexture = SDL_CreateTexture(m_renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, SCREEN_WIDTH, SCREEN_WIDTH);
    if (!m_boardTexture) {
        std::cerr << "Failed to create board texture! SDL_Error: " << SDL_GetError() << std::endl;
        return;
    }

    SDL_SetRenderTarget(m_renderer, m_boardTexture);

    bool toggle_color = 0;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            m_rect.x = j * SCREEN_WIDTH / 8;
            m_rect.y = i * SCREEN_WIDTH / 8;
            if (toggle_color)
                SDL_SetRenderDrawColor(m_renderer, 50, 50, 50, 255);
            else
                SDL_SetRenderDrawColor(m_renderer, 190, 190, 190, 255);
            SDL_RenderFillRect(m_renderer, &m_rect);
            if (j != 7) //needed for chess color pattern
                toggle_color = !toggle_color;
        }
    }

    SDL_SetRenderTarget(m_renderer, nullptr);
} 




void Screen::draw_board(){
    SDL_RenderCopy(m_renderer, m_boardTexture, nullptr, nullptr);
}


//TODO: use anti alising 
void Screen::draw_pieces(const GameState &gamestate){
    //iterate over board
    for(int rank=0; rank<8;rank++){
        for(int file=0; file<8;file++){
            if(gamestate.m_chessBoard[rank][file] != 0)
                {
                m_rect.x = file*SCREEN_WIDTH/8;
                m_rect.y = rank*SCREEN_WIDTH/8;
                m_texture = SDL_CreateTextureFromSurface(m_renderer, m_images[m_pieceToImageIndex[gamestate.m_chessBoard[rank][file]]]);
                SDL_RenderCopy(m_renderer,m_texture,NULL,&m_rect);
                }
        }    
    } 
}

void Screen::drawHighlights(const std::vector<Move> &legalMoves, int x, int y){
    SDL_SetRenderDrawColor(m_renderer, 255, 255, 0, 128);

    for (const Move &move : legalMoves) {
        if(move.m_start_x == x && move.m_start_y == y){
            m_rect.x = move.m_end_x * SCREEN_WIDTH/8;
            m_rect.y = move.m_end_y * SCREEN_WIDTH/8;
            SDL_RenderFillRect(m_renderer, &m_rect);
        }
    }
}


//TODO: use reference
void Screen::update(const GameState &gamestate, const std::vector<Move> &legalMoves, int x, int y, bool b_drawHighlights){
    SDL_RenderClear(m_renderer);
    //TODO: use precompied board texture
    draw_board();
    if(b_drawHighlights)
        drawHighlights(legalMoves, x, y);
    draw_pieces(gamestate);
    SDL_RenderPresent(m_renderer);
}



void Screen::close(){
    IMG_Quit();
	SDL_DestroyRenderer(m_renderer);
	SDL_DestroyTexture(m_texture);
	SDL_DestroyWindow(m_window);
	SDL_Quit();
}