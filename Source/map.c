#include "../Headers/plateau.h"
#include "../Headers/piece.h"
#include "../Headers/screen.h"
#include "../Headers/map.h"
#include <stdio.h>
#include <stdlib.h>

/**
* Fausse implementation d'une hashmap.
*/


void create_map(Map *m,int taille){
    m->key = NULL;
    m->value = NULL;
    m->last_ind = 0;
    m->taille = taille;
    m->key = malloc((taille*NOMBRE_PIECE) * sizeof(int));
    m->value = malloc((taille*NOMBRE_PIECE) * sizeof(char**));
    
    if ( m->value == NULL)
    {
        perror("Erreur lors de l'allocation...\n");
        exit(0);
    }
    
}

void add_to_map(Map *m,int key,char* value){
    m->key[m->last_ind] = key;
    m->value[m->last_ind] = value;
    printf("Clé %d ajouter pour la valeur %s \n",key,value);
    
    m->last_ind++;
}


char* get_from_map(Map *m,int key){
    for (int i = 0; i < m->taille; i++)
    {
        if (m->key[i] == key)
        {
            return m->value[i];
        }
        
    }

    return NULL;
    
}





void init_piece_map(Map* map){
    create_map(map,NOMBRE_PIECE+1);
    add_to_map(map,0,"Vide");
    add_to_map(map,PION,"Pion");
    add_to_map(map,TOUR,"Tour");
    add_to_map(map,CAVALIER,"Cavalier");
    add_to_map(map,FOU,"Fou");
    add_to_map(map,REINE,"Reine");
    add_to_map(map,ROI,"Roi");
}
