#include "header.h"

// Fonction pour créer un athlète et initialiser ses informations
Athlete* creerAthlete(char* nom, char* prenom) {
    Athlete* athlete = (Athlete*) malloc(sizeof(Athlete));
    strcpy(athlete->nom, nom);
    strcpy(athlete->prenom, prenom);
    return athlete;
}

// Fonction pour afficher les informations d'un athlète
void afficherAthlete(Athlete* athlete) {
    printf("Nom: %s, Prénom: %s\n", athlete->nom, athlete->prenom);
}

// Fonction pour ajouter un athlète dans le fichier athletes.txt
void ajouterAthlete(char* nom) {
    FILE* athletesFile = fopen("athlete.txt", "a");
    if (athletesFile != NULL) {
        fprintf(athletesFile, "%s\n", nom);
        fclose(athletesFile);
    } else {
        printf("Erreur : Impossible d'ouvrir le fichier athletes.txt\n");
    }
}

// Vérifie si un athlète existe dans le fichier athletes.txt
int verifierAthleteExistant(char* nom) {
    FILE* athletesFile = fopen("athlete.txt", "r");
    if (athletesFile != NULL) {
        char athleteName[50];
        while (fgets(athleteName, sizeof(athleteName), athletesFile)) {
            athleteName[strcspn(athleteName, "\n")] = '\0'; // Retire le saut de ligne
            if (strcmp(athleteName, nom) == 0) {
                fclose(athletesFile);
                return 1; // Athlète trouvé
            }
        }
        fclose(athletesFile);
    }
    return 0; // Athlète non trouvé
}

// Vérifie si un athlète a déjà couru un relais à une date donnée
int verifierParticipationDuJour(char* nom, char* date) {
    char filename[60];
    sprintf(filename, "%s.txt", nom);
    FILE* file = fopen(filename, "r");
    if (file != NULL) {
        char line[100];
        while (fgets(line, sizeof(line), file)) {
            char dateLue[11], epreuveLue[50];
            sscanf(line, "%10[^,],%49[^,]", dateLue, epreuveLue);
            if (strcmp(date, dateLue) == 0 && strcmp(epreuveLue, "relais") == 0) {
                fclose(file);
                return 0; // Athlète a déjà couru un relais ce jour-là
            }
        }
        fclose(file);
    }
    return 1; // Athlète n'a pas couru un relais ce jour-là
}
// Vérifie si un relais est unique par jour
int verifierRelaisUnique(char* date) {
    FILE* athletesFile = fopen("athlete.txt", "r");
    if (athletesFile != NULL) {
        char athleteName[50];
        int relaisCount = 0;
        while (fgets(athleteName, sizeof(athleteName), athletesFile)) {
            athleteName[strcspn(athleteName, "\n")] = '\0'; // Retire le saut de ligne
            char filename[60];
            sprintf(filename, "%s.txt", athleteName);
            FILE* file = fopen(filename, "r");
            if (file != NULL) {
                char line[100];
                while (fgets(line, sizeof(line), file)) {
                    char dateLue[11], epreuveLue[50];
                    sscanf(line, "%10[^,],%49[^,]", dateLue, epreuveLue);
                    if (strcmp(date, dateLue) == 0 && strcmp(epreuveLue, "relais") == 0) {
                        relaisCount++;
                        if (relaisCount >= 4) {
                            fclose(file);
                            fclose(athletesFile);
                            return 0; // Quatre relais déjà enregistrés ce jour-là
                        }
                    }
                }
                fclose(file);
            }
        }
        fclose(athletesFile);
    }
    return 1; // Moins de quatre relais trouvés ce jour-là
}

// Vérifie la position dans un relais à une date donnée
int verifierPositionRelais(char* date, int position) {
    FILE* athletesFile = fopen("athlete.txt", "r");
    if (athletesFile != NULL) {
        char athleteName[50];
        while (fgets(athleteName, sizeof(athleteName), athletesFile)) {
            athleteName[strcspn(athleteName, "\n")] = '\0'; // Retire le saut de ligne
            char filename[60];
            sprintf(filename, "%s.txt", athleteName);
            FILE* file = fopen(filename, "r");
            if (file != NULL) {
                char line[100];
                while (fgets(line, sizeof(line), file)) {
                    char dateLue[11], epreuveLue[50];
                    int positionLue;
                    sscanf(line, "%10[^,],%49[^,],%*f,%d", dateLue, epreuveLue, &positionLue);
                    if (strcmp(date, dateLue) == 0 && strcmp(epreuveLue, "relais") == 0 && position == positionLue) {
                        fclose(file);
                        fclose(athletesFile);
                        return 0; // Position déjà occupée pour ce jour
                    }
                }
                fclose(file);
            }
        }
        fclose(athletesFile);
    }
    return 1; // Position disponible
}
