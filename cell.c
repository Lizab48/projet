//
// Created by loeiz on 26/10/2023.
//

#include "cell.h"
#include <stdlib.h>

p_sk_cell Create_cell_sk (int val , int level){
    p_sk_cell mycell;
    mycell-> value = val;
    mycell->level = level;
    mycell->values = (p_sk_cell*)malloc(sizeof(p_sk_cell)*level);
    return mycell;
}