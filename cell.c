//
// Created by loeiz on 26/10/2023.
//

#include "cell.h"
#include <stdlib.h>
#include <stdio.h>

p_sk_cell Create_cell_sk (int val , int level){ // level c'est 0 le premier normalement alors on fait quoi ? Ici, la manière dont c'est codé, on a dit que level c'est 1 le premier...
    p_sk_cell mycell;
    mycell = (p_sk_cell)malloc(sizeof (p_sk_cell)); // attention generer la place de la structure sinon ne fonctionne pas
    mycell->value = val;
    mycell->level = level;
    mycell->values = (p_sk_cell*)malloc(level * sizeof(p_sk_cell));
    for (int i=0; i<=level; i++){ //mettre toute les cases du tableau à vide sinon il vas il y avoir des valeurs inconnu et pour verifier si la cell est vide (si mycell->values[0]==NULL
        mycell->values[i]=NULL;
    }
    return mycell;
}