#ifdef WIN32
#include <SDKDDKVer.h>
// Exclude rarely-used stuff from Windows headers
#define WIN32_LEAN_AND_MEAN
// Windows Header Files:
#include <windows.h>
#endif

#include <iostream>
#include <iterator>
#include <fstream>
#include <sstream>

#include <boost/algorithm/string.hpp>

#include <Text.h>
#include <GeneralOptions.h>

namespace po = boost::program_options;

namespace gos {
namespace ex {
namespace udpdpoc {

typedef std::vector<std::string> CmdLineVector;
typedef CmdLineVector::iterator CmdLineVectorIterator;

static const char* DefaultConfigurationFile = "udpdatagrams.cfg";

static std::string configuration_file_name;

static po::options_description generic_description("Generic options");
static po::options_description configuration_file_description;

static void createoptions();
static void processcmdline(CmdLineVector& vector, const char* cmdline);

static ParseOptionResult processconfigurationfile(po::variables_map& varmap);
static ParseOptionResult parseoptions(CmdLineVector cmdlineargs);

ParseOptionResult parseoptions(const char* cmdline) {
  ParseOptionResult result = ParseOptionResult::Ok;

  CmdLineVector cmdlineargs;
  processcmdline(cmdlineargs, cmdline);

  createoptions();
  
  po::variables_map varmap;
  po::command_line_parser cmdlinparser(cmdlineargs);
  po::parsed_options parseopt = cmdlinparser.options(generic_description)
    .style(po::command_line_style::default_style).run();
  po::store(parseopt, varmap);
  po::notify(varmap);

  result = processconfigurationfile(varmap);

  parsevalues();

  return result;
}

ParseOptionResult parseoptions(int argc, char* argv[]) {
  ParseOptionResult result = ParseOptionResult::Ok;

  createoptions();

  po::variables_map varmap;
  po::command_line_parser cmdlinparser(argc, argv);
  po::parsed_options parseopt = cmdlinparser.options(generic_description)
    .style(po::command_line_style::default_style).run();
  po::store(parseopt, varmap);
  po::notify(varmap);

  result = processconfigurationfile(varmap);

  parsevalues();

  return result;
}

void createoptions() {
  generic_description.add_options()
    ("version,v", "print version string")
    ("help,h", "show help message")
    ("config,c", po::value<std::string>(&configuration_file_name)->
    default_value(DefaultConfigurationFile),
    "name of a file of a configuration");
  po::options_description confoptdesc("Configuration");
  gos::ex::udpdpoc::options(confoptdesc); // Creaet UDP options
  po::options_description cmdloptdesc;
  cmdloptdesc.add(generic_description).add(confoptdesc);
  configuration_file_description.add(confoptdesc);
}

void processcmdline(CmdLineVector& vector, const char* cmdline) {
  std::string trimed, cmdlinestr = std::string((const char*)cmdline);
  if (cmdlinestr.size() > 0) {
    CmdLineVector temporaryvector;
    boost::split(temporaryvector, cmdlinestr, [](char c){
      return c == ' ' || c == '\t'; });
    CmdLineVectorIterator i, e = temporaryvector.end();
    for (i = temporaryvector.begin(); i != e; i++) {
      trimed = ::boost::algorithm::trim_copy(*i);
      if (trimed.size() > 0) {
        vector.push_back(trimed);
      }
    }
  }
}

static ParseOptionResult processconfigurationfile(po::variables_map& varmap) {
  ParseOptionResult result = ParseOptionResult::Ok;
  std::ifstream conffilestream(configuration_file_name.c_str());
  if (conffilestream) {
    auto parsedfile = po::parse_config_file(
      conffilestream,
      configuration_file_description);
    po::store(parsedfile, varmap);
    po::notify(varmap);
  }
  else {
    result = configuration_file_name == DefaultConfigurationFile ?
      ParseOptionResult::OpenDefaultConfigurationFileFailed :
      ParseOptionResult::OpenConfigurationFileFailed;
  }
  return result;
}

bool displayoptionresult(const ParseOptionResult& result) {
  return result != ParseOptionResult::OpenDefaultConfigurationFileFailed;
}

std::wstring optionresult2wstr(const ParseOptionResult& result) {
  std::wstringstream wstrstr;
  switch (result) {
    /* Successfull messages */
  case ParseOptionResult::Ok:
    wstrstr << L"Successfully processed the configuration file "
      << text2wtext(configuration_file_name);
    return wstrstr.str();
  case ParseOptionResult::OpenConfigurationFileFailed:
    wstrstr << L"Failed to open configuration file "
      << text2wtext(configuration_file_name);
    return wstrstr.str();
  default:
    return L"Not yet implemented option result text!!!";
  }
}

}
}
}
