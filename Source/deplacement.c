#include "../Headers/deplacement.h"



void deplacement_pion(int plateau[][8],Choice* c,int ligne,int colonne,int color);
void deplacement_tour(int plateau[][8],Choice* c,int ligne,int colonne);
void deplacement_cavalier(int plateau[][8],Choice* c,int ligne,int colonne);
void deplacement_fou(int plateau[][8],Choice* c,int ligne,int colonne);
void deplacement_roi(int plateau[][8],Choice* c,int ligne,int colonne);
void deplacement_reine(int plateau[][8],Choice* c,int ligne,int colonne);

/**
 * @brief 
 * 
 * @param plateau 
 * @param c 
 * @param ligne 
 * @param colonne 
 * @param color 1 ou -1
 */
void deplacement_pion(int plateau[][8],Choice* c,int ligne,int colonne,int color){
    printf("Deplacement de la piece : pion\n");
            if (ligne == 6)
            {
                c[0].choice_info.h = 200;
            }else{
                c[0].choice_info.h = 100;
            }
            c[0].choice_info.w = 100;
            c[0].choice_info.x = (colonne * 100) ;
            c[0].choice_info.y = (ligne * 100) + (color * 200) ;   
}



void deplacement_tour(int plateau[][8],Choice* c,int ligne,int colonne){
    printf("Deplacement de la piece : tour\n");
            c[0].choice_info.h = 100;
            c[0].choice_info.w = 800;
            c[0].choice_info.x = (colonne * 100);
            c[0].choice_info.y = (ligne * 100);

            c[1].choice_info.h = 800;
            c[1].choice_info.w = 100;
            c[1].choice_info.x = (colonne * 100);
            c[1].choice_info.y = (ligne * 100);

            c[2].choice_info.h = 100;
            c[2].choice_info.w = -800;
            c[2].choice_info.x = (colonne * 100);
            c[2].choice_info.y = (ligne * 100);

            c[3].choice_info.h = -800;
            c[3].choice_info.w = 100;
            c[3].choice_info.x = (colonne * 100);
            c[3].choice_info.y = (ligne * 100); 
}



void deplacement_cavalier(int plateau[][8],Choice* c,int ligne,int colonne){
    printf("Deplacement de la piece : cavalier\n");
            c[0].choice_info.h = 100;
            c[0].choice_info.w = 100;
            c[0].choice_info.x = (colonne * 100) + 100;
            c[0].choice_info.y = (ligne * 100) + 200 ;

            c[1].choice_info.h = 100;
            c[1].choice_info.w = 100;
            c[1].choice_info.x = (colonne * 100) - 100;
            c[1].choice_info.y = (ligne * 100) + 200 ;   

            c[2].choice_info.h = 100;
            c[2].choice_info.w = 100;
            c[2].choice_info.x = (colonne * 100) + 200;
            c[2].choice_info.y = (ligne * 100) + 100 ;

            c[3].choice_info.h = 100;
            c[3].choice_info.w = 100;
            c[3].choice_info.x = (colonne * 100) - 200;
            c[3].choice_info.y = (ligne * 100) + 100 ;  

            c[4].choice_info.h = 100;
            c[4].choice_info.w = 100;
            c[4].choice_info.x = (colonne * 100) + 100;
            c[4].choice_info.y = (ligne * 100) - 200 ;

            c[5].choice_info.h = 100;
            c[5].choice_info.w = 100;
            c[5].choice_info.x = (colonne * 100) - 100;
            c[5].choice_info.y = (ligne * 100) - 200 ; 

            c[6].choice_info.h = 100;
            c[6].choice_info.w = 100;
            c[6].choice_info.x = (colonne * 100) + 200;
            c[6].choice_info.y = (ligne * 100) - 100 ;

            c[7].choice_info.h = 100;
            c[7].choice_info.w = 100;
            c[7].choice_info.x = (colonne * 100) - 200;
            c[7].choice_info.y = (ligne * 100) - 100 ; 
}



void deplacement_fou(int plateau[][8],Choice* c,int ligne,int colonne){
    printf("Deplacement de la piece : fou\n");
        int ind = 0;
        for (int i = 0; i < 8; i++)
        {
            c[i].choice_info.h = 100;
            c[i].choice_info.w = 100;
            c[i].choice_info.x = (colonne * 100) + ( i*100);
            c[i].choice_info.y = (ligne * 100) + (i*100 );
        }
       for (int i = 8; i < 16; i++)
        {
            c[i].choice_info.h = 100;
            c[i].choice_info.w = 100;
            c[i].choice_info.x = (colonne * 100) -( ind*100);
            c[i].choice_info.y = (ligne * 100) - (ind*100 );
            ind++;
        }
        ind =0;
        for (int i = 16; i < 24; i++)
        {
            c[i].choice_info.h = 100;
            c[i].choice_info.w = 100;
            c[i].choice_info.x = (colonne * 100) +( ind*100);
            c[i].choice_info.y = (ligne * 100) - (ind*100 );
            ind++;
        }
        ind =0;
        for (int i = 24; i < 32; i++)
        {
            c[i].choice_info.h = 100;
            c[i].choice_info.w = 100;
            c[i].choice_info.x = (colonne * 100) -( ind*100);
            c[i].choice_info.y = (ligne * 100) + (ind*100 );
            ind++;
        }
}



void deplacement_roi(int plateau[][8],Choice* c,int ligne,int colonne){
    printf("Deplacement de la piece : roi\n");
           
        c[0].choice_info.h = 100;
        c[0].choice_info.w = 200;
        c[0].choice_info.x = (colonne * 100);
        c[0].choice_info.y = (ligne * 100) + 100 ;

        c[1].choice_info.h = 100;
        c[1].choice_info.w = 200;
        c[1].choice_info.x = (colonne * 100);
        c[1].choice_info.y = (ligne * 100) - 100 ; 


        c[2].choice_info.h = 200;
        c[2].choice_info.w = 100;
        c[2].choice_info.x = (colonne * 100) +100;
        c[2].choice_info.y = (ligne * 100); 
        
        c[3].choice_info.h = 200;
        c[3].choice_info.w = 100;
        c[3].choice_info.x = (colonne * 100) - 100;
        c[3].choice_info.y = (ligne * 100); 
}



void deplacement_reine(int plateau[][8],Choice* c,int ligne,int colonne){
    printf("Deplacement de la piece : reine\n");
    deplacement_fou(plateau,c,ligne,colonne);
            c[33].choice_info.h = 100;
            c[33].choice_info.w = 800;
            c[33].choice_info.x = (colonne * 100);
            c[33].choice_info.y = (ligne * 100);

            c[34].choice_info.h = 800;
            c[34].choice_info.w = 100;
            c[34].choice_info.x = (colonne * 100);
            c[34].choice_info.y = (ligne * 100);

            c[35].choice_info.h = 100;
            c[35].choice_info.w = -800;
            c[35].choice_info.x = (colonne * 100);
            c[35].choice_info.y = (ligne * 100);

            c[36].choice_info.h = -800;
            c[36].choice_info.w = 100;
            c[36].choice_info.x = (colonne * 100);
            c[36].choice_info.y = (ligne * 100);
}



int en_passant(){
    return 1;
    return -1;
}

int roque(){
    return 1;
    return -1;
}