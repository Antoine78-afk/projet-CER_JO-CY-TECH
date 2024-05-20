#ifndef FILE_UTILS_H
#define FILE_UTILS_H

#include "performance.h"

// Déclaration de la fonction pour sauvegarder une performance dans un fichier
void sauvegarderPerformance(char* nom, Performance* performance);

// Déclaration de la fonction pour lire l'historique des performances d'un athlète depuis un fichier
void lireHistorique(char* nom);

#endif // FILE_UTILS_H
