#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QMessageBox>
#include <QNetworkAccessManager>

class GameWindow : public QMainWindow
{
    Q_OBJECT

public:
    GameWindow(const QString &username, const QString &password, QWidget *parent = nullptr);
    ~GameWindow();

private slots:
    void loadGames();
    void loadNextPage();
    void loadPrevPage();
    void searchGames();

private:
    int currentPage;
    QString searchQuery;
    QNetworkAccessManager *manager;
    QGridLayout *bodyLayout;
    QPushButton *prevButton;
    QPushButton *nextButton;
    QLineEdit *searchField;
    QLabel *usernameLabel;
};


#endif // GAMEWINDOW_H

