#ifndef TCPCONTROL_H
#define TCPCONTROL_H

#include <QWidget>
#include <QTcpSocket>
#include <QAbstractSocket>
#include <QtDebug>

namespace Ui {
class TcpControl;
}

class TcpControl : public QWidget
{
    Q_OBJECT

public:
    explicit TcpControl(QTcpSocket* socket, QWidget *parent = nullptr);
    ~TcpControl();

    QTcpSocket* tcpSocket;

signals:
    void portToggled(bool open);   

private:
    Ui::TcpControl *ui;
    void open();
};

#endif // TCPCONTROL_H
