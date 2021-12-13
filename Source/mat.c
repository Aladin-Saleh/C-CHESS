#include "../Headers/piece.h"


int is_king_echec(int plateau[][8],int plateau_color[][8],SDL_Renderer *pRenderer){
    //1er etape verifier que le roi et entouré et qu'il n'y pas de cavalier autour de lui
    //Si roi pas entouré de piece à lui, verifier les diagonale,les horizontale,les verticales




    //Récuperation de la position du rois
    //Roi noir

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
    int horizontal_g = -1;
    int vertical = -1;
    int vertical_bas = -1;

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
        for (int i = 1; i < 8-(yBlanc); i++)
        {
            //Diagonale droite
            if (plateau_color[(xBlanc)-i][(yBlanc)+i] == 1 
            && echec_fou_dd == -1  
            && (plateau[(xBlanc)-i][(yBlanc)+i] == 4 || plateau[(xBlanc)-i][(yBlanc)+i] == 5 ))
            {
                echec_fou_dd = 1;
            }
            else if(plateau_color[xBlanc-i][yBlanc+i] == 2 && echec_fou_dd == -1 ){//Si on trouve une piece allié sur le chemin on arrete de verifier
                echec_fou_dd = 0;
            }   
        }

        for (int l = 1; l < yBlanc+1; l++)
        {
            //Diagonale gauche
            if (plateau_color[(xBlanc)-l][(yBlanc)-l] == 1 
            && echec_fou_dg == -1 
            && (plateau[(xBlanc)-l][(yBlanc)-l] == 4 || plateau[(xBlanc)-l][(yBlanc)-l] == 5 ) )
            {
                echec_fou_dg = 1;
            }
            else if(plateau_color[xBlanc-l][yBlanc-l] == 2 && echec_fou_dg == -1 ){
                echec_fou_dg = 0;
            } 
        }
        


        for (int j = 1; j < 8-xBlanc; j++)
        {
            printf("Fou dd :%d\n",plateau_color[xBlanc+j][yBlanc+j]);
            //Diagonale droite bas
            if (plateau_color[(xBlanc)+j][(yBlanc)+j] == 1 && echec_fou_dd_bas == -1 )
            {
                printf("Piece trouvé\n");
                echec_fou_dd_bas = 1;
            }
            else if(plateau_color[xBlanc+j][yBlanc+j] == 2 && echec_fou_dd_bas == -1){
                echec_fou_dd_bas = 0;
            }   

            //Diagonale gauche bas
            if (plateau_color[(xBlanc)+j][(yBlanc)-j] == 1 && echec_fou_dg_bas == -1 )
            {
                echec_fou_dg_bas = 1;
            }
            else if(plateau_color[xBlanc+j][yBlanc-j] == 2 && echec_fou_dd_bas == -1){
                echec_fou_dg_bas = 0;
            } 
        }

        
        //int horizontal = -1;
        //int vertical = -1;
        for (int k = 1; k < 8; k++)
        {
            if (plateau_color[(xBlanc)-k][(yBlanc)] == 1 
            && (plateau[(xBlanc)-k][(yBlanc)] == 2 || plateau[(xBlanc)-k][(yBlanc)] == 5 )
            && vertical == -1)
            {
                vertical = 1;
            }
            else if(plateau_color[(xBlanc)-k][(yBlanc)] == 2 && vertical == -1){
                vertical = 0;
            }
            
        }

        for (int m = 1; m < 8-xBlanc; m++)
        {
            printf("Vertical :%d\n",plateau_color[xBlanc+m][yBlanc]);
            if (plateau_color[(xBlanc)+m][(yBlanc)] == 1 
            && (plateau[(xBlanc)+m][(yBlanc)] == 2 || plateau[(xBlanc)+m][(yBlanc)] == 5 )
            && vertical_bas == -1)
            {
                vertical_bas = 1;
            }
            else if(plateau_color[(xBlanc)+m][(yBlanc)] == 2 && vertical_bas == -1){
                vertical_bas = 0;
            }
        }

        //Axe horizontal
        for (int h = 1; h < 8-yBlanc; h++)
        {
            if (plateau_color[(xBlanc)][(yBlanc)+h] == 1 
            && (plateau[(xBlanc)][(yBlanc)+h] == 2 || plateau[(xBlanc)][(yBlanc)+h] == 5 )
            && horizontal == -1)
            {
                horizontal = 1;
            }
            else if(plateau_color[(xBlanc)][(yBlanc)+h] == 2 && horizontal == -1){
                horizontal = 0;
            }

            if (plateau_color[(xBlanc)][(yBlanc)-h] == 1 
            && (plateau[(xBlanc)][(yBlanc)-h] == 2 || plateau[(xBlanc)][(yBlanc)-h] == 5 )
            && horizontal_g == -1)
            {
                horizontal_g = 1;
            }
            else if(plateau_color[(xBlanc)][(yBlanc)-h] == 2 && horizontal_g == -1){
                horizontal_g = 0;
            }
        }
        
        for (int f = 1; f < 8-((8-yBlanc))+1; f++)
        {   

            printf("%d HORIZONTAL : %d\n",8-((8-yBlanc)),plateau_color[(xBlanc)][(yBlanc)-f]);
            if (plateau_color[(xBlanc)][(yBlanc)-f] == 1 
            && (plateau[(xBlanc)][(yBlanc)-f] == 2 || plateau[(xBlanc)][(yBlanc)-f] == 5 )
            && horizontal_g == -1)
            {
                horizontal_g = 1;
            }
            else if(plateau_color[(xBlanc)][(yBlanc)-f] == 2 && horizontal_g == -1){
                horizontal_g = 0;
            }
        }
        
        
        printf("VERTICAl FINAL : %d\n",vertical);
            



        if (echec_fou_dd == 1 
        || echec_fou_dg == 1 
        || echec_fou_dg_bas == 1 
        || echec_fou_dd_bas == 1 
        || vertical == 1 
        || vertical_bas == 1 
        || horizontal == 1
        || horizontal_g == 1)
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




int is_king_echec_noir(int plateau[][8],int plateau_color[][8],SDL_Renderer *pRenderer){

    int xNoir = roi_blanc[0].rect.y/100;
    int yNoir = roi_blanc[0].rect.x/100;
    
    //Diagonale
    int echec_fou_dd = -1;
    int echec_fou_dg = -1;
    int echec_fou_dd_bas = -1;
    int echec_fou_dg_bas = -1;

    //Axe horizontaux et verticaux
    int horizontal = -1;
    int horizontal_g = -1;
    int vertical = -1;
    int vertical_bas = -1;

    for (int i = 1; i < 8-(xNoir); i++)
    {
        //Diagonale droite
        if (plateau_color[(xNoir)-i][(yNoir)+i] == 2 
        && echec_fou_dd == -1  
        && (plateau[(xNoir)-i][(yNoir)+i] == 4 || plateau[(xNoir)-i][(yNoir)+i] == 5 ))
        {
            echec_fou_dd = 1;
        }
        else if(plateau_color[xNoir-i][yNoir+i] == 1 && echec_fou_dd == -1 ){//Si on trouve une piece allié sur le chemin on arrete de verifier
            echec_fou_dd = 0;
        }   
    }

    for (int l = 1; l < yNoir+1; l++)
    {
        //Diagonale gauche
        if (plateau_color[(xNoir)-l][(yNoir)-l] == 2 
        && echec_fou_dg == -1 
        && (plateau[(xNoir)-l][(yNoir)-l] == 4 || plateau[(xNoir)-l][(yNoir)-l] == 5 ) )
        {
            echec_fou_dg = 1;
        }
        else if(plateau_color[xNoir-l][yNoir-l] == 1 && echec_fou_dg == -1 ){
            echec_fou_dg = 0;
        } 
    }


    for (int j = 1; j < 8-yNoir; j++)
    {
        printf("XNOIR : %d\n",xNoir);
        //Diagonale droite bas
        if (plateau_color[(xNoir)+j][(yNoir)+j] == 2 
        && echec_fou_dd_bas == -1 )
        {
            printf("Piece trouvé\n");
            echec_fou_dd_bas = 1;
        }
        else if(plateau_color[xNoir+j][yNoir+j] == 1 && echec_fou_dd_bas == -1){
            echec_fou_dd_bas = 0;
        }   
        

    }    

    for (int y = 1; y < (8-yNoir)+1; y++)
    {
        printf("Fou dg :%d\n",plateau_color[xNoir+y][yNoir-y]);
        printf("echec_fou_dg_bas :%d\n",echec_fou_dg_bas);
        //Diagonale gauche bas
        if (plateau_color[(xNoir)+y][(yNoir)-y] == 2 
        && echec_fou_dg_bas == -1
        && (plateau[(xNoir)+y][(yNoir)-y] == 4 || plateau[(xNoir)+y][(yNoir)-y] == 5 ) )
        {
            echec_fou_dg_bas = 1;
        }
        else if(plateau_color[xNoir+y][yNoir-y] == 1 && echec_fou_dg_bas == -1){
            echec_fou_dg_bas = 0;
        } 
    }

    //Axe horizontal
    for (int h = 1; h < 8-yNoir; h++)
    {
        if (plateau_color[(xNoir)][(yNoir)+h] == 2
        && (plateau[(xNoir)][(yNoir)+h] == 2 || plateau[(xNoir)][(yNoir)+h] == 5 )
        && horizontal == -1)
        {
            horizontal = 1;
        }
        else if(plateau_color[(xNoir)][(yNoir)+h] == 1 && horizontal == -1){
            horizontal = 0;
        }

        if (plateau_color[(xNoir)][(yNoir)-h] == 2
        && (plateau[(xNoir)][(yNoir)-h] == 2 || plateau[(xNoir)][(yNoir)-h] == 5 )
        && horizontal_g == -1)
        {
            horizontal_g = 1;
        }
        else if(plateau_color[(xNoir)][(yNoir)-h] == 1 && horizontal_g == -1){
            horizontal_g = 0;
        }
    }
        
    for (int f = 1; f < 8-((8-yNoir))+1; f++)
    {   
        printf("%d HORIZONTAL : %d\n",8-((8-yNoir)),plateau_color[(xNoir)][(yNoir)-f]);
        if (plateau_color[(xNoir)][(yNoir)-f] == 2
        && (plateau[(xNoir)][(yNoir)-f] == 2 || plateau[(xNoir)][(yNoir)-f] == 5 )
        && horizontal_g == -1)
        {
            horizontal_g = 1;
        }
        else if(plateau_color[(xNoir)][(yNoir)-f] == 1 && horizontal_g == -1){
            horizontal_g = 0;
        }
    }


    //Axe vertical 
    for (int k = 1; k < 8; k++)
    {
        if (plateau_color[(xNoir)-k][(yNoir)] == 2 
        && (plateau[(xNoir)-k][(yNoir)] == 2 || plateau[(xNoir)-k][(yNoir)] == 5 )
        && vertical == -1)
        {
            vertical = 1;
        }
        else if(plateau_color[(xNoir)-k][(yNoir)] == 1 && vertical == -1){
            vertical = 0;
        }
        
    }

    for (int m = 1; m < 8-xNoir; m++)
    {
        printf("Vertical :%d\n",plateau_color[xNoir+m][yNoir]);
        if (plateau_color[(xNoir)+m][(yNoir)] == 2 
        && (plateau[(xNoir)+m][(yNoir)] == 2 || plateau[(xNoir)+m][(yNoir)] == 5 )
        && vertical_bas == -1)
        {
            vertical_bas = 1;
        }
        else if(plateau_color[(xNoir)+m][(yNoir)] == 1 && vertical_bas == -1){
            vertical_bas = 0;
        }
    }


    

    
    if (echec_fou_dd == 1 
    || echec_fou_dg == 1 
    || echec_fou_dg_bas == 1 
    || echec_fou_dd_bas == 1 
    || vertical == 1 
    || vertical_bas == 1 
    || horizontal == 1
    || horizontal_g == 1)
    {
        roi_blanc[0].surface_piece = SDL_LoadBMP("../Img/Roi__echec.bmp");
        roi_blanc[0].texture_piece = SDL_CreateTextureFromSurface(pRenderer,roi_blanc[0].surface_piece);
        SDL_FreeSurface(roi_blanc[0].surface_piece);
        
        printf("ECHEC\n");
    }
    else{
        roi_blanc[0].surface_piece = SDL_LoadBMP("../Img/Roi_noir.bmp");
        roi_blanc[0].texture_piece = SDL_CreateTextureFromSurface(pRenderer,roi_blanc[0].surface_piece);
        SDL_FreeSurface(roi_blanc[0].surface_piece);

        printf("PAS ECHEC\n");
    }
}