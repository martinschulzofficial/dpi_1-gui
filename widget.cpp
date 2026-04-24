#include "widget.h"
#include "./ui_widget.h"

#include <QSystemTrayIcon>
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

#include <iostream>

#include "zapret/zaprethandler.h"

const int kTrayIconOn = 1;
const int kTrayIconOff = 0;

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    zapretHandler = new ZapretHandler();

    createIconGroupBox();
    createActions();
    createTrayIcon();

    trayIcon->show();


    domainsTextEdit = findChild<QPlainTextEdit*>("domainsTextEdit");
    domainsTextEdit->setPlainText(QString::fromStdString(zapretHandler->getDomains()));

    ipsTextEdit = findChild<QPlainTextEdit*>("ipsTextEdit");
    ipsTextEdit->setPlainText(QString::fromStdString(zapretHandler->getIps()));

    toggleButton = findChild<QPushButton*>("toggleButton");

    connect(zapretHandler, &ZapretHandler::statusChanged, this, &Widget::updateStatus);
    connect(trayIcon, &QSystemTrayIcon::activated, this, &Widget::iconActivated);
    updateStatus();


}

void Widget::iconActivated(QSystemTrayIcon::ActivationReason reason)
{
    switch (reason) {
    case QSystemTrayIcon::Trigger:
        this->show();
        break;
    default:
        ;
    }
}

void Widget::closeEvent(QCloseEvent *event) {
    event->ignore();
    this->hide();
}

void Widget::updateStatus() {
    setIcon();
    setToggleButtonText();
}

void Widget::setIcon()
{
    const int index = zapretHandler->isActive() ? kTrayIconOn : kTrayIconOff;
    QIcon icon = iconComboBox->itemIcon(index);
    trayIcon->setIcon(icon);
    setWindowIcon(icon);

    std::cout << "Icon index" << index << std::endl;
    trayIcon->setToolTip(iconComboBox->itemText(index));
}

void Widget::setToggleButtonText() {
    const auto text = zapretHandler->isActive() ? "Stop" : "Start";
    toggleButton->setText(QString::fromStdString(text));
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

void Widget::createActions()
{
    quitAction = new QAction("Quit", this);
    connect(quitAction, &QAction::triggered, qApp, &QCoreApplication::quit);
}

void Widget::createTrayIcon()
{

    trayIconMenu = new QMenu(this);
    trayIconMenu->addAction(quitAction);

    trayIcon = new QSystemTrayIcon(this);
    trayIcon->setContextMenu(trayIconMenu);
}

Widget::~Widget()
{
    delete ui;
}


void Widget::on_toggleButton_clicked()
{
    zapretHandler->toggle();
}

