#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTableWidget>  // Inclure pour utiliser QTableWidget

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    // Constructeur de la classe Widget
    explicit Widget(QWidget *parent = nullptr);

    // Destructeur de la classe Widget
    ~Widget();

private:
    Ui::Widget *ui;  // Pointeur vers l'interface utilisateur générée par Qt Designer

    // Déclaration du QTableWidget pour afficher les résultats
    QTableWidget *tableWidget;  // Tableau pour afficher les données récupérées de la base de données

private slots:
    // Slot qui sera appelé lorsque l'utilisateur modifie une cellule dans le tableau
    void updateNoteInDatabase(QTableWidgetItem* item);
};

#endif // WIDGET_H

