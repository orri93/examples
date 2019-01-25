#include <boost/asio.hpp>

#ifdef WIN32
#include <SDKDDKVer.h>
// Exclude rarely-used stuff from Windows headers
#define WIN32_LEAN_AND_MEAN
// Windows Header Files:
#include <windows.h>
#endif

#include <memory>
#include <vector>
#include <sstream>
#include <string>

#include <Text.h>
#include <UdpDatagrams.h>
#include <DataStructures.h>
#include <CommunicationOptions.h>

namespace gos {
namespace ex {
namespace udpdpoc {

typedef std::vector<std::string> BroadcastRegistry;

typedef std::unique_ptr<char[]> CharacterArrayPointer;

typedef boost::asio::streambuf AsioStreamBuffer;
typedef boost::asio::const_buffer AsioConstantBuffer;
typedef boost::asio::io_context AsioContext;
typedef boost::asio::ip::udp::socket UdpSocket;
typedef boost::asio::ip::udp::resolver UdpResolver;
typedef boost::asio::ip::udp::endpoint UdpEndpoint;
typedef boost::asio::ip::address IpAddress;
typedef UdpSocket::endpoint_type UdpSocketEndpoint;
typedef UdpResolver::iterator UdpResolverIterator;
typedef UdpResolver::query UdpResolverQuery;

typedef std::unique_ptr<AsioContext> AsioContextPointer;
typedef std::unique_ptr<UdpResolver> UdpResolverPointer;
typedef std::unique_ptr<UdpEndpoint> UdpEndpointPointer;
typedef std::unique_ptr<UdpSocket> UdpSocketPointer;

static const CommunicationResult successfullcommresult[] = {
  CommunicationResult::Ok,
  CommunicationResult::NoMoreBuffered,
  CommunicationResult::BufferConsumed
};

static BroadcastRegistry broadcastregistry;

static AsioContextPointer asiocontext;
static UdpResolverPointer resolver;
static IpAddress bindaddress;
static UdpEndpointPointer bindendpoint;
static UdpSocketPointer bindsocket;

static struct ipconfiguration bindinformation;

static CharacterArrayPointer incomingbuffer;

static size_t expectedincomingsize = 0;

static std::wstring dataid2wstr(DataId id);

CommunicationResult initialize() {
  boost::system::error_code error;

  asiocontext = std::make_unique<AsioContext>();
  if (!asiocontext) {
    return CommunicationResult::MemoryContext;
  }

  getbindinginfo(bindinformation);

  bindaddress = IpAddress::from_string(bindinformation.address, error);
  if (error) {
    return CommunicationResult::FailBindAddress;
  }
  bindendpoint = std::make_unique<UdpEndpoint>(
    bindaddress,
    bindinformation.port);
  if (!bindendpoint) {
    return CommunicationResult::MemoryBindEndpoint;
  }

  DataId incomingdataid = getincomingdataid();
  expectedincomingsize = sizeofdata(incomingdataid);
  if (expectedincomingsize <= 0) {
    return CommunicationResult::IncomingDataSize;
  }

  return CommunicationResult::Ok;
}

CommunicationResult isready() {
  if (!bindendpoint) {
    return CommunicationResult::BindEndpointUndefined;
  }
  return CommunicationResult::Ok;
}

CommunicationResult createbindsocket() {
  boost::system::error_code error;
  bindsocket = std::make_unique<UdpSocket>(*asiocontext, *bindendpoint);
  if (error) {
    return CommunicationResult::FailBindSocket;
  }
  return CommunicationResult::Ok;
}

CommunicationResult consume(std::string& address, int& port) {
  size_t buffersize = expectedincomingsize * 1.5;
  boost::system::error_code error;
  CharacterArrayPointer temporarybuffer =
    std::make_unique<char[]>(buffersize);
  UdpSocketEndpoint endpoint;
  auto buffer = boost::asio::buffer(temporarybuffer.get(), buffersize);
  size_t size = bindsocket->receive_from(buffer, endpoint, 0, error);
  if (error) {
    return CommunicationResult::FailConsuming;
  }
  if (size == expectedincomingsize) {
    incomingbuffer = std::make_unique<char[]>(expectedincomingsize);
    memcpy(incomingbuffer.get(), temporarybuffer.get(), expectedincomingsize);
    IpAddress sendersaddress = endpoint.address();
    address = sendersaddress.to_string();
    port = endpoint.port();
    return CommunicationResult::BufferConsumed;
  } else if (size == 0) {
    return CommunicationResult::NoMoreBuffered;
  } else {
    return CommunicationResult::IncomingIncorrectSize;
  }
}

bool iscommunicationresulterror(const CommunicationResult& result) {
  auto constend = std::end(successfullcommresult);
  return std::find(
    std::begin(successfullcommresult),
    constend,
    result) == constend;
}

std::string communicationresult2str(const CommunicationResult& result) {
  std::stringstream strstrm;
  switch (result) {
  case CommunicationResult::Ok:
    return "communication ok";
  case CommunicationResult::IncomingIncorrectSize:
    return "incorrect incoming size";
  case CommunicationResult::BindEndpointUndefined:
    return "bind endpoint is undefined!";
  case CommunicationResult::MemoryBindEndpoint:
    return "out of memory for bind endpoint creation";
  case CommunicationResult::MemoryContext:
    return "out of memory for context creation";
  case CommunicationResult::FailConsuming:
    return "consuming incoming data failed";
  case CommunicationResult::FailBindAddress:
    strstrm << "failed to parse the bind address '"
      << bindinformation.address << "'";
    return strstrm.str();
  case CommunicationResult::FailBindSocket:
    return "failed to create UDP socket for binding";
  case CommunicationResult::IncomingDataSize:
    strstrm << "The data size " << expectedincomingsize
      << "for incoming data structure is invalid";
    return strstrm.str();
  default:
    return "Not yet implemented communication result text!!!";
  }
}

std::wstring communicationresult2wstr(const CommunicationResult& result) {
  return text2wtext(communicationresult2str(result));
}

}
}
}
