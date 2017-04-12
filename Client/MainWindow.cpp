#include "MainWindow.h"
#include "ui_MainWindow.h"
#include <QLocalSocket>
#include <QThread>

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	ui->setupUi(this);
}

MainWindow::~MainWindow()
{
	delete ui;
}

void MainWindow::on_pushButton_clicked()
{
	QLocalSocket *sock = new QLocalSocket;
	connect(sock, &QLocalSocket::connected, [&](){
		sock->write("Hell", 4);
		sock->waitForBytesWritten();
		sock->write("o, w", 4);
		sock->waitForBytesWritten();
		sock->write("orld", 4);
		sock->waitForBytesWritten();
		sock->disconnectFromServer();
		delete sock;
	});
	sock->connectToServer("myserver");
}
