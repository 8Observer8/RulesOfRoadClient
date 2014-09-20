#include "Connection.h"

Connection::Connection() :
    m_nextBlockSize( 0 )
{
    m_socket = new QTcpSocket( this );
    connect( m_socket, SIGNAL( readyRead() ),
             this, SLOT( slotReadyRead() ) );
    connect( m_socket, SIGNAL( error( QAbstractSocket::SocketError ) ),
            this, SLOT( slotSendError( QAbstractSocket::SocketError ) ) );
}

void Connection::open( const QString &hostName, const int portNumber )
{
    m_socket->connectToHost( hostName, portNumber );
}

bool Connection::isOpen() const
{
    return m_socket->isOpen();
}

void Connection::send( const QString &data )
{
    QByteArray arrBlock;
    QDataStream out( &arrBlock, QIODevice::WriteOnly );
    out.setVersion( QDataStream::Qt_5_0 );

    out << quint16( 0 ) << data;

    out.device()->seek( 0 );
    out << quint16( arrBlock.size() - sizeof( quint16 ) );

    m_socket->write( arrBlock );
}

void Connection::slotReadyRead()
{
    QTcpSocket* clientSocket = ( QTcpSocket* )sender();
    QDataStream in( clientSocket );
    in.setVersion( QDataStream::Qt_5_0 );

    for ( ;; ) {
        if (!m_nextBlockSize ) {
            if ( clientSocket->bytesAvailable() < ( int )sizeof( quint16 ) ) {
                break;
            }
            in >> m_nextBlockSize;
        }

        if ( clientSocket->bytesAvailable() < m_nextBlockSize ) {
            break;
        }

        QString inputData;
        in >> inputData;
        emit signalReceivedData( inputData );

        m_nextBlockSize = 0;
    }
}

void Connection::slotSendError( const QAbstractSocket::SocketError &socketError )
{
    QString message;
    switch ( socketError ) {
    case QAbstractSocket::RemoteHostClosedError:
        break;
    case QAbstractSocket::HostNotFoundError:
        message = tr( "The host was not found. Please check the "
                      "host name and port settings.");
        emit signalError( message );
        break;
    case QAbstractSocket::ConnectionRefusedError:
        message = tr( "The connection was refused by the peer. "
                      "Make sure the server is running, "
                      "settings are correct.");
        emit signalError( message );
        break;
    default:
        message = tr( "The following error occurred: %1." )
                .arg( m_socket->errorString() );
        emit signalError( message );
    }
}
