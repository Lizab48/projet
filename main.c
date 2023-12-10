#include <stdio.h>
#include "list.h"
#include "agenda_list.h"
#include <stdlib.h>
#include "timer.h"

void test_partie_1(){
    printf("Ceci est le test 1 : \n");
    t_sk_list mylist = Create_empty_list(5);
    printf(" mylist est créer avec 5 niveaux \n");
    p_sk_cell cell = Create_cell_sk(18, 1); // 18: value , 1: level_max
    Insert_in_list_head ( &mylist , cell);
    printf(" la cellule de valeur 18 à 2 niveaux est inserée\n");

    printf(" AFFICHAGE NIVEAU 1 DE LA LISTE:\n");
    Display_level_list(mylist, 1);

    printf(" AFFICHAGE ENSEMBLE DE LA LISTE:\n");
    Display_list_simple (mylist);

    p_sk_cell cell2 = Create_cell_sk(13 , 0);
    Insert_in_list_croissant(&mylist , cell2);
    p_sk_cell cell3 = Create_cell_sk(20 , 3);
    Insert_in_list_croissant(&mylist , cell3);
    p_sk_cell cell4 = Create_cell_sk(14 , 1);
    Insert_in_list_croissant(&mylist , cell4);
    p_sk_cell cell5 = Create_cell_sk(12 , 1);
    Insert_in_list_croissant(&mylist , cell5);
    p_sk_cell cell6 = Create_cell_sk(19 , 1);
    Insert_in_list_croissant(&mylist , cell6);
    // VERIFICATION :
    printf(" AFFICHAGE ENSEMBLE DE LA LISTE:\n");
    Display_list_simple (mylist);
    Delete_sk_list(&mylist);
    return;
}

void test_partie_2(){

    printf("Création d'une liste à 3 niveaux ( 15 éléments )\n");
    t_sk_list mylist = Create_level_list(3);
    printf("\nAFFICHAGE LIST SIMPLE: \n");
    Display_list_simple(mylist);
    printf("\nAFFICHAGE LIST NIVEAUX : \n");
    Display_level_list(mylist, 2);
    printf("\nOn a chercher la valeur 2 dans la liste, la fonction renvoie : %d\n",Search_list_simple(mylist ,2) );
    printf("On a chercher la valeur 2 de maière dichotomique dans la liste, la fonction renvoie : %d\n",Search_list_upper_level(mylist , 2) );
    printf ("Comparaison de compléxité : \n                             Recherche simple                 Recherche dichotomique\n");
    int recherche=0;

    // POUR 100
    startTimer();
    for (int i=0; i<100 ; i++){
        recherche = rand() % 7 + 1;
        Search_list_simple(mylist , recherche);
    }
    stopTimer();
    char* time_simple = getTimeAsString();
    startTimer();
    for (int i=0; i<100 ; i++){
        recherche = rand() % 7 + 1;
        Search_list_upper_level(mylist,recherche);
    }
    stopTimer();
    char* time_dico = getTimeAsString();
    printf("Pour 100 recherches :        %s                     %s\n", time_simple , time_dico);


    // Pour 1 000
    startTimer();
    for (int i=0; i<1000 ; i++){
        recherche = rand() % 7 + 1;
        Search_list_simple(mylist , recherche);
    }
    stopTimer();
    time_simple = getTimeAsString();
    startTimer();
    for (int i=0; i<1000 ; i++){
        recherche = rand() % 7 + 1;
        Search_list_upper_level(mylist,recherche);
    }
    stopTimer();
    time_dico = getTimeAsString();
    printf("Pour 1 000 recherches :        %s                     %s\n", time_simple , time_dico);


    //Pour 10 000
    startTimer();
    for (int i=0; i<10000 ; i++){
        recherche = rand() % 7 + 1;
        Search_list_simple(mylist , recherche);
    }
    stopTimer();
    time_simple = getTimeAsString();
    startTimer();
    for (int i=0; i<10000 ; i++){
        recherche = rand() % 7 + 1;
        Search_list_upper_level(mylist,recherche);
    }
    stopTimer();
    time_dico = getTimeAsString();
    printf("Pour 10 000 recherches :        %s                     %s\n", time_simple , time_dico);

    //POUR 100 000
    startTimer();
    for (int i=0; i<100000 ; i++){
        recherche = rand() % 7 + 1;
        Search_list_simple(mylist , recherche);
    }
    stopTimer();
    time_simple = getTimeAsString();
    startTimer();
    for (int i=0; i<100000 ; i++){
        recherche = rand() % 7 + 1;
        Search_list_upper_level(mylist,recherche);
    }
    stopTimer();
    time_dico = getTimeAsString();
    printf("Pour 100 000 recherches :        %s                     %s\n", time_simple , time_dico);
    return;
}

void test_partie3(){
    printf("Test de scanString()\n");
    char* mystr = scanString("Selectionnez votre nom sous la forme 'nom prenom' : ");
    int i =0;
    char c = mystr[i];
    printf("Voici ma chaine  : %s\n", mystr);  //-> fonctionne
    menu_agenda();
    printf("fin test part3.");
    return;
}

void test_complexité_graphe(){
    for (int level=1; level<=3; level++){
        FILE *log_file = fopen("../log.txt","w");
        char format[] = "%d\t%s\t%s\n" ;
        t_sk_list mylist = Create_level_list(level);
        int recherche;
        startTimer();
        for (int i=0; i<10000 ; i++){
            recherche = rand() % 7 + 1;
            Search_list_simple(mylist , recherche);
        }
        stopTimer();
        char *time_simple = getTimeAsString();
        startTimer();
        for (int i=0; i<10000 ; i++){
            recherche = rand() % 7 + 1;
            Search_list_upper_level(mylist,recherche);
        }
        stopTimer();
        char* time_dico = getTimeAsString();
        fprintf(log_file,format,level,time_simple, time_dico);
        fclose(log_file);
    }
    return;
}

int main() {
    test_partie_1();
    //test_partie_2();
    //test_complexité_graphe();
    //test_partie3();
    return 0;
}