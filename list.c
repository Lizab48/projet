//
// Created by loeiz on 26/10/2023.
//

#include "list.h"
#include "complementaire.h"
#include <stdio.h>
#include <stdlib.h>
//#include <malloc.h>
#include <stdlib.h>
#include <math.h>

t_sk_list Create_empty_list(int level_max){
    // retourne
    t_sk_list mylist;
    mylist.head = (t_sk_cell**)malloc(level_max*sizeof( t_sk_cell*));
    for (int i=0; i<level_max; i++){ //mettre toute les cases du tableau à vide sinon il va y avoir des valeurs inconnu et pour verifier si la liste est vide (si mylist.head[0]==NULL
        mylist.head[i]=NULL;
    }
    mylist.max_level = level_max;
    return mylist;
}

int is_Empty_list(t_sk_list mylist){     // a tester
    int vide = 1;
    for (int i=0 ; i<= mylist.max_level ; i++){
        if (mylist.head[i] != NULL ){
            vide = 0;
            return vide;
        }
    }
    return vide;
}

void Insert_in_list_head ( t_sk_list* mylist, t_sk_cell *cell){  // optimiser cette fonction

    for (int i = 0; i <= cell->level; i++) {
        if (mylist->head[i] != NULL) { //si le niveau est vide, met comme premier
            cell->values[i] = mylist->head[i];
            mylist->head[i] = cell; //-> pas besoin de mettre & car c'est deja un pointeur (c'est deja l'adresse)
        }else {
            mylist->head[i] = cell;
            printf("inserer niveau vide\n");
        }
    }
    return;
}

void Insert_in_list_croissant(p_sk_list mylist, p_sk_cell cell){        // VRAIMENT PAS CERTAINE °-°
    if ( mylist->max_level <= (cell->level - 1) ){
        printf("La cellule ne peut pas être entrer dans la liste, car elle est trop longue");
        return;
    }
    if (is_Empty_list(*mylist)){       // si la liste est vide ;
        Insert_in_list_head( mylist , cell );
    }
    else{
        p_sk_cell temp = mylist->head[0];
        if ( temp->value >= cell->value ){  // si la premiere cellule est plus petite que cell
            Insert_in_list_head( mylist , cell );
        }
        else{
            p_sk_cell prev  = temp;
            while(temp != NULL){  //parcours du premier niveau;
                prev = temp ;
                temp = temp->values[0];
                if ( cell->value <= temp->value ){
                    // insertion cell, entre prev et temp.

                    for (int i=0; i<= cell->level ; i++){
                        cell->values[i] = prev->values[i];
                        prev->values[i] = cell;
                    }
                    if ( cell->level > prev->level){
                        printf("La cellule ajouter est plus longue que prévu, le chainage n'est pas correctement fait");
                        for (int i= prev->level ; i <= cell->level; i++ ){
                            p_sk_cell precedent = mylist->head[i];
                            if (precedent->values[i]->value >= cell->value){
                                // alors on fait le nouveau lien !
                                cell->values[i] = precedent->values[i];
                                precedent->values[i] = cell ;
                            }
                        }
                    }
                    return ;
                }
            }
            // ajouter en fin de liste.
            for (int i=0; i<= cell->level ; i++){
                cell->values[i] = prev->values[i];
                prev->values[i] = cell;
            }
            if ( cell->level > prev->level){
                printf("La cellule ajouter est plus longue que prévu, le chainage n'est pas correctement fait");
                for (int i= prev->level ; i <= cell->level; i++ ){
                    p_sk_cell precedent = mylist->head[i];
                    if (precedent->values[i]->value >= cell->value){
                        // alors on fait le nouveau lien !
                        cell->values[i] = precedent->values[i];
                        precedent->values[i] = cell ;
                    }
                }
            }
        }
    }
    return;
}


void Display_list_simple (t_sk_list mylist){
    for (int i= 0 ; i < mylist.max_level; i++){
        Display_level_list(mylist , i);
    }
    return;
}

void Display_level_list (t_sk_list mylist, int level){  // a quoi sert la variable level.
    // ATTENTION ; ON RAPPELLE QUE LES NIVEAU COMMENCE A ZERO !!!
    printf("[ list head_%d @ ]-->", level);
    t_sk_cell *temp = (mylist.head[level]);
    while( temp != NULL){
        printf("[%d | @ ]-->", temp->value);
        temp = temp->values[level];
    }
    printf("NULL\n");
    return;
}


void testlist(){
    printf("ok");
    return;
}


// FONCTIONS PARTIES 2 :

t_sk_list Create_level_list(int n){
    t_sk_list mylist  = Create_empty_list(n);
    //AFFICHAGE A SUPPRIMER
    printf("liste vide créer pour level liste\n");
    // Initialisation de la liste avec les niveaux correspondant.
    t_tab * mytab = level(n);   // comporte [0,1,0,2,0,1,0] --> ok!
    //Display tab
    printf("Voici mon tableau pour n=%d : [",n);
    for (int i=0; i<mytab->longueur ; i++){
        printf(" %d ",mytab->value[i]);
    }
    printf("]\n");
    for (int i=mytab->longueur; i>= 1 ; i--){
        p_sk_cell cell = Create_cell_sk(i, mytab->value[i-1]);
        Insert_in_list_head(&mylist , cell);
    }
    return mylist;
}


int Search_list_simple(t_sk_list mylist ,int n){ //a tester
    // recherche dans la liste uniquement depuis le premier niveau complexité o(n)
    p_sk_cell cell = mylist.head[0];
    while(cell !=NULL){
        if ( cell->value == n){
            return 1;
        }
        cell = cell->values[0];
    }
    return 0;
}




int Search_list_level_part (int level, int val, p_sk_cell cell_depart, t_sk_list mylist ) { // a tester

    //printf(" Searching list level part (level %d) (val %d) (current cell_depart %d)\n", level , val, cell_depart->value);
    if ( cell_depart-> value == val){
        return 1;
    }
    else if (cell_depart->value < val){  // si ma val se trouve dans le tableau de droite
        if ( level ==0){
            return 0;
        }
        else{ // c'est pas bon tu oublie ma cellule 0.
            return Search_list_level_part( level-1, val, cell_depart->values[level-1], mylist);
        }
    }
    else if (cell_depart->value > val){ // si ma val se trouve dans le tableau de gauche
        p_sk_cell temp = cell_depart->values[level];
        while (temp != NULL){
            if (temp->value == val){
                return 1;
            }
            else{
                temp = temp->values[level];
            }
        }
        if ( level == 0){
            return 0;
        }
        else {
            return Search_list_level_part(level-1 , val , mylist.head[level-1], mylist);

        }
    }

    /*
    t_sk_cell* cell_s ;// = (t_sk_cell*) malloc(sizeof (t_sk_cell));
    cell_s = cell_d;
    while (cell_s->value <= val)
    {
        if (cell_s->values[level]==NULL)
            return 0; // on arrive a la fin de la liste et on n'a pas trouver
        cell_s = cell_s->values[level];
    }
    if (cell_s->value == val)
        return 1; //valeur trouver;
    else if (cell_s->value < val)
        return Search_list_level_part(level-1,val,cell_d->values[level-1]); //on repart de la cellule du debut mais du niveaux du dessous
    else
        return Search_list_level_part(level-1, val, cell_s->values[level-1]);
    */
}

int Search_list_upper_level(t_sk_list mylist , int val){ // a tester
    // recherche dichotomique , à partir du plus haut niveau. o(n/2)
    // fonction a completer
    if (is_Empty_list(mylist)){
        return 0;
    }
    else{
        int level = mylist.max_level -1;
        p_sk_cell cell = mylist.head[level];
        return Search_list_level_part(level, val, cell, mylist);
    }
}

void Delete_sk_list(t_sk_list* mylist){
    p_sk_cell temp =mylist->head[0];
    p_sk_cell prev = temp;
    while ( temp!=NULL){
        temp = prev->values[0];
        Delete_sk_cell(prev);
        prev = temp;
    }
    free(mylist);
    return;
}