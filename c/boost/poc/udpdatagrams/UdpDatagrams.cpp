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

#include <UdpDatagrams.h>

namespace gos {
namespace ex {
namespace udpdpoc {

typedef std::vector<std::string> BroadcastRegistry;

typedef boost::asio::io_context AsioContext;
typedef boost::asio::ip::udp::socket UdpSocket;
typedef boost::asio::ip::udp::resolver UdpResolver;
typedef boost::asio::ip::udp::endpoint UdpEndpoint;
typedef boost::asio::ip::address IpAddress;
typedef UdpResolver::iterator UdpResolverIterator;
typedef UdpResolver::query UdpResolverQuery;

typedef std::unique_ptr<AsioContext> AsioContextPointer;
typedef std::unique_ptr<UdpResolver> UdpResolverPointer;
typedef std::unique_ptr<UdpEndpoint> UdpEndpointPointer;
typedef std::unique_ptr<UdpSocket> UdpSocketPointer;

static BroadcastRegistry broadcastregistry;

static AsioContextPointer asiocontext;
static UdpResolverPointer resolver;
static IpAddress bindaddress;
static UdpEndpointPointer bindendpoint;
static UdpSocketPointer bindsocket;

static std::wstring dataid2wstr(DataId id);

CommunicationResult initialize() {
  boost::system::error_code error;

  asiocontext = std::make_unique<AsioContext>();

  bindaddress = IpAddress::from_string(binding_address, error);
  if (error) {
    return CommunicationResult::FailBindAddress;
  }
  bindendpoint = std::make_unique<UdpEndpoint>(
    bindaddress, binding_port, error);
  if (error) {
    return CommunicationResult::FailBindEndpoint;
  }

  return CommunicationResult::Ok;
}

CommunicationResult createbindsocket() {
  boost::system::error_code error;
  bindsocket = std::make_unique<UdpSocket>(*asiocontext, *bindendpoint, error);
  if (error) {
    return CommunicationResult::FailBindSocket;
  }
  return CommunicationResult::Ok;
}

}
}
}
