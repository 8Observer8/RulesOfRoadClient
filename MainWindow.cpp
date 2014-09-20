
#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "ConnectionDialog.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setFixedSize( this->size() );

    m_connection = new Connection;

    // Status Label
    statusLabel = new QLabel;
    statusLabel->setText( tr( "Отсоединён" ) );
    ui->statusBar->addPermanentWidget( statusLabel, 1 );
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionConnection_triggered()
{
    ConnectionDialog dialog;
    dialog.setModal( true );
    connect( &dialog, SIGNAL( signalConnect( QString, int ) ),
             this, SLOT( slotConnect( QString, int ) ) );
    dialog.exec();
}

void MainWindow::slotConnect( const QString &hostName,
                              const int portNumber )
{
    m_connection->open( hostName, portNumber );
    connect( m_connection, SIGNAL( signalReceivedData( QString ) ),
             this, SLOT( slotReceivedData( QString ) ) );
    connect( m_connection, SIGNAL( signalError( QString ) ),
             this, SLOT( slotShowError( QString ) ) );
    m_connection->send( "Ok" );
}

void MainWindow::slotReceivedData( const QString &text )
{
    if ( text == QString( "Ok" ) ) {
        statusLabel->setText( tr( "Присоединён" ) );
    }
}

void MainWindow::slotShowError( const QString &errorText )
{
    statusLabel->setText( errorText );
}

void MainWindow::on_sendButton_clicked()
{
    if ( !m_connection->isOpen() ) {
        on_actionConnection_triggered();
        return;
    }

    QString firstName = ui->firstNameLineEdit->text();
    QString lastName = ui->lastNameLineEdit->text();
    QString group = ui->groupLineEdit->text();

    QString message;
    message = QString( "%1,%2,%3" ).arg( firstName ).arg( lastName ).arg( group );
    m_connection->send( message );
}
