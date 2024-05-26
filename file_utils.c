#include "header.h" // Inclusion du fichier d'en-tête contenant les déclarations et les définitions partagées
#include <stdio.h> // Inclusion de la bibliothèque standard pour les opérations d'entrée/sortie
#include <stdlib.h> // Inclusion de la bibliothèque standard pour les fonctions utilitaires générales
#include <string.h> // Inclusion de la bibliothèque standard pour les opérations sur les chaînes de caractères

// Sauvegarde une performance dans un fichier
// Paramètres : nom (chaîne de caractères), performance (pointeur vers une structure Performance)
// Sauvegarde les informations de la performance dans un fichier nommé [nom].txt
void sauvegarderPerformance(char* nom, Performance* performance) {
    char filename[60]; // Buffer pour stocker le nom du fichier de l'athlète
    sprintf(filename, "%s.txt", nom); // Formate le nom du fichier en ajoutant l'extension .txt au nom de l'athlète
    FILE* file = fopen(filename, "a"); // Ouvre le fichier de l'athlète en mode ajout (append)
    if (file != NULL) { // Vérifie si le fichier a été ouvert avec succès
        // Écrit les informations de la performance dans le fichier sous forme de chaîne formatée
        fprintf(file, "%s,%s,%.2f,%d\n", performance->date, performance->epreuve, performance->temps, performance->positionRelais);
        fclose(file); // Ferme le fichier
    } else {
        printf("Erreur d'ouverture du fichier\n"); // Affiche un message d'erreur si le fichier ne peut pas être ouvert
    }
}

// Lit l'historique des performances d'un athlète
// Paramètre : nom (chaîne de caractères)
// Affiche les informations de toutes les performances de l'athlète
void lireHistorique(char* nom) {
    char filename[60]; // Buffer pour stocker le nom du fichier de l'athlète
    sprintf(filename, "%s.txt", nom); // Formate le nom du fichier en ajoutant l'extension .txt au nom de l'athlète
    FILE* file = fopen(filename, "r"); // Ouvre le fichier de l'athlète en mode lecture
    if (file != NULL) { // Vérifie si le fichier a été ouvert avec succès
        char line[100]; // Buffer pour stocker chaque ligne lue du fichier
        while (fgets(line, sizeof(line), file)) { // Lit chaque ligne du fichier
            char date[11], epreuve[50]; // Buffers pour stocker la date et l'épreuve lues depuis la ligne
            float temps; // Variable pour stocker le temps lu depuis la ligne
            int positionRelais; // Variable pour stocker la position du relais lue depuis la ligne
            // Extrait la date, l'épreuve, le temps et la position du relais de la ligne lue
            sscanf(line, "%10[^,],%49[^,],%f,%d", date, epreuve, &temps, &positionRelais);
            // Crée une nouvelle structure Performance avec les informations extraites
            Performance* performance = creerPerformance(date, epreuve, temps, positionRelais, nom);
            afficherPerformance(performance); // Affiche les informations de la performance
            free(performance); // Libère la mémoire allouée pour la structure Performance
        }
        fclose(file); // Ferme le fichier
    } else {
        printf("Pas d'historique trouvé pour cet athlète\n"); // Affiche un message si le fichier de l'athlète ne peut pas être ouvert
    }
}
