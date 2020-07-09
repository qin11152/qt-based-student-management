#ifndef INSERT_H
#define INSERT_H

#include <QWidget>

namespace Ui {
class insert;
}

class insert : public QWidget
{
    Q_OBJECT

public:
    explicit insert(QWidget *parent = nullptr);
    ~insert();

    bool connectdatabase();
    bool insertstudent(QString name,QString math,QString english);

private:
    Ui::insert *ui;
};

#endif // INSERT_H
