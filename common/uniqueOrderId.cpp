#include "uniqueOrderId.h"
#include <boost/lexical_cast.hpp>

namespace UT {
  // static variables need definition
  boost::mutex UniqueOrderId::_mutex;
  std::string UniqueOrderId::_date="";
  long UniqueOrderId::_orderId = 0;
  ofstream UniqueOrderId::_outputFile;
  std::string UniqueOrderId::_fileName = "";

  std::string UniqueOrderId::get(char moduleId) {

    boost::mutex::scoped_lock lock(_mutex);

    if (UniqueOrderId::_orderId == 0) {
      // First time being read, se if anything in the file
      _fileName = moduleId;
      _fileName += "-";
      _fileName += "orderNumber.txt";

      ifstream inputFile(_fileName.c_str());
      if ( inputFile.is_open() ) {
        std::string line, previousLine;
        while (true) {
          getline(inputFile, line);
          if ( line.empty() ) {
            break;
          } else {
            previousLine = line;
          }
        }
        _orderId = atoi(previousLine.c_str());
        inputFile.close();
      } else {
        std::cout << std::endl << "~!~!~!~!!~!~!~ NO FILE ~!~!~!~!!~!~!~  " << std::endl;
      }
      _outputFile.open(_fileName.c_str());
    }
    _orderId++;
    _outputFile << _orderId << std::endl;
    _outputFile.flush();
    
    boost::posix_time::time_facet
      *facet = new boost::posix_time::time_facet("%Y%m%d");

    std::stringstream ss;

    ss.imbue(locale(ss.getloc(), facet));
    ss << boost::posix_time::second_clock::local_time();

    if (_date == "" ||
        _date != ss.str())
    {
      _date = ss.str();
      //_orderId = 1;
    }

    return makeString(moduleId);
  }

  std::string UniqueOrderId::makeString(char moduleId)
  {
    std::stringstream ss;
    ss << moduleId;
    ss << _date;
    ss << setw(10)
       << setfill('0')
       << _orderId;
    return ss.str();
  }

}
