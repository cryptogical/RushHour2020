// Bibliothèque des fonctions utilisées pour le jeu

//utilitaire
void ThrowAnException(char * args);
int char_to_int(char d);

typedef struct vehicule {
    char *name;
    int type;
    int x;
    int y;
    char dir;
    struct vehicule *next;
} vehicule;

//gestion des vehicules

void insert(char *name, int type, int posX, int posY, char dir);
void deplace(char * name, char dir, int nbrDep);
char* assimilateur(int c);
int libcase(int a);


//graphiques
void couleur(char a);
void grille();

void ThrowAnException(char * args);
bool ended();
void dlconfig(int n);
void resolution();
void resolution2();
