#include <SDL2/SDL.h>
    

#define WIDTH 800
#define HEIGHT 800

typedef struct Choice Choice;
struct Choice
{
    int mvmt_count;
    SDL_Rect choice_info;
};



void initialiser_fenetre(int plateau[][8],int plateau_blc_and_wht[][8]);
int get_piece_indice(int value,int colonne, int ligne);