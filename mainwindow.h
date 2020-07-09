#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlDatabase>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
   bool connectdatabase();
   bool createtable();
   bool insertintodatabase();
   bool queryall(QString m_table);
   bool deletedata(QString m_table);
   bool checkpassword(QString table,QString user,QString password);
   bool checkpassword1(QString table,QString user,QString password);
   bool deletetable(QString m_table);
   bool selectcount(QString table,QString user);
   int countall(QString m_table);
   bool showtables();
   bool updatescore(QString m_name);
private slots:

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
