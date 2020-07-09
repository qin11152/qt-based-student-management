#include "regist.h"
#include "ui_regist.h"
#include <QPushButton>
#include <QMessageBox>
#include <QtDebug>
#include <QSqlDatabase>
#include <QSqlQuery>



regist::regist(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::regist)
{
    ui->setupUi(this);
    connect(ui->pushButton,&QPushButton::clicked,[=](){
       QString acc,pass1,pass2;
       acc=ui->account->text();
       pass1=ui->password->text();
       pass2=ui->password_2->text();
       if(pass1!=pass2)
       {
           QMessageBox::critical(this,"错误","两次输入密码不同");
       }else
       {
           bool state=selectcount("stu_user_password",acc);
           if(state)
           {
               QMessageBox::critical(this,"错误","用户已存在");
           }else
           {
               bool success=insertstudent_user(acc,pass1);
               if(success)
               {
                   QMessageBox::information(this,"恭喜","注册成功");
               }else
               {
                   QMessageBox::critical(this,"错误","注册失败");
               }
           }
       }
    });
}


bool regist::connecttodatabase()
{
    QSqlDatabase db=QSqlDatabase::addDatabase("QSQLITE","sqlitel");
    db.setDatabaseName(".//qtDb.db");
    if(!db.open())
    {
        qDebug()<<"无法与数据库连接";
        return false;
    }else
    {
        //qDebug()<<"连接成功";
        return true;
    }
}


bool regist::insertstudent_user(QString name, QString pass)
{
    QSqlDatabase db=QSqlDatabase::database("sqlitel");
    QSqlQuery query(db);
    QString s="insert into stu_user_password values(?,?)";
    query.prepare(s);
    query.bindValue(0,name);
    query.bindValue(1,pass);
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



int regist::countall(QString m_table)
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




bool regist::selectcount(QString table,QString user)
{
   QSqlDatabase db=QSqlDatabase::database("sqlitel");
   QSqlQuery query(db);
   QString s="select count(*) from ";
   s+=table;
   s+=" where user=";
   s+=user;
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




regist::~regist()
{
    delete ui;
}
