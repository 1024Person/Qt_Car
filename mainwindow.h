#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include"docxml.h"
#include<QDateTime>
#include<vector>
#include<QFile>
using namespace std;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    void generateElement(); // 生成xml节点元素的方法
    void setQssSheet(QString filePath); // 通过qss文件，设置qss样式表
private:
    Ui::MainWindow *ui;
    QString filePath = "/home/ytu/Qt/Qt_Car/test.xml";
};
#endif // MAINWINDOW_H
