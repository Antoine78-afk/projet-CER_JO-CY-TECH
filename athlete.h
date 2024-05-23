#ifndef ATHLETE_H
#define ATHLETE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure représentant un athlète
typedef struct {
    char nom[50];
    char prenom[50];
} Athlete;

// Fonction pour créer un athlète
// Alloue de la mémoire et initialise les champs nom et prénom
Athlete* creerAthlete(char* nom, char* prenom);

// Fonction pour afficher les informations d'un athlète
void afficherAthlete(Athlete* athlete);

// Structure représentant une performance athlétique
typedef struct {
    char date[11];
    char epreuve[50];
    float temps;
    int positionRelais; // -1 si ce n'est pas une épreuve de relais
} Performance;

// Fonction pour créer une performance
// Alloue de la mémoire et initialise les champs date, epreuve, temps et positionRelais
Performance* creerPerformance(char* date, char* epreuve, float temps, int positionRelais);

// Fonction pour afficher une performance
void afficherPerformance(Performance* performance);

// Fonction pour ajouter un nouvel entraînement
void ajouterEntrainement();

// Fonction pour consulter l'historique des entraînements
void consulterHistorique();

// Fonction pour valider le format d'une date
// Retourne 1 si la date est valide, 0 sinon
int validerDate(char* date);

// Fonction pour valider le format d'un temps
// Retourne 1 si le temps est valide, 0 sinon
int validerTemps(float temps);

// Fonction pour valider le nom d'une épreuve
// Retourne 1 si l'épreuve est valide, 0 sinon
int validerEpreuve(char* epreuve);

// Fonction pour afficher les statistiques des performances d'un athlète pour une épreuve donnée
void afficherStats(char* nom, char* epreuve);

// Fonction pour sauvegarder une performance dans un fichier
void sauvegarderPerformance(char* nom, Performance* performance);

// Fonction pour lire l'historique des performances d'un athlète
void lireHistorique(char* nom);

// Fonction pour afficher les trois meilleurs athlètes pour chaque épreuve et les envoyer aux JO
void envoyerAuxJO();

// Fonction pour afficher la progression d'un athlète pour une même épreuve entre deux dates
void afficherProgression(char* nom, char* epreuve, char* date1, char* date2);

#endif // ATHLETE_H
