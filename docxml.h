#ifndef DOCXML_H
#define DOCXML_H
#include<QString>
#include<QFile>
#include<QDomElement>   // 元素
#include<QDomDocument>  // 文件
#include<QDomProcessingInstruction> //格式头部
#include<QDomNamedNodeMap>  // 获取元素的所有属性的映射关系
#include<QDebug>
#include<QTextStream>   // 文本流
#include<QStringList>
#include<QDomNodeList>
#include<vector>
#include<QDateTime>

#include<QVector>

using namespace std;
#define cout qDebug()<<"["<<__FILE__<<":"<<__LINE__<<"]"

// 使用xml一般是用来保存数据的


class DocXML
{
public:
    // 文件路径
    DocXML(QString filePath);
    // 创建空的xml文件
    static void createXml(QString& filePath,QString& rootName);

    // 添加子节点（不用根据属性进行判断）
    static void appendNodeXml(const QString& filePath,const QVector<QVector<QStringList>>& emtName_attrName_attrValue_s,const QVector<QStringList>& textName_Values=QVector<QStringList>());
    // 添加子节点（属性相同的话，就在这个属性相同的节点下面创建新的子节点）,默认是不兼容的
    static void appendNodeXml(const QString& filePath,const QVector<QVector<QStringList>>& emtName_attrName_attrValue_s, bool isMerger = false,const QVector<QStringList>& textName_Values=QVector<QStringList>());

    // 将xml文件中的所有数据读出来，怎么存进去的就怎么读出来？这里通过传引用的方式，将读取到的参数返回出去
    // 读取成功，就返回true，否则返回false
    // emtName_attrName_attrValue_text返回的数据结构，就是第一层的name，attrName,attrValue,text，下面就是这个节点的直接子节点
    // 这个只调用一次的话，就只能获取一个节点下面的所有直接子节点
    // 但是应该可以使用递归的方式，递归出口就是判断这个节点下面是否还有子节点，hasChildNode()
    // 那么还需要再添加两个参数：bool isRoot=false,QDomElement parentEmt = QDomElement();
    static bool readDataXml(const QString& filePath,QVector<QVector<QStringList>>& emtName_attrName_attrValue_text,bool isRoot,int parentId=0,const QDomElement parentEmt = QDomElement());
    // 重载版本，如果isRoot是true的话，就调用这个函数，这样能够有效的解耦和
    static bool readDataXml(const QString& filePath,QVector<QVector<QStringList>>& emtName_attrName_attrValue_text);
    static void clearID(){ID=0;}    // 每次读取完xml文档的时候，需要将这个ID恢复成0，否则的话，下一次开始读取的话，就会出错
private:

    static QVector<QVector<QStringList>> connectTreeNode(QVector<QVector<QStringList>>&emtName_attrName_attrValue);
    // 获取一个元素的所有属性,
    // name1 value1 name2 value2 name3 value3   ... ...
    static bool getAllAttr(const QDomElement& emt,QStringList& attrNameValue);

    // 给定一个节点，向当前节点下写入数据,写入的数据默认为空
    static void writeXml(QDomDocument& doc,QDomElement& parentEmt,const QVector<QStringList>&emtName_attrName_attrValue,const QStringList& textName_Values=QStringList());
    static QDomElement createElement(const QString& name,const QStringList& attrName = QStringList(),const QStringList& attrValue=QStringList());
private:
    // doc文档
    QDomDocument doc;
    // 每个节点的ID
    static int ID;

};

#endif // DOCXML_H
