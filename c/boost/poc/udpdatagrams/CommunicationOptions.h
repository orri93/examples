#ifndef _GOS_EXAMPLES_C_POC_UDP_COMMUNICATION_OPTIONS_H_
#define _GOS_EXAMPLES_C_POC_UDP_COMMUNICATION_OPTIONS_H_

#include <string>

#include <boost/program_options.hpp>

namespace gos {
namespace ex {
namespace udpdpoc {

void options(boost::program_options::options_description& description);
void parsevalues();

std::wstring bindmessage();
std::wstring broadcastmessage();
std::wstring datamessage();

}
}
}

#endif