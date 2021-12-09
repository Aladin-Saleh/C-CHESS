#include "../Headers/piece.h"
#include "../Headers/plateau.h"
#include "../Headers/deplacement.h"
#include "../Headers/promotion.h"
#include <SDL2/SDL.h>   
#include <stdio.h>
#include <stdlib.h>
#include "../Headers/map.h"
#include "../Headers/manger.h"
#include "../Headers/mat.h"

#define BLANC 255
#define NOIR 0

//$(sdl2-config --cflags --libs)
struct Cases
{
    SDL_Rect cases_de_jeu;
    int ligne;
    int colonne;
    int x1,x2;
    int y1,y2;
};



void initialier_plateau(int xBuf[][8],int yBuf[][8],int bool);
void check(int click_x,int click_y,int plateau[][8],int* colonne,int* ligne);
int read_plateau(int ligne,int colonne,int plateau[][8]);
void select_pion(int click_x,int click_y,SDL_Rect* r,int cases_value,int* is_piece_selected);
void show_choice_available(int ligne,int colonne,int piece,Choice* c,int color,int plateau[][8]);
int get_piece_indice(int value,int colonne, int ligne);
int move_piece(int value,int colonne, int ligne,int piece_selected,int color,int prev_l,int prev_c,int plateau_blc_and_wht[][8],int plateau[][8]);
void eat(int color_array[][8],int piece_array[][8],int ligne,int colonne);
int get_indice_pion(int xCoord,int yCoord);

void initialiser_fenetre(int plateau[][TAILLE_PLATEAU],int plateau_blc_and_wht[][TAILLE_PLATEAU]){

    int yCoordArray[8][8];//buffer
    int xCoordArray[8][8];
    int isOpen = 1;//boucle de jeu
    int isPieceSelected = 0;
    int ligne = 0;
    int colonne = 0;
    int last_piece = 0;
    int indice_piece = 0;
    int piece_color = 2;
    int piece_selected = -1;
    //2 blanc
    //1 noir
    int who_play = 2;
    int l_buf = 0;//Position à n-1
    int c_buf = 0;//Position à n-1



    struct Cases c;
    Choice choice_piece[50];

    Map noir_blanc;
    Map map_piece;

    create_map(&noir_blanc,3);
    add_to_map(&noir_blanc,0,"VIDE");
    add_to_map(&noir_blanc,1,"NOIR");
    add_to_map(&noir_blanc,2,"BLANC");
    

    init_piece_map(&map_piece);
    
    SDL_Rect selected;
    SDL_Rect src;
    SDL_Window* pWindow = NULL; 
    SDL_Renderer* pRenderer = NULL; 
    SDL_Event sEvents;  
    SDL_version nb;
    SDL_VERSION(&nb);

    //void init_pion(Piece* piece[],int taille_array,int is_piece_noir,SDL_Renderer* pRenderer)





    if(SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "[debug] %s", SDL_GetError());//Gestionnaire d'erreur SDL
        exit(-1);
    }
    printf("Starting screen...\nVersion : %d.%d.%d\n",nb.major,nb.minor,nb.patch);
    
 
    
    //Creation de la fenetre.
    pWindow = SDL_CreateWindow("Chess", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);       
    if (pWindow == NULL)//return null en cas d'echec.  
    {         
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "[DEBUG] > %s", SDL_GetError()); //Gestionnaire d'erreur SDL        
        SDL_Quit();         
        exit(EXIT_FAILURE); 
    }       

    //Creation du rendu de la fenetre.
    //SDL_Renderer* SDL_CreateRenderer(SDL_Window* window, int index, Uint32 flags)
    //La fenetre en premier paramètre.
    //L'index du pilote (-1 permet de laisser SDL choisir le meilleur pilote).
    //Flags : 
    //SDL_RENDERER_SOFTWARE : utilise l'accélération logiciel pour faire les calculs de rendu depuis le CPU
    //SDL_RENDERER_ACCELERATED : utilise l'accélération matériel pour faire les calculs de rendu depuis la GPU
    //SDL_RENDERER_PRESENTVSYNC : synchronise l'affichage en fonction du taux de rafraîchissement de votre écran
    //SDL_RENDER_TARGETTEXTURE : autorise-le rendu sur une SDL_Texture (on verra plus en profondeur cette notion dans un chapitre dédié aux textures)
    pRenderer = SDL_CreateRenderer(pWindow,-1,SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
     if (pRenderer == NULL)//return null en cas d'echec.
        {
            SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "[DEBUG] > %s", SDL_GetError()); //Gestionnaire d'erreur SDL        
            SDL_Quit();         
            exit(EXIT_FAILURE); 
        }


    /*
    SDL_Texture* SDL_CreateTexture(
                               SDL_Renderer* renderer, //rendu de fenêtre.
                               Uint32        format,
                               int           access, //l'accès à la texture.
                               int           w, //largeur
                               int           h //hauteur
                               )
    La fonction retourne un pointeur sur une SDL_Texture et NULL si ça n'a pas pu crée la texture.
    */
    init_pion(pions_noir,8,1,pRenderer);
    init_pion(pions_blanc,8,0,pRenderer);

    init_tour(tour_noir,2,1,pRenderer);
    init_tour(tour_blanc,2,0,pRenderer);

    init_fou(fou_noir,2,1,pRenderer);
    init_fou(fou_blanc,2,0,pRenderer);    


    init_cavalier(cavalier_noir,2,1,pRenderer);
    init_cavalier(cavalier_blanc,2,0,pRenderer);

    
    init_roi(roi_noir,1,1,pRenderer);
    init_roi(roi_blanc,1,0,pRenderer);

    
    init_reine(reine_noir,1,1,pRenderer);    
    init_reine(reine_blanc,1,0,pRenderer);    




    //{0, 0, 0, 0};
    src.h=0;
    src.w=0;
    src.x=0;
    src.y=0;

    for (int ndice = 0; ndice < 8; ndice++)
    {
        SDL_QueryTexture(pions_noir[ndice].texture_piece, NULL,NULL, &src.w, &src.h);
        SDL_QueryTexture(pions_blanc[ndice].texture_piece, NULL,NULL, &src.w, &src.h);

    }
    
    for (int ind_tour = 0; ind_tour < 2; ind_tour++)
    {
        SDL_QueryTexture(tour_noir[ind_tour].texture_piece, NULL,NULL, &src.w, &src.h);
        SDL_QueryTexture(tour_blanc[ind_tour].texture_piece, NULL,NULL, &src.w, &src.h);


        SDL_QueryTexture(cavalier_noir[ind_tour].texture_piece, NULL,NULL, &src.w, &src.h);
        SDL_QueryTexture(cavalier_blanc[ind_tour].texture_piece, NULL,NULL, &src.w, &src.h);

        
        SDL_QueryTexture(fou_noir[ind_tour].texture_piece, NULL,NULL, &src.w, &src.h);
        SDL_QueryTexture(fou_blanc[ind_tour].texture_piece, NULL,NULL, &src.w, &src.h);

    }
    
        SDL_QueryTexture(roi_noir[0].texture_piece, NULL,NULL, &src.w, &src.h);
        SDL_QueryTexture(roi_blanc[0].texture_piece, NULL,NULL, &src.w, &src.h);


        SDL_QueryTexture(reine_noir[0].texture_piece, NULL,NULL, &src.w, &src.h);
        SDL_QueryTexture(reine_blanc[0].texture_piece, NULL,NULL, &src.w, &src.h);



    initialier_plateau(xCoordArray,yCoordArray,0);

    /*On créer des potentiel cases de selection en leur donnant une taille de 0 h et w*/
    for (int ind_slctd_set = 0; ind_slctd_set < 50; ind_slctd_set++)
    {
        choice_piece[ind_slctd_set].choice_info.h = 0;
        choice_piece[ind_slctd_set].choice_info.w = 0;
    }

    int *p;
    while (isOpen)//Cette boucle vas maintenir le programme en "vie".
    {

        while (SDL_PollEvent(&sEvents))
        { 
            printf("%d\n",check_white_pions());
             switch (sEvents.type)
            {
                 case SDL_QUIT://Event lorsque l'on clique pour fermer le programme.
                    isOpen = 0;
                    printf("Screen closing ...\n");
                    break;
                 case SDL_MOUSEBUTTONDOWN: // Click de souris (Gestionnaire souris)
                   

                   
                   /*
                        Test changment de piece (promotion)
                    pions_blanc[2].surface_piece = SDL_LoadBMP("../Img/Tour.bmp");
                    pions_blanc[2].texture_piece = SDL_CreateTextureFromSurface(pRenderer,pions_blanc[2].surface_piece);
                    SDL_FreeSurface(pions_blanc[2].surface_piece);
                    */

                    //*p = get_king_position(plateau,plateau_blc_and_wht,2);
                    //printf("ligne : %d\ncolonne : %d\n",*(p+0),*(p+1));
                    check(sEvents.motion.x,sEvents.motion.y,plateau,&colonne,&ligne);
                    //printf("Clique sur X : %d Y: %d\n",colonne,ligne);
                    //printf("%s\n",get_from_map(&noir_blanc,read_plateau(ligne,colonne,plateau_blc_and_wht)));
                    //printf("%s\n",get_from_map(&map_piece,read_plateau(ligne,colonne,plateau)));
                    show_choice_available(ligne,colonne,read_plateau(ligne,colonne,plateau),choice_piece,plateau_blc_and_wht[ligne][colonne],plateau);
                    select_pion(sEvents.motion.x,sEvents.motion.y,&selected,read_plateau(ligne,colonne,plateau),&isPieceSelected);//yellow case

                    if ((read_plateau(ligne,colonne,plateau) != 0) && (read_plateau(ligne,colonne,plateau_blc_and_wht) == piece_color))
                    {
                        for (int i_p = 0; i_p < 8; i_p++)
                        {
                            printf("%d\nXCORD : %d\nYCORD : %d\n---------------\n",i_p,pions_noir[i_p].rect.x,pions_noir[i_p].rect.y);
                        }
                        
                        
                        //printf("Indice de piece : %d\n",get_piece_indice(read_plateau(ligne,colonne,plateau),colonne,ligne));
                        printf("Clique sur X : %d Y: %d\n",(colonne*100)+10,(ligne*100)+10);
                        printf("INDICE DE LA PIECE : %d\n",get_indice_pion((colonne*100)+10,(ligne*100)+10));
                        indice_piece = read_plateau(ligne,colonne,plateau);
                        l_buf = ligne;
                        c_buf = colonne;
                        
                        piece_selected = get_piece_indice(read_plateau(ligne,colonne,plateau),colonne,ligne);
                        //printf("Piece selected = %d\n",piece_selected);
                    }
                    
                    //printf("Case contain a %s",get_from_map(&map_piece,read_plateau(ligne,colonne,plateau)));
                    /*Noir et blanc sont inversé, à fixer si j'ai le temps*/
                    if (piece_color == 2 && sEvents.button.clicks == 2 && piece_selected != -1 && is_movable(plateau_blc_and_wht,plateau[l_buf][c_buf],plateau[ligne][colonne],plateau_blc_and_wht[l_buf][c_buf],plateau_blc_and_wht[ligne][colonne],l_buf,c_buf,ligne,colonne) != -1)//On bouge les blancs
                    {
                        //printf("Au tour des blancs \n");           
                        //printf("Indice piece : %d\n",piece_selected);      
                        move_piece(indice_piece,colonne,ligne,piece_selected,piece_color,l_buf,c_buf,plateau_blc_and_wht,plateau); 
                        piece_color = 1;
                        piece_selected = -1;
                        indice_piece = 0;
                    }
                    else if(piece_color == 1 && sEvents.button.clicks == 2 && piece_selected != -1 && is_movable(plateau_blc_and_wht,plateau[l_buf][c_buf],plateau[ligne][colonne],plateau_blc_and_wht[l_buf][c_buf],plateau_blc_and_wht[ligne][colonne],l_buf,c_buf,ligne,colonne) != -1){//On bouge les noirs
                        //printf("Au tour des noirs \n");   
                        move_piece(indice_piece,colonne,ligne,piece_selected,piece_color,l_buf,c_buf,plateau_blc_and_wht,plateau); 
                        piece_color = 2;
                        indice_piece = 0;
                        piece_selected = -1;
                    }
                    afficher_plateau(plateau);
                    afficher_plateau(plateau_blc_and_wht);
                    //printf("Indice piece apres deplacement : %d \n",indice_piece);
                    break;
            }  
        }


        //printf("%s\n",get_from_map(&map_piece,read_plateau(ligne,colonne,plateau)));

        SDL_SetRenderDrawColor(pRenderer, 55, 0, 100, 255);//Rendu,Red,Green,Blue,Alpha(transparence);
        SDL_RenderClear(pRenderer);//On nettoie le contenue de la fenetre
        //SDL_RenderPresent(pRenderer);//Update de la fenetre

        for (int i = 0; i < 8; i++)
        {   
            for (int j = 0; j < 8; j++)
            {
                c.cases_de_jeu.h = 100;
                c.cases_de_jeu.w = 100;
                c.cases_de_jeu.y = yCoordArray[i][j];
                c.cases_de_jeu.x = xCoordArray[i][j];
                c.ligne = i;
                c.colonne = j;
                
                if ((i+j)%2 == 0)
                {
                    SDL_SetRenderDrawColor(pRenderer, BLANC,BLANC,BLANC, 255);
                }
                else{
                    SDL_SetRenderDrawColor(pRenderer, 255,0,0, 255);
                }
                SDL_RenderFillRect(pRenderer,&c.cases_de_jeu);
            }
        
        }
       //Case de selection
        SDL_SetRenderDrawColor(pRenderer, 255,255,0, 0);
        SDL_RenderFillRect(pRenderer,&selected);

        SDL_SetRenderDrawColor(pRenderer,0,255,255,255);
        for (int ind_slctd = 0; ind_slctd < 50; ind_slctd++)
        {
            SDL_RenderFillRect(pRenderer,&choice_piece[ind_slctd].choice_info);
            SDL_RenderFillRect(pRenderer,&choice_piece[ind_slctd].choice_info);
        }
        
        //SDL_RenderCopy(pRenderer, pTexture, &src, &dst); // Affiche ma texture sur touts l'écran
        //SDL_RenderCopy(pRenderer, pTexture_noir, &src, &dst_noir); // Affiche ma texture sur touts l'écran
        for (int indCopy = 0; indCopy < 8; indCopy++)
        {
            SDL_RenderCopy(pRenderer, pions_noir[indCopy].texture_piece, &src,&pions_noir[indCopy].rect);
            SDL_RenderCopy(pRenderer, pions_blanc[indCopy].texture_piece, &src,&pions_blanc[indCopy].rect);

        }

        for (int ind_tourv1 = 0; ind_tourv1 < 2; ind_tourv1++)
        {
            SDL_RenderCopy(pRenderer, tour_noir[ind_tourv1].texture_piece, &src,&tour_noir[ind_tourv1].rect);
            SDL_RenderCopy(pRenderer, tour_blanc[ind_tourv1].texture_piece, &src,&tour_blanc[ind_tourv1].rect);


            SDL_RenderCopy(pRenderer, cavalier_noir[ind_tourv1].texture_piece, &src,&cavalier_noir[ind_tourv1].rect);
            SDL_RenderCopy(pRenderer, cavalier_blanc[ind_tourv1].texture_piece, &src,&cavalier_blanc[ind_tourv1].rect);


            SDL_RenderCopy(pRenderer, fou_noir[ind_tourv1].texture_piece, &src,&fou_noir[ind_tourv1].rect);
            SDL_RenderCopy(pRenderer, fou_blanc[ind_tourv1].texture_piece, &src,&fou_blanc[ind_tourv1].rect);

   

        }
                   
            SDL_RenderCopy(pRenderer, roi_noir[0].texture_piece, &src,&roi_noir[0].rect);
            SDL_RenderCopy(pRenderer, roi_blanc[0].texture_piece, &src,&roi_blanc[0].rect);


            SDL_RenderCopy(pRenderer, reine_noir[0].texture_piece, &src,&reine_noir[0].rect);  
            SDL_RenderCopy(pRenderer, reine_blanc[0].texture_piece, &src,&reine_blanc[0].rect);



        SDL_RenderPresent(pRenderer);



    }
    //Liberation de la memoire.

    SDL_DestroyWindow(pWindow);//Destruction de la fenetre.  
    SDL_DestroyRenderer(pRenderer); //Destruction du rendu 
    SDL_Quit();     

    


}

/**
 * @xCoordArray[][8] (int) container pour les coordonnées en x;
 * @yCoordArray[][8] (int) container pour les coordonnées en y;
 * @bool_show_coord (int) agit comme un boolean, afficher ou pas les coordonnées dans la console;
 * Cette fonction vas remplir les tableaux x et y des coordonnées des cases du plateau
*/
void initialier_plateau(int xCoordArray[][8],int yCoordArray[][8],int bool_show_coord){

    int xBuf = 0;
    int yBuf = 0;
    int ind = 0;

    for (int i = 0; i < 8; i++)
    {   
        for (int j = 0; j < 8; j++)
        {
            yCoordArray[i][j] = yBuf;
            xCoordArray[i][j] = xBuf; 
            if (bool_show_coord)
            {
                printf("-----------------------------\nX = %d \nY = %d \nLigne = %d\nColonne = %d\nTest indice = %d \n-----------------------------\n",xCoordArray[i][j],yCoordArray[i][j],i,j,ind);
            }
            xBuf+=100;
        ind++;
        }
        xBuf = 0;   
        yBuf += 100;
        
    }
}

void check(int click_x,int click_y,int plateau[][8],int* _colonne,int* _ligne){
    
    *_colonne = click_x/100;
    *_ligne = click_y/100;

    int colonne = click_x/100;
    int ligne = click_y/100;
}


int read_plateau(int ligne,int colonne, int plateau[][8]){
    return plateau[ligne][colonne];
}   

void select_pion(int click_x,int click_y,SDL_Rect* r,int cases_value,int* is_piece_selected){
    int coord_x = (click_x/100) *100 ; 
    int coord_y = (click_y/100) *100 ;
    if (cases_value != 0)
    {
        *is_piece_selected = 1;
        r->h = 100;
        r->w = 100;
        r->x = coord_x ;
        r->y = coord_y ;
    }
    

}

void show_choice_available(int ligne,int colonne,int piece,Choice* c,int color,int plateau[][8]){
    /*"Supprime" les cases selectionner (h et w = 0)*/
    for (int i = 0; i < 50; i++)
    {
            c[i].choice_info.h = 0;
            c[i].choice_info.w = 0;
    }
    
    switch (piece)
    {
    case 0://vide
        break;
    case 1://pion
        if (color == 1)
        {
            deplacement_pion(plateau,c,ligne,colonne,1);
        }
        else if (color == 2)
        {
            deplacement_pion(plateau,c,ligne,colonne,-1);
        }
        break;
    case 2://tour
        deplacement_tour(plateau,c,ligne,colonne);     
        break;
    case 3://cavalier
        deplacement_cavalier(plateau,c,ligne,colonne);       
        break;
    case 4://fou
        deplacement_fou(plateau,c,ligne,colonne);
        break;
    case 6://roi
        deplacement_roi(plateau,c,ligne,colonne);
        break;
    case 5://reine
        deplacement_reine(plateau,c,ligne,colonne);
        break;
    }

}

int get_piece_indice(int value,int colonne, int ligne){

    switch (value)
    {
    case 0:
        return 0;
        break;
    case 1:
    for (int ind_p = 0; ind_p < 8; ind_p++)
    {

        return get_indice_pion((colonne*100)+10,(ligne*100)+10);
    }
        break;
    case 2:
    for (int ind_p = 0; ind_p < 2; ind_p++)
    {
        if ((tour_blanc[ind_p].rect.x == (colonne*100)+10) && (tour_blanc[ind_p].rect.y == (ligne*100)+10))
        {
            return ind_p;
        }

        if ((tour_noir[ind_p].rect.x == (colonne*100)+10) && (tour_noir[ind_p].rect.y == (ligne*100)+10))
        {
            return ind_p;
        }        
        
    }

        break;
    case 3:
    for (int ind_p = 0; ind_p < 2; ind_p++)
    {
        if ((cavalier_blanc[ind_p].rect.x == (colonne*100)+10) && (cavalier_blanc[ind_p].rect.y == (ligne*100)+10))
        {
            return ind_p;
        }

        if ((cavalier_noir[ind_p].rect.x == (colonne*100)+10) && (cavalier_noir[ind_p].rect.y == (ligne*100)+10))
        {
            return ind_p;
        }        
        
    }
        break;
    case 4:
    for (int ind_p = 0; ind_p < 2; ind_p++)
    {
        if ((fou_blanc[ind_p].rect.x == (colonne*100)+10) && (fou_blanc[ind_p].rect.y == (ligne*100)+10))
        {
            return ind_p;
        }

        if ((fou_noir[ind_p].rect.x == (colonne*100)+10) && (fou_noir[ind_p].rect.y == (ligne*100)+10))
        {
            return ind_p;
        }        
        
    }
        break;
    case 5:
    for (int ind_p = 0; ind_p < 1; ind_p++)
    {
        if ((reine_blanc[ind_p].rect.x == (colonne*100)+10) && (reine_blanc[ind_p].rect.y == (ligne*100)+10))
        {
            return ind_p;
        }

        if ((reine_noir[ind_p].rect.x == (colonne*100)+10) && (reine_noir[ind_p].rect.y == (ligne*100)+10))
        {
            return ind_p;
        }        
        
    }
        break;
    case 6:
    for (int ind_p = 0; ind_p < 1; ind_p++)
    {
        if ((roi_blanc[ind_p].rect.x == (colonne*100)+10) && (roi_blanc[ind_p].rect.y == (ligne*100)+10))
        {
            return ind_p;
        }

        if ((roi_noir[ind_p].rect.x == (colonne*100)+10) && (roi_noir[ind_p].rect.y == (ligne*100)+10))
        {
            return ind_p;
        }        
        
    }
        break;                
    }
}

int move_piece(int value,int colonne, int ligne,int piece_selected,int color,int prev_l,int prev_c,int plateau_blc_and_wht[][8],int plateau[][8]){
//blc = 2;
//noir = 1;
    switch (value)
    {
    case 0:
        return 0;
        break;
    case PION:
        if (color == 2)//blanc
        {
            eat(plateau_blc_and_wht,plateau,ligne,colonne);
            pions_noir[piece_selected].rect.x = (colonne*100)+10;
            pions_noir[piece_selected].rect.y = (ligne*100)+10;
            plateau_blc_and_wht[prev_l][prev_c] = 0;
            plateau_blc_and_wht[ligne][colonne] = 2;                                    
            plateau[prev_l][prev_c] = 0;
            plateau[ligne][colonne] = PION;
        }
        else
        {
            eat(plateau_blc_and_wht,plateau,ligne,colonne);
            pions_blanc[piece_selected].rect.x = (colonne*100)+10;
            pions_blanc[piece_selected].rect.y = (ligne*100)+10;
            plateau_blc_and_wht[prev_l][prev_c] = 0;
            plateau_blc_and_wht[ligne][colonne] = 1;                                    
            plateau[prev_l][prev_c] = 0;
            plateau[ligne][colonne] = PION;
        }
        
        
        break;
        
    case TOUR:
        if (color == 2)//blanc
        {
            eat(plateau_blc_and_wht,plateau,ligne,colonne);
            tour_noir[piece_selected].rect.x = (colonne*100)+10;
            tour_noir[piece_selected].rect.y = (ligne*100)+10;
            plateau_blc_and_wht[prev_l][prev_c] = 0;
            plateau_blc_and_wht[ligne][colonne] = 2;                                    
            plateau[prev_l][prev_c] = 0;
            plateau[ligne][colonne] = TOUR;
        }
        else
        {
            eat(plateau_blc_and_wht,plateau,ligne,colonne);
            tour_blanc[piece_selected].rect.x = (colonne*100)+10;
            tour_blanc[piece_selected].rect.y = (ligne*100)+10;
            plateau_blc_and_wht[prev_l][prev_c] = 0;
            plateau_blc_and_wht[ligne][colonne] = 1;                                    
            plateau[prev_l][prev_c] = 0;
            plateau[ligne][colonne] = TOUR;

        }
        
        
        break;
        
    case CAVALIER:
        if (color == 2)//blanc
        {
            eat(plateau_blc_and_wht,plateau,ligne,colonne);
            cavalier_noir[piece_selected].rect.x = (colonne*100)+10;
            cavalier_noir[piece_selected].rect.y = (ligne*100)+10;
            plateau_blc_and_wht[prev_l][prev_c] = 0;
            plateau_blc_and_wht[ligne][colonne] = 2;                                    
            plateau[prev_l][prev_c] = 0;
            plateau[ligne][colonne] = CAVALIER;
        }
        else
        {
            eat(plateau_blc_and_wht,plateau,ligne,colonne);
            cavalier_blanc[piece_selected].rect.x = (colonne*100)+10;
            cavalier_blanc[piece_selected].rect.y = (ligne*100)+10;
            plateau_blc_and_wht[prev_l][prev_c] = 0;
            plateau_blc_and_wht[ligne][colonne] = 1;                                    
            plateau[prev_l][prev_c] = 0;
            plateau[ligne][colonne] = CAVALIER;
        }
        
        
        break;
        
    case FOU:
        if (color == 2)//blanc
        {
            eat(plateau_blc_and_wht,plateau,ligne,colonne);
            fou_noir[piece_selected].rect.x = (colonne*100)+10;
            fou_noir[piece_selected].rect.y = (ligne*100)+10;
            plateau_blc_and_wht[prev_l][prev_c] = 0;
            plateau_blc_and_wht[ligne][colonne] = 2;                                    
            plateau[prev_l][prev_c] = 0;
            plateau[ligne][colonne] = FOU;
        }
        else
        {
            eat(plateau_blc_and_wht,plateau,ligne,colonne);
            fou_blanc[piece_selected].rect.x = (colonne*100)+10;
            fou_blanc[piece_selected].rect.y = (ligne*100)+10;
            plateau_blc_and_wht[prev_l][prev_c] = 0;
            plateau_blc_and_wht[ligne][colonne] = 1;                                    
            plateau[prev_l][prev_c] = 0;
            plateau[ligne][colonne] = FOU;
        }
        
        
        break;
    case REINE:
        if (color == 2)//blanc
        {
            eat(plateau_blc_and_wht,plateau,ligne,colonne);
            reine_noir[piece_selected].rect.x = (colonne*100)+10;
            reine_noir[piece_selected].rect.y = (ligne*100)+10;
            plateau_blc_and_wht[prev_l][prev_c] = 0;
            plateau_blc_and_wht[ligne][colonne] = 2;                                    
            plateau[prev_l][prev_c] = 0;
            plateau[ligne][colonne] = REINE;
        }
        else
        {
            eat(plateau_blc_and_wht,plateau,ligne,colonne);            
            reine_blanc[piece_selected].rect.x = (colonne*100)+10;
            reine_blanc[piece_selected].rect.y = (ligne*100)+10;
            plateau_blc_and_wht[prev_l][prev_c] = 0;
            plateau_blc_and_wht[ligne][colonne] = 1;                                    
            plateau[prev_l][prev_c] = 0;
            plateau[ligne][colonne] = REINE;
        }
        
        
        break;
    case ROI:
        if (color == 2)//blanc
        {
            eat(plateau_blc_and_wht,plateau,ligne,colonne);            
            roi_noir[piece_selected].rect.x = (colonne*100)+10;
            roi_noir[piece_selected].rect.y = (ligne*100)+10;
            plateau_blc_and_wht[prev_l][prev_c] = 0;
            plateau_blc_and_wht[ligne][colonne] = 2;                                    
            plateau[prev_l][prev_c] = 0;
            plateau[ligne][colonne] = ROI;
        }
        else
        {
            eat(plateau_blc_and_wht,plateau,ligne,colonne);            
            roi_blanc[piece_selected].rect.x = (colonne*100)+10;
            roi_blanc[piece_selected].rect.y = (ligne*100)+10;
            plateau_blc_and_wht[prev_l][prev_c] = 0;
            plateau_blc_and_wht[ligne][colonne] = 1;                                    
            plateau[prev_l][prev_c] = 0;
            plateau[ligne][colonne] = ROI;
        }
        
        break;                
    }
}



/**
 * @brief 
 * Fonction qui lit le tableau et retourne la piece contenu dans la case du tableau.
 * 
 */
void eat(int color_array[][8],int piece_array[][8],int ligne,int colonne){
    
    int buf_ind = 0;
    if (piece_array[ligne][colonne] != 0)
    {
       printf("Une piece a été manger ! \n"); 
       buf_ind = get_piece_indice(piece_array[ligne][colonne],colonne,ligne);
       manger_piece(piece_array[ligne][colonne],buf_ind,color_array[ligne][colonne]);
    }
    else{
       printf("Rien à manger :( \n");
    }
}

/**
 * @brief Get the indice pion   
 * Fonction à part pour les pions qui sont gérer differement lorsque que plusieurs pions sont sur la meme ligne/colonne
 * @param xCoord 
 * @param yCoord 
 * @return int indice du pions
 */
int get_indice_pion(int xCoord,int yCoord){
    printf("xCoord : %d\n yCoord : %d\n",xCoord,yCoord);
    int last_ind_found = -1;
    for (int i = 0; i < 8; i++)
    {
        if (pions_blanc[i].rect.x == xCoord && pions_blanc[i].rect.y == yCoord)
        {
            printf("Find ind in %d\n",i);
            last_ind_found = i;
            //return i;
        }

        if (pions_noir[i].rect.x == xCoord && pions_noir[i].rect.y == yCoord)
        {
            printf("Find ind in %d\n",i);
            last_ind_found = i;
            //return i;
        }
        
    }
    return last_ind_found;
}