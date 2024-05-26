#ifndef ATHLETE_H // Début de la directive de préprocesseur pour éviter les inclusions multiples
#define ATHLETE_H // Définit le macro ATHLETE_H

#include <stdio.h> // Inclusion de la bibliothèque standard pour les opérations d'entrée/sortie
#include <stdlib.h> // Inclusion de la bibliothèque standard pour les fonctions utilitaires générales
#include <string.h> // Inclusion de la bibliothèque standard pour les opérations sur les chaînes de caractères

// Séquences d'échappement ANSI pour les couleurs
#define RESET "\x1b[0m" // Réinitialise toutes les caractéristiques
#define BOLD "\x1b[1m" // Gras
#define UNDERLINE "\x1b[4m" // Souligné
#define BLUE "\x1b[34m" // Bleu
#define CYAN "\x1b[36m" // Cyan
#define YELLOW "\x1b[33m" // Jaune
#define RED "\x1b[31m" // Rouge
#define GREEN "\x1b[32m" // Vert

// Structure représentant un athlète
typedef struct {
    char nom[50]; // Nom de l'athlète
    char prenom[50]; // Prénom de l'athlète
} Athlete; // Définition de la structure Athlete

// Fonction pour créer un athlète
// Paramètres : nom (chaîne de caractères), prenom (chaîne de caractères)
// Retourne : un pointeur vers une structure Athlete nouvellement créée
Athlete* creerAthlete(char* nom, char* prenom);

// Fonction pour afficher les informations d'un athlète
// Paramètre : athlete (pointeur vers une structure Athlete)
// Affiche le nom et le prénom de l'athlète
void afficherAthlete(Athlete* athlete);

// Structure représentant une performance athlétique
typedef struct {
    char date[11]; // Date de la performance au format AAAA-MM-JJ
    char epreuve[50]; // Nom de l'épreuve
    float temps; // Temps réalisé par l'athlète
    int positionRelais; // Position dans le relais (de 1 à 4), -1 si ce n'est pas une épreuve de relais
    char nom[50];
} Performance; // Définition de la structure Performance

// Structure représentant les performances moyennes d'un athlète
typedef struct {
    char nom[50]; // Nom de l'athlète
    float tempsMoyen; // Temps moyen réalisé par l'athlète
} AthletePerformance; // Définition de la structure AthletePerformance

// Fonction pour créer une performance
// Paramètres : date (chaîne de caractères), epreuve (chaîne de caractères), temps (nombre flottant), positionRelais (entier)
// Retourne : un pointeur vers une structure Performance nouvellement créée
Performance* creerPerformance(char* date, char* epreuve, float temps, int positionRelais, char* nom);

// Fonction pour afficher une performance
// Paramètre : performance (pointeur vers une structure Performance)
// Affiche la date, l'épreuve, le temps et éventuellement la position dans le relais
void afficherPerformance(Performance* performance);

// Fonction pour ajouter un nouvel entraînement
// Affiche des messages et lit les entrées de l'utilisateur pour ajouter un nouvel entraînement
void ajouterEntrainement();

// Fonction pour consulter l'historique des entraînements
// Affiche des messages et lit les entrées de l'utilisateur pour consulter l'historique des entraînements
void consulterHistorique();

// Fonction pour consulter l'historique des entraînements par date et épreuve
// Paramètres : nom (chaîne de caractères ou NULL), date (chaîne de caractères ou NULL), epreuve (chaîne de caractères ou NULL)
// Affiche les performances correspondant aux critères fournis
void consulterHistoriqueParDateEpreuve(char* nom, char* date, char* epreuve);

// Fonction pour valider le format d'une date
// Paramètre : date (chaîne de caractères)
// Retourne : 1 si la date est valide, 0 sinon
int validerDate(char* date);

// Fonction pour valider le format d'un temps
// Paramètre : temps (nombre flottant)
// Retourne : 1 si le temps est valide, 0 sinon
int validerTemps(float temps);

// Fonction pour valider le nom d'une épreuve
// Paramètre : epreuve (chaîne de caractères)
// Retourne : 1 si l'épreuve est valide, 0 sinon
int validerEpreuve(char* epreuve);

// Fonction pour afficher les statistiques des performances d'un athlète pour une épreuve donnée
// Paramètres : nom (chaîne de caractères), epreuve (chaîne de caractères)
// Affiche les statistiques des performances de l'athlète pour l'épreuve spécifiée
void afficherStats(char* nom, char* epreuve);

// Fonction pour sauvegarder une performance dans un fichier
// Paramètres : nom (chaîne de caractères), performance (pointeur vers une structure Performance)
// Sauvegarde les informations de la performance dans un fichier
void sauvegarderPerformance(char* nom, Performance* performance);

// Fonction pour lire l'historique des performances d'un athlète
// Paramètre : nom (chaîne de caractères)
// Affiche l'historique des performances de l'athlète
void lireHistorique(char* nom);

// Fonction pour vérifier qu'un relais est unique par jour
// Paramètre : date (chaîne de caractères)
// Retourne : 1 si aucun autre relais n'est enregistré ce jour-là, 0 sinon
int verifierRelaisUnique(char* date);

// Fonction pour vérifier qu'un athlète existe
// Paramètre : nom (chaîne de caractères)
// Retourne : 1 si l'athlète existe, 0 sinon
int verifierAthleteExistant(char* nom);

// Fonction pour vérifier si un athlète a déjà couru dans une journée donnée
// Paramètres : nom (chaîne de caractères), date (chaîne de caractères)
// Retourne : 1 si l'athlète n'a pas couru ce jour-là, 0 sinon
int verifierParticipationDuJour(char* nom, char* date);

// Fonction pour vérifier la position dans un relais à une date donnée
// Paramètres : date (chaîne de caractères), position (entier)
// Retourne : 1 si la position est disponible, 0 sinon
int verifierPositionRelais(char* date, int position);

// Fonction pour ajouter un athlète
// Paramètre : nom (chaîne de caractères)
// Ajoute le nom de l'athlète dans un fichier
void ajouterAthlete(char* nom);

// Fonction pour afficher les trois meilleurs athlètes pour chaque épreuve et les envoyer aux JO
// Affiche les noms des trois meilleurs athlètes et leurs temps moyens pour l'épreuve choisie
void envoyerAuxJO();

// Fonction pour afficher la progression d'un athlète pour une même épreuve entre deux dates
// Paramètres : nom (chaîne de caractères), epreuve (chaîne de caractères), date1 (chaîne de caractères), date2 (chaîne de caractères)
// Affiche la progression de l'athlète pour l'épreuve spécifiée entre les deux dates fournies
void afficherProgression(char* nom, char* epreuve, char* date1, char* date2);

#endif // ATHLETE_H
