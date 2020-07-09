#ifndef STUWINDOW_H
#define STUWINDOW_H

#include <QWidget>

namespace Ui {
class stuwindow;
}

class stuwindow : public QWidget
{
    Q_OBJECT

public:
    explicit stuwindow(QWidget *parent = nullptr,QString m_name=" ");
    ~stuwindow();

    QVector<QVector<QString>> queryall(QString m_table);
    bool showtable();

private:
    Ui::stuwindow *ui;
    QString name;
};

#endif // STUWINDOW_H
