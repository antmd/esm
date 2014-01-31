#ifndef ESM_ORDER_LISTH_H
#define ESM_ORDER_LISTH_H

#include <map>
#include <boost/unordered_map.hpp>

#include "../common/definesForCreateEndianless.h"
#include "order.h"

namespace ESM
{
  struct MarketData
  {
      UT::LONG price[5] ;
      UT::LONG qty[5] ;
  };

  template< class Compare >
  class OrderList
  {
    // class OrdersByPriceMap : public std::multimap< long, OrderPtr, std::less <long> > {} ;
    // class OrdersByOrderIdMap : public boost::unordered_map< std::string, OrdersByPriceMap::iterator > {} ;
    typedef typename std::multimap < long, OrderPtr, Compare > OrdersByPriceMap; 
    typedef typename boost::unordered_map< std::string, typename OrdersByPriceMap::iterator > OrdersByOrderIdMap ;

    public :

      OrderPtr first()
      {
        _iOrdersByPrice = _ordersByPrice.begin() ;
        if( _iOrdersByPrice == _ordersByPrice.end() )
        {
          //DEBUG_1( "OrderList is empty so throwing" ) ;
          throw ListIsEmpty() ;
        }
        return _iOrdersByPrice->second ;
      }

      bool insert( long price, OrderPtr order )
      {
        //boost::mutex::scoped_lock lock( _mutexForMarketData ) ;
        _iOrdersByPrice = _ordersByPrice.insert ( typename OrdersByPriceMap::value_type ( price, order ) ) ;
        _ordersByOrderId.insert ( std::make_pair (  order->getOrderId(),  _iOrdersByPrice ) ) ;
        //DEBUG_4( "inserting with price ", price, " and qty ", order->getPendingQty() ) ;
        return true ;
      }

      OrderPtr cancel( OrderPtr order )
      {
        //boost::mutex::scoped_lock lock( _mutexForMarketData ) ;
        _iOrdersByOrderId = _ordersByOrderId.find( order->getOrderId() ) ;
        if( _iOrdersByOrderId == _ordersByOrderId.end() )
        {
          throw OrderIdNotFound( order->getOrderId() ) ;
        }
        OrderPtr oldOrder = _iOrdersByOrderId->second->second ;
        oldOrder->cancel( *order ) ;

        _ordersByPrice.erase( _iOrdersByOrderId->second ) ;
        _ordersByOrderId.erase( _iOrdersByOrderId ) ;

        return oldOrder ;
      }

      OrderPtr replace( OrderPtr order )
      {
        //boost::mutex::scoped_lock lock( _mutexForMarketData ) ;
        _iOrdersByOrderId = _ordersByOrderId.find( order->getOrderId() ) ;
        if( _iOrdersByOrderId == _ordersByOrderId.end() )
        {
          throw OrderIdNotFound( order->getOrderId() ) ;
        }

        OrderPtr oldOrder = _iOrdersByOrderId->second->second ;

        // UT::LONG oldPrice = oldOrder->getPrice() ;
        // UT::LONG oldPendingQty = oldOrder->getPendingQty() ;
        //DEBUG_4( "Old price ", oldPrice, " and old qty ", oldPendingQty ) ;
        //DEBUG_4( "New  price ", order->getPrice(), " and New  qty ", order->getPendingQty() ) ;

        oldOrder->replace( *order ) ;

        //DEBUG_4( "New price ", oldOrder->getPrice(), " and New qty ", oldOrder->getPendingQty() ) ;
        return oldOrder ;
      }

      MarketData &getMarketData( )
      {
        //boost::mutex::scoped_lock lock( _mutexForMarketData ) ;

        _marketData.price[0] = 0 ;
        _marketData.qty[0] = 0 ;
        _marketData.price[1] = 0 ;
        _marketData.qty[1] = 0 ;
        _marketData.price[2] = 0 ;
        _marketData.qty[2] = 0 ;
        _marketData.price[3] = 0 ;
        _marketData.qty[3] = 0 ;
        _marketData.price[4] = 0 ;
        _marketData.qty[4] = 0 ;

        _counter = 0 ;
        _iOrdersByPriceForMarketData = _ordersByPrice.begin() ;

        if ( _iOrdersByPriceForMarketData != _ordersByPrice.end() ) 
        {
          _marketData.price[_counter] = _iOrdersByPriceForMarketData->first ;
          _marketData.qty[_counter] = _iOrdersByPriceForMarketData->second->getPendingQty() ;

          while ( ++_iOrdersByPriceForMarketData != _ordersByPrice.end() ) 
          {
            if( _marketData.price[_counter] == _iOrdersByPriceForMarketData->first )
            {
              _marketData.qty[_counter] += _iOrdersByPriceForMarketData->second->getPendingQty() ;
            }
            else 
            {
              if( ++_counter == 5 ) break ;

              _marketData.price[_counter] = _iOrdersByPriceForMarketData->first ;
              _marketData.qty[_counter] = _iOrdersByPriceForMarketData->second->getPendingQty() ;
            }
          }
        }
        else
        {
          //std::cout << "i didnt find any market data" << std::endl ;
        }

        return _marketData ;
      }

      void print()
      {
        std::cout << "=============BEGIN============================" << std::endl ;
        for( _iOrdersByPrice = _ordersByPrice.begin() ;
             _iOrdersByPrice != _ordersByPrice.end() ;
             ++_iOrdersByPrice )
        {
          _iOrdersByPrice->second->print() ;
        }
        std::cout << "=============END============================\n\n" << std::endl ;

      }

      OrderPtr erase( const OrderPtr &order )
      {
        return erase( order->getOrderId() ) ;
      }

      OrderPtr erase( const std::string &orderId )
      {
        //boost::mutex::scoped_lock lock( _mutexForMarketData ) ;
        _iOrdersByOrderId = _ordersByOrderId.find( orderId ) ;

        if( _iOrdersByOrderId != _ordersByOrderId.end() )
        {
          OrderPtr order = _iOrdersByOrderId->second->second ;

          _ordersByPrice.erase( _iOrdersByOrderId->second ) ;
          _ordersByOrderId.erase( _iOrdersByOrderId ) ;
          //DEBUG_1( "After deleting from list " ) ;
          return order ;
        }
        throw OrderIdNotFound( orderId ) ;
      }

      void fill( long price, long qty )
      {
        //boost::mutex::scoped_lock lock( _mutexForMarketData ) ;
        OrderPtr order = first() ;
        order->fill( price, qty ) ;
        if( order->getPendingQty() == 0) 
        {
          erase( order ) ;
        }
      }

    private :
      OrdersByPriceMap _ordersByPrice ;
      OrdersByOrderIdMap _ordersByOrderId ;
      MarketData _marketData ;

      typename OrdersByPriceMap::iterator _iOrdersByPrice;
      typename OrdersByOrderIdMap::iterator _iOrdersByOrderId;

      typename OrdersByPriceMap::iterator _iOrdersByPriceForMarketData;
      int _counter ;

      //boost::mutex _mutexForMarketData ;
  };

  /* Order book sorted by price Ascending */
  class AscOrderList : public OrderList < std::less<long> > {};
  
  /* Order book sorted by price Descending */
  class DescOrderList : public OrderList < std::greater< long> > { };
}

#endif // ESM_ORDER_LISTH_H
