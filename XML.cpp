#include "XML.h"


XML::XML(void)
{
}


XML::~XML(void)
{
}

void XML::ReadXML()  
{ 
	qDebug()<<QDir::currentPath();
	//新建一个QDomDocument类对象，代表一个XML文档
	
	QDomDocument doc;
	QFile file("D:/Study/VC++_project/ShowImage/MainWindow/MainWindow/XML/paras.xml");
	if(!file.open(QIODevice::ReadOnly)) return;
	if(!doc.setContent((&file)))
	{
		file.close();
		return;

	}

	file.close();
	//返回根节点
	QDomElement docElem=doc.documentElement();
	qDebug()<<"root Node name is "<<docElem.tagName();

	//返回根节点的第一个节点
	QDomNode n=docElem.firstChildElement();
	qDebug()<<" Node name is "<<n.toElement().tagName();
	
	//如果节点不为空，则转到下一个节点
	while(!n.isNull())
	{
		//将它转换为元素
		QDomElement e=n.toElement();
		//qDebug()<<" now child node is "<<e.tagName()<<e.text();
		qDebug()<<" now child node is "<<e.tagName();

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

void XML::UpdateXML()  
{ 

	qDebug()<<QDir::currentPath();
	//新建一个QDomDocument类对象，代表一个XML文档

	QDomDocument doc;
	QFile file("D:/Study/VC++_project/ShowImage/MainWindow/MainWindow/XML/paras.xml");
	if(!file.open(QIODevice::ReadOnly)) return;
	if(!doc.setContent((&file)))
	{
		file.close();
		return;

	}

	file.close();
	//返回根节点

	//修改保存xml  
	QDomElement root = doc.documentElement();  
	if(root.tagName()!= "Paras")  
		return ;  
	QDomNode n = root.firstChild();  
	while ( !n.isNull() )  
	{  
		QDomElement e = n.toElement();  
		qDebug()<<" now child node is "<<e.tagName();
		if( !e.isNull())  
		{  
			if( e.nodeName() == "ChooseSAT" )  
			{  
				QDomNodeList list = e.childNodes(); //获得元素e的所有子节点的列表  
				for(int a=0; a<list.count(); a++) //遍历该列表  
				{  
					QDomNode node = list.at(a);  
					qDebug()<<" now child child node is "<<node.nodeName()<<node.nodeValue();
					if(node.isElement())  
					{  
						if( node.nodeName() == "value" )  
						{  
							QDomNode oldnode = node.firstChild();     //标签之间的内容作为节点的子节点出现，得到原来的子节点  
							node.firstChild().setNodeValue("newvalue1");   //用提供的value值来设置子节点的内容  
							qDebug()<<"after change,the value is"<<node.toElement().text();  
							QDomNode newnode = node.firstChild();     //值修改过后  
							node.replaceChild(newnode,oldnode);      //调用节点的replaceChild方法实现修改功能  

						}  
						
					}  
				}  
			}  
		}  
		n = n.nextSibling();  

	} 

		QFile filexml("D:/Study/VC++_project/ShowImage/MainWindow/MainWindow/XML/paras.xml");  
		if( !filexml.open( QFile::WriteOnly | QFile::Truncate) ){  
			qWarning("error::ParserXML->writeOperateXml->file.open\n");  
			return ;  
		}  
		QTextStream ts(&filexml);  
		ts.reset();  
		ts.setCodec("utf-8");  
	   doc.save(ts, 4, QDomNode::EncodingFromTextStream);  
		filexml.close();  
		return;  
	 
	
}


