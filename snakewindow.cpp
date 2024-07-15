#include "gamewindow.h"
#include "snakewindow.h"
#include "snake.h"

#include <QTimer>

Snakewindow::Snakewindow(QWidget *parent)
    : QMainWindow(parent) {
    auto *centralWidget = new QWidget(this);

    grid = new QGridLayout(centralWidget);
    grid->setAlignment(Qt::AlignVCenter | Qt::AlignHCenter);
    grid->setContentsMargins(300, 100, 300, 300);

    auto snake = new SnakeGame();
    snake->loadGameMap();

    int maxX = snake->getMaxX();
    int maxY = snake->getMaxY();
    gameGrid = snake->getGameGrid();

    for (int row = maxY - 1; row >= 0; --row) {
        for (int col = maxX - 1; col >= 0; --col) {
            auto *cellWidget = new QLabel(this);
            cellWidget->setFixedSize(25, 25);
            cellWidget->setStyleSheet("border: 1px solid white;");

            if (gameGrid[col + row * maxX] != 0 && gameGrid[col + row * maxX] != 5) {
                cellWidget->setStyleSheet("background-color: green;");
            }

            if (gameGrid[col + row * maxX] == 5) {
                cellWidget->setStyleSheet("background-color: red;");
            }

            grid->addWidget(cellWidget, row, col);
        }
    }

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, [this, snake] { this->updateTime(snake); });
    timer->start(1000);

    setCentralWidget(centralWidget);
    setWindowTitle("Game Launcher");
    resize(1500, 1000);
}

void Snakewindow::updateTime(SnakeGame *snake) {
    snake->loop();
    int maxX = snake->getMaxX();
    int maxY = snake->getMaxY();

    for (int row = maxY - 1; row >= 0; --row) {
        for (int col = maxX - 1; col >= 0; --col) {
            QLayoutItem* item = grid->itemAtPosition(row, col);
            if (item) {
                QLabel* cellWidget = qobject_cast<QLabel*>(item->widget());
                if (cellWidget) {
                    cellWidget->setFixedSize(25, 25);
                    cellWidget->setStyleSheet("border: 1px solid white;background-color: none;");

                    switch (gameGrid[col + row * maxX]) {
                        case 1:
                            cellWidget->setStyleSheet("background-color: green;");
                            break;
                        case 2:
                            cellWidget->setStyleSheet("background-color: blue;");
                            break;
                        case 3:
                            cellWidget->setStyleSheet("background-color: yellow;");
                            break;
                        case 4:
                            cellWidget->setStyleSheet("background-color: purple;");
                            break;
                        case 5:
                            cellWidget->setStyleSheet("background-color: red;");
                            break;
                        }
                }
            }
        }
    }
}
