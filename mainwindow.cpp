#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlRecord>
#include "admin.h"
#include <QMessageBox>
#include <regist.h>
#include "stuwindow.h"



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    connectdatabase();
    //qDebug()<<countall("user_password");
    //selectcount("xy");
    //deletetable("stu_user_password");
    //createtable();
    //insertintodatabase();
    //deletedata("user_password");
    //queryall("stu_user_password");
    //checkpassword("'xyc'","qinbiao");
    //updatescore("谢亚超");
    ui->setupUi(this);
    connect(ui->zhuce,&QPushButton::clicked,[=](){
       regist *regis=new regist();
       regis->show();
    });
    connect(ui->pushButton,&QPushButton::clicked,[=](){
        if(ui->radioButton->isChecked())
        {
            QString user,password;
            user+="'";
            user+=ui->lineEdit->text();
            user+="'";
            password+=ui->lineEdit_2->text();
            if(!selectcount("user_password",user))
            {
                QMessageBox::critical(this,"错误","用户不存在");
            }else
            {
            if(checkpassword("user_password",user,password))
            {
                admin* administer=new admin();
                administer->show();
            }else
            {
                QMessageBox::critical(this,"错误","密码错误");
            }
            }
        }else
        {
            QString user,password;
            QString user1;
            user1=ui->lineEdit->text();
            user+="'";
            user+=ui->lineEdit->text();
            user+="'";
            password+=ui->lineEdit_2->text();
            if(!selectcount("stu_user_password",user))
            {
                QMessageBox::critical(this,"错误","用户不存在");
            }else
            {
                if(checkpassword("stu_user_password",user,password))
                {
                    qDebug()<<"yes";
                    stuwindow *stu=new stuwindow(nullptr,user1);
                    stu->show();
                }else
                {
                    qDebug()<<"false";
                }
            }
        }
        //this->close();
    });
}

bool MainWindow::connectdatabase()
{
    QSqlDatabase db=QSqlDatabase::addDatabase("QSQLITE","sqlitel");
    db.setDatabaseName(".//qtDb.db");
    if(!db.open())
    {
        qDebug()<<"无法与数据库连接";
        return false;
    }else
    {
        qDebug()<<"连接成功";
        return true;
    }
}


bool MainWindow::createtable()
{
    QSqlDatabase db=QSqlDatabase::database("sqlitel");
    QSqlQuery query(db);
    bool success=query.exec("create table stu_user_password(user varchar(30) primary key,password varchar(40))");
    if(success)
    {
        qDebug()<<"创建表成功";
        return true;
    }else
    {
        qDebug()<<"创建表失败";
        return false;
    }
}


bool MainWindow::insertintodatabase()
{
    QSqlDatabase db=QSqlDatabase::database("sqlitel");
    QSqlQuery query(db);
    query.prepare("insert into student values(?,?,?)");
    query.bindValue(0,"xieyachao");
    query.bindValue(1,10);
    query.bindValue(2,20);
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


bool MainWindow::queryall(QString m_table)
{
    QSqlDatabase db=QSqlDatabase::database("sqlitel");
    QString s;
    s+="select * from ";
    s+=m_table;
    QSqlQuery query(db);
    query.exec(s);
    QSqlRecord record=query.record();
    qDebug()<<"表子段数"<<record.count();
    while(query.next())
    {
        qDebug()<<query.value(0).toString()<<" "<<query.value(1).toString()<<" "<<query.value(2).toString();
    }
    return true;
}



bool MainWindow::deletetable(QString m_table)
{
    QSqlDatabase db=QSqlDatabase::database("sqlitel");
    QSqlQuery query(db);
    QString s="drop table stu_user_password";
    bool success=query.exec(s);
    if(success)
    {
        qDebug()<<"删除表成功";
        return true;
    }else
    {
        qDebug()<<"删除失败";
        return false;
    }
}


bool MainWindow::checkpassword(QString table,QString user,QString password)
{
    QString s="select * from ";
    s+=table;
    s+=" where user=";
    s+=user;
    qDebug()<<s;
    QSqlDatabase db=QSqlDatabase::database("sqlitel");
    QSqlQuery query(db);
    query.exec(s);
    query.next();
    QString pass=query.value(1).toString();
    qDebug()<<pass;
    if(password==pass)
    {
        return true;
    }
    return false;
}






bool MainWindow::selectcount(QString table,QString user)
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



int MainWindow::countall(QString m_table)
{
    QSqlDatabase db=QSqlDatabase::database("sqlitel");
    QSqlQuery query(db);
    QString s="select count(*) from user_password";
    query.exec(s);
    query.next();
    int res=query.value(0).toInt();
    return res;
}



bool MainWindow::updatescore(QString m_name)
{
    QSqlDatabase db=QSqlDatabase::database("sqlitel");
    QSqlQuery query(db);
    QString quer="update student set math=100 where name ='"+m_name+"'";
    bool success=query.exec(quer);
    if(success)
    {
        qDebug()<<"更新成功";
        return true;
    }
    else
    {
        qDebug()<<"更新失败";
        return false;
    }
}


MainWindow::~MainWindow()
{
    delete ui;
}
