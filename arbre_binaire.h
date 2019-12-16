#include <stdlib.h>

/* Definition d'un arbre binaire */
typedef struct arbre_bin{
    double val;            // Probabilité
    char* car;           // Si c'est une feuille possèe un caractère attribué
    struct arbre_bin *fils_droit;  // Pointeur vers le sous arbre droit
    struct arbre_bin *fils_gauche; // Pointeur vers le sous arbre gauche
} arbre_bin;
// Définition d'un pointeur vers un  arbre binaire.
typedef arbre_bin* Arbre;

/** Fonction qui crée un arbre binaire vide (allocation de mémoire)
 *  \param i Probabilité
 *  \param c Chaine de caractère du noeud
 *  \param Droit Fils droit de l'arbre à crée
 *  \param Gauche Fils Gauche de l'arbre à crée
 *  \return l'adreese mémoire de l'arbre crée
 */ 
Arbre createBinaryTree(double i, char* c, Arbre Droit, Arbre Gauche);


/** Fonction qui affiche chaque noeud de l'arbre passé en paramètre (en affichant d'abord le noeud fils gauche puis droit)
 * \param A Arbre 
 */ 
void afficheArbre(Arbre A);


/**  \struct lettre Cette structure va permettre de stocker chaque caractère ascii avec son code */
typedef struct lettre
{
    char car;
    char* code;
}lettre;
typedef lettre* Lettre;

/** Fonction qui stocke dans le tableau  passé en paramètre les Lettres.
 *  \param A Arbre de Huffman construit à partir du fichier passer en paramètre au début du main
 *  \param code Code de la chaine de caractère de l'arbre à l'apelle récursif x
 *  \param i indice de placement dans le tableau de Lettre
 *  \param tab Tableau contenant les caractères ascii avec leur code
 *  
 *  \bug Possible fuite de mémoire avec les codes du noeud parent
 */
void codeFeuille(Arbre A, char* code, size_t* i, Lettre* tab);