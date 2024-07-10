#include "screen.h"
#include <iostream>
#include "Gamestate.h"
#include <map>




// void drawPieces(SDL_Renderer *renderer, int SQUARE_SIZE)
// {
//     //int chessBoard[8][8]

//     SDL_Surface *surface = IMG_Load( "src/images/wB.png" ); 
//     SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);

    
    
//     SDL_Rect destRect = {100, 100, 200, 200}; // Destination rectangle for rendering (x, y, width, height)
//     SDL_RenderCopy(renderer, texture, nullptr, &destRect);
// }


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


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

	m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_PRESENTVSYNC);
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

    SDL_SetRenderDrawColor(m_renderer, 255, 255, 255, 255); // Background color
    SDL_RenderClear(m_renderer);
    SDL_RenderPresent(m_renderer);

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



void Screen::draw_board(){
    SDL_Rect rect;
    bool toggle_color = 0;
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            rect.x = j * SCREEN_WIDTH/8;
            rect.y = i * SCREEN_WIDTH/8;
            rect.w = SCREEN_WIDTH/8;
            rect.h = SCREEN_WIDTH/8;
            if (toggle_color)
                SDL_SetRenderDrawColor(m_renderer, 50, 50, 50, 255);
            else
                SDL_SetRenderDrawColor(m_renderer, 255, 255, 255, 255);
            SDL_RenderFillRect(m_renderer, &rect);
            if(j != 7) //needed for chess color pattern
            toggle_color = !toggle_color;
        }
    }
}



// void Screen::draw_bitboard_pieces(unsigned long long bitboards[12]){
//     //init rect
//     SDL_Rect rect;
//     rect.w = SCREEN_WIDTH/8;
//     rect.h = SCREEN_WIDTH/8;
//     //iterate over bitboards
//     for(int i=0; i<12;i++){
//         for(int rank=0; rank<8;rank++){
//             for(int file=0; file<8;file++){
//                 int square=rank*8 +file;
//                 if(get_bit(bitboards[i],square)){
//                     rect.x = file*SCREEN_WIDTH/8;
//                     rect.y = rank*SCREEN_WIDTH/8;
//                     m_texture = SDL_CreateTextureFromSurface(m_renderer, m_images[i]);
//                     SDL_RenderCopy(m_renderer,m_texture,NULL,&rect);
//                         }
//             }    
//         }
//     }   
//     SDL_RenderPresent(m_renderer); 
// }



void Screen::update(){
    draw_board();
    //draw_bitboard_pieces(bitboards);
    SDL_RenderPresent(m_renderer);

}


// void Screen::draw_hightlight(unsigned long long bitboards[12]){
    
//     unsigned long long bitboard = 4ULL;

//     //init rect
//     SDL_Rect rect;
//     rect.w = SCREEN_WIDTH/8;
//     rect.h = SCREEN_WIDTH/8;
//     SDL_SetRenderDrawColor(m_renderer, 255, 255, 0, 100);
//     //iterate over bitboards
//     for(int rank=0; rank<8;rank++){
//         for(int file=0; file<8;file++){
//             int square=rank*8 +file;
//             if(get_bit(bitboard,square)){
//                 rect.x = file*SCREEN_WIDTH/8;
//                 rect.y = rank*SCREEN_WIDTH/8;
//                 SDL_SetRenderDrawBlendMode(m_renderer, SDL_BLENDMODE_BLEND);
//                 SDL_RenderFillRect(m_renderer, &rect);
//             }

//         }    
//     } 
//     draw_bitboard_pieces(bitboards);
    
// }


void Screen::close(){
    	
    IMG_Quit();
	SDL_DestroyRenderer(m_renderer);
	SDL_DestroyTexture(m_texture);
	SDL_DestroyWindow(m_window);
	SDL_Quit();
}