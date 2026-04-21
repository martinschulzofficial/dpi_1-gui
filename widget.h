#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QSystemTrayIcon>
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

private:
    Ui::Widget *ui;
    void createIconGroupBox();
    void createTrayIcon();

    QSystemTrayIcon *trayIcon;
    QComboBox *iconComboBox;
    QGroupBox *iconGroupBox;

    ZapretHandler *zapretHandler;
};
#endif // WIDGET_H
