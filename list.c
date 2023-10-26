//
// Created by loeiz on 26/10/2023.
//

#include "list.h"

#include <stdlib.h>

p_sk_list Create_list (int level_max){
    p_sk_list p_list;
    p_list->max_level = level_max;
    p_list->head = (p_sk_list*)malloc(sizeof(p_sk_list)*level_max);
    return p_list;
}