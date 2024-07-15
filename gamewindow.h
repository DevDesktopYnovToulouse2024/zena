#pragma once
#ifndef GAME_WINDOW_H
#define GAME_WINDOW_H

#include "clickablelabel.h"
#include <QMainWindow>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QUrl>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QMessageBox>

class GameWindow : public QMainWindow
{
    Q_OBJECT

public:
    GameWindow(const QString &username, const QString &password, QWidget *parent = nullptr);
    ~GameWindow() override = default;

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

