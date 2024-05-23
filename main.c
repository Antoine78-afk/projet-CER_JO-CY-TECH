#include <stdio.h>
#include <stdlib.h>
#include "athlete.h"
#include "performance.h"
#include "file_utils.h"
#include "stats.h"

// Déclare la fonction pour envoyer les athlètes aux JO
void envoyerAuxJO();

// Déclare la fonction pour consulter les statistiques des athlètes et afficher la progression
void consulterStatsEtProgression();

// Déclare la fonction pour ajouter un nouvel entraînement
void ajouterEntrainement();

// Séquences d'échappement ANSI pour les couleurs
#define RESET "\x1b[0m"
#define BOLD "\x1b[1m"
#define UNDERLINE "\x1b[4m"
#define BLUE "\x1b[34m"
#define CYAN "\x1b[36m"
#define YELLOW "\x1b[33m"
#define RED "\x1b[31m"
#define GREEN "\x1b[32m"

// Affiche le menu principal
void afficherBordure() {
    printf(BOLD CYAN "=============================================================\n" RESET);
}

void afficherTitre() {
    printf(BOLD CYAN "||" RESET "                 " BOLD YELLOW "Gestion des Performances des Athlètes" RESET "                 " BOLD CYAN "||\n" RESET);
}

void menu() {
    afficherBordure();
    afficherTitre();
    afficherBordure();
    printf(BOLD CYAN "||" RESET " " BOLD GREEN "1. Ajouter un nouvel entraînement" RESET "                                   " BOLD CYAN "||\n" RESET);
    printf(BOLD CYAN "||" RESET " " BOLD GREEN "2. Consulter l'historique des entraînements" RESET "                         " BOLD CYAN "||\n" RESET);
    printf(BOLD CYAN "||" RESET " " BOLD GREEN "3. Consulter les statistiques et la progression d'un athlète" RESET "        " BOLD CYAN "||\n" RESET);
    printf(BOLD CYAN "||" RESET " " BOLD GREEN "4. Voir les 3 meilleurs athlètes pour chaque épreuve et les envoyer aux JO" RESET " " BOLD CYAN "||\n" RESET);
    printf(BOLD CYAN "||" RESET " " BOLD RED "5. Quitter" RESET "                                                          " BOLD CYAN "||\n" RESET);
    afficherBordure();
}

int main() {
    int choix;
    do {
        system("clear"); // Clear console (use "cls" on Windows)
        menu();
        printf("Choisissez une option : ");
        scanf("%d", &choix);
        switch (choix) {
            case 1:
                ajouterEntrainement();
                break;
            case 2:
                consulterHistorique();
                break;
            case 3:
                consulterStatsEtProgression();
                break;
            case 4:
                envoyerAuxJO();
                break;
            case 5:
                afficherBordure();
                printf(BOLD CYAN "||" RESET "                      " BOLD RED "Au revoir!" RESET "                                   " BOLD CYAN "||\n" RESET);
                afficherBordure();
                break;
            default:
                afficherBordure();
                printf(BOLD CYAN "||" RESET "                " BOLD RED "Option invalide, veuillez réessayer." RESET "                 " BOLD CYAN "||\n" RESET);
                afficherBordure();
        }
        if (choix != 5) {
            printf("Appuyez sur Entrée pour continuer...");
            while (getchar() != '\n'); // Attend que l'utilisateur appuie sur Entrée
            getchar(); // Consomme le '\n' restant après scanf
        }
    } while (choix != 5);

    return 0;
}

// Affiche les statistiques des athlètes et permet d'afficher la progression d'un athlète
void consulterStatsEtProgression() {
    int choix;
    char nom[50], epreuve[50], date1[11], date2[11];
    
    afficherBordure();
    printf(BOLD CYAN "||" RESET " " BOLD GREEN "1. Consulter les statistiques" RESET "                                      " BOLD CYAN "||\n" RESET);
    printf(BOLD CYAN "||" RESET " " BOLD GREEN "2. Afficher la progression d'un athlète" RESET "                            " BOLD CYAN "||\n" RESET);
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
            afficherBordure();
            afficherProgression(nom, epreuve, date1, date2);
            afficherBordure();
            break;
        default:
            afficherBordure();
            printf(BOLD CYAN "||" RESET "                " BOLD RED "Option invalide, retour au menu principal." RESET "          " BOLD CYAN "||\n" RESET);
            afficherBordure();
    }
}   
