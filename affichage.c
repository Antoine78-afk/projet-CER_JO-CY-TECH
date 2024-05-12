void menu()
{
    printf("bienvenue dans l'application  préparation jo\n");  
    printf("pour choisir un athlète, entrer son numéro associé\n");
    printf("pour choisir une épreuve entrer sa lettre associé\n\n ");


    char tab[5][20] = {"100m","200m","400m","marathon","relais 4*400"};
    for(char c = 'a';c<'a'+5;c++){
        printf("%c : %s \n",c,tab[c%97]);
    }



}
    

    





    