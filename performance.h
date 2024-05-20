#ifndef PERFORMANCE_H
#define PERFORMANCE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "athlete.h"

// Définition de la structure Performance
typedef struct {
    char date[11]; // Date de la performance au format AAAA-MM-JJ
    char epreuve[50]; // Nom de l'épreuve
    float temps; // Temps réalisé lors de l'épreuve
    int positionRelais; // Position dans le relais, -1 si ce n'est pas une épreuve de relais
} Performance;

// Déclaration de la fonction pour créer une nouvelle performance
Performance* creerPerformance(char* date, char* epreuve, float temps, int positionRelais);

// Déclaration de la fonction pour afficher les détails d'une performance
void afficherPerformance(Performance* performance);

// Déclaration de la fonction pour ajouter un nouvel entraînement
void ajouterEntrainement();

// Déclaration de la fonction pour consulter l'historique des performances
void consulterHistorique();

// Déclaration de la fonction pour consulter les statistiques des performances
void consulterStats();

#endif // PERFORMANCE_H
