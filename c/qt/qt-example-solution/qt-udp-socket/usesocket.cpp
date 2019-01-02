#include "usesocket.h"

#include <memory>
#include <exception>
#include <iostream>

#include <QCoreApplication>

#define COUNTING_START 0
#define COUNTING_END 100

#define INTERVAL 1000

UseSocket::UseSocket(QObject *parent) :
  tick_(INTERVAL),
  method_(UseSocket::Method::Event),
  counting_(UseSocket::Counting::Forward),
  bindport_(0),
  broadcastport_(0),
  remoteport_(0),
  bindsocket_(nullptr),
  broadcastsocket_(nullptr),
  QObject(parent)
{
  this->bindsocket_ = new QUdpSocket(this);
  this->broadcastsocket_ = new QUdpSocket(this);
}

void UseSocket::execute()
{
  Tick::Ticking current = 0;
  bool bindresult =
      this->bindsocket_->bind(this->bindaddress_, this->bindport_);
  if(bindresult) {
    std::cout << "Successfully binding to "
              << this->bindaddress_.toString().toStdString() << " through port "
              << this->bindport_ << std::endl;
    if(this->method_ == UseSocket::Method::Event) {
      std::cout << "Event method specified so connecting" << std::endl;
      this->connection_ = this->bindsocket_->connect(
            this->bindsocket_,
            &QUdpSocket::readyRead,
            this,
            &UseSocket::ready);
      if(!(bool)this->connection_) {
        throw std::exception("Failed to connect");
      }
    }
    if(this->counting_ == UseSocket::Counting::Forward) {
      std::cout << "Start counting forward" << std::endl;
      for(int i = COUNTING_START; i < COUNTING_END; i++) {
        while(!this->tick_.is(current)) {
          QCoreApplication::processEvents();
          current = this->tick_.millis();
        }
        oncount(i);
      }
    } else {
      std::cout << "Start counting backwards" << std::endl;
      for(int i = COUNTING_END - 1; i >= COUNTING_START; i--) {
        while(!this->tick_.is(current)) {
          QCoreApplication::processEvents();
          current = this->tick_.millis();
        }
        oncount(i);
      }
    }

  } else {
    std::cerr << "Failed to binding to "
              << this->bindaddress_.toString().toStdString() << " through port "
              << this->bindport_ << std::endl;
  }

  std::cout << "Finished!" << std::endl;
  emit finished();
}

void UseSocket::quit() {
  if(this->bindsocket_ != nullptr) {
    if(this->connection_) {
      bool result = this->bindsocket_->disconnect(this->connection_);
      if(result) {
        std::cout << "Successfully disconnection from the ready the event"
                  << std::endl;
      } else {
        std::cerr << "Failed to disconnect from the ready event" << std::endl;
      }
    }
  }
}

void UseSocket::ready() {
  int value = read();
  if(value >= 0) {
    std::cout << "Sucessfully getting " << value
              << " through a ready event from "
              << this->remoteaddress_.toString().toStdString()
              << " through port " << this->remoteport_ << std::endl;
  } else {
    std::cerr << "Failed to  get value through a ready event" << std::endl;
  }
}

void UseSocket::oncount(const int& count) {
  int value, length;
  length = send(count);
  if(length == TAG_SIZE) {
    std::cout << "Successfully sent " << length
              << " bytes of value " << count << " to "
              << this->broadcastaddress_.toString().toStdString()
              << " through port " << this->broadcastport_;
  } else {
    std::cerr << "Send failure for " << count
              << " bytes count is " << length
              << " but expected to be " << TAG_SIZE;
  }
  if(this->method_ == UseSocket::Method::Poll) {
    value = read();
    if(value >= 0) {
      std::cout << " reciving " << value
                << " from " << this->remoteaddress_.toString().toStdString()
                << " via port " << this->remoteport_;
    }
  }
  std::cout << std::endl;
}


int UseSocket::send(const int &value) {
  this->i16tagout_.value = (quint16)value;
  const qint64 length = TAG_SIZE;
  qint64 written = this->broadcastsocket_->writeDatagram(
        (const char*)this->i16tagout_.bytes,
        length,
        this->broadcastaddress_,
        this->broadcastport_);
  return (int)written;

  if(this->method_ == UseSocket::Method::Poll) {
    int reading = read();
    if(reading >= 0) {
      std::cout << "Getting " << reading << " through a polling" << std::endl;
    }
  }
}

int UseSocket::read() {
  qint64 size = this->bindsocket_->pendingDatagramSize();
  if(size > 0) {
    std::unique_ptr<char[]> buffer = std::make_unique<char[]>(size);
    qint64 read = this->bindsocket_->readDatagram(
          buffer.get(),
          size,
          &(this->remoteaddress_),
          &(this->remoteport_));
    if(read == TAG_SIZE) {
      memcpy(this->i16tagin_.bytes, buffer.get(), TAG_SIZE);
      return (int)this->i16tagin_.value;
    }
  }
  return -1;
}
