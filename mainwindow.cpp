#include "mainwindow.h"
#include "gdal.h"
#include "gdal_priv.h"



MainWindow::MainWindow(QWidget *parent, Qt::WFlags flags)
	: QMainWindow(parent, flags)
{
	ui.setupUi(this);
	
	QToolBar *pToolBar=addToolBar(tr("&File"));
	
	
	QObject::connect(ui.openAction,SIGNAL(triggered()),this,SLOT(openFileSlot()));
    //QObject::connect(ui.treeWidget,SIGNAL(itemChanged(QTreeWidgetItem*,int)),this,SLOT(treeItemChanged(QTreeWidgetItem*,int)));
	
	//ShowTree(fileName,nBandCount);
	
	QObject::connect(ui.PanAction,SIGNAL(triggered()),this,SLOT(panPicSlot()));
}

MainWindow::~MainWindow()
{
	
}




void MainWindow::openFileSlot()
{
	qDebug()<<"fileName is";
	//get file name
	QString fileName=QFileDialog::getOpenFileName(this,"Open File",QDir::currentPath()); // ��mainwindow.h�Ѷ���
	qDebug()<<"fileName is"<<fileName;

	if(fileName.isEmpty())
	{

		QMessageBox::information(this,"Error Message","Please select a file");
		return;
	}


	else
	{
		QImage *img=new QImage;
		
		if(! ( img->load(fileName) ) ) //����ͼ��
		{
			QMessageBox::information(this,
				tr("��ͼ��ʧ��"),
				tr("��ͼ��ʧ��!"));
			delete img;
			return;
		}

		GDALAllRegister();         //����GDAL��ȡͼƬ����Ҫ����ע��  

		//CPLSetConfigOption("GDAL_FILENAME_IS_UTF8","NO");   //����֧������·��  

		GDALDataset *poDataset;

		GDALRasterBand  *poBand;
		GDALAllRegister();
		
		QByteArray ba=fileName.toLatin1();
		char *mm=ba.data();
		qDebug()<<mm<<endl;

		poDataset=(GDALDataset*)GDALOpen(mm,GA_ReadOnly);

		//��ȡͼ��Ĵ�С
		int width=poDataset->GetRasterXSize();    
		int height=poDataset->GetRasterYSize();     
		

		//��ȡͼ��Ĳ�����
		int nBandCount=poDataset->GetRasterCount();
		qDebug()<<nBandCount<<endl;	

		//��ȡӰ����������
		poBand=poDataset->GetRasterBand(1);
		poBand -> GetRasterDataType();
				
		//�����ʾͼ���GraphicsViewʵ�ʳߴ�
	    int widthGraphicsView=ui.graphicsView->size().width();
		int heightGraphicsView=ui.graphicsView->size().height();



		int bytePerLine = (width * 24 + 31 )/ 8;  
		unsigned char* allBandUC = new unsigned char[bytePerLine * height];  

		//int y=ui.graphicsView->y();
		//QPoint GlobalPoint=(graphicsView->mapToGlobal(QPoint(0, 0)));//��ȡ�ؼ��ڴ����е�����
		//int x = GlobalPoint.x();
		//int y = GlobalPoint.y(); 

		//unsigned char* allBandUC = new unsigned char[width* height];  

		
		poBand ->RasterIO(GF_Read,0,0, width, height,allBandUC, width, height, GDT_Byte, 0, 0);

		QGraphicsPixmapItem *pItem=new QGraphicsPixmapItem( QPixmap::fromImage(QImage (allBandUC,width,height,QImage::Format_RGB888)));

		//QGraphicsPixmapItem *pItem=new QGraphicsPixmapItem( QPixmap::fromImage(QImage (allBandUC,width,height,bytePerLine,QImage::Format_RGB888)));
		
		//��item�����������
		QGraphicsScene *pScene=new QGraphicsScene();
		pScene->addItem(pItem);

		//Ϊ��ͼ���ó���		
		QGraphicsView *graphicsView=new QGraphicsView ();
		ui.graphicsView->setScene(pScene);
			
		qDebug()<<"pic width is"<<img->width();
		qDebug()<<"pic height is"<<img->height();

		//ShowImg(imgBand);
		//ui.label->setPixmap(QPixmap::fromImage(*img));
		//ui.label->setPixmap(QPixmap::fromImage(*img));
		ShowTree(fileName,nBandCount);
			

	}

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


void MainWindow::panPicSlot()

{


}

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
