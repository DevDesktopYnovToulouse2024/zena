#ifndef SNAKE_H
#define SNAKE_H

#include <QMainWindow>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QMessageBox>
#include <QNetworkAccessManager>
#include <QKeyEvent>

class SnakeGame : public QMainWindow
{
    Q_OBJECT

public:
    SnakeGame(QWidget *parent = nullptr);
    ~SnakeGame();

private slots:
    void loadGameMap();
    void loop();

private:
    void spawnApple();
    void removeTail();
    void keyPressEvent(QKeyEvent *event) override;
    char* gameGrid;
    int score;
    int MAX_X;
    int MAX_Y;
    int HEAD_X;
    int HEAD_Y;
    int SNAKE_SIZE = 1;
    int direction;
    QGridLayout *bodyLayout;
    QLineEdit *searchField;
    QLabel *scoreText;

signals:

};


#endif // SNAKE_H
