#include "gamewindow.h"

GameWindow::GameWindow(const QString &username, const QString &password, QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle("Game Window");
    resize(800, 600);

    QWidget *topBar = new QWidget(this);
    QHBoxLayout *topLayout = new QHBoxLayout(topBar);
    QLabel *usernameLabel = new QLabel("Welcome, " + username, this);
    QPushButton *prevButton = new QPushButton("Previous", this);
    QPushButton *nextButton = new QPushButton("Next", this);
    topLayout->addWidget(usernameLabel);
    topLayout->addStretch();
    topLayout->addWidget(prevButton);
    topLayout->addWidget(nextButton);

    topBar->setFixedHeight(40);

    QString topBarStyle = "QWidget {"
                          "    background-color: #4CAF50;"
                          "}";
    topBar->setStyleSheet(topBarStyle);

    QWidget *bodyWidget = new QWidget(this);
    QGridLayout *bodyLayout = new QGridLayout(bodyWidget);
    bodyLayout->setContentsMargins(10, 10, 10, 10);
    bodyLayout->setSpacing(10);

    QStringList gameTitles = {"Game 1", "Game 2", "Game 3", "Game 4", "Game 5", "Game 6"};
    QStringList gameImages = {"/home/lucas/200.jpg", "/home/lucas/200.jpg", "/home/lucas/200.jpg", "/home/lucas/200.jpg", "/home/lucas/200.jpg", "/home/lucas/200.jpg"};

    for (int i = 0; i < 6; ++i) {
        QLabel *titleLabel = new QLabel(gameTitles[i], this);
        QPixmap pixmap(gameImages[i]);
        QLabel *imageLabel = new QLabel(this);
        imageLabel->setPixmap(pixmap.scaled(150, 150, Qt::KeepAspectRatio));
        bodyLayout->addWidget(titleLabel, i / 3, i % 3, Qt::AlignCenter);
        bodyLayout->addWidget(imageLabel, i / 3, i % 3, Qt::AlignCenter);
    }

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(topBar);
    mainLayout->addWidget(bodyWidget);

    QWidget *centralWidget = new QWidget(this);
    centralWidget->setLayout(mainLayout);
    setCentralWidget(centralWidget);
}

GameWindow::~GameWindow()
{
}
