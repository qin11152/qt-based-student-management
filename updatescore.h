#ifndef UPDATESCORE_H
#define UPDATESCORE_H

#include <QWidget>

namespace Ui {
class updatescore;
}

class updatescore : public QWidget
{
    Q_OBJECT

public:
    explicit updatescore(QWidget *parent = nullptr);
    ~updatescore();

    bool updatescores(QString subject,QString name,QString score);
    bool selectcount(QString table,QString user);

private:
    Ui::updatescore *ui;
};

#endif // UPDATESCORE_H
