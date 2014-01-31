#ifndef UNIQUE_ORDER_ID_H
#define UNIQUE_ORDER_ID_H

#include <sstream>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/date_time/posix_time/posix_time_io.hpp>
#include <boost/thread/mutex.hpp>
#include <fstream>

using namespace std;

namespace UT {
  class UniqueOrderId {
  public:
    static std::string get(char moduleId);
  private:
    static std::string makeString(char moduleId);

    static boost::mutex _mutex;
    static std::string _date;
    static long _orderId;
    static ofstream _outputFile;
    static std::string _fileName;
  };
}

#endif
