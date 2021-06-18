#include "docxml.h"



DocXML::DocXML(QString filePath)
{

}


void DocXML::createXml(QString filePath,QString rootName)
{
    QFile file(filePath);
    if(file.exists() == true){
        cout<<"文件已经存在";
        return ;
    }
    else{
        bool isOK = file.open(QIODevice::WriteOnly);    // 只写方式打开
        // 文件
        if(!isOK){
            cout<<filePath<<"文件打开失败";
            return;
        }
        else{
            // 文件打开成功，就是创建了新的文件
            // 开始创建xml文档
            QDomDocument doc;   // 文档对象

            // 创建xml头部格式   <?xml version='1.0' encoding='utf-8'?>
            QDomProcessingInstruction head;
            // 创建成功了，创建头部元素
            head = doc.createProcessingInstruction("xml","version=\'1.0\' encoding=\'utf-8\'");
            // 追加到文件中
            doc.appendChild(head);
            // 创建根节点元素
            QDomElement root = doc.createElement(rootName);


            // 将创建的元素，追加到doc中
            doc.appendChild(root);

            QTextStream stream(&file);  // 文本流关联文件
            stream.setCodec("UTF-8");
            doc.save(stream,4);   // 将doc中的内容，保存到stream文本流中，并且设置缩进为4
            file.close();

        }
    }
}


// 下面的几个方法都是搞好的非常  泛式 的接口，调用者自己向其中传进去参数
void DocXML::appendNodeXml(const QString filePath,const vector<vector<QStringList>>&emtName_attrName_attrValue,const vector<QStringList>& textName_Values)
{
    /*
 * emtName_attrName_attrValue,是一个二维数组，每一行代表着name，attrNames，attrValues，
 * textName_Values 是一个一维数组，表着attrName1 attrValue1 attrName2 attrValue2 .....
 * 传递进来的emtName_attrName_attrValue，如果不想传递进来属性的话，可以只传递进来name
 *  textName_Values 可以不传递东西，因为默认就是空
 *
*/
    QFile file(filePath);
    if(!file.open(QIODevice::ReadOnly)){
        cout<<"文件打开失败"<<filePath;
        return;
    }
    QDomDocument doc;
    if(!doc.setContent(&file)){
        cout<<"文件关联失败"<<filePath;
        file.close();
        return;
    }
    file.close();
    // 获取根节点
    QDomElement root = doc.documentElement();
    // 上面的变量名字太长了，就用这个来代替了
    auto replace_var = emtName_attrName_attrValue;

    // emtName_attrName_attrValue
    auto child = createElement(replace_var[0][0][0],replace_var[0][1],replace_var[0][2]);

    root.appendChild(child);
    // 不断的在当前节点下面写入新的节点，注意是在当前节点下面！！！
    for(size_t i = 1;i<replace_var.size();i++)
        // 这里需要判断一下，当前节点下面是否要建立文本子节点
        // 当前节点没有文本子节点
        if(i-1<textName_Values.size())
            writeXml(doc,child,replace_var[i],textName_Values[i-1]);
        // 当前节点有自己的文本子节点
        else{
            writeXml(doc,child,replace_var[i]);
        }
    if(!file.open(QIODevice::WriteOnly)){
        cout<<"保存文件失败"<<filePath;
        return;
    }
    QTextStream stream(&file);
    doc.save(stream,4);
    file.close();   // 关闭文件
}

void DocXML::appendNodeXml(const QString filePath, const vector<vector<QStringList> > &emtName_attrName_attrValue_s, bool isMerger, const vector<QStringList> &textName_Values)
{
    if(!isMerger){  // 如果不兼并的话，就直接在根节点下面创建节点
        return appendNodeXml(filePath,emtName_attrName_attrValue_s,textName_Values);
    }
    /*
 *  如果是兼容的话，就需要判断最后一个节点的属性是否和当前要添加节点的属性一样，
 * 如果一样的话，就不能再重新创建新的节点了，但是如果不一样的话，就要重新创建新的节点
*/


    QFile file(filePath);
    if(!file.open(QIODevice::ReadOnly)){
        cout<<"文件打开失败"<<filePath;
        return;
    }
    QDomDocument doc;
    if(!doc.setContent(&file)){
        cout<<"文件关联失败"<<filePath;
        file.close();
        return;
    }
    file.close();
    QDomElement root = doc.documentElement();
    if(!root.hasChildNodes()){// 如果根节点下面没有子节点，
/*
* 也就是说如果这个xml文档是刚刚创建传来的新文档的话，
* 就直接在root节点下面创建子节点
*/
        return appendNodeXml(filePath,emtName_attrName_attrValue_s,textName_Values);
    }
    // 找到最后一个和当前要插入的节点名字一样的节点
    QDomElement lastEmt = root.lastChildElement(emtName_attrName_attrValue_s[0][0][0]);
    cout<<lastEmt.tagName()<<root.tagName()<<root.lastChildElement().tagName();


    /*
    *  标记是否在最后一个节点上插入，
    *  如果flag==true的话，就在该节点上插入新的节点
    * 否则的话，就在根节点上再次插入新的节点
   */
    bool flag = true;
    cout<<emtName_attrName_attrValue_s[0][1].length();
    for(int j = 0;j<emtName_attrName_attrValue_s[0][1].length();j++)
    {
        auto temp1 = lastEmt.attribute(emtName_attrName_attrValue_s[0][1][j]);
        auto temp2 = emtName_attrName_attrValue_s[0][2][j];
        // 判断属性值是否相同
        if(lastEmt.attribute(emtName_attrName_attrValue_s[0][1][j]) != emtName_attrName_attrValue_s[0][2][j]){
            flag = false;
            break;
        }
    }

    /*
         *  判断出这个新创建的节点应该是添加到根节点上，还是在最后一个节点上进行插入
        */

    if(flag){   // 应该在这个节点上添加新的节点
        for(size_t k = 1;k<emtName_attrName_attrValue_s.size();k++){
            writeXml(doc,lastEmt,emtName_attrName_attrValue_s[k],textName_Values[k-1]);
        }
    }
    else{   // 在根节点上直接添加新的节点
        return appendNodeXml(filePath,emtName_attrName_attrValue_s,textName_Values);
    }

    // 保存文件
    if(!file.open(QIODevice::WriteOnly)){
        cout<<"文件保存失败";
        return;
    };
    QTextStream stream(&file);
    doc.save(stream,4);
    file.close();


}

void DocXML::writeXml(QDomDocument &doc, QDomElement &parentEmt,const vector<QStringList>&emtName_attrName_attrValue,const QStringList& textName_Values)
{
    auto repalce_emt = emtName_attrName_attrValue;
    QDomElement curEmt;
    // 创建子元素
    if(repalce_emt.size()<=1){
        curEmt = createElement(repalce_emt[0][0]);
    }
    else{
        curEmt = createElement(repalce_emt[0][0],repalce_emt[1],repalce_emt[2]);
    }
    // 添加到父亲节点中
    parentEmt.appendChild(curEmt);
    // 如果没有传进来text节点，就直接返回
    if(textName_Values.isEmpty()){
        return;
    }
    for(int i = 0;i<textName_Values.length();i++){
        auto childNode = doc.createElement(textName_Values.at(i));
        QDomText childText = doc.createTextNode(textName_Values.at(++i));  // 创建文本节点
        childNode.appendChild(childText);   // 将这个文本节点添加到子元素中？
        curEmt.appendChild(childNode);     // 将子节点添加到time元素中去
    }

}

QDomElement DocXML::createElement(const QString &name,const QStringList& attrName,const QStringList& attrValue)
{
    QDomElement childEelement = QDomDocument().createElement(name);
    if(attrName.isEmpty()) return childEelement;   // 没有属性，就直接返回
    // 创建属性
    for(int i = 0;i<attrName.length();i+=2){
        childEelement.setAttribute(attrName.at(i),attrValue.at(i));
    }
    return childEelement;
}
