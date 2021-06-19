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
    void setQssSheet(const QString& filePath); // 通过qss文件，设置qss样式表
    void getXMLInfo();  // 读取到XML文件中的所有信息
    void cleaningData(vector<vector<QStringList>>& data);   // 因为读出来的数据是“脏的”还需要进一步的处理
private:
    Ui::MainWindow *ui;
    QStringList fieldName;
    QString filePath = "/home/ytu/Qt/Qt_Car/saleList.xml";
};
#endif // MAINWINDOW_H
