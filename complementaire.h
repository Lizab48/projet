#ifndef PROJET__COMPLEMENTAIRE_H
#define PROJET__COMPLEMENTAIRE_H



typedef struct s_cell_std{
    int value;
    struct s_cell_std * next;
}t_cell_std;

typedef struct s_std_list{
    t_cell_std* head ;
} t_std_list;

typedef struct s_tab {
    int* value;
    int longueur;
}t_tab;

t_tab* level(int);

#endif //PROJET__COMPLEMENTAIRE_H