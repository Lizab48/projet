//
// Created by Benjamin Ducasse on 19/11/2023.
//

#ifndef PROJET__APPLI_AGENDA_H
#define PROJET__APPLI_AGENDA_H
#include "agenda.h"


int menu_agenda();

p_contact Searching_contact_in_list(t_sk_list_agenda*); //1
p_contact Searching_contact_from_str(char*);

void Display_rdv(p_contact ); //2

void Display_contact(p_contact);

void Create_Add_contact(t_sk_list_agenda*,t_contact); //3

void Create_rdv(t_sk_list_agenda*); //4

void Delete_rdv(t_rdv*); //5 ??????
void Delete_rdv_from_agenda(t_rdv*,t_contact);

// 6 7 8 a faire.

t_sk_list_agenda* Create_empty_agenda();
void Filling_agenda_w_contacts(int, t_sk_list_agenda*);

#endif //PROJET__APPLI_AGENDA_H
