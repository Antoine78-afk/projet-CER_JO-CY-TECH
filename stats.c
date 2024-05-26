#include "header.h" // Inclusion du fichier d'en-tête contenant les déclarations et les définitions partagées
#include <float.h> // Inclusion de la bibliothèque pour les constantes de types flottants

// Affiche les statistiques des performances d'un athlète pour une épreuve donnée
// Paramètres : nom (chaîne de caractères), epreuve (chaîne de caractères)
// Affiche les meilleures, pires et moyennes performances d'un athlète pour une épreuve spécifiée
void afficherStats(char* nom, char* epreuve) {
    char filename[60]; // Buffer pour stocker le nom du fichier de l'athlète
    sprintf(filename, "%s.txt", nom); // Formate le nom du fichier
    FILE* file = fopen(filename, "r"); // Ouvre le fichier de l'athlète en mode lecture
    if (file != NULL) { // Vérifie si le fichier a été ouvert avec succès
        char line[100]; // Buffer pour stocker chaque ligne lue
        float meilleurTemps = FLT_MAX, pireTemps = 0, sommeTemps = 0; // Variables pour stocker le meilleur, le pire et la somme des temps
        int nbEntrainements = 0; // Compteur pour le nombre d'entraînements

        while (fgets(line, sizeof(line), file)) { // Lit chaque ligne du fichier
            char date[11], event[50]; // Buffers pour stocker la date et l'épreuve lues depuis la ligne
            float temps; // Variable pour stocker le temps lu depuis la ligne
            int positionRelais; // Variable pour stocker la position du relais lue depuis la ligne
            sscanf(line, "%10[^,],%49[^,],%f,%d", date, event, &temps, &positionRelais); // Extrait la date, l'épreuve, le temps et la position du relais de la ligne lue
            if (strcmp(event, epreuve) == 0) { // Vérifie si l'épreuve correspond à celle spécifiée
                if (temps < meilleurTemps) meilleurTemps = temps; // Met à jour le meilleur temps si le temps actuel est meilleur
                if (temps > pireTemps) pireTemps = temps; // Met à jour le pire temps si le temps actuel est pire
                sommeTemps += temps; // Ajoute le temps actuel à la somme des temps
                nbEntrainements++; // Incrémente le compteur d'entraînements
            }
        }
        fclose(file); // Ferme le fichier

        if (nbEntrainements > 0) { // Vérifie s'il y a des entraînements pour l'épreuve spécifiée
            printf("Statistiques pour %s dans l'épreuve %s:\n", nom, epreuve); // Affiche le titre des statistiques
            printf("Meilleur temps: %.2f\n", meilleurTemps); // Affiche le meilleur temps
            printf("Pire temps: %.2f\n", pireTemps); // Affiche le pire temps
            printf("Temps moyen: %.2f\n", sommeTemps / nbEntrainements); // Affiche le temps moyen
        } else {
            printf("Aucun entraînement trouvé pour %s dans l'épreuve %s\n", nom, epreuve); // Affiche un message si aucun entraînement n'est trouvé
        }
    } else {
        printf("Pas d'historique trouvé pour cet athlète\n"); // Affiche un message si le fichier de l'athlète ne peut pas être ouvert
    }
}

// Fonction de comparaison des athlètes par temps moyen
// Paramètres : a (pointeur vers le premier élément à comparer), b (pointeur vers le second élément à comparer)
// Retourne : -1 si le temps moyen du premier athlète est inférieur à celui du second, 1 s'il est supérieur, 0 s'ils sont égaux
int comparerAthletes(const void* a, const void* b) {
    AthletePerformance* athleteA = (AthletePerformance*)a; // Convertit le pointeur a en pointeur vers une structure AthletePerformance
    AthletePerformance* athleteB = (AthletePerformance*)b; // Convertit le pointeur b en pointeur vers une structure AthletePerformance
    if (athleteA->tempsMoyen < athleteB->tempsMoyen) return -1; // Retourne -1 si le temps moyen de l'athlète A est inférieur à celui de l'athlète B
    if (athleteA->tempsMoyen > athleteB->tempsMoyen) return 1; // Retourne 1 si le temps moyen de l'athlète A est supérieur à celui de l'athlète B
    return 0; // Retourne 0 si les temps moyens des athlètes A et B sont égaux
}

// Affiche les trois meilleurs athlètes pour chaque épreuve et les envoie aux JO
// Affiche les noms des trois meilleurs athlètes et leurs temps moyens pour l'épreuve choisie
void envoyerAuxJO() {
    char epreuve[50]; // Buffer pour stocker le nom de l'épreuve
    printf("Choisissez une épreuve (100m, 400m, 5000m, marathon, relais) : ");
    scanf("%s", epreuve); // Lit le nom de l'épreuve choisie

    if (!validerEpreuve(epreuve)) { // Vérifie si l'épreuve est valide
        printf("Epreuve invalide.\n");
        return; // Sort de la fonction si l'épreuve n'est pas valide
    }

    char athletes[100][50]; // Tableau pour stocker les noms des athlètes
    int nbAthletes = 0; // Compteur pour le nombre d'athlètes

    // Charger la liste des athlètes
    FILE* athletesFile = fopen("athlete.txt", "r"); // Ouvre le fichier athletes.txt en mode lecture
    if (athletesFile != NULL) { // Vérifie si le fichier a été ouvert avec succès
        while (fgets(athletes[nbAthletes], sizeof(athletes[nbAthletes]), athletesFile)) { // Lit chaque ligne du fichier
            athletes[nbAthletes][strcspn(athletes[nbAthletes], "\n")] = '\0'; // Retire le saut de ligne à la fin du nom
            nbAthletes++; // Incrémente le compteur d'athlètes
        }
        fclose(athletesFile); // Ferme le fichier
    } else {
        perror("Erreur lors de l'ouverture du fichier des athlètes"); // Affiche un message d'erreur si le fichier ne peut pas être ouvert
        return; // Sort de la fonction en cas d'erreur
    }

    AthletePerformance performances[100]; // Tableau pour stocker les performances des athlètes
    int nbPerformances = 0; // Compteur pour le nombre de performances

    for (int j = 0; j < nbAthletes; j++) { // Parcourt la liste des athlètes
        char filename[60]; // Buffer pour stocker le nom du fichier de l'athlète
        sprintf(filename, "%s.txt", athletes[j]); // Formate le nom du fichier
        FILE* file = fopen(filename, "r"); // Ouvre le fichier de l'athlète en mode lecture
        if (file != NULL) { // Vérifie si le fichier a été ouvert avec succès
            char line[100]; // Buffer pour stocker chaque ligne lue
            float sommeTemps = 0; // Variable pour stocker la somme des temps
            int nbEntrainements = 0; // Compteur pour le nombre d'entraînements

            while (fgets(line, sizeof(line), file)) { // Lit chaque ligne du fichier
                char date[11], event[50]; // Buffers pour stocker la date et l'épreuve lues depuis la ligne
                float temps; // Variable pour stocker le temps lu depuis la ligne
                int positionRelais; // Variable pour stocker la position du relais lue depuis la ligne
                sscanf(line, "%10[^,],%49[^,],%f,%d", date, event, &temps, &positionRelais); // Extrait la date, l'épreuve, le temps et la position du relais de la ligne lue
                if (strcmp(event, epreuve) == 0) { // Vérifie si l'épreuve correspond à celle spécifiée
                    sommeTemps += temps; // Ajoute le temps actuel à la somme des temps
                    nbEntrainements++; // Incrémente le compteur d'entraînements
                }
            }
            fclose(file); // Ferme le fichier

            if (nbEntrainements > 0) { // Vérifie s'il y a des entraînements pour l'épreuve spécifiée
                performances[nbPerformances].tempsMoyen = sommeTemps / nbEntrainements; // Calcule le temps moyen et le stocke dans la structure AthletePerformance
                strcpy(performances[nbPerformances].nom, athletes[j]); // Copie le nom de l'athlète dans la structure AthletePerformance
                nbPerformances++; // Incrémente le compteur de performances
            }
        }
    }

        // Trier les performances pour trouver les trois meilleurs
    if (nbPerformances > 0) { // Vérifie s'il y a des performances enregistrées
        qsort(performances, nbPerformances, sizeof(AthletePerformance), comparerAthletes); // Trie les performances par temps moyen en utilisant la fonction comparerAthletes

        // Afficher les trois meilleurs
        printf(BOLD GREEN "Les trois meilleurs athlètes pour l'épreuve %s sont:\n" RESET, epreuve); // Affiche un titre en vert indiquant les meilleurs athlètes pour l'épreuve spécifiée
        for (int k = 0; k < 3 && k < nbPerformances; k++) { // Parcourt les trois meilleures performances ou le nombre de performances disponibles s'il est inférieur à trois
            printf("%d. %s avec un temps moyen de %.2f\n", k + 1, performances[k].nom, performances[k].tempsMoyen); // Affiche le classement, le nom de l'athlète et son temps moyen
        }
    } else {
        printf(BOLD GREEN "Aucune performance trouvée pour l'épreuve %s.\n" RESET, epreuve); // Affiche un message en vert indiquant qu'aucune performance n'a été trouvée pour l'épreuve spécifiée
    }
}

// Affiche la progression d'un athlète pour une même épreuve entre deux dates
// Paramètres : nom (chaîne de caractères), epreuve (chaîne de caractères), date1 (chaîne de caractères), date2 (chaîne de caractères)
// Affiche l'évolution des performances d'un athlète pour une épreuve donnée entre deux dates
void afficherProgression(char* nom, char* epreuve, char* date1, char* date2) {
    char filename[60]; // Buffer pour stocker le nom du fichier de l'athlète
    sprintf(filename, "%s.txt", nom); // Formate le nom du fichier
    FILE* file = fopen(filename, "r"); // Ouvre le fichier de l'athlète en mode lecture
    if (file != NULL) { // Vérifie si le fichier a été ouvert avec succès
        char line[100]; // Buffer pour stocker chaque ligne lue
        float temps1 = -1, temps2 = -1; // Variables pour stocker les temps aux deux dates spécifiées, initialisées à -1 pour indiquer l'absence de temps

        while (fgets(line, sizeof(line), file)) { // Lit chaque ligne du fichier
            char date[11], event[50]; // Buffers pour stocker la date et l'épreuve lues depuis la ligne
            float temps; // Variable pour stocker le temps lu depuis la ligne
            int positionRelais; // Variable pour stocker la position du relais lue depuis la ligne
            sscanf(line, "%10[^,],%49[^,],%f,%d", date, event, &temps, &positionRelais); // Extrait la date, l'épreuve, le temps et la position du relais de la ligne lue
            if (strcmp(event, epreuve) == 0) { // Vérifie si l'épreuve correspond à celle spécifiée
                if (strcmp(date, date1) == 0) { // Vérifie si la date correspond à la première date spécifiée
                    temps1 = temps; // Stocke le temps de la première date
                }
                if (strcmp(date, date2) == 0) { // Vérifie si la date correspond à la deuxième date spécifiée
                    temps2 = temps; // Stocke le temps de la deuxième date
                }
            }
        }
        fclose(file); // Ferme le fichier

        if (temps1 == -1 || temps2 == -1) { // Vérifie si les temps pour les deux dates ont été trouvés
            printf("Erreur : L'athlète n'a pas de temps enregistré pour les deux dates spécifiées.\n"); // Affiche un message d'erreur si l'un des temps est manquant
        } else {
            printf("Progression de %s dans l'épreuve %s entre %s et %s : %.2f secondes\n", nom, epreuve, date1, date2, temps2 - temps1); // Affiche la progression de l'athlète entre les deux dates spécifiées
        }
    } else {
        printf("Pas d'historique trouvé pour cet athlète\n"); // Affiche un message si le fichier de l'athlète ne peut pas être ouvert
    }
}
