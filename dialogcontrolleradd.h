#ifndef DIALOGCONTROLLERADD_H
#define DIALOGCONTROLLERADD_H

#include <QDialog>

namespace Ui {
class DialogControllerAdd;
}

class DialogControllerAdd : public QDialog
{
    Q_OBJECT

public:
    explicit DialogControllerAdd(QWidget *parent = 0);
    ~DialogControllerAdd();
    QString getIP() const;
    void setIP(const QString &value);
    QString getName() const;
    void setName(const QString &value);
    int getPort() const;
    void setPort(int value);

private:
    Ui::DialogControllerAdd *ui;
};

#endif // DIALOGCONTROLLERADD_H
