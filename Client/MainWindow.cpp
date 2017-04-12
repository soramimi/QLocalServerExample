#include "MainWindow.h"
#include "ui_MainWindow.h"
#include <QLocalSocket>

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
#if 1
		sock->write("Hell", 4);
		sock->waitForBytesWritten();
		sock->write("o, w", 4);
		sock->waitForBytesWritten();
		sock->write("orld", 4);
		sock->waitForBytesWritten();
		sock->write("!\n", 2);
		sock->waitForBytesWritten();
#else
		sock->write("Hello, world!\n", 14);
		sock->waitForBytesWritten();
#endif
		sock->disconnectFromServer();
		delete sock;
	});
	sock->connectToServer("myserver");
}
