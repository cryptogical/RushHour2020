#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <math.h>
#define SIZE_ARRAY(x)  (sizeof(x) / sizeof((x)[0]))
#define _GNU_SOURCE

void insert(char *name, int type, int posX, int posY, char dir) 
{
    vehicule *link = (vehicule*) malloc(sizeof(vehicule));
    link->name = name;
    link->type = type;
    link->x = posX;
    link->y = posY;
    link->dir = dir;
    link->next = head;
    head = link;
}

void couleur(char a)
{
    switch(a){
        case 'R':{
            printf("\033[1;31m");
            printf(" %c ", a);
            printf("\033[0m");
            break;
        }
        case 'G':{
            printf("\033[1;32m");
            printf(" %c ", a);
            printf("\033[0m");
            break;
        }
        case 'Y':{
            printf("\033[1;33m");
            printf(" %c ", a);
            printf("\033[0m");
            break;
        }
        case 'M':{
            printf("\033[1;35m");
            printf(" %c ", a);
            printf("\033[0m");
            break;
        }
        case 'B':{
            printf("\033[1;36m");
            printf(" %c ", a);
            printf("\033[0m");
            break;
        }
        case 'O':{
            printf("\033[1;34m");
            printf(" %c ", a);
            printf("\033[0m");
            break;
        }
        default:{
            printf(" %c ",a);
        }
    }
}

void grille()
{
    grid = (char*) malloc(36*sizeof(char));
	vehicule *ptr = head;
	char c = ' ';
	for(int i=0;i<36;i++) 
	{
		grid[i]=c;
	}
    while(ptr != NULL)
    {        
        grid[6*(ptr->x)+(ptr->y)]=*(ptr->name);
        switch(ptr->dir) 
        {
            case 'D': 
            {
                switch(ptr->type) 
        		{
            		case 2: 
            		{
                		grid[6*(ptr->x)+1+(ptr->y)]=*(ptr->name);
                		break;
            		}
            		case 3: 
            		{
                		for (int i = 1; i < 3; ++i)
                		{
                			grid[6*(ptr->x)+i+(ptr->y)]=*(ptr->name);
    					}
                		break;
            		}
        		}
                break;
            }
            case 'G': 
            {
                switch(ptr->type) 
        		{
            		case 2: 
            		{
                		grid[6*(ptr->x)-1+(ptr->y)]=*(ptr->name);
                		break;
            		}
            		case 3: 
            		{
                		for (int i = 1; i < 3; ++i)
                		{
                			grid[6*(ptr->x)-i+(ptr->y)]=*(ptr->name);
    					}
                		break;
            		}
        		}
                break;
            }
            case 'B': 
            {
                switch(ptr->type) 
        		{
            		case 2: 
            		{
                		grid[6*((ptr->x)+1)+(ptr->y)]=*(ptr->name);
                		break;
            		}
            		case 3: 
            		{
                		for (int i = 1; i < 3; ++i)
                		{
                			grid[6*((ptr->x)+i)+(ptr->y)]=*(ptr->name);
    					}
                		break;
            		}
        		}
                break;
            }
            case 'H': 
            {
                switch(ptr->type) 
        		{
            		case 2: 
            		{
                		grid[6*((ptr->x)-1)+(ptr->y)]=*(ptr->name);
                		break;
            		}
            		case 3: 
            		{
                		for (int i = 1; i < 3; ++i)
                		{
                			grid[6*((ptr->x)-i)+(ptr->y)]=*(ptr->name);
    					}
                		break;
            		}
        		}
                break;
            }
        }
		ptr = ptr->next;
    }
    printf("\033[4m                                    \033[0m \n");
    printf("\n");
    for (int i = 0; i < 6; ++i)
    {
    	printf("|");
        couleur(grid[0+i*6]);
        printf(" | ");
        couleur(grid[1+i*6]);
        printf(" | ");
        couleur(grid[2+i*6]);
        printf(" | ");
        couleur(grid[3+i*6]);
        printf(" | ");
        couleur(grid[4+i*6]);
        printf(" | ");
        if(i==2)
        {
            couleur(grid[5+i*6]);
            printf("\n");
            printf("\033[4m                                       \033[0m \n");
            printf("\n");    
        }
        else if (i==1)
        {
            couleur(grid[5+i*6]);
            printf(" | ");
            printf("\n");
            printf("\033[4m                                       \033[0m \n");
            printf("\n");          
        }
        else
        {
            couleur(grid[5+i*6]);
            printf(" | ");
            printf("\n");
            printf("\033[4m                                    \033[0m \n");
            printf("\n");
        }
    }
}

void ThrowAnException(char * args) {
    printf("Problème rencontré /!\\ Raison : %s ", args);
}

int deplace(char * name, char dir, int nbrDep) {
    while(nbrDep < 0 || nbrDep > 6){
        printf("%d n'est pas accepté car il n'est pas compris entre 0 et 6. Choisissez un nouveau nombre !\n",nbrDep);
        scanf("%d", &nbrDep);
    }
    int verifDeplacement = 0;
    vehicule *ptr = head;
    int distMax = 0;
    while (ptr != NULL){
        if(strcmp(ptr->name , name) == 0){
            if (ptr->dir == 'D'){
                distMax = 6 - (ptr->y + ptr->type);
                if(ptr->dir != dir)
                    distMax = 6 - (distMax + ptr->type);
                if(nbrDep > distMax){
                    ThrowAnException("Vous sortez de la grille !\n");
                   return 37;
                }
                if(dir == 'H' || dir == 'B'){
                    ThrowAnException("Le véhicule ne va pas dans cette direction !\n");
                    break;
                }

                if(ptr->dir != dir){
                    for (int i = 1 ; i<nbrDep+1 ; i++){
                        if(grid[ptr->y - i + 6*ptr->x] != ' '){
                            ThrowAnException("Déplacement impossible, un véhicule se trouve sur votre chemin !\n");
                            return ptr->y - i + 6*ptr->x;
                        }
                        else
                            verifDeplacement += 1;
                    }
                }
                else{
                    for (int i = 0 ; i<nbrDep ; i++){
                        if(grid[ptr->y + ptr->type + 6*ptr->x + i] != ' '){
                            ThrowAnException("Déplacement impossible, un véhicule se trouve sur votre chemin !\n");
                            return (ptr->y + ptr->type + 6*ptr->x + i);
                        }
                        else
                            verifDeplacement += 1;
                    }
                }

                if (verifDeplacement >= nbrDep){
                    if(ptr->dir != dir)
                        ptr->y -= nbrDep;
                    else
                        ptr->y += nbrDep;
                    return 0;
                }
                
            }

            if (ptr->dir == 'G'){
                distMax = ptr->y - ptr->type + 1;
                if(ptr->dir != dir)
                    distMax = 6 - (distMax + ptr->type);
                if(nbrDep > distMax){
                    ThrowAnException("Vous sortez de la grille !\n");
                    return 37;
                }
                if(dir == 'H' || dir == 'B'){
                    ThrowAnException("Le véhicule ne va pas dans cette direction !\n");
                    break;
                }
                if(ptr->dir != dir){
                    for (int i = 1 ; i<nbrDep+1 ; i++){
                        if(grid[ptr->y + i + 6*ptr->x] != ' '){
                            ThrowAnException("Déplacement impossible, un véhicule se trouve sur votre chemin !\n");
                            return ptr->y + i + 6*ptr->x;
                        }
                        else
                            verifDeplacement += 1;
                    }
                }
                else{
                    for (int i = 0 ; i<nbrDep ; i++){
                        if(grid[ptr->y + 6*ptr->x - ptr->type - i] != ' '){
                            ThrowAnException("Déplacement impossible, un véhicule se trouve sur votre chemin !\n");
                            return ptr->y + 6*ptr->x - ptr->type - i;
                        }
                        else
                            verifDeplacement += 1;
                    }
                }

                if (verifDeplacement >= nbrDep){
                    if(ptr->dir != dir)
                        ptr->y += nbrDep;
                    else
                        ptr->y -= nbrDep;
                    return 0;
                }
            }

            if (ptr->dir == 'H'){
                distMax = 1 + ptr->x - ptr->type;
                if(ptr->dir != dir)
                    distMax = 5 - ptr->x;
                if(nbrDep > distMax){
                    ThrowAnException("Vous sortez de la grille !\n");
                    return 37;
                }
                if(dir == 'G' || dir == 'D'){
                    ThrowAnException("Le véhicule ne va pas dans cette direction !\n");
                    break;
                }
                if(ptr->dir != dir){
                    for (int i = 1 ; i<nbrDep+1 ; i++){
                        if(grid[ptr->y + 6*(ptr->x + i)] != ' '){
                            ThrowAnException("Déplacement impossible, un véhicule se trouve sur votre chemin !\n");
                            return ptr->y + 6*(ptr->x + i);
                        }
                        else
                            verifDeplacement += 1;
                    }
                }
                else{
                    for (int i = 0 ; i<nbrDep ; i++){ //i=0 ; i<nbrDep ; i++
                        if(grid[ptr->y + 6*ptr->x - 6*(ptr->type + i)] != ' '){
                            ThrowAnException("Déplacement impossible, un véhicule se trouve sur votre chemin !\n");
                            return ptr->y + 6*ptr->x - 6*(ptr->type + i);
                        }
                        else
                            verifDeplacement += 1;
                    }
                }

                if (verifDeplacement >= nbrDep){
                    if(ptr->dir != dir)
                        ptr->x += nbrDep;
                    else
                        ptr->x -= nbrDep;
                    return 0;
                }

            }

            if (ptr->dir == 'B'){
                distMax = 6 - (ptr->x + ptr->type);
                if(ptr->dir != dir)
                    distMax = 6 - (distMax + ptr->type);
                if(nbrDep > distMax){
                    ThrowAnException("Vous sortez de la grille !\n");
                    return 37;
                }
                if(dir == 'G' || dir == 'D'){
                    ThrowAnException("Le véhicule ne va pas dans cette direction !\n");
                    break;
                }
                
                if(ptr->dir != dir){
                    for (int i = 1 ; i<nbrDep+1 ; i++){
                        if(grid[ptr->y + 6*(ptr->x - i)] != ' '){
                            ThrowAnException("Déplacement impossible, un véhicule se trouve sur votre chemin !\n");
                            return ptr->y + 6*(ptr->x - i);
                        }
                        else
                            verifDeplacement += 1;
                    }
                }
                else{
                    for (int i = 0 ; i<nbrDep ; i++){
                        if(grid[ptr->y + 6*(ptr->x + ptr->type + i)] != ' '){
                            ThrowAnException("Déplacement impossible, un véhicule se trouve sur votre chemin !\n");
                            return ptr->y + 6*(ptr->x + ptr->type + i);
                        }
                        else
                            verifDeplacement += 1;
                    }
                }

                if (verifDeplacement >= nbrDep){
                    if(ptr->dir != dir)
                        ptr->x -= nbrDep;
                    else
                        ptr->x += nbrDep;
                    return 0;
                }
            }
            break;
        }
        else 
            ptr = ptr->next;
    }
}

bool ended() {
    vehicule *ptr = head;
    while (ptr != NULL) {
        if(strcmp(ptr->name , "Red") == 0 && ptr->y == 4) {
            printf("Vous avez réussi jeune aventurier !\n");
            return true;
        }
        else {
            ptr = ptr->next;
        }
    }
    return false;
}

void dlconfig(int n)
{
    char fichier[] = "Carte X";
    fichier[6]=n + '0';
    FILE* config=fopen(fichier,"r");
    char ligne[200];
    int compteur=0;
    while(fgets(ligne,200,config) != NULL)
    {
        char *color = (char*) malloc(sizeof(char));
        char dire;
        int taille, abs, ord;
        sscanf(ligne, "%s%d%d%d", listecouleurs[compteur], &taille, &abs, &ord);
        dire=ligne[strlen(ligne)-2];
        insert(listecouleurs[compteur],taille,abs,ord,dire);
        compteur += 1;
    }
    fclose(config);
}

char* assimilateur(int c) {
    for (int i = 0; i < 16; ++i)
    {
        if (listecouleurs[i][0]==grid[c])
        {
            return listecouleurs[i];
        }
    }
}

int libcase(int a){
    vehicule* ptr = head;
    char* V = (char*) malloc(15*sizeof(char));
    int geneur;
    while (grid[a] != ' '){
        if (geneur != 0)    
            V = assimilateur(a);
        int d = 1;
        while (strcmp(ptr->name , V) != 0) { 
            ptr = ptr->next;
        }
        switch(ptr->dir){
            case 'B' :
            case 'H' : {
                    while(geneur == 0) {
                        geneur = deplace(V, 'B', 1);
                    }
                    if(geneur != 0 && geneur != 37) {
                        geneur = deplace(V, 'H', 1);
                        while(geneur == 0) {
                            geneur = deplace(V, 'H', 1);
                        }
                    }
                    if(geneur == 37) {
                        geneur = deplace(V, 'B', 1);
                        while(geneur == 0) {
                            geneur = deplace(V, 'B', 1);
                        }
                    }
                    grille();
                    V = assimilateur(geneur);
                break;  
            }
            case 'D' :
            case 'G' : {
                while(geneur == 0) {
                        geneur = deplace(V, 'G', 1);
                    }
                    if(geneur != 0 && geneur != 37) {
                        geneur = deplace(V, 'D', 1);
                        while(geneur == 0) {
                            geneur = deplace(V, 'D', 1);
                        }
                    }
                    if(geneur == 37) {
                        geneur = deplace(V, 'G', 1);
                        while(geneur == 0) {
                            geneur = deplace(V, 'G', 1);
                        }
                    }
                grille(); 
                break;
            }
            d += 1;
        }
        if (geneur != 37) {
            libcase(geneur);
        }
        else {
            geneur = deplace("Red" , 'D' , 1);
            while (geneur == 0){
                geneur = deplace("Red" , 'D' , 1);
            }
            if (!ended()){
                libcase(geneur);
            }
        }
    }
    return geneur;
}

void resolution2(){
    int geneur = 0; 
    char* Vgen=(char*) malloc(15*sizeof(char));
    while(!ended()) {      
        while(geneur == 0){
            geneur = deplace("Red" , 'D' , 1);
            grille();
            printf("%d\n", geneur);
        }
        if (geneur < 37){
            Vgen = assimilateur(geneur);
            printf("%s\n",Vgen);
            libcase(geneur);
        }
    }
    grille();
}

void resolution() {
    vehicule * ptr = head;
    int cpt = 0;
    while (ptr != NULL) {
        bool rndDist = rand() % 3 + 1;
        printf("%d", rndDist);
        deplace(ptr->name, ptr->dir, rndDist);
        cpt++;
        if(ended())
            break;
    }
    ptr = ptr->next;
    printf("Cpt : %d \n" , cpt);
}
