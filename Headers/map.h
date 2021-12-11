typedef struct Map Map;
struct Map
{
    int* key;
    char** value;
    int last_ind;
    int taille;
};

void create_map(Map *m,int taille);
void add_to_map(Map *m,int key,char* value);
char* get_from_map(Map *m,int key);
void init_piece_map(Map* map);