#include "gamewindow.h"
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QUrl>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

GameWindow::GameWindow(const QString &username, const QString &password, QWidget *parent)
    : QMainWindow(parent), currentPage(1), searchQuery("")
{
    setWindowTitle("Game Window");
    resize(800, 600);

    QWidget *topBar = new QWidget(this);
    QHBoxLayout *topLayout = new QHBoxLayout(topBar);
    usernameLabel = new QLabel("Welcome, " + username, this);
    searchField = new QLineEdit(this);
    searchField->setPlaceholderText("Search for a game...");
    prevButton = new QPushButton("Previous", this);
    nextButton = new QPushButton("Next", this);
    topLayout->addWidget(usernameLabel);
    topLayout->addWidget(searchField);
    topLayout->addStretch();
    topLayout->addWidget(prevButton);
    topLayout->addWidget(nextButton);

    topBar->setFixedHeight(40);

    QString topBarStyle = "QWidget {"
                          "    background-color: #4CAF50;"
                          "}";
    topBar->setStyleSheet(topBarStyle);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    bodyLayout = new QGridLayout(this);
    bodyLayout->setContentsMargins(10, 10, 10, 10);
    bodyLayout->setSpacing(10);

    mainLayout->addWidget(topBar);
    mainLayout->addLayout(bodyLayout);

    QWidget *centralWidget = new QWidget(this);
    centralWidget->setLayout(mainLayout);
    setCentralWidget(centralWidget);

    manager = new QNetworkAccessManager(this);

    connect(nextButton, &QPushButton::clicked, this, &GameWindow::loadNextPage);
    connect(prevButton, &QPushButton::clicked, this, &GameWindow::loadPrevPage);
    connect(searchField, &QLineEdit::returnPressed, this, &GameWindow::searchGames);

    loadGames();
}

void GameWindow::loadGames()
{
    QString apiUrl = QString("https://api.rawg.io/api/games?key=b4da2c8394a949d1a89335b73419c932&page=%1&page_size=6").arg(currentPage);
    if (!searchQuery.isEmpty()) {
        apiUrl += "&search=" + QUrl::toPercentEncoding(searchQuery);
    }
    QUrl url(apiUrl);

    QNetworkReply *reply = manager->get(QNetworkRequest(url));

    connect(reply, &QNetworkReply::finished, this, [=]() {
        if (reply->error() == QNetworkReply::NoError) {
            QByteArray data = reply->readAll();
            QJsonDocument jsonDoc = QJsonDocument::fromJson(data);

            if (jsonDoc.isObject()) {
                QJsonObject jsonObj = jsonDoc.object();

                if (jsonObj.contains("results")) {
                    QJsonArray gamesArray = jsonObj["results"].toArray();

                    QLayoutItem *child;
                    while ((child = bodyLayout->takeAt(0)) != nullptr) {
                        delete child->widget();
                        delete child;
                    }

                    for (int i = 0; i < gamesArray.size(); ++i) {
                        QJsonObject gameObj = gamesArray[i].toObject();
                        QString imageUrl = gameObj["background_image"].toString();
                        QLabel *imageLabel = new QLabel(this);
                        QLabel *nameLabel = new QLabel(gameObj["name"].toString());

                        int row = i / 3;
                        int col = i % 3;

                        bodyLayout->addWidget(imageLabel, row * 2, col);
                        bodyLayout->addWidget(nameLabel, row * 2 + 1, col);

                        QNetworkAccessManager *imageManager = new QNetworkAccessManager(this);
                        QUrl url(imageUrl);
                        QNetworkReply *reply = imageManager->get(QNetworkRequest(url));

                        connect(reply, &QNetworkReply::finished, this, [=]() {
                            if (reply->error() == QNetworkReply::NoError) {
                                QByteArray imageData = reply->readAll();
                                QPixmap pixmap;
                                if (pixmap.loadFromData(imageData)) {
                                    imageLabel->setPixmap(pixmap.scaled(150, 150, Qt::KeepAspectRatio));
                                } else {
                                    qDebug() << "Failed to load pixmap from data";
                                }
                            } else {
                                qDebug() << "Error:" << reply->errorString();
                            }
                            reply->deleteLater();
                        });
                    }
                }
            }
        } else {
            qDebug() << "Error:" << reply->errorString();
        }
        reply->deleteLater();
    });
}

void GameWindow::loadNextPage()
{
    ++currentPage;
    loadGames();
}

void GameWindow::loadPrevPage()
{
    if (currentPage > 1) {
        --currentPage;
        loadGames();
    }
}

void GameWindow::searchGames()
{
    searchQuery = searchField->text();
    currentPage = 1;
    loadGames();
}
