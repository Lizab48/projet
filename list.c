
#include "list.h"
#include "complementaire.h"
#include <stdio.h>
#include <stdlib.h>
//#include <malloc.h>   // a mettre en commentaire selon votre d'ordinateur
#include <stdlib.h>
#include <math.h>


// FONCTIONS DE LA PARTIE 1 ..............................................................................
t_sk_list Create_empty_list(int level_max){

    t_sk_list mylist;
    mylist.head = (t_sk_cell**)malloc(level_max*sizeof( t_sk_cell*));
    for (int i=0; i<level_max; i++){
        mylist.head[i]=NULL;
    }
    mylist.max_level = level_max;
    return mylist;
}

int is_Empty_list(t_sk_list mylist){
    if (mylist.head[0] != NULL ){
        return 0;
    }
    return 1;
}

void Insert_in_list_head ( t_sk_list* mylist, t_sk_cell *cell_new){
    for (int i = 0; i <= cell_new->level; i++) {
        if (mylist->head[i] != NULL) {
            cell_new->values[i] = mylist->head[i];
            mylist->head[i] = cell_new;

        }else {
            mylist->head[i] = cell_new;
        }
    }
    return;
}

void Insert_in_list_croissant(p_sk_list mylist, p_sk_cell new_cell){  // cette fonction est opérationnelle uniquement sur certains ordinateurs...
    if ( mylist->max_level <= (new_cell->level - 1) ){    // si le nombre de niveaux de new_cell est trop grand
        printf("La cellule ne peut pas être entrer dans la liste, car elle est trop longue");
        return;
    }
    if (is_Empty_list(*mylist)){       // si la liste est vide
        printf("td (%d  ) ", new_cell->value);
        Insert_in_list_head( mylist , new_cell );
    }
    else{
        p_sk_cell temp = mylist->head[0];
        //printf("(prem cell : %d)", temp->value);
        if ( temp->value >= new_cell->value ){  // si la valeur de la premiere cellule est plus grande que new_cell
            Insert_in_list_head( mylist , new_cell );
            return;
        }
        else{
            p_sk_cell prev  = temp;
            while(temp != NULL){  //parcours du premier niveau;

                if ( new_cell->value <= temp->value ){
                    // insertion cell, entre prev et temp.

                    for (int i=0; i<= new_cell->level ; i++){
                        new_cell->values[i] = prev->values[i];
                        prev->values[i] = new_cell;
                    }
                    if ( new_cell->level > prev->level){
                        for (int i= prev->level +1; i <= new_cell->level; i++ ){

                            p_sk_cell precedent = mylist->head[i];
                            if (precedent == NULL){
                                // alors on fait le nouveau lien
                                precedent = new_cell ;
                            }
                            else if (precedent->value >= new_cell->value){
                                // alors on fait le nouveau lien
                                printf(" %d >= %d",precedent->value ,new_cell->value);
                                new_cell->values[i] = precedent;
                                mylist->head[i] = new_cell;
                            }
                        }
                    }
                    return ;
                }
                prev = temp ;
                temp = temp->values[0];
            }
            // ajout en fin de liste
            for (int i=0; i<= prev->level ; i++){
                prev->values[i] = new_cell;
            }
            if ( new_cell->level > prev->level){  // la cellule de fin est plus longue que prev, on fait le chainage :
                for (int i= prev->level +1; i <= new_cell->level; i++ ){
                    p_sk_cell precedent = mylist->head[i];
                    if (precedent ==NULL){
                        mylist->head[i] = new_cell;
                    }
                    else if (precedent->value >= new_cell->value){
                        printf(" %d >= %d",precedent->value ,new_cell->value);
                        mylist->head[i] = new_cell;
                        new_cell->values[i] = precedent;
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

void Display_level_list (t_sk_list mylist, int level){  // affichage d'une liste sur un niveau donné
    // ATTENTION : ON RAPPELLE QUE LES NIVEAU COMMENCE A ZERO !!!
    printf("[ list head_%d @ ]-->", level);

    p_sk_cell temp = (mylist.head[level]);
    while( temp != NULL){
        printf("[%d | @ ]-->", temp->value);
        temp = temp->values[level];
    }
    printf("NULL\n");
    return;
}


// FONCTIONS DE LA PARTIE 2 ..............................................................................

t_sk_list Create_level_list(int n){            //n le nombre de niveau
    t_sk_list mylist  = Create_empty_list(n);
    printf("liste vide créer pour level liste\n");
    //Display_list_simple(mylist);
    t_tab * mytab = level(n);   // Initialisation de la liste avec les niveaux correspondant
    // AFFICHAGE DU TABLEAU
    printf("Voici mon tableau pour n=%d : [",n);
    for (int i=0; i<mytab->longueur ; i++){
        printf(" %d ",mytab->value[i]);
    }
    printf("]\n");

    for (int i=mytab->longueur; i>= 1 ; i--){
        p_sk_cell cell = Create_cell_sk(i, mytab->value[i-1]);  // Create_cell_sk( value , niveau )
        Insert_in_list_head(&mylist , cell);
        //AFFICHAGE DE VERIFICATION DE CHAINAGE :
        //printf(" Insertion reussi apriori : level%d %d\n",mytab->value[i-1] , i);
        //Display_list_simple(mylist);
    }
    return mylist;
}


int Search_list_simple(t_sk_list mylist ,int n){
    // Recherche dans la liste uniquement depuis le premier niveau. Complexité o(n)
    p_sk_cell cell = mylist.head[0];
    while(cell !=NULL){
        if ( cell->value == n){
            return 1;
        }
        cell = cell->values[0];
    }
    return 0;
}




int Search_list_level_part (int val, t_sk_list mylist ) {
    //printf(" Searching list level part (val %d) (current cell_depart %d)\n", level , val, cell_depart->value);
    p_sk_cell temp = mylist.head[mylist.max_level -1];  // initialisation
    p_sk_cell prev = temp;
    int current_level = mylist.max_level -1;
    while ( current_level>=0 ) {
        int quit = 0;
         while (temp !=NULL && quit ==0){
             if (temp->value <= val){
                 if ( temp->value == val){
                     return 1;
                 }
                 prev = temp;
                 temp = temp->values[current_level];
             }
             else {
                 quit =1;
             }
         }

         if (temp ==NULL){
             current_level-=1;
             temp = prev->values[current_level];
         }else if (temp->value > val){   // on va parcourir à gauche

             if ( prev == mylist.head[current_level] ){
                 current_level-=1;
                 temp = mylist.head[current_level];
                 prev = temp;
             }
             else{
                 current_level-=1;
                 temp = prev->values[current_level];
             }
         }

    }
    return 0;
}

int Search_list_upper_level(t_sk_list mylist , int val){
    // recherche dichotomique , à partir du plus haut niveau. o(n/2)
    if (is_Empty_list(mylist)){
        return 0;
    }
    else{
        return Search_list_level_part(val, mylist);
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
    //free(mylist); -> provoque une erreur... je ne comprends pas
    return;
}