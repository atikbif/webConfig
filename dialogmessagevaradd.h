#ifndef DIALOGMESSAGEVARADD_H
#define DIALOGMESSAGEVARADD_H

#include <QDialog>

namespace Ui {
class DialogMessageVarAdd;
}

class DialogMessageVarAdd : public QDialog
{
    Q_OBJECT

public:
    explicit DialogMessageVarAdd(QWidget *parent = 0);
    ~DialogMessageVarAdd();
    QString getMessage() const;
    void setMessage(const QString &value);
    int getType() const;
    void setType(int value);
    QString getParent() const;
    void setParent(const QString &value);
    int getBitNum() const;
    void setBitNum(int value);
    void updateParentList(const QStringList &list);

private:
    Ui::DialogMessageVarAdd *ui;
};

#endif // DIALOGMESSAGEVARADD_H
