#ifndef DIALOGANALOGVARADD_H
#define DIALOGANALOGVARADD_H

#include <QDialog>

namespace Ui {
class DialogAnalogVarAdd;
}

class DialogAnalogVarAdd : public QDialog
{
    Q_OBJECT

public:
    explicit DialogAnalogVarAdd(QWidget *parent = 0);
    ~DialogAnalogVarAdd();
    QString getName() const;
    void setName(const QString &value);
    int getPriority() const;
    void setPriority(int value);
    int getAddress() const;
    void setAddress(int value);
    int getScaleMin() const;
    void setScaleMin(int value);
    int getScaleMax() const;
    void setScaleMax(int value);
    int getAlarmMin() const;
    void setAlarmMin(int value);
    int getAlarmMax() const;
    void setAlarmMax(int value);
    double getCoeff() const;
    void setCoeff(double value);

private:
    Ui::DialogAnalogVarAdd *ui;
};

#endif // DIALOGANALOGVARADD_H
