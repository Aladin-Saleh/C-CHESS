#include "../Headers/plateau.h"
#include "../Headers/piece.h"
#include "../Headers/screen.h"
#include <stdio.h>
#include <stdlib.h>



#define PION 1
#define TOUR 2
#define CAVALIER 3

int main(int argc, char const *argv[])
{
    //Map m_blanc;
    //Map m_noir;



    //printf("%s\n",get_from_map(&m_blanc,1));
    //printf("%s\n",get_from_map(&m_blanc,6));


    int plateau[TAILLE_PLATEAU][TAILLE_PLATEAU];
    int plateau_blc_and_wht[TAILLE_PLATEAU][TAILLE_PLATEAU];

    //Creation des plateaux
    initialisation_plateau(plateau);
    initialisation_plateau_noir_blanc(plateau_blc_and_wht);

    //Creation des pieces
    initialiser_black_and_white_piece(plateau_blc_and_wht);
    initialiser_piece(plateau);

    initialiser_fenetre(plateau,plateau_blc_and_wht);

    
    return 0;
}


