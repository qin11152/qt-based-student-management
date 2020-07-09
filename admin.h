#ifndef ADMIN_H
#define ADMIN_H

#include <QWidget>

namespace Ui {
class admin;
}

class admin : public QWidget
{
    Q_OBJECT

public:
    explicit admin(QWidget *parent = nullptr);
    ~admin();

    int countall(QString m_table);
    bool connectdatabase();
    QVector<QVector<QString>> queryall(QString m_table);
    bool showtable();

private:
    Ui::admin *ui;
};

#endif // ADMIN_H
