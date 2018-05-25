/********************************************************************************
** Form generated from reading UI file 'ParasDlg.ui'
**
** Created: Thu May 24 21:19:08 2018
**      by: Qt User Interface Compiler version 4.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PARASDLG_H
#define UI_PARASDLG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QDialog>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QTabWidget>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ParasDlg
{
public:
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *spacerItem;
    QPushButton *okButton;
    QPushButton *cancelButton;
    QTabWidget *tabWidget;
    QWidget *ProjectPara;
    QComboBox *ChooseCamera;
    QLabel *ChooseSATLbl;
    QLabel *ChooseCameraLbl;
    QComboBox *ChooseSAT;
    QComboBox *SpectralResponseFunction;
    QLabel *SpectralResponseFunctionLbl;
    QGroupBox *groupBox;
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout;
    QLineEdit *focus;
    QLineEdit *MainPointX;
    QLabel *label_4;
    QLabel *PixelSizeLbl;
    QLabel *label_10;
    QLabel *focusLbl;
    QLineEdit *PixelSize;
    QLabel *MainPointXLbl;
    QLabel *label_15;
    QWidget *FlightPara;
    QGroupBox *groupBox_2;
    QGroupBox *groupBox_3;
    QWidget *gridLayoutWidget_2;
    QGridLayout *gridLayout_2;
    QLabel *longitudeLbl;
    QLineEdit *longitude;
    QLabel *label_11;
    QLineEdit *height;
    QLabel *latitudeLbl;
    QLabel *label_5;
    QLineEdit *latitude;
    QLabel *heightLbl;
    QLabel *label_16;
    QLabel *label_17;
    QLineEdit *GroundElevation;
    QLabel *GroundElevationLbl;

    void setupUi(QDialog *ParasDlg)
    {
        if (ParasDlg->objectName().isEmpty())
            ParasDlg->setObjectName(QString::fromUtf8("ParasDlg"));
        ParasDlg->resize(808, 848);
        layoutWidget = new QWidget(ParasDlg);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(171, 801, 333, 33));
        horizontalLayout = new QHBoxLayout(layoutWidget);
        horizontalLayout->setSpacing(7);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        spacerItem = new QSpacerItem(131, 31, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(spacerItem);

        okButton = new QPushButton(layoutWidget);
        okButton->setObjectName(QString::fromUtf8("okButton"));

        horizontalLayout->addWidget(okButton);

        cancelButton = new QPushButton(layoutWidget);
        cancelButton->setObjectName(QString::fromUtf8("cancelButton"));

        horizontalLayout->addWidget(cancelButton);

        tabWidget = new QTabWidget(ParasDlg);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabWidget->setGeometry(QRect(0, 0, 800, 771));
        ProjectPara = new QWidget();
        ProjectPara->setObjectName(QString::fromUtf8("ProjectPara"));
        ChooseCamera = new QComboBox(ProjectPara);
        ChooseCamera->setObjectName(QString::fromUtf8("ChooseCamera"));
        ChooseCamera->setGeometry(QRect(100, 100, 191, 21));
        ChooseSATLbl = new QLabel(ProjectPara);
        ChooseSATLbl->setObjectName(QString::fromUtf8("ChooseSATLbl"));
        ChooseSATLbl->setGeometry(QRect(30, 50, 72, 20));
        ChooseCameraLbl = new QLabel(ProjectPara);
        ChooseCameraLbl->setObjectName(QString::fromUtf8("ChooseCameraLbl"));
        ChooseCameraLbl->setGeometry(QRect(30, 100, 72, 16));
        ChooseSAT = new QComboBox(ProjectPara);
        ChooseSAT->setObjectName(QString::fromUtf8("ChooseSAT"));
        ChooseSAT->setGeometry(QRect(100, 50, 191, 21));
        SpectralResponseFunction = new QComboBox(ProjectPara);
        SpectralResponseFunction->setObjectName(QString::fromUtf8("SpectralResponseFunction"));
        SpectralResponseFunction->setGeometry(QRect(520, 50, 171, 21));
        SpectralResponseFunctionLbl = new QLabel(ProjectPara);
        SpectralResponseFunctionLbl->setObjectName(QString::fromUtf8("SpectralResponseFunctionLbl"));
        SpectralResponseFunctionLbl->setGeometry(QRect(391, 50, 121, 20));
        groupBox = new QGroupBox(ProjectPara);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(30, 150, 671, 271));
        gridLayoutWidget = new QWidget(groupBox);
        gridLayoutWidget->setObjectName(QString::fromUtf8("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(10, 30, 291, 141));
        gridLayout = new QGridLayout(gridLayoutWidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setHorizontalSpacing(7);
        gridLayout->setContentsMargins(0, 0, 0, 0);
        focus = new QLineEdit(gridLayoutWidget);
        focus->setObjectName(QString::fromUtf8("focus"));

        gridLayout->addWidget(focus, 0, 1, 1, 1);

        MainPointX = new QLineEdit(gridLayoutWidget);
        MainPointX->setObjectName(QString::fromUtf8("MainPointX"));

        gridLayout->addWidget(MainPointX, 2, 1, 1, 1);

        label_4 = new QLabel(gridLayoutWidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        gridLayout->addWidget(label_4, 0, 2, 1, 1);

        PixelSizeLbl = new QLabel(gridLayoutWidget);
        PixelSizeLbl->setObjectName(QString::fromUtf8("PixelSizeLbl"));

        gridLayout->addWidget(PixelSizeLbl, 1, 0, 1, 1);

        label_10 = new QLabel(gridLayoutWidget);
        label_10->setObjectName(QString::fromUtf8("label_10"));

        gridLayout->addWidget(label_10, 1, 2, 1, 1);

        focusLbl = new QLabel(gridLayoutWidget);
        focusLbl->setObjectName(QString::fromUtf8("focusLbl"));

        gridLayout->addWidget(focusLbl, 0, 0, 1, 1);

        PixelSize = new QLineEdit(gridLayoutWidget);
        PixelSize->setObjectName(QString::fromUtf8("PixelSize"));

        gridLayout->addWidget(PixelSize, 1, 1, 1, 1);

        MainPointXLbl = new QLabel(gridLayoutWidget);
        MainPointXLbl->setObjectName(QString::fromUtf8("MainPointXLbl"));

        gridLayout->addWidget(MainPointXLbl, 2, 0, 1, 1);

        label_15 = new QLabel(gridLayoutWidget);
        label_15->setObjectName(QString::fromUtf8("label_15"));

        gridLayout->addWidget(label_15, 2, 2, 1, 1);

        tabWidget->addTab(ProjectPara, QString());
        FlightPara = new QWidget();
        FlightPara->setObjectName(QString::fromUtf8("FlightPara"));
        groupBox_2 = new QGroupBox(FlightPara);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        groupBox_2->setGeometry(QRect(10, 10, 771, 271));
        groupBox_3 = new QGroupBox(groupBox_2);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        groupBox_3->setGeometry(QRect(20, 30, 731, 231));
        gridLayoutWidget_2 = new QWidget(groupBox_3);
        gridLayoutWidget_2->setObjectName(QString::fromUtf8("gridLayoutWidget_2"));
        gridLayoutWidget_2->setGeometry(QRect(10, 30, 261, 171));
        gridLayout_2 = new QGridLayout(gridLayoutWidget_2);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        gridLayout_2->setHorizontalSpacing(7);
        gridLayout_2->setContentsMargins(0, 0, 0, 0);
        longitudeLbl = new QLabel(gridLayoutWidget_2);
        longitudeLbl->setObjectName(QString::fromUtf8("longitudeLbl"));

        gridLayout_2->addWidget(longitudeLbl, 0, 0, 1, 1);

        longitude = new QLineEdit(gridLayoutWidget_2);
        longitude->setObjectName(QString::fromUtf8("longitude"));

        gridLayout_2->addWidget(longitude, 0, 1, 1, 1);

        label_11 = new QLabel(gridLayoutWidget_2);
        label_11->setObjectName(QString::fromUtf8("label_11"));

        gridLayout_2->addWidget(label_11, 1, 2, 1, 1);

        height = new QLineEdit(gridLayoutWidget_2);
        height->setObjectName(QString::fromUtf8("height"));

        gridLayout_2->addWidget(height, 2, 1, 1, 1);

        latitudeLbl = new QLabel(gridLayoutWidget_2);
        latitudeLbl->setObjectName(QString::fromUtf8("latitudeLbl"));

        gridLayout_2->addWidget(latitudeLbl, 1, 0, 1, 1);

        label_5 = new QLabel(gridLayoutWidget_2);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        gridLayout_2->addWidget(label_5, 0, 2, 1, 1);

        latitude = new QLineEdit(gridLayoutWidget_2);
        latitude->setObjectName(QString::fromUtf8("latitude"));

        gridLayout_2->addWidget(latitude, 1, 1, 1, 1);

        heightLbl = new QLabel(gridLayoutWidget_2);
        heightLbl->setObjectName(QString::fromUtf8("heightLbl"));

        gridLayout_2->addWidget(heightLbl, 2, 0, 1, 1);

        label_16 = new QLabel(gridLayoutWidget_2);
        label_16->setObjectName(QString::fromUtf8("label_16"));

        gridLayout_2->addWidget(label_16, 2, 2, 1, 1);

        label_17 = new QLabel(gridLayoutWidget_2);
        label_17->setObjectName(QString::fromUtf8("label_17"));

        gridLayout_2->addWidget(label_17, 3, 2, 1, 1);

        GroundElevation = new QLineEdit(gridLayoutWidget_2);
        GroundElevation->setObjectName(QString::fromUtf8("GroundElevation"));

        gridLayout_2->addWidget(GroundElevation, 3, 1, 1, 1);

        GroundElevationLbl = new QLabel(gridLayoutWidget_2);
        GroundElevationLbl->setObjectName(QString::fromUtf8("GroundElevationLbl"));

        gridLayout_2->addWidget(GroundElevationLbl, 3, 0, 1, 1);

        tabWidget->addTab(FlightPara, QString());
        groupBox_2->raise();
        layoutWidget->raise();
        tabWidget->raise();
        layoutWidget->raise();

        retranslateUi(ParasDlg);
        QObject::connect(okButton, SIGNAL(clicked()), ParasDlg, SLOT(accept()));
        QObject::connect(cancelButton, SIGNAL(clicked()), ParasDlg, SLOT(reject()));

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(ParasDlg);
    } // setupUi

    void retranslateUi(QDialog *ParasDlg)
    {
        ParasDlg->setWindowTitle(QApplication::translate("ParasDlg", "Dialog", 0, QApplication::UnicodeUTF8));
        okButton->setText(QApplication::translate("ParasDlg", "OK", 0, QApplication::UnicodeUTF8));
        cancelButton->setText(QApplication::translate("ParasDlg", "Cancel", 0, QApplication::UnicodeUTF8));
        ChooseCamera->clear();
        ChooseCamera->insertItems(0, QStringList()
         << QApplication::translate("ParasDlg", "\347\233\270\346\234\272\344\270\200", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("ParasDlg", "\347\233\270\346\234\272\344\272\214", 0, QApplication::UnicodeUTF8)
        );
        ChooseSATLbl->setText(QApplication::translate("ParasDlg", "\351\200\211\346\213\251\345\215\253\346\230\237", 0, QApplication::UnicodeUTF8));
        ChooseCameraLbl->setText(QApplication::translate("ParasDlg", "\351\200\211\346\213\251\347\233\270\346\234\272", 0, QApplication::UnicodeUTF8));
        ChooseSAT->clear();
        ChooseSAT->insertItems(0, QStringList()
         << QApplication::translate("ParasDlg", "\345\215\253\346\230\237\344\270\200", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("ParasDlg", "\345\215\253\346\230\237\344\272\214", 0, QApplication::UnicodeUTF8)
        );
        SpectralResponseFunction->clear();
        SpectralResponseFunction->insertItems(0, QStringList()
         << QApplication::translate("ParasDlg", "x*6+8", 0, QApplication::UnicodeUTF8)
        );
        SpectralResponseFunctionLbl->setText(QApplication::translate("ParasDlg", "\346\230\237\350\275\275\345\205\211\350\260\261\345\223\215\345\272\224\345\207\275\346\225\260", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("ParasDlg", "GroupBox", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("ParasDlg", "mm", 0, QApplication::UnicodeUTF8));
        PixelSizeLbl->setText(QApplication::translate("ParasDlg", "\345\203\217\347\264\240\345\244\247\345\260\217", 0, QApplication::UnicodeUTF8));
        label_10->setText(QApplication::translate("ParasDlg", "m", 0, QApplication::UnicodeUTF8));
        focusLbl->setText(QApplication::translate("ParasDlg", "\347\204\246\350\267\235", 0, QApplication::UnicodeUTF8));
        MainPointXLbl->setText(QApplication::translate("ParasDlg", "\345\203\217\344\270\273\347\202\271X", 0, QApplication::UnicodeUTF8));
        label_15->setText(QApplication::translate("ParasDlg", "pix", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(ProjectPara), QApplication::translate("ParasDlg", "\345\267\245\347\250\213\345\217\202\346\225\260", 0, QApplication::UnicodeUTF8));
        groupBox_2->setTitle(QApplication::translate("ParasDlg", "\346\265\213\345\214\272\345\217\202\346\225\260", 0, QApplication::UnicodeUTF8));
        groupBox_3->setTitle(QApplication::translate("ParasDlg", "\346\265\213\345\214\272\345\216\237\347\202\271", 0, QApplication::UnicodeUTF8));
        longitudeLbl->setText(QApplication::translate("ParasDlg", "\347\273\217\345\272\246", 0, QApplication::UnicodeUTF8));
        label_11->setText(QApplication::translate("ParasDlg", "\343\202\234", 0, QApplication::UnicodeUTF8));
        latitudeLbl->setText(QApplication::translate("ParasDlg", "\347\272\254\345\272\246", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("ParasDlg", "\343\202\234", 0, QApplication::UnicodeUTF8));
        heightLbl->setText(QApplication::translate("ParasDlg", "\351\253\230\345\272\246", 0, QApplication::UnicodeUTF8));
        label_16->setText(QApplication::translate("ParasDlg", "km", 0, QApplication::UnicodeUTF8));
        label_17->setText(QApplication::translate("ParasDlg", "km", 0, QApplication::UnicodeUTF8));
        GroundElevationLbl->setText(QApplication::translate("ParasDlg", "\345\234\260\350\241\250\351\253\230\347\250\213", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(FlightPara), QApplication::translate("ParasDlg", "\351\243\236\350\241\214\345\217\202\346\225\260", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class ParasDlg: public Ui_ParasDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PARASDLG_H
