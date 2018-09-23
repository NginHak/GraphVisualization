#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QFile>
#include<QFileDialog>
#include<QTimer>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->groupBox->setFixedWidth(270);
    ui->visual->close();
}
MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    ui->plot->close();
    ui->visual->show();
    const QString fileName = QFileDialog::getOpenFileName(this,
      "Open file",QDir::rootPath(), "excel Files (*.xlsx *.xls *.csv)");
      if (!fileName.isEmpty())
          OpenFile(fileName);
}

void MainWindow::OpenFile(const QString &fileName)
{
     QFile file(fileName);
    ui->lineEdit->setText(fileName);
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;
    else{
        ui->visual->openFile(fileName);
    }
}

void MainWindow::on_comboBox_currentIndexChanged(int index)
{
    ui->visual->createChart(index);
}

void MainWindow::on_comboBox_2_currentIndexChanged(int index)
{
    ui->visual->setTheme(index);
}
