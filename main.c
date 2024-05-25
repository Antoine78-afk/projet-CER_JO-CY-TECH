#include <stdio.h>
#include <stdlib.h>
#include "header.h"
#include <locale.h>

// Déclarations des fonctions
void envoyerAuxJO();
void consulterStatsEtProgression();
void ajouterEntrainement();
void afficherBordure();
void afficherTitre();
void menu();
void consulterHistorique();
void consulterHistoriqueParCritere();

// Séquences d'échappement ANSI pour les couleurs
#define RESET "\x1b[0m"
#define BOLD "\x1b[1m"
#define UNDERLINE "\x1b[4m"
#define BLUE "\x1b[34m"
#define CYAN "\x1b[36m"
#define YELLOW "\x1b[33m"
#define RED "\x1b[31m"
#define GREEN "\x1b[32m"

// Affiche la bordure du menu
void afficherBordure() {
    printf(BOLD CYAN "=================================================================================\n" RESET);
}

// Affiche le titre du menu
void afficherTitre() {
    printf(BOLD CYAN "||" RESET "                 " BOLD YELLOW "Gestion des Performances des Athlètes" RESET "                        " BOLD CYAN "||\n" RESET);
}

// Affiche le menu principal
void menu() {
    afficherBordure();
    afficherTitre();
    afficherBordure();
    printf(BOLD CYAN "||" RESET " " BOLD GREEN "1. Ajouter un nouvel entraînement" RESET "                                            " BOLD CYAN "||\n" RESET);
    printf(BOLD CYAN "||" RESET " " BOLD GREEN "2. Consulter l'historique des entraînements" RESET "                                  " BOLD CYAN "||\n" RESET);
    printf(BOLD CYAN "||" RESET " " BOLD GREEN "3. Consulter les statistiques et la progression d'un athlète" RESET "                 " BOLD CYAN "||\n" RESET);
    printf(BOLD CYAN "||" RESET " " BOLD GREEN "4. Voir les 3 meilleurs athlètes pour une épreuve et les envoyer aux JO" RESET "      " BOLD CYAN "||\n" RESET);
    printf(BOLD CYAN "||" RESET " " BOLD RED "5. Quitter" RESET "                                                                   " BOLD CYAN "||\n" RESET);
    afficherBordure();
}

// Fonction principale
int main() {
    setlocale(LC_ALL, "en_US.UTF-8");
    int choix;
    do {
        system("clear"); // Efface la console (utilise "cls" sur Windows)
        menu();
        printf("Choisissez une option : ");
        scanf("%d", &choix);
        switch (choix) {
            case 1:
                printf(BOLD CYAN "||" RESET "                " BOLD GREEN "Nouvel entrainement:" RESET "                                  " BOLD CYAN "||\n" RESET);
                ajouterEntrainement();
                afficherBordure();
                printf(BOLD CYAN "||" RESET "                " BOLD GREEN "Nouvel entraînement ajouté avec succès!" RESET "               " BOLD CYAN "||\n" RESET);
                afficherBordure();
                break;
            case 2:
                printf(BOLD CYAN "||" RESET "                " BOLD GREEN "Consultation de l'historique:" RESET "                          " BOLD CYAN "||\n" RESET);
                consulterHistoriqueParCritere();
                break;
            case 3:
                printf(BOLD CYAN "||" RESET "                " BOLD GREEN "Consultation des statistiques:" RESET "                         " BOLD CYAN "||\n" RESET);
                consulterStatsEtProgression();
                break;
            case 4:
                printf(BOLD CYAN "||" RESET "                " BOLD GREEN "Selection olympique:" RESET "                                   " BOLD CYAN "||\n" RESET);
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
    printf(BOLD CYAN "||" RESET " " BOLD GREEN "1. Consulter par NOM" RESET "                                                " BOLD CYAN "||\n" RESET);
    printf(BOLD CYAN "||" RESET " " BOLD GREEN "2. Consulter par DATE" RESET "                                               " BOLD CYAN "||\n" RESET);
    printf(BOLD CYAN "||" RESET " " BOLD GREEN "3. Consulter par ÉPREUVE" RESET "                                            " BOLD CYAN "||\n" RESET);
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
