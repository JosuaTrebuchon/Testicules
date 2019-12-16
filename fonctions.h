#include <stdlib.h>
#include "arbre_binaire.h"
/** \struct tab structure pour chaque chaine de caractère, sa probabilité*/
typedef struct tab{
    double probas; // probas d'apparition
    char* car;       // code du caractère
} tab;

/** Compte le nombre d'occurence de chaque caractère ASCII dans un fichier 
 * et le place dans le tableau passer en paramètre
 * Renvoie le nombre de type de caractère différents dans le fichier (inférieur à 256)
 *  \param chemin Nom du fichier
 *  \param table[] Probas de chaque caractère ASCII (les 256)
 *  \return Nombre de caractères différents dans le fichier  
 */
size_t probas(char* chemin, double table[]);

/** Affiche toutes les valeurs supérieur à 0 dans un struct tab
 * \param tableau[] tableau avec toute les probabilités
 * \param taille Taille du tableau
 */
void affiche(tab tableau[], size_t taille);

/** Rempli le tableau passer e 3eme paramètre avec les valeurs du tableau 
 * passer en premier pramètre. 
 * Problème : On ne connait pas la taille du tableau vide 
 * \param full[] Tableau des acarctère ASCII avec les probabilités
 * \param size_P Taile de full
 * \param empty[] tableau vide
 */
void remplirTab(double full[], size_t size_P, tab empty[]);

/** Recherche les deux minimums dans un tableau de taille donnée
 *  \param T[] tableau dans lequel il faut trouver les deux minimums
 *  \param s Taille du tableau
 *  \return Tableau contenant les indices des deux minimums
 */
size_t* deuxMinimum(tab T[], size_t s);

/**  Fonction qui a pour but de construire l'arbre de HUFFMAN
 *  Pour cela, elle crée plusieurs arbres qui sont stockés dans un tableau,
 *  pour chaque arbre a fonction va ensuite les associer entre eux
 *  \param tab[] Tableau à partir duquel on crée l'arbre
 *  \param s taille du tableau
 */
Arbre construction(tab T[], size_t s);

/** Fonction qui crée une archive du dossier passée en paramètre 
 * \param chemin nom du fichier
 * \param tab[] Tableau de Lettre
 * \param size taille du tableau
 * \return retourne 0 si tout se passe bien, -1 sinon
 * \bug Le fichier créer est plus lourd que le fichier initiale, car on écris plus de caractères
 */ 
int archive(char* chemin, Lettre* tab, size_t size);


