#ifndef DIALOGGROUPADD_H
#define DIALOGGROUPADD_H

#include <QDialog>

namespace Ui {
class DialogGroupAdd;
}

class DialogGroupAdd : public QDialog
{
    Q_OBJECT
    QString name;
public:
    explicit DialogGroupAdd(QWidget *parent = 0);
    ~DialogGroupAdd();
    QString getName() const;
private:
    Ui::DialogGroupAdd *ui;
};

#endif // DIALOGGROUPADD_H
