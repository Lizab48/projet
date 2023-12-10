//
// Created by Louise Monciero on 19/11/2023.
//

#ifndef PROJET__AGENDA_LIST_H
#define PROJET__AGENDA_LIST_H
#include "agenda.h"


// STRUCTURE...........................................................................................................

typedef struct s_sk_list_agenda{
    t_sk_cell_agenda ** head;
    int max_level;
}t_sk_list_agenda;


// FONCTIONS DE GESTIONS DE LA LIST D'AGENDAS...........................................................................
int menu_agenda();  // Fonction appelante de toutes les autres fonctions

// RECHERCHE DE CONTACTS DANS LA LISTE
p_sk_cell_agenda Search_list_simple_agenda(t_sk_list_agenda  ,char *);
p_sk_cell_agenda Search_list_level_part_agenda (int , char *, p_sk_cell_agenda , t_sk_list_agenda );
p_sk_cell_agenda Search_list_upper_level_agenda(t_sk_list_agenda , char *);

void Add_contact(t_sk_list_agenda , p_sk_cell_agenda);    // ajoute un contact dans la liste au premier niveau sont la trier.
void Display_contact(p_contact);


// CREATION DE LISTE D'AGENDA
t_sk_list_agenda* Create_empty_agenda_list();
void Filling_agenda_w_contacts(int, t_sk_list_agenda*);   // Le fichier n'est pas exploité par le programme
void Filling_agenda_sans_fichier(int, t_sk_list_agenda*); //pour eviter d'etre bloquer, cette fonction rempli un agenda par défault
void Insert_entry_agenda_in_list (p_sk_cell_agenda , t_sk_list_agenda*); // Fonction non compléte.

//AFFICHAGE DE LISTE D'AGENDA
void Display_list_simple_agenda (t_sk_list_agenda);
void Display_level_list_agenda (t_sk_list_agenda mylist, int level);


void Delete_list_agenda(t_sk_list_agenda*);
#endif //PROJET__AGENDA_LIST_H