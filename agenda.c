//
// Created by Benjamin Ducasse on 19/11/2023.
//

#include "agenda.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

char *scanString(void) {
    int T_L = 10; //taille logique variable
    int index = 0;

    // Allouer de la mémoire pour le tableau de caractères
    char* mystr = (char *)malloc(T_L * sizeof(char));

    printf("Saisissez votre chaîne de caractères (appuyez sur entrée pour valider) : ");
    char c; // CHAT GPT MA DIT DE METTRE INT A LA PLACE MAIS J42I PAS COMPRIS... CHAR->> ook! vs INT->> ok! c'est a dire il double la premiere lettre
    while ((c = getchar()) != '\n') {
        if (index == T_L - 1) { // On a plus la place dans le tableau
            T_L += 10;
            mystr = (char *)realloc(mystr, T_L * sizeof(char));

            if (mystr == NULL) {
                printf("Erreur realloc\n");
                return "";
            }
        }
        mystr[index] = c;
        index++;
    }
    mystr[index] = '\0';

    return mystr;
}



t_sk_cell_agenda * Create_entry_agenda(int level, char* nom){ // ATENTION level = niveau partant de 0.
    t_sk_cell_agenda* entry = (t_sk_cell_agenda*)malloc(sizeof(t_sk_cell_agenda));
    entry->value = nom;
    entry->level = level;
    entry->agenda = NULL;
    entry->values = (t_sk_cell_agenda**) malloc(level * sizeof(t_sk_cell_agenda*));
    for (int i=0; i<=level ; i++){
        entry->values[i] = NULL;
    }
    return entry;
}

void Delete_sk_cell_agenda(t_sk_cell_agenda * cell){
    if (cell->agenda != NULL){
        Delete_agenda(cell->agenda);
    }
    //Delete_agenda(cell->agenda);
    free( cell);  // a finir.
    return;
}

void Delete_agenda (p_agenda agenda){
    Delete_contact(&(agenda->personne));
    Delete_rdv_list(&(agenda->rdv));
    free(agenda);
    return;
}


void Delete_contact(t_contact* c){
    free(c);
    return;
}

void Delete_rdv_list(t_std_list_rdv* list_rdv){
    t_cell_rdv* temp = list_rdv->head;
    t_cell_rdv * prev;
    prev = temp;
    while (temp != NULL){
        Delete_rdv(&(prev->rdv));
        free(prev);
        temp = temp->next;
        prev = temp;
    }
    free(list_rdv);
    return;
}

void Delete_rdv(t_rdv * rdv){
    Delete_date( &(rdv->date));
    Delete_hour(&(rdv->duree_rdv));
    Delete_hour(&(rdv->heure_rdv));
    free(rdv);
    return;
}

void Delete_hour (t_heure* h){
    free(h);
    return;
}

void Delete_date(t_date* d){
    free(d);
    return;
}