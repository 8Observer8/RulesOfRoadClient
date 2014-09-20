
#include <QHostInfo>
#include "ConnectionDialog.h"
#include "ui_ConnectionDialog.h"

ConnectionDialog::ConnectionDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ConnectionDialog)
{
    ui->setupUi(this);

    // Init host name
    QString name = QHostInfo::localHostName();
    ui->addressLineEdit->setText( name );
}

ConnectionDialog::~ConnectionDialog()
{
    delete ui;
}

void ConnectionDialog::on_connectButton_clicked()
{
    QString hostName = ui->addressLineEdit->text();
    int portNumber = ui->portNumberSpinBox->value();
    emit signalConnect( hostName, portNumber );
    this->close();
}
