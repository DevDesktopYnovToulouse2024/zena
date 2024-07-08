#include "gamewindow.h"
#include "snakewindow.h"

Snakewindow::Snakewindow(QWidget *parent)
    : QMainWindow(parent) {
    auto *centralWidget = new QWidget(this);
    auto *grid = new QGridLayout(centralWidget);
    grid->setAlignment(Qt::AlignVCenter | Qt::AlignHCenter);
    grid->setContentsMargins(300, 100, 300, 300);

    for (int row = 0; row < 20; ++row) {
        for (int col = 0; col < 20; ++col) {
            auto *cellWidget = new QLabel(this);
            cellWidget->setFixedSize(25, 25); // Set the size of each cell
            cellWidget->setStyleSheet("border: 1px solid white;"); // Add border to each cell
            grid->addWidget(cellWidget, row, col);
        }
    }

    setCentralWidget(centralWidget);
    setWindowTitle("Game Launcher");
    resize(1500, 1000);
}
