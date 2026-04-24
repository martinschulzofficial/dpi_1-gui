#include "widget.h"
#include "./ui_widget.h"

#include <ApplicationServices/ApplicationServices.h>
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

    ProcessSerialNumber psn = { 0, kCurrentProcess };
    TransformProcessType(&psn, kProcessTransformToUIElementApplication);
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
    connect(trayIcon, &QSystemTrayIcon::activated, this, &Widget::onTrayIconActivated);
    updateStatus();
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

void Widget::onForceKill() {
    zapretHandler->forceKill();
}

void Widget::createActions()
{
    forceKillAction = new QAction(tr("Force Kill"), this);
    connect(forceKillAction, &QAction::triggered, this, &Widget::onForceKill);

    showWindowAction = new QAction(tr("Show window"), this);
    connect(showWindowAction, &QAction::triggered, this, &Widget::showWindow);

    quitAction = new QAction(tr("Quit"), this);
    connect(quitAction, &QAction::triggered, qApp, &QCoreApplication::quit);
}

void Widget::showWindow() {
    this->show();
}

void Widget::onTrayIconActivated(QSystemTrayIcon::ActivationReason reason) {
    if (reason == QSystemTrayIcon::Context) {
        // Position the menu at the current cursor location and show it
        trayIconMenu->popup(QCursor::pos());
    } else if (reason == QSystemTrayIcon::Trigger) {
        zapretHandler->toggle();
    }
}

void Widget::createTrayIcon()
{
    trayIconMenu = new QMenu(this);
    trayIconMenu->addAction(showWindowAction);
    // trayIconMenu->addAction(forceKillAction);
    trayIconMenu->addAction(quitAction);
    trayIcon = new QSystemTrayIcon(this);
    // trayIcon->setContextMenu(trayIconMenu);
}

Widget::~Widget()
{
    delete ui;
}


void Widget::on_toggleButton_clicked()
{
    zapretHandler->toggle();
}

