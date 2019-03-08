#ifndef KNXTUNNEL_H
#define KNXTUNNEL_H

#include <QTimer>
#include <QObject>

#include <QHostAddress>
#include <QKnxNetIpTunnel>

class KnxTunnel : public QObject
{
    Q_OBJECT
public:
    explicit KnxTunnel(const QHostAddress &remoteAddress, QObject *parent = nullptr);

    QHostAddress remoteAddress() const;
    void setRemoteAddress(const QHostAddress &remoteAddress);

    bool connected() const;

    void connectTunnel();
    void disconnectTunnel();

    void switchLight(const QKnxAddress &knxAddress, bool power);

private:
    QHostAddress m_remoteAddress;
    QKnxNetIpTunnel *m_tunnel = nullptr;
    QTimer *m_timer = nullptr;

    QList<QKnxAddress> m_knxDeviceAddresses;
    QList<QKnxAddress> m_knxGroupAddresses;

    void collectAddress(const QKnxAddress &address);
    void printFrame(const QKnxLinkLayerFrame &frame);

signals:
    void connectedChanged();

private slots:
    void onTimeout();

    void onTunnelConnected();
    void onTunnelDisconnected();
    void onTunnelStateChanged(QKnxNetIpEndpointConnection::State state);
    void onTunnelFrameReceived(const QKnxLinkLayerFrame &frame);
};

#endif // KNXTUNNEL_H
