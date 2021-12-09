#include "../Headers/piece.h"
#include <SDL2/SDL.h>   
int check_white_pions();
int promotion(){

}


int check_white_pions(){
    int new_value_piece;
    for (int i = 0; i < 8; i++)
    {
        if (pions_noir[i].rect.y == 10)
        {
           printf("PROMOTION\n");
           scanf("Nouvelle valeur de la piece : %d",&new_value_piece);
        }
        
    }

    
}

