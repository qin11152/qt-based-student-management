#include "insert.h"
#include "ui_insert.h"
#include <QPushButton>
#include <QSqlDatabase>
#include <QDebug>
#include <QSqlQuery>
#include <QMessageBox>




insert::insert(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::insert)
{
    ui->setupUi(this);
    connect(ui->pushButton_2,&QPushButton::clicked,[=](){
        this->close();
    });
    connect(ui->pushButton,&QPushButton::clicked,[=](){
        QString name=ui->name->text();
        QString math=ui->math->text();
        QString english=ui->english->text();
        bool success=insertstudent(name,math,english);
        if(success)
        {
            QMessageBox::information(this,"提示","插入成功");
        }else
        {
            QMessageBox::critical(this,"提示","插入失败");
        }
    });
}



bool insert::insertstudent(QString name, QString math, QString english)
{
    QSqlDatabase db=QSqlDatabase::database("sqlitel");
    QSqlQuery query(db);
    int shuxue=math.toInt();
    int yingyu=english.toInt();
    QString s="insert into student values(?,?,?)";
    query.prepare(s);
    query.bindValue(0,name);
    query.bindValue(1,shuxue);
    query.bindValue(2,yingyu);
    bool success=query.exec();
    if(success)
    {
        qDebug()<<"插入成功";
        return true;
    }else
    {
        qDebug()<<"插入失败";
        return false;
    }
}




bool insert::connectdatabase()
{
        QSqlDatabase db=QSqlDatabase::addDatabase("QSQLITE","sqlitel");
        db.setDatabaseName(".//qtDb.db");
        if(!db.open())
        {
            qDebug()<<"无法与数据库连接";
            return false;
        }else
        {
            //qDebug()<<"admin连接成功";
            return true;
        }
}


insert::~insert()
{
    delete ui;
}
