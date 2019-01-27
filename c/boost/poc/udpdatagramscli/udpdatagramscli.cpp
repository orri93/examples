// udpdatagramscli.cpp : Defines the entry point for the console application.
//

#ifdef WIN32
#include <SDKDDKVer.h>
#include <stdio.h>
#include <tchar.h>
#endif

#include <iostream>
#include <chrono>
#include <atomic>

#include <GeneralOptions.h>
#include <Text.h>

#define GOS_TIMER_INTERVAL 500

#ifdef WIN32
#else
#endif

static std::atomic_bool rununtilbreak;

namespace gos {
namespace ex {
namespace udpdpoc {

static ParseOptionResult optionparseresult;

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

  optionparseresult = parseoptions(argc, argv);
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

  return 0;
}

}
}
}

int _tmain(int argc, char* argv[])
{
  int result = 0;

  result = gos::ex::udpdpoc::Initialize(argc, argv);

  std::chrono::steady_clock clock;
  std::chrono::steady_clock::time_point tick, next = clock.now();

  rununtilbreak = true;
  while (rununtilbreak) {
    tick = clock.now();
    if (tick >= next) {
      std::wstringstream wstrstr;
      wstrstr << gos::ex::udpdpoc::clocktext();
      std::wcout << wstrstr.str() << std::endl;
      next = tick + std::chrono::milliseconds{ GOS_TIMER_INTERVAL };
    }
  }

	return 0;
}

