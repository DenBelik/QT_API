#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QObject>
#include <QMainWindow>
#include <QInputDialog>
#include <QUrl>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QDateTime>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    int now;
    QDateTime currDateTime;
    QString location;
    QString country;
    QString currTime;
    int temperature;

    void getRequest(QUrl url);

public slots:
    void showReply(QNetworkReply *r);


private slots:
    void on_toolButton_lat_clicked();

    void on_toolButton_lon_clicked();

    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;

    float lat;
    float lon;
    const QString api_key = "68fef704-ebe6-4f79-9211-8470f91adb3f";
};
#endif // MAINWINDOW_H
