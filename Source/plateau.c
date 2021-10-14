#include "../Headers/plateau.h"
#include <SDL2/SDL.h>   
#include <stdio.h>
#include <stdlib.h>



void initialisation_plateau(int array[][8]){

    for (int ligne = 0; ligne < TAILLE_PLATEAU; ligne++)
    {
        for (int colonne = 0; colonne < TAILLE_PLATEAU; colonne++)
        {
            array[ligne][colonne] = 0;
        }
        
    }

    afficher_plateau(array);
}

void initialisation_plateau_noir_blanc(int array[][8]){
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            array[i][j] = 0;
        }
        
    }
    
    afficher_plateau_blc_wht(array);

}


void afficher_plateau(int plateau[][8]){
    for (int ligne = 0; ligne < TAILLE_PLATEAU; ligne++)
    {
        printf("%d |",ligne+1);
        for (int colonne = 0; colonne < TAILLE_PLATEAU; colonne++)
        {
            printf(" %d ",plateau[ligne][colonne]);
        }
        printf("\n");
        
    }
    printf("\n");

}


void afficher_plateau_blc_wht(int plateau_blc_wht[][8]){
    for (int ligne = 0; ligne < TAILLE_PLATEAU; ligne++)
    {
        printf("%d |",ligne+1);
        for (int colonne = 0; colonne < TAILLE_PLATEAU; colonne++)
        {
            printf(" %d ",plateau_blc_wht[ligne][colonne]);
        }
        printf("\n");
        
    }
    printf("\n");

}

