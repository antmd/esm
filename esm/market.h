#ifndef ESM_MARKET_H
#define ESM_MARKET_H

#include "orderBook.h"
#include "udpSender.h"

namespace ESM
{
  class Market
  {
    public :
      Market( ReplyApplication &replyApplication,
              const std::string &address,
              const std::string &port) ;

      void insert( NewOrderPtr order ) ;
      void replace( ReplaceOrderPtr order ) ;
      void cancel( CancelOrderPtr order ) ;

      void readCommands( ) ;
      bool executeCommand( const std::string &command ) ;

      void stop() ;
      void start() ;

    private :
      ReplyApplication &_replyApplication ;

      typedef boost::unordered_map< std::string, OrderBookPtr > OrderBooksMap ;
      OrderBooksMap _orderBooks ;
      MarketPicture _marketPicture ;

      boost::mutex _mutexForNewBook ;

      std::vector< OrderBookPtr > _orderBooksForMarketPicture ;
      void sendMarketPicture() ;

      UdpSender _udpSender ;
  };
}
#endif // ESM_MARKET_H
