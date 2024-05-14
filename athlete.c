const int MAX_ENTRAINEMENTS = 10;
#define MAX_athlete_relai 4


//structure d'un entrainement
typedef struct   {
    char date [20];
    char type_epreuve[20];
    float temps;
    int position_relais;//pour le relai




} Entrainement;


//structure d'un athlete
typedef struct  {
    
    char *prenom;
    float performance[]
    


    
    
};Athlete;


// structure pour le relai 4*400
typedef struct {
    char date[20];
    char type_epreuve[20];
    float temps[MAX_athlete_relai]; // Temps de chaque participant
} EntrainementRelais;
