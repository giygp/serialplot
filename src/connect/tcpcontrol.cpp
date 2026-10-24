#include "connect/tcpcontrol.h"
#include "ui_tcpcontrol.h"

TcpControl::TcpControl(QTcpSocket* socket, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::TcpControl)
{
    ui->setupUi(this);
    ui->leHost->setText("192.168.1.102");
    // QSpinBox 默认范围是 0-99，必须放宽才能输入真实端口号
    ui->sbPort->setRange(1, 65535);
    ui->sbPort->setValue(23);

    tcpSocket = socket;
    connect(ui->pbConnect, &QPushButton::clicked,
                     this, &TcpControl::open);
    connect(tcpSocket, &QAbstractSocket::connected, this, [this]()
    {
        ui->pbConnect->setText("Disconnect");
        qDebug() << "TCP connected!";
        emit portToggled(true);
    });
    connect(tcpSocket, &QAbstractSocket::disconnected, this, [this]()
    {
        ui->pbConnect->setText("Connect");
        qDebug() << "TCP disconnected!";
        emit portToggled(false);
    });
    // 连接失败时（拒绝/超时/不可达）给出反馈，否则界面上看不出任何现象
    connect(tcpSocket, &QAbstractSocket::errorOccurred, this, [this](QAbstractSocket::SocketError error)
    {
        qDebug() << "TCP error:" << error << tcpSocket->errorString();
        ui->pbConnect->setText("Connect");
    });
}

TcpControl::~TcpControl()
{
    delete ui;
}

void TcpControl::open()
{
    if (tcpSocket->state() == QAbstractSocket::ConnectedState)
    {
        tcpSocket->disconnectFromHost(); //挂断
    }

    else if (tcpSocket->state() == QAbstractSocket::UnconnectedState)
    {
        QString hostName = ui->leHost->text().trimmed();
        if (hostName.isEmpty()) return;
        quint16 prot = (quint16) ui->sbPort->value();
        tcpSocket->connectToHost(hostName, prot);
    }
}
