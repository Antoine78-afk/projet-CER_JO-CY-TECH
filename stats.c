#include <float.h> // Inclusion pour utiliser les constantes FLT_MAX
#include "stats.h"
#include "performance.h"
#include "file_utils.h"

// Fonction pour afficher les statistiques d'un athlète pour une épreuve donnée
void afficherStats(char* nom, char* epreuve) {
    char filename[60]; // Variable pour stocker le nom du fichier
    sprintf(filename, "%s.txt", nom); // Formatte le nom de fichier en ajoutant ".txt" au nom de l'athlète
    FILE* file = fopen(filename, "r"); // Ouvre le fichier en mode lecture ("r")
    if (file != NULL) { // Vérifie si le fichier a été ouvert avec succès
        char line[100]; // Variable pour stocker chaque ligne lue du fichier
        float meilleurTemps = FLT_MAX, pireTemps = 0, sommeTemps = 0; // Initialisation des variables pour les statistiques
        int nbEntrainements = 0; // Compteur pour le nombre d'entraînements

        while (fgets(line, sizeof(line), file)) { // Lit chaque ligne du fichier jusqu'à la fin
            char date[11], event[50]; // Variables pour stocker la date et l'épreuve lues
            float temps; // Variable pour stocker le temps lu
            int positionRelais; // Variable pour stocker la position dans le relais lue
            // Parse la ligne lue et extrait les valeurs dans les variables correspondantes
            sscanf(line, "%10[^,],%49[^,],%f,%d", date, event, &temps, &positionRelais);
            if (strcmp(event, epreuve) == 0) { // Vérifie si l'épreuve lue correspond à celle demandée
                if (temps < meilleurTemps) meilleurTemps = temps; // Met à jour le meilleur temps
                if (temps > pireTemps) pireTemps = temps; // Met à jour le pire temps
                sommeTemps += temps; // Ajoute le temps à la somme totale
                nbEntrainements++; // Incrémente le compteur d'entraînements
            }
        }
        fclose(file); // Ferme le fichier après la lecture

        if (nbEntrainements > 0) { // Vérifie si des entraînements ont été trouvés pour l'épreuve donnée
            printf("Statistiques pour %s dans l'épreuve %s:\n", nom, epreuve);
            printf("Meilleur temps: %.2f\n", meilleurTemps);
            printf("Pire temps: %.2f\n", pireTemps);
            printf("Temps moyen: %.2f\n", sommeTemps / nbEntrainements);
        } else { // Aucun entraînement trouvé pour l'épreuve donnée
            printf("Aucun entraînement trouvé pour %s dans l'épreuve %s\n", nom, epreuve);
        }
    } else { // Si l'ouverture du fichier échoue, affiche un message d'erreur
        printf("Pas d'historique trouvé pour cet athlète\n");
    }
}

