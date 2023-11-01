#include <stdio.h>
#include "list.h"

void test_partie_1(){
    printf("Ceci est le test 1 : \n");
    testlist();
    t_sk_list mylist = Create_empty_list(5);
    printf(" mylist est créer de longueur 5! \n");
    p_sk_cell cell = Create_cell_sk(18, 1);    // revoir tout les types pointeurs ou nom des fonctions , est ce que c'est optimiser ?
    Insert_in_list_head ( &mylist , cell);
    printf(" la cellule de valeur 18 à 2 niveaux est inserée\n");
    printf(" AFFICHAGE NIVEAU 1 DE LA LISTE:\n");
    Display_level_list(mylist, 1);
    printf(" AFFICHAGE ENSEMBLE DE LA LISTE:\n");
    Display_list_simple (mylist);
    //En option : afficher tous les niveaux de la liste, en alignant les cellules
    p_sk_cell cell2 = Create_cell_sk(13 , 0);
    Insert_in_list_croissant(&mylist , cell2);
    // VERIFICATION : 
    printf(" AFFICHAGE ENSEMBLE DE LA LISTE:\n");
    Display_list_simple (mylist);

    /* Hehe ?
• Insérer une cellule à niveau dans la liste, au bon endroit, de manière à ce que la
liste reste triée par ordre croissant
Pour cette dernière fonctionnalité, il est possible de faire une ‘simple’ insertion à
chaque niveau en partant du début de la liste, mais il est possible d’être plus
efficace, à vous de trouver comment. */
    return;
}

int main() {
    printf("Hello, World!\n");
    test_partie_1();
    return 0;
}
