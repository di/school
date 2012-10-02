/********************************************************************************
** Form generated from reading ui file 'mainwindow.ui'
**
** Created: Tue Jan 26 14:45:10 2010
**      by: Qt User Interface Compiler version 4.5.3
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QCommandLinkButton>
#include <QtGui/QFrame>
#include <QtGui/QGroupBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QStatusBar>
#include <QtGui/QTabWidget>
#include <QtGui/QTableWidget>
#include <QtGui/QTextEdit>
#include <QtGui/QToolBar>
#include <QtGui/QToolButton>
#include <QtGui/QTreeWidget>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QTabWidget *hhh;
    QWidget *tab;
    QTableWidget *tableWidget;
    QLineEdit *lineEdit;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QToolButton *toolButton;
    QGroupBox *groupBox;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_5;
    QLabel *label_6;
    QLabel *label_7;
    QLabel *label_8;
    QLabel *label_9;
    QLabel *label_10;
    QLabel *label_11;
    QWidget *tab_3;
    QTableWidget *tableWidget_2;
    QPushButton *pushButton_4;
    QLineEdit *lineEdit_2;
    QLabel *label_12;
    QPushButton *pushButton_3;
    QToolButton *toolButton_2;
    QGroupBox *groupBox_2;
    QPushButton *pushButton_5;
    QLabel *label_13;
    QLabel *label_14;
    QLabel *label_16;
    QLabel *label_15;
    QLabel *label_17;
    QLabel *label_18;
    QFrame *line;
    QLabel *label_29;
    QLabel *label_30;
    QLabel *label_31;
    QLabel *label_32;
    QGroupBox *groupBox_3;
    QLabel *label_19;
    QLabel *label_20;
    QLabel *label_21;
    QLabel *label_22;
    QLabel *label_23;
    QLabel *label_24;
    QLabel *label_25;
    QLabel *label_26;
    QLabel *label_27;
    QLabel *label_28;
    QWidget *tab_2;
    QWidget *tab_4;
    QTreeWidget *treeWidget;
    QTabWidget *tabWidget;
    QWidget *tab_5;
    QToolButton *toolButton_3;
    QCheckBox *checkBox;
    QGroupBox *groupBox_4;
    QLabel *label_33;
    QLabel *label_34;
    QLabel *label_35;
    QLabel *label_36;
    QLabel *label_37;
    QLabel *label_38;
    QGroupBox *groupBox_5;
    QLabel *label_39;
    QLabel *label_40;
    QLabel *label_41;
    QLabel *label_42;
    QWidget *tab_6;
    QTextEdit *textEdit;
    QWidget *tab_7;
    QTextEdit *textEdit_2;
    QCommandLinkButton *commandLinkButton;
    QCommandLinkButton *commandLinkButton_2;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QMenu *menuEdit;
    QMenu *menuProcessors;
    QMenu *menuSomething_Cool;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(727, 491);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        hhh = new QTabWidget(centralWidget);
        hhh->setObjectName(QString::fromUtf8("hhh"));
        hhh->setGeometry(QRect(4, 2, 721, 431));
        hhh->setTabShape(QTabWidget::Rounded);
        hhh->setTabsClosable(true);
        hhh->setMovable(true);
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        tableWidget = new QTableWidget(tab);
        if (tableWidget->columnCount() < 6)
            tableWidget->setColumnCount(6);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(5, __qtablewidgetitem5);
        if (tableWidget->rowCount() < 10)
            tableWidget->setRowCount(10);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(0, __qtablewidgetitem6);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(1, __qtablewidgetitem7);
        QTableWidgetItem *__qtablewidgetitem8 = new QTableWidgetItem();
        __qtablewidgetitem8->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter|Qt::AlignCenter);
        tableWidget->setVerticalHeaderItem(2, __qtablewidgetitem8);
        QTableWidgetItem *__qtablewidgetitem9 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(3, __qtablewidgetitem9);
        QTableWidgetItem *__qtablewidgetitem10 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(4, __qtablewidgetitem10);
        QTableWidgetItem *__qtablewidgetitem11 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(5, __qtablewidgetitem11);
        QTableWidgetItem *__qtablewidgetitem12 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(6, __qtablewidgetitem12);
        QTableWidgetItem *__qtablewidgetitem13 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(7, __qtablewidgetitem13);
        QTableWidgetItem *__qtablewidgetitem14 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(8, __qtablewidgetitem14);
        QTableWidgetItem *__qtablewidgetitem15 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(9, __qtablewidgetitem15);
        QTableWidgetItem *__qtablewidgetitem16 = new QTableWidgetItem();
        tableWidget->setItem(0, 0, __qtablewidgetitem16);
        QTableWidgetItem *__qtablewidgetitem17 = new QTableWidgetItem();
        tableWidget->setItem(0, 1, __qtablewidgetitem17);
        QTableWidgetItem *__qtablewidgetitem18 = new QTableWidgetItem();
        tableWidget->setItem(0, 2, __qtablewidgetitem18);
        QTableWidgetItem *__qtablewidgetitem19 = new QTableWidgetItem();
        tableWidget->setItem(0, 3, __qtablewidgetitem19);
        QTableWidgetItem *__qtablewidgetitem20 = new QTableWidgetItem();
        tableWidget->setItem(0, 4, __qtablewidgetitem20);
        QTableWidgetItem *__qtablewidgetitem21 = new QTableWidgetItem();
        tableWidget->setItem(0, 5, __qtablewidgetitem21);
        QTableWidgetItem *__qtablewidgetitem22 = new QTableWidgetItem();
        tableWidget->setItem(1, 0, __qtablewidgetitem22);
        QTableWidgetItem *__qtablewidgetitem23 = new QTableWidgetItem();
        tableWidget->setItem(1, 1, __qtablewidgetitem23);
        QTableWidgetItem *__qtablewidgetitem24 = new QTableWidgetItem();
        tableWidget->setItem(1, 2, __qtablewidgetitem24);
        QTableWidgetItem *__qtablewidgetitem25 = new QTableWidgetItem();
        tableWidget->setItem(1, 3, __qtablewidgetitem25);
        QTableWidgetItem *__qtablewidgetitem26 = new QTableWidgetItem();
        tableWidget->setItem(1, 4, __qtablewidgetitem26);
        QTableWidgetItem *__qtablewidgetitem27 = new QTableWidgetItem();
        tableWidget->setItem(1, 5, __qtablewidgetitem27);
        QTableWidgetItem *__qtablewidgetitem28 = new QTableWidgetItem();
        tableWidget->setItem(2, 0, __qtablewidgetitem28);
        QTableWidgetItem *__qtablewidgetitem29 = new QTableWidgetItem();
        tableWidget->setItem(2, 1, __qtablewidgetitem29);
        QTableWidgetItem *__qtablewidgetitem30 = new QTableWidgetItem();
        tableWidget->setItem(2, 2, __qtablewidgetitem30);
        QTableWidgetItem *__qtablewidgetitem31 = new QTableWidgetItem();
        tableWidget->setItem(2, 3, __qtablewidgetitem31);
        QTableWidgetItem *__qtablewidgetitem32 = new QTableWidgetItem();
        tableWidget->setItem(2, 4, __qtablewidgetitem32);
        QTableWidgetItem *__qtablewidgetitem33 = new QTableWidgetItem();
        tableWidget->setItem(2, 5, __qtablewidgetitem33);
        tableWidget->setObjectName(QString::fromUtf8("tableWidget"));
        tableWidget->setGeometry(QRect(0, 50, 701, 251));
        lineEdit = new QLineEdit(tab);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        lineEdit->setGeometry(QRect(48, 11, 435, 22));
        pushButton = new QPushButton(tab);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(531, 10, 80, 26));
        pushButton_2 = new QPushButton(tab);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setGeometry(QRect(622, 10, 79, 26));
        toolButton = new QToolButton(tab);
        toolButton->setObjectName(QString::fromUtf8("toolButton"));
        toolButton->setGeometry(QRect(493, 10, 30, 25));
        groupBox = new QGroupBox(tab);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(0, 310, 701, 80));
        label = new QLabel(groupBox);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(13, 18, 91, 16));
        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(100, 16, 168, 20));
        label_2->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_3 = new QLabel(groupBox);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(302, 18, 20, 20));
        label_4 = new QLabel(groupBox);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(316, 20, 106, 16));
        label_4->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_5 = new QLabel(groupBox);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(445, 18, 34, 20));
        label_6 = new QLabel(groupBox);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(480, 20, 106, 16));
        label_6->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_7 = new QLabel(groupBox);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setGeometry(QRect(14, 42, 123, 16));
        label_8 = new QLabel(groupBox);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setGeometry(QRect(143, 43, 57, 16));
        label_9 = new QLabel(groupBox);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setGeometry(QRect(232, 42, 135, 16));
        label_10 = new QLabel(groupBox);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        label_10->setGeometry(QRect(373, 42, 57, 16));
        label_11 = new QLabel(tab);
        label_11->setObjectName(QString::fromUtf8("label_11"));
        label_11->setGeometry(QRect(0, 13, 57, 16));
        QFont font;
        font.setPointSize(13);
        label_11->setFont(font);
        label_11->setTextFormat(Qt::PlainText);
        hhh->addTab(tab, QString());
        tab_3 = new QWidget();
        tab_3->setObjectName(QString::fromUtf8("tab_3"));
        tableWidget_2 = new QTableWidget(tab_3);
        if (tableWidget_2->columnCount() < 4)
            tableWidget_2->setColumnCount(4);
        QTableWidgetItem *__qtablewidgetitem34 = new QTableWidgetItem();
        tableWidget_2->setHorizontalHeaderItem(0, __qtablewidgetitem34);
        QTableWidgetItem *__qtablewidgetitem35 = new QTableWidgetItem();
        tableWidget_2->setHorizontalHeaderItem(1, __qtablewidgetitem35);
        QTableWidgetItem *__qtablewidgetitem36 = new QTableWidgetItem();
        tableWidget_2->setHorizontalHeaderItem(2, __qtablewidgetitem36);
        QTableWidgetItem *__qtablewidgetitem37 = new QTableWidgetItem();
        tableWidget_2->setHorizontalHeaderItem(3, __qtablewidgetitem37);
        if (tableWidget_2->rowCount() < 9)
            tableWidget_2->setRowCount(9);
        QTableWidgetItem *__qtablewidgetitem38 = new QTableWidgetItem();
        tableWidget_2->setVerticalHeaderItem(0, __qtablewidgetitem38);
        QTableWidgetItem *__qtablewidgetitem39 = new QTableWidgetItem();
        tableWidget_2->setVerticalHeaderItem(1, __qtablewidgetitem39);
        QTableWidgetItem *__qtablewidgetitem40 = new QTableWidgetItem();
        tableWidget_2->setVerticalHeaderItem(2, __qtablewidgetitem40);
        QTableWidgetItem *__qtablewidgetitem41 = new QTableWidgetItem();
        tableWidget_2->setVerticalHeaderItem(3, __qtablewidgetitem41);
        QTableWidgetItem *__qtablewidgetitem42 = new QTableWidgetItem();
        tableWidget_2->setVerticalHeaderItem(4, __qtablewidgetitem42);
        QTableWidgetItem *__qtablewidgetitem43 = new QTableWidgetItem();
        tableWidget_2->setVerticalHeaderItem(5, __qtablewidgetitem43);
        QTableWidgetItem *__qtablewidgetitem44 = new QTableWidgetItem();
        tableWidget_2->setVerticalHeaderItem(6, __qtablewidgetitem44);
        QTableWidgetItem *__qtablewidgetitem45 = new QTableWidgetItem();
        tableWidget_2->setVerticalHeaderItem(7, __qtablewidgetitem45);
        QTableWidgetItem *__qtablewidgetitem46 = new QTableWidgetItem();
        tableWidget_2->setVerticalHeaderItem(8, __qtablewidgetitem46);
        QTableWidgetItem *__qtablewidgetitem47 = new QTableWidgetItem();
        tableWidget_2->setItem(0, 0, __qtablewidgetitem47);
        QTableWidgetItem *__qtablewidgetitem48 = new QTableWidgetItem();
        tableWidget_2->setItem(0, 1, __qtablewidgetitem48);
        QTableWidgetItem *__qtablewidgetitem49 = new QTableWidgetItem();
        tableWidget_2->setItem(0, 2, __qtablewidgetitem49);
        QTableWidgetItem *__qtablewidgetitem50 = new QTableWidgetItem();
        tableWidget_2->setItem(0, 3, __qtablewidgetitem50);
        QTableWidgetItem *__qtablewidgetitem51 = new QTableWidgetItem();
        tableWidget_2->setItem(1, 0, __qtablewidgetitem51);
        QTableWidgetItem *__qtablewidgetitem52 = new QTableWidgetItem();
        tableWidget_2->setItem(1, 1, __qtablewidgetitem52);
        QTableWidgetItem *__qtablewidgetitem53 = new QTableWidgetItem();
        tableWidget_2->setItem(1, 2, __qtablewidgetitem53);
        QTableWidgetItem *__qtablewidgetitem54 = new QTableWidgetItem();
        tableWidget_2->setItem(1, 3, __qtablewidgetitem54);
        tableWidget_2->setObjectName(QString::fromUtf8("tableWidget_2"));
        tableWidget_2->setGeometry(QRect(0, 112, 433, 290));
        pushButton_4 = new QPushButton(tab_3);
        pushButton_4->setObjectName(QString::fromUtf8("pushButton_4"));
        pushButton_4->setGeometry(QRect(542, 80, 80, 26));
        lineEdit_2 = new QLineEdit(tab_3);
        lineEdit_2->setObjectName(QString::fromUtf8("lineEdit_2"));
        lineEdit_2->setGeometry(QRect(58, 81, 435, 22));
        label_12 = new QLabel(tab_3);
        label_12->setObjectName(QString::fromUtf8("label_12"));
        label_12->setGeometry(QRect(4, 83, 57, 16));
        label_12->setFont(font);
        label_12->setTextFormat(Qt::PlainText);
        pushButton_3 = new QPushButton(tab_3);
        pushButton_3->setObjectName(QString::fromUtf8("pushButton_3"));
        pushButton_3->setGeometry(QRect(632, 80, 79, 26));
        toolButton_2 = new QToolButton(tab_3);
        toolButton_2->setObjectName(QString::fromUtf8("toolButton_2"));
        toolButton_2->setGeometry(QRect(502, 80, 30, 25));
        groupBox_2 = new QGroupBox(tab_3);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        groupBox_2->setGeometry(QRect(440, 107, 273, 295));
        pushButton_5 = new QPushButton(groupBox_2);
        pushButton_5->setObjectName(QString::fromUtf8("pushButton_5"));
        pushButton_5->setGeometry(QRect(7, 262, 260, 26));
        label_13 = new QLabel(groupBox_2);
        label_13->setObjectName(QString::fromUtf8("label_13"));
        label_13->setGeometry(QRect(14, 28, 114, 16));
        label_14 = new QLabel(groupBox_2);
        label_14->setObjectName(QString::fromUtf8("label_14"));
        label_14->setGeometry(QRect(96, 26, 159, 20));
        label_14->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        label_16 = new QLabel(groupBox_2);
        label_16->setObjectName(QString::fromUtf8("label_16"));
        label_16->setGeometry(QRect(96, 46, 159, 20));
        label_16->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        label_15 = new QLabel(groupBox_2);
        label_15->setObjectName(QString::fromUtf8("label_15"));
        label_15->setGeometry(QRect(14, 48, 114, 16));
        label_17 = new QLabel(groupBox_2);
        label_17->setObjectName(QString::fromUtf8("label_17"));
        label_17->setGeometry(QRect(14, 69, 114, 16));
        label_18 = new QLabel(groupBox_2);
        label_18->setObjectName(QString::fromUtf8("label_18"));
        label_18->setGeometry(QRect(96, 67, 159, 20));
        label_18->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        line = new QFrame(groupBox_2);
        line->setObjectName(QString::fromUtf8("line"));
        line->setGeometry(QRect(12, 80, 253, 16));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);
        label_29 = new QLabel(groupBox_2);
        label_29->setObjectName(QString::fromUtf8("label_29"));
        label_29->setGeometry(QRect(13, 99, 81, 16));
        label_30 = new QLabel(groupBox_2);
        label_30->setObjectName(QString::fromUtf8("label_30"));
        label_30->setGeometry(QRect(98, 98, 159, 20));
        label_30->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        label_31 = new QLabel(groupBox_2);
        label_31->setObjectName(QString::fromUtf8("label_31"));
        label_31->setGeometry(QRect(99, 117, 159, 20));
        label_31->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        label_32 = new QLabel(groupBox_2);
        label_32->setObjectName(QString::fromUtf8("label_32"));
        label_32->setGeometry(QRect(14, 118, 104, 16));
        groupBox_3 = new QGroupBox(tab_3);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        groupBox_3->setGeometry(QRect(2, 5, 701, 64));
        label_19 = new QLabel(groupBox_3);
        label_19->setObjectName(QString::fromUtf8("label_19"));
        label_19->setGeometry(QRect(13, 18, 91, 16));
        label_20 = new QLabel(groupBox_3);
        label_20->setObjectName(QString::fromUtf8("label_20"));
        label_20->setGeometry(QRect(100, 16, 168, 20));
        label_20->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_21 = new QLabel(groupBox_3);
        label_21->setObjectName(QString::fromUtf8("label_21"));
        label_21->setGeometry(QRect(302, 18, 20, 20));
        label_22 = new QLabel(groupBox_3);
        label_22->setObjectName(QString::fromUtf8("label_22"));
        label_22->setGeometry(QRect(316, 20, 106, 16));
        label_22->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_23 = new QLabel(groupBox_3);
        label_23->setObjectName(QString::fromUtf8("label_23"));
        label_23->setGeometry(QRect(445, 18, 34, 20));
        label_24 = new QLabel(groupBox_3);
        label_24->setObjectName(QString::fromUtf8("label_24"));
        label_24->setGeometry(QRect(480, 20, 106, 16));
        label_24->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_25 = new QLabel(groupBox_3);
        label_25->setObjectName(QString::fromUtf8("label_25"));
        label_25->setGeometry(QRect(14, 42, 123, 16));
        label_26 = new QLabel(groupBox_3);
        label_26->setObjectName(QString::fromUtf8("label_26"));
        label_26->setGeometry(QRect(143, 43, 57, 16));
        label_27 = new QLabel(groupBox_3);
        label_27->setObjectName(QString::fromUtf8("label_27"));
        label_27->setGeometry(QRect(232, 42, 135, 16));
        label_28 = new QLabel(groupBox_3);
        label_28->setObjectName(QString::fromUtf8("label_28"));
        label_28->setGeometry(QRect(373, 42, 57, 16));
        hhh->addTab(tab_3, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QString::fromUtf8("tab_2"));
        hhh->addTab(tab_2, QString());
        tab_4 = new QWidget();
        tab_4->setObjectName(QString::fromUtf8("tab_4"));
        treeWidget = new QTreeWidget(tab_4);
        QTreeWidgetItem *__qtreewidgetitem = new QTreeWidgetItem(treeWidget);
        new QTreeWidgetItem(__qtreewidgetitem);
        new QTreeWidgetItem(__qtreewidgetitem);
        QTreeWidgetItem *__qtreewidgetitem1 = new QTreeWidgetItem(treeWidget);
        QTreeWidgetItem *__qtreewidgetitem2 = new QTreeWidgetItem(__qtreewidgetitem1);
        new QTreeWidgetItem(__qtreewidgetitem2);
        new QTreeWidgetItem(__qtreewidgetitem2);
        treeWidget->setObjectName(QString::fromUtf8("treeWidget"));
        treeWidget->setGeometry(QRect(3, 5, 215, 337));
        tabWidget = new QTabWidget(tab_4);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabWidget->setGeometry(QRect(227, 6, 480, 380));
        tab_5 = new QWidget();
        tab_5->setObjectName(QString::fromUtf8("tab_5"));
        toolButton_3 = new QToolButton(tab_5);
        toolButton_3->setObjectName(QString::fromUtf8("toolButton_3"));
        toolButton_3->setGeometry(QRect(308, 324, 162, 22));
        checkBox = new QCheckBox(tab_5);
        checkBox->setObjectName(QString::fromUtf8("checkBox"));
        checkBox->setGeometry(QRect(15, 321, 83, 20));
        groupBox_4 = new QGroupBox(tab_5);
        groupBox_4->setObjectName(QString::fromUtf8("groupBox_4"));
        groupBox_4->setGeometry(QRect(16, 13, 437, 135));
        label_33 = new QLabel(groupBox_4);
        label_33->setObjectName(QString::fromUtf8("label_33"));
        label_33->setGeometry(QRect(21, 23, 98, 16));
        label_34 = new QLabel(groupBox_4);
        label_34->setObjectName(QString::fromUtf8("label_34"));
        label_34->setGeometry(QRect(129, 23, 114, 16));
        label_35 = new QLabel(groupBox_4);
        label_35->setObjectName(QString::fromUtf8("label_35"));
        label_35->setGeometry(QRect(23, 57, 137, 16));
        label_36 = new QLabel(groupBox_4);
        label_36->setObjectName(QString::fromUtf8("label_36"));
        label_36->setGeometry(QRect(170, 56, 52, 15));
        label_37 = new QLabel(groupBox_4);
        label_37->setObjectName(QString::fromUtf8("label_37"));
        label_37->setGeometry(QRect(24, 90, 129, 16));
        label_38 = new QLabel(groupBox_4);
        label_38->setObjectName(QString::fromUtf8("label_38"));
        label_38->setGeometry(QRect(139, 90, 52, 15));
        groupBox_5 = new QGroupBox(tab_5);
        groupBox_5->setObjectName(QString::fromUtf8("groupBox_5"));
        groupBox_5->setGeometry(QRect(17, 174, 435, 133));
        label_39 = new QLabel(groupBox_5);
        label_39->setObjectName(QString::fromUtf8("label_39"));
        label_39->setGeometry(QRect(17, 24, 82, 16));
        label_40 = new QLabel(groupBox_5);
        label_40->setObjectName(QString::fromUtf8("label_40"));
        label_40->setGeometry(QRect(97, 25, 86, 16));
        label_41 = new QLabel(groupBox_5);
        label_41->setObjectName(QString::fromUtf8("label_41"));
        label_41->setGeometry(QRect(17, 57, 52, 15));
        label_42 = new QLabel(groupBox_5);
        label_42->setObjectName(QString::fromUtf8("label_42"));
        label_42->setGeometry(QRect(98, 53, 52, 15));
        tabWidget->addTab(tab_5, QString());
        tab_6 = new QWidget();
        tab_6->setObjectName(QString::fromUtf8("tab_6"));
        textEdit = new QTextEdit(tab_6);
        textEdit->setObjectName(QString::fromUtf8("textEdit"));
        textEdit->setGeometry(QRect(5, 6, 464, 337));
        textEdit->setReadOnly(true);
        tabWidget->addTab(tab_6, QString());
        tab_7 = new QWidget();
        tab_7->setObjectName(QString::fromUtf8("tab_7"));
        textEdit_2 = new QTextEdit(tab_7);
        textEdit_2->setObjectName(QString::fromUtf8("textEdit_2"));
        textEdit_2->setGeometry(QRect(8, 10, 460, 328));
        textEdit_2->setReadOnly(true);
        tabWidget->addTab(tab_7, QString());
        commandLinkButton = new QCommandLinkButton(tab_4);
        commandLinkButton->setObjectName(QString::fromUtf8("commandLinkButton"));
        commandLinkButton->setGeometry(QRect(25, 348, 63, 41));
        commandLinkButton_2 = new QCommandLinkButton(tab_4);
        commandLinkButton_2->setObjectName(QString::fromUtf8("commandLinkButton_2"));
        commandLinkButton_2->setGeometry(QRect(97, 349, 101, 41));
        hhh->addTab(tab_4, QString());
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 727, 22));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QString::fromUtf8("menuFile"));
        menuEdit = new QMenu(menuBar);
        menuEdit->setObjectName(QString::fromUtf8("menuEdit"));
        menuProcessors = new QMenu(menuBar);
        menuProcessors->setObjectName(QString::fromUtf8("menuProcessors"));
        menuSomething_Cool = new QMenu(menuProcessors);
        menuSomething_Cool->setObjectName(QString::fromUtf8("menuSomething_Cool"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menuFile->menuAction());
        menuBar->addAction(menuEdit->menuAction());
        menuBar->addAction(menuProcessors->menuAction());
        menuProcessors->addAction(menuSomething_Cool->menuAction());
        menuProcessors->addSeparator();
        menuSomething_Cool->addSeparator();

        retranslateUi(MainWindow);

        hhh->setCurrentIndex(3);
        tabWidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("MainWindow", "Date", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("MainWindow", "Time", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QApplication::translate("MainWindow", "Server IP", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidget->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QApplication::translate("MainWindow", "Port", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidget->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QApplication::translate("MainWindow", "Name", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem5 = tableWidget->horizontalHeaderItem(5);
        ___qtablewidgetitem5->setText(QApplication::translate("MainWindow", "Number of Clients", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem6 = tableWidget->verticalHeaderItem(0);
        ___qtablewidgetitem6->setText(QApplication::translate("MainWindow", "01", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem7 = tableWidget->verticalHeaderItem(1);
        ___qtablewidgetitem7->setText(QApplication::translate("MainWindow", "02", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem8 = tableWidget->verticalHeaderItem(2);
        ___qtablewidgetitem8->setText(QApplication::translate("MainWindow", "03", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem9 = tableWidget->verticalHeaderItem(3);
        ___qtablewidgetitem9->setText(QApplication::translate("MainWindow", "04", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem10 = tableWidget->verticalHeaderItem(4);
        ___qtablewidgetitem10->setText(QApplication::translate("MainWindow", "05", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem11 = tableWidget->verticalHeaderItem(5);
        ___qtablewidgetitem11->setText(QApplication::translate("MainWindow", "06", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem12 = tableWidget->verticalHeaderItem(6);
        ___qtablewidgetitem12->setText(QApplication::translate("MainWindow", "07", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem13 = tableWidget->verticalHeaderItem(7);
        ___qtablewidgetitem13->setText(QApplication::translate("MainWindow", "08", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem14 = tableWidget->verticalHeaderItem(8);
        ___qtablewidgetitem14->setText(QApplication::translate("MainWindow", "09", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem15 = tableWidget->verticalHeaderItem(9);
        ___qtablewidgetitem15->setText(QApplication::translate("MainWindow", "10", 0, QApplication::UnicodeUTF8));

        const bool __sortingEnabled = tableWidget->isSortingEnabled();
        tableWidget->setSortingEnabled(false);
        QTableWidgetItem *___qtablewidgetitem16 = tableWidget->item(0, 0);
        ___qtablewidgetitem16->setText(QApplication::translate("MainWindow", "1-1-10", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem17 = tableWidget->item(0, 1);
        ___qtablewidgetitem17->setText(QApplication::translate("MainWindow", "12:00PM", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem18 = tableWidget->item(0, 2);
        ___qtablewidgetitem18->setText(QApplication::translate("MainWindow", "192.168.1.2", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem19 = tableWidget->item(0, 3);
        ___qtablewidgetitem19->setText(QApplication::translate("MainWindow", "80", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem20 = tableWidget->item(0, 4);
        ___qtablewidgetitem20->setText(QApplication::translate("MainWindow", "Weather", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem21 = tableWidget->item(0, 5);
        ___qtablewidgetitem21->setText(QApplication::translate("MainWindow", "10", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem22 = tableWidget->item(1, 0);
        ___qtablewidgetitem22->setText(QApplication::translate("MainWindow", "1-1-10", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem23 = tableWidget->item(1, 1);
        ___qtablewidgetitem23->setText(QApplication::translate("MainWindow", "12:12PM", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem24 = tableWidget->item(1, 2);
        ___qtablewidgetitem24->setText(QApplication::translate("MainWindow", "example.net", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem25 = tableWidget->item(1, 3);
        ___qtablewidgetitem25->setText(QApplication::translate("MainWindow", "8080", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem26 = tableWidget->item(1, 4);
        ___qtablewidgetitem26->setText(QApplication::translate("MainWindow", "Email", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem27 = tableWidget->item(1, 5);
        ___qtablewidgetitem27->setText(QApplication::translate("MainWindow", "2", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem28 = tableWidget->item(2, 0);
        ___qtablewidgetitem28->setText(QApplication::translate("MainWindow", "1-1-10", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem29 = tableWidget->item(2, 1);
        ___qtablewidgetitem29->setText(QApplication::translate("MainWindow", "11:10a", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem30 = tableWidget->item(2, 2);
        ___qtablewidgetitem30->setText(QApplication::translate("MainWindow", "cam.drexel.edu", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem31 = tableWidget->item(2, 3);
        ___qtablewidgetitem31->setText(QApplication::translate("MainWindow", "700", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem32 = tableWidget->item(2, 4);
        ___qtablewidgetitem32->setText(QApplication::translate("MainWindow", "Quad Camera", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem33 = tableWidget->item(2, 5);
        ___qtablewidgetitem33->setText(QApplication::translate("MainWindow", "2", 0, QApplication::UnicodeUTF8));
        tableWidget->setSortingEnabled(__sortingEnabled);

        pushButton->setText(QApplication::translate("MainWindow", "Apply Filter", 0, QApplication::UnicodeUTF8));
        pushButton_2->setText(QApplication::translate("MainWindow", "Clear", 0, QApplication::UnicodeUTF8));
        toolButton->setText(QApplication::translate("MainWindow", "...", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("MainWindow", " Details ", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("MainWindow", "Server Name:", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("MainWindow", "example.net", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("MainWindow", "IP:", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("MainWindow", "192.168.1.4", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("MainWindow", "Port:", 0, QApplication::UnicodeUTF8));
        label_6->setText(QApplication::translate("MainWindow", "8080", 0, QApplication::UnicodeUTF8));
        label_7->setText(QApplication::translate("MainWindow", "Number of Clients:", 0, QApplication::UnicodeUTF8));
        label_8->setText(QApplication::translate("MainWindow", "2", 0, QApplication::UnicodeUTF8));
        label_9->setText(QApplication::translate("MainWindow", "Packets Associated:", 0, QApplication::UnicodeUTF8));
        label_10->setText(QApplication::translate("MainWindow", "2000", 0, QApplication::UnicodeUTF8));
        label_11->setText(QApplication::translate("MainWindow", "Filter", 0, QApplication::UnicodeUTF8));
        hhh->setTabText(hhh->indexOf(tab), QApplication::translate("MainWindow", "Main", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem34 = tableWidget_2->horizontalHeaderItem(0);
        ___qtablewidgetitem34->setText(QApplication::translate("MainWindow", "Date", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem35 = tableWidget_2->horizontalHeaderItem(1);
        ___qtablewidgetitem35->setText(QApplication::translate("MainWindow", "Time", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem36 = tableWidget_2->horizontalHeaderItem(2);
        ___qtablewidgetitem36->setText(QApplication::translate("MainWindow", "Client Name", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem37 = tableWidget_2->horizontalHeaderItem(3);
        ___qtablewidgetitem37->setText(QApplication::translate("MainWindow", "Client IP", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem38 = tableWidget_2->verticalHeaderItem(0);
        ___qtablewidgetitem38->setText(QApplication::translate("MainWindow", "1", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem39 = tableWidget_2->verticalHeaderItem(1);
        ___qtablewidgetitem39->setText(QApplication::translate("MainWindow", "2", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem40 = tableWidget_2->verticalHeaderItem(2);
        ___qtablewidgetitem40->setText(QApplication::translate("MainWindow", "3", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem41 = tableWidget_2->verticalHeaderItem(3);
        ___qtablewidgetitem41->setText(QApplication::translate("MainWindow", "4", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem42 = tableWidget_2->verticalHeaderItem(4);
        ___qtablewidgetitem42->setText(QApplication::translate("MainWindow", "5", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem43 = tableWidget_2->verticalHeaderItem(5);
        ___qtablewidgetitem43->setText(QApplication::translate("MainWindow", "6", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem44 = tableWidget_2->verticalHeaderItem(6);
        ___qtablewidgetitem44->setText(QApplication::translate("MainWindow", "7", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem45 = tableWidget_2->verticalHeaderItem(7);
        ___qtablewidgetitem45->setText(QApplication::translate("MainWindow", "8", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem46 = tableWidget_2->verticalHeaderItem(8);
        ___qtablewidgetitem46->setText(QApplication::translate("MainWindow", "10", 0, QApplication::UnicodeUTF8));

        const bool __sortingEnabled1 = tableWidget_2->isSortingEnabled();
        tableWidget_2->setSortingEnabled(false);
        QTableWidgetItem *___qtablewidgetitem47 = tableWidget_2->item(0, 0);
        ___qtablewidgetitem47->setText(QApplication::translate("MainWindow", "1-1-10", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem48 = tableWidget_2->item(0, 1);
        ___qtablewidgetitem48->setText(QApplication::translate("MainWindow", "12:00pm", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem49 = tableWidget_2->item(0, 2);
        ___qtablewidgetitem49->setText(QApplication::translate("MainWindow", "tom", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem50 = tableWidget_2->item(0, 3);
        ___qtablewidgetitem50->setText(QApplication::translate("MainWindow", "192.168.1.11", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem51 = tableWidget_2->item(1, 0);
        ___qtablewidgetitem51->setText(QApplication::translate("MainWindow", "1-1-10", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem52 = tableWidget_2->item(1, 1);
        ___qtablewidgetitem52->setText(QApplication::translate("MainWindow", "12:00pm", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem53 = tableWidget_2->item(1, 2);
        ___qtablewidgetitem53->setText(QApplication::translate("MainWindow", "phil", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem54 = tableWidget_2->item(1, 3);
        ___qtablewidgetitem54->setText(QApplication::translate("MainWindow", "192.168.12", 0, QApplication::UnicodeUTF8));
        tableWidget_2->setSortingEnabled(__sortingEnabled1);

        pushButton_4->setText(QApplication::translate("MainWindow", "Apply Filter", 0, QApplication::UnicodeUTF8));
        label_12->setText(QApplication::translate("MainWindow", "Filter", 0, QApplication::UnicodeUTF8));
        pushButton_3->setText(QApplication::translate("MainWindow", "Clear", 0, QApplication::UnicodeUTF8));
        toolButton_2->setText(QApplication::translate("MainWindow", "...", 0, QApplication::UnicodeUTF8));
        groupBox_2->setTitle(QApplication::translate("MainWindow", " Details ", 0, QApplication::UnicodeUTF8));
        pushButton_5->setText(QApplication::translate("MainWindow", "See Communcition Chain...", 0, QApplication::UnicodeUTF8));
        label_13->setText(QApplication::translate("MainWindow", "Client Name:", 0, QApplication::UnicodeUTF8));
        label_14->setText(QApplication::translate("MainWindow", "tom", 0, QApplication::UnicodeUTF8));
        label_16->setText(QApplication::translate("MainWindow", "192.168,1,11", 0, QApplication::UnicodeUTF8));
        label_15->setText(QApplication::translate("MainWindow", "IP Address:", 0, QApplication::UnicodeUTF8));
        label_17->setText(QApplication::translate("MainWindow", "Source Port:", 0, QApplication::UnicodeUTF8));
        label_18->setText(QApplication::translate("MainWindow", "59829", 0, QApplication::UnicodeUTF8));
        label_29->setText(QApplication::translate("MainWindow", "Client Sent:", 0, QApplication::UnicodeUTF8));
        label_30->setText(QApplication::translate("MainWindow", "500", 0, QApplication::UnicodeUTF8));
        label_31->setText(QApplication::translate("MainWindow", "500", 0, QApplication::UnicodeUTF8));
        label_32->setText(QApplication::translate("MainWindow", "Client Recieved:", 0, QApplication::UnicodeUTF8));
        groupBox_3->setTitle(QApplication::translate("MainWindow", " Details - example.net ", 0, QApplication::UnicodeUTF8));
        label_19->setText(QApplication::translate("MainWindow", "Server Name:", 0, QApplication::UnicodeUTF8));
        label_20->setText(QApplication::translate("MainWindow", "example.net", 0, QApplication::UnicodeUTF8));
        label_21->setText(QApplication::translate("MainWindow", "IP:", 0, QApplication::UnicodeUTF8));
        label_22->setText(QApplication::translate("MainWindow", "192.168.1.4", 0, QApplication::UnicodeUTF8));
        label_23->setText(QApplication::translate("MainWindow", "Port:", 0, QApplication::UnicodeUTF8));
        label_24->setText(QApplication::translate("MainWindow", "8080", 0, QApplication::UnicodeUTF8));
        label_25->setText(QApplication::translate("MainWindow", "Number of Clients:", 0, QApplication::UnicodeUTF8));
        label_26->setText(QApplication::translate("MainWindow", "2", 0, QApplication::UnicodeUTF8));
        label_27->setText(QApplication::translate("MainWindow", "Packets Associated:", 0, QApplication::UnicodeUTF8));
        label_28->setText(QApplication::translate("MainWindow", "2000", 0, QApplication::UnicodeUTF8));
        hhh->setTabText(hhh->indexOf(tab_3), QApplication::translate("MainWindow", "example.net:8080 - Email (2)", 0, QApplication::UnicodeUTF8));
        hhh->setTabText(hhh->indexOf(tab_2), QApplication::translate("MainWindow", "example.net:80 - Weather (10)", 0, QApplication::UnicodeUTF8));
        QTreeWidgetItem *___qtreewidgetitem = treeWidget->headerItem();
        ___qtreewidgetitem->setText(0, QApplication::translate("MainWindow", "Registry Entiries", 0, QApplication::UnicodeUTF8));

        const bool __sortingEnabled2 = treeWidget->isSortingEnabled();
        treeWidget->setSortingEnabled(false);
        QTreeWidgetItem *___qtreewidgetitem1 = treeWidget->topLevelItem(0);
        ___qtreewidgetitem1->setText(0, QApplication::translate("MainWindow", "example.net", 0, QApplication::UnicodeUTF8));
        QTreeWidgetItem *___qtreewidgetitem2 = ___qtreewidgetitem1->child(0);
        ___qtreewidgetitem2->setText(0, QApplication::translate("MainWindow", "email", 0, QApplication::UnicodeUTF8));
        QTreeWidgetItem *___qtreewidgetitem3 = ___qtreewidgetitem1->child(1);
        ___qtreewidgetitem3->setText(0, QApplication::translate("MainWindow", "weather", 0, QApplication::UnicodeUTF8));
        QTreeWidgetItem *___qtreewidgetitem4 = treeWidget->topLevelItem(1);
        ___qtreewidgetitem4->setText(0, QApplication::translate("MainWindow", "getquote.com", 0, QApplication::UnicodeUTF8));
        QTreeWidgetItem *___qtreewidgetitem5 = ___qtreewidgetitem4->child(0);
        ___qtreewidgetitem5->setText(0, QApplication::translate("MainWindow", "SingleSymbolStockQuoteService", 0, QApplication::UnicodeUTF8));
        QTreeWidgetItem *___qtreewidgetitem6 = ___qtreewidgetitem5->child(0);
        ___qtreewidgetitem6->setText(0, QApplication::translate("MainWindow", "Input", 0, QApplication::UnicodeUTF8));
        QTreeWidgetItem *___qtreewidgetitem7 = ___qtreewidgetitem5->child(1);
        ___qtreewidgetitem7->setText(0, QApplication::translate("MainWindow", "Output", 0, QApplication::UnicodeUTF8));
        treeWidget->setSortingEnabled(__sortingEnabled2);

        toolButton_3->setText(QApplication::translate("MainWindow", "Invoke Service", 0, QApplication::UnicodeUTF8));
        checkBox->setText(QApplication::translate("MainWindow", "Disabled", 0, QApplication::UnicodeUTF8));
        groupBox_4->setTitle(QApplication::translate("MainWindow", "Client Information", 0, QApplication::UnicodeUTF8));
        label_33->setText(QApplication::translate("MainWindow", "Last to connect:", 0, QApplication::UnicodeUTF8));
        label_34->setText(QApplication::translate("MainWindow", "192.168.1.19", 0, QApplication::UnicodeUTF8));
        label_35->setText(QApplication::translate("MainWindow", "Total Clients Detected:", 0, QApplication::UnicodeUTF8));
        label_36->setText(QApplication::translate("MainWindow", "2", 0, QApplication::UnicodeUTF8));
        label_37->setText(QApplication::translate("MainWindow", "Total Invokcations:", 0, QApplication::UnicodeUTF8));
        label_38->setText(QApplication::translate("MainWindow", "50", 0, QApplication::UnicodeUTF8));
        groupBox_5->setTitle(QApplication::translate("MainWindow", "Server Information", 0, QApplication::UnicodeUTF8));
        label_39->setText(QApplication::translate("MainWindow", "IP address:", 0, QApplication::UnicodeUTF8));
        label_40->setText(QApplication::translate("MainWindow", "192,168,1,11", 0, QApplication::UnicodeUTF8));
        label_41->setText(QApplication::translate("MainWindow", "Port:", 0, QApplication::UnicodeUTF8));
        label_42->setText(QApplication::translate("MainWindow", "8080", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tab_5), QApplication::translate("MainWindow", "General Information", 0, QApplication::UnicodeUTF8));
        textEdit->setHtml(QApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Sans'; font-size:8pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:12px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Courier New,courier';\">&lt;?xml version=\"1.0\"?&gt;</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Courier New,courier';\">&lt;tModel tModelKey=\"\"&gt;</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Courier New,courier';\">  &lt;name&gt;</span><span style=\" font-family:'Courier New,courier'; font-weight:6"
                        "00;\">http://www.getquote.com/StockQuoteService-interface</span><span style=\" font-family:'Courier New,courier';\">&lt;/name&gt;</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Courier New,courier';\"> </span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Courier New,courier';\">  &lt;description xml:lang=\"en\"&gt;</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Courier New,courier';\">    </span><span style=\" font-family:'Courier New,courier'; font-weight:600;\">Standard service interface definition for a stock quote service.</span><span style=\" font-family:'Courier New,courier';\"> </span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-"
                        "right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Courier New,courier';\">  &lt;/description&gt;</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Courier New,courier';\"> </span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Courier New,courier';\">  &lt;overviewDoc&gt;</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Courier New,courier';\">    &lt;description xml:lang=\"en\"&gt;</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Courier New,courier';\">      WSDL Service Interface Document</span></p>\n"
"<p style=\" margin-top:0px; mar"
                        "gin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Courier New,courier';\">    &lt;/description&gt;</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Courier New,courier';\">    &lt;overviewURL&gt;</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Courier New,courier';\">      </span><span style=\" font-family:'Courier New,courier'; font-weight:600;\">http://www.getquote.com/services/</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Courier New,courier'; font-weight:600;\">SQS-interface.wsdl#SingleSymbolBinding</span><span style=\" font-family:'Courier New,courier';\"> </span></p>\n"
"<p style=\" margin-top:"
                        "0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Courier New,courier';\">    &lt;/overviewURL&gt;</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Courier New,courier';\">  &lt;/overviewDoc&gt;</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Courier New,courier';\"> </span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Courier New,courier';\">  &lt;categoryBag&gt;</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Courier New,courier';\">    &lt;keyedReference tModelKey=\"UUID:C1ACF26D-96"
                        "72-4404-9D70-39B756E62AB4\"</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Courier New,courier';\">                    keyName=\"</span><span style=\" font-family:'Courier New,courier'; font-weight:600;\">uddi-org:types</span><span style=\" font-family:'Courier New,courier';\">\" keyValue=\"</span><span style=\" font-family:'Courier New,courier'; font-weight:600;\">wsdlSpec</span><span style=\" font-family:'Courier New,courier';\">\"/&gt;</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Courier New,courier';\">    &lt;keyedReference tModelKey=\"UUID:DB77450D-9FA8-45D4-A7BC-04411D14E384\" </span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Courier New,courier';\">         "
                        "           keyName=\"Stock market trading services\" </span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Courier New,courier';\">                    keyValue=\"84121801\"/&gt;</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Courier New,courier';\">  &lt;/categoryBag&gt;</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Courier New,courier';\">&lt;/tModel&gt;</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Courier New,courier';\">&lt;!--source: http://www.ibm.com/developerworks/library/ws-wsdl/ --&gt;</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tab_6), QApplication::translate("MainWindow", "Soure", 0, QApplication::UnicodeUTF8));
        textEdit_2->setHtml(QApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Sans'; font-size:8pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Courier New,courier';\">&lt;?xml version=\"1.0\"?&gt;</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Courier New,courier';\">&lt;definitions name=\"StockQuoteService-interface\"</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Courier New,courier';\">  targetNamespace=\"</span><span style=\" font-family:'Courier"
                        " New,courier'; font-weight:600;\">http://www.getquote.com/StockQuoteService-interface</span><span style=\" font-family:'Courier New,courier';\">\"</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Courier New,courier';\">  xmlns:tns=\"http://www.getquote.com/StockQuoteService-interface\"</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Courier New,courier';\">  xmlns:xsd=\" http://www.w3.org/2001/XMLSchema \"</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Courier New,courier';\">  xmlns:soap=\"http://schemas.xmlsoap.org/wsdl/soap/\"</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><spa"
                        "n style=\" font-family:'Courier New,courier';\">  xmlns=\"http://schemas.xmlsoap.org/wsdl/\"&gt;</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Courier New,courier';\"> </span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Courier New,courier';\">  &lt;documentation&gt;</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Courier New,courier';\">    </span><span style=\" font-family:'Courier New,courier'; font-weight:600;\">Standard WSDL service interface definition for a stock quote service.</span><span style=\" font-family:'Courier New,courier';\"> </span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent"
                        ":0px;\"><span style=\" font-family:'Courier New,courier';\">  &lt;/documentation&gt;</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Courier New,courier';\"> </span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Courier New,courier';\">  &lt;message name=\"SingleSymbolRequest\"&gt;</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Courier New,courier';\">    &lt;part name=\"symbol\" type=\"xsd:string\"/&gt;</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Courier New,courier';\">  &lt;/message&gt;</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; marg"
                        "in-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Courier New,courier';\"> </span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Courier New,courier';\">  &lt;message name=\"SingleSymbolQuoteResponse\"&gt;</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Courier New,courier';\">    &lt;part name=\"quote\" type=\"xsd:string\"/&gt;</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Courier New,courier';\">  &lt;/message&gt;</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Courier New,courier';\"> </span></p>\n"
"<p styl"
                        "e=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Courier New,courier';\">  &lt;portType name=\"SingleSymbolStockQuoteService\"&gt;</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Courier New,courier';\">    &lt;operation name=\"getQuote\"&gt;</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Courier New,courier';\">      &lt;input message=\"tns:SingleSymbolRequest\"/&gt;</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Courier New,courier';\">      &lt;output message=\"tns:SingleSymbolQuoteResponse\"/&gt;</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0p"
                        "x; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Courier New,courier';\">    &lt;/operation&gt;</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Courier New,courier';\">  &lt;/portType&gt;</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Courier New,courier';\"> </span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Courier New,courier';\">  &lt;binding name=\"</span><span style=\" font-family:'Courier New,courier'; font-weight:600;\">SingleSymbolBinding</span><span style=\" font-family:'Courier New,courier';\">\"</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-inde"
                        "nt:0px;\"><span style=\" font-family:'Courier New,courier';\">           type=\"tns:SingleSymbolStockQuoteService\"&gt;</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Courier New,courier';\">    &lt;soap:binding style=\"rpc\"</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Courier New,courier';\">                  transport=\"http://schemas.xmlsoap.org/soap/http\"/&gt;</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Courier New,courier';\">    &lt;operation name=\"getQuote\"&gt;</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Courier New,courier';\">    "
                        "  &lt;soap:operation soapAction=\"http://www.getquote.com/GetQuote\"/&gt;</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Courier New,courier';\">      &lt;input&gt;</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Courier New,courier';\">        &lt;soap:body use=\"encoded\"</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Courier New,courier';\">            namespace=\"urn:single-symbol-stock-quotes\"</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Courier New,courier';\">            encodingStyle=\"http://schemas.xmlsoap.org/soap/encoding/\"/&gt;</span><"
                        "/p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Courier New,courier';\">      &lt;/input&gt;</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Courier New,courier';\">      &lt;output&gt;</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Courier New,courier';\">        &lt;soap:body use=\"encoded\"</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Courier New,courier';\">            namespace=\"urn:single-symbol-stock-quotes\"</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span s"
                        "tyle=\" font-family:'Courier New,courier';\">            encodingStyle=\"http://schemas.xmlsoap.org/soap/encoding/\"/&gt;</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Courier New,courier';\">      &lt;/output&gt;</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Courier New,courier';\">    &lt;/operation&gt;</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Courier New,courier';\">  &lt;/binding&gt;  </span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Courier New,courier';\">&lt;/definitions&gt;</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tab_7), QApplication::translate("MainWindow", "WSDL Soure", 0, QApplication::UnicodeUTF8));
        commandLinkButton->setText(QApplication::translate("MainWindow", "Add", 0, QApplication::UnicodeUTF8));
        commandLinkButton_2->setText(QApplication::translate("MainWindow", "Remove", 0, QApplication::UnicodeUTF8));
        hhh->setTabText(hhh->indexOf(tab_4), QApplication::translate("MainWindow", "UDDI", 0, QApplication::UnicodeUTF8));
        menuFile->setTitle(QApplication::translate("MainWindow", "File", 0, QApplication::UnicodeUTF8));
        menuEdit->setTitle(QApplication::translate("MainWindow", "Edit", 0, QApplication::UnicodeUTF8));
        menuProcessors->setTitle(QApplication::translate("MainWindow", "Processors", 0, QApplication::UnicodeUTF8));
        menuSomething_Cool->setTitle(QApplication::translate("MainWindow", "Something Cool", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
