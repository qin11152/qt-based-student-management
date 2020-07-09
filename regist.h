#ifndef REGIST_H
#define REGIST_H

#include <QWidget>

namespace Ui {
class regist;
}

class regist : public QWidget
{
    Q_OBJECT

public:
    explicit regist(QWidget *parent = nullptr);
    bool connecttodatabase();
    bool insertstudent_user(QString name,QString pass);
    int countall(QString m_table);
    bool selectcount(QString table,QString user);
    ~regist();

private:
    Ui::regist *ui;
};

#endif // REGIST_H
