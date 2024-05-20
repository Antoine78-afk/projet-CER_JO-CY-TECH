#ifndef ATHLETE_H
#define ATHLETE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Définition de la structure Athlete
typedef struct {
    char nom[50]; // Nom de l'athlète
    char prenom[50]; // Prénom de l'athlète
    char genre[10]; // Genre de l'athlète
} Athlete;

// Déclaration de la fonction pour créer un athlète
Athlete* creerAthlete(char* nom, char* prenom, char* genre);

// Déclaration de la fonction pour afficher les informations d'un athlète
void afficherAthlete(Athlete* athlete);

#endif // ATHLETE_H
