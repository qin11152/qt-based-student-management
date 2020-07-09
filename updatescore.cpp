#include "updatescore.h"
#include "ui_updatescore.h"
#include <QMessageBox>

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDebug>


updatescore::updatescore(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::updatescore)
{
    ui->setupUi(this);
    connect(ui->uppdate,&QPushButton::clicked,[=](){
        QString m_name=ui->name->text();
        QString math=ui->math->text();
        QString english=ui->english->text();
        if(!selectcount("student",m_name))
        {
            QMessageBox::critical(this,"错误","没有该生");
        }else
        {
            if(math.length()>0)
            {
                updatescores("math",m_name,math);
            }
            if(english.length()>0)
            {
                updatescores("english",m_name,english);
            }
            QMessageBox::information(this,"提示","更新成功");
        }
    });
}

updatescore::~updatescore()
{
    delete ui;
}



bool updatescore::updatescores(QString subject, QString name,QString score)
{
    QSqlDatabase db=QSqlDatabase::database("sqlitel");
    QSqlQuery query(db);
    QString quer="update student set "+subject+"="+score+" where name='"+name+"'";
    bool success=query.exec(quer);
    if(success)
    {
        qDebug()<<"更新成功";
        return true;
    }else
    {
        qDebug()<<"更新失败";
        return false;
    }
}



bool updatescore::selectcount(QString table,QString user)
{
    QSqlDatabase db=QSqlDatabase::database("sqlitel");
   QSqlQuery query(db);
   QString s="select count(*) from "+table+" where name='"+user+"'";
   qDebug()<<s;
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
