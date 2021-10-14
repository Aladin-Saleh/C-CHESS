#include <SDL2/SDL.h>

typedef struct Piece Piece;
struct Piece
{
    int val_piece;
    int piece_blanche;
    SDL_Surface* surface_piece;
    SDL_Texture* texture_piece;
    SDL_Rect rect;
};

#define PION 1
#define TOUR 2
#define CAVALIER 3
#define FOU 4
#define ROI 6
#define REINE 5
#define NOMBRE_PIECE 6


Piece pions_blanc[8];
Piece pions_noir[8];

Piece tour_blanc[2];
Piece tour_noir[2];

Piece cavalier_blanc[2];
Piece cavalier_noir[2];

Piece fou_blanc[2];
Piece fou_noir[2];

Piece roi_blanc[1];
Piece roi_noir[1];

Piece reine_blanc[1];
Piece reine_noir[1];


void init_pion(Piece piece[],int taille_array,int is_piece_blanche,SDL_Renderer* pRenderer);
void init_tour(Piece piece[],int taille_array,int is_piece_blanche,SDL_Renderer* pRenderer);
void init_cavalier(Piece piece[],int taille_array,int is_piece_blanche,SDL_Renderer* pRenderer);
void init_fou(Piece piece[],int taille_array,int is_piece_blanche,SDL_Renderer* pRenderer);
void init_roi(Piece piece[],int taille_array,int is_piece_blanche,SDL_Renderer* pRenderer);
void init_reine(Piece piece[],int taille_array,int is_piece_blanche,SDL_Renderer* pRenderer);
void initialiser_piece(int plateau[][8]);
int is_case_contain_piece(int value);

/*
void deplacement_pion();
void deplacement_tour();
void deplacement_cavalier();
void deplacement_fou();
void deplacement_roi();
void deplacement_reine();
*/