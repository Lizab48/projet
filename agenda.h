//
// Created by Benjamin Ducasse on 19/11/2023.
//

#ifndef PROJET__AGENDA_H
#define PROJET__AGENDA_H

// PARTIE 3 :
// TYPE STRUCTURES DE DONNEES
typedef struct s_contact {
    char* nom;
    char* prenom;
} t_contact, *p_contact;

typedef struct s_date {
    int jour;
    int mois;
    int annee;
}t_date;

typedef struct s_heure {
    int heure;
    int minute;
}t_heure;

typedef struct s_rdv {
    t_date date;
    t_heure heure_rdv;
    t_heure duree_rdv;
    char * obj_rdv;
} t_rdv;

typedef struct s_cell_rdv{
    t_rdv rdv;
    struct s_cell_rdv * next;
}t_cell_rdv, *p_cell_rdv;

typedef struct s_std_list_rdv {
    p_cell_rdv head;
}t_std_list_rdv;

typedef struct s_agenda {
    t_contact personne;
    t_std_list_rdv rdv;

}t_agenda, *p_agenda;

typedef struct s_sk_cell_agenda {   //entree dans un agenda.
    p_agenda agenda ;
    int level;
    struct s_sk_cell_agenda ** values;
    char* value; // du type nom_prenom
}t_sk_cell_agenda ;


char *scanString(void); // je la mets ou cette fonction ?

t_sk_cell_agenda * Create_entry_agenda(int , char*); //level , nom du contact  // utilise Create_entry_agenda() dans agenda.c


//FONCTIONS DELETE.
void Delete_sk_cell_agenda(t_sk_cell_agenda * );
void Delete_agenda (p_agenda agenda);
void Delete_contact(t_contact*);
void Delete_rdv_list(t_std_list_rdv*);
void Delete_rdv(t_rdv *);
void Delete_hour (t_heure*);
void Delete_date(t_date*);

#endif //PROJET__AGENDA_H
