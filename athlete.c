#include "header.h" // Inclusion du fichier d'en-tête contenant les déclarations et les définitions partagées

// Fonction pour créer un athlète et initialiser ses informations
// Paramètres : nom (chaîne de caractères), prenom (chaîne de caractères)
// Retourne : un pointeur vers une structure Athlete nouvellement créée
Athlete* creerAthlete(char* nom, char* prenom) {
    Athlete* athlete = (Athlete*) malloc(sizeof(Athlete)); // Alloue de la mémoire pour un nouvel athlète
    strcpy(athlete->nom, nom); // Copie le nom fourni dans le champ nom de la structure Athlete
    strcpy(athlete->prenom, prenom); // Copie le prénom fourni dans le champ prénom de la structure Athlete
    return athlete; // Retourne le pointeur vers la structure Athlete nouvellement créée
}

// Fonction pour afficher les informations d'un athlète
// Paramètre : athlete (pointeur vers une structure Athlete)
// Affiche le nom et le prénom de l'athlète au format "Nom: [nom], Prénom: [prénom]"
void afficherAthlete(Athlete* athlete) {
    printf("Nom: %s, Prénom: %s\n", athlete->nom, athlete->prenom); // Affiche les informations de l'athlète
}

// Fonction pour ajouter un athlète dans le fichier athletes.txt
// Paramètre : nom (chaîne de caractères)
// Ajoute le nom de l'athlète à la fin du fichier athletes.txt
void ajouterAthlete(char* nom) {
    FILE* athletesFile = fopen("athlete.txt", "a"); // Ouvre le fichier athletes.txt en mode ajout
    if (athletesFile != NULL) { // Vérifie si le fichier a été ouvert avec succès
        fprintf(athletesFile, "%s\n", nom); // Écrit le nom de l'athlète dans le fichier
        fclose(athletesFile); // Ferme le fichier
    } else {
        printf("Erreur : Impossible d'ouvrir le fichier athletes.txt\n"); // Affiche un message d'erreur si le fichier ne peut pas être ouvert
    }
}

// Vérifie si un athlète existe dans le fichier athletes.txt
// Paramètre : nom (chaîne de caractères)
// Retourne : 1 si l'athlète existe, 0 sinon
int verifierAthleteExistant(char* nom) {
    FILE* athletesFile = fopen("athlete.txt", "r"); // Ouvre le fichier athletes.txt en mode lecture
    if (athletesFile != NULL) { // Vérifie si le fichier a été ouvert avec succès
        char athleteName[50]; // Buffer pour stocker le nom de l'athlète lu depuis le fichier
        while (fgets(athleteName, sizeof(athleteName), athletesFile)) { // Lit chaque ligne du fichier
            athleteName[strcspn(athleteName, "\n")] = '\0'; // Retire le saut de ligne à la fin du nom
            if (strcmp(athleteName, nom) == 0) { // Compare le nom lu avec le nom recherché
                fclose(athletesFile); // Ferme le fichier
                return 1; // Retourne 1 si l'athlète est trouvé
            }
        }
        fclose(athletesFile); // Ferme le fichier si l'athlète n'est pas trouvé
    }
    return 0; // Retourne 0 si l'athlète n'est pas trouvé
}

// Vérifie si un athlète a déjà couru un relais à une date donnée
// Paramètres : nom (chaîne de caractères), date (chaîne de caractères)
// Retourne : 1 si l'athlète n'a pas couru un relais ce jour-là, 0 sinon
int verifierParticipationDuJour(char* nom, char* date) {
    char filename[60]; // Buffer pour stocker le nom du fichier de l'athlète
    sprintf(filename, "%s.txt", nom); // Formate le nom du fichier
    FILE* file = fopen(filename, "r"); // Ouvre le fichier de l'athlète en mode lecture
    if (file != NULL) { // Vérifie si le fichier a été ouvert avec succès
        char line[100]; // Buffer pour stocker chaque ligne lue
        while (fgets(line, sizeof(line), file)) { // Lit chaque ligne du fichier
            char dateLue[11], epreuveLue[50]; // Buffers pour stocker la date et l'épreuve lues depuis la ligne
            sscanf(line, "%10[^,],%49[^,]", dateLue, epreuveLue); // Extrait la date et l'épreuve de la ligne lue
            if (strcmp(date, dateLue) == 0 && strcmp(epreuveLue, "relais") == 0) { // Vérifie si l'athlète a couru un relais ce jour-là
                fclose(file); // Ferme le fichier
                return 0; // Retourne 0 si l'athlète a déjà couru un relais ce jour-là
            }
        }
        fclose(file); // Ferme le fichier
    }
    return 1; // Retourne 1 si l'athlète n'a pas couru un relais ce jour-là
}

// Vérifie si un relais est unique par jour
// Paramètre : date (chaîne de caractères)
// Retourne : 1 si moins de quatre relais sont trouvés ce jour-là, 0 sinon
int verifierRelaisUnique(char* date) {
    FILE* athletesFile = fopen("athlete.txt", "r"); // Ouvre le fichier athletes.txt en mode lecture
    if (athletesFile != NULL) { // Vérifie si le fichier a été ouvert avec succès
        char athleteName[50]; // Buffer pour stocker le nom de l'athlète lu depuis le fichier
        int relaisCount = 0; // Compteur pour le nombre de relais trouvés ce jour-là
        while (fgets(athleteName, sizeof(athleteName), athletesFile)) { // Lit chaque ligne du fichier
            athleteName[strcspn(athleteName, "\n")] = '\0'; // Retire le saut de ligne à la fin du nom
            char filename[60]; // Buffer pour stocker le nom du fichier de l'athlète
            sprintf(filename, "%s.txt", athleteName); // Formate le nom du fichier
            FILE* file = fopen(filename, "r"); // Ouvre le fichier de l'athlète en mode lecture
            if (file != NULL) { // Vérifie si le fichier a été ouvert avec succès
                char line[100]; // Buffer pour stocker chaque ligne lue
                while (fgets(line, sizeof(line), file)) { // Lit chaque ligne du fichier
                    char dateLue[11], epreuveLue[50]; // Buffers pour stocker la date et l'épreuve lues depuis la ligne
                    sscanf(line, "%10[^,],%49[^,]", dateLue, epreuveLue); // Extrait la date et l'épreuve de la ligne lue
                    if (strcmp(date, dateLue) == 0 && strcmp(epreuveLue, "relais") == 0) { // Vérifie si un relais est trouvé ce jour-là
                        relaisCount++; // Incrémente le compteur de relais
                        if (relaisCount >= 4) { // Vérifie si quatre relais sont déjà trouvés
                            fclose(file); // Ferme le fichier de l'athlète
                            fclose(athletesFile); // Ferme le fichier athletes.txt
                            return 0; // Retourne 0 si quatre relais sont trouvés
                        }
                    }
                }
                fclose(file); // Ferme le fichier de l'athlète
            }
        }
        fclose(athletesFile); // Ferme le fichier athletes.txt
    }
    return 1; // Retourne 1 si moins de quatre relais sont trouvés ce jour-là
}

// Vérifie la position dans un relais à une date donnée
// Paramètres : date (chaîne de caractères), position (entier)
// Retourne : 1 si la position est disponible, 0 sinon
int verifierPositionRelais(char* date, int position) {
    FILE* athletesFile = fopen("athlete.txt", "r"); // Ouvre le fichier athletes.txt en mode lecture
    if (athletesFile != NULL) { // Vérifie si le fichier a été ouvert avec succès
        char athleteName[50]; // Buffer pour stocker le nom de l'athlète lu depuis le fichier
        while (fgets(athleteName, sizeof(athleteName), athletesFile)) { // Lit chaque ligne du fichier
            athleteName[strcspn(athleteName, "\n")] = '\0'; // Retire le saut de ligne à la fin du nom
            char filename[60]; // Buffer pour stocker le nom du fichier de l'athlète
            sprintf(filename, "%s.txt", athleteName); // Formate le nom du fichier
            FILE* file = fopen(filename, "r"); // Ouvre le fichier de l'athlète en mode lecture
            if (file != NULL) { // Vérifie si le fichier a été ouvert avec succès
                char line[100]; // Buffer pour stocker chaque ligne lue
                while (fgets(line, sizeof(line), file)) { // Lit chaque ligne du fichier
                    char dateLue[11], epreuveLue[50]; // Buffers pour stocker la date et l'épreuve lues depuis la ligne
                    int positionLue; // Variable pour stocker la position lue depuis la ligne
                    sscanf(line, "%10[^,],%49[^,],%*f,%d", dateLue, epreuveLue, &positionLue); // Extrait la date, l'épreuve et la position de la ligne lue
                    if (strcmp(date, dateLue) == 0 && strcmp(epreuveLue, "relais") == 0 && position == positionLue) { // Vérifie si la position est déjà occupée pour ce jour
                        fclose(file); // Ferme le fichier de l'athlète
                        fclose(athletesFile); // Ferme le fichier athletes.txt
                        return 0; // Retourne 0 si la position est déjà occupée pour ce jour
                    }
                }
                fclose(file); // Ferme le fichier de l'athlète
            }
        }
        fclose(athletesFile); // Ferme le fichier athletes.txt
    }
    return 1; // Retourne 1 si la position est disponible
}
