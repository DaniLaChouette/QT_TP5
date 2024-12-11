#include "widget.h"
#include "ui_widget.h"
#include <QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QTableWidget>
#include <QtDebug>
#include <QSqlError>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    // Initialiser le QTableWidget (tableau de données)
    tableWidget = new QTableWidget(this);
    tableWidget->setRowCount(0);  // Commencer avec 0 ligne
    tableWidget->setColumnCount(3);  // Trois colonnes (Nom, Club, Note)
    tableWidget->setHorizontalHeaderLabels(QStringList() << "Nom" << "Club" << "Note");

    // Activer l'édition des cellules (double-clic ou clic sélectionné)
    tableWidget->setEditTriggers(QAbstractItemView::DoubleClicked | QAbstractItemView::SelectedClicked);

    // Connexion à la base de données MySQL
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setDatabaseName("jeu");  // Nom de la base de données
    db.setUserName("etudiant"); // Nom d'utilisateur pour se connecter
    db.setPassword("Passciel2"); // Mot de passe pour se connecter

    // Vérification de la connexion à la base de données
    if (db.open())
    {
        qDebug() << "Connecté à la base de données."; // Affichage de confirmation dans le débogueur

        // Créer une requête SQL pour récupérer les données (nom, club, note)
        QSqlQuery query("SELECT * FROM `jeu`");

        // Remplir le QTableWidget avec les données de la base
        int row = 0;
        while (query.next()) {  // Parcours des résultats de la requête
            QString nom = query.value(1).toString();  // Récupérer le nom du joueur
            QString club = query.value(2).toString(); // Récupérer le club du joueur
            int note = query.value(3).toInt();         // Récupérer la note du joueur

            // Ajouter une nouvelle ligne dans le tableau
            tableWidget->insertRow(row);
            // Remplir les cellules de la ligne
            tableWidget->setItem(row, 0, new QTableWidgetItem(nom));
            tableWidget->setItem(row, 1, new QTableWidgetItem(club));
            tableWidget->setItem(row, 2, new QTableWidgetItem(QString::number(note)));
            row++;
        }

        // Redimensionner et positionner le tableau dans la fenêtre
        tableWidget->resize(400, 300);
        tableWidget->move(50, 50);

        // Connecter le signal 'itemChanged' (quand un élément de la table est modifié)
        connect(tableWidget, &QTableWidget::itemChanged, this, &Widget::updateNoteInDatabase);

        db.close();  // Fermer la connexion à la base de données après avoir récupéré les données
    }
    else
    {
        // Si la connexion échoue, afficher une erreur dans le débogueur
        qDebug() << "Échec de la connexion à la base de données:" << db.lastError().text();
    }
}

// Méthode pour mettre à jour la note dans la base de données lorsqu'une cellule est modifiée
void Widget::updateNoteInDatabase(QTableWidgetItem* item)
{
    // Vérifier si la colonne modifiée est la colonne "Note" (colonne 2)
    if (item->column() != 2) return;  // Si ce n'est pas la colonne "Note", ne rien faire

    // Récupérer la ligne et la nouvelle valeur de la note
    int row = item->row();
    bool ok;
    int newNote = item->text().toInt(&ok);  // Convertir la valeur de la note en entier

    if (!ok) {
        // Si la note n'est pas un entier valide, afficher un message d'erreur
        qDebug() << "La note n'est pas un entier valide";
        return;
    }

    // Récupérer le nom du joueur (colonne 0)
    QString nom = tableWidget->item(row, 0)->text();

    // Créer une nouvelle connexion à la base de données pour mettre à jour la note
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setDatabaseName("jeu");
    db.setUserName("etudiant");
    db.setPassword("Passciel2");

    // Vérification de la connexion à la base de données pour la mise à jour
    if (db.open()) {
        // Préparer la requête SQL pour mettre à jour la note du joueur
        QSqlQuery query;
        query.prepare("UPDATE `jeu` SET `Note` = :note WHERE `Nom` = :nom");
        query.bindValue(":note", newNote);  // Lier la nouvelle note
        query.bindValue(":nom", nom);       // Lier le nom du joueur

        // Exécuter la requête et vérifier si la mise à jour a réussi
        if (query.exec()) {
            qDebug() << "Nouvelle note pour" << nom << "qui passe à:" << newNote;
        } else {
            // Si l'exécution échoue, afficher une erreur
            qDebug() << "Erreur lors de la mise à jour de la note:" << query.lastError().text();
        }

        db.close();  // Fermer la connexion après la mise à jour
    } else {
        // Si la connexion échoue, afficher une erreur
        qDebug() << "Échec de la connexion pour la mise à jour de la note.";
    }
}

Widget::~Widget()
{
    delete ui;  // Libérer la mémoire utilisée par l'interface utilisateur
}
