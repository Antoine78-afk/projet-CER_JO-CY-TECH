#include "header.h"

Performance* creerPerformance(char* date, char* epreuve, float temps, int positionRelais) {
    Performance* performance = (Performance*) malloc(sizeof(Performance));
    strcpy(performance->date, date);
    strcpy(performance->epreuve, epreuve);
    performance->temps = temps;
    performance->positionRelais = positionRelais;
    return performance;
}

void afficherPerformance(Performance* performance) {
    printf("Date: %s, Epreuve: %s, Temps: %.2f", performance->date, performance->epreuve, performance->temps);
    if (performance->positionRelais != -1) {
        printf(", Position Relais: %d", performance->positionRelais);
    }
    printf("\n");
}

int validerDate(char* date) {
    int annee, mois, jour;
    if (sscanf(date, "%4d-%2d-%2d", &annee, &mois, &jour) != 3) {
        return 0; // Format incorrect
    }
    if (annee < 2000 || annee > 2100 || mois < 1 || mois > 12 || jour < 1 || jour > 31) {
        return 0; // Valeurs invalides
    }
    // Vérification des jours par mois
    if ((mois == 4 || mois == 6 || mois == 9 || mois == 11) && jour > 30) {
        return 0; // Mois de 30 jours
    }
    return 1; // Date valide
}

int validerTemps(float temps) {
    return (temps > 0 && temps < 86400);
}

int validerEpreuve(char* epreuve) {
    const char* epreuves[] = {"100m", "200m", "400m", "marathon", "relais"};
    for (int i = 0; i < 5; i++) {
        if (strcmp(epreuve, epreuves[i]) == 0) {
            return 1;
        }
    }
    return 0;
}

void ajouterEntrainement() {
    char nom[50], prenom[50], date[11], epreuve[50];
    float temps;
    int positionRelais = -1;

    printf("Nom: ");
    scanf("%s", nom);
    printf("Prénom: ");
    scanf("%s", prenom);

    // Ajouter l'athlète au fichier athletes.txt s'il n'existe pas déjà
    if (!verifierAthleteExistant(nom)) {
        ajouterAthlete(nom);
    }

    do {
        printf("Date (AAAA-MM-JJ): ");
        scanf("%s", date);
        if (!validerDate(date)) {
            printf("Date invalide. Veuillez entrer une date valide au format AAAA-MM-JJ.\n");
        }
    } while (!validerDate(date));

    do {
        printf("Epreuve (choisissez parmi '100m', '200m', '400m', 'marathon', 'relais'): ");
        scanf("%s", epreuve);
        if (!validerEpreuve(epreuve)) {
            printf("Epreuve invalide. Veuillez choisir une épreuve valide.\n");
        }
    } while (!validerEpreuve(epreuve));

    if (strcmp(epreuve, "relais") == 0) {
        // Vérifier si l'athlète a déjà couru un relais ce jour-là
        if (!verifierParticipationDuJour(nom, date)) {
            printf("Erreur : L'athlète a déjà couru un relais ce jour-là.\n");
            return;
        }

        if (!verifierRelaisUnique(date)) {
            printf("Erreur : Quatre relais sont déjà enregistrés à cette date.\n");
            return;
        }

        do {
            printf("Position dans le relais (1-4): ");
            scanf("%d", &positionRelais);
            if (positionRelais < 1 || positionRelais > 4 || !verifierPositionRelais(date, positionRelais)) {
                printf("Position invalide ou déjà occupée. Veuillez choisir une position différente entre 1 et 4.\n");
            }
        } while (positionRelais < 1 || positionRelais > 4 || !verifierPositionRelais(date, positionRelais));
    }

    do {
        printf("Temps: ");
        if (scanf("%f", &temps) == 1 && validerTemps(temps)) {
            break;
        } else {
            printf("Temps invalide. Veuillez entrer un temps positif.\n");
            while (getchar() != '\n'); // Nettoie le buffer d'entrée
        }
    } while (1);

    Athlete* athlete = creerAthlete(nom, prenom);
    Performance* performance = creerPerformance(date, epreuve, temps, positionRelais);
    sauvegarderPerformance(nom, performance);
    afficherAthlete(athlete);
    afficherPerformance(performance);
    free(athlete);
    free(performance);
}

void consulterHistorique() {
    char nom[50], date[11], epreuve[50];
    printf("Nom de l'athlète: ");
    scanf("%s", nom);
    printf("Date (AAAA-MM-JJ): ");
    scanf("%s", date);
    printf("Epreuve: ");
    scanf("%s", epreuve);

    consulterHistoriqueParDateEpreuve(nom, date, epreuve);
}
