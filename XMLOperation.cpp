#include "XMLOperation.h"


XMLOperation::XMLOperation(void)
{
}


XMLOperation::~XMLOperation(void)
{
}


void XMLOperation::parseXML()  
{ 
	//�½�һ��QDomDocument����󣬴���һ��XML�ĵ�

	QDomDocument doc;
	QFile file("../XML/para.xml");
	if(!file.open(QIODevice::ReadOnly)) return 0;
	if(!doc.setContent((&file)))
	{
		file.close();
		return 0;

	}

	file.close();
	//���ظ��ڵ�
	QDomDocument docElem=doc.documentElement();
	//���ظ��ڵ�ĵ�һ���ڵ�
	QDomNode n=docElem.firstChild();
	//����ڵ㲻Ϊ�գ���ת����һ���ڵ�
	while(!n.isNull())
	{
		//����ת��ΪԪ��
		QDomElement e=n.toElement();
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

