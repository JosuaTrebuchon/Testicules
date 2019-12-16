Nom de L'équipe : TREBUCHON Josua
                  DERROUICHE Rayan


Etat d'avancement du projet :

    Notre projet s'arrête à la construction de l'arbre et la création de code pour chaque caractère
    mais sous forme de chaine de caractères.
    Nous avons bloqués sur la manipulation des bites.

Bugs :

    - Notre projet ne prends pas en compte des fichiers qui comporte moins de 2 caractère différent
    - Possible fuite mémoire lors de la création des codes
    - Fichier crée (archive) plus lourde que le fichier à compresser.

Lancement du programme :

    gcc -Wall -o huffman main.c fonctions.c arbre_binaire.c

    ./huffman <nom fichier>