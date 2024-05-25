//#include "header.h"

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
    const char* epreuves[] = {"100m", "400m","5000m","marathon", "relais"};
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
        printf("Epreuve (choisissez parmi '100m', '400m', '5000m', 'marathon', 'relais'): ");
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
// Fonction pour consulter les statistiques des athlètes et afficher la progression
void consulterStatsEtProgression() {
    int choix;
    char nom[50], epreuve[50], date1[11], date2[11];
    
    do {
        afficherBordure();
        printf(BOLD CYAN "||" RESET " " BOLD GREEN "1. Consulter les statistiques" RESET "                                                " BOLD CYAN "||\n" RESET);
        printf(BOLD CYAN "||" RESET " " BOLD GREEN "2. Afficher la progression d'un athlète" RESET "                                      " BOLD CYAN "||\n" RESET);
        printf(BOLD CYAN "||" RESET " " BOLD RED "3. Retour au menu principal" RESET "                                                  " BOLD CYAN "||\n" RESET);
        afficherBordure();
        printf("Choisissez une option : ");
        scanf("%d", &choix);
        
        switch (choix) {
            case 1:
                printf("Nom de l'athlète: ");
                scanf("%s", nom);
                printf("Épreuve: ");
                scanf("%s", epreuve);
                afficherBordure();
                afficherStats(nom, epreuve);
                afficherBordure();
                break;
            case 2:
                printf("Nom de l'athlète: ");
                scanf("%s", nom);
                printf("Épreuve: ");
                scanf("%s", epreuve);
                printf("Date de début (AAAA-MM-JJ): ");
                scanf("%s", date1);
                printf("Date de fin (AAAA-MM-JJ): ");
                scanf("%s", date2);
                
                if (!validerDate(date1) || !validerDate(date2)) {
                    printf("Les dates entrées ne sont pas valides.\n");
                    break;
                }
                
                afficherBordure();
                afficherProgression(nom, epreuve, date1, date2);
                afficherBordure();
                break;
            case 3:
                return; // Retourne au menu principal
            default:
                afficherBordure();
                printf(BOLD CYAN "||" RESET "                " BOLD RED "Option invalide, retour au menu principal." RESET "          " BOLD CYAN "||\n" RESET);
                afficherBordure();
        }
        printf("Appuyez sur Entrée pour continuer...");
        while (getchar() != '\n'); // Attend que l'utilisateur appuie sur Entrée
        getchar(); // Consomme le '\n' restant après scanf
    } while (choix != 3);
}

// Fonction pour consulter l'historique selon différents critères
void consulterHistoriqueParCritere() {
    int critere;
    char valeur[50];
    afficherBordure();
    printf(BOLD CYAN "||" RESET " " BOLD GREEN "1. Consulter par NOM" RESET "                                                         " BOLD CYAN "||\n" RESET);
    printf(BOLD CYAN "||" RESET " " BOLD GREEN "2. Consulter par DATE" RESET "                                                        " BOLD CYAN "||\n" RESET);
    printf(BOLD CYAN "||" RESET " " BOLD GREEN "3. Consulter par ÉPREUVE" RESET "                                                     " BOLD CYAN "||\n" RESET);
    afficherBordure();
    printf("Choisissez un critère : ");
    scanf("%d", &critere);

    switch (critere) {
        case 1:
            printf("Nom de l'athlète: ");
            scanf("%s", valeur);
            consulterHistoriqueParDateEpreuve(valeur, NULL, NULL);
            break;
        case 2:
            printf("Date (AAAA-MM-JJ): ");
            scanf("%s", valeur);
            consulterHistoriqueParDateEpreuve(NULL, valeur, NULL);
            break;
        case 3:
            printf("Epreuve: ");
            scanf("%s", valeur);
            consulterHistoriqueParDateEpreuve(NULL, NULL, valeur);
            break;
        default:
            afficherBordure();
            printf(BOLD CYAN "||" RESET "                " BOLD RED "Option invalide, retour au menu principal." RESET "          " BOLD CYAN "||\n" RESET);
            afficherBordure();
    }
}
