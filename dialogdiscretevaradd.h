#ifndef DIALOGDISCRETEVARADD_H
#define DIALOGDISCRETEVARADD_H

#include <QDialog>

namespace Ui {
class DialogDiscreteVarAdd;
}

class DialogDiscreteVarAdd : public QDialog
{
    Q_OBJECT

public:
    explicit DialogDiscreteVarAdd(QWidget *parent = 0);
    ~DialogDiscreteVarAdd();
    QString getName() const;
    void setName(const QString &value);
    int getPriority() const;
    void setPriority(int value);
    void updateParentList(const QStringList &list);
    QString getParent() const;
    void setParent(const QString &value);
    int getBitNum() const;
    void setBitNum(int value);

private:
    Ui::DialogDiscreteVarAdd *ui;
};

#endif // DIALOGDISCRETEVARADD_H
