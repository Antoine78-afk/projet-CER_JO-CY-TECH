#include "athlete.h"
#include <stdio.h>
#include <string.h>


#define MAX_ENTRAINEMENTS 100

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
    float meilleur_temps = athlete->entrainements[0].temps;
    float pire_temps = athlete->entrainements[0].temps;
    float somme_temps = 0;
//calcule la moyenne des temps ainsi que le pire et le meilleur
    for (int i = 0; i < athlete->nb_entrainements; i++) {
        float temps = athlete->entrainements[i].temps;
        somme_temps += temps;
        if (temps < meilleur_temps) {
            meilleur_temps = temps;
        }
        if (temps > pire_temps) {
            pire_temps = temps;
        }
    }

    float moyenne_temps = somme_temps / athlete->nb_entrainements;

    printf("Statistiques de performance pour %s:\n", athlete->nom);
    printf("Meilleur temps: %.2f\n", meilleur_temps);
    printf("Pire temps: %.2f\n", pire_temps);
    printf("Moyenne des temps: %.2f\n", moyenne_temps);
}
