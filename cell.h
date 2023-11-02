//
// Created by loeiz on 26/10/2023.
//

#ifndef PROJET__CELL_H
#define PROJET__CELL_H


typedef struct s_sk_cell {
    int value;
    int level;
    struct s_sk_cell ** values;
}t_sk_cell;

typedef t_sk_cell *p_sk_cell;

// FONCTIONS ASSOCIEES

p_sk_cell Create_cell_sk (int, int);








#endif //PROJET__CELL_H
