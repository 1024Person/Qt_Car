#ifndef DOCXML_H
#define DOCXML_H
#include<QString>
#include<QFile>
#include<QDomElement>   // 元素
#include<QDomDocument>  // 文件
#include<QDomProcessingInstruction> //格式头部
#include<QDebug>
#include<QTextStream>   // 文本流
#include<QStringList>
#include<QDomNodeList>

#include<QDateTime>


using namespace std;
#define cout qDebug()<<"["<<__FILE__<<":"<<__LINE__<<"]"

// 使用xml一般是用来保存数据的


class DocXML
{
public:
    // 文件路径
    DocXML(QString filePath);
    // 创建空的xml文件
    static void createXml(QString filePath,QString rootName);

    // 添加子节点（不用根据属性进行判断）
    static void appendNodeXml(const QString filePath,const vector<vector<QStringList>>& emtName_attrName_attrValue_s,const vector<QStringList>& textName_Values=vector<QStringList>());
    // 添加子节点（属性相同的话，就在这个属性相同的节点下面创建新的子节点）,默认是不兼容的
    static void appendNodeXml(const QString filePath,const vector<vector<QStringList>>& emtName_attrName_attrValue_s, bool isMerger = false,const vector<QStringList>& textName_Values=vector<QStringList>());


private:
    // 给定一个节点，向当前节点下写入数据,写入的数据默认为空
    static void writeXml(QDomDocument& doc,QDomElement& parentEmt,const vector<QStringList>&emtName_attrName_attrValue,const QStringList& textName_Values=QStringList());
    static QDomElement createElement(const QString& name,const QStringList& attrName = QStringList(),const QStringList& attrValue=QStringList());
private:
    // doc文档
    QDomDocument doc;



};

#endif // DOCXML_H
