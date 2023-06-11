
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <curl/curl.h>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //Call function on start
    FetchData();
}

MainWindow::~MainWindow()
{
    delete ui;
}

size_t WriteCallback(char *contents, size_t size, size_t nmemb, void *userp)
{
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

void MainWindow::FetchData(){
    CURL* easyhandle = curl_easy_init();
    std::string readBuffer;

    curl_easy_setopt(easyhandle, CURLOPT_URL, "https://jsonplaceholder.typicode.com/todos");
    curl_easy_setopt(easyhandle, CURLOPT_SSL_VERIFYPEER, false);
    curl_easy_setopt(easyhandle, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(easyhandle, CURLOPT_WRITEDATA, &readBuffer);

    curl_easy_perform(easyhandle);

    //Parse JSON object
    QJsonDocument jsonResponse = QJsonDocument::fromJson(readBuffer.c_str());
    QJsonArray jsonArray = jsonResponse.array();

    //Sets tableWidget row count
    ui->tableWidget->setRowCount(jsonArray.count());
    int currentRow = 0;
    for (int var = 0; var < jsonArray.count(); ++var) {
        //qDebug() << jsonArray[var].toObject()["id"].toInt();
        //qDebug() << jsonArray[var].toObject()["title"].toString();

        ui->tableWidget->setItem(currentRow, 0, new QTableWidgetItem(QString::number(jsonArray[var].toObject()["id"].toInt())));
        ui->tableWidget->setItem(currentRow, 1, new QTableWidgetItem((jsonArray[var].toObject()["title"].toString())));
        currentRow = currentRow + 1;
    }
}
