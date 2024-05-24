#include "header.h"

// Crée une nouvelle performance
Performance* creerPerformance(char* date, char* epreuve, float temps, int positionRelais) {
    Performance* performance = (Performance*) malloc(sizeof(Performance));
    strcpy(performance->date, date);
    strcpy(performance->epreuve, epreuve);
    performance->temps = temps;
    performance->positionRelais = positionRelais;
    return performance;
}

// Affiche les détails d'une performance
void afficherPerformance(Performance* performance) {
    printf("Date: %s, Epreuve: %s, Temps: %.2f", performance->date, performance->epreuve, performance->temps);
    if (performance->positionRelais != -1) {
        printf(", Position Relais: %d", performance->positionRelais);
    }
    printf("\n");
}

// Valide le format de la date (AAAA-MM-JJ)
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

// Valide que le temps est positif et raisonnable (< 24 heures)
int validerTemps(float temps) {
    if (temps > 0 && temps < 86400) {
        return 1;
    }
    return 0;
}

// Valide que l'épreuve est reconnue
int validerEpreuve(char* epreuve) {
    const char* epreuves[] = {"100m", "400m", "5000m", "marathon", "relais"};
    for (int i = 0; i < 5; i++) {
        if (strcmp(epreuve, epreuves[i]) == 0) {
            return 1;
        }
    }
    return 0;
}

// Vérifie qu'il n'y a pas déjà un entraînement de relais à cette date
int verifierRelaisUnique(char* date) {
    FILE* athletesFile = fopen("athlete.txt", "r");
    if (athletesFile != NULL) {
        char athleteName[50];
        while (fgets(athleteName, sizeof(athleteName), athletesFile)) {
            athleteName[strcspn(athleteName, "\n")] = '\0'; // Retire le saut de ligne
            char filename[60];
            sprintf(filename, "%s.txt", athleteName);
            FILE* file = fopen(filename, "r");
            if (file != NULL) {
                char line[100];
                while (fgets(line, sizeof(line), file)) {
                    char dateLue[11], epreuveLue[50];
                    sscanf(line, "%10[^,],%49[^,]", dateLue, epreuveLue);
                    if (strcmp(date, dateLue) == 0 && strcmp(epreuveLue, "relais") == 0) {
                        fclose(file);
                        fclose(athletesFile);
                        return 0; // Un autre relais existe déjà ce jour-là
                    }
                }
                fclose(file);
            }
        }
        fclose(athletesFile);
    }
    return 1; // Aucun relais trouvé ce jour-là
}

// Vérifie si un athlète existe dans le fichier athletes.txt
int verifierAthleteExistant(char* nom) {
    FILE* athletesFile = fopen("athlete.txt", "r");
    if (athletesFile != NULL) {
        char athleteName[50];
        while (fgets(athleteName, sizeof(athleteName), athletesFile)) {
            athleteName[strcspn(athleteName, "\n")] = '\0'; // Retire le saut de ligne
            if (strcmp(athleteName, nom) == 0) {
                fclose(athletesFile);
                return 1; // Athlète trouvé
            }
        }
        fclose(athletesFile);
    }
    return 0; // Athlète non trouvé
}

// Ajoute un athlète dans le fichier athletes.txt
void ajouterAthlete(char* nom) {
    FILE* athletesFile = fopen("athlete.txt", "a");
    if (athletesFile != NULL) {
        fprintf(athletesFile, "%s\n", nom);
        fclose(athletesFile);
    } else {
        printf("Erreur : Impossible d'ouvrir le fichier athletes.txt\n");
    }
}

// Ajoute un nouvel entraînement
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
        printf("Epreuve (choisissez parmi '100m', '400m', '5000m', 'marathon', 'relais'): ");
        scanf("%s", epreuve);
        if (!validerEpreuve(epreuve)) {
            printf("Epreuve invalide. Veuillez choisir une épreuve valide.\n");
        }
    } while (!validerEpreuve(epreuve));

    if (strcmp(epreuve, "relais") == 0) {
        if (!verifierRelaisUnique(date)) {
            printf("Erreur : Un autre relais est déjà enregistré à cette date.\n");
            return;
        }

        printf("Position dans le relais (1-4): ");
        scanf("%d", &positionRelais);

        // Vérifie qu'aucun athlète n'a déjà la même position dans le relais ce jour-là
        FILE* athletesFile = fopen("athlete.txt", "r");
        if (athletesFile != NULL) {
            char athleteName[50];
            while (fgets(athleteName, sizeof(athleteName), athletesFile)) {
                athleteName[strcspn(athleteName, "\n")] = '\0'; // Retire le saut de ligne
                char filename[60];
                sprintf(filename, "%s.txt", athleteName);
                FILE* file = fopen(filename, "r");
                if (file != NULL) {
                    char line[100];
                    while (fgets(line, sizeof(line), file)) {
                        char dateLue[11], epreuveLue[50];
                        int positionRelaisLue;
                        sscanf(line, "%10[^,],%49[^,],%*f,%d", dateLue, epreuveLue, &positionRelaisLue);
                        if (strcmp(date, dateLue) == 0 && strcmp(epreuveLue, "relais") == 0 && positionRelais == positionRelaisLue) {
                            printf("Erreur : Un autre athlète a déjà la position %d dans le relais pour cette date.\n", positionRelais);
                            fclose(file);
                            fclose(athletesFile);
                            return;
                        }
                    }
                    fclose(file);
                }
            }
            fclose(athletesFile);
        }
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
    free(athlete);
    free(performance);
}

// Consulte l'historique des entraînements d'un athlète
void consulterHistorique() {
    char nom[50];
    printf("Nom de l'athlète: ");
    scanf("%s", nom);
    lireHistorique(nom);
}

