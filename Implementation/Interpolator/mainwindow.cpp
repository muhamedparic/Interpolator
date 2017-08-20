#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "test/test_diamond_search.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    Test_diamond_search();
}
