# Lucas Cheekhooree 

## Contribution
- Ajout des murs avec Loïc
  - ajout des coordonnées
- Collision avec dots et energizers
  - collision avec entité. Ajout au stat retire du vecteur et à la prochaine actualisation l'objet n'existe plus
- Direction du personnage
  - adoussissement de la direction pour simplifier le jeu
    - prise en compte de la direction souhaité. Entité va essayé d'aller dans la direction se qui évite au joueur de s'aligner au pixel prêt
- IA fantome
  - Direction aléatoire en fonction des possibilité
    - Utile dans le cas d'une intersection en croix. Car la deuzième fonction ne cherche pas de direction tant que l'entité n'est pas bloqué. Du coup cette fonction permet de voir si il a un autre chemin
  - si bloqué test différentres directions
    - fonction basique qui teste si l'entité est bloqué sur la même position. Si oui elle cherche toutes les directions
- Code rendu plus objet
  - création des bases de classes entity, person, player, ghost
    - Création de base d'une architecture pour rendre le code le plus objet possible
  - collision pacgomme & energizer déplacer dans un class player
    - collision préablement mis dans pacman.cpp. Modification des classes et des méthodes pour qu'elle soit gérer côté Player
  - animation déplacer dans person
    - animation d'abord divisé en deux parties dans main. Créait des bugs d'affichage en plus. Tout a été rendu objet et gérer par Person
- reset Game
  - ré-initiliasition des status / etat / entité