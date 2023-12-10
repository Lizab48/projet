//
// Created by Louise Monciero on 19/11/2023.
//

#ifndef PROJET__AGENDA_H
#define PROJET__AGENDA_H


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

typedef struct s_horaire {
    int heure;
    int minute;
}t_horaire;

typedef struct s_rdv {
    t_date *date;
    t_horaire *heure_rdv;
    t_horaire *duree_rdv;
    char * obj_rdv;
} t_rdv;

typedef struct s_cell_rdv{
    t_rdv *rdv;
    struct s_cell_rdv * next;
}t_cell_rdv, *p_cell_rdv;

typedef struct s_std_list_rdv {
    p_cell_rdv head;
}t_std_list_rdv;

typedef struct s_agenda {
    t_contact *personne;
    t_std_list_rdv *rdv_list;

}t_agenda, *p_agenda;

typedef struct s_sk_cell_agenda {   //les entrees dans un agenda.
    p_agenda agenda ;
    int level;
    struct s_sk_cell_agenda ** values;
    char* value; // du type nom_prenom
}t_sk_cell_agenda ;
typedef t_sk_cell_agenda *p_sk_cell_agenda;

char *scanString(char* message);

//FONCTIONS DE CREATION DES MULTIPLES STRUCTURES........................................................................
p_sk_cell_agenda Create_New_cell_agenda (char *); //appelle Create_entry_agenda()
t_sk_cell_agenda * Create_entry_agenda(int , char*); // (level , nom du contact)
p_contact Create_p_contact(char *);
p_agenda Create_p_agenda ( t_contact*);
t_date* Create_t_date (int, int, int);
t_horaire* Create_t_heure (int, int);




//FONCITONS DE GESTIONS DE RENDEZ-VOUS............................................................................
void add_rdv (p_agenda agenda); // lance tout les fonctions necessaire pour ajouter un rdv
void add_rdv_to_p_agenda (p_agenda, t_rdv*);
t_rdv* Create_t_rdv (t_date*, t_horaire*, t_horaire*, char *);
t_cell_rdv * Create_t_cell_rdv (t_rdv *);
void delete_search_rdv_date(t_std_list_rdv*);
void delete_search_rdv_obj(t_std_list_rdv*);
void Display_rdv (t_rdv*);
void Display_list_rdv(t_std_list_rdv* rdv);


//FONCTIONS SUPPESSION DES STRUCTURES.............................................................................
void Delete_sk_cell_agenda(t_sk_cell_agenda * );
void Delete_agenda (p_agenda agenda);
void Delete_contact(t_contact*);
void Delete_rdv_list(t_std_list_rdv*);
void Delete_cell_rdv(t_cell_rdv * cell);
void Delete_rdv(t_rdv *);
void Delete_hour (t_horaire*);
void Delete_date(t_date*);


#endif //PROJET__AGENDA_H