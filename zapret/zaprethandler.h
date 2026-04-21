#include <QObject>

#ifndef ZAPRETHANDLER_H
#define ZAPRETHANDLER_H

class ZapretHandler : public QObject
{
    Q_OBJECT

public:
    ZapretHandler();

    bool isActive();

    void start();

    void stop();

signals:
    void statusChanged(bool newValue);

private:
    bool status;
    void checkStatus();
};

#endif // ZAPRETHANDLER_H
