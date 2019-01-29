// udpdatagramscli.cpp : Defines the entry point for the console application.
//

#ifdef WIN32
#include <SDKDDKVer.h>
#include <stdio.h>
#include <tchar.h>
#endif

#include <iostream>
#include <chrono>

#include <UdpDatagrams.h>
#include <GeneralOptions.h>
#include <DataStructures.h>
#include <Text.h>

#include "Handler.h"

#define GOS_TIMER_INTERVAL 100

#ifdef WIN32
#else
#endif

namespace gos {
namespace ex {
namespace udpdpoc {

static unsigned long long incremental = 0;

int Initialize(int argc, char* argv[]) {
  std::wstring wmsg;

  /* Reverse the defaults */
  struct ipconfiguration default_binding = {
    GOS_DEFAULT_BIND_ADDRESS,
    GOS_DEFAULT_BROADCAST_PORT
  };
  struct ipconfiguration default_broadcast = {
    GOS_DEFAULT_BROADCAST_ADDRESS,
    GOS_DEFAULT_BIND_PORT
  };
  setdefaults(
    default_binding,
    default_broadcast,
    GOS_DEFAULT_INCOMING_DATA_ID,
    GOS_DEFAULT_OUTGOING_DATA_ID);

  ParseOptionResult optionparseresult = parseoptions(argc, argv);
  if (displayoptionresult(optionparseresult)) {
    wmsg = optionresult2wstr(optionparseresult);
    std::wcout << wmsg << std::endl;
  }

  wmsg = bindmessage();
  std::wcout << wmsg << std::endl;
  wmsg = broadcastmessage();
  std::wcout << wmsg << std::endl;
  wmsg = datamessage();
  std::wcout << wmsg << std::endl;

  CommunicationResult comminitresult = initialize(GOS_TIMER_INTERVAL);
  if (comminitresult != CommunicationResult::Ok) {
    std::wstring errormessage = communicationresult2wstr(comminitresult);
    std::wcerr << errormessage << std::endl;
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}

}
}
}

typedef std::chrono::steady_clock LoopClock;
typedef LoopClock::time_point LoopTimePoint;

int _tmain(int argc, char* argv[])
{
  int result = EXIT_SUCCESS;

  result = gos::ex::udpdpoc::Initialize(argc, argv);
  if (result != EXIT_SUCCESS) {
    return result;
  }

  gos::ex::udpdpoc::rununtilbreak = true;
  while (gos::ex::udpdpoc::rununtilbreak) {
    if (gos::ex::udpdpoc::istimeforloop()) {
      std::wstringstream wstrstr;
      gos::ex::udpdpoc::loop(wstrstr, gos::ex::udpdpoc::incremental++);
      std::wcout << wstrstr.str() << std::endl;
    }
  }
  try {
    std::lock_guard<std::mutex> guard(gos::ex::udpdpoc::breakstringmutex);    
    std::wcout << std::endl << gos::ex::udpdpoc::breakingmessage << std::endl;
    gos::ex::udpdpoc::cleanup();
  }
  catch (std::exception ex) {
    std::cerr << "Locking for Ctrl handler failed with an exception: "
      << ex.what() << std::endl;
    return EXIT_FAILURE;
  }
  catch (...) {
    std::cerr << "Locking for Ctrl handler failed with an exception!"
      << std::endl;
    return EXIT_FAILURE;
  }

  return result;
}

