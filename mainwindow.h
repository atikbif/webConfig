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
    QTreeWidgetItem *addController(Controller &c, QTreeWidgetItem *obItem);
    void addObject();
    QTreeWidgetItem *addObject(DispObject &ob, QTreeWidgetItem *grItem);
    void deleteGroup();
    void changeGroupName();
    void editObject();
    void deleteObject();
    void addAnalogVar();
    QTreeWidgetItem *addAnalogVar(AnalogVar &var, QTreeWidgetItem *cItem);
    void addDiscreteVar();
    QTreeWidgetItem *addDiscreteVar(DiscreteVar &var, QTreeWidgetItem *cItem);
    void addMessage();
    QTreeWidgetItem *addMessage(MessageVar &var, QTreeWidgetItem *cItem);
    void editController();
    void deleteController();
    void editAnalogVar();
    void deleteAnalogVar();
    void editDiscreteVar();
    void deleteDiscreteVar();
    void editMessageVar();
    void deleteMessageVar();
    void saveProject();
    void loadProject();
    void clearProject();
    QTreeWidgetItem* loadController(const QString &fName, QTreeWidgetItem *obItem);
    QTreeWidgetItem* loadObject(const QString &fName, QTreeWidgetItem *grItem);
    QTreeWidgetItem* addGroup(const ObjectGroup &gr);
    void saveObjectXML(const QString &dirPath, QSharedPointer<DispObject> ob);
    void saveControllerXML(const QString &fName, QSharedPointer<Controller> c);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
