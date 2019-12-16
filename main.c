#include "fonctions.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main (int argc, char** argv){
    // tableau de caractère ASCII
    double ASCII[256] = {0};
    if(argc < 2){
        perror("Veuillez rentrer un ou plusieurs noms de fichiers à traiter en paramètre \n");
        return 1;
    }
    // Nombre de caractères différents
    size_t nbcar = probas(argv[1], ASCII);
    if(nbcar < 2){
        perror("Le fichier contient moins de 2 caractères, compression impossible\n");
        return 2;
    }
    // Tabeau de probabilité pour chaque caractère
    tab PROBAS[nbcar];
    // On rempli le tableau PROBAS
    remplirTab(ASCII, 256, PROBAS);
    // On affiche juste pour etre sur
    affiche(PROBAS, nbcar);
    // mise en place de l'arbre
    Arbre a = construction(PROBAS, nbcar);
    //afficheArbre(a);
    Lettre tableauLettre[nbcar];
    size_t* test = malloc(sizeof(size_t));
    *test = 0;
    char* vide = malloc(sizeof(char)*2);
    vide = ""; 
    // Mise en place des codes
    codeFeuille(a, vide, test, tableauLettre);
    
    // Création de l'archive
    if(archive(argv[1], tableauLettre, nbcar) == 0){
        printf("archive crée avec succés! \n");
    }else{
        printf("erreur dans la procédure \n");
        return 3;
    }

    return 0;
}