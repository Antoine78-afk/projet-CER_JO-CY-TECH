#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>
#include "affichage.c"
#include "athlete.h"

int main() {
    Athlete athlete1;
    strcpy(athlete1.nom, "John Doe");
    athlete1.nb_entrainements = 0;

    ajouterEntrainement(&athlete1, "2024-05-14", "100m", 10.5, -1);
    ajouterEntrainement(&athlete1, "2024-05-15", "Relais", 0, 2);

    consulterHistoriqueEntrainements(&athlete1);
    consulterStatistiquesPerformance(&athlete1);

    return 0;
}




















