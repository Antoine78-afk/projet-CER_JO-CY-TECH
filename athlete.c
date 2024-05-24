#include "header.h" // Inclut le fichier d'en-tête contenant les déclarations des fonctions et des structures

// Fonction pour créer un athlète et initialiser ses informations
Athlete* creerAthlete(char* nom, char* prenom) {
    // Alloue de la mémoire pour un nouvel athlète
    Athlete* athlete = (Athlete*) malloc(sizeof(Athlete));
    // Copie le nom fourni dans le champ nom de la structure Athlete
    strcpy(athlete->nom, nom);
    // Copie le prénom fourni dans le champ prénom de la structure Athlete
    strcpy(athlete->prenom, prenom);
    // Retourne le pointeur vers la structure Athlete nouvellement créée
    return athlete;
}

// Fonction pour afficher les informations d'un athlète
void afficherAthlete(Athlete* athlete) {
    // Affiche le nom et le prénom de l'athlète au format "Nom: [nom], Prénom: [prénom]"
    printf("Nom: %s, Prénom: %s\n", athlete->nom, athlete->prenom);
}


