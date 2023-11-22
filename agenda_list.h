//
// Created by Benjamin Ducasse on 19/11/2023.
//

#ifndef PROJET__AGENDA_LIST_H
#define PROJET__AGENDA_LIST_H
#include "agenda.h"


// TOUTES LES FONCTIONS QUI GERENT LA LONGUE LISTE D'ENTREES D'AGENDA

typedef struct s_sk_list_agenda{
    t_sk_cell_agenda ** head;
    int max_level;

}t_sk_list_agenda;  // agenda


int menu_agenda();

p_contact Searching_contact_in_list(t_sk_list_agenda*); //1
p_contact Searching_contact_from_str(char*);  // called by Searching_contact_in_list

void Display_rdv(p_contact ); //2

void Display_contact(p_contact);

// 4 5 6 7 8 a faire.

t_sk_list_agenda* Create_empty_agenda();
void Filling_agenda_w_contacts(int, t_sk_list_agenda*);
void Filling_agenda_sans_fichier(int, t_sk_list_agenda*); //pour eviter d'etre bloquer parce qu'il ne vuet pas ouvrir de fichier.

void Display_list_simple_agenda (t_sk_list_agenda);
void Display_level_list_agenda (t_sk_list_agenda mylist, int level);

// Fonctions delete

void Delet_list_agenda(t_sk_list_agenda*);
#endif //PROJET__AGENDA_LIST_H
