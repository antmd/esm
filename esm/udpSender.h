#ifndef UT_ESM_UDP_SENDER_H
#define UT_ESM_UDP_SENDER_H

#include <cstdlib>
#include <cstring>
#include <iostream>
#include <boost/asio.hpp>

#include "structures.h"

using boost::asio::ip::udp;

namespace ESM 
{
  class UdpSender
  {
    public :
      UdpSender( const std::string &address, const std::string &port ) 
      {
        _socket = new udp::socket( _ioService, udp::endpoint(udp::v4(), 0) ) ;

        udp::resolver resolver( _ioService );
        udp::resolver::query query( udp::v4(), address.c_str(), port.c_str());
        _iterator = resolver.resolve(query);
      }

      void send( const Message &message )
      {
        try
        {
          _socket->send_to( boost::asio::buffer( &message, message.getMsgLen() + 8 ), *_iterator ) ;
        }
        catch (std::exception& e)
        {
          std::cerr << "Exception: " << e.what() << "\n";
        }
      }

      ~UdpSender()
      {
        delete _socket ;
      }

    private :
      udp::socket *_socket ;
      udp::resolver::iterator _iterator ;

      boost::asio::io_service _ioService;
  };

}
#endif
