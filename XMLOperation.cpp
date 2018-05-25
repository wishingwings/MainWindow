#include "XMLOperation.h"


XMLOperation::XMLOperation(void)
{
}


XMLOperation::~XMLOperation(void)
{
}


void XMLOperation::parseXML()  
{ 
	//新建一个QDomDocument类对象，代表一个XML文档

	QDomDocument doc;
	QFile file("../XML/para.xml");
	if(!file.open(QIODevice::ReadOnly)) return 0;
	if(!doc.setContent((&file)))
	{
		file.close();
		return 0;

	}

	file.close();
	//返回根节点
	QDomDocument docElem=doc.documentElement();
	//返回根节点的第一个节点
	QDomNode n=docElem.firstChild();
	//如果节点不为空，则转到下一个节点
	while(!n.isNull())
	{
		//将它转换为元素
		QDomElement e=n.toElement();
		//获得元素e所有子节点的列表
		QDomNodeList list=e.childNodes();
		//遍历该列表
		for(int i=0;i<list.count();i++)
		{
			QDomNode node=list.at(i);
			if(node.isElement())
				qDebug()<<" "<<node.toElement().tagName()<<node.toElement().text();

		}

		n=n.nextSibling();

	}


	
}

