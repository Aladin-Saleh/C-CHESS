#include "../Headers/piece.h"
#include "../Headers/plateau.h"
#include "../Headers/deplacement.h"
#include <SDL2/SDL.h>   
#include <stdio.h>
#include <stdlib.h>
#include "../Headers/map.h"

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

void initialiser_fenetre(int plateau[][TAILLE_PLATEAU],int plateau_blc_and_wht[][TAILLE_PLATEAU]){




    int yCoordArray[8][8];
    int xCoordArray[8][8];



    struct Cases c;
    Map noir_blanc;
    create_map(&noir_blanc,3);

    add_to_map(&noir_blanc,0,"VIDE");
    add_to_map(&noir_blanc,1,"NOIR");
    add_to_map(&noir_blanc,2,"BLANC");
    
    Choice choice_piece[50];

    Map map_piece;
    init_piece_map(&map_piece);
    
    SDL_Rect selected;
    

    SDL_Window* pWindow = NULL; 
    SDL_Renderer* pRenderer = NULL; 
    SDL_Event sEvents;  

    SDL_version nb;
    SDL_VERSION(&nb);

    //void init_pion(Piece* piece[],int taille_array,int is_piece_noir,SDL_Renderer* pRenderer)



    int isOpen = 1;
    int isPieceSelected = 0;

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




    SDL_Rect src;
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
    int ligne = 0;
    int colonne = 0;
    int last_piece = 0;
    int indice_piece = 0;
    int is_piece_noir = 1;

    int l_buf = 0;
    int c_buf = 0;

    /*On créer des potentiel cases de selection en leur donnant une taille de 0 h et w*/
    for (int ind_slctd_set = 0; ind_slctd_set < 50; ind_slctd_set++)
    {
        choice_piece[ind_slctd_set].choice_info.h = 0;
        choice_piece[ind_slctd_set].choice_info.w = 0;
    }

    while (isOpen)//Cette boucle vas maintenir le programme en "vie".
    {

        while (SDL_PollEvent(&sEvents))
        { 
             switch (sEvents.type)
            {
                 case SDL_QUIT://Event lorsque l'on clique pour fermer le programme.
                    isOpen = 0;
                    printf("Screen closing ...\n");
                    break;
                 case SDL_MOUSEBUTTONDOWN: // Click de souris (Gestionnaire souris)
                    printf("Contain piece ? : %d\n",is_case_contain_piece(read_plateau(ligne,colonne,plateau)));
                    printf("%s\n",get_from_map(&map_piece,read_plateau(ligne,colonne,plateau)));
                    printf("%s\n",get_from_map(&noir_blanc,plateau_blc_and_wht[ligne][colonne]));
                    check(sEvents.motion.x,sEvents.motion.y,plateau,&colonne,&ligne);
                    show_choice_available(ligne,colonne,read_plateau(ligne,colonne,plateau),choice_piece,plateau_blc_and_wht[ligne][colonne],plateau);

/*Noir et blanc sont inversé, à fixer si j'ai le temps*/
                    if (isPieceSelected == 1 && sEvents.button.clicks == 2)
                    {
                        printf("Piece selected ! \n");
                        isPieceSelected = 0;

                            switch (last_piece)
                            {
                            case 0:
                                /* code */
                                break;
                            case 1:
                            if (is_piece_noir == 0)
                            {
                                pions_blanc[indice_piece].rect.y = (ligne*100)+10; 
                                pions_blanc[indice_piece].rect.x = (colonne*100)+10;
                                is_piece_noir = 1; 
                                plateau_blc_and_wht[l_buf][c_buf] = 0;
                                plateau_blc_and_wht[ligne][colonne] = 1;                                    
                                plateau[l_buf][c_buf] = 0;
                                plateau[ligne][colonne] = 1;
                            }
                            else if(is_piece_noir == 1){
                                pions_noir[indice_piece].rect.y = (ligne*100)+10;
                                pions_noir[indice_piece].rect.x = (colonne*100)+10;
                                is_piece_noir = 0;
                                plateau_blc_and_wht[l_buf][c_buf] = 0;
                                plateau_blc_and_wht[ligne][colonne] = 2;                                    
                                plateau[l_buf][c_buf] = 0;
                                plateau[ligne][colonne] = 1; 
                            }
                            afficher_plateau(plateau);
                            afficher_plateau(plateau_blc_and_wht);
                                break;
                            case 2:
                            if (is_piece_noir == 0)
                            {
                                tour_blanc[indice_piece].rect.y = (ligne*100)+10; 
                                tour_blanc[indice_piece].rect.x = (colonne*100)+10;
                                is_piece_noir = 1;
                                plateau_blc_and_wht[l_buf][c_buf] = 0;
                                plateau_blc_and_wht[ligne][colonne] = 1;                                    
                                plateau[l_buf][c_buf] = 0;
                                plateau[ligne][colonne] = TOUR;   

                            }else if(is_piece_noir == 1){
                                tour_noir[indice_piece].rect.y = (ligne*100)+10; 
                                tour_noir[indice_piece].rect.x = (colonne*100)+10;
                                is_piece_noir = 0;
                                plateau_blc_and_wht[l_buf][c_buf] = 0;
                                plateau_blc_and_wht[ligne][colonne] = 2;                                    
                                plateau[l_buf][c_buf] = 0;
                                plateau[ligne][colonne] = TOUR; 
                            }
                            afficher_plateau(plateau);
                            afficher_plateau(plateau_blc_and_wht);
                                break;
                            case 3:
                            if (is_piece_noir == 0)
                            {
                                cavalier_blanc[indice_piece].rect.y = (ligne*100)+10; 
                                cavalier_blanc[indice_piece].rect.x = (colonne*100)+10;
                                is_piece_noir = 1;
                                plateau_blc_and_wht[l_buf][c_buf] = 0;
                                plateau_blc_and_wht[ligne][colonne] = 1;                                    
                                plateau[l_buf][c_buf] = 0;
                                plateau[ligne][colonne] = CAVALIER; 

                            }else if(is_piece_noir == 1){
                                cavalier_noir[indice_piece].rect.y = (ligne*100)+10;
                                cavalier_noir[indice_piece].rect.x = (colonne*100)+10;
                                is_piece_noir = 0;
                                plateau_blc_and_wht[l_buf][c_buf] = 0;
                                plateau_blc_and_wht[ligne][colonne] = 2;                                    
                                plateau[l_buf][c_buf] = 0;
                                plateau[ligne][colonne] = CAVALIER; 
                            }
                            afficher_plateau(plateau);
                            afficher_plateau(plateau_blc_and_wht);
                                break;
                            case 4:
                            if (is_piece_noir == 0)
                            {
                                fou_blanc[indice_piece].rect.y = (ligne*100)+10; 
                                fou_blanc[indice_piece].rect.x = (colonne*100)+10;
                                is_piece_noir = 1;
                                plateau_blc_and_wht[l_buf][c_buf] = 0;
                                plateau_blc_and_wht[ligne][colonne] = 1;                                    
                                plateau[l_buf][c_buf] = 0;
                                plateau[ligne][colonne] = FOU; 

                            }else if(is_piece_noir == 1){
                                fou_noir[indice_piece].rect.y = (ligne*100)+10;
                                fou_noir[indice_piece].rect.x = (colonne*100)+10;
                                is_piece_noir = 0;
                                plateau_blc_and_wht[l_buf][c_buf] = 0;
                                plateau_blc_and_wht[ligne][colonne] = 2;                                    
                                plateau[l_buf][c_buf] = 0;
                                plateau[ligne][colonne] = FOU; 
                            }
                            afficher_plateau(plateau);
                            afficher_plateau(plateau_blc_and_wht);
                                break;
                            case 5:
                            if (is_piece_noir == 0)
                            {   
                                reine_blanc[indice_piece].rect.y = (ligne*100)+10; 
                                reine_blanc[indice_piece].rect.x = (colonne*100)+10;
                                is_piece_noir = 1;
                                plateau_blc_and_wht[l_buf][c_buf] = 0;
                                plateau_blc_and_wht[ligne][colonne] = 1;    
                                plateau[l_buf][c_buf] = 0;
                                plateau[ligne][colonne] = REINE; 

                            }else if(is_piece_noir == 1){
                                reine_noir[indice_piece].rect.y = (ligne*100)+10;
                                reine_noir[indice_piece].rect.x = (colonne*100)+10;                       
                                is_piece_noir = 0;
                                plateau_blc_and_wht[l_buf][c_buf] = 0;
                                plateau_blc_and_wht[ligne][colonne] = 2;    
                                plateau[l_buf][c_buf] = 0;
                                plateau[ligne][colonne] = REINE; 
                            }
                            afficher_plateau(plateau);
                            afficher_plateau(plateau_blc_and_wht);
                                break;
                            case 6:
                            if (is_piece_noir == 0)
                            {
                                roi_blanc[indice_piece].rect.y = (ligne*100)+10; 
                                roi_blanc[indice_piece].rect.x = (colonne*100)+10;
                                is_piece_noir = 1;
                                plateau_blc_and_wht[l_buf][c_buf] = 0;
                                plateau_blc_and_wht[ligne][colonne] = 1;                                
                                plateau[l_buf][c_buf] = 0;
                                plateau[ligne][colonne] = ROI; 

                            }else if(is_piece_noir == 1){
                                
                                roi_noir[indice_piece].rect.y = (ligne*100)+10;
                                roi_noir[indice_piece].rect.x = (colonne*100)+10;
                                is_piece_noir = 0;
                                plateau_blc_and_wht[l_buf][c_buf] = 0;
                                plateau_blc_and_wht[ligne][colonne] = 2;                                
                                plateau[l_buf][c_buf] = 0;
                                plateau[ligne][colonne] = ROI; 

                            }
                            afficher_plateau(plateau);
                            afficher_plateau(plateau_blc_and_wht);
                                break;                
                            }                       
                        
                    }
                    if (read_plateau(ligne,colonne,plateau) != 0)
                    {
                        last_piece = read_plateau(ligne,colonne,plateau);
                        indice_piece = get_piece_indice(read_plateau(ligne,colonne,plateau),colonne,ligne);
                        l_buf = ligne;
                        c_buf = colonne;
                    }
                    
                    printf("last_piece : %d\n",last_piece);
                    printf("indice_piece : %d\n",indice_piece);
                    select_pion(sEvents.motion.x,sEvents.motion.y,&selected,read_plateau(ligne,colonne,plateau),&isPieceSelected);
                    


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
    printf("X = %d\nY = %d\n",ligne,colonne);
    printf("Case contain : %d\n",read_plateau(ligne,colonne,plateau));

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
    int add_y = 100;
    int ind =0;

    //int add_x = 100;


    printf("LIGNE : %d\n",ligne);
    printf("COLONNE : %d\n",colonne);
    /*"Supprime" les cases selectionner (h et w = 0)*/
    for (int i = 0; i < 50; i++)
    {
            c[i].choice_info.h = 0;
            c[i].choice_info.w = 0;
    }
    
    switch (piece)
    {
    case 0://vide
        printf("%d :: \n",piece);  
        break;
    case 1://pion
        printf("%d :: \n",piece);
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
        printf("%d ::\n",piece);
        deplacement_fou(plateau,c,ligne,colonne);
        break;
    case 6://roi
        printf("%d ::\n",piece);
        deplacement_roi(plateau,c,ligne,colonne);
        break;
    case 5://reine
        printf("%d ::\n",piece);
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
        if ((pions_blanc[ind_p].rect.x == (colonne*100)+10) && (pions_blanc[ind_p].rect.y == (ligne*100)+10))
        {
            return ind_p;
        }

        if ((pions_noir[ind_p].rect.x == (colonne*100)+10) && (pions_noir[ind_p].rect.y == (ligne*100)+10))
        {
            return ind_p;
        }
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


