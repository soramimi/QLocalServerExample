#include <QCoreApplication>
#include <QLocalServer>
#include <QLocalSocket>
#include <stdio.h>

int main(int argc, char *argv[])
{
	QCoreApplication a(argc, argv);

	QLocalServer server;
	server.listen("myserver");
	QObject::connect(&server, &QLocalServer::newConnection, [&](){
		QLocalSocket *sock = server.nextPendingConnection();
		if (sock) {
			puts("--- connected ---");
			while (1) {
				QLocalSocket::LocalSocketState s = sock->state();
				if (sock->waitForReadyRead(1)) {
					QByteArray ba = sock->readAll();
					std::string str = QString::fromLatin1(ba).toStdString();
					fwrite(str.c_str(), 1, str.size(), stdout);
				} else if (s == QLocalSocket::LocalSocketState::UnconnectedState) {
					break;
				}
			}
			putchar('\n');
			puts("--- disconnected ---");
		}
	});

	return a.exec();
}
