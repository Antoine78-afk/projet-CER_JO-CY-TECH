#include "file_utils.h"

// Fonction pour sauvegarder une performance dans un fichier
void sauvegarderPerformance(char* nom, Performance* performance) {
    char filename[60]; // Variable pour stocker le nom de fichier
    sprintf(filename, "%s.txt", nom); // Formatte le nom de fichier en ajoutant ".txt" au nom de l'athlète
    FILE* file = fopen(filename, "a"); // Ouvre le fichier en mode ajout ("a")
    if (file != NULL) {
        // Si le fichier est ouvert avec succès, écrit la performance dans le fichier
        fprintf(file, "%s,%s,%.2f,%d\n", performance->date, performance->epreuve, performance->temps, performance->positionRelais);
        fclose(file); // Ferme le fichier après l'écriture
    } else {
        // Si l'ouverture du fichier échoue, affiche un message d'erreur
        printf("Erreur d'ouverture du fichier\n");
    }
}

// Fonction pour lire l'historique des performances d'un athlète depuis un fichier
void lireHistorique(char* nom) {
    char filename[60]; // Variable pour stocker le nom de fichier
    sprintf(filename, "%s.txt", nom); // Formatte le nom de fichier en ajoutant ".txt" au nom de l'athlète
    FILE* file = fopen(filename, "r"); // Ouvre le fichier en mode lecture ("r")
    if (file != NULL) {
        char line[100]; // Variable pour stocker chaque ligne lue du fichier
        while (fgets(line, sizeof(line), file)) { // Lit chaque ligne du fichier jusqu'à la fin
            char date[11], epreuve[50]; // Variables pour stocker la date et l'épreuve lues
            float temps; // Variable pour stocker le temps lu
            int positionRelais; // Variable pour stocker la position dans le relais lue
            // Parse la ligne lue et extrait les valeurs dans les variables correspondantes
            sscanf(line, "%10[^,],%49[^,],%f,%d", date, epreuve, &temps, &positionRelais);
            // Crée une nouvelle instance de Performance avec les valeurs extraites
            Performance* performance = creerPerformance(date, epreuve, temps, positionRelais);
            // Affiche la performance
            afficherPerformance(performance);
            // Libère la mémoire allouée pour la performance
            free(performance);
        }
        fclose(file); // Ferme le fichier après la lecture
    } else {
        // Si l'ouverture du fichier échoue, affiche un message d'erreur indiquant que l'historique n'a pas été trouvé
        printf("Pas d'historique trouvé pour cet athlète\n");
    }
}



