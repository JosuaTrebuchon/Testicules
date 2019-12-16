#include "arbre_binaire.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*  Création d'un arbre binaire, initialisé avec la valeur i
    et l'arbre Droit comme fils droit et Gauche comme fils gauche */
Arbre createBinaryTree(double i,char* c, Arbre Droit, Arbre Gauche){
    Arbre a = malloc(sizeof(arbre_bin));
    a->val = i;
    a->car = c;
    a->fils_droit = Droit;
    a->fils_gauche = Gauche;
    return a;
}

void afficheArbre(Arbre A){
    if(A != NULL){
        printf("Arbre : val = %f ; car = %s \n", A->val, A->car);
        afficheArbre(A->fils_gauche);
        afficheArbre(A->fils_droit);
    }
}


void codeFeuille(Arbre A, char* code, size_t* i, Lettre* tab){
    // Si l'arbre est non null et on n'est pas à la fin du tableau
    if(A!=NULL && *i<256){
        // Si l'arbre est une feuille
        if(A->fils_gauche == NULL && A->fils_droit == NULL){
            // on enregistre le caractère et son code
            Lettre l1 = malloc(sizeof(lettre));
            l1->code = code;
            l1->car = A->car[0];
            // On la place dans le tableau
            tab[*i] = l1;
            // incrémentation dans le tableau
            *i += 1;
        }else{
            // Sinon on crée le code du noeud fils gauche
            char* code_gauche = malloc(sizeof(strlen(code)) + sizeof(char));
            strcat(code_gauche, code);
            strcat(code_gauche, "1"); 
            // Et on fait un appel récursif sur le fils gauche
            codeFeuille(A->fils_gauche, code_gauche, i, tab);
            // On crée le code du noeud fils droit
            char* code_droit = malloc(sizeof(strlen(code)) + sizeof(char));
            strcat(code_droit, code);
            strcat(code_droit, "0");
            // On fait un appel récursif sur le fils droit
            codeFeuille(A->fils_droit, code_droit, i, tab);
        }
    }
    return;
}