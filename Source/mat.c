#include "../Headers/piece.h"


int is_king_echec(int plateau[][8],int plateau_color[][8]){
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


    //check roi blanc 2
    if ((plateau_color[xBlanc-1][yBlanc] ||
        plateau_color[xBlanc-1][yBlanc-1] ||
        plateau_color[xBlanc-1][yBlanc+1] ||
        plateau_color[xBlanc][yBlanc+1] ||
        plateau_color[xBlanc][yBlanc-1]) != 2)
    {
        //On verifie jouant tout les coups possible autour du roi
        printf("Checking 2 :!\n ");
    }
    
    //printf("[xBlanc-1][yBlanc] : %d\n",plateau_color[xBlanc-1][yBlanc]);
    //printf("[xBlanc-1][yBlanc-1] : %d\n",plateau_color[xBlanc-1][yBlanc-1]);
    //printf("[xBlanc-1][yBlanc+1] : %d\n",plateau_color[xBlanc-1][yBlanc+1]);
    //printf("[xBlanc][yBlanc+1] : %d\n",plateau_color[xBlanc][yBlanc+1]);
    //printf("[xBlanc][yBlanc-1] : %d\n",plateau_color[xBlanc][yBlanc-1]);



}




