#ifndef ESM_ORDER_BOOK_H
#define ESM_ORDER_BOOK_H

#include <boost/thread.hpp>

#include "orderList.h"
#include "replyApplication.h"

namespace ESM
{
  class OrderBook
  {
    public :
      OrderBook( ReplyApplication &replyApplication, OrderPtr order ) ;

      void insert( OrderPtr order ) ;
      void replace( OrderPtr order ) ;
      void cancel( OrderPtr order ) ;

      const MarketPicture::Record &getMarketPictureRecord( ) ;

      bool hasChanged() { return _hasChanged ; } 

      void start() ;
      void stop() ;

    private :
      DescOrderList _buyOrders ;
      AscOrderList _sellOrders ;

      AscOrderList _stopLossBuyOrders ;
      DescOrderList _stopLossSellOrders ;

      ReplyApplication &_replyApplication ;

      bool _hasChanged ;

      MarketPicture::Record _marketPictureRecord ;

      boost::mutex _mutexOnMatch ;

      bool _isActive ;

      void insertBuy( OrderPtr order ) ;
      void insertSell( OrderPtr order ) ;
      void insertStopLossBuy( OrderPtr order ) ;
      void insertStopLossSell( OrderPtr order ) ;

      void replaceBuy( OrderPtr order ) ;
      void replaceSell( OrderPtr order ) ;

      void checkTriggeredOrders( ) ;
      void updateMarketData( int price, int qty ) ;

      void print() ;

      template< class CancelOrderList >
        void cancelAll( CancelOrderList &list )
        {
          char displayChar = '\\' ;

          OrderPtr canceledOrder ;

          try
          {
            while( true ) // When the list is over, we will get a exception ListIsEmpty thrown 
            {
              canceledOrder = list.first() ;
              canceledOrder = list.cancel( canceledOrder ) ;
              _replyApplication.sendCancelConfirm( canceledOrder, "Order Cancelled As System Is Shutting Down" ) ;

              std::cout << '\b' << displayChar  ;
              switch( displayChar )
              {
                case '\\' :
                  displayChar = '|' ;
                  break ;
                case '|' :
                  displayChar = '/' ;
                  break ;
                case '/' :
                  displayChar = '-' ;
                  break ;
                case '-' :
                  displayChar = '\\' ;
                  break ;
              }

              _hasChanged = true ;
            }
            std::cout << '\b' ;
          }catch( ListIsEmpty &e) {
          }
        }
  };

  typedef boost::shared_ptr< OrderBook > OrderBookPtr ;
}
#endif // ESM_ORDER_BOOK_H
