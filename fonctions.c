#include "fonctions.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Compte le nombre d'occurence de chaque caractère ASCII dans un fichier 
 * et le place dans le tableau passer en paramètre
 * Renvoie le nombre de type de caractère différents dans le fichier (inférieur à 256)
 */
size_t probas(char* chemin, double table[]){
	// Ouverture du fichier en écriture
	FILE *file = fopen(chemin, "r");
	// Vérification de l'ouverture du fichier
	if(file == NULL){
		printf("Donnez un fichier valide\n");
		return 2;
	}
	int c; // initialisation du caractère de lecture
	double n =0;
    int T[256] = {0};
	while((c = fgetc(file)) != EOF){
        printf("%c  %i\n",c,c );
        if(c>0){
            T[c]++;
            n++;
        }
	}
	// Fermeture du fichier
	fclose(file);
    // Calcule des probas et des car différents
    size_t nbCar = 0;
    for(int i = 0; i<256; i++){
        if(T[i] > 0){
            nbCar++;
            table[i] = (T[i]/n) *100;// calcule de la probabilité d'apparition
        }
    }
    // On renvoie le nombre de caractères différents dans le fichier
	return nbCar;
}

/*  Affiche toutes les valeurs supérieur à 0 dans un struct tab */
void affiche(tab T[], size_t taille){
    for(size_t i = 0; i<taille; i++){
        if(T[i].probas > 0){
            printf("indice %li : caractère %i avec une présence de %f %% \n", i, T[i].car[0], T[i].probas);
        }
    }
    return;
}
 
void remplirTab(double full[], size_t size_F,tab empty[]){
    size_t j=0;
    for(size_t i=0; i<size_F; i++){
        if(full[i] > 0){
            empty[j].probas = full[i];
            // Mise en place chaine de caractère
            char* mot = malloc(sizeof(char) *2);
            mot[0] = (char) i;
            mot[1] = '\0';
            
            empty[j].car = mot;
            j++;
        }
    }
    return;
}

size_t* deuxMinimum(tab T[], size_t s){

    size_t i_min1=0, i_min2=0; // Indices des minimums
    if(s >= 2){
        double min1 = T[i_min1].probas, min2 = T[i_min2].probas; // valeurs des minimums
        for(size_t i = 0; i<s; i++){
            if(T[i].probas < min1){ // Si T[i] inférieur à min1, min1 prend sa valeur
                i_min1 = i;
                min1 = T[i_min1].probas;
            }
            if(T[i].probas < min2 && T[i].probas >= min1 && i != i_min1){ // Si T[i] inférieur à min2 et supérieur ou égale à min1 alors c'est le second min
                i_min2 = i;
                min2 = T[i_min2].probas;
            }

        }
        // Echange des valeurs
        tab temp = T[s-2];
        T[s-2] = T[i_min2];
        T[i_min2] = temp; 

        temp = T[s-1];
        T[s-1] = T[i_min1];
        T[i_min1] = temp; 
    }
    size_t* res =NULL;
    res = malloc(sizeof(size_t)*2);
    res[0] = s-1;
    res[1] = s-2;
    return res;
}

Arbre construction(tab T[], size_t s){
    size_t i = s, j=0;
    Arbre arbres[s-1]; // Tableau des sous arbres
    size_t* mins;
    while(i>1){
        mins = deuxMinimum(T, i);
        size_t a = mins[1], b=mins[0];// a = min1 b = min2 où min1 < min2
        //printf("\n\n Les deux mins :  min1 = %f (indice %li) , min2 = %f (indice %li) \n", T[a].probas,a,T[b].probas,b );
        //affiche(T, i);
        double p_1 = T[a].probas, p_2 = T[b].probas; // Probabilité du parent
        char* mot = malloc(sizeof(T[a].car) + sizeof(T[b].car));// Chaine du parent
        strcat(mot, T[b].car); // Concaténation
        strcat(mot, T[a].car);
        // Création du triplet
        Arbre q = createBinaryTree(p_1+p_2, mot, createBinaryTree(p_1, T[a].car, NULL ,NULL), createBinaryTree(p_2, T[b].car, NULL ,NULL));
        // Enregistrement du triplet dans le tableau
        arbres[j] = q;
        // On change la valeur de l'avant dernier element du tableau (concaténation des probas et string)
        T[a].probas = p_1+p_2; 
        T[a].car = mot;
        // On réduit i pour appeler la fonction "deuxMinimum" avec un indice en moins
        i--;
        j++;
    }
    free(mins);// libération du tableau mins
    // Maintenant on relie les sous arbres entre eux en comparant les chaines de caractères
    // Pour les sous arbres déjà existant on va libérer l'espace sinon ça explose
    // Pour chaque arbre on parcours le tableau voir si il y a ses fils dedans
    for(i=0; i< s-1; i++){
        for(j=0; j<s-1; j++){
            // Si l'arbre existe (si il n'est pas déjà fils de quelqu'un)
            if(arbres[i] != NULL && arbres[j] != NULL && j != i){
                // Si ce n'est pas une feuille
                if(arbres[i]->fils_droit != NULL && arbres[i]->fils_gauche != NULL ){
                    // Si la chaine du fils gauche = celle de l'autre arbre
                    if(strcmp(arbres[i]->fils_gauche->car, arbres[j]->car) == 0){
                       // On libère la mémoire du fils gauche de l'arbre courant 
                       free(arbres[i]->fils_gauche);
                       // On attribue l'autre arbre comme fils gauche
                       arbres[i]->fils_gauche = arbres[j]; 
                        //printf("Libération du fils gauche de l'arbre %s %f (fils gauche : %s %f ||| autre arbre : %s %f )\n\n", arbres[i]->car,arbres[i]->val,arbres[i]->fils_gauche->car,arbres[i]->fils_gauche->val,arbres[j]->car,arbres[j]->val);
                    }
                    // Si la chaine du fils droit = celle de l'autre arbre
                    else if(strcmp(arbres[i]->fils_droit->car, arbres[j]->car)== 0){
                       // On libère la mémoire du fils droit de l'arbre courant
                       free(arbres[i]->fils_droit);
                       // On attribue l'autre arbre comme fils droit
                       arbres[i]->fils_droit = arbres[j]; 
                    }
                }
            }
        }
    }
    // Onretourne le dernier arbre créer dans le tableau
    return arbres[s-2];
}

int archive(char* chemin, Lettre* lettres, size_t size){
    // ouverture des fichiers ecriture et lecture
    FILE *read = fopen(chemin, "r");
    FILE *write = fopen("archive.txt", "w");
    if(read == NULL || write == NULL){
		printf("fonctionen galère !!\n");
		return -1;
	}
    int c; // initialisation du caractère de lecture
	int i;
    //Pour chaque caractère dans le fichier initiale
	while((c = fgetc(read)) != EOF){
        i = 0;
        if(c > 0){
            // On cherche dans le tableau de code
            while(i < size && lettres[i]->car != c){
                i++;
            }
            // On ecrit le code dans le fichier
            for(int g = 0; g < strlen(lettres[i]->code); g++){
                char* un = &lettres[i]->code[g];
                fwrite(un, 1, sizeof(char), write);
            }
        }
	}
    // On ferme les fichiers
    fclose(read);
    fclose(write);
    return 0;
}