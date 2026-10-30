#include "mywidget.h"
#include "ui_mywidget.h"

#include<QFile>
#include<QDebug>
#include<QFileDialog>
#include<QTextStream>

//QString mFilename = "C:\\Users\\wecha\\OneDrive\\Desktop\\ex";

void Write(QString Filename,QString str){
    QFile mFile(Filename);
    if(!mFile.open(QFile::WriteOnly | QFile::Text)){
        qDebug()<<"could not open file for write";
        return;
    }

    QTextStream out(&mFile);
    out<<str;
    mFile.flush();
    mFile.close();


}

MyWidget::MyWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MyWidget)
{
    ui->setupUi(this);

    QStringList ColTotle;

    ui->tableWidget->setColumnCount(4);
    ColTotle<<QStringLiteral("學號")<<QStringLiteral("班級")<<QStringLiteral("姓名")<<QStringLiteral("電話");
    ui->tableWidget->setHorizontalHeaderLabels(ColTotle);


}

MyWidget::~MyWidget()
{
    delete ui;
}

void MyWidget::on_pushButton_clicked()
{
    QTableWidgetItem *inputRow1, *inputRow2, *inputRow3, *inputRow4;

    inputRow1 = new QTableWidgetItem(QString(ui->lineEdit->text()));
    inputRow2 = new QTableWidgetItem(QString(ui->lineEdit_2->text()));
    inputRow3 = new QTableWidgetItem(QString(ui->lineEdit_3->text()));
    inputRow4 = new QTableWidgetItem(QString(ui->lineEdit_4->text()));

    ui->tableWidget->insertRow(ui->tableWidget->rowCount());

    ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,0,inputRow1);
    ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,1,inputRow2);
    ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,2,inputRow3);
    ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,3,inputRow4);
}


void MyWidget::on_pushButton_2_clicked()
{
    QString fileName;
    QString saveStr;
    fileName = QFileDialog::getSaveFileName(this,"匯出通訊錄",".","CSV Files (.csv);;Text Files (.txt)");

    for(int i=0; i<ui->tableWidget->rowCount();i++)
    {
        for(int j=0; j<ui->tableWidget->columnCount();j++)
        {
            saveStr+=ui->tableWidget->item(i,j)->text()+(j<ui->tableWidget->columnCount() ? ",":"");
        }
        saveStr +="\n";
    }
    saveStr+="\n";
    Write(fileName,saveStr);
}


void MyWidget::on_pushButton_3_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, "匯入通訊錄", ".", "CSV Files (.csv);;Text Files (.txt)");

    if (fileName.isEmpty())
        return;
    QFile file(fileName);

    if (!file.open(QFile::ReadOnly | QFile::Text))
    {
        qDebug() << "Open File for reading failed!";
        return;
    }

    QTextStream in(&file);
    in.setEncoding(QStringConverter::System);
    ui->tableWidget->setRowCount(0);

    while (!in.atEnd())
    {
        QString line = in.readLine().trimmed();

        if (line.isEmpty())
            continue;

        QStringList fields = line.split(',');
        int row = ui->tableWidget->rowCount();
        ui->tableWidget->insertRow(row);

        for (int i=0; i<fields.size() && i<ui->tableWidget->columnCount();i++)
        {
            ui->tableWidget->setItem(row, i, new QTableWidgetItem(fields[i]));
        }
    }
    file.close();
}

