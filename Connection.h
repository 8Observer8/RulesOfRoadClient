#ifndef CONNECTION_H
#define CONNECTION_H

#include <QObject>
#include <QByteArray>
#include <QTcpSocket>

class Connection : public QObject
{
    Q_OBJECT

public:
    Connection();
    void open( const QString &hostName,
               const int portNumber );
    bool isOpen() const;
    void send( const QString &data );

signals:
    void signalReceivedData( const QString &data );
    void signalError( const QString &errorText );

private slots:
    void slotReadyRead( );
    void slotSendError( const QAbstractSocket::SocketError &socketError );

private:
    QTcpSocket *m_socket;
    quint16 m_nextBlockSize;
};

#endif // CONNECTION_H
