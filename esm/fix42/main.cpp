#include "../../config.h"

#include <boost/program_options.hpp>
#include <fstream>

#include "quickfix/FileStore.h"
#include "quickfix/ThreadedSocketAcceptor.h"

#include "requestApplication.h"
#include "replyApplication.h"

int main ( int argc, char * argv[] )
{
  namespace bpo = boost::program_options;

  std::string esmSettingsFile, configFile, udpAddress, udpPort ;

  bpo::options_description visible("Allowed options");
  bpo::variables_map vm;

  try {
    // only command-line options
    bpo::options_description generic("Generic options");
    generic.add_options()
      ("version,v", "print version string")
      ("help,h", "produce help message")
      ("config,c",
       bpo::value<std::string>(&configFile)->default_value("utrade.conf"),
       "configuration file.")
      ;

    // both on command line and config file options
    bpo::options_description config("Configuration");
    config.add_options()
      ("ESM.nse_settings_file", bpo::value<std::string>(&esmSettingsFile), "Settings file to configure ESM NSE")
      ("ESM.nse_udp_host", bpo::value<std::string>(&udpAddress), "udp host for market data")
      ("MCL.esmnse_port", bpo::value<std::string>(&udpPort), "Udp Port For MarketData")
      ;

    bpo::options_description cmdLineOptions;
    cmdLineOptions.add(generic).add(config);

    bpo::options_description configFileOptions;
    configFileOptions.add(config);

    visible.add(generic).add(config);

    store(bpo::command_line_parser(argc, argv).options(cmdLineOptions).run(), vm);
    notify(vm);

    std::ifstream ifs(configFile.c_str());
    if (ifs) {
      store(parse_config_file(ifs, configFileOptions, true), vm);
      notify(vm);
    }
    else {
      std::cout << "Cannot open file " << configFile << std::endl ;
      return 1 ;
    }

    if (vm.count("help")) {
      std::cout << visible << std::endl ;
      return 1;
    }

    if (vm.count("version")) {
      std::cout << "uTrade ESM version 2.0 : " VERSION_STRING "\n";
      return 1;
    }

    if( !vm.count( "ESM.nse_udp_host" ) )
    {
      std::cout << "Host to send market data missing in config file: ESM.nse_udp_host " << std::endl ;
      return 1;
    }
    else if( !vm.count( "MCL.esmnse_port" ) )
    {
      std::cout << "Address to send market data missing in config file: MCL.esmnse_port" << std::endl ;
      return 1;
    }
    else if( !vm.count( "ESM.nse_settings_file" ) )
    {
      std::cout << "FIX Settings file for ESMNSE is missing : ESM.nse_settings_file " << std::endl ;
      return 1;
    }
  }
  catch(boost::program_options::error &e) {
    std::cout << "Found error in the configuration file : " << e.what() << std::endl ;
    return 1;
  }
  catch(std::exception& e) {
    std::cout << "Found an error : " << e.what() << std::endl ;
    return 1;
  }

  try 
  {
    FIX::SessionSettings settings( esmSettingsFile );
    ESM::NSE::RequestApplication requestApplication( udpAddress, udpPort ) ;

    FIX::SessionSettings sessionSettings( settings )  ;
    FIX::FileStoreFactory fileStoreFactory( settings );
    //FIX::ScreenLogFactory screenLogFactory( settings );
    FIX::ThreadedSocketAcceptor acceptor( requestApplication, fileStoreFactory, sessionSettings /*, screenLogFactory */);

    acceptor.start() ;

    requestApplication.readCommands() ;

    acceptor.stop() ;
  }
  catch( std::exception &e )
  {
    std::cout << "stopping due to error " << e.what() << std::endl ;
  }

  return 0 ;

}
