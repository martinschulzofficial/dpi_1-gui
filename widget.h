#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QSystemTrayIcon>
#include <QPlainTextEdit>
#include <QPushButton>

#include "zapret/zaprethandler.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class Widget;
}
class QAction;
class QCheckBox;
class QComboBox;
class QGroupBox;
class QLabel;
class QLineEdit;
class QMenu;
class QPushButton;
class QSpinBox;
class QTextEdit;
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = nullptr);
    ~Widget() override;


private slots:
    void setIcon();
    void updateStatus();

    void on_toggleButton_clicked();

    void on_updateDomainsButton_clicked();

protected:
    void closeEvent(QCloseEvent *event) override;

private:
    Ui::Widget *ui;
    void createIconGroupBox();
    void createTrayIcon();
    void setToggleButtonText();

    void showWindow();
    void createActions();

    void onTrayIconActivated(QSystemTrayIcon::ActivationReason reason);
    void onForceKill();

    QSystemTrayIcon *trayIcon;
    QComboBox *iconComboBox;
    QGroupBox *iconGroupBox;
    QPlainTextEdit *domainsTextEdit;
    QPlainTextEdit *ipsTextEdit;
    QPushButton *toggleButton;
    QMenu *trayIconMenu;

    QAction *quitAction;
    QAction *showWindowAction;
    QAction *forceKillAction;

    ZapretHandler *zapretHandler;
};
#endif // WIDGET_H
