#include "stuwindow.h"
#include "ui_stuwindow.h"


#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDebug>
#include <QSqlRecord>


stuwindow::stuwindow(QWidget *parent,QString m_name) :
    QWidget(parent),
    ui(new Ui::stuwindow),
    name(m_name)
{
    ui->setupUi(this);
    showtable();
}

stuwindow::~stuwindow()
{
    delete ui;
}

QVector<QVector<QString>> stuwindow::queryall(QString m_table)
{
    QSqlDatabase db=QSqlDatabase::database("sqlitel");
    QString s;
    s+="select * from ";
    s+=m_table;
    s+=" where name =";
    QString nam="'";
    nam+=name;
    nam+="'";
    s+=nam;
    QSqlQuery query(db);
    query.exec(s);
    QVector<QVector<QString>> res(1);
    int i=0;
    while(i<1)
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



bool stuwindow::showtable()
{
    ui->tableWidget->setRowCount(1);
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
