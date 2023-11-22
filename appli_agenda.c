//
// Created by Benjamin Ducasse on 19/11/2023.
//

#include "appli_agenda.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int menu_agenda(){
    printf("----BIENVENUE DANS LE MENU DE GESTION D'AGENDA----\n");
    printf("Creation d'un agenda à 3 entrée\n");
    t_sk_list_agenda * mylist_agenda = Create_empty_agenda();
    Filling_agenda_w_contacts(3, mylist_agenda);
    printf("    1. Rechercher un contact\n"
           "    2. Afficher les rendez-vous d’un contact ;\n"
           "    3. Créer un contact (avec insertion dans la liste) ;\n"
           "    4. Créer un rendez-vous pour un contact (avec insertion dans la liste si le contact n’existe pas) ;\n"
           "    5. Supprimer un rendez-vous ;\n"
           "    6. Sauvegarder le fichier de tous les rendez-vous ;\n"
           "    7. Charger un fichier de rendez-vous ;\n"
           "    8. Fournir les temps de calcul pour une insertion de nouveau contact : voir point 2) ci –dessous.\n"
           "    9.Quitter.\n");
    int c=0,quit=0;
    while (quit != 1){
        printf("Votre choix:\n");
        c = getchar(); //?
        switch (c) {
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
            default:
                quit =1;
                printf ("Votre choix n'est pas pris en compte, veuillez recommencer\n");
        }

    }
    return 0;
}

p_contact Searching_contact_in_list( t_sk_list_agenda* myagenda_list){
    // a completer, ne pas hesitez à changer le prototype.
    return NULL;
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