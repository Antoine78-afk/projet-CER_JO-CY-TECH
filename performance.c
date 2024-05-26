#include "header.h" // Inclusion du fichier d'en-tête contenant les déclarations et les définitions partagées

// Fonction pour créer une performance et initialiser ses informations
// Paramètres : date (chaîne de caractères), epreuve (chaîne de caractères), temps (nombre flottant), positionRelais (entier)
// Retourne : un pointeur vers une structure Performance nouvellement créée
Performance* creerPerformance(char* date, char* epreuve, float temps, int positionRelais) {
    Performance* performance = (Performance*) malloc(sizeof(Performance)); // Alloue de la mémoire pour une nouvelle performance
    strcpy(performance->date, date); // Copie la date fournie dans le champ date de la structure Performance
    strcpy(performance->epreuve, epreuve); // Copie le nom de l'épreuve fournie dans le champ epreuve de la structure Performance
    performance->temps = temps; // Initialise le champ temps de la structure Performance avec la valeur fournie
    performance->positionRelais = positionRelais; // Initialise le champ positionRelais de la structure Performance avec la valeur fournie
    return performance; // Retourne le pointeur vers la structure Performance nouvellement créée
}

// Fonction pour afficher une performance
// Paramètre : performance (pointeur vers une structure Performance)
// Affiche la date, l'épreuve, le temps et éventuellement la position dans le relais
void afficherPerformance(Performance* performance) {
    printf("Date: %s, Epreuve: %s, Temps: %.2f", performance->date, performance->epreuve, performance->temps); // Affiche la date, l'épreuve et le temps de la performance
    if (performance->positionRelais != -1) { // Vérifie si la performance concerne une épreuve de relais
        printf(", Position Relais: %d", performance->positionRelais); // Affiche la position dans le relais
    }
    printf("\n"); // Ajoute une nouvelle ligne
}

// Fonction pour valider le format d'une date
// Paramètre : date (chaîne de caractères)
// Retourne : 1 si la date est valide, 0 sinon
int validerDate(char* date) {
    int annee, mois, jour; // Variables pour stocker l'année, le mois et le jour extraits de la date
    if (sscanf(date, "%4d-%2d-%2d", &annee, &mois, &jour) != 3) { // Extrait l'année, le mois et le jour de la date
        return 0; // Retourne 0 si le format est incorrect
    }
    if (annee < 2000 || annee > 2100 || mois < 1 || mois > 12 || jour < 1 || jour > 31) { // Vérifie si les valeurs extraites sont valides
        return 0; // Retourne 0 si les valeurs sont invalides
    }
    // Vérification des jours par mois
    if ((mois == 4 || mois == 6 || mois == 9 || mois == 11) && jour > 30) { // Vérifie si le jour est valide pour les mois de 30 jours
        return 0; // Retourne 0 si le jour est invalide pour les mois de 30 jours
    }
    return 1; // Retourne 1 si la date est valide
}

// Fonction pour valider le format d'un temps
// Paramètre : temps (nombre flottant)
// Retourne : 1 si le temps est valide, 0 sinon
int validerTemps(float temps) {
    return (temps > 0 && temps < 86400); // Vérifie si le temps est positif et inférieur à 86400 secondes (24 heures)
}

// Fonction pour valider le nom d'une épreuve
// Paramètre : epreuve (chaîne de caractères)
// Retourne : 1 si l'épreuve est valide, 0 sinon
int validerEpreuve(char* epreuve) {
    const char* epreuves[] = {"100m", "400m", "5000m", "marathon", "relais"}; // Tableau contenant les noms des épreuves valides
    for (int i = 0; i < 5; i++) { // Parcourt le tableau des épreuves valides
        if (strcmp(epreuve, epreuves[i]) == 0) { // Compare l'épreuve fournie avec chaque épreuve du tableau
            return 1; // Retourne 1 si l'épreuve est valide
        }
    }
    return 0; // Retourne 0 si l'épreuve n'est pas valide
}

// Fonction pour ajouter un nouvel entraînement
// Affiche des messages et lit les entrées de l'utilisateur pour ajouter un nouvel entraînement
void ajouterEntrainement() {
    char nom[50], prenom[50], date[11], epreuve[50]; // Variables pour stocker le nom, le prénom, la date et l'épreuve
    float temps; // Variable pour stocker le temps
    int positionRelais = -1; // Variable pour stocker la position dans le relais, initialisée à -1 pour les non-relais

    printf("Nom: ");
    scanf("%s", nom); // Lit le nom de l'athlète
    printf("Prénom: ");
    scanf("%s", prenom); // Lit le prénom de l'athlète

    // Ajouter l'athlète au fichier athletes.txt s'il n'existe pas déjà
    if (!verifierAthleteExistant(nom)) { // Vérifie si l'athlète existe déjà
        ajouterAthlete(nom); // Ajoute l'athlète s'il n'existe pas
    }

    do {
        printf("Date (AAAA-MM-JJ): ");
        scanf("%s", date); // Lit la date de l'entraînement
        if (!validerDate(date)) { // Vérifie si la date est valide
            printf("Date invalide. Veuillez entrer une date valide au format AAAA-MM-JJ.\n");
        }
    } while (!validerDate(date)); // Répète la lecture de la date jusqu'à ce qu'elle soit valide

    do {
        printf("Epreuve (choisissez parmi '100m', '400m', '5000m', 'marathon', 'relais'): ");
        scanf("%s", epreuve); // Lit le nom de l'épreuve
        if (!validerEpreuve(epreuve)) { // Vérifie si l'épreuve est valide
            printf("Epreuve invalide. Veuillez choisir une épreuve valide.\n");
        }
    } while (!validerEpreuve(epreuve)); // Répète la lecture de l'épreuve jusqu'à ce qu'elle soit valide

    if (strcmp(epreuve, "relais") == 0) { // Vérifie si l'épreuve est un relais
        // Vérifier si l'athlète a déjà couru un relais ce jour-là
        if (!verifierParticipationDuJour(nom, date)) { // Vérifie si l'athlète a déjà couru un relais ce jour-là
            printf("Erreur : L'athlète a déjà couru un relais ce jour-là.\n");
            return; // Sort de la fonction si l'athlète a déjà couru un relais ce jour-là
        }

        if (!verifierRelaisUnique(date)) { // Vérifie si quatre relais sont déjà enregistrés à cette date
            printf("Erreur : Quatre relais sont déjà enregistrés à cette date.\n");
            return; // Sort de la fonction si quatre relais sont déjà enregistrés à cette date
        }

        do {
            printf("Position dans le relais (1-4): ");
            scanf("%d", &positionRelais); // Lit la position dans le relais
            if (positionRelais < 1 || positionRelais > 4 || !verifierPositionRelais(date, positionRelais)) { // Vérifie si la position est valide et disponible
                printf("Position invalide ou déjà occupée. Veuillez choisir une position différente entre 1 et 4.\n");
            }
        } while (positionRelais < 1 || positionRelais > 4 || !verifierPositionRelais(date, positionRelais)); // Répète la lecture de la position jusqu'à ce qu'elle soit valide et disponible
    }

    do {
        printf("Temps: ");
        if (scanf("%f", &temps) == 1 && validerTemps(temps)) { // Lit le temps et vérifie s'il est valide
            break; // Sort de la boucle si le temps est valide
        } else {
            printf("Temps invalide. Veuillez entrer un temps positif.\n");
            while (getchar() != '\n'); // Nettoie le buffer d'entrée
        }
    } while (1); // Répète la lecture du temps jusqu'à ce qu'il soit valide

    Athlete* athlete = creerAthlete(nom, prenom); // Crée un nouvel athlète
    Performance* performance = creerPerformance(date, epreuve, temps, positionRelais); // Crée une nouvelle performance
    sauvegarderPerformance(nom, performance); // Sauvegarde la performance dans un fichier
    afficherAthlete(athlete); // Affiche les informations de l'athlète
    afficherPerformance(performance); // Affiche les informations de la performance
        free(athlete); // Libère la mémoire allouée pour la structure Athlete
    free(performance); // Libère la mémoire allouée pour la structure Performance
}

// Fonction pour consulter l'historique des entraînements
// Affiche des messages et lit les entrées de l'utilisateur pour consulter l'historique des entraînements
void consulterHistorique() {
    char nom[50], date[11], epreuve[50]; // Variables pour stocker le nom, la date et l'épreuve

    printf("Nom de l'athlète: ");
    scanf("%s", nom); // Lit le nom de l'athlète
    printf("Date (AAAA-MM-JJ): ");
    scanf("%s", date); // Lit la date
    printf("Epreuve: ");
    scanf("%s", epreuve); // Lit le nom de l'épreuve

    consulterHistoriqueParDateEpreuve(nom, date, epreuve); // Appelle la fonction pour consulter l'historique par nom, date et épreuve
}
