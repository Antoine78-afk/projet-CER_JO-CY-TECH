const int MAX_ENTRAINEMENTS = 10;
#define MAX_athlete_relai 4



typedef struct   {
    char date [20];
    char type_epreuve[20];
    float temps;
    int position_relais;//pour le relai




} Entrainement;



typedef struct  {
    char nom[50];
    float performance;
    int nb_entrainement;
    Entrainement entrainement[MAX_ENTRAINEMENTS];


    
    
};Athlete;



typedef struct {
    char date[20];
    char type_epreuve[20];
    float temps[MAX_athlete_relai]; // Temps de chaque participant
} EntrainementRelais;
