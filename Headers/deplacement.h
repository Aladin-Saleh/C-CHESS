#include "../Headers/screen.h"
#include <stdio.h>
#include <stdlib.h>

void deplacement_pion(int plateau[][8],Choice* c,int ligne,int colonne,int color);
void deplacement_tour(int plateau[][8],Choice* c,int ligne,int colonne);
void deplacement_cavalier(int plateau[][8],Choice* c,int ligne,int colonne);
void deplacement_fou(int plateau[][8],Choice* c,int ligne,int colonne);
void deplacement_roi(int plateau[][8],Choice* c,int ligne,int colonne);
void deplacement_reine(int plateau[][8],Choice* c,int ligne,int colonne);