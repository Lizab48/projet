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
    while (quit != 1){
        printf("Votre choix:\n");
        scanf("%d",&choix);
        switch (choix) {
            case 1:{
                //Rechercher un contact -> a tester
                int i=0;
                p_contact mycontact = Searching_contact_in_list( mylist_agenda ); // fonction a completer
                Display_contact(mycontact); //-> a tester
                break;
            }
            case 2:{
                p_contact mycontact = Searching_contact_in_list( mylist_agenda );  // a tester, a completer.
                Display_rdv(mycontact);
                break;
            }
                /*case 3:{
                    p_contact mycontact = Searching_contact();
                    t_sk_list_agenda myagenda = Create_empty_agenda();
                    Create_Add_contact(myagenda, mycontact);
                    break;
                }*/
            case 9: {
                printf("Vous quittez l'application\n");
                quit = 1;
                break;
            }
            default:
                printf ("Votre choix n'est pas pris en compte, veuillez recommencer\n");
        }

    }
    Delet_list_agenda(mylist_agenda);
    return 0;
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

void Display_contact(p_contact cont){
    if (cont != NULL){
        printf("%s %s\n", cont->nom, cont->prenom);
    }
    else{
        printf("Le contact n'a pas pu être affiché puisqu'il n'existe pas\n");
    }
    return;
}

void Display_rdv(p_contact cont){
    if (cont != NULL){
        // a completer .
        printf(" Le contact existe, mais la fonction qui affiche ses rendez vous n'est pas defini\n");
    }
    else{
        printf("Les rendez vous n'ont pas pu être affiché puisqu'il n'existe pas\n");
    }
    return;
}


t_sk_list_agenda* Create_empty_agenda(){
    t_sk_list_agenda* list_agenda = (t_sk_list_agenda *)malloc (sizeof(t_sk_list_agenda));
    list_agenda->max_level=4; //par default
    list_agenda->head = (t_sk_cell_agenda**)malloc(4*sizeof(t_sk_cell_agenda*)); //4 case adresse.
    return list_agenda;
}

void Filling_agenda_w_contacts(int ncontact, t_sk_list_agenda* list_agenda){

    FILE * fichier = fopen("/CLionProjects/noms.txt", "r");
    if ( fichier==NULL){
        printf("erreur ouverture fichier\n");
    }
    else{
        int pas = rand() % 219; //seul pbm, les noms apres 218 000 ne seront jamais choisi.
        char* ligne;
        int i=0; // mon iterateur pour avoir le pas.
        int n=0; // mon iterateur pour avoir le nombre de contact dans ma liste d'agenda
        t_sk_cell_agenda * temp = list_agenda->head[0];

        while (fgets(ligne, 20, fichier) != NULL && n< ncontact){ // On lit le fichier ligne pas ligne tant qu'on ne reçoit pas d'erreur (NULL)
            if (i == pas){
                printf("Nom selecioné : %s\n", ligne);
                i=0;
                pas = rand() % 219;
                //ajoute un contact dans l'agenda du nom suivant.
                t_sk_cell_agenda * myentry = Create_entry_agenda(0,ligne);  // pour l'instant la chaine est simplement chainée au premier niveau.
                temp->values[0]= myentry;
                temp = myentry;
                n++;
            }
            else{
                i++; // pas sur de l'endroit ou j'ai mis l'iteration.
            }
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

void Delet_list_agenda(t_sk_list_agenda* mylist_a){
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