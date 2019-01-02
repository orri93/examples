#include <windows.h>

#include <memory>
#include <iostream>
#include <exception>

#include <QException>
#include <QCoreApplication>
#include <QTimer>

#include "usesocket.h"

#define ARGC_SIZE 7

#define ARGC_INDEX_METHOD 1
#define ARGC_INDEX_COUNT 2
#define ARGC_INDEX_BIND_ADDRESS 3
#define ARGC_INDEX_BIND_PORT 4
#define ARGC_INDEX_BROADCAST_ADDRESS 5
#define ARGC_INDEC_BROADCAST_PORT 6

#define ARGV_METHOD_EVENT "event"
#define ARGV_METHOD_POLL "poll"

#define ARGV_COUNT_FORWARD "forward"
#define ARGV_COUNT_BACKWARD "backward"

#define EXECUTE_DELAY 100

int usage();
QHostAddress atohost(const char* text);

int main(int argc, char *argv[])
{
  int result = EXIT_FAILURE;
  try
  {
    QCoreApplication a(argc, argv);
    UseSocket* usesocket = new UseSocket(&a);
    if(usesocket) {
      QHostAddress bindaddress, broadcastaddress;
      quint16 bindport,broadcastport;

      if(argc == ARGC_SIZE) {
        // Method
        if(strncmp(
             ARGV_METHOD_EVENT,
             argv[ARGC_INDEX_METHOD],
             sizeof(ARGV_METHOD_EVENT)) == 0) {
          usesocket->SetMethod(UseSocket::Method::Event);
        } else if(strncmp(
                    ARGV_METHOD_POLL,
                    argv[ARGC_INDEX_METHOD],
                    sizeof(ARGV_METHOD_POLL)) == 0) {
          usesocket->SetMethod(UseSocket::Method::Poll);
        } else {
          return usage();
        }

        // Counting
        if(strncmp(
             ARGV_COUNT_FORWARD,
             argv[ARGC_INDEX_COUNT],
             sizeof(ARGV_COUNT_FORWARD)) == 0) {
          usesocket->SetCount(UseSocket::Counting::Forward);
        } else if(strncmp(
                    ARGV_COUNT_BACKWARD,
                    argv[ARGC_INDEX_COUNT],
                    sizeof(ARGV_COUNT_BACKWARD)) == 0) {
          usesocket->SetCount(UseSocket::Counting::Backward);
        } else {
          return usage();
        }

        // Binding
        bindaddress = atohost(argv[ARGC_INDEX_BIND_ADDRESS]);
        bindport = atoi(argv[ARGC_INDEX_BIND_PORT]);
        usesocket->SetBinding(bindaddress, bindport);

        // Broadcasting
        broadcastaddress = atohost(argv[ARGC_INDEX_BROADCAST_ADDRESS]);
        broadcastport = atoi(argv[ARGC_INDEC_BROADCAST_PORT]);
        usesocket->SetBroadcast(broadcastaddress, broadcastport);

        QMetaObject::Connection connection = QObject::connect(
              usesocket,
              SIGNAL(finished()),
              &a,
              SLOT(quit()));
        if(connection) {
          QTimer::singleShot(EXECUTE_DELAY, usesocket, SLOT(execute()));
          result = a.exec();
        } else {
          std::cerr << "Failed to connect to the "
                       "Use Socket object's finish signal" << std::endl;
        }
      } else {
        return usage();
      }
    } else {
      std::cerr
          << "Out of memory when attempting to create Use Socket object"
          << std::endl;
    }
  }
  catch(QException& ex) {
    std::cerr << "Qt Excpetion: " << ex.what() << std::endl;
  }
  catch(std::exception& ex) {
    std::cerr << "Excpetion: " << ex.what() << std::endl;
  }
  catch(...) {
    std::cerr << "Excpetion!" << std::endl;
  }

  return result;
}

int usage() {
  std::cout << "Usage qt-udp-socket.exe "
               "method count "
               "bind-address bind-port "
               "broadcast-address broadcast-port" << std::endl;
  return 0;
}

QHostAddress atohost(const char* text) {
  return QHostAddress(QString(text));
}
