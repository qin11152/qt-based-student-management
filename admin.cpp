#include "admin.h"
#include "ui_admin.h"
#include <QTableWidget>
#include "mainwindow.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDebug>
#include <QSqlRecord>
#include <QVector>
#include <QtNetwork>
#include "insert.h"
#include "updatescore.h"
#include "findscore.h"


//stu_user_password user_password student



admin::admin(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::admin)
{
    ui->setupUi(this);
    //connectdatabase();
    showtable();
    connect(ui->refresh,&QPushButton::clicked,[=](){
        showtable();
    });
    connect(ui->insert,&QPushButton::clicked,[=](){
       insert* son=new insert();
       son->show();
    });
    connect(ui->update,&QPushButton::clicked,[=](){
       updatescore *updat=new updatescore();
       updat->show();
    });
    connect(ui->find,&QPushButton::clicked,[=](){
        findscore *fin=new findscore();
        fin->show();
    });
}



bool admin::showtable()
{
    ui->tableWidget->setRowCount(countall("student"));
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget->setColumnCount(3);
    //ui->tableWidget->setColumnWidth(3,90);
    ui->tableWidget->setHorizontalHeaderLabels(QStringList()<<"姓名"<<"数学成绩"<<"英语成绩");
    QVector<QVector<QString>> res;
    res=queryall("student");
    for(int i=0;i<res.size();i++)
    {
        for(int j=0;j<res[i].size();j++)
        {
            ui->tableWidget->setItem(i,j,new QTableWidgetItem(res[i][j]));
        }
    }
    res.clear();
    return true;
}


bool admin::connectdatabase()
{
    QSqlDatabase db=QSqlDatabase::addDatabase("QSQLITE","sqlitel");
    db.setDatabaseName(".//qtDb.db");
    if(!db.open())
    {
        qDebug()<<"无法与数据库连接";
        return false;
    }else
    {
        qDebug()<<"admin连接成功";
        return true;
    }
}




int admin::countall(QString m_table)
{
    QSqlDatabase db=QSqlDatabase::database("sqlitel");
    QSqlQuery query(db);
    QString s="select count(*) from ";
    s+=m_table;
    query.exec(s);
    query.next();
    int res=query.value(0).toInt();
    return res;
}



QVector<QVector<QString>> admin::queryall(QString m_table)
{
    QSqlDatabase db=QSqlDatabase::database("sqlitel");
    QString s;
    s+="select * from ";
    s+=m_table;
    QSqlQuery query(db);
    query.exec(s);
    QSqlRecord record=query.record();
    int c=countall(m_table);
    qDebug()<<"c:"<<c;
    QVector<QVector<QString>> res(c);
    int i=0;
    while(i<c)
    {
        query.next();
        for(int j=0;j<3;j++)
        {
            qDebug()<<query.value(j).toString();
            res[i].push_back(query.value(j).toString());
        }
        i++;
    }
    return res;
}







admin::~admin()
{
    delete ui;
}
