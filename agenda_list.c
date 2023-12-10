//
// Created by Louise Monciero on 19/11/2023.
//

#include "agenda_list.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int menu_agenda(){
    printf("----BIENVENUE DANS LE MENU DE GESTION D'AGENDA----\n\n");
    printf("Quel agenda voulez vous manipuler ?\n"
           "    1. Un agenda generé aléatoirement avec 1000 entrée\n"
           "    2. Un agenda prédefini avec 8 entrée\n"
           "    3. Quitter l'application\n");
    int choix = -1;
    int passed=0;
    t_sk_list_agenda * mylist_agenda;
    while (passed != 1){
        printf("Votre choix :\n");
        scanf("%d",&choix);
        switch (choix){
            case 1:{
                printf("Ce choix est disponible mais ne fonctionne pas pour le moment en raison d'un problème de lecture de fichier\n");
                //mylist_agenda = Create_empty_agenda_list();
                //Filling_agenda_w_contacts(10 , mylist_agenda);
                break;
            }
            case 2 :{
                printf("Création d'un agenda à partir d'un tableau de Nom\n");
                mylist_agenda = Create_empty_agenda_list();
                Filling_agenda_sans_fichier(8, mylist_agenda);
                passed = 1;
                break;
            }
            case 3:{
                printf("Vous quittez l'application\n");
                return 0;
            }
            default:{
                printf("choix : %d\n", choix);
                return 0;
            }
        }
    }
    int quit = 0;
    printf("Voici votre agenda : \n");
    Display_list_simple_agenda(*mylist_agenda);
    printf("\n    1. Rechercher un contact\n"
           "    2. Afficher les rendez-vous d’un contact ;\n"
           "    3. Créer un contact (avec insertion dans la liste) ;\n"
           "    4. Créer un rendez-vous pour un contact (avec insertion dans la liste si le contact n’existe pas) ;\n"
           "    5. Supprimer un rendez-vous ;\n"
           "    6.Quitter.\n");
    char * actual_person_name ="" ;
    while (quit != 1){
        char *choix = scanString("Votre choix\n");
        switch (choix[0]) {
            case '1':{   // cette fonctionnalité est opérationnelle
                actual_person_name = scanString("Entrer le nom du contact recherché :\n");
                p_sk_cell_agenda cell = Search_list_simple_agenda(*mylist_agenda , actual_person_name);
                    if (cell == NULL){
                    printf("La personne que vous recherchez n'existe pas (%s)\n",actual_person_name);
                    actual_person_name ="";
                }else{
                    printf("Le contact %s se trouve dans la liste des agandas\n", actual_person_name);
                }
                break;
            }
            case '2':{  // cette fonctionnalité est opérationnelle
                if ( strcmp(actual_person_name,"") !=0 ) {
                    int quit_2 = 0;
                    while (quit_2 != 1) {
                        printf("La personne enregistrée par défault est %s, voulez vous choisir une autre personne\n     1.oui\n     2.non\n",actual_person_name);
                        char *choix_2 = scanString("");
                        switch (choix_2[0]) {
                            case '1': {
                                actual_person_name = scanString("Seletionner le contact dont vous voulez voir les rendez-vous : \n");
                                break;
                            }
                            case '2': {
                                quit_2 = 1;
                                break;
                            }
                            default : {
                                printf("Votre choix n'est pas pris en compte, veuillez recommencer\n");

                            }
                        }
                    }
                }
                else{
                    actual_person_name = scanString("Entrer le nom du contact recherché :\n");
                }

                p_sk_cell_agenda cell  = Search_list_simple_agenda(*mylist_agenda , actual_person_name);

                if (cell == NULL){
                    printf("Le contact n'est pas présente dans l'agenda\n");
                }else{
                    p_agenda agenda = cell->agenda;
                    t_std_list_rdv * listrdv = agenda->rdv_list;
                    Display_list_rdv(listrdv);
                }
                break;
            }
            case '3':{  // cette fonctionnalité est opérationnelle même si le chainage ne s'est pas faite de manière complexe.
                actual_person_name = scanString("Entrer le nom du contact à ajouter (nom ): \n");
                p_sk_cell_agenda cell = Search_list_simple_agenda(*mylist_agenda, actual_person_name);
                if ( cell != NULL) { //si la personne est deja presente, ne va pas ajouter le contact
                    printf("Le contact existe deja, vous ne pouvez pas l'ajoutez\n");
                }
                else{ // ajout du contact
                    p_sk_cell_agenda cell_agenda = Create_New_cell_agenda (actual_person_name);
                    printf("cell created value : %s\n", cell_agenda->value);
                    Add_contact(*mylist_agenda, cell_agenda);
                    Display_list_simple_agenda(*mylist_agenda);
                }
                break;
            }
            case '4':{       //creer et ajouter un rdv => fonctionnalité non fonctionnelle.
                char *personne = scanString("Seletionner le proprietaire du rdv (nom prenom): ");
                p_sk_cell_agenda cell = Search_list_simple_agenda(*mylist_agenda, personne);
                if ( cell == NULL) {            //si la personne n'est pas dans l'agenda, va cree le contacte et l'jouter a la liste
                    cell = Create_New_cell_agenda (personne);
                    Add_contact(*mylist_agenda, cell);
                }
                p_agenda agenda = cell->agenda;
                add_rdv(agenda);
                break;
            }
            case '5':{ //supprimer un rdv
                char *personne = scanString("Seletionner le proprietaire du rdv (nom prenom): ");
                p_sk_cell_agenda cell = Search_list_simple_agenda(*mylist_agenda, personne);
                if (cell == NULL) { //si la personne n'est pas dans l'agenda, on ne peut pas supprimer de rdv
                    printf("Ce contact n'existe pas\n");
                    break;
                }
                p_agenda agenda = cell->agenda;
                if (agenda->rdv_list == NULL)
                    printf("Ce contact ne possède pas de rdv d'enregistre\n");
                delete_search_rdv(agenda);
                break;
            }
            case '6': {
                printf("Vous quittez l'application\n");
                quit = 1;
                break;
            }
            default:
                printf ("Votre choix n'est pas pris en compte, veuillez recommencer\n");
        }

    }
    free(actual_person_name);
    Delete_list_agenda(mylist_agenda);
    return 0;
}

p_sk_cell_agenda Search_list_simple_agenda(t_sk_list_agenda mylist ,char * name) {
    // recherche dans la liste uniquement depuis le premier niveau complexité o(n)
    p_sk_cell_agenda cell = mylist.head[0];
    while (cell != NULL) {
        if ( strcmp(cell->value , name) ==0){
            return cell;
        }
        cell = cell->values[0];
    }
    return NULL;
}


int is_Empty_list_agenda(t_sk_list_agenda mylist){
    int vide = 1;
    for (int i=0 ; i<= mylist.max_level ; i++){
        if (mylist.head[i] != NULL ){
            vide = 0;
            return vide;
        }
    }
    return vide;
}


p_sk_cell_agenda Search_list_level_part_agenda (int level, char *c, p_sk_cell_agenda cell_depart, t_sk_list_agenda mylist ) {
    // Ceci est la premiere version de notre fonction de recherche dichotomique, elle est recursive
    //printf(" Searching list level part (level %d) (val %d) (current cell_depart %d)\n", level , val, cell_depart->value);
    if ( cell_depart-> value == c){
        return cell_depart;
    }
    else if (cell_depart->value < c){  // si ma valeur se trouve dans le tableau de droite
        if ( level ==0){
            return NULL;
        }
        else{
            return Search_list_level_part_agenda( level-1, c, cell_depart->values[level-1], mylist);
        }
    }
    else if (cell_depart->value > c){ // si ma valeur se trouve dans le tableau de gauche
        p_sk_cell_agenda temp = cell_depart->values[level];
        while (temp != NULL){
            if (temp->value == c){
                return temp;
            }
            else{
                temp = temp->values[level];
            }
        }
        if ( level == 0){
            return NULL;
        }
        else {
            return Search_list_level_part_agenda(level-1 , c , mylist.head[level-1], mylist);

        }
    }
}

p_sk_cell_agenda Search_list_upper_level_agenda(t_sk_list_agenda mylist , char *c){
    // recherche dichotomique , à partir du plus haut niveau. o(n/2)
    if (is_Empty_list_agenda(mylist)){
        return NULL;
    }
    else{
        int level = mylist.max_level -1;
        p_sk_cell_agenda cell = mylist.head[level];
        return Search_list_level_part_agenda(level, c, cell, mylist);
    }
}




void Add_contact(t_sk_list_agenda list, p_sk_cell_agenda cell_new){  // ajout du contact au niveau zéro en tête de liste par défault
    p_sk_cell_agenda temp = list.head[0];
    list.head[0] = cell_new;
    cell_new->values[0] = temp;
    return;
}

void Display_contact(p_contact cont) {
    if (cont != NULL) {
        printf("%s %s\n", cont->nom, cont->prenom);
    } else {
        printf("Le contact n'a pas pu être affiché puisqu'il n'existe pas\n");
    }
    return;
}


t_sk_list_agenda* Create_empty_agenda_list(){
    t_sk_list_agenda* list_agenda = (t_sk_list_agenda *)malloc (sizeof(t_sk_list_agenda));
    list_agenda->max_level=4; //par default
    list_agenda->head = (t_sk_cell_agenda**)malloc(4*sizeof(t_sk_cell_agenda*)); //4 case adresse.
    return list_agenda;
}

void Filling_agenda_w_contacts(int ncontact, t_sk_list_agenda* list_agenda){

    FILE * fichier_nom = fopen("../noms.txt", "rt");
    FILE * fichier_prenom = fopen("../prenoms.txt", "rt");
    if ( fichier_nom==NULL || fichier_prenom==NULL){
        printf("erreur ouverture fichier\n");
    }else{
        char  ligne_nom [20] ="";
        char  ligne_prenom [20] ="";

        for (int i=0; i<ncontact ; i++){
            int pas = rand()%100+1; // le pas est determiner de facon aléatoire.
            while (pas < 0){
                fgets(ligne_nom, 20, fichier_nom);
                fgets(ligne_prenom, 20, fichier_prenom);
                pas -=1;
            }
            printf("%s %s contact num %d", ligne_nom, ligne_prenom, i+1); // ligne_prenom = "" et ligne_nom = "" tout le temps.

            //Inserer dans la liste une entrée d'agenda suivznt le format "nom_prenom" :
            //...
            // Cette partie n'a pas été codé en raison de l'impossibilité de lire le fichier
            //...
        }
        fclose(fichier_nom);
        fclose(fichier_prenom);
    }
    return;
}

void Filling_agenda_sans_fichier(int taille, t_sk_list_agenda* list_agenda){  // Cette fonction ne fonctionne apriori que sur certain ordinateur.
    char* t[8] = {"Flamel","Gallouin","Garnier","Gartner","Grandin","Gruss","Guetta", "Humbert"};
    t_sk_cell_agenda* new_cell;
    new_cell = Create_entry_agenda(4, t[0]); // level , nom
    for (int i=0; i<4; i++){
        list_agenda->head[i] = new_cell;  // lie la premiere cellule.
    }
    t_sk_cell_agenda * temp1 = new_cell;
    t_sk_cell_agenda * temp2 = temp1;
    t_sk_cell_agenda * temp3 = temp1;
    for (int i=1; i<taille ; i++){
        if (temp1->value[0] != t[i][0]){  // comparaison de la premiere lettre
            new_cell->values[0] = Create_entry_agenda(4,t[i]);
            new_cell = new_cell->values[0];
            temp1->values[3] = new_cell;
            temp2->values[2] = new_cell;
            temp3->values[1] = new_cell;
            temp1 = new_cell; temp2 = new_cell; temp3 = new_cell;
        }
        else{  // si la premiere lettre est la meme, temp1, ne change pas, la nouvelle cell aura 3 etage.
            if (temp2->value[1] != t[i][1]){ // comparaison de la deuxieme lettre
                new_cell->values[0] = Create_entry_agenda(3,t[i]);
                new_cell = new_cell->values[0];
                temp3->values[1] = new_cell;
                temp2->values[2] = new_cell;
                temp2 = new_cell; temp3 = new_cell;
            }
            else{  // si la deuxieme lettre est la meme, temp2 ne changera pas, la nouvelle cell aura 2 etage.
                if (temp3->value[2] != t[i][2]){ // comparaison de la deuxieme lettre
                    new_cell->values[0] = Create_entry_agenda(2,t[i]);
                    new_cell = new_cell->values[0];
                    temp3->values[1] = new_cell;
                    temp3 = new_cell;
                }
                else{ // si la troisieme lettre est la meme, temp3 ne changera pas, la nouvelle cell aura 1 seul etage.
                    new_cell->values[0] = Create_entry_agenda(1,t[i]);
                    new_cell = new_cell->values[0];
                }

            }
        }

    }
    return;
}

void Insert_entry_agenda_in_list (p_sk_cell_agenda cell, t_sk_list_agenda* mylist){ // cette fonction n'a pas pu être codée jusqu'au bout
    char* name = cell->value;
    p_sk_cell_agenda temp = mylist->head[ mylist->max_level -1];
    if (temp == NULL){
        printf("la liste est vide\n");
        for (int i=0; i<mylist->max_level ; i++){
            mylist->head[i] = cell;
        }
        return;
    }
    p_sk_cell_agenda prev = temp;
    while (temp != NULL){

        if ( name[0] < temp->value[0]  ){ // la cellule doit être chainée avant.
            printf("a faire");
        }else if ( name[0] == temp->value[0] ){
            p_sk_cell_agenda temp2 = temp->values[mylist->max_level -1 ];
            p_sk_cell_agenda prev2 = temp2;
            while (temp2 != NULL){

                if ( name[1] < temp2->value[1]  ){ // la cellule doit être chainée avant.
                    //...
                }else if ( name[1] == temp2->value[1] ){
                    p_sk_cell_agenda temp3 = temp->values[mylist->max_level -1 ];
                    p_sk_cell_agenda prev3= temp3;


                }

        }
        prev = temp;
        temp = temp->values[mylist->max_level];

    }
    // ajout fin de liste :
    for (int i=0; i<mylist->max_level ; i++){
        prev->values[i] = cell;
    }
    return;
}}



void Display_list_simple_agenda (t_sk_list_agenda mylist){
    for (int i= 0 ; i < mylist.max_level; i++){
        Display_level_list_agenda(mylist , i);
    }
    return;
}

void Display_level_list_agenda (t_sk_list_agenda mylist, int level){
    // ATTENTION ; ON RAPPELLE QUE LES NIVEAUX COMMENCENT A ZERO !!!
    printf("[ list head_%d @ ]-->", level);
    t_sk_cell_agenda *temp = (mylist.head[level]);
    while( temp != NULL){
        printf("[%s | @ ]-->", temp->value);
        temp = temp->values[level];
    }
    printf("NULL\n");
    return;
}

void Delete_list_agenda(t_sk_list_agenda* mylist_a){
    t_sk_cell_agenda* temp =mylist_a->head[0];
    t_sk_cell_agenda *prev = temp;
    while ( temp!=NULL){
        temp = prev->values[0];
        Delete_sk_cell_agenda(prev);
        prev = temp;
    }
    free(mylist_a);
    return;
}