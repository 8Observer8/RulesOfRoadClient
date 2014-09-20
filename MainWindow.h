#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include "Connection.h"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_actionConnection_triggered();
    void slotConnect( const QString &hostName,
                      const int portNumber );
    void slotShowError( const QString &errorText );
    void slotReceivedData( const QString &text );

    void on_sendButton_clicked();

private:
    Ui::MainWindow *ui;
    QLabel *statusLabel;
    Connection *m_connection;
};

#endif // MAINWINDOW_H
