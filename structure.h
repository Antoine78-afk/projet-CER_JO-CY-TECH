#ifndef STRUCTURES_H
#define STRUCTURES_H

#define MAX_ENTRAINEMENTS 100

typedef struct {
    char date[20];
    char type_epreuve[20];
    float temps;
    int position_relais; // Pour le relais
} Entrainement;

typedef struct {
    char nom[50];
    int nb_entrainements;
    Entrainement entrainements[MAX_ENTRAINEMENTS];
} Athlete;

#endif /* STRUCTURES_H */


