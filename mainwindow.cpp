#include "mainwindow.h"

#include "gdal.h"
#include "gdal_priv.h"



MainWindow::MainWindow(QWidget *parent, Qt::WFlags flags)
	: QMainWindow(parent, flags)
{
	ui.setupUi(this);
	strList=new QStringList();
	Rect *rect = new Rect(); 
	

	//int x=currentPos.x();
		/*int y=currentPos.y();
		const QRectF *rect=new QRectF (currentPos,QSizeF(100,100));
		qDebug()<<"createrect"<<endl;
		QGraphicsRectItem *item_rect=new QGraphicsRectItem();
		item_rect->setRect(QRectF (currentPos,QSizeF(0,0)));*/
		

	myScene=new MyScene(this);
	
	myScene->addItem(rect);

	//Ϊ��ͼ���ó���
	//QGraphicsView *graphicsView=new QGraphicsView (this);
	//ui.graphicsView->setScene(pScene);
	ui.graphicsView->setScene(myScene);


	
	//ui.graphicsView->setMouseTracking(true);
	
	//ui.centralWidget->setMouseTracking(true);
   //MainWindow::setMouseTracking(true);
	
	setWindowState(Qt::WindowMaximized);//ʹ�ô������
	
	//���������ʾ��������
	QTextCodec *codec = QTextCodec::codecForName("UTF-8");
	QTextCodec::setCodecForTr(codec);
	QTextCodec::setCodecForLocale(QTextCodec::codecForLocale());
	QTextCodec::setCodecForCStrings(QTextCodec::codecForLocale());
	//���������ʾ��������

	QToolBar *pToolBar=addToolBar(tr("&File"));
		
	QObject::connect(ui.openAction,SIGNAL(triggered()),this,SLOT(openFileSlot()));
   	
	QObject::connect(ui.PanAction,SIGNAL(triggered()),this,SLOT(panPicSlot()));
		
	QObject::connect(ui.MagnifyAction,SIGNAL(triggered()),this,SLOT(MagnifyActionSlot()));

	QObject::connect(ui.NewROIAction,SIGNAL(triggered()),this,SLOT(NewROIActionSlot()));

	QObject::connect(this,SIGNAL(clicked()),this,SLOT(mousePressEventSlot()));

	QObject::connect(rect,SIGNAL(itemIsPressed()),this,SLOT(isPressed()));  //FIXME
	QObject::connect(rect,SIGNAL(itemIsReleased()),this,SLOT(isReleased()));//FIXME


	//QObject::connect(this,SIGNAL(RectMouseIsPressed()),this,SLOT(mousePressEventSlot()));

	//QObject::connect(this,SIGNAL(released()),this,SLOT(mouseReleaseEvent()));

		
}

MainWindow::~MainWindow()
{
	
}
void MainWindow::resizeEvent() 
{
	ui.graphicsView->size();
	int widthGraphicsView=ui.graphicsView->size().width();
	int heightGraphicsView=ui.graphicsView->size().height();

}

void MainWindow::ReadImgInfo(QString fileName)
{

	if ( fileName == "" || poDataset== NULL )  
	{  
		return;  
	}  

	 int row = 0; // ������¼����ģ�͵��к� 

	 // ͼ��ĸ�ʽ��Ϣ  
	 imgMetaModel->setItem( row, 0, new QStandardItem(tr( "Description" ) ) );  
	 imgMetaModel->setItem( row++, 1, new QStandardItem( poDataset->GetDriver()->GetDescription() ) );  
	 imgMetaModel->setItem( row, 0, new QStandardItem(tr( "Meta Infor") ) );  
	 imgMetaModel->setItem( row++, 1, new QStandardItem( poDataset->GetDriver()->GetMetadataItem( GDAL_DMD_LONGNAME) ) ) ;  
	 imgMetaModel->setItem( row, 0, new QStandardItem(tr("Data Type") ) );  
	 imgMetaModel->setItem( row++, 1, new QStandardItem(GDALGetDataTypeName( ( poDataset->GetRasterBand( 1)->GetRasterDataType() ) ) ) );  

	 // ͼ��Ĵ�С�Ͳ��θ���  
	 imgMetaModel->setItem( row, 0, new QStandardItem(tr( "X Size" ) ) );  
	 imgMetaModel->setItem( row++, 1, new QStandardItem( QString::number( poDataset->GetRasterXSize() ) ) );  
	 imgMetaModel->setItem( row, 0, new QStandardItem( tr( "Y Size" ) ) );  
	 imgMetaModel->setItem( row++, 1, new QStandardItem( QString::number( poDataset->GetRasterYSize() ) ) );  
	 imgMetaModel->setItem( row, 0, new QStandardItem( tr( "Band Count" ) ) );  
	 imgMetaModel->setItem( row++, 1, new QStandardItem( QString::number( poDataset->GetRasterCount() ) ) );  

	 // ͼ���ͶӰ��Ϣ  
	 imgMetaModel->setItem( row, 0, new QStandardItem( tr( "Projection" ) ) );  
	 imgMetaModel->setItem( row++, 1, new QStandardItem( poDataset->GetProjectionRef() ) );  

	 // ͼ�������ͷֱ�����Ϣ  
	 double adfGeoTransform[6];  
	 QString origin = "";  
	 QString pixelSize = "";  
	 if( poDataset->GetGeoTransform(adfGeoTransform ) == CE_None )  
	 {  
		 origin = QString::number(adfGeoTransform[0] ) + "," + QString::number( adfGeoTransform[3] );  
		 pixelSize = QString::number(adfGeoTransform[1] ) + "," + QString::number( adfGeoTransform[5] );  
	 }  
	 imgMetaModel->setItem( row, 0, new QStandardItem(tr( "Origin" ) ) );  
	 imgMetaModel->setItem( row++, 1, new QStandardItem(origin ) );  
	 imgMetaModel->setItem( row, 0, new QStandardItem(tr( "Pixel Size" ) ) );  
	 imgMetaModel->setItem( row++, 1, new QStandardItem(pixelSize ) );  


}

void MainWindow::openFileSlot()
{
	qDebug()<<"fileName is";
	//get file name
	fileName=QFileDialog::getOpenFileName(this,"Open File",QDir::currentPath()); // ��mainwindow.h�Ѷ���
	qDebug()<<"fileName is"<<fileName;

	if(fileName.isEmpty())
	{

		QMessageBox::information(this,"��ʾ","��ѡ����Ҫ�򿪵��ļ�");
		return;
	}


	else
	{
		/*QImage *img=new QImage;
		
		if(! ( img->load(fileName) ) ) //����ͼ��
		{
			QMessageBox::information(this,
				tr("��ͼ��ʧ��"),
				tr("��ͼ��ʧ��!"));
			delete img;
			return;
		}*/

		ReadImg(fileName);
		//ReadImgInfo(fileName);
		ShowTree(fileName,nBandCount);

	
					

	}

}

void MainWindow::ReadImg(QString fileName)

{
	GDALAllRegister();         //����GDAL��ȡͼƬ����Ҫ����ע��  

	//CPLSetConfigOption("GDAL_FILENAME_IS_UTF8","NO");   //����֧������·��  

	GDALDataset *poDataset;

	GDALRasterBand  *poBand;
	

	QByteArray ba=fileName.toLatin1();
	char *mm=ba.data();
	qDebug()<<mm<<endl;

	poDataset=(GDALDataset*)GDALOpen(mm,GA_ReadOnly);

	
		
	//��ȡͼ��Ĵ�С
	int width=poDataset->GetRasterXSize();    
	int height=poDataset->GetRasterYSize();     


	//��ȡͼ��Ĳ�����
	nBandCount=poDataset->GetRasterCount();
	qDebug()<<nBandCount<<endl;	

	//��ȡӰ����������
	poBand=poDataset->GetRasterBand(1);
	poBand -> GetRasterDataType();


	// ͼ�������ͷֱ�����Ϣ  
	double adfGeoTransform[6];  
	QString origin = "";  
	QString pixelSize = "";
	poDataset->GetGeoTransform(adfGeoTransform);

	if( poDataset->GetGeoTransform(adfGeoTransform ) == CE_None )  
	{  
		poDataset->GetGeoTransform(adfGeoTransform);
	}

	//�����ʾͼ���GraphicsViewʵ�ʳߴ�
	int widthGraphicsView=ui.graphicsView->size().width();
	int heightGraphicsView=ui.graphicsView->size().height();
	 

	int bytePerLine = (width * 8 + 31 )/ 32*4;  
	unsigned char* allBandUC = new unsigned char[bytePerLine * height]; 

	
	poBand ->RasterIO(GF_Read,0,0, width, height,allBandUC ,width, height, GDT_Byte, 0, 0);

	pItem=new QGraphicsPixmapItem( QPixmap::fromImage(QImage(allBandUC,width,height,QImage::Format_Indexed8)));
	

	//QGraphicsPixmapItem *pItem=new QGraphicsPixmapItem( QPixmap::fromImage(QImage (allBandUC,width,height,bytePerLine,QImage::Format_RGB888)));

	//��item�����������
	//pScene=new QGraphicsScene(this);
	//pScene->addItem(pItem);
	myScene->addItem(pItem);

	//Ϊ��ͼ���ó���
	//QGraphicsView *graphicsView=new QGraphicsView (this);
	//ui.graphicsView->setScene(pScene);
	ui.graphicsView->setScene(myScene);

	
	
}

void MainWindow::InitTree()

{
	ui.treeWidget->clear();    //��ʼ�����οؼ�
	ui.treeWidget->show();

	//addTreeRoot
	//ui.treeWidget->setHeaderLabel("tree");
	//ui.treeWidget->setHeaderHidden(1); // TreeWidget �������� 1Ϊ����Header���� 0 Ϊ��ʾHeader����

	QTreeWidgetItem *items1 = new QTreeWidgetItem(ui.treeWidget,
		QStringList(QString("num_1")));
	items1->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
	items1->setCheckState(0,Qt::Unchecked); //��ʼ״̬û�б�ѡ��

	QTreeWidgetItem *items2 = new QTreeWidgetItem(items1,
		QStringList(QString("num_2")));
	items2->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
	items2->setCheckState(0,Qt::Unchecked); //��ʼ״̬û�б�ѡ��

	QTreeWidgetItem *items3 = new QTreeWidgetItem(items1,
		QStringList(QString("num_3")));
	items3->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
	items3->setCheckState(0,Qt::Unchecked); //��ʼ״̬û�б�ѡ��


}

//<summary>  
///��ȡ�������� (Ϊ�˷������֣������������GraphicsView��������������������ĸ����󷢳����ź�)
///</summary>  
///
void MainWindow::getActionName()

{
	
	QAction *act=(QAction*) sender();//��ȡ���������Ķ���
	QString actName=act->objectName();//��ȡ����������������֣�����ΪMagnifyAction
	
	
	strList->append(actName);

	
};

//<summary>  
///�������� ʵ��ͼ��ƽ�Ʋ�
///</summary>  
///<param name="event">�������¼�</param
void MainWindow::panPicSlot()

{
	//�ж��Ƿ��Ѿ���ͼ������
	if(fileName.isEmpty())
	{
		QMessageBox::information(this,"Error Message","Please select a file");
		return;
	}
	
	getActionName();

}

//<summary>  
///�������� ʵ��ͼ��Ŵ�� 
///</summary>  
///<param name="event">�������¼�</param>  
void MainWindow::MagnifyActionSlot()

{
	//�ж��Ƿ��Ѿ���ͼ������
	if(fileName.isEmpty())
	{
		QMessageBox::information(this,"Error Message","Please select a file");
		return;
	}

	getActionName();
	ui.graphicsView->setDragMode(QGraphicsView::NoDrag); 

	cursor.setShape(Qt::ArrowCursor);	
			
}

//<summary>  
///�������� ʵ��ͼ��ѡ��ROI��
///</summary>  

void MainWindow::NewROIActionSlot()

{
	//�ж��Ƿ��Ѿ���ͼ������
	if(fileName.isEmpty())
	{
		QMessageBox::information(this,"��ʾ","��ѡ����Ҫ�򿪵��ļ�");
		return;
	}

	getActionName();



}

//���Ӱ�������¼�������
void MainWindow::mousePressEvent(QMouseEvent *event)
{
	//strList=new QStringList();
	//�ҵ�scrollArea����Ļ���ϵľ��ε�λ�ã������˾��ε����Ͻǵ������
	QRect *rect=new QRect(ui.scrollArea->pos()+ui.centralWidget->pos(),ui.scrollArea->size());
	
	currentPos = event->pos();
	qDebug()<<"mousePressEvent"<<endl;
	if ( rect->contains(currentPos))//������ĵ���scrollArea�ľ��η�Χ�ڣ��򷢳��ź�
	{
		emit clicked();
	}
	
	else
	{
		return;
	}
}

//<summary>  
///��������Graphicsview�ϰ�����������Ӧ�¼�
///</summary>  
///<param name="event">�������¼�</param> 
void MainWindow::mousePressEventSlot()
{
	mouseGrabber();
	//strList�ĳ�ʼ��������mousePressEventSlot()
	if (strList->size()==0)
	{
		QMessageBox::information(this,"Error Message","��������Ĳ���");
	}
	ui.graphicsView->setDragMode(QGraphicsView::NoDrag); 

	cursor.setShape(Qt::ArrowCursor);	
	QString temp="";
	if (strList->count()==0)
	{
		return;
	}

	if (strList->count()>0)
	{
		int nstrList=strList->count();
		temp=strList->at(nstrList-1);
	}
	
	if (temp=="PanAction")
	{
		cursor.setShape(Qt::ClosedHandCursor);
		ui.graphicsView->setDragMode(QGraphicsView::ScrollHandDrag); 
			
	}
	
	
	if (temp=="MagnifyAction")
	{
		
		double dScalefactor=1.2;

		matrix.scale(dScalefactor,dScalefactor);  
		
		pItem->setMatrix(matrix);

		ui.graphicsView->show();

	}

	if (temp=="NewROIAction")//������½�ROI
	{
		
		qDebug()<<"NewROIActon"<<endl;
		//emit(RectMouseIsPressed());
		
		
		/*int x=currentPos.x();
		int y=currentPos.y();
		const QRectF *rect=new QRectF (currentPos,QSizeF(100,100));
		qDebug()<<"createrect"<<endl;
		QGraphicsRectItem *item_rect=new QGraphicsRectItem();
		item_rect->setRect(QRectF (currentPos,QSizeF(0,0)));*/
		

		
		//pScene->addItem(item_rect);
		//qDebug()<<"Scene added item"<<endl;
		//ui.graphicsView->setScene(pScene);*/
		
		//mouseMoveEvent(QGraphicsSceneMouseEvent *event);
	
	}


}

void MainWindow::isPressed()
{
	qDebug()<<"ItemIsclicked in MainWindow"<<endl;
}
//�ۣ���rect����ͷ�ʱִ��
//Ӧ�����ñ�־λ����UIͼƬֹͣ������϶��¼�����Ӧ
void MainWindow::isReleased()
{
	qDebug()<<"ItemIsRelease in MainWindow"<<endl;
}
void MainWindow::mouseReleaseEvent(QMouseEvent * event)
{
	releaseMouse();
/*int x=currentPos.x();
		int y=currentPos.y();
		const QRectF *rect=new QRectF (currentPos,QSizeF(100,100));
		qDebug()<<"createrect"<<endl;
		QGraphicsRectItem *item_rect=new QGraphicsRectItem();
		item_rect->setRect(QRectF (currentPos,QSizeF(0,0)));*/
			qDebug()<<"mouseReleaseEvent"<<endl;
	//strList=new QStringList();
	//�ҵ�scrollArea����Ļ���ϵľ��ε�λ�ã������˾��ε����Ͻǵ������
	QRect *rect=new QRect(ui.scrollArea->pos()+ui.centralWidget->pos(),ui.scrollArea->size());

	currentPos = event->pos();
	
	if ( rect->contains(currentPos))//������ĵ���scrollArea�ľ��η�Χ�ڣ��򷢳��ź�
	{
		emit released();
	}

	else
	{
		return;
	}
	
}
/*void MainWindow::mouseReleaseEventSlot()
{
	qDebug()<<"mouseReleaseEvent"<<endl;
	
	//strList�ĳ�ʼ��������mousePressEventSlot()
	//if (strList->size()==0)
	//{
		//QMessageBox::information(this,"Error Message","��������Ĳ���");
	//}
	/*ui.graphicsView->setDragMode(QGraphicsView::NoDrag); 

	cursor.setShape(Qt::ArrowCursor);	
	QString temp="";
	if (strList->count()==0)
	{
		return;
	}

	if (strList->count()>0)
	{
		int nstrList=strList->count();
		temp=strList->at(nstrList-1);
	}

	if (temp=="PanAction")
	{
		cursor.setShape(Qt::ClosedHandCursor);
		ui.graphicsView->setDragMode(QGraphicsView::ScrollHandDrag); 

	}
}*/

/*void MainWindow::paintEvent(QPaintEvent * event)
{
	paint=new QPainter;
	paint->begin(this);
	paint->setPen(QPen(Qt::blue,4,Qt::DashLine));//���û�����ʽ 
	paint->setBrush(QBrush(Qt::red,Qt::SolidPattern));//���û�ˢ��ʽ 
	paint->drawRect(20,20,160,160);
	paint->end();

}*/


/*void MainWindow::mouseReleaseEvent( QMouseEvent *event )  
{  
	if ( event->button() == Qt::LeftButton)  
	{  
		ui.graphicsView->setDragMode(QGraphicsView::NoDrag); 

	}  
}  

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
	if (graphicsView->dragMode() ==QGraphicsView::ScrollHandDrag)
	{
		QPoint temp;
		int x1;
		x1=event->x();//����ƶ����λ��
		int dx=x1-x0;
		graphicsView->horizontalScrollBar()->setValue(graphicsView->horizontalScrollBar()->value()+dx);

	}


}*/

//<summary>  
///�����¼������� 
///</summary>  
///<param name="obj">�ؼ�����</param>  
///<param name="event">�ؼ��¼�</param>  
/*bool MainWindow::eventFilter(QObject *obj,QEvent *event)
{
	if (obj==ui.PanAction)//�����ͼ��ƽ�Ʋ���

	{
		qDebug()<<"Pan"<<endl;
		QMouseEvent *mouseEvent=static_cast<QMouseEvent *>(event);
		if(mouseEvent->button()==Qt::LeftButton)
		{
			
			QCursor cursor;
			cursor.setShape(Qt::ClosedHandCursor);
			QApplication::setOverrideCursor(cursor);
			x0=mouseEvent->x();//�����ʼλ��
		
			if (graphicsView==NULL)
			{
				return false;
			}
			ui.graphicsView->setDragMode(QGraphicsView::ScrollHandDrag); 

			return false; 
		}

		
	}
	else 	if (obj==ui.MagnifyAction)
	{
			{
				qDebug()<<"Mag"<<endl;
				QMouseEvent *mouseEvent=static_cast<QMouseEvent *>(event);
				//if(mouseEvent->type()==QEvent::MouseButtonPress)
				if(mouseEvent->button()==Qt::LeftButton)
				{
				//x0=mouseEvent->x();//
				//y0=mouseEvent->y();

				//Ϊ��ͼ���ó���
				QGraphicsView *graphicsView=new QGraphicsView (this);

				QMatrix matrix;  
				double dScalefactor=1.5;

				matrix.scale(dScalefactor,dScalefactor);  
				pItem->setMatrix(matrix);

				ui.graphicsView->show();
				return false;
				}

			}
		
		
	}
		else return QMainWindow::eventFilter(obj,event);
	
	}*/
	



/*void MainWindow::treeItemChanged(QTreeWidgetItem* item,int column)
{
	//QString itemText = item->text(0);
	if(Qt::Checked == item->checkState(0))
	{
		// QTreeWidgetItem* parent = item->parent();
		int count = item->childCount(); //��������ĸ���
		if(count >0)
		{
			for(int i=0; i<count; i++)
			{
				item->child(i)->setCheckState(0,Qt::Checked);
			}
		}
		else
		{
			updateParentItem(item);
		}
	}
	else if(Qt::Unchecked == item->checkState(0))
	{
		int count = item->childCount();
		if(count > 0)
		{
			for(int i=0; i<count; i++)
			{
				item->child(i)->setCheckState(0,Qt::Unchecked);
			}
		}
		else
		{
			updateParentItem(item);
		}
	}
}*/


/*void MainWindow::updateParentItem(QTreeWidgetItem* item)
{
	QTreeWidgetItem *parent = item->parent();
	if(parent == NULL)
	{
		return ;
	}

	int selectedCount = 0;
	int childCount = parent->childCount();
	for(int i=0;i<childCount;i++) //�ж��ж��ٸ����ѡ��
	{
		QTreeWidgetItem* childItem = parent->child(i);
		if(childItem->checkState(0) == Qt::Checked)
		{
			selectedCount++;
		}
	}
	if(selectedCount <= 0)  //���û�����ѡ�У���������Ϊδѡ��״̬
	{
		parent->setCheckState(0,Qt::Unchecked);
	}
	else if(selectedCount>0 && selectedCount<childCount)    //����в������ѡ�У���������Ϊ����ѡ��״̬�����û�ɫ��ʾ
	{
		parent->setCheckState(0,Qt::PartiallyChecked);
	}
	else if(selectedCount == childCount)    //�������ȫ����ѡ�У�����������Ϊѡ��״̬
	{
		parent->setCheckState(0,Qt::Checked);
	}
}*/

void  MainWindow::ShowTree(const QString filename,int nBandCount)
{
	if(filename==""||nBandCount==0)
	{
		return;
	}
	treeView=new QTreeView(this);

	QFileInfo fileInfo(filename);
	qDebug()<<filename<<endl;
    model = new QStandardItemModel(nBandCount,0); 

	QStandardItem *rootItem=new QStandardItem(filename);
	
	for(int i=0;i<nBandCount;i++)
	{
		QStandardItem *childItem = new QStandardItem (tr("Band %0").arg(i+1));
		
		rootItem->setChild(i,childItem);
		int m=rootItem->rowCount();
	}
	 model->setItem(0,rootItem);
	 ui.treeView->setModel(model);	
	 ui.treeView->show();
	
}
///<summary>  
/// ��ȡͼ���ļ�  
///</summary>  
///<param name="filename">ͼ���ļ�</param>  
/*void MainWindow::ReadImg(const QString filename)
{

	GDALAllRegister();  
	CPLSetConfigOption("GDAL_FILENAME_IS_UTF8", "NO" );  
	poDataset = ( GDALDataset* )GDALOpen(filename.toStdString().c_str(),GA_ReadOnly );  
	if ( poDataset == NULL )  
	{  
		QMessageBox::critical( this, tr("Error!" ), tr( "Can not open file %1" ).arg(filename) );  
		return;  
	}  

	
	//ShowFileList( imgPath );  
	//ShowImgInfor( imgPath );  
	// ���ͼ���ļ������������Σ���Ĭ��ֻ��ʾ��һ���λҶ�ͼ��  
	if ( poDataset->GetRasterCount() != 3 )  
	{  
		m_showColor = false;  
		ShowBand( poDataset->GetRasterBand(1 ) );  
	}  
	// ���ͼ�������������Σ���Ĭ����RGB��˳����ʾ��ɫͼ  
	else  
	{  
		m_showColor = true;  
		QList<GDALRasterBand*> bandList;  
		bandList.append(poDataset->GetRasterBand( 1 ) );  
		bandList.append(poDataset->GetRasterBand( 2 ) );  
		bandList.append(poDataset->GetRasterBand( 3 ) );  
		ShowImg( &bandList );  
	}  
	GDALClose( poDataset );  
}*/
///<summary>  
///��ʾ������ͼ��  
///</summary>  
///<param name="band">ͼ�񲨶�</param>  
/*void MainWindow::ShowBand( GDALRasterBand* band )  
{  
	if ( band == NULL )  
	{  
		return;  
	}  

	QList<GDALRasterBand*> myBand;  
	myBand.append( band );  
	myBand.append( band );  
	myBand.append( band );  

	ShowImg( &myBand );  

}*/

///<summary>  
/// ��ʾͼ��  
///</summary>  
///<param name="imgBand">ͼ�񲨶�</param>  
/*void MainWindow::ShowImg( QList<GDALRasterBand*> *imgBand )  
{  
	if ( imgBand->size() != 3 )  
	{  
		return;  
	}  
	//��ȡ�ò���ͼ��ĳ��Ϳ�
	int imgWidth = imgBand->at( 0)->GetXSize();  
	int imgHeight = imgBand->at( 0)->GetYSize();  

	m_scaleFactor = this->height() * 1.0 /imgHeight;  

	int iScaleWidth = ( int )( imgWidth *m_scaleFactor - 1 );  
	int iScaleHeight = ( int )( imgHeight *m_scaleFactor - 1 );  
	
	//��ȡӰ����������
	GDALDataType dataType = imgBand->at( 0)->GetRasterDataType();  

	// ���ȷֱ��ȡRGB��������  
	float* rBand = new float[iScaleWidth *iScaleHeight];  
	float* gBand = new float[iScaleWidth *iScaleHeight];  
	float* bBand = new float[iScaleWidth *iScaleHeight];  

	unsigned char *rBandUC, *gBandUC, *bBandUC;  

	// �����Ƿ���ʾ��ɫͼ���ж�RGB�������ε���ɷ�ʽ�����ֱ��ȡ  
	if ( m_showColor == true )  
	{  
		imgBand->at( 0 )->RasterIO(GF_Read, 0, 0, imgWidth, imgHeight, rBand , iScaleWidth, iScaleHeight,GDT_Float32, 0, 0 );  
		imgBand->at( 1 )->RasterIO(GF_Read, 0, 0, imgWidth, imgHeight, gBand, iScaleWidth, iScaleHeight,GDT_Float32, 0, 0 );  
		imgBand->at( 2 )->RasterIO(GF_Read, 0, 0, imgWidth, imgHeight, bBand, iScaleWidth, iScaleHeight,GDT_Float32, 0, 0 );  

		// �ֱ�����ÿ�����β���Floatת��Ϊunsigned char  
		//rBandUC = ImgSketch( rBand,imgBand->at( 0 ), iScaleWidth * iScaleHeight, imgBand->at( 0)->GetNoDataValue() );  
		//gBandUC = ImgSketch( gBand,imgBand->at( 1 ), iScaleWidth * iScaleHeight, imgBand->at( 1)->GetNoDataValue() );  
		//bBandUC = ImgSketch( bBand,imgBand->at( 2 ), iScaleWidth * iScaleHeight, imgBand->at( 2)->GetNoDataValue() );  
	}  
	else  
	{  
		imgBand->at( 0 )->RasterIO(GF_Read, 0, 0, imgWidth, imgHeight, rBand , iScaleWidth, iScaleHeight,GDT_Float32, 0, 0 );  

		//rBandUC = ImgSketch( rBand,imgBand->at( 0 ), iScaleWidth * iScaleHeight, imgBand->at( 0)->GetNoDataValue() );  
		//gBandUC = rBandUC;  
		//bBandUC = rBandUC;  
	}  

	// �����������������  
	/*int bytePerLine = ( iScaleWidth * 24 + 31 )/ 8;  
	unsigned char* allBandUC = new unsigned char[bytePerLine * iScaleHeight * 3];  
	for( int h = 0; h < iScaleHeight; h++ )  
	{  
		for( int w = 0; w < iScaleWidth; w++)  
		{  
			allBandUC[h * bytePerLine + w * 3 +0] = rBandUC[h * iScaleWidth + w];  
			allBandUC[h * bytePerLine + w * 3 +1] = gBandUC[h * iScaleWidth + w];  
			allBandUC[h * bytePerLine + w * 3 +2] = bBandUC[h * iScaleWidth + w];  
		}  
	}  

	// ����ͼ����ʾ  
	//QGraphicsPixmapItem *imgItem = new QGraphicsPixmapItem (QPixmap::fromImage(QImage( allBandUC, iScaleWidth, iScaleHeight, bytePerLine,QImage::Format_RGB888  ) ) );  
	//QGraphicsScene *myScene = new QGraphicsScene();  
	//myScene->addItem( imgItem );  
	//this->setScene( myScene );  


}  */
