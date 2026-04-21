#include "widget.h"
#include "./ui_widget.h"
#include <QSystemTrayIcon>
#include <QMenu>

#include <QAction>
#include <QCheckBox>
#include <QComboBox>
#include <QCoreApplication>
#include <QCloseEvent>
#include <QGroupBox>
#include <QLabel>
#include <QLineEdit>
#include <QMenu>
#include <QPushButton>
#include <QSpinBox>
#include <QTextEdit>
#include <QVBoxLayout>
#include <QMessageBox>

const int kTrayIconOn = 1;
const int kTrayIconOff = 0;

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    createIconGroupBox();
    createTrayIcon();

    // setIcon(kTrayIconOff);
    setIcon(kTrayIconOn);
    trayIcon->show();
}

void Widget::setIcon(int index)
{
    QIcon icon = iconComboBox->itemIcon(index);
    trayIcon->setIcon(icon);
    setWindowIcon(icon);

    trayIcon->setToolTip(iconComboBox->itemText(index));
}

void Widget::createIconGroupBox()
{
    iconGroupBox = new QGroupBox(tr("Tray Icon"));

    iconComboBox = new QComboBox;
    iconComboBox->addItem(QIcon(":/images/zzz-off.svg"), tr("Off"));
    iconComboBox->addItem(QIcon(":/images/zzz.svg"), tr("On"));

    QHBoxLayout *iconLayout = new QHBoxLayout;
    iconLayout->addWidget(iconComboBox);
    iconLayout->addStretch();
    iconGroupBox->setLayout(iconLayout);
}

void Widget::createTrayIcon()
{
    trayIcon = new QSystemTrayIcon(this);
}

Widget::~Widget()
{
    delete ui;
}
