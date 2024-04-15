#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QMessageBox>

class GameWindow : public QMainWindow
{
    Q_OBJECT

public:
    GameWindow(const QString &username, const QString &password, QWidget *parent = nullptr);
    ~GameWindow();

private:
    QLabel *usernameLabel;
};

#endif // GAMEWINDOW_H

