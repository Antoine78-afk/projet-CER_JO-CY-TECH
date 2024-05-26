# Introduction
Ce programme permet de gérer et de suivre les performances d'athlètes dans diverses épreuves d'athlétisme.
Il est conçu pour gérer des sportifs d'un seul genre et stocke les résultats d'entraînements dans des fichiers individuels pour chaque athlète.
Les fonctionnalités principales incluent l'enregistrement de nouveaux entraînements, la consultation de l'historique des entraînements et l'analyse des performances des athlètes. La finalté de ce programme est d'ensuite envoyer les meilleurs athtlètes avec les meilleurs performances aux  jeux Olympique.

 ### Fonctionnalités
Enregistrement des Entraînements\
Date de l'entraînement : La date à laquelle l'entraînement a eu lieu.\
Type d'épreuve : L'épreuve effectuée (100 m, 400 m, 5000 m, marathon, relais 4*400 m).\
Temps réalisé : Le temps réalisé par l'athlète.\
Position dans le relais : Pour les épreuves de relais, la position de l'athlète (1 à 4).\
Consultation de l'Historique des Entraînements\
Par athlète : Affichage de tous les entraînements d'un athlète.\
Par épreuve : Affichage des entraînements par type d'épreuve.\
Par date : Affichage des entraînements par date.\
Statistiques sur les Athlètes\
Résumé des performances : Affiche le meilleur, le pire et le temps moyen d'un athlète pour une épreuve donnée.\
Sélection pour les JO : Affiche les trois meilleurs athlètes pour chaque discipline, basé sur les meilleurs temps moyens.\
Progression des performances : Affiche la différence de temps pour une même épreuve entre deux dates.\
Structure des Fichiers\
Chaque fichier d'athlète contient une liste des entraînements sous le format suivant :(date,épreuve,temps,place dans le relais:-1 si autre sport)

 ### Améliorations possibles
Régression linéaire : Calculer l'évolution des performances d'un athlète à l'aide de la méthode des moindres carrés.\
Affichage trié : Permet de trier l'historique des entraînements par date, par ordre alphabétique de joueur, etc.\
Ajout d'épreuves : Possibilité d'ajouter de nouvelles épreuves.\
Rendre paramétrable l'emplacement des fichiers des athlètes.



### Utilisation du Programme
Entrer et sauvegarder les résultats d'un nouvel entraînement\
L'utilisateur sera invité à saisir les informations nécessaires (date, type d'épreuve, temps, position pour le relais) et ces données seront sauvegardées dans le fichier correspondant à l'athlète.

Consulter l'historique des entraînements\
L'utilisateur peut sélectionner un critère de consultation (par athlète, par épreuve ou par date) et le programme affichera les informations correspondantes.

Consulter des statistiques de performances\
L'utilisateur peut demander un résumé des performances d'un athlète, les trois meilleurs athlètes pour une discipline ou la progression des performances d'un athlète entre deux dates.
Afin de faciliter l'utilisation du programme voici la liste des athlète dèjà présent:
Antoine
