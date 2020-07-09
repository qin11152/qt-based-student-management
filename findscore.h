#ifndef FINDSCORE_H
#define FINDSCORE_H

#include <QWidget>

namespace Ui {
class findscore;
}

class findscore : public QWidget
{
    Q_OBJECT

public:
    explicit findscore(QWidget *parent = nullptr);
    ~findscore();

    QVector<QVector<QString>> queryall(QString m_table,QString name);
    bool showtable(QString name);
    bool selectcount(QString table,QString user);
private:
    Ui::findscore *ui;
};

#endif // FINDSCORE_H
