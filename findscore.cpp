#include "findscore.h"
#include "ui_findscore.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDebug>
#include <QMessageBox>


findscore::findscore(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::findscore)
{
    ui->setupUi(this);
    connect(ui->pushButton,&QPushButton::clicked,[=](){
        QString name=ui->lineEdit->text();
        if(!selectcount("student",name))
        {
            QMessageBox::critical(this,"提示","该生不存在");
        }else
        {
            showtable(name);
        }
    });
}

findscore::~findscore()
{
    delete ui;
}



bool findscore::selectcount(QString table,QString user)
{
    QSqlDatabase db=QSqlDatabase::database("sqlitel");
   QSqlQuery query(db);
   QString s="select count(*) from student where name='"+user+"'";
   query.exec(s);
   query.next();
   int c=query.value(0).toInt();
   if(c>0)
   {
       return true;
   }else
   {
       return false;
   }
}



QVector<QVector<QString>> findscore::queryall(QString m_table,QString name)
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



bool findscore::showtable(QString name)
{
    ui->tableWidget->setRowCount(1);
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget->setColumnCount(3);
    //ui->tableWidget->setColumnWidth(3,90);
    ui->tableWidget->setHorizontalHeaderLabels(QStringList()<<"姓名"<<"数学成绩"<<"英语成绩");
    QVector<QVector<QString>> res;
    res=queryall("student",name);
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
