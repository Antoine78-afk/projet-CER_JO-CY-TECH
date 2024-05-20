#include "athlete.h"

// Cette fonction crée une nouvelle instance d'un athlète avec les informations fournies
Athlete* creerAthlete(char* nom, char* prenom, char* genre) {
    // Allocation de mémoire pour une nouvelle structure Athlete
    Athlete* athlete = (Athlete*) malloc(sizeof(Athlete));
    
    // Copie des informations dans les champs de la structure Athlete
    strcpy(athlete->nom, nom); // Copie le nom
    strcpy(athlete->prenom, prenom); // Copie le prénom
    strcpy(athlete->genre, genre); // Copie le genre
    
    // Retourne un pointeur vers la nouvelle structure Athlete
    return athlete;
}

// Cette fonction affiche les informations d'un athlète donné
void afficherAthlete(Athlete* athlete) {
    // Affiche le nom, le prénom et le genre de l'athlète
    printf("Nom: %s, Prénom: %s, Genre: %s\n", athlete->nom, athlete->prenom, athlete->genre);
}



    
