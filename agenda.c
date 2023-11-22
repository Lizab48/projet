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
    for (int i=0; i<=level ; i++){
        entry->values[i] = NULL;
    }
    return entry;
}