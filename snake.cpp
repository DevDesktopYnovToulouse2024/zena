#include "snake.h"

SnakeGame::SnakeGame() {
    //allocate the game array
    this->gameGrid = (char *)malloc(sizeof(char) * MAX_X * MAX_Y);

    //fill it with 0
    int index = MAX_X * MAX_Y - 1;
    while(index--) {
        gameGrid[index] = 0;
    }

    HEAD_X = MAX_X / 2;
    HEAD_Y = MAX_Y / 2;
}

SnakeGame::~SnakeGame() {
    free(gameGrid);
}

void SnakeGame::loadGameMap() {
    //spawn the snake facing up
    gameGrid[HEAD_X + HEAD_Y * MAX_X] = 1;
    direction = 1;
    //spawn apple after snake
    spawnApple();
}

void SnakeGame::removeTail() {
    int x = HEAD_X, y = HEAD_Y, count = 0;
    while (count != SNAKE_SIZE) {
        count++;
        //traverse the snake until you find the tail
        //limited by SNAKE_SIZE in case of oroboros
        switch (gameGrid[x + y * MAX_X]) {
        case 1:
            y -= 1;
            break;
        case 2:
            x -= 1;
            break;
        case 3:
            y += 1;
            break;
        case 4:
            x += 1;
            break;
        }
    }
    gameGrid[x + y * MAX_X] = 0;
}

int SnakeGame::loop() {
    //add segment in front of head
    int new_X = HEAD_X, new_Y = HEAD_Y;
    switch (direction) {
        case 1:
            new_Y += 1;
            break;
        case 2:
            new_X += 1;
            break;
        case 3:
            new_Y -= 1;
            break;
        case 4:
            new_X -= 1;
            break;
    }


    //check if out of bounds
    if (new_X < 0 || new_X >= MAX_X || new_Y < 0 || new_Y >= MAX_Y ||
        (gameGrid[new_X + new_Y * MAX_X] != 0 && gameGrid[new_X + new_Y * MAX_X] != 5)) {
        return -1;
    }

    if (gameGrid[new_X + new_Y * MAX_X] == 5) {
        //if the movement is on an apple position the new head
        HEAD_X = new_X;
        HEAD_Y = new_Y;
        SNAKE_SIZE++;
        gameGrid[HEAD_X + HEAD_Y * MAX_X] = direction;
        spawnApple();
    } else {
        //if its not on an apple remove the last one
        HEAD_X = new_X;
        HEAD_Y = new_Y;
        gameGrid[HEAD_X + HEAD_Y * MAX_X] = direction;
        removeTail();
    };
    return 0;
}

void SnakeGame::spawnApple() {
    int x = rand() % MAX_X,y = rand() % MAX_Y;

    while(gameGrid[x + y * MAX_X] != 0) {
        x = rand() % MAX_X;
        y = rand() % MAX_Y;
    }

    gameGrid[x + y * MAX_X] = 5;
}

void SnakeGame::keyPressEvent(QKeyEvent *event) {
    switch (event->key()) {
        case Qt::Key_Escape:
            //exit the game

            break;
        case Qt::Key_Up:
            if (gameGrid[HEAD_X + HEAD_Y * MAX_X] != 1) {
                direction = 3;
            }
            break;
        case Qt::Key_Right:
            if (gameGrid[HEAD_X + HEAD_Y * MAX_X] != 4) {
                direction = 2;
            }
            break;
        case Qt::Key_Down:
            if (gameGrid[HEAD_X + HEAD_Y * MAX_X] != 3) {
                direction = 1;
            }
            break;
        case Qt::Key_Left:
            if (gameGrid[HEAD_X + HEAD_Y * MAX_X] != 2) {
                direction = 4;
            }
            break;
    }
}
