//
// Created by Benjamin Ducasse on 19/11/2023.
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
                printf("Ce choix n'est pas disponible pour le moment\n");
                mylist_agenda = Create_empty_agenda();
                Filling_agenda_w_contacts(10 , mylist_agenda, "../noms.txt");
                break;
            }
            case 2 :{
                printf("Création d'un agenda à partir d'un tableau de Nom\n");
                mylist_agenda = Create_empty_agenda();
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
    //Filling_agenda_w_contacts(3, mylist_agenda);
    printf("Voici votre agenda : \n");
    Display_list_simple_agenda(*mylist_agenda);
    printf("\n    1. Rechercher un contact\n"
           "    2. Afficher les rendez-vous d’un contact ;\n"
           "    3. Créer un contact (avec insertion dans la liste) ;\n"
           "    4. Créer un rendez-vous pour un contact (avec insertion dans la liste si le contact n’existe pas) ;\n"
           "    5. Supprimer un rendez-vous ;\n"
           "    6. Sauvegarder le fichier de tous les rendez-vous ;\n"
           "    7. Charger un fichier de rendez-vous ;\n"
           "    8. Fournir les temps de calcul pour une insertion de nouveau contact : voir point 2) ci –dessous.\n"
           "    9.Quitter.\n");
    // a ne pas enelver sinon il n'est pas content...
    char * actual_person_name ="" ;
    while (quit != 1){
        //printf("Votre choix:\n");
        char *choix = scanString("Votre choix\n");

        //scanf("%d",&choix);
        switch (choix[0]) {
            case '1':{
                //Rechercher un contact -> a tester
                actual_person_name = scanString("Entrer le nom du contact recherché :\n");
                //p_sk_cell_agenda cell = Search_list_simple_agenda(*mylist_agenda , actual_person_name);
                p_sk_cell_agenda cell = Search_list_upper_level_agenda(*mylist_agenda , actual_person_name);

                    if (cell == NULL){
                    printf("La personne que vous recherchez n'existe pas (%s)\n",actual_person_name);
                    actual_person_name =""; // la personne n'existe plus
                }else{
                    printf("Le contact %s se trouve dans la liste des agandas\n", actual_person_name);
                }
                break;
            }
            case '2':{
                //p_contact mycontact = Searching_contact_in_list( mylist_agenda );  // a tester, a completer.
                //Display_rdv(mycontact);
                if ( strcmp(actual_person_name,"") !=0 ) { // ok
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
                                quit_2 = 1; // je ne comprends pas le pbmdbjfdbnklqe
                                break;
                            }
                            default : {
                                printf("Votre choix n'est pas pris en compte, veuillez recommencer\n");

                            }
                        }
                    }
                }else{ //pbm ici inexpliqué.
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
            case '3':{
                actual_person_name = scanString("Entrer le nom du contact à ajouter (nom ): \n");
                p_sk_cell_agenda cell = Search_list_simple_agenda(*mylist_agenda, actual_person_name);
                if ( cell != NULL) { //si la personne est deja presente, ne va pas ajouter le contact
                    printf("Le contact existe deja, vous ne pouvez pas l'ajoutez\n");
                }
                else{ // ajout du contact
                    p_sk_cell_agenda cell_agenda = Create_New_cell_agenda (actual_person_name);
                    printf("test");
                    printf("cell created value : %s\n", cell_agenda->value);
                    Add_contact(*mylist_agenda, cell_agenda);
                    Display_list_simple_agenda(*mylist_agenda);
                }
                break;
            }
            case '4':{ //cree et ajouter un rdv
                char *personne = scanString("Seletionner le proprietaire du rdv (nom prenom): ");
                p_sk_cell_agenda cell = Search_list_simple_agenda(*mylist_agenda, personne);
                if ( cell == NULL) { //si la personne n'est pas dans l'agenda, va cree le contacte et l'jouter a la liste
                    p_sk_cell_agenda cell_agenda = Create_New_cell_agenda (personne);
                    Add_contact(*mylist_agenda, cell_agenda);
                }
                p_agenda agenda = cell->agenda; //fait les demande necessaire pour cree un rdv et ajoute le rdv
                add_rdv(agenda);
                break;
            }
            case '5':{//supprimer un rdv
                char *personne = scanString("Seletionner le proprietaire du rdv (nom prenom): ");
                p_sk_cell_agenda cell = Search_list_simple_agenda(*mylist_agenda, personne);
                if (cell == NULL) { //si la personne n'est pas dans l'agenda, on ne peut pas supprimer de rdv
                    printf("Ce contact n'existe pas\n");
                    break;
                }
                p_agenda agenda = cell->agenda;
                if (agenda->rdv_list == NULL)
                    printf("Ce contact ne possède pas de rdv d'enregistre\n");
                delete_search_rdv(&agenda);
                break;
            }
            case '9': {
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

p_sk_cell_agenda Search_list_simple_agenda(t_sk_list_agenda mylist ,char * name) { //a tester
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


int is_Empty_list_agenda(t_sk_list_agenda mylist){     // a tester
    int vide = 1;
    for (int i=0 ; i<= mylist.max_level ; i++){
        if (mylist.head[i] != NULL ){
            vide = 0;
            return vide;
        }
    }
    return vide;
}


p_sk_cell_agenda Search_list_level_part_agenda (int level, char *c, p_sk_cell_agenda cell_depart, t_sk_list_agenda mylist ) { // a tester

    //printf(" Searching list level part (level %d) (val %d) (current cell_depart %d)\n", level , val, cell_depart->value);
    if ( cell_depart-> value == c){
        return cell_depart;
    }
    else if (cell_depart->value < c){  // si ma val se trouve dans le tableau de droite
        if ( level ==0){
            return NULL;
        }
        else{ // c'est pas bon tu oublie ma cellule 0.
            return Search_list_level_part_agenda( level-1, c, cell_depart->values[level-1], mylist);
        }
    }
    else if (cell_depart->value > c){ // si ma val se trouve dans le tableau de gauche
        printf("fzepfgzeg\n");
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
p_sk_cell_agenda Search_list_upper_level_agenda(t_sk_list_agenda mylist , char *c){ // a tester
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




void Add_contact(t_sk_list_agenda list, p_sk_cell_agenda cell){
    printf("pas encore fait, ajout de la cell d'un contacte dans la liste");

}



p_contact Searching_contact_in_list( t_sk_list_agenda* myagenda_list){ //avec autocompletion auto.
    // a completer, ne pas hesitez à changer le prototype.

    return NULL;
}


p_contact Searching_contact_from_str(char* mot){
    p_contact mycontact;
    for (int i=0; i< (int)strlen(mot ); i++){
        //gkd
    }
    return mycontact;
}

void Display_contact(p_contact cont) {
    if (cont != NULL) {
        printf("%s %s\n", cont->nom, cont->prenom);
    } else {
        printf("Le contact n'a pas pu être affiché puisqu'il n'existe pas\n");
    }
    return;
}

void Display_list_rdv(t_std_list_rdv* list_rdv){
    if (list_rdv == NULL){
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


t_sk_list_agenda* Create_empty_agenda(){
    t_sk_list_agenda* list_agenda = (t_sk_list_agenda *)malloc (sizeof(t_sk_list_agenda));
    list_agenda->max_level=4; //par default
    list_agenda->head = (t_sk_cell_agenda**)malloc(4*sizeof(t_sk_cell_agenda*)); //4 case adresse.
    return list_agenda;
}

void Filling_agenda_w_contacts(int ncontact, t_sk_list_agenda* list_agenda, char* fichier_name){

    FILE * fichier = fopen(fichier_name, "r");
    if ( fichier==NULL){
        printf("erreur ouverture fichier\n");
    }
    else{
        char * ligne =NULL;
        while (fscanf(fichier, "%[^\n] ", ligne) != EOF) {
            printf("> %s\n", ligne);
        }

        //fgets( ligne,20, fichier );  // stocke dans ligne la ligne (de taille max 20 characteres) dans le fichier.// lecture ligne pas ligne.
        fclose(fichier);
    }
}

void Filling_agenda_sans_fichier(int taille, t_sk_list_agenda* list_agenda){
    char* t[8] = {"Flamel","Gallouin","Garnier","Gartner","Grandin","Gruss","Guetta", "Humbert"};
    t_sk_cell_agenda* new_cell;
    new_cell = Create_entry_agenda(4, t[0]);
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

void Display_list_simple_agenda (t_sk_list_agenda mylist){
    for (int i= 0 ; i < mylist.max_level; i++){
        Display_level_list_agenda(mylist , i);
    }
    return;
}

void Display_level_list_agenda (t_sk_list_agenda mylist, int level){
    // ATTENTION ; ON RAPPELLE QUE LES NIVEAU COMMENCE A ZERO !!!
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