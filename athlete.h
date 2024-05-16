
#ifndef ATHLETE_H
#define ATHLETE_H

#include "structure.h"

void ajouterEntrainement(Athlete *athlete, char date[], char type_epreuve[], float temps, int position_relais);
void consulterHistoriqueEntrainements(Athlete *athlete);
void consulterHistoriqueEntrainementsParType(Athlete *athlete, char type_epreuve[]);
void consulterHistoriqueEntrainementsParDate(Athlete *athlete, char date[]);
void consulterStatistiquesPerformance(Athlete *athlete);

#endif /* ATHLETE_H */
