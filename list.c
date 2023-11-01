//
// Created by loeiz on 26/10/2023.
//

#include "list.h"
#include <stdio.h>

t_sk_list Create_empty_list(int level_max){   // a tester 
    t_sk_list mylist;
    mylist.head = (t_sk_cell**)calloc(level_max, sizeof( t_sk_cell*));
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
        for (int i=0 ; i <= cell->level ; i++){
            cell->values[i] = mylist->head[i];
            mylist->head[i] = &(cell);
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


void Display_list_simple (t_sk_list mylist){     // a tester
    for (int i= 0 ; i <= mylist.max_level; i++){
        Display_level_list(mylist , i);
    }
    return;
}

void Display_level_list (t_sk_list mylist, int level){  // a tester
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
