#ifndef SNAKE_H
#define SNAKE_H

#include <QMainWindow>
#include <QLabel>
#include <QLineEdit>
#include <QNetworkAccessManager>
#include <QKeyEvent>

class SnakeGame : public QMainWindow {
    Q_OBJECT

public:
    SnakeGame();
    ~SnakeGame() override;

    [[nodiscard]] int getMaxX() const { return MAX_X; };
    [[nodiscard]] int getMaxY() const { return MAX_Y; };
    [[nodiscard]] int getHeadX() const { return HEAD_X; };
    [[nodiscard]] int getHeadY() const { return HEAD_Y; };
    [[nodiscard]] char* getGameGrid() const { return gameGrid; };
    void loadGameMap();
    void loop();

private:
    void spawnApple();

    void removeTail();

    void keyPressEvent(QKeyEvent *event) override;

    char *gameGrid;
    int score;
    int MAX_X = 20;
    int MAX_Y = 20;
    int HEAD_X;
    int HEAD_Y;
    int SNAKE_SIZE = 1;
    int direction;
};


#endif // SNAKE_H
