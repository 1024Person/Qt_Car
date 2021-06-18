#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //DocXML::createXml(filePath,"日销售清单");
    //generateElement();

    this->setQssSheet(":/qssFile/qss.qss");

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::generateElement()
{
    QDateTime dateTime = QDateTime::currentDateTime();
    QString dateStr = dateTime.toString("yyyy-MM-dd");
    QString timeStr = dateTime.toString("hh-mm-ss");

    vector<vector<QStringList>> emtName_attrName_attrValue_s;   // 元素数组
    vector<QStringList> node;
    vector<QStringList> node2;
    node.push_back(QStringList("日期"));
    QStringList attrName1;
    QStringList attrValue1;
    attrName1<<"date";
    node.push_back(attrName1);
    attrValue1<<dateStr;
    node.push_back(attrValue1);
    emtName_attrName_attrValue_s.push_back(node);

    node2.push_back(QStringList("时间"));
    QStringList attrName2;
    QStringList attrValue2;
    attrName2<<"time";
    node2.push_back(attrName2);
    attrValue2<<timeStr;
    node2.push_back(attrValue2);
    emtName_attrName_attrValue_s.push_back(node2);


    vector<QStringList> node3;
    node3.push_back(QStringList("stu"));
    QStringList attrName3;
    QStringList attrValue3;
    attrName3<<"id";
    node3.push_back(attrName3);
    attrValue3<<"1";
    node3.push_back(attrValue3);
    emtName_attrName_attrValue_s.push_back(node3);


    vector<QStringList> textName_Values;
    QStringList nodeText1;
    nodeText1<<"厂家"<<"二汽神龙"<<"品牌"<<"毕加索"<<"报价"<<"39"<<"数量"<<"1"<<"金额"<<"39";
    textName_Values.push_back(nodeText1);
    QStringList nodeText2;
    nodeText2<<"name"<<"zhangsan"<<"score"<<"100"<<"sex"<<"f";
    textName_Values.push_back(nodeText2);

    DocXML::appendNodeXml(filePath,emtName_attrName_attrValue_s,true,textName_Values);

}

void MainWindow::setQssSheet(QString filePath)
{
    QFile qssFile(filePath);
    if(qssFile.open(QIODevice::ReadOnly)){
        QString qss = qssFile.readAll();
        cout<<qss;
        this->setStyleSheet(qss);
        qssFile.close();    // 关闭文件
    }
    else{
        cout<<"打开qss文件失败"<<filePath;
    }
}

