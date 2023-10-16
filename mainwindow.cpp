#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::getRequest(QUrl url)
{
    QNetworkAccessManager *m = new QNetworkAccessManager();
    connect(m, &QNetworkAccessManager::finished, this, &MainWindow::showReply);

    QNetworkRequest request;
    request.setRawHeader("X-Yandex-API-Key", api_key.toUtf8());
    request.setUrl(url);

    m->get(request);
}

void MainWindow::showReply(QNetworkReply *r)
{
    if (r->error()) {
        ui->textBrowser->append(r->errorString());
        return;
    }
    QString answer = r->readAll();
    //ui->textBrowser->append(answer);

    QJsonDocument jsonResponse = QJsonDocument::fromJson(answer.toUtf8());
    QJsonObject jsonObject = jsonResponse.object();
    now = jsonObject["now"].toInt();

    QJsonObject fact = jsonObject["fact"].toObject();
    temperature = fact["temp"].toInt();

    int hour = now / 3600 % 24 + 3;
    int minute = now / 60 % 60;

    if (hour > 23) {
        hour = hour - 24;
    }

    ui->textBrowser->append("Now - " + QString::number(hour) + ":" + QString::number(minute));
    ui->textBrowser->append("Temperature: " + QString::number(temperature) + " °C");
}


void MainWindow::on_toolButton_lat_clicked()
{
    double min = -90;
    double max = 90;
    int numberDecimal = 4;
    bool ok;
    QString dialogHeader = "Введите значение долготы";
    float value = 0;
    value = QInputDialog::getDouble(this, dialogHeader, "Долгота", 37.6176, min, max, numberDecimal, &ok);

    if (ok) {
        lat = value;
        ui->lineEdit_lat->setText(QString::number(lat));

    }
}

void MainWindow::on_toolButton_lon_clicked()
{
    double min = -180;
    double max = 180;
    int numberDecimal = 4;
    bool ok;
    QString dialogHeader = "Введите значение широты";
    float value = 0;
    value = QInputDialog::getDouble(this, dialogHeader, "Широта", 55.7558, min, max, numberDecimal, &ok);

    if (ok) {
        lon = value;
        ui->lineEdit_lon->setText(QString::number(lon));
    }
}

void MainWindow::on_pushButton_clicked()
{
    if (lon && lat) {
        QString str = "https://api.weather.yandex.ru/v2/forecast?lat=" + QString::number(lat) + "&lon" + QString::number(lon) + "&lang=ru_RU";
        ui->textBrowser->append(str);
        getRequest(QUrl::fromUserInput(str));
    }
    qDebug() << QSslSocket::supportsSsl() << QSslSocket::sslLibraryBuildVersionString() << QSslSocket::sslLibraryVersionString();
}
