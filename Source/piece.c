#include "../Headers/plateau.h"
#include "../Headers/piece.h"
#include <SDL2/SDL.h>   
#include <stdio.h>
#include <stdlib.h>

void init_pion(Piece piece[],int taille_array,int is_piece_blanche,SDL_Renderer* pRenderer);
void init_tour(Piece piece[],int taille_array,int is_piece_blanche,SDL_Renderer* pRenderer);
void init_cavalier(Piece piece[],int taille_array,int is_piece_blanche,SDL_Renderer* pRenderer);
void init_fou(Piece piece[],int taille_array,int is_piece_blanche,SDL_Renderer* pRenderer);
void init_roi(Piece piece[],int taille_array,int is_piece_blanche,SDL_Renderer* pRenderer);
void init_reine(Piece piece[],int taille_array,int is_piece_blanche,SDL_Renderer* pRenderer);
int is_case_contain_piece(int value);



void initialiser_piece(int plateau[][8]){

    int rangee_blanc = 1;
    int rangee_noir = 6;
    int ind_piece_up = 2;
    int ind_piece_down = 4;

    printf("Initialisation des pieces...\n");

    for (int i = 0; i < TAILLE_PLATEAU; i++)
    {
        plateau[rangee_blanc][i] = PION;
        plateau[rangee_noir][i] = PION;
        if (i > NOMBRE_PIECE-2)
        {
            plateau[rangee_blanc-1][i] = ind_piece_down;
            plateau[rangee_noir+1][i] = ind_piece_down;
            ind_piece_down--;

        }
        else{
        plateau[rangee_blanc-1][i] = ind_piece_up;
        plateau[rangee_noir+1][i] = ind_piece_up;
        ind_piece_up++;
        }

        
    }

    
    afficher_plateau(plateau);
}


void initialiser_black_and_white_piece(int plateau_blc_wht[][8]){
    //1 = noir
    //2 = blanc

    for (int i = 0; i < 8; i++)
    {
        plateau_blc_wht[0][i] = 1;
        plateau_blc_wht[1][i] = 1;

        plateau_blc_wht[6][i] = 2;
        plateau_blc_wht[7][i] = 2;
    }
    
    afficher_plateau(plateau_blc_wht);
}


void init_pion(Piece piece[],int taille_array,int is_piece_blanche,SDL_Renderer* pRenderer){
    int xBuf;
    int yBuf;
    
    if (is_piece_blanche)
    {
        xBuf = 10;
        yBuf = 610;
    }
    else{        
        xBuf = 10;
        yBuf = 110;
    }

    for (int i = 0; i < taille_array; i++)
    {
        if (is_piece_blanche)
        {

            piece[i].surface_piece = SDL_LoadBMP("../Img/Pion.bmp");
            piece[i].piece_blanche = is_piece_blanche;
            piece[i].rect.w = 90;
            piece[i].rect.h = 90;
            piece[i].rect.y = yBuf;
            piece[i].rect.x = xBuf;
            piece[i].texture_piece = SDL_CreateTextureFromSurface(pRenderer,piece[i].surface_piece);
            SDL_FreeSurface(piece[i].surface_piece);

        }
        else
        {
            piece[i].surface_piece = SDL_LoadBMP("../Img/Pion_noir.bmp");
            piece[i].piece_blanche = is_piece_blanche;
            piece[i].rect.w = 90;
            piece[i].rect.h = 90;
            piece[i].rect.y = yBuf;
            piece[i].rect.x = xBuf;
            piece[i].texture_piece = SDL_CreateTextureFromSurface(pRenderer,piece[i].surface_piece);
            SDL_FreeSurface(piece[i].surface_piece);
            
        }
        
        xBuf += 100;
    }
    
}

void init_tour(Piece piece[],int taille_array,int is_piece_blanche,SDL_Renderer* pRenderer){

    int x[2] = {10,710};
        
        if (is_piece_blanche)
        {
            for (int  i = 0; i < taille_array; i++)
            {
                piece[i].surface_piece = SDL_LoadBMP("../Img/Tour.bmp");
                piece[i].piece_blanche = is_piece_blanche;
                piece[i].rect.w = 90;
                piece[i].rect.h = 90;
                piece[i].rect.y = 710;
                piece[i].rect.x = x[i];
                piece[i].texture_piece = SDL_CreateTextureFromSurface(pRenderer,piece[i].surface_piece);
                SDL_FreeSurface(piece[i].surface_piece);

            }
        }else
        {
            
            for (int  i = 0; i < taille_array; i++)
            {
                piece[i].surface_piece = SDL_LoadBMP("../Img/Tour_noir.bmp");
                piece[i].piece_blanche = is_piece_blanche;
                piece[i].rect.w = 90;
                piece[i].rect.h = 90;
                piece[i].rect.y = 10;
                piece[i].rect.x = x[i];
                piece[i].texture_piece = SDL_CreateTextureFromSurface(pRenderer,piece[i].surface_piece);
                SDL_FreeSurface(piece[i].surface_piece);

            }
        }
        
        

}

void init_cavalier(Piece piece[],int taille_array,int is_piece_blanche,SDL_Renderer* pRenderer){

    int x[2] = {110,610};
        
        if (is_piece_blanche)
        {
            for (int  i = 0; i < taille_array; i++)
            {
                piece[i].surface_piece = SDL_LoadBMP("../Img/Cavalier.bmp");
                piece[i].piece_blanche = is_piece_blanche;
                piece[i].rect.w = 90;
                piece[i].rect.h = 90;
                piece[i].rect.y = 710;
                piece[i].rect.x = x[i];
                piece[i].texture_piece = SDL_CreateTextureFromSurface(pRenderer,piece[i].surface_piece);
                SDL_FreeSurface(piece[i].surface_piece);

            }
        }else
        {
            
            for (int  i = 0; i < taille_array; i++)
            {
                piece[i].surface_piece = SDL_LoadBMP("../Img/Cavalier_noir.bmp");
                piece[i].piece_blanche = is_piece_blanche;
                piece[i].rect.w = 90;
                piece[i].rect.h = 90;
                piece[i].rect.y = 10;
                piece[i].rect.x = x[i];
                piece[i].texture_piece = SDL_CreateTextureFromSurface(pRenderer,piece[i].surface_piece);
                SDL_FreeSurface(piece[i].surface_piece);

            }
        }
        
        

}

void init_fou(Piece piece[],int taille_array,int is_piece_blanche,SDL_Renderer* pRenderer){

    int x[2] = {210,510};
        
        if (is_piece_blanche)
        {
            for (int  i = 0; i < taille_array; i++)
            {
                piece[i].surface_piece = SDL_LoadBMP("../Img/Fou.bmp");
                piece[i].piece_blanche = is_piece_blanche;
                piece[i].rect.w = 90;
                piece[i].rect.h = 90;
                piece[i].rect.y = 710;
                piece[i].rect.x = x[i];
                piece[i].texture_piece = SDL_CreateTextureFromSurface(pRenderer,piece[i].surface_piece);
                SDL_FreeSurface(piece[i].surface_piece);

            }
        }else
        {
            
            for (int  i = 0; i < taille_array; i++)
            {
                piece[i].surface_piece = SDL_LoadBMP("../Img/Fou_noir.bmp");
                piece[i].piece_blanche = is_piece_blanche;
                piece[i].rect.w = 90;
                piece[i].rect.h = 90;
                piece[i].rect.y = 10;
                piece[i].rect.x = x[i];
                piece[i].texture_piece = SDL_CreateTextureFromSurface(pRenderer,piece[i].surface_piece);
                SDL_FreeSurface(piece[i].surface_piece);

            }
        }
        
        

}

void init_roi(Piece piece[],int taille_array,int is_piece_blanche,SDL_Renderer* pRenderer){

    int x = 410;
        
        if (is_piece_blanche)
        {
                piece[0].surface_piece = SDL_LoadBMP("../Img/Roi.bmp");
                piece[0].piece_blanche = is_piece_blanche;
                piece[0].rect.w = 90;
                piece[0].rect.h = 90;
                piece[0].rect.y = 710;
                piece[0].rect.x = x;
                piece[0].texture_piece = SDL_CreateTextureFromSurface(pRenderer,piece[0].surface_piece);
                SDL_FreeSurface(piece[0].surface_piece);

        }else
        {
            
                piece[0].surface_piece = SDL_LoadBMP("../Img/Roi_noir.bmp");
                piece[0].piece_blanche = is_piece_blanche;
                piece[0].rect.w = 90;
                piece[0].rect.h = 90;
                piece[0].rect.y = 10;
                piece[0].rect.x = x;
                piece[0].texture_piece = SDL_CreateTextureFromSurface(pRenderer,piece[0].surface_piece);
                SDL_FreeSurface(piece[0].surface_piece);

        }
        
        

}

void init_reine(Piece piece[],int taille_array,int is_piece_blanche,SDL_Renderer* pRenderer){

    int x = 310;
        
        if (is_piece_blanche)
        {
                piece[0].surface_piece = SDL_LoadBMP("../Img/Reine.bmp");
                piece[0].piece_blanche = is_piece_blanche;
                piece[0].rect.w = 90;
                piece[0].rect.h = 90;
                piece[0].rect.y = 710;
                piece[0].rect.x = x;
                piece[0].texture_piece = SDL_CreateTextureFromSurface(pRenderer,piece[0].surface_piece);
                SDL_FreeSurface(piece[0].surface_piece);

        }else
        {
            
                piece[0].surface_piece = SDL_LoadBMP("../Img/Reine_noir.bmp");
                piece[0].piece_blanche = is_piece_blanche;
                piece[0].rect.w = 90;
                piece[0].rect.h = 90;
                piece[0].rect.y = 10;
                piece[0].rect.x = x;
                piece[0].texture_piece = SDL_CreateTextureFromSurface(pRenderer,piece[0].surface_piece);
                SDL_FreeSurface(piece[0].surface_piece);

        }
        

}


int is_case_contain_piece(int value){
    if (value != 0)
    {
        return 1;
    }
return 0;
}



