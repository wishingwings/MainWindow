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
	QString fileName=QFileDialog::getOpenFileName(this,"Open File",QDir::currentPath()); // 在mainwindow.h已定义
	qDebug()<<"fileName is"<<fileName;

	if(fileName.isEmpty())
	{

		QMessageBox::information(this,"Error Message","Please select a file");
		return;
	}


	else
	{
		QImage *img=new QImage;
		
		if(! ( img->load(fileName) ) ) //加载图像
		{
			QMessageBox::information(this,
				tr("打开图像失败"),
				tr("打开图像失败!"));
			delete img;
			return;
		}

		GDALAllRegister();         //利用GDAL读取图片，先要进行注册  

		//CPLSetConfigOption("GDAL_FILENAME_IS_UTF8","NO");   //设置支持中文路径  

		GDALDataset *poDataset;

		GDALRasterBand  *poBand;
		GDALAllRegister();
		
		QByteArray ba=fileName.toLatin1();
		char *mm=ba.data();
		qDebug()<<mm<<endl;

		poDataset=(GDALDataset*)GDALOpen(mm,GA_ReadOnly);

		//获取图像的大小
		int width=poDataset->GetRasterXSize();    
		int height=poDataset->GetRasterYSize();     
		

		//获取图像的波段数
		int nBandCount=poDataset->GetRasterCount();
		qDebug()<<nBandCount<<endl;	

		//获取影像数据类型
		poBand=poDataset->GetRasterBand(1);
		poBand -> GetRasterDataType();
				
		//获得显示图像的GraphicsView实际尺寸
	    int widthGraphicsView=ui.graphicsView->size().width();
		int heightGraphicsView=ui.graphicsView->size().height();



		int bytePerLine = (width * 24 + 31 )/ 8;  
		unsigned char* allBandUC = new unsigned char[bytePerLine * height];  

		//int y=ui.graphicsView->y();
		//QPoint GlobalPoint=(graphicsView->mapToGlobal(QPoint(0, 0)));//获取控件在窗体中的坐标
		//int x = GlobalPoint.x();
		//int y = GlobalPoint.y(); 

		//unsigned char* allBandUC = new unsigned char[width* height];  

		
		poBand ->RasterIO(GF_Read,0,0, width, height,allBandUC, width, height, GDT_Byte, 0, 0);

		QGraphicsPixmapItem *pItem=new QGraphicsPixmapItem( QPixmap::fromImage(QImage (allBandUC,width,height,QImage::Format_RGB888)));

		//QGraphicsPixmapItem *pItem=new QGraphicsPixmapItem( QPixmap::fromImage(QImage (allBandUC,width,height,bytePerLine,QImage::Format_RGB888)));
		
		//将item添加至场景中
		QGraphicsScene *pScene=new QGraphicsScene();
		pScene->addItem(pItem);

		//为视图设置场景		
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
	ui.treeWidget->clear();    //初始化树形控件
	ui.treeWidget->show();

	//addTreeRoot
	//ui.treeWidget->setHeaderLabel("tree");
	//ui.treeWidget->setHeaderHidden(1); // TreeWidget 标题设置 1为隐藏Header标题 0 为显示Header标题

	QTreeWidgetItem *items1 = new QTreeWidgetItem(ui.treeWidget,
		QStringList(QString("num_1")));
	items1->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
	items1->setCheckState(0,Qt::Unchecked); //初始状态没有被选中

	QTreeWidgetItem *items2 = new QTreeWidgetItem(items1,
		QStringList(QString("num_2")));
	items2->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
	items2->setCheckState(0,Qt::Unchecked); //初始状态没有被选中

	QTreeWidgetItem *items3 = new QTreeWidgetItem(items1,
		QStringList(QString("num_3")));
	items3->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
	items3->setCheckState(0,Qt::Unchecked); //初始状态没有被选中


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
		int count = item->childCount(); //返回子项的个数
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
	for(int i=0;i<childCount;i++) //判断有多少个子项被选中
	{
		QTreeWidgetItem* childItem = parent->child(i);
		if(childItem->checkState(0) == Qt::Checked)
		{
			selectedCount++;
		}
	}
	if(selectedCount <= 0)  //如果没有子项被选中，父项设置为未选中状态
	{
		parent->setCheckState(0,Qt::Unchecked);
	}
	else if(selectedCount>0 && selectedCount<childCount)    //如果有部分子项被选中，父项设置为部分选中状态，即用灰色显示
	{
		parent->setCheckState(0,Qt::PartiallyChecked);
	}
	else if(selectedCount == childCount)    //如果子项全部被选中，父项则设置为选中状态
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
/// 读取图像文件  
///</summary>  
///<param name="filename">图像文件</param>  
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
	// 如果图像文件并非三个波段，则默认只显示第一波段灰度图像  
	if ( poDataset->GetRasterCount() != 3 )  
	{  
		m_showColor = false;  
		ShowBand( poDataset->GetRasterBand(1 ) );  
	}  
	// 如果图像正好三个波段，则默认以RGB的顺序显示彩色图  
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
///显示单波段图像  
///</summary>  
///<param name="band">图像波段</param>  
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
/// 显示图像  
///</summary>  
///<param name="imgBand">图像波段</param>  
/*void MainWindow::ShowImg( QList<GDALRasterBand*> *imgBand )  
{  
	if ( imgBand->size() != 3 )  
	{  
		return;  
	}  
	//获取该波段图像的长和宽
	int imgWidth = imgBand->at( 0)->GetXSize();  
	int imgHeight = imgBand->at( 0)->GetYSize();  

	m_scaleFactor = this->height() * 1.0 /imgHeight;  

	int iScaleWidth = ( int )( imgWidth *m_scaleFactor - 1 );  
	int iScaleHeight = ( int )( imgHeight *m_scaleFactor - 1 );  
	
	//获取影像数据类型
	GDALDataType dataType = imgBand->at( 0)->GetRasterDataType();  

	// 首先分别读取RGB三个波段  
	float* rBand = new float[iScaleWidth *iScaleHeight];  
	float* gBand = new float[iScaleWidth *iScaleHeight];  
	float* bBand = new float[iScaleWidth *iScaleHeight];  

	unsigned char *rBandUC, *gBandUC, *bBandUC;  

	// 根据是否显示彩色图像，判断RGB三个波段的组成方式，并分别读取  
	if ( m_showColor == true )  
	{  
		imgBand->at( 0 )->RasterIO(GF_Read, 0, 0, imgWidth, imgHeight, rBand , iScaleWidth, iScaleHeight,GDT_Float32, 0, 0 );  
		imgBand->at( 1 )->RasterIO(GF_Read, 0, 0, imgWidth, imgHeight, gBand, iScaleWidth, iScaleHeight,GDT_Float32, 0, 0 );  
		imgBand->at( 2 )->RasterIO(GF_Read, 0, 0, imgWidth, imgHeight, bBand, iScaleWidth, iScaleHeight,GDT_Float32, 0, 0 );  

		// 分别拉伸每个波段并将Float转换为unsigned char  
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

	// 将三个波段组合起来  
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

	// 构造图像并显示  
	//QGraphicsPixmapItem *imgItem = new QGraphicsPixmapItem (QPixmap::fromImage(QImage( allBandUC, iScaleWidth, iScaleHeight, bytePerLine,QImage::Format_RGB888  ) ) );  
	//QGraphicsScene *myScene = new QGraphicsScene();  
	//myScene->addItem( imgItem );  
	//this->setScene( myScene );  


}  */
