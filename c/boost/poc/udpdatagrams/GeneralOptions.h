#ifndef _GOS_EXAMPLES_C_POC_UDP_GENERAL_OPTIONS_H_
#define _GOS_EXAMPLES_C_POC_UDP_GENERAL_OPTIONS_H_

#include <string>

#include <boost/program_options.hpp>

#include <CommunicationOptions.h>

namespace gos {
namespace ex {
namespace udpdpoc {

enum class ParseOptionResult {
  /* Success */
  Ok,

  /* Not need to display */
  OpenDefaultConfigurationFileFailed,

  /* Errors */
  OpenConfigurationFileFailed
};

ParseOptionResult parseoptions(const char* cmdline);
ParseOptionResult parseoptions(int argc, char* argv[]);

bool displayoptionresult(const ParseOptionResult& result);

std::wstring optionresult2wstr(const ParseOptionResult& result);

}
}
}

#endif
