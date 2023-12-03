//
// Created by loeiz on 26/10/2023.
//

#include "cell.h"
#include <stdlib.h>
#include <stdio.h>

p_sk_cell Create_cell_sk (int val , int level){ // level c'est 0 le premier niveaux
    p_sk_cell mycell;
    mycell = (p_sk_cell)malloc(sizeof (t_sk_cell )); // attention generer la place de la structure sinon ne fonctionne pas
    mycell->value = val;
    mycell->level = level;
    mycell->values = (p_sk_cell*)malloc(level * sizeof(p_sk_cell));
    for (int i=0; i<=level; i++){
        mycell->values[i]=NULL;
    }
    return mycell;
}

void Delete_sk_cell(t_sk_cell* cell){
    free(cell);
    return;
}