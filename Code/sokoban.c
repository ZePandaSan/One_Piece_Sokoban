#include <stdio.h>
#include <SDL.h>
#define TAILLE 12
#define TAILLE_MUR 34

void freeTab2D(char **tab, int taille){
	for (int i=0; i<taille;i++){
		free(tab[i]);
	}
	free(tab);
}

char **initTab(FILE *fd){
	char ** tab = malloc(12*sizeof(char*));
  	for(int i = 0; i<12; i++)
    tab[i] = malloc(12*sizeof(char));
  	char buffer[BUFSIZ];
  	int l = 0;
  	while(fgets(buffer, BUFSIZ, fd) != NULL){
    int k = 0;
    while(buffer[k] != '\n'){
      tab[l][k] = buffer[k];
      k++;
    }
    l++;
  }
  return tab;
}

int gagne(char **tab){
	int compteur = 0;
	for (int i = 0; i < 12; i++) {
		for (int j = 0; j < 12; j++) {
			if (tab[j][i] == 'I' || tab[j][i] == '@')
				compteur++;
		}
	}
	return (compteur == 0);
}

int * affiche(char **tab){
	int * pos = malloc(2*sizeof(int));
	SDL_Surface * ecran = NULL, * mur = NULL, * luffy=NULL, * caisse=NULL, * objectif=NULL, * fond=NULL, * tresor=NULL;
	SDL_Rect position, posluffy, poscaisse, posobjectif, posFond, postresor;
	position.x=0;
	position.y=0;
	posluffy.x=0;
	posluffy.y=0;
	poscaisse.x=0;
	poscaisse.y=0;
	posobjectif.x=0;
	posobjectif.y=0;
	postresor.x=0;
	postresor.y=0;
	if(SDL_Init(SDL_INIT_VIDEO)!=0){
		fprintf(stderr, "\nUnable to initialise SDL: %s\n",SDL_GetError());
		exit(EXIT_FAILURE);
	}
	SDL_WM_SetIcon(SDL_LoadBMP("icone.bmp"), NULL);
	if ((ecran = SDL_SetVideoMode(442,442,32,SDL_HWSURFACE))==NULL){
		fprintf(stderr, "Erreur VideoMode %s\n",SDL_GetError() );
		exit(EXIT_FAILURE);
	}
	SDL_WM_SetCaption("One Piece Sokoban", NULL);
  	mur = SDL_LoadBMP("mur.bmp");
  	luffy = SDL_LoadBMP("luffy.bmp");
  	caisse = SDL_LoadBMP("caisse.bmp");
  	objectif = SDL_LoadBMP("objectif.bmp");
  	fond = SDL_LoadBMP("fond.BMP");
  	tresor = SDL_LoadBMP("tresor.BMP");
	for (int i=0;i<12;i++){
		position.x=i*34;
		posluffy.x=i*34;
		poscaisse.x=i*34;
		posobjectif.x=i*34;
		posFond.x=i*34;
		postresor.x=i*34;
		for (int j=0;j<12;j++){
			position.y=j*34;
			posluffy.y=j*34;
			poscaisse.y=j*34;
			posobjectif.y=j*34;
			posFond.y=j*34;
			postresor.y=j*34;
			SDL_BlitSurface(fond, NULL, ecran, &posFond);
			SDL_Flip(ecran);
			if (tab[i][j]=='#'){
				SDL_BlitSurface(mur, NULL, ecran, &position);
				SDL_Flip(ecran);
			}
			else if (tab[i][j]=='P' || tab[i][j]=='@'){
				SDL_BlitSurface(luffy, NULL, ecran, &posluffy);
				SDL_Flip(ecran);
				pos[0] = i;
				pos[1] = j;
			}
			else if (tab[i][j]=='C'){
				SDL_BlitSurface(caisse, NULL, ecran, &poscaisse);
				SDL_Flip(ecran);
			}
			else if (tab[i][j]=='I'){
				SDL_BlitSurface(objectif, NULL, ecran, &posobjectif);
				SDL_Flip(ecran);
			}
			else if (tab[i][j]=='X'){
				SDL_BlitSurface(tresor, NULL, ecran, &postresor);
				SDL_Flip(ecran);
			}
		}
	}
	SDL_Flip(ecran);
	return pos;
}

char ** modifTab(char ** tab, int * pos){
	if ((tab[pos[0]][pos[1]]=='C' || tab[pos[0]][pos[1]] == 'X') && pos[2] == 0 && tab[pos[0]][pos[1]-1] != '#' && tab[pos[0]][pos[1]-1] != 'C' && tab[pos[0]][pos[1]-1] != 'X'){ 
			if (tab[pos[0]][pos[1]-1] == 'I')
				tab[pos[0]][pos[1]-1] = 'X';
			else
				tab[pos[0]][pos[1]-1] = 'C';
			if (tab[pos[0]][pos[1]] == 'X')
				tab[pos[0]][pos[1]] = '@';
			else
				tab[pos[0]][pos[1]] = 'P';
			if (tab[pos[0]][pos[1]+1] == '@')
				tab[pos[0]][pos[1]+1] = 'I';
			else
				tab[pos[0]][pos[1]+1] = '0';
	}
	else if((tab[pos[0]][pos[1]]=='C' || tab[pos[0]][pos[1]] == 'X') && pos[2] == 1 && tab[pos[0]][pos[1]+1] != '#' && tab[pos[0]][pos[1]+1] != 'C' && tab[pos[0]][pos[1]+1] != 'X'){ 
			if (tab[pos[0]][pos[1]+1] == 'I')
				tab[pos[0]][pos[1]+1] = 'X';
			else
				tab[pos[0]][pos[1]+1] = 'C';
			if (tab[pos[0]][pos[1]] == 'X')
				tab[pos[0]][pos[1]] = '@';
			else
				tab[pos[0]][pos[1]] = 'P';
			if (tab[pos[0]][pos[1]-1] == '@')
				tab[pos[0]][pos[1]-1] = 'I';
			else
				tab[pos[0]][pos[1]-1] = '0';
	}
	else if((tab[pos[0]][pos[1]]=='C' || tab[pos[0]][pos[1]] == 'X') && pos[2] == 2 && tab[pos[0]-1][pos[1]] != '#' && tab[pos[0]-1][pos[1]] != 'C' && tab[pos[0]-1][pos[1]] != 'X'){ 
			if (tab[pos[0]-1][pos[1]] == 'I')
				tab[pos[0]-1][pos[1]] = 'X';
			else
				tab[pos[0]-1][pos[1]] = 'C';
			if (tab[pos[0]][pos[1]] == 'X')
				tab[pos[0]][pos[1]] = '@';
			else
				tab[pos[0]][pos[1]] = 'P';
			if (tab[pos[0]+1][pos[1]] == '@')
				tab[pos[0]+1][pos[1]] = 'I';
			else
				tab[pos[0]+1][pos[1]] = '0';
	}
	else if((tab[pos[0]][pos[1]]=='C' || tab[pos[0]][pos[1]] == 'X') && pos[2] == 3 && tab[pos[0]+1][pos[1]] != '#' && tab[pos[0]+1][pos[1]] != 'C' && tab[pos[0]+1][pos[1]] != 'X'){ 
			if (tab[pos[0]+1][pos[1]] == 'I')
				tab[pos[0]+1][pos[1]] = 'X';
			else
				tab[pos[0]+1][pos[1]] = 'C';
			if (tab[pos[0]][pos[1]] == 'X')
				tab[pos[0]][pos[1]] = '@';
			else
				tab[pos[0]][pos[1]] = 'P';
			if (tab[pos[0]-1][pos[1]] == '@')
				tab[pos[0]-1][pos[1]] = 'I';
			else
				tab[pos[0]-1][pos[1]] = '0';
	}
	if (tab[pos[0]][pos[1]]=='I' && pos[2] == 0){ 
			tab[pos[0]][pos[1]] = '@';
			if (tab[pos[0]][pos[1]+1] == '@')
				tab[pos[0]][pos[1]+1] = 'I';
			else
				tab[pos[0]][pos[1]+1] = '0';
	}
	else if(tab[pos[0]][pos[1]]=='I' && pos[2] == 1){ 
			tab[pos[0]][pos[1]] = '@';
			if (tab[pos[0]][pos[1]-1] == '@')
				tab[pos[0]][pos[1]-1] = 'I';
			else
				tab[pos[0]][pos[1]-1] = '0';
	}
	else if(tab[pos[0]][pos[1]]=='I' && pos[2] == 2){ 
			tab[pos[0]][pos[1]] = '@';
			if (tab[pos[0]+1][pos[1]] == '@')
				tab[pos[0]+1][pos[1]] = 'I';
			else
				tab[pos[0]+1][pos[1]] = '0';
	}
	else if(tab[pos[0]][pos[1]]=='I' && pos[2] == 3){ 
			tab[pos[0]][pos[1]] = '@';
			if (tab[pos[0]-1][pos[1]] == '@')
				tab[pos[0]-1][pos[1]] = 'I';
			else
				tab[pos[0]-1][pos[1]] = '0';
	}
	else if (tab[pos[0]][pos[1]]!='#' && tab[pos[0]][pos[1]] != 'C'){
		for(int i = 0; i < 12; i++){
		for(int j = 0; j < 12; j++){
			if(tab[i][j] == 'P')
				tab[i][j] = '0';
			else if (tab[i][j] == '@')
				tab[i][j] = 'I';
		}
	}
	if (tab[pos[0]][pos[1]] == 'I' || tab[pos[0]][pos[1]] == '@')
		tab[pos[0]][pos[1]] = '@';
	else
		tab[pos[0]][pos[1]] = 'P';
	}
	else {
		switch (pos[2]) {
			case 0:
				pos[1]++;
				break;
			case 1:
				pos[1]--;
				break;
			case 2:
				pos[0]++;
				break;
			case 3:
				pos[0]--;
				break;
		}
	}
	return tab;
}

void boucleEv(char **tab, int * pos){
	int cont = 1;
	SDL_Event event;
	while(cont){
		SDL_WaitEvent(&event);
		switch(event.type){
			case SDL_KEYDOWN:
				switch(event.key.keysym.sym){
					case SDLK_UP:
						if (tab[pos[0]][pos[1]-1]!='#'){
							pos[2] = 0;
							pos[1] -=1;
						}
					break;
					case SDLK_DOWN:
						if (tab[pos[0]][pos[1]+1]!='#'){
							pos[2] = 1;
							pos[1] += 1;
						}
					break;
					case SDLK_LEFT:
						if (tab[pos[0]-1][pos[1]]!='#'){
							pos[2] = 2;
							pos[0] -= 1;
						}
					break;
					case SDLK_RIGHT:
						if (tab[pos[0]+1][pos[1]]!='#'){
							pos[2] = 3;
							pos[0] += 1;
						}
					break;
					default:
					break;
				}
				affiche(modifTab(tab, pos));
			break;
			case SDL_QUIT:
				cont=0;
		break;
		}
		if (gagne(tab))
			cont = 0;
	}
}

int main(void){
  	FILE * fd = fopen("soko.txt", "r");
  	char **tab=initTab(fd);
  	int * pos = malloc(3*sizeof(int));
  	pos = affiche(tab);
	boucleEv(tab, pos);
	SDL_Quit();
	fclose(fd);
	freeTab2D(tab,TAILLE);
	return EXIT_SUCCESS; 
}

