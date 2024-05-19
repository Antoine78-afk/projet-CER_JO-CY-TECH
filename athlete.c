#include "athlete.h"
#include <stdio.h>
#include <string.h>


#define MAX_ENTRAINEMENTS 100
#define MAX_TYPES_EPREUVES 10


void ajouterEntrainement(Athlete *athlete, char date[], char type_epreuve[], float temps, int position_relais) {
    // Vérifier si l'athlète a atteint le nombre maximum d'entraînements
    if (athlete->nb_entrainements >= MAX_ENTRAINEMENTS) {
        printf("Nombre maximum d'entraînements atteint pour cet athlète.\n");
        return;
    }

    // Ajouter les détails de l'entraînement à la liste des entraînements de l'athlète
    strcpy(athlete->entrainements[athlete->nb_entrainements].date, date);
    strcpy(athlete->entrainements[athlete->nb_entrainements].type_epreuve, type_epreuve);
    athlete->entrainements[athlete->nb_entrainements].temps = temps;
    athlete->entrainements[athlete->nb_entrainements].position_relais = position_relais;

    // Incrémenter le nombre d'entraînements de l'athlète
    athlete->nb_entrainements++;

    printf("Entraînement ajouté avec succès pour %s.\n", athlete->nom);
}

void consulterHistoriqueEntrainements(Athlete *athlete) {
    printf("Historique des entraînements pour %s:\n", athlete->nom);
    for (int i = 0; i < athlete->nb_entrainements; i++) {
        printf("Date: %s, Type d'épreuve: %s, Temps: %.2f\n", 
               athlete->entrainements[i].date, 
               athlete->entrainements[i].type_epreuve, 
               athlete->entrainements[i].temps);
    }
}

void consulterHistoriqueEntrainementsParType(Athlete *athlete, char type_epreuve[]) {
    printf("Historique des entraînements pour %s - Type d'épreuve: %s:\n", athlete->nom, type_epreuve);
    for (int i = 0; i < athlete->nb_entrainements; i++) {
        if (strcmp(athlete->entrainements[i].type_epreuve, type_epreuve) == 0) {
            printf("Date: %s, Temps: %.2f\n", athlete->entrainements[i].date, athlete->entrainements[i].temps);
        }
    }
}

void consulterHistoriqueEntrainementsParDate(Athlete *athlete, char date[]) {
    printf("Historique des entraînements pour %s - Date: %s:\n", athlete->nom, date);
    for (int i = 0; i < athlete->nb_entrainements; i++) {
        if (strcmp(athlete->entrainements[i].date, date) == 0) {
            printf("Type d'épreuve: %s, Temps: %.2f\n", athlete->entrainements[i].type_epreuve, athlete->entrainements[i].temps);
        }
    }
}

void consulterStatistiquesPerformance(Athlete *athlete) {
    StatistiquesEpreuve stats[MAX_TYPES_EPREUVES];
    int nb_types_epreuves = 0;

    for (int i = 0; i < athlete->nb_entrainements; i++) {
        char *type_epreuve = athlete->entrainements[i].type_epreuve;
        float temps = athlete->entrainements[i].temps;

        int j;
        for (j = 0; j < nb_types_epreuves; j++) {
            if (strcmp(stats[j].type_epreuve, type_epreuve) == 0) {
                break;
            }
        }

        if (j == nb_types_epreuves) {
            strcpy(stats[nb_types_epreuves].type_epreuve, type_epreuve);
            stats[nb_types_epreuves].meilleur_temps = temps;
            stats[nb_types_epreuves].pire_temps = temps;
            stats[nb_types_epreuves].somme_temps = temps;
            stats[nb_types_epreuves].nb_entrainements = 1;
            nb_types_epreuves++;
        } else {
            if (temps < stats[j].meilleur_temps) {
                stats[j].meilleur_temps = temps;
            }
            if (temps > stats[j].pire_temps) {
                stats[j].pire_temps = temps;
            }
            stats[j].somme_temps += temps;
            stats[j].nb_entrainements++;
        }
    }

    printf("Statistiques de performance pour %s:\n", athlete->nom);
    for (int i = 0; i < nb_types_epreuves; i++) {
        float moyenne_temps = stats[i].somme_temps / stats[i].nb_entrainements;
        printf("Type d'épreuve: %s\n", stats[i].type_epreuve);
        printf("  Meilleur temps: %.2f\n", stats[i].meilleur_temps);
        printf("  Pire temps: %.2f\n", stats[i].pire_temps);
        printf("  Moyenne des temps: %.2");
    }
}
    