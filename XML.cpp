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
	//�½�һ��QDomDocument����󣬴���һ��XML�ĵ�
	
	QDomDocument doc;
	QFile file("D:/Study/VC++_project/ShowImage/MainWindow/MainWindow/XML/paras.xml");
	if(!file.open(QIODevice::ReadOnly)) return;
	if(!doc.setContent((&file)))
	{
		file.close();
		return;

	}

	file.close();
	//���ظ��ڵ�
	QDomElement docElem=doc.documentElement();
	qDebug()<<"root Node name is "<<docElem.tagName();

	//���ظ��ڵ�ĵ�һ���ڵ�
	QDomNode n=docElem.firstChildElement();
	qDebug()<<" Node name is "<<n.toElement().tagName();
	
	//����ڵ㲻Ϊ�գ���ת����һ���ڵ�
	while(!n.isNull())
	{
		//����ת��ΪԪ��
		QDomElement e=n.toElement();
		//qDebug()<<" now child node is "<<e.tagName()<<e.text();
		qDebug()<<" now child node is "<<e.tagName();

		//���Ԫ��e�����ӽڵ���б�
		QDomNodeList list=e.childNodes();
		//�������б�
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
	//�½�һ��QDomDocument����󣬴���һ��XML�ĵ�

	QDomDocument doc;
	QFile file("D:/Study/VC++_project/ShowImage/MainWindow/MainWindow/XML/paras.xml");
	if(!file.open(QIODevice::ReadOnly)) return;
	if(!doc.setContent((&file)))
	{
		file.close();
		return;

	}

	file.close();
	//���ظ��ڵ�

	//�޸ı���xml  
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
				QDomNodeList list = e.childNodes(); //���Ԫ��e�������ӽڵ���б�  
				for(int a=0; a<list.count(); a++) //�������б�  
				{  
					QDomNode node = list.at(a);  
					qDebug()<<" now child child node is "<<node.nodeName()<<node.nodeValue();
					if(node.isElement())  
					{  
						if( node.nodeName() == "value" )  
						{  
							QDomNode oldnode = node.firstChild();     //��ǩ֮���������Ϊ�ڵ���ӽڵ���֣��õ�ԭ�����ӽڵ�  
							node.firstChild().setNodeValue("newvalue1");   //���ṩ��valueֵ�������ӽڵ������  
							qDebug()<<"after change,the value is"<<node.toElement().text();  
							QDomNode newnode = node.firstChild();     //ֵ�޸Ĺ���  
							node.replaceChild(newnode,oldnode);      //���ýڵ��replaceChild����ʵ���޸Ĺ���  

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


