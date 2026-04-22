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
class QComboBox;
class QGroupBox;
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

protected:
    void closeEvent(QCloseEvent *event) override;

private:
    Ui::Widget *ui;
    void createIconGroupBox();
    void createTrayIcon();
    void setToggleButtonText();

    void iconActivated(QSystemTrayIcon::ActivationReason reason);

    QSystemTrayIcon *trayIcon;
    QComboBox *iconComboBox;
    QGroupBox *iconGroupBox;
    QPlainTextEdit *domainsTextEdit;
    QPlainTextEdit *ipsTextEdit;
    QPushButton *toggleButton;

    ZapretHandler *zapretHandler;
};
#endif // WIDGET_H
