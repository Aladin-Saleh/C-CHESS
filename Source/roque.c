#include "../Headers/piece.h"
#include "../Headers/screen.h"
    //Roi noir
    //int xNoir = roi_blanc[0].rect.y/100;
    //int yNoir = roi_blanc[0].rect.x/100;


int _roque_blanc(int plateau[][8],int plateau_color[][8]){


    //Roi blanc
    int xBlanc = roi_noir[0].rect.y/100;
    int yBlanc = roi_noir[0].rect.x/100;

    int id_tour;
        //droite
        if (plateau_color[xBlanc][yBlanc+1] == 0 && plateau_color[xBlanc][yBlanc+2] == 0)
        {
            printf("[xBlanc][yBlanc+1] : %d\n",plateau_color[xBlanc][yBlanc+1]);
            printf("[xBlanc][yBlanc-1] : %d\n",plateau_color[xBlanc][yBlanc+1]);
            if (plateau_color[xBlanc][yBlanc+3] == 2 && plateau[xBlanc][yBlanc+3] == 2)
            {
                printf("[xBlanc][yBlanc+1] : %d\n",plateau_color[xBlanc][yBlanc+3]);
                id_tour = get_piece_indice(2,xBlanc,yBlanc+3);//Recupere l'id de la tour avec qui on fait le roque
                printf("ID TOUR : %d\n",id_tour);
                tour_noir[id_tour].rect.x = ((yBlanc+1)*100)+10;
                tour_noir[id_tour].rect.y = (xBlanc*100)+10;

                plateau[xBlanc][yBlanc+3] = 0;
                plateau_color[xBlanc][yBlanc+3] = 0;
                plateau[xBlanc][yBlanc+1] = 2;
                plateau_color[xBlanc][yBlanc+1] = 2;
                printf("Roque possible blanc\n");
                return 1;
            }
            else{
                printf("Roque impossible blanc\n");
            }
         
        }


        if (plateau_color[xBlanc][yBlanc-1] == 0 && plateau_color[xBlanc][yBlanc-2] == 0 && plateau_color[xBlanc][yBlanc-3] == 0)
        {

            if (plateau_color[xBlanc][yBlanc+3] == 2 && plateau[xBlanc][yBlanc+3] == 2)
            {
                id_tour = get_piece_indice(2,xBlanc,0);//Recupere l'id de la tour avec qui on fait le roque
                tour_noir[0].rect.x = ((yBlanc-1)*100)+10;
                tour_noir[0].rect.y = (xBlanc*100)+10;
                plateau[xBlanc][yBlanc-4] = 0;
                plateau_color[xBlanc][yBlanc-4] = 0;
                plateau[xBlanc][yBlanc-1] = 2;
                plateau_color[xBlanc][yBlanc-1] = 2;
                printf("Roque possible blanc\n");
                return 1;
            }
            else{
                printf("Roque impossible blanc\n");
            }
         
        }

        return -1;

}




int _roque_noir(int plateau[][8],int plateau_color[][8]){


    //Roi noir
    int xNoir = roi_blanc[0].rect.y/100;
    int yNoir = roi_blanc[0].rect.x/100;

    int id_tour;
        //droite
        if (plateau_color[xNoir][yNoir+1] == 0 && plateau_color[xNoir][yNoir+2] == 0)
        {
            printf("[xBlanc][yNoir+1] : %d\n",plateau_color[xNoir][yNoir+1]);
            printf("[xBlanc][yNoir-1] : %d\n",plateau_color[xNoir][yNoir+1]);
            if (plateau_color[xNoir][yNoir+3] == 1 && plateau[xNoir][yNoir+3] == 2)
            {
                printf("[xBlanc][yNoir+1] : %d\n",plateau_color[xNoir][yNoir+3]);
                id_tour = get_piece_indice(2,xNoir,yNoir+3);//Recupere l'id de la tour avec qui on fait le roque
                printf("ID TOUR : %d\n",id_tour);
                tour_blanc[1].rect.x = ((yNoir+1)*100)+10;
                tour_blanc[1].rect.y = (xNoir*100)+10;

                plateau[xNoir][yNoir+3] = 0;
                plateau_color[xNoir][yNoir+3] = 0;
                plateau[xNoir][yNoir+1] = 2;
                plateau_color[xNoir][yNoir+1] = 1;
                printf("Roque possible blanc\n");
                return 1;
            }
            else{
                printf("Roque impossible blanc\n");
            }
         
        }


        if (plateau_color[xNoir][yNoir-1] == 0 && plateau_color[xNoir][yNoir-2] == 0 && plateau_color[xNoir][yNoir-3] == 0)
        {

            if (plateau_color[xNoir][yNoir+3] == 1 && plateau[xNoir][yNoir+3] == 2)
            {
                id_tour = get_piece_indice(2,xNoir,0);//Recupere l'id de la tour avec qui on fait le roque
                tour_blanc[0].rect.x = ((yNoir-1)*100)+10;
                tour_blanc[0].rect.y = (xNoir*100)+10;
                plateau[xNoir][yNoir-4] = 0;
                plateau_color[xNoir][yNoir-4] = 0;
                plateau[xNoir][yNoir-1] = 2;
                plateau_color[xNoir][yNoir-1] = 1;
                printf("Roque possible blanc\n");
                return 1;
            }
            else{
                printf("Roque impossible blanc\n");
            }
         
        }

        return -1;

}