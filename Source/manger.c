#include <stdio.h>
#include <stdlib.h>
#include "../Headers/map.h"
#include "../Headers/piece.h"
#include "../Headers/screen.h"
#include <SDL2/SDL.h>

int is_movable(int plateau_blc_wht[][8],int last_piece_value,int new_piece_value,int last_piece_color,int new_piece_color,int l,int c,int nl,int nc);

void manger_piece(int value_piece_to_eat,int indice_piece,int is_black){
    switch (value_piece_to_eat)
    {
    case 1:
    if (is_black == 1)
    {
        printf("indice_piece eat : %d\n",indice_piece);
        pions_blanc[indice_piece].rect.h = 0;
        pions_blanc[indice_piece].rect.w = 0;
    }
    else if(is_black == 2){
        pions_noir[indice_piece].rect.h = 0;
        pions_noir[indice_piece].rect.w = 0;
    }
        break;
    case 2:
    if (is_black == 1)
    {
        tour_blanc[indice_piece].rect.h = 0;
        tour_blanc[indice_piece].rect.w = 0;
    }
    else if(is_black == 2){
        tour_noir[indice_piece].rect.h = 0;
        tour_noir[indice_piece].rect.w = 0;
    }
        break;
    case 3:
    if (is_black == 1)
    {
        cavalier_blanc[indice_piece].rect.h = 0;
        cavalier_blanc[indice_piece].rect.w = 0;
    }
    else if(is_black == 2){
        cavalier_noir[indice_piece].rect.h = 0;
        cavalier_noir[indice_piece].rect.w = 0;
    }
        break;
    case 4:
    if (is_black == 1)
    {
        fou_blanc[indice_piece].rect.h = 0;
        fou_blanc[indice_piece].rect.w = 0;
    }
    else if(is_black == 2){
        fou_noir[indice_piece].rect.h = 0;
        fou_noir[indice_piece].rect.w = 0;
    }
    
        
        break;
    case 5:
    if (is_black == 1)
    {
        reine_blanc[indice_piece].rect.h = 0;
        reine_blanc[indice_piece].rect.w = 0;
    }
    else if(is_black == 2){
        reine_noir[indice_piece].rect.h = 0;
        reine_noir[indice_piece].rect.w = 0;
    }
    
        
        break;
    case 6:
    if (is_black == 1)
    {
        roi_blanc[indice_piece].rect.h = 0;
        roi_blanc[indice_piece].rect.w = 0;
    }
    else if(is_black == 2){
        roi_noir[indice_piece].rect.h = 0;
        roi_noir[indice_piece].rect.w = 0;
    }
        break;
    }
}




/**
 * @brief 
 * Fonction qui va lire le tableau des couleur (noir et blanc)
 * Si le roi est entouré de piece de la meme couleur que lui on suppose qu'il est en sécurité (sauf pour le cavalier).
 * 
 */
int can_we_eat_king(){

}

int is_movable(int plateau_blc_wht[][8],int last_piece_value,int new_piece_value,int last_piece_color,int new_piece_color,int l,int c,int nl,int nc){
    //PION :
    //diagonale gauche : ligne : -1 colonne : -1
    int dgn_gauche_l = 0;
    int dgn_gauche_c = 0;
    //diagonale droite : ligne : +1 colonne : +1
    int dgn_droite_l = 0;
    int dgn_droite_c = 0;
    int count = 0;
    //avancer : ligne : 1 colonne : +1
    
    if (last_piece_color == new_piece_color)
    {
        return -1;
    }
    switch (last_piece_value)
    {
    case PION:
        if (plateau_blc_wht[nl][nc] != 0)
        {
            return -1;
        }
        else{
            if ((l-1 == nl && c == nc && last_piece_color == 2) || (l+1 == nl && c == nc && last_piece_color == 1))
            {
                printf("1\n");
                return 1;
            }
            if ((l-2 == nl && c == nc && last_piece_color == 2 && l == 6) || (l+2 == nl && c == nc && last_piece_color == 1 && l == 1 ))
            {
                printf("2\n");
                return 1;
            }

            if ((l-2 == nl && last_piece_color == 2 && l == 6) || (l+2 == nl && c == nc && last_piece_color == 1 && l == 1 ))
            {
                printf("4\n");
                return 1;
            }
        }
        
        //diagonale droite
        if (c+1 == nc && l-1 == nl && plateau_blc_wht[nl][nc] == 1)
        {
            return 1;
        }
        //diagonale gauche
        if (c-1 == nc && l-1 == nl && plateau_blc_wht[nl][nc] == 1)
        {
            return 1;
        }     

        //diagonale gauche bas            
        if (c-1 == nc && l+1 == nl && plateau_blc_wht[nl][nc] == 2)
        {
            return 1;
        }
        //diagonale droite bas
        if (c+1 == nc && l+1 == nl && plateau_blc_wht[nl][nc] == 2)
        {
            return 1;
        }   
        
            return -1;
        break;
    case TOUR:

        if (c == nc || l == nl)
        {

            if (l != nl)
            {
                if (l > nl)//Remplacer par une fonction 
                {
                    for (int i = nl; i < l; i++)
                    {
                        printf("[%d][%d]::%d\n",i,c,plateau_blc_wht[i][c]);
                        if (plateau_blc_wht[i][c] == last_piece_color)
                        {
                            return -1;
                        }

                    }
                }
                else{
                    printf("L : %d \nNL : %d\n",l,nl);
                    for (int i = nl; i > l; i--)
                    {
                        printf("[%d][%d]::%d\n",i,c,plateau_blc_wht[i][c]);
                        if (plateau_blc_wht[i][c] == last_piece_color)
                        {
                            return -1;
                        }

                    }
                }
                
                
            }else if(c != nc){
                if (c > nc)//Remplacer par une fonction 
                {
                    for (int i = nc; i < c; i++)
                    {
                        printf("[%d][%d]::%d\n",l,i,plateau_blc_wht[l][i]);
                        if (plateau_blc_wht[l][i] == last_piece_color)
                        {
                            return -1;
                        }
                    }
                }
                else{
                    for (int i = nc; i > c; i--)
                    {
                        printf("[%d][%d]::%d\n",l,i,plateau_blc_wht[l][i]);
                        if (plateau_blc_wht[l][i] == last_piece_color)
                        {
                            return -1;
                        }

                    }
                }
            }
            
            return 1;
        }
        return -1;
        
        break;
    case FOU:
        for (int i = 0; i < 8; i++)
        {
            count = abs(c-nc);
            //diagonale droite
            if (c+i == nc && l-i == nl)
            {
                printf("Count : %d\n",count);
                for (int j = 1; j < count; j++)
                {

                    printf("fou[%d][%d] : %d\n",c+j,l-j,plateau_blc_wht[l-j][c+j]);
                    if (plateau_blc_wht[l-j][c+j] == last_piece_color)
                    {
                        return -1;
                    }
                    

                }
                    
                return 1;
            }
            //diagonale gauche
            if (c-i == nc && l-i == nl)
            {                
                printf("Count : %d\n",count);
                for (int j = 1; j < count; j++)
                {

                    printf("fou[%d][%d] : %d\n",c+j,l-j,plateau_blc_wht[l-j][c+j]);
                    if (plateau_blc_wht[l-j][c-j] == last_piece_color)
                    {
                        return -1;
                    }
                    

                }
                
                return 1;
            }
            //diagonale gauche bas            
            if (c-i == nc && l+i == nl)
            {
                for (int j = 1; j < count; j++)
                {

                    //printf("fou[%d][%d] : %d\n",c+j,l-j,plateau_blc_wht[l-j][c+j]);
                    if (plateau_blc_wht[l+j][c-j] == last_piece_color)
                    {
                        return -1;
                    }
                    

                }
                return 1;
            }
            //diagonale droite bas
            if (c+i == nc && l+i == nl)
            {
                for (int j = 1; j < count; j++)
                {

                    if (plateau_blc_wht[l+j][c+j] == last_piece_color)
                    {
                        return -1;
                    }
                    

                }
                return 1;
            }
            
        }
        return -1;
        
        break;
    case CAVALIER:
        //diagonale droite
        if (c+1 == nc && l-2 == nl)
        {
            return 1;
        }
        //diagonale gauche
        if (c-1 == nc && l-2 == nl)
        {
            return 1;
        }     

        //diagonale gauche bas            
        if (c-1 == nc && l+2 == nl)
        {
            return 1;
        }
        //diagonale droite bas
        if (c+1 == nc && l+2 == nl)
        {
            return 1;
        }  
        //diagonale droite
        if (c+2 == nc && l-1 == nl)
        {
            return 1;
        }
        //diagonale gauche
        if (c-2 == nc && l-1 == nl)
        {
            return 1;
        }     
        //diagonale gauche bas            
        if (c-2 == nc && l+1 == nl)
        {
            return 1;
        }
        //diagonale droite bas
        if (c+2 == nc && l+1 == nl)
        {
            return 1;
        }         
        return -1;
        break;
    case REINE:
        //droite et gauche
        if (c == nc || l == nl)
        {
            return 1;
        }
        for (int i = 0; i < 8; i++)
        {
            //diagonale droite
            if (c+i == nc && l-i == nl)
            {
                return 1;
            }
            //diagonale gauche
            if (c-i == nc && l-i == nl)
            {
                return 1;
            }
            //diagonale gauche bas            
            if (c-i == nc && l+i == nl)
            {
                return 1;
            }
            //diagonale droite bas
            if (c+i == nc && l+i == nl)
            {
                return 1;
            }
            
        }
        return -1;

        break; 
    case ROI:
        
        //diagonale droite
        if (c+1 == nc && l-1 == nl)
        {
            return 1;
        }
        //diagonale gauche
        if (c-1 == nc && l-1 == nl)
        {
            return 1;
        }     

        //diagonale gauche bas            
        if (c-1 == nc && l+1 == nl)
        {
            return 1;
        }
        //diagonale droite bas
        if (c+1 == nc && l+1 == nl)
        {
            return 1;
        }   
        
        if (c == nc || l-1 == nl)
        {
            return 1;
        }
        
        if (c == nc || l+1 == nl)
        {
            return 1;
        }

        if (c-1 == nc || l == nl)
        {
            return 1;
        }

        if (c+1 == nc || l == nl)
        {
            return 1;
        }

        return -1;
        break;                       
    }
}

int piece_around(){

}
//check fou 
//check tour 
//check reine

int check_fou(int plt[][8],int current_pos,int dest_pos){

    
}

int check_tour(){

}