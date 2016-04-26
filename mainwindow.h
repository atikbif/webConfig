#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QHash>
#include <QTreeWidgetItem>
#include "disproot.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    QHash<QTreeWidgetItem*,void*> treeLink;
    QTreeWidgetItem *contextItem;
    DispRoot root;
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();
    void on_treeWidget_customContextMenuRequested(const QPoint &pos);
    void addController();
    void addObject();
    void deleteGroup();
    void changeGroupName();
    void editObject();
    void deleteObject();
    void addAnalogVar();
    void addDiscreteVar();
    void addMessage();
    void editController();
    void deleteController();
    void editAnalogVar();
    void deleteAnalogVar();
    void editDiscreteVar();
    void deleteDiscreteVar();
    void editMessageVar();
    void deleteMessageVar();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
