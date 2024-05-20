#include <stdio.h>
#include <stdlib.h>
#include "athlete.h"
#include "performance.h"
#include "file_utils.h"
#include "stats.h"

// Cette fonction affiche le menu principal du programme
void menu() {
    printf("Gestion des performances des athlètes\n"); // Titre du menu
    printf("1. Ajouter un nouvel entraînement\n"); // Option pour ajouter un entraînement
    printf("2. Consulter l'historique des entraînements\n"); // Option pour consulter l'historique
    printf("3. Consulter les statistiques\n"); // Option pour consulter les statistiques
    printf("4. Quitter\n"); // Option pour quitter le programme
}

int main() {
    int choix; // Variable pour stocker le choix de l'utilisateur
    do {
        menu(); // Appelle la fonction pour afficher le menu
        printf("Choisissez une option : "); // Demande à l'utilisateur de choisir une option
        scanf("%d", &choix); // Lit le choix de l'utilisateur
        switch (choix) { // Exécute une action en fonction du choix de l'utilisateur
            case 1:
                ajouterEntrainement(); // Appelle la fonction pour ajouter un entraînement
                break;
            case 2:
                consulterHistorique(); // Appelle la fonction pour consulter l'historique des entraînements
                break;
            case 3:
                consulterStats(); // Appelle la fonction pour consulter les statistiques
                break;
            case 4:
                printf("Au revoir!\n"); // Message de sortie
                break;
            default:
                printf("Option invalide, veuillez réessayer.\n"); // Message pour un choix invalide
        }
    } while (choix != 4); // Répète le menu jusqu'à ce que l'utilisateur choisisse de quitter

    return 0; // Retourne 0 pour indiquer que le programme s'est terminé correctement
}


