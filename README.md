# QT_TP5
Objectif
Ce projet consiste à créer une base de données MySQL appelée jeu avec une table jeu contenant les colonnes suivantes :

    nom : le nom du joueur.
    club : le club auquel appartient le joueur.
    note : une note entre 0 et 100 pour chaque joueur.

Ensuite, nous utiliserons Qt pour créer une interface permettant de modifier la note d'un joueur, et de sauvegarder cette modification directement dans la base de données MySQL.

Avant de commencer, assurez-vous d'avoir installé les éléments suivants :
    Qt Creator : Téléchargez et installez Qt Creator.
    MySQL : Vous devez avoir une instance MySQL fonctionnelle. Si vous n'avez pas encore MySQL installé, vous pouvez le télécharger depuis MySQL.
    Driver MySQL pour Qt : Assurez-vous d'avoir installé le driver MySQL pour Qt. Cela est souvent inclus dans l'installation de Qt, mais vérifiez qu'il est bien installé dans votre version de Qt.
Maintenant, installer mes fichiers présent dans ce répertoire.

Suivez ces instruction pour éxécuter mon projet.

1. Créer la base de données MySQL
Créer la base de données jeu
    Connectez-vous à votre serveur MySQL avec un outil comme MySQL Workbench ou en utilisant la ligne de commande.
    Exécutez la commande SQL suivante pour créer la base de données et la table jeu :

CREATE DATABASE jeu;

USE jeu;

CREATE TABLE jeu (
    id INT AUTO_INCREMENT PRIMARY KEY,
    nom VARCHAR(100) NOT NULL,
    club VARCHAR(100) NOT NULL,
    note INT CHECK(note BETWEEN 0 AND 100)
);

Cette commande crée une base de données jeu et une table jeu avec les colonnes id, nom, club, et note.

1. Ouvrir le projet dans Qt Creator

    Ouvrez Qt Creator.
    Cliquez sur Fichier > Ouvrir le projet... et sélectionnez le fichier .pro de votre projet (votre-projet.pro).
    Qt Creator va analyser et configurer le projet automatiquement.

Dans mes fichier .cpp faites en sorte que la connexion à la base de donnés soit bien mis avec vos information 
