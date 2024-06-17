#include "mainwindow.h"
#include "gamewindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    QWidget *centralWidget = new QWidget(this);
    QVBoxLayout *layout = new QVBoxLayout(centralWidget);
    layout->setAlignment(Qt::AlignVCenter);
    layout->setAlignment(Qt::AlignHCenter);
    layout->setContentsMargins(300, 100, 300, 300);

    QLabel *logoLabel = new QLabel(this);
    QPixmap logoPixmap("/home/lucas/firstApp/logo_zena.png");
    logoPixmap = logoPixmap.scaled(200, 200, Qt::KeepAspectRatio);

    logoLabel->setPixmap(logoPixmap);
    logoLabel->resize(200,200);

    usernameLineEdit = new QLineEdit(this);
    usernameLineEdit->setPlaceholderText("Username");
    usernameLineEdit->setAlignment(Qt::AlignCenter);
    usernameLineEdit->setFixedWidth(200);

    passwordLineEdit = new QLineEdit(this);
    passwordLineEdit->setPlaceholderText("Password");
    passwordLineEdit->setEchoMode(QLineEdit::Password);
    passwordLineEdit->setAlignment(Qt::AlignCenter);
    passwordLineEdit->setFixedWidth(200);

    QPushButton *startButton = new QPushButton("Start Game", this);
    connect(startButton, &QPushButton::clicked, this, &MainWindow::startGame);

    QString inputStyle = "QLineEdit {"
                         "    border: 2px solid #ccc;"
                         "    border-radius: 5px;"
                         "    padding: 8px;"
                         "    font-size: 16px;"
                         "}";
    usernameLineEdit->setStyleSheet(inputStyle);
    passwordLineEdit->setStyleSheet(inputStyle);

    QString buttonStyle = "QPushButton {"
                          "    background-color: #4CAF50;"
                          "    color: white;"
                          "    padding: 10px 20px;"
                          "    border: none;"
                          "    border-radius: 5px;"
                          "    font-size: 16px;"
                          "}";
    startButton->setStyleSheet(buttonStyle);

    layout->addWidget(logoLabel);
    layout->addWidget(usernameLineEdit);
    layout->addWidget(passwordLineEdit);
    layout->addWidget(startButton);

    setCentralWidget(centralWidget);
    setWindowTitle("Game Launcher");
    resize(1500,1000);
}


MainWindow::~MainWindow()
{
}

void MainWindow::startGame()
{
    QString username = usernameLineEdit->text();
    QString password = passwordLineEdit->text();

    if (username == "Lucas" && password == "password") {
        GameWindow *gameWindow = new GameWindow(username, password);
        gameWindow->show();
        close();
    } else {
        attempts++;

        if (attempts >= 5) {
            QMessageBox::critical(this, "Too many attempts", "Too many login attempts. Closing the application.");
            close();
        } else {
            QMessageBox::warning(this, "Incorrect credentials", "Incorrect username or password. Please try again.");
        }
    }
}
