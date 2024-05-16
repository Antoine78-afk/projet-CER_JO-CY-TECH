#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>
#include "athlete.h"
#include "structure.h"
#include "athlete.c"
//void menu()
//{
    //printf("bienvenue dans l'application  préparation jo\n");  
   // printf("pour choisir un athlète, entrer son numéro associé\n");
    //printf("pour choisir une épreuve entrer sa lettre associé\n\n ");

    //création des différentes épreuves et attribution d'une lettre à chaque épreuve
    //char tab[5][20] = {"100m","200m","400m","marathon","relais 4*400"}; 
       // printf("%c : %s \n",c,tab[c%97]);
   // }




// pour que l'entraineur ajoute les entrainements    
//void ajouterEntrainement(Athlete *athlete, char date[], char type_epreuve[], float temps, int position_relais) {
int main() {
    Athlete athlete1;
    strcpy(athlete1.nom, "John Doe");
    athlete1.nb_entrainements = 0;

    ajouterEntrainement(&athlete1, "2024-05-14", "100m", 10.5, -1);
    ajouterEntrainement(&athlete1, "2024-05-15", "Relais", 0, 2);

    consulterHistoriqueEntrainements(&athlete1);
    consulterStatistiquesPerformance(&athlete1);

    return 0;
}




















