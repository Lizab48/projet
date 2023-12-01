#include "complementaire.h"
#include <stdlib.h>

t_tab* level(int n){
    // 2 -> [0,1,0] sous forme d'un tableau dynamique
    // 3 -> [0,1,0,2,0,1,0] sous forme d'un tableau dynamique
    // Permet de generer l'ordre des niveaux des cellules.
    if (n==0){
        return NULL;
    }
    else if ( n==1){
        t_tab* tab_0 = (t_tab*) malloc(sizeof(t_tab));
        tab_0->value = (int*)malloc(sizeof(int));
        tab_0->longueur = 1;
        tab_0->value[0] = 0;       // a tester, les tableaux j'aime pas trop alors...
        return tab_0;
    }
    else{
        t_tab* mytab = (t_tab*) malloc(sizeof(t_tab));
        t_tab* tab_left = level(n-1);   //optimisable ??
        t_tab* tab_right = level(n-1);

        mytab->longueur = tab_left->longueur + tab_right->longueur + 1; // normalement pareil que mytab->longueur = pow(2,n)-1

        mytab->value = (int*)malloc(mytab->longueur*sizeof(int));
        int i;
        for ( i=0 ; i < tab_left->longueur ; i++){
            mytab->value[i] = tab_left->value[i];
            mytab->value[i+n+1] = tab_right->value[i];
        }
        mytab->value[i] = n-1;
        free(tab_left->value);
        free(tab_left);
        free(tab_right->value);
        free(tab_right);
        return mytab;
    }
}
