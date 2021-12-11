#include "../Headers/piece.h"


int is_king_echec(int plateau[][8],int plateau_color[][8],SDL_Renderer *pRenderer){
    //1er etape verifier que le roi et entouré et qu'il n'y pas de cavalier autour de lui
    //Si roi pas entouré de piece à lui, verifier les diagonale,les horizontale,les verticales




    //Récuperation de la position des deux rois
    //Roi noir
    int xNoir = roi_blanc[0].rect.y/100;
    int yNoir = roi_blanc[0].rect.x/100;
    //printf("X : %d\nY : %d\n---\n",xNoir,yNoir);
    //Roi blanc
    int xBlanc = roi_noir[0].rect.y/100;
    int yBlanc = roi_noir[0].rect.x/100;
    //printf("X : %d\nY : %d\n---\n",xBlanc,yBlanc);
    int echec_fou_dd = -1;
    int echec_fou_dg = -1;

    int echec_fou_dd_bas = -1;
    int echec_fou_dg_bas = -1;

    int horizontal = -1;
    int vertical = -1;

    //check roi blanc 2
    if (plateau_color[xBlanc-1][yBlanc] != 2||
        plateau_color[xBlanc-1][yBlanc-1] != 2 ||
        plateau_color[xBlanc-1][yBlanc+1] != 2 ||
        plateau_color[xBlanc][yBlanc+1] != 2 ||
        plateau_color[xBlanc][yBlanc-1] != 2 )
    {
        //On verifie en jouant tout les coups possible autour du roi
        printf("Checking 2 :!\n ");
        //Fou
        for (int i = 1; i < 8-yBlanc; i++)
        {
            //Diagonale droite
            if (plateau_color[(xBlanc)-i][(yBlanc)+i] == 1 && echec_fou_dd != 0 )
            {
                echec_fou_dd = 1;
            }
            else if(plateau_color[xBlanc-i][yBlanc+i] == 2){//Si on trouve une piece allié sur le chemin on arrete de verifier
                echec_fou_dd = 0;
            }   
            //Diagonale gauche
            if (plateau_color[(xBlanc)-i][(yBlanc)-i] == 1 && echec_fou_dg != 0 )
            {
                echec_fou_dg = 1;
            }
            else if(plateau_color[xBlanc-i][yBlanc-i] == 2){
                echec_fou_dg = 0;
            } 
            
        }


        for (int j = 1; j < 8-xBlanc; j++)
        {
            printf("Fou dd :%d\n",plateau_color[xBlanc+j][yBlanc+j]);
                        //Diagonale droite bas
            if (plateau_color[(xBlanc)+j][(yBlanc)+j] == 1 && echec_fou_dd_bas != 0 )
            {
                echec_fou_dd_bas = 1;
            }
            else if(plateau_color[xBlanc+j][yBlanc+j] == 2){
                echec_fou_dd_bas = 0;
            }   

            //Diagonale gauche bas
            if (plateau_color[(xBlanc)+j][(yBlanc)-j] == 1 && echec_fou_dg_bas != 0 )
            {
                echec_fou_dg_bas = 1;
            }
            else if(plateau_color[xBlanc+j][yBlanc-j] == 2){
                echec_fou_dg_bas = 0;
            } 
        }

        
        //int horizontal = -1;
        //int vertical = -1;
        for (int k = 1; k < 8; k++)
        {
            printf("VER : %d\n ",plateau_color[(xBlanc)-k][(yBlanc)]);
            if (plateau_color[(xBlanc)-k][(yBlanc)] == 1 
            && (plateau[(xBlanc)-k][(yBlanc)] == 2 || plateau[(xBlanc)-k][(yBlanc)] == 5 )
            && vertical != 0)
            {
                vertical = 1;
            }
            else if(plateau_color[(xBlanc)-k][(yBlanc)] == 2){
                vertical = 0;
            }
            
        }
            



        if (echec_fou_dd == 1 || echec_fou_dg == 1 || echec_fou_dg_bas == 1 || echec_fou_dd_bas == 1 || vertical == 1)
        {
            roi_noir[0].surface_piece = SDL_LoadBMP("../Img/Roi__echec.bmp");
            roi_noir[0].texture_piece = SDL_CreateTextureFromSurface(pRenderer,roi_noir[0].surface_piece);
            SDL_FreeSurface(roi_noir[0].surface_piece);
            
            printf("ECHEC\n");
        }
        else{
            roi_noir[0].surface_piece = SDL_LoadBMP("../Img/Roi.bmp");
            roi_noir[0].texture_piece = SDL_CreateTextureFromSurface(pRenderer,roi_noir[0].surface_piece);
            SDL_FreeSurface(roi_noir[0].surface_piece);

            printf("PAS ECHEC\n");
        }
        
        
    }
    




}




