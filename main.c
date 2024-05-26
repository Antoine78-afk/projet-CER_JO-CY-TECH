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
    // Affiche une ligne horizontale avec des couleurs et des styles
    printf(BOLD CYAN "=================================================================================\n" RESET);
}

// Affiche le titre du menu
void afficherTitre() {
    // Affiche le titre du menu avec des couleurs et des styles
    printf(BOLD CYAN "||" RESET "                 " BOLD YELLOW "Gestion des Performances des Athlètes" RESET "                        " BOLD CYAN "||\n" RESET);
}

// Affiche le menu principal
void menu() {
    afficherBordure(); // Affiche la bordure en haut du menu
    afficherTitre(); // Affiche le titre du menu
    afficherBordure(); // Affiche une autre bordure
    // Affiche les différentes options du menu avec des couleurs et des styles
    printf(BOLD CYAN "||" RESET " " BOLD GREEN "1. Ajouter un nouvel entraînement" RESET "                                            " BOLD CYAN "||\n" RESET);
    printf(BOLD CYAN "||" RESET " " BOLD GREEN "2. Consulter l'historique des entraînements" RESET "                                  " BOLD CYAN "||\n" RESET);
    printf(BOLD CYAN "||" RESET " " BOLD GREEN "3. Consulter les statistiques et la progression d'un athlète" RESET "                 " BOLD CYAN "||\n" RESET);
    printf(BOLD CYAN "||" RESET " " BOLD GREEN "4. Voir les 3 meilleurs athlètes pour une épreuve et les envoyer aux JO" RESET "      " BOLD CYAN "||\n" RESET);
    printf(BOLD CYAN "||" RESET " " BOLD RED "5. Quitter" RESET "                                                                   " BOLD CYAN "||\n" RESET);
    afficherBordure(); // Affiche la bordure en bas du menu
}

// Fonction principale
int main() {
    setlocale(LC_ALL, "en_US.UTF-8"); // Configure la localisation pour l'affichage correct des caractères spéciaux
    int choix; // Variable pour stocker le choix de l'utilisateur
    do {
        system("clear"); // Efface la console (utilise "cls" sur Windows)
        menu(); // Affiche le menu principal
        printf("Choisissez une option : ");
        scanf("%d", &choix); // Lit le choix de l'utilisateur
        switch (choix) {
            case 1:
                // Cas pour ajouter un nouvel entraînement
                printf(BOLD CYAN "||" RESET "                " BOLD GREEN "Nouvel entrainement:" RESET "                                          " BOLD CYAN "||\n" RESET);
                ajouterEntrainement(); // Appelle la fonction pour ajouter un entraînement
                afficherBordure();
                printf(BOLD CYAN "||" RESET "                " BOLD GREEN "Nouvel entraînement ajouté avec succès!" RESET "                       " BOLD CYAN "||\n" RESET);
                afficherBordure();
                break;
            case 2:
                // Cas pour consulter l'historique des entraînements
                printf(BOLD CYAN "||" RESET "                " BOLD GREEN "Consultation de l'historique:" RESET "                                 " BOLD CYAN "||\n" RESET);
                consulterHistoriqueParCritere(); // Appelle la fonction pour consulter l'historique selon différents critères
                break;
            case 3:
                // Cas pour consulter les statistiques et la progression d'un athlète
                printf(BOLD CYAN "||" RESET "                " BOLD GREEN "Consultation des statistiques:" RESET "                                " BOLD CYAN "||\n" RESET);
                consulterStatsEtProgression(); // Appelle la fonction pour consulter les statistiques et la progression
                break;
            case 4:
                // Cas pour voir les 3 meilleurs athlètes et les envoyer aux JO
                printf(BOLD CYAN "||" RESET "                " BOLD GREEN "Selection olympique:" RESET "                                          " BOLD CYAN "||\n" RESET);
                envoyerAuxJO(); // Appelle la fonction pour envoyer les athlètes aux JO
                break;
            case 5:
                // Cas pour quitter le programme
                afficherBordure();
                printf(BOLD CYAN "||" RESET "                      " BOLD RED "Au revoir!" RESET "                                              " BOLD CYAN "||\n" RESET);
                afficherBordure();
                break;
            default:
                // Cas pour une option invalide
                afficherBordure();
                printf(BOLD CYAN "||" RESET "                " BOLD RED "Option invalide, veuillez réessayer." RESET "                            " BOLD CYAN "||\n" RESET);
                afficherBordure();
        }
        if (choix != 5) {
            printf("Appuyez sur Entrée pour continuer...");
            while (getchar() != '\n'); // Attend que l'utilisateur appuie sur Entrée
            getchar(); // Consomme le '\n' restant après scanf
        }
    } while (choix != 5); // Continue de montrer le menu jusqu'à ce que l'utilisateur choisisse de quitter

    return 0;
}

// Fonction pour consulter les statistiques des athlètes et afficher la progression
void consulterStatsEtProgression() {
    int choix;
    char nom[50], epreuve[50], date1[11], date2[11];
    
    do {
        afficherBordure(); // Affiche la bordure en haut du menu
        // Affiche les différentes options du sous-menu avec des couleurs et des styles
        printf(BOLD CYAN "||" RESET " " BOLD GREEN "1. Consulter les statistiques" RESET "                                                " BOLD CYAN "||\n" RESET);
        printf(BOLD CYAN "||" RESET " " BOLD GREEN "2. Afficher la progression d'un athlète" RESET "                                      " BOLD CYAN "||\n" RESET);
        printf(BOLD CYAN "||" RESET " " BOLD RED "3. Retour au menu principal" RESET "                                                  " BOLD CYAN "||\n" RESET);
        afficherBordure(); // Affiche la bordure en bas du sous-menu
        printf("Choisissez une option : ");
        scanf("%d", &choix); // Lit le choix de l'utilisateur
        
        switch (choix) {
            case 1:
                // Cas pour consulter les statistiques d'un athlète
                printf("Nom de l'athlète: ");
                scanf("%s", nom); // Lit le nom de l'athlète
                printf("Épreuve: ");
                scanf("%s", epreuve); // Lit le nom de l'épreuve
                afficherBordure();
                afficherStats(nom, epreuve); // Appelle la fonction pour afficher les statistiques
                afficherBordure();
                break;
            case 2:
                // Cas pour afficher la progression d'un athlète
                printf("Nom de l'athlète: ");
                scanf("%s", nom); // Lit le nom de l'athlète
                printf("Épreuve: ");
                scanf("%s", epreuve); // Lit le nom de l'épreuve
                printf("Date de début (AAAA-MM-JJ): ");
                scanf("%s", date1); // Lit la date de début
                printf("Date de fin (AAAA-MM-JJ): ");
                scanf("%s", date2); // Lit la date de fin
                
                if (!validerDate(date1) || !validerDate(date2)) {
                    // Vérifie si les dates sont valides
                    printf("Les dates entrées ne sont pas valides.\n");
                    break;
                }
                
                afficherBordure();
                afficherProgression(nom, epreuve, date1, date2); // Appelle la fonction pour afficher la progression
                afficherBordure();
                break;
            case 3:
                return; // Retourne au menu principal
            default:
                // Cas pour une option invalide
                afficherBordure();
                printf(BOLD CYAN "||" RESET "                " BOLD RED "Option invalide, retour au menu principal." RESET "          " BOLD CYAN "||\n" RESET);
                afficherBordure();
        }
        printf("Appuyez sur Entrée pour continuer...");
        while (getchar() != '\n'); // Attend que l'utilisateur appuie sur Entrée
        getchar(); // Consomme le '\n' restant après scanf
    } while (choix != 3); // Continue de montrer le sous-menu jusqu'à ce que l'utilisateur choisisse de retourner au menu principal
}
// Fonction pour consulter l'historique selon différents critères
void consulterHistoriqueParCritere() {
    int critere; // Variable pour stocker le critère choisi
    char valeur[50]; // Variable pour stocker la valeur correspondant au critère
    afficherBordure(); // Affiche la bordure en haut du sous-menu
    // Affiche les différentes options du sous-menu avec des couleurs et des styles
    printf(BOLD CYAN "||" RESET " " BOLD GREEN "1. Consulter par NOM" RESET "                                                         " BOLD CYAN "||\n" RESET);
    printf(BOLD CYAN "||" RESET " " BOLD GREEN "2. Consulter par DATE" RESET "                                                        " BOLD CYAN "||\n" RESET);
    printf(BOLD CYAN "||" RESET " " BOLD GREEN "3. Consulter par ÉPREUVE" RESET "                                                     " BOLD CYAN "||\n" RESET);
    afficherBordure(); // Affiche la bordure en bas du sous-menu
    printf("Choisissez un critère : ");
    scanf("%d", &critere); // Lit le critère choisi par l'utilisateur

    switch (critere) {
        case 1:
            // Cas pour consulter par nom
            printf("Nom de l'athlète: ");
            scanf("%s", valeur); // Lit le nom de l'athlète
            consulterHistoriqueParDateEpreuve(valeur, NULL, NULL); // Appelle la fonction pour consulter l'historique par nom
            break;
        case 2:
            // Cas pour consulter par date
            printf("Date (AAAA-MM-JJ): ");
            scanf("%s", valeur); // Lit la date
            consulterHistoriqueParDateEpreuve(NULL, valeur, NULL); // Appelle la fonction pour consulter l'historique par date
            break;
        case 3:
            // Cas pour consulter par épreuve
            printf("Epreuve: ");
            scanf("%s", valeur); // Lit le nom de l'épreuve
            consulterHistoriqueParDateEpreuve(NULL, NULL, valeur); // Appelle la fonction pour consulter l'historique par épreuve
            break;
        default:
            // Cas pour une option invalide
            afficherBordure(); // Affiche la bordure en haut
            printf(BOLD CYAN "||" RESET "                " BOLD RED "Option invalide, retour au menu principal." RESET "          " BOLD CYAN "||\n" RESET);
            afficherBordure(); // Affiche la bordure en bas
    }
}
