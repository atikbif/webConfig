#ifndef DIALOGGROUPCHANGENAME_H
#define DIALOGGROUPCHANGENAME_H

#include <QDialog>

namespace Ui {
class DialogGroupChangeName;
}

class DialogGroupChangeName : public QDialog
{
    Q_OBJECT
public:
    explicit DialogGroupChangeName(QWidget *parent = 0);
    ~DialogGroupChangeName();

    QString getGrName() const;
    void setGrName(const QString &value);

private:
    Ui::DialogGroupChangeName *ui;
};

#endif // DIALOGGROUPCHANGENAME_H
