//
// Created by loeiz on 26/10/2023.
//

#ifndef PROJET__LIST_H
#define PROJET__LIST_H
#include "cell.h"



typedef struct s_sk_list{
    t_sk_cell ** head;
    int max_level;

}t_sk_list;

typedef  t_sk_list *p_sk_list;








#endif //PROJET__LIST_H
