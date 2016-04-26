#ifndef DIALOGOBJECTADD_H
#define DIALOGOBJECTADD_H

#include <QDialog>

namespace Ui {
class DialogObjectAdd;
}

class DialogObjectAdd : public QDialog
{
    Q_OBJECT

public:
    explicit DialogObjectAdd(QWidget *parent = 0);
    ~DialogObjectAdd();
    QString getName() const;
    void setName(const QString &value);
    QString getComment() const;
    void setComment(const QString &value);
    int getPeriod() const;
    void setPeriod(int value);
    int getWaitTime() const;
    void setWaitTime(int value);
private:
    Ui::DialogObjectAdd *ui;
};

#endif // DIALOGOBJECTADD_H
