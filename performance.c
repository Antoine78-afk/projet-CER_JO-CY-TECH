#include "performance.h"
#include "file_utils.h"
#include "stats.h"

// Cette fonction crée une nouvelle performance et renvoie un pointeur vers celle-ci
Performance* creerPerformance(char* date, char* epreuve, float temps, int positionRelais) {
    Performance* performance = (Performance*) malloc(sizeof(Performance)); // Allocation mémoire pour une nouvelle performance
    strcpy(performance->date, date); // Copie la date dans la structure performance
    strcpy(performance->epreuve, epreuve); // Copie l'épreuve dans la structure performance
    performance->temps = temps; // Assigne le temps à la structure performance
    performance->positionRelais = positionRelais; // Assigne la position dans le relais à la structure performance
    return performance; // Retourne le pointeur vers la nouvelle performance
}

// Cette fonction affiche les détails d'une performance
void afficherPerformance(Performance* performance) {
    printf("Date: %s, Epreuve: %s, Temps: %.2f", performance->date, performance->epreuve, performance->temps); // Affiche la date, l'épreuve et le temps
    if (performance->positionRelais != -1) { // Vérifie si la performance concerne un relais
        printf(", Position Relais: %d", performance->positionRelais); // Si oui, affiche la position dans le relais
    }
    printf("\n");
}

// Cette fonction permet d'ajouter un entraînement pour un athlète
void ajouterEntrainement() {
    char nom[50], date[11], epreuve[50];
    float temps;
    int positionRelais = -1;

    // Demande les informations de l'entraînement à l'utilisateur
    printf("Nom de l'athlète: ");
    scanf("%s", nom);
    printf("Date (AAAA-MM-JJ): ");
    scanf("%s", date);
    printf("Epreuve: ");
    scanf("%s", epreuve);
    printf("Temps: ");
    scanf("%f", &temps);

    if (strcmp(epreuve, "relais") == 0) { // Vérifie si l'épreuve est un relais
        printf("Position dans le relais (1-4): ");
        scanf("%d", &positionRelais); // Si oui, demande la position dans le relais
    }

    // Crée une nouvelle performance avec les données fournies
    Performance* performance = creerPerformance(date, epreuve, temps, positionRelais);
    sauvegarderPerformance(nom, performance); // Sauvegarde la performance dans un fichier
    free(performance); // Libère la mémoire allouée pour la performance
}

// Cette fonction permet de consulter l'historique des performances d'un athlète
void consulterHistorique() {
    char nom[50];
    printf("Nom de l'athlète: ");
    scanf("%s", nom); // Demande le nom de l'athlète à l'utilisateur
    lireHistorique(nom); // Lit et affiche l'historique des performances de l'athlète
}

// Cette fonction permet de consulter les statistiques d'un athlète pour une épreuve donnée
void consulterStats() {
    char nom[50], epreuve[50];
    printf("Nom de l'athlète: ");
    scanf("%s", nom); // Demande le nom de l'athlète à l'utilisateur
    printf("Epreuve: ");
    scanf("%s", epreuve); // Demande l'épreuve à l'utilisateur
    afficherStats(nom, epreuve); // Affiche les statistiques de l'athlète pour l'épreuve spécifiée
}

