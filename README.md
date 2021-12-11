# C-CHESS

## Projet réalisés dans le cadre du cours de mise à niveau en informatique (I3ARIOC, Unilasalle Amiens)
### Jeux d'échecs réaliser via le langage C et la bibliothèque graphique SDL2

Ce projet est un jeux d'échecs classique.
Il comprend la totalité des règles à l'exception de l'echec et l'echec et mat.
Il comprend : 
* Le Roque (petit et grand roque).
* La prise en passant.
* La promotion (rencontre quelque bugs).
   
## Comment le projet marche ? 
Le code est compiler via GCC.  
Les fichiers sont construit via Make (source : https://fr.wikipedia.org/wiki/Make).  
Vous pouvez acceder à notre makefile ici : [Makefile](https://github.com/Aladin-Saleh/C-CHESS/blob/main/Source/Makefile).  
La bibliothèque graphique utilisé est SDL2 (source : https://www.libsdl.org/download-2.0.php).  

## Explication du code !

Notre programme fonctionne principalement en utilisant deux matrice (8x8).
* Une matrice de couleur des pieces.
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




