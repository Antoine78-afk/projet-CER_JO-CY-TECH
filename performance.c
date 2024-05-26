#include "header.h"

// Fonction pour créer une performance et initialiser ses informations
Performance* creerPerformance(char* date, char* epreuve, float temps, int positionRelais, char* nom) {
    Performance* performance = (Performance*)malloc(sizeof(Performance));
    strcpy(performance->date, date);
    strcpy(performance->epreuve, epreuve);
    performance->temps = temps;
    performance->positionRelais = positionRelais;
    strcpy(performance->nom, nom); // Ajouter le nom de l'athlète
    return performance;
}

// Fonction pour afficher une performance
void afficherPerformance(Performance* performance) {
    printf("Athlète: %s\n", performance->nom); // Afficher le nom de l'athlète
    printf("Date: %s, Epreuve: %s, Temps: %.2f", performance->date, performance->epreuve, performance->temps);
    if (performance->positionRelais != -1) {
        printf(", Position Relais: %d", performance->positionRelais);
    }
    printf("\n");
}

// Fonction pour valider le format d'une date
int validerDate(char* date) {
    int annee, mois, jour;
    if (sscanf(date, "%4d-%2d-%2d", &annee, &mois, &jour) != 3) {
        return 0;
    }
    if (annee < 2000 || annee > 2100 || mois < 1 || mois > 12 || jour < 1 || jour > 31) {
        return 0;
    }
    if ((mois == 4 || mois == 6 || mois == 9 || mois == 11) && jour > 30) {
        return 0;
    }
    return 1;
}

// Fonction pour valider le format d'un temps
int validerTemps(float temps) {
    return (temps > 0 && temps < 86400);
}

// Fonction pour valider le nom d'une épreuve
int validerEpreuve(char* epreuve) {
    const char* epreuves[] = {"100m", "400m", "5000m", "marathon", "relais"};
    for (int i = 0; i < 5; i++) {
        if (strcmp(epreuve, epreuves[i]) == 0) {
            return 1;
        }
    }
    return 0;
}

// Fonction pour ajouter un nouvel entraînement
void ajouterEntrainement() {
    char nom[50], prenom[50], date[11], epreuve[50];
    float temps;
    int positionRelais = -1;

    printf("Nom: ");
    scanf("%s", nom);
    printf("Prénom: ");
    scanf("%s", prenom);

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
        printf("Epreuve (choisissez parmi '100m', '400m', '5000m', 'marathon', 'relais'): ");
        scanf("%s", epreuve);
        if (!validerEpreuve(epreuve)) {
            printf("Epreuve invalide. Veuillez choisir une épreuve valide.\n");
        }
    } while (!validerEpreuve(epreuve));

    if (strcmp(epreuve, "relais") == 0) {
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
            while (getchar() != '\n');
        }
    } while (1);

    Athlete* athlete = creerAthlete(nom, prenom);
    Performance* performance = creerPerformance(date, epreuve, temps, positionRelais, nom);
    sauvegarderPerformance(nom, performance);
    afficherAthlete(athlete);
    afficherPerformance(performance);
    free(athlete);
    free(performance);
}

// Fonction pour consulter l'historique des entraînements
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

// Fonction pour consulter l'historique par date et épreuve
void consulterHistoriqueParDateEpreuve(char* nom, char* date, char* epreuve) {
    FILE* athletesFile = fopen("athlete.txt", "r");
    if (athletesFile == NULL) {
        printf("Erreur d'ouverture du fichier des athlètes\n");
        return;
    }

    char athleteName[50];
    while (fgets(athleteName, sizeof(athleteName), athletesFile)) {
        athleteName[strcspn(athleteName, "\n")] = '\0';

        char filename[60];
        sprintf(filename, "%s.txt", athleteName);
        FILE* file = fopen(filename, "r");
        if (file == NULL) {
            continue;
        }

        char line[100];
        while (fgets(line, sizeof(line), file)) {
            char dateLue[11], epreuveLue[50];
            float temps;
            int positionRelais;
            sscanf(line, "%10[^,],%49[^,],%f,%d", dateLue, epreuveLue, &temps, &positionRelais);

            if ((nom != NULL && strcmp(athleteName, nom) == 0) ||
                (date != NULL && strcmp(dateLue, date) == 0) ||
                (epreuve != NULL && strcmp(epreuveLue, epreuve) == 0)) {
                Performance* performance = creerPerformance(dateLue, epreuveLue, temps, positionRelais, athleteName);
                afficherPerformance(performance);
                free(performance);
            }
        }
        fclose(file);
    }
    fclose(athletesFile);
}
