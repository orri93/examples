#ifndef USESOCKET_H
#define USESOCKET_H

#include <iostream>

#include <QObject>
#include <QUdpSocket>
#include <QHostAddress>

#include "tick.h"

#define TAG_SIZE 2

class UseSocket : public QObject
{
  Q_OBJECT
public:

  enum class Method {
    Event,
    Poll
  };

  enum class Counting {
    Forward,
    Backward
  };

  explicit UseSocket(QObject *parent = 0);

  void SetMethod(const Method& method) {
    this->method_ = method;
  }

  void SetCount(const Counting& counting) {
    this->counting_ = counting;
  }

  void SetBinding(const QHostAddress& address, const quint16 port) {
    this->bindaddress_ = address;
    this->bindport_ = port;
    std::cout << "Binding set to "
              << this->bindaddress_.toString().toStdString() << " through "
              << this->bindport_ << std::endl;
  }

  void SetBroadcast(const QHostAddress& address, const quint16 port) {
    this->broadcastaddress_ = address;
    this->broadcastport_ = port;
    std::cout << "Broadcast set to "
              << this->broadcastaddress_.toString().toStdString() << " through "
              << this->broadcastport_ << std::endl;
  }

  void SetShare(bool share) {
    this->share_socket_ = share;
  }

  void SetFire(bool fire) {
    this->fire_event_ = fire;
  }

  void quit();

signals:
  void finished();

public slots:
  void execute();
  void ready();

private:
  typedef union {unsigned char bytes[TAG_SIZE]; quint16 value;} I16Tag;

  Tick tick_;
  Method method_;
  Counting counting_;
  QHostAddress bindaddress_;
  QHostAddress broadcastaddress_;
  QHostAddress remoteaddress_;
  quint16 bindport_;
  quint16 broadcastport_;
  quint16 remoteport_;
  QUdpSocket* bindsocket_;
  QUdpSocket* broadcastsocket_;
  QMetaObject::Connection connection_;
  I16Tag i16tagin_;
  I16Tag i16tagout_;
  bool share_socket_;
  bool fire_event_;

  void oncount(const int& count);
  int send(const int& value);
  int read();
};

#endif // USESOCKET_H
