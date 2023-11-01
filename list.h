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


t_sk_list Create_empty_list(int);

int is_Empty_list(t_sk_list);

void Insert_in_list_head ( t_sk_list* , p_sk_cell);

void Insert_in_list_croissant(p_sk_list , p_sk_cell);

void Display_list_simple (t_sk_list);

void Display_level_list (t_sk_list , int );

void testlist();




#endif //PROJET__LIST_H
