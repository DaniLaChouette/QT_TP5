#include "widget.h"
#include <QApplication>
#include <QtSql/QSqlDatabase>  // Inclure pour utiliser QSqlDatabase
#include <QtDebug>
#include <QtSql/QSqlQuery>     // Inclure pour exécuter des requêtes SQL
#include <QSqlError>           // Inclure pour gérer les erreurs de la base de données

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);  // Créer une instance de l'application Qt
    Widget w;                    // Créer une instance de la classe Widget
    // Initialisation de la connexion à la base de données MySQL
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");  // Spécifie le type de base de données (MySQL)
    db.setDatabaseName("jeu");   // Spécifie le nom de la base de données à utiliser

    db.setUserName("etudiant");  // Spécifie le nom d'utilisateur pour la connexion à la base de données
    db.setPassword("Passciel2"); // Spécifie le mot de passe pour la connexion à la base de données

    // Tenter d'ouvrir la connexion à la base de données
    if(db.open())
    {
        // Si la connexion est réussie, afficher le nom de l'hôte
        qDebug() << "Vous êtes maintenant connecté à " << db.hostName();

        QSqlQuery query;  // Créer un objet QSqlQuery pour exécuter une requête SQL

        // Exécuter une requête SQL pour sélectionner toutes les lignes de la table "jeu"
        query.exec("SELECT * FROM `jeu`");

        // Boucler sur les résultats de la requête
        while (query.next()) {
            QString id = query.value(0).toString();    // Récupérer la première colonne (id)
            QString Nom = query.value(1).toString();   // Récupérer la deuxième colonne (Nom)
            QString club = query.value(2).toString();  // Récupérer la troisième colonne (Club)

            // Afficher les données récupérées dans le débogueur
            qDebug() << Nom << club;
        }
        // Afficher un message indiquant que la requête a réussi
        qDebug() << "Requête ok ! :)";
        
        db.close();  // Fermer la connexion à la base de données après l'exécution de la requête
    }
    else
    {
        // Si la connexion échoue, afficher un message d'erreur
        qDebug() << "La connexion a échouée, désolé" << db.lastError().text();
    }

    w.show();  // Afficher l'interface graphique (fenêtre) de l'application
    return a.exec();  // Exécuter la boucle principale de l'application
}
