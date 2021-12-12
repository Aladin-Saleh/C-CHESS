# C-CHESS

## Projet réalisés dans le cadre du cours de mise à niveau en informatique (I3ARIOC, Unilasalle Amiens)
### Jeux d'échecs réaliser via le langage C et la bibliothèque graphique SDL2

Ce projet est un jeux d'échecs classique.
Il comprend la totalité des règles à l'exception de l'echec et mat.
Il comprend : 
* L'echec (partiellement).
* Le Roque (petit et grand roque).
* La prise en passant.
* La promotion (rencontre quelque bugs).
   
## Comment le projet marche ? 
Le code est compiler via GCC.  
Les fichiers sont construit via Make (source : https://fr.wikipedia.org/wiki/Make).  
Vous pouvez acceder à notre makefile ici : [Makefile](https://github.com/Aladin-Saleh/C-CHESS/blob/main/Source/Makefile).  
La bibliothèque graphique utilisé est SDL2 (source : https://www.libsdl.org/download-2.0.php).  

## Explication du code !

### Plateau de jeu et pieces
Notre programme fonctionne principalement en utilisant deux matrice (8x8).
* Une matrice de couleur des pieces.  Les 1 representent les noirs et 2 les blancs.  
* Une matrice de piece avec leurs valeurs.

Dans le code, elles sont initialisé dans le main :
[main.c](https://github.com/Aladin-Saleh/C-CHESS/blob/main/Source/main.c).  
```C
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
```
On créer d'abord les matrices (les plateaux) en vide.  
Puis on y place les pieces.  
Voila ce qu'on obtient dans la console :  
![image](https://user-images.githubusercontent.com/67257097/145692827-f41d152a-5426-420e-94a1-a7fee1caa2e3.png)


### Affichage graphique

L'affichage graphique est gerer via SDL2.
L'initialisation ce fait grace à ces structures et fonction : 
[screen.c](https://github.com/Aladin-Saleh/C-CHESS/blob/main/Source/screen.c).  
```C
    SDL_Window* pWindow = NULL; 
    SDL_Renderer* pRenderer = NULL; 
    SDL_Event sEvents;  
    

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

```

Pour rester en "vie", le programme utilise une boucle permettant de maintenir le programme en vie.  
Cela permet aussi au programme de ce mettre à jour et effectuer des actions données toutes le 1 ms.  
```C
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
                 ......
             }
        }
        
      }
```

#### Creation du plateau graphique et initialisation des pieces.

Voici comment le plateau est créer : 

```C

        for (int i = 0; i < 8; i++)
        {   
            for (int j = 0; j < 8; j++)
            {
                c.cases_de_jeu.h = 100;
                c.cases_de_jeu.w = 100;
                c.cases_de_jeu.y = yCoordArray[i][j];//Ce sont des buffers de valeurs
                c.cases_de_jeu.x = xCoordArray[i][j];
                c.ligne = i;
                c.colonne = j;
                
                if ((i+j)%2 == 0)
                {
                    SDL_SetRenderDrawColor(pRenderer, BLANC,BLANC,BLANC, 255);//Rendu de la couleur
                }
                else{
                    SDL_SetRenderDrawColor(pRenderer, 100,21,0, 255);
                }
                SDL_RenderFillRect(pRenderer,&c.cases_de_jeu);//Creation du carré avec le rendu définie juste avant.
            }
        
        }
```
La valeur de la somme de i+j vas alterner en 0 et 1.  
Lorsque la somme vaut 0 on ajoute une case blanches sinon, on y ajoute un case marron.
Une case est une structure contenant les informations suivantes : 
```C
struct Cases
{
    SDL_Rect cases_de_jeu;//Case (rendu)
    int ligne;
    int colonne;
    int x1,x2;//Coordonnées x
    int y1,y2;//Coordonnées y
};

```
 #### Les pieces

Les pieces sont des images au format BMP. (Il est possible d'utiliser d'autres formats, mais cela nécessite d'inclure une autre bibliothèque de SDL)
[Les images](https://github.com/Aladin-Saleh/C-CHESS/tree/main/Img).  
Une piece est aussi une structure créer tel que : 
```C
struct Piece
{
    int val_piece;//Valeur de la piece
    int piece_blanche;
    SDL_Surface* surface_piece;//La surface de l'image (structure sdl)
    SDL_Texture* texture_piece;//La texure
    SDL_Rect rect;//La zone d'affichage
};

```

On retrouve 32 pieces initialisés via cette structures de la manieres suivantes.

```C
Piece pions_blanc[8];
Piece pions_noir[8];

Piece tour_blanc[2];
Piece tour_noir[2];

Piece cavalier_blanc[2];
Piece cavalier_noir[2];

Piece fou_blanc[2];
Piece fou_noir[2];

Piece roi_blanc[1];
Piece roi_noir[1];

Piece reine_blanc[1];
Piece reine_noir[1];

```

De plus chaque piece a une valeur constante tel que :  
```C
#define PION 1
#define TOUR 2
#define CAVALIER 3
#define FOU 4
#define ROI 6
#define REINE 5
#define NOMBRE_PIECE 6
```

Chaque piece possède une fonction d'initialisation : 
```C
void init_pion(Piece piece[],int taille_array,int is_piece_blanche,SDL_Renderer* pRenderer);
void init_tour(Piece piece[],int taille_array,int is_piece_blanche,SDL_Renderer* pRenderer);
void init_cavalier(Piece piece[],int taille_array,int is_piece_blanche,SDL_Renderer* pRenderer);
void init_fou(Piece piece[],int taille_array,int is_piece_blanche,SDL_Renderer* pRenderer);
void init_roi(Piece piece[],int taille_array,int is_piece_blanche,SDL_Renderer* pRenderer);
void init_reine(Piece piece[],int taille_array,int is_piece_blanche,SDL_Renderer* pRenderer);
void initialiser_piece(int plateau[][8]);

```

Exemple avec l'initialisation de la tour : 
```C
void init_tour(Piece piece[],int taille_array,int is_piece_blanche,SDL_Renderer* pRenderer){

    int x[2] = {10,710};
        
        if (is_piece_blanche)
        {
            for (int  i = 0; i < taille_array; i++)
            {
                piece[i].surface_piece = SDL_LoadBMP("../Img/Tour.bmp");
                piece[i].piece_blanche = is_piece_blanche;
                piece[i].rect.w = 90;
                piece[i].rect.h = 90;
                piece[i].rect.y = 710;
                piece[i].rect.x = x[i];
                piece[i].texture_piece = SDL_CreateTextureFromSurface(pRenderer,piece[i].surface_piece);
                SDL_FreeSurface(piece[i].surface_piece);

            }
        }else
        {
            
            for (int  i = 0; i < taille_array; i++)
            {
                piece[i].surface_piece = SDL_LoadBMP("../Img/Tour_noir.bmp");
                piece[i].piece_blanche = is_piece_blanche;
                piece[i].rect.w = 90;
                piece[i].rect.h = 90;
                piece[i].rect.y = 10;
                piece[i].rect.x = x[i];
                piece[i].texture_piece = SDL_CreateTextureFromSurface(pRenderer,piece[i].surface_piece);
                SDL_FreeSurface(piece[i].surface_piece);

            }
        }
        
        

}

```
Chaque piece est placée via leur coordonnée x,y et par rapport à leur position dans la matrice (leur indice de matrice)
Exemple : La tour noir en haut à gauche est en X = 0 Y = 0 et dans la matrice ces indices sont : ```ma_matrice[0][0]```

Une fois l'initialisation du plateau et des pieces faites voici ce que l'on obtient : 
![image](https://user-images.githubusercontent.com/67257097/145693399-7bf43d32-873f-496d-b87c-f862d959b6ac.png)


### Deplacement et coup spéciaux.


### Echec
Tout le long de la partie, le programme verifie que les rois ne sont pas en echec.  
Pour cela, le programme verifie d'abord si le roi est entouré par des pieces alliés.
```C
    //check roi blanc 2
    if (plateau_color[xBlanc-1][yBlanc] != 2||
        plateau_color[xBlanc-1][yBlanc-1] != 2 ||
        plateau_color[xBlanc-1][yBlanc+1] != 2 ||
        plateau_color[xBlanc][yBlanc+1] != 2 ||
        plateau_color[xBlanc][yBlanc-1] != 2 )
````
Si c'est le cas, il n'est pas nécessaire de verifier sauf pour le cavalier.  
Sinon, le programme joue tout les coups possible sur le roi et verifie si ils ne sont pas jouable.  
Exemple : 
Verification des diagonale.  
```C
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
````
Lorsque le roi est en echec, la piece devient rouge.  
Chaque coup possible a une valeur initialisé à -1
```C
    int echec_fou_dd = -1;
    int echec_fou_dg = -1;

    int echec_fou_dd_bas = -1;
    int echec_fou_dg_bas = -1;

    int horizontal = -1;
    int vertical = -1;
````
Si une de ces valeurs est mise à 1, cela signifie que le roi est en echec.
```C

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
````
Le code complet : [mat.c](https://github.com/Aladin-Saleh/C-CHESS/blob/main/Source/mat.c).  
![image](https://user-images.githubusercontent.com/67257097/145717195-50e588a2-8005-421a-8b78-42611edf6638.png)

### Roque
Les regles : https://fr.wikipedia.org/wiki/Roque_(%C3%A9checs) .  
Le code : [roque.c](https://github.com/Aladin-Saleh/C-CHESS/blob/main/Source/roque.c).  

Le roque est un déplacement spécial du roi et d'une des tours au jeu d'échecs.  
Le roque permet, en un seul coup, de mettre le roi à l'abri tout en centralisant une tour, ce qui permet par la même occasion de mobiliser rapidement cette dernière.  
Il s'agit du seul coup légal permettant de déplacer deux pièces, sans respecter le déplacement classique du roi et de la tour de surcroît.  

Le programme verifie les cotes adjacent du roi pour pouvoir determiner si le roque est jouable.
Cela comprend le petit et grand roque.
https://user-images.githubusercontent.com/67257097/145717564-b1923f20-6a91-49a9-b63d-01c7ccb6ff1f.mp4


### Prise en passant

Les regles : https://fr.wikipedia.org/wiki/En_passant_(%C3%A9checs)
Le code : [manger.c](https://github.com/Aladin-Saleh/C-CHESS/blob/main/Source/manger.c).  

Le coup n'est jouable que sur la ligne 3 pour les blancs et ligne 4 pour les noirs (les lignes sont compris de 0 a 7).
Prise en passant pour les blancs
```C
        //diagonale droite en passant
        if (c+1 == nc && l-1 == nl && plateau_blc_wht[nl][nc] == 0 && plateau_blc_wht[nl+1][nc] == 1 && l == 3)
        {
            
            manger_piece(1,nc,1);//La regle en passant ne s'applique qu'au pion
            return 1;
        }

        //diagonale gauche en passant 
        if (c-1 == nc && l-1 == nl && plateau_blc_wht[nl][nc] == 0 && plateau_blc_wht[nl+1][nc] == 1 && l == 3)
        {
            manger_piece(1,nc,1);
            return 1;
        }
```




