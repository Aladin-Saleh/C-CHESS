#include "../Headers/piece.h"
#include <SDL2/SDL.h>   
#include "../Headers/map.h"

void promotion(SDL_Renderer *pRenderer,Map *map_image,int plateau[][8]);
int check_pions(Piece pion_to_check[]);


void promotion(SDL_Renderer *pRenderer,Map *map_image,int plateau[][8]){
    int new_value_piece = 0;//Valeur de la nouvelle piece
    int res;//Variable de reponse
    int id_promote;
    int id;
    int x,y;
    int n = check_pions(pions_noir);
  /*  if (check_pions(pions_blanc) != -1)
    {
        id = check_pions(pions_noir);
        printf("PROMOTION\nEntrer une nouvelle valeur pour promouvoir votre piece !\n2 : TOUR\n3 : CAVALIER\n4 : FOU\n5 : DAME\n");
        res = scanf("%d",&new_value_piece);
        pions_blanc[check_pions(pions_blanc)].surface_piece = SDL_LoadBMP(get_from_map(map_image,new_value_piece)); 
        pions_blanc[check_pions(pions_blanc)].texture_piece = SDL_CreateTextureFromSurface(pRenderer,pions_blanc[check_pions(pions_blanc)].surface_piece);
        SDL_FreeSurface(pions_blanc[check_pions(pions_blanc)].surface_piece);
    }*/

    if (n != -1)
    {
        id = check_pions(pions_noir);
        printf("PROMOTION\nEntrer une nouvelle valeur pour promouvoir votre piece !\n2 : TOUR\n3 : CAVALIER\n4 : FOU\n5 : DAME\n");
        res = scanf("%d",&new_value_piece);
        printf("%s\n",get_from_map(map_image,new_value_piece));
        printf("X : %d Y:%d\n",pions_noir[id].rect.y/100,pions_noir[id].rect.x/100);
        x = pions_noir[id].rect.y/100;
        y = pions_noir[id].rect.x/100;

        plateau[x][y] = new_value_piece;
        printf("O_O\n");

        //get_from_map(map_image,new_value_piece)
        //pions_blanc[id].surface_piece = SDL_LoadBMP("../Img/Tour.bmp"); 
        //printf("O_O\n");
        //pions_noir[id].texture_piece = SDL_CreateTextureFromSurface(pRenderer,pions_noir[id].surface_piece);
        //SDL_FreeSurface(pions_noir[1].surface_piece);
        //pions_noir[id].surface_piece = SDL_LoadBMP("../Img/Tour.bmp");
        //pions_noir[id].texture_piece = SDL_CreateTextureFromSurface(pRenderer,pions_noir[id].surface_piece);
        //SDL_FreeSurface(pions_noir[id].surface_piece);
    }
}


/**
 * @brief Verifie si un pions blanc a atteint la zone enemi afin de promouvoir ce pion
 * Si il trouve un pions blanc dans la zone enemi, il retourne 
 * 
 * @return int : indice du pions ayant atteint la zone enemi. 
 * sinon retourne -1 dans le cas ou rien n'a été trouvé
 */
int check_pions(Piece pion_to_check[]){
    for (int i = 0; i < 8; i++)
    {
        if (pion_to_check[i].rect.y == 10 )
        {
            return i;
        }
    }
    return -1;
}

