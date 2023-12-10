
#include "agenda.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

char *scanString(char* message) {
    int T_L = 10;                  //taille logique variable
    int index = 0;
    char* mystr = (char *)malloc(T_L * sizeof(char));
    printf("%s",message);
    char c;
    while ((c = getchar()) != '\n') {
        if (index == T_L - 1) { // Si on a atteint le nombre de caractères maximales
            T_L += 10;
            mystr = (char *)realloc(mystr, T_L * sizeof(char));
            if (mystr == NULL) {
                printf("Erreur realloc\n");
                return "";
            }
        }
        mystr[index] = c;
        index++;
    }
    mystr[index] = '\0';
    return mystr;
}

p_contact Create_p_contact(char * name){
    p_contact contact = (p_contact) malloc(sizeof (t_contact));
    int i = 0;
    contact->nom = (char*)malloc(sizeof(char)*strlen(name));
    while (name[i] != ' ' && name[i] != '\n' && name[i] != '\0' && name[i] != '_'){ // Dans les cas où : il n'y a pas de prenoms, nom et prenom sont separe d'un espace ou d'un _
        contact->nom[i]=name[i];
        i++;
    }
    int j =i;
    while (name[i] != '\n' && name[i] != '\0'){
        contact->prenom[i-j]=name[i];
    }
    return contact;
}

t_sk_cell_agenda * Create_entry_agenda(int level, char* nom){ // ATENTION level => niveau partant de 0
    t_sk_cell_agenda* entry = (t_sk_cell_agenda*)malloc(sizeof(t_sk_cell_agenda));
    entry->value = nom;
    entry->level = level;
    entry->agenda = Create_p_agenda(nom);
    entry->values = (t_sk_cell_agenda**) malloc(level * sizeof(t_sk_cell_agenda*));
    for (int i=0; i<=level ; i++){
        entry->values[i] = NULL;
    }
    return entry;
}


t_date* Create_t_date (int j, int m, int a){
    t_date* date = (t_date*) malloc(sizeof (t_date));
    date->jour =j;
    date->mois = m;
    date->annee = a;
    return date;
}


t_horaire* Create_t_heure (int h, int m){
    t_horaire *heure = (t_horaire*) malloc(sizeof (t_horaire));
    heure->heure = h;
    heure->minute = m;
    return heure;
}

t_rdv* Create_t_rdv (t_date* date, t_horaire* h, t_horaire* dure, char * obj){
    t_rdv* rdv = (t_rdv*)malloc(sizeof (t_rdv));
    rdv->date = date;
    rdv->duree_rdv = dure;
    rdv->heure_rdv = h;
    rdv->obj_rdv = obj;
    return rdv;
}


t_cell_rdv * Create_t_cell_rdv ( t_rdv * rdv){
    t_cell_rdv* cell = (t_cell_rdv*) malloc(sizeof (t_cell_rdv));
    cell->rdv = rdv;
    cell->next = NULL;
    return cell;
}

void add_rdv_to_p_agenda (p_agenda agenda, t_rdv* rdv){
    t_cell_rdv * cell = Create_t_cell_rdv(rdv) ;
    if (agenda->rdv_list->head == NULL){           //si liste des rdv est vide ajoute au debut
        agenda->rdv_list->head = cell;
        Display_rdv(rdv);
    }
    else {
        // sinon ajoute a la fin
        t_cell_rdv * temp = agenda->rdv_list->head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = cell;
    }
    return;
}

void add_rdv (p_agenda agenda){// lance tout les fonctions necessaires pour ajouter un rdv
    int a,m,j,h1,m1,h2,m2;
    printf("Jour (le numéro): ");
    scanf("%d",&j);
    printf("Mois (numéro): ");
    scanf("%d",&m);
    printf("Année (numéro): ");
    scanf("%d",&a);
    printf("Heure de debut (ex : 18): ");
    scanf("%d",&h1);
    printf("Minute de debut : ");
    scanf("%d",&m1);
    printf("Duree heure : ");
    scanf("%d",&h2);
    printf("Duree minute : ");
    scanf("%d",&m2);
    char * obj = scanString("Objet du rdv : ");
    add_rdv_to_p_agenda(agenda,Create_t_rdv(Create_t_date(j,m,a), Create_t_heure(h1,m1), Create_t_heure(h2,m2),obj));
    printf("Le rdv a ete ajoute\n");
    return;
}



p_agenda Create_p_agenda ( t_contact* name){
    p_agenda agenda = (p_agenda)malloc(sizeof (t_agenda));
    agenda->personne = Create_p_contact(name);
    t_std_list_rdv* list_rdv = (t_std_list_rdv*) malloc(sizeof (t_std_list_rdv));
    list_rdv->head = NULL;
    agenda->rdv_list = list_rdv;
    return agenda;
}

p_sk_cell_agenda Create_New_cell_agenda (char * name){
    p_sk_cell_agenda cell = Create_entry_agenda(1,name); //level cree de base 1
    p_contact contact = Create_p_contact(name);
    cell->agenda = Create_p_agenda(contact);
    return cell;
}


//-------------------------FCT AFFICHAGE---------------------------

void Display_rdv (t_rdv* rdv){
    if (rdv->obj_rdv!= NULL){
        printf("RDV : %s\n", rdv->obj_rdv);
    }
    printf("     Le : %d/%d/%d \n",rdv->date->jour,rdv->date->mois,rdv->date->annee);
    printf("     A : %dh%d\n",rdv->heure_rdv->heure,rdv->heure_rdv->minute);
    printf("     De : %dh%d\n\n",rdv->duree_rdv->heure,rdv->duree_rdv->minute);
    return ;
}

void Display_list_rdv(t_std_list_rdv* list_rdv){
    if (list_rdv->head == NULL){
        printf("Il n'y a pas de rdv enregistre pour ce contact\n");
    }
    else{
        p_cell_rdv cell_rdv = list_rdv->head;
        while (cell_rdv != NULL){
            Display_rdv(cell_rdv->rdv);
            cell_rdv = cell_rdv->next;
            printf("-----");
        }
    }
    return;
}




void delete_search_rdv(t_std_list_rdv* list_rdv){
    int a,m,j,h1,m1;
    printf("Selectionnez les information du rdv pour le supprimer\n");
    printf("Jour : ");
    scanf("%d",&j);
    printf("Mois : ");
    scanf("%d",&m);
    printf("Année : ");
    scanf("%d",&a);
    printf("Heure de debut : ");
    scanf("%d",&h1);
    printf("Minute de debut : ");
    scanf("%d",&m1);
    p_cell_rdv cell_rdv = list_rdv->head;
    p_cell_rdv pres = cell_rdv;
    //si premiere cell
    if (cell_rdv->rdv->date->annee == a && cell_rdv->rdv->date->mois == m && cell_rdv->rdv->date->jour == j && cell_rdv->rdv->heure_rdv->heure == h1 && cell_rdv->rdv->heure_rdv->minute == m1){
        list_rdv->head = cell_rdv->next;
        Delete_cell_rdv(cell_rdv);
        printf("Le rdv a bien ete supprime\n");
        return ;
    }
    while(cell_rdv != NULL){
        if (cell_rdv->rdv->date->annee == a && cell_rdv->rdv->date->mois == m && cell_rdv->rdv->date->jour == j && cell_rdv->rdv->heure_rdv->heure == h1 && cell_rdv->rdv->heure_rdv->minute == m1){
            pres->next = cell_rdv->next;
            Delete_cell_rdv(cell_rdv);
            printf("Le rdv a bien ete supprime\n");
            return;
        }
        pres = cell_rdv;
        cell_rdv = cell_rdv->next;
    }
    printf("Le rdv n'existe pas\n");
    return;
}



//-------------------------FCT Delete-------------------------------

void Delete_sk_cell_agenda(t_sk_cell_agenda * cell){
    if (cell->agenda != NULL){
        Delete_agenda(cell->agenda);
    }
    free( cell);
    return;
}

void Delete_agenda (p_agenda agenda){
    Delete_contact(agenda->personne);
    Delete_rdv_list(agenda->rdv_list);
    free(agenda);
    return;
}


void Delete_contact(t_contact* c){
    free(c);
    return;
}

void Delete_rdv_list(t_std_list_rdv* list_rdv){
    t_cell_rdv* temp = list_rdv->head;
    t_cell_rdv * prev;
    prev = temp;
    while (temp != NULL){
        Delete_rdv(prev->rdv);
        free(prev);
        temp = temp->next;
        prev = temp;
    }
    free(list_rdv);
    return;
}

void Delete_cell_rdv(t_cell_rdv * cell){
    Delete_rdv(cell->rdv);
    free(cell);
    return;
}

void Delete_rdv(t_rdv * rdv){
    Delete_date( rdv->date);
    Delete_hour(rdv->duree_rdv);
    Delete_hour(rdv->heure_rdv);
    free(rdv);
    return;
}

void Delete_hour (t_horaire* h){
    free(h);
    return;
}

void Delete_date(t_date* d){
    free(d);
    return;
}

