#include <boost/asio.hpp>

#ifdef WIN32
#include <SDKDDKVer.h>
// Exclude rarely-used stuff from Windows headers
#define WIN32_LEAN_AND_MEAN
// Windows Header Files:
#include <windows.h>
#endif

#include <cassert>
#include <memory>
#include <vector>
#include <string>
#include <chrono>

#include <Text.h>
#include <UdpDatagrams.h>
#include <DataStructures.h>
#include <CommunicationOptions.h>

namespace basio = boost::asio;
namespace basip = boost::asio::ip;

namespace gos {
namespace ex {
namespace udpdpoc {

typedef std::unique_ptr<char[]> CharacterArrayPointer;

typedef basio::streambuf AsioStreamBuffer;
typedef basio::const_buffer AsioConstantBuffer;
typedef basio::io_context AsioContext;
typedef basip::address IpAddress;
typedef basip::udp::socket UdpSocket;
typedef basip::udp::resolver UdpResolver;
typedef basip::udp::endpoint UdpEndpoint;
typedef UdpSocket::endpoint_type UdpSocketEndpoint;
typedef UdpSocket::protocol_type UdpSocketProtocol;
typedef UdpSocket::shutdown_type UdpSocketShutdown;
typedef UdpResolver::iterator UdpResolverIterator;
typedef UdpResolver::query UdpResolverQuery;

typedef std::unique_ptr<AsioContext> AsioContextPointer;
typedef std::unique_ptr<UdpResolver> UdpResolverPointer;
typedef std::unique_ptr<UdpEndpoint> UdpEndpointPointer;
typedef std::unique_ptr<UdpSocketProtocol> UdpSocketProtocolPointer;
typedef std::unique_ptr<UdpSocket> UdpSocketPointer;

typedef std::vector<UdpEndpoint> BroadcastRegistry;
typedef BroadcastRegistry::iterator BroadcastRegistryIterator;

typedef std::chrono::steady_clock LoopClock;
typedef LoopClock::time_point LoopTimePoint;

static const CommunicationResult successfullcommresult[] = {
  CommunicationResult::Ok,
  CommunicationResult::NoMoreBuffered,
  CommunicationResult::BufferConsumed
};

static BroadcastRegistry broadcastregistry;
static IpInformation lastresolving;

static UdpEndpoint lastsendingto;

static AsioContextPointer asiocontext;
static UdpResolverPointer resolver;
static IpAddress bindaddress;
static UdpEndpointPointer bindendpoint;
#ifdef GOS_EXAMPLES_C_POC_UDP_DATAGRAMS_SHARE_SOCKET
static UdpSocketPointer sharedsocket;
#else
static UdpSocketPointer bindsocket;
static UdpSocketPointer broadcastsocket;
#endif

boost::system::error_code guderror;

static struct ipconfiguration bindinformation;

static CharacterArrayPointer incomingbuffer;

static size_t expectedincomingsize = 0;
static size_t incomingsize = 0;

static LoopTimePoint tick, nextloop, nextsocketcreation;
static int loopintervalmillis = 1000;

static bool istimeforsocketcreation();
static CommunicationResult isready();
static CommunicationResult accesssocket(UdpSocketPointer& socket, bool bind);
static CommunicationResult getbindsocket(UdpSocketPointer& socket);
static CommunicationResult getbroadcastsocket(UdpSocketPointer& socket);
static CommunicationResult releasebindsocket(UdpSocketPointer& socket);
static CommunicationResult releasebroadcastsocket(UdpSocketPointer& socket);
static CommunicationResult consume(
  UdpSocket& socket,
  std::string& address,
  int& port);
static CommunicationResult broadcast(
  UdpSocket& socket,
  const DataPointer& datapointer,
  const size_t& size);

static void recycle();
static void clearincoming();

static std::wstring dataid2wstr(DataId id);

CommunicationResult initialize() {
  nextloop = nextsocketcreation = LoopClock::now();

  asiocontext = std::make_unique<AsioContext>();
  if (!asiocontext) {
    return CommunicationResult::MemoryContext;
  }
  getbindinginfo(bindinformation);

  bindaddress = IpAddress::from_string(bindinformation.address, guderror);
  if (guderror) {
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

  resolver = std::make_unique<UdpResolver>(*asiocontext);
  if (!resolver) {
    return CommunicationResult::MemoryResolver;
  }

  /* Register the default broadcast endpoint */
  struct ipconfiguration defaultbroadcastinginformation;
  getbroadcastinfo(defaultbroadcastinginformation);
  CommunicationResult registerresult =
    registerbroadcasting(defaultbroadcastinginformation);
  if (registerresult != CommunicationResult::Ok) {
    return registerresult;
  }

  /* Create a bind socket on startup to fail early */
  UdpSocketPointer socket;
  CommunicationResult createresult = getbindsocket(socket);
  if (socket) {
    CommunicationResult releaseresult = releasebindsocket(socket);
    return createresult ==
      CommunicationResult::Ok ? releaseresult : createresult;
  } else {
    return createresult;
  }
}

CommunicationResult initialize(const int& intervalinmillis) {
  loopintervalmillis = intervalinmillis;
  return initialize();
}

CommunicationResult registerbroadcasting(const IpInformation& endpoint) {
  cloneipinformation(lastresolving, endpoint);
  std::stringstream portstream;
  portstream << endpoint.port;
  UdpResolverQuery query(endpoint.address, portstream.str());
  auto endpointer = resolver->resolve(query, guderror);
  if (guderror) {
    return CommunicationResult::FailResolve;
  }
  UdpEndpoint udpendpoint = *(endpointer);
  broadcastregistry.push_back(udpendpoint);
  return CommunicationResult::Ok;
}

CommunicationResult loop(
  std::wstringstream& wstrstr,
  const unsigned long long& incremental) {

  CommunicationResult result;
  UdpSocketPointer internalbindsocket;
  UdpSocketPointer internalbroadcastsocket;

  /* Add the clock text */
  wstrstr << clocktext();

  try {
    std::string senderaddress;
    int senderport;

    result = isready();
    if (result != CommunicationResult::Ok) {
      goto gos_ex_udpdpoc_loop_process_outputing_result_;
    }

    DataId inid = getincomingdataid();
    DataId outid = getoutgoingdataid();
    switch (outid) {
    case DataId::A:
      createdataa(incremental);
      break;
    case DataId::B:
      createdatab(incremental);
      break;
    }

    DataPointer datapointer = nullptr;
    size_t datasize = 0;
    accessdata(outid, datapointer, datasize);
    if (datapointer == nullptr || datasize == 0) {
      wstrstr << "Failed to access outgoing data";
      goto gos_ex_udpdpoc_loop_process_exit_;
    }

    int firstcount = 0, secondcount = 0;

    /* Clear the incoming buffer */
    clearincoming();

    /* Recycle the sockets if enabled */
    recycle();

    /* First consumtion */
    result = getbindsocket(internalbindsocket);
    if (result != CommunicationResult::Ok) {
      goto gos_ex_udpdpoc_loop_process_outputing_result_;
    }
    do {
      result = consume(*internalbindsocket, senderaddress, senderport);
      firstcount += result == CommunicationResult::BufferConsumed ? 1 : 0;
    } while (result == CommunicationResult::BufferConsumed);
    if (iscommunicationresulterror(result)) {
      goto gos_ex_udpdpoc_loop_process_outputing_result_;
    }
    result = releasebindsocket(internalbindsocket);
    if (result != CommunicationResult::Ok) {
      goto gos_ex_udpdpoc_loop_process_outputing_result_;
    }

    /* Broadcasting */
    result = getbroadcastsocket(internalbroadcastsocket);
    if (result != CommunicationResult::Ok) {
      goto gos_ex_udpdpoc_loop_process_outputing_result_;
    }
    result = broadcast(*internalbroadcastsocket, datapointer, datasize);
    if (result != CommunicationResult::Ok) {
      goto gos_ex_udpdpoc_loop_process_outputing_result_;
    }
    result = releasebroadcastsocket(internalbroadcastsocket);
    if (result != CommunicationResult::Ok) {
      goto gos_ex_udpdpoc_loop_process_outputing_result_;
    }

    /* Second consumtion */
    result = getbindsocket(internalbindsocket);
    if (result != CommunicationResult::Ok) {
      goto gos_ex_udpdpoc_loop_process_outputing_result_;
    }
    do {
      result = consume(*internalbindsocket, senderaddress, senderport);
      secondcount += result == CommunicationResult::BufferConsumed ? 1 : 0;
    } while (result == CommunicationResult::BufferConsumed);
    if (iscommunicationresulterror(result)) {
      goto gos_ex_udpdpoc_loop_process_outputing_result_;
    }
    result = releasebindsocket(internalbindsocket);
    if (result != CommunicationResult::Ok) {
      goto gos_ex_udpdpoc_loop_process_outputing_result_;
    }

    if (firstcount > 0) {
      wstrstr << " first: " << firstcount;
    }
    if (secondcount > 0) {
      wstrstr << " second: " << secondcount;
    }


    /* Consider incoming buffer */
    if (incomingbuffer && incomingsize > 0) {
      wstrstr << " ";
      parsedata(inid, incomingbuffer.get(), incomingsize);
      dumpdata(wstrstr, inid);
    }
  }
  catch (std::exception ex) {
    wstrstr << L" - exception: " << ex.what();
    goto gos_ex_udpdpoc_loop_process_exit_;
  }
  catch (...) {
    wstrstr << L" - exception!!!";
    goto gos_ex_udpdpoc_loop_process_exit_;
  }

gos_ex_udpdpoc_loop_process_outputing_result_:
  if (internalbindsocket) {
    releasebindsocket(internalbindsocket);
  }
  if (internalbroadcastsocket) {
    releasebroadcastsocket(internalbroadcastsocket);
  }

  wstrstr << L" - " << communicationresult2wstr(result);

gos_ex_udpdpoc_loop_process_exit_:
  CommunicationResult releasebindresult = CommunicationResult::Ok;
  CommunicationResult releasebroadcastresult = CommunicationResult::Ok;
  if (internalbindsocket) {
    releasebindresult = releasebindsocket(internalbindsocket);
    if (releasebindresult != CommunicationResult::Ok) {
      wstrstr << L" (also failed to release a bind socket)";
    }
  }
  if (internalbroadcastsocket) {
    releasebroadcastresult = releasebroadcastsocket(internalbroadcastsocket);
    if (releasebroadcastresult != CommunicationResult::Ok) {
      wstrstr << L" (also failed to release a broadcast socket)";
    }
  }
  if (result == CommunicationResult::Ok) {
    if (releasebindresult == CommunicationResult::Ok) {
      return releasebroadcastresult;
    } else {
      return releasebindresult;
    }
  }
  return result;
}

bool istimeforloop() {
  tick = LoopClock::now();
  if (tick < nextloop) {
    return false;
  } else {
    nextloop = tick + std::chrono::milliseconds{ loopintervalmillis };
    return true;
  }
}

bool istimeforsocketcreation() {
#ifdef GOS_EXAMPLES_C_POC_UDP_DATAGRAMS_SOCKET_LIVE_TIME_MIN
  tick = LoopClock::now();
  if (tick < nextsocketcreation) {
    return false;
  } else {
    nextsocketcreation = tick + std::chrono::minutes{
      GOS_EXAMPLES_C_POC_UDP_DATAGRAMS_SOCKET_LIVE_TIME_MIN };
    return true;
  }
#else
  return false;
#endif
}

CommunicationResult isready() {
  if (!bindendpoint) {
    return CommunicationResult::BindEndpointUndefined;
  }
  return CommunicationResult::Ok;
}

CommunicationResult accesssocket(UdpSocketPointer& socket) {
  if (socket) {
    return CommunicationResult::Ok;
  } else {
    socket = std::make_unique<UdpSocket>(*asiocontext);
  }
  if (!socket) {
    return CommunicationResult::MemorySocket;
  }
  return CommunicationResult::Ok;
}

CommunicationResult getbindsocket(UdpSocketPointer& socket) {
  assert(!socket);
#ifdef GOS_EXAMPLES_C_POC_UDP_DATAGRAMS_SHARE_SOCKET
  UdpSocketPointer& socketpointer = sharedsocket;
#else
  UdpSocketPointer& socketpointer = bindsocket;
#endif
  if (!socketpointer) {
    socketpointer = std::make_unique<UdpSocket>(*asiocontext);
    if (!socketpointer) {
      return CommunicationResult::MemorySocket;
    }
    socketpointer->open(basip::udp::v4(), guderror);
    if (guderror) {
      return CommunicationResult::FailOpen;
    }
    socketpointer->bind(*bindendpoint, guderror);
    if (guderror) {
      return CommunicationResult::FailBind;
    }
  }
  assert(socketpointer);
  socket = std::move(socketpointer);
  assert(!socketpointer);
  assert(socket);
  return CommunicationResult::Ok;
}

CommunicationResult getbroadcastsocket(UdpSocketPointer& socket) {
  assert(!socket);
#ifdef GOS_EXAMPLES_C_POC_UDP_DATAGRAMS_SHARE_SOCKET
  UdpSocketPointer& socketpointer = sharedsocket;
#else
  UdpSocketPointer& socketpointer = broadcastsocket;
#endif
  CommunicationResult result = accesssocket(socketpointer);
  if (result == CommunicationResult::Ok) {
    assert(socketpointer);
    socket = std::move(socketpointer);
    assert(!socketpointer);
    assert(socket);
  }
  return result;
}

CommunicationResult releasebindsocket(UdpSocketPointer& socket) {
  assert(socket);
#ifdef GOS_EXAMPLES_C_POC_UDP_DATAGRAMS_SHARE_SOCKET
  UdpSocketPointer& socketpointer = sharedsocket;
#else
  UdpSocketPointer& socketpointer = bindsocket;
#endif
  assert(!socketpointer);
  socketpointer = std::move(socket);
  assert(socketpointer);
  assert(!socket);
  return CommunicationResult::Ok;
}

CommunicationResult releasebroadcastsocket(UdpSocketPointer& socket) {
  assert(socket);
#ifdef GOS_EXAMPLES_C_POC_UDP_DATAGRAMS_SHARE_SOCKET
  UdpSocketPointer& socketpointer = sharedsocket;
#else
  UdpSocketPointer& socketpointer = broadcastsocket;
#endif
  assert(!socketpointer);
  socketpointer = std::move(socket);
  assert(socketpointer);
  assert(!socket);
  return CommunicationResult::Ok;
}

CommunicationResult consume(
  UdpSocket& socket,
  std::string& address,
  int& port) {
  size_t available = socket.available(guderror);
  if (guderror) {
    return CommunicationResult::FailAvailable;
  }
  CharacterArrayPointer temporarybuffer;
  UdpSocketEndpoint endpoint;
  if (available >= expectedincomingsize) {
    temporarybuffer = std::make_unique<char[]>(expectedincomingsize);
    auto buffer = boost::asio::buffer(
      temporarybuffer.get(), expectedincomingsize);
    size_t size = socket.receive_from(buffer, endpoint, 0, guderror);
    if (guderror) {
      return CommunicationResult::FailConsuming;
    }
    if (size == expectedincomingsize) {
      if (incomingbuffer) {
        /* Ignore last buffer */
        incomingbuffer.reset(new char[expectedincomingsize]);
      } else {
        incomingbuffer = std::make_unique<char[]>(expectedincomingsize);
      }
      if (!incomingbuffer) {
        return CommunicationResult::MemoryBuffer;
      }
      incomingsize = size;
      memcpy(
        incomingbuffer.get(),
        temporarybuffer.get(),
        incomingsize);
      IpAddress sendersaddress = endpoint.address();
      address = sendersaddress.to_string();
      port = endpoint.port();
      return CommunicationResult::BufferConsumed;
    } else if (size > 0) {
      return CommunicationResult::IncomingIncorrectSize;
    } else {
      return CommunicationResult::IncomingZeroSize;
    }
  } else if (available > 0) {
    return CommunicationResult::AvailableIncorrectSize;
  } else {
    return CommunicationResult::NoMoreBuffered;
  }
}

CommunicationResult broadcast(
  UdpSocket& socket,
  const DataPointer& datapointer,
  const size_t& size) {
  size_t sentsize;
  BroadcastRegistryIterator i = broadcastregistry.begin();
  while (i != broadcastregistry.end()) {
    sentsize = socket.send_to(
      boost::asio::buffer(datapointer, size), /* Buffers */
      *i,                                     /* Destination */
      0,                                      /* Flags */
      guderror);                              /* Error code */
    if (guderror) {
      lastsendingto = *i;
      return CommunicationResult::FailSend;
    }
    i++;
  }
  return CommunicationResult::Ok;
}

bool iscommunicationresulterror(const CommunicationResult& result) {
  auto constend = std::end(successfullcommresult);
  return std::find(
    std::begin(successfullcommresult),
    constend,
    result) == constend;
}

void cleanup() {
  recycle();
}

void recycle() {
  if (istimeforsocketcreation()) {
#ifdef GOS_EXAMPLES_C_POC_UDP_DATAGRAMS_SHARE_SOCKET
    if (sharedsocket) {
      if (sharedsocket->is_open()) {
        sharedsocket->shutdown(UdpSocketShutdown::shutdown_both);
        sharedsocket->close();
      }
      sharedsocket.reset(nullptr);
    }
#else
    if (bindsocket) {
      if (bindsocket->is_open()) {
        bindsocket->close();
      }
      bindsocket.reset(nullptr);
    }
    if (broadcastsocket) {
      if (sharedsocket->is_open()) {
        broadcastsocket->close();
      }
      broadcastsocket.reset(nullptr);
    }
#endif
  }
}

void clearincoming() {
  if (incomingbuffer) {
    incomingbuffer.reset(nullptr);
  }
  assert(!incomingbuffer);
  incomingsize = 0;
}

std::string communicationresult2str(const CommunicationResult& result) {
  std::stringstream strstrm;
  switch (result) {
    /* Successfull messages */
  case CommunicationResult::Ok:
    return "ok";
  case CommunicationResult::NoMoreBuffered:
    return "no data waiting";

    /* Failure messages */
  case CommunicationResult::IncomingZeroSize:
    return "zero incoming size";
  case CommunicationResult::IncomingIncorrectSize:
    return "incorrect incoming size";
  case CommunicationResult::AvailableIncorrectSize:
    return "incorrect available size";
  case CommunicationResult::BindEndpointUndefined:
    return "bind endpoint is undefined!";
  case CommunicationResult::MemoryBindEndpoint:
    return "out of memory for bind endpoint creation";
  case CommunicationResult::MemoryResolver:
    return "out of memory for resolver creation";
  case CommunicationResult::MemoryContext:
    return "out of memory for context creation";
  case CommunicationResult::MemorySocket:
    return "out of memory for socket creation";
  case CommunicationResult::MemoryBuffer:
    return "out of memory for incoming buffer creation";
  case CommunicationResult::FailOpen:
    return "failed to open the socket";
  case CommunicationResult::FailBind:
    strstrm << "failed to bind the socket";
    if (bindendpoint) {
      strstrm << " to the address '"
        << bindendpoint->address().to_string()
        << "' through port " << bindendpoint->port();      
    }
    if (guderror) {
      strstrm << ": " << guderror.message();
    }
    return strstrm.str();
  case CommunicationResult::FailSend:
    strstrm << "failed to send to the address '"
      << lastsendingto.address().to_string()
      << "' through port " << lastsendingto.port();
    return strstrm.str();
  case CommunicationResult::FailResolve:
    strstrm << "failed to resolve the address '"
      << lastresolving.address << "' with port " << lastresolving.port;
    return strstrm.str();
  case CommunicationResult::FailAvailable:
    return "getting available from bind socket failed";
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
