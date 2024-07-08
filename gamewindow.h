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
    ~GameWindow();

private slots:
    void loadGames();
    void loadNextPage();
    void loadPrevPage();
    void searchGames();

private:
    QLabel *usernameLabel;
    QLineEdit *searchField;
    QPushButton *prevButton;
    QPushButton *nextButton;
    QGridLayout *bodyLayout;
    QNetworkAccessManager *manager;
    int currentPage;
    QString searchQuery;
};
