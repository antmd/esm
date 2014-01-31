
#ifndef ESM_ORDER_H
#define ESM_ORDER_H

#include <string>

#include "errorMessages.h"
#include "exceptions.h"
#include "structures.h"

#include "../common/uniqueOrderId.h"

namespace ESM
{
  class Order
  {
    public :
      Order( const std::string &orderId,
             const std::string &securityId,
             const std::string &clientOrderId,
             const std::string &senderId,
             Side side,
             OrderType orderType,
             long orderQty
           ) 
        : _originalClientOrderId( "" ),

          _orderId( orderId ) ,
          _securityId( securityId ),
          _clientOrderId( clientOrderId ),
          _senderId( senderId ),
          _side( side ),
          _orderType( orderType ),
          _orderQty( orderQty ),
          //_orderStatus( OrderStatus_NEW ),
          _timeInForce( TimeInForce_DAY ),

          _price( 0 ),
          _stopPrice( 0 ),
          _filledQty( 0 ),
          _disclosedPendingQty( orderQty ) ,
          _avgPrice( 0 ),
          _lastPrice( 0 ),
          _lastShares( 0 ),
          _disclosedQty( orderQty )
      {
      }

      // All the Set Fields
      bool isFilled() const ;

      void cancel ( const Order &order ) ;
      bool replace ( const Order &order ) ;
      void fill( long price, long qty);

      void trigger()  ;
      void setMarketToLimit( long price ) ;
      void print() ;

      const std::string &getSecurityId() const { return _securityId ; }
      const std::string &getClientOrderId() const { return _clientOrderId ; }
      const std::string &getSenderId() const { return _senderId ; }
      Side getSide() const { return _side ; }
      OrderType getOrderType() const { return _orderType ; }
      long getOrderQty() const { return _orderQty ; } 
      TimeInForce getTimeInForce() const { return _timeInForce; }

      const std::string &getOrderId() const { return _orderId ; }
      const std::string &getOriginalClientOrderId() const { return _originalClientOrderId ; }

      //primary keys
      long getPrice() const { return _price; }
      long getStopPrice() const { return _stopPrice; }
      long getAvgPrice() const { return _avgPrice; }
      long getLastPrice() const { return _lastPrice; }
      long getLastShares() const { return _lastShares; }
      long getFilledQty() const { return _filledQty ; }
      long getPendingQty() const { return _disclosedPendingQty ; }
      long getActualPendingQty() const { return _orderQty - _filledQty ; }
      long getDisclosedQty() const { return _disclosedQty ; } 
      //OrderStatus getOrderStatus() const { return _orderStatus ; }

      void setPrice( long price ) { _price = price ; }
      void setStopPrice( long stopPrice ) { _stopPrice = stopPrice ; }
      void setTimeInForce( TimeInForce timeInForce ) { _timeInForce = timeInForce ; }
      void addOrderQty( long orderQty ) { _orderQty += orderQty ; }
      void setDisclosedQty( long disclosedQty ) 
      {
        _disclosedQty = disclosedQty ;
        setPendingQty() ;
      }

    protected :
      std::string _originalClientOrderId ;
    private :
      std::string _orderId ;
      std::string _securityId ;
      std::string _clientOrderId ;
      std::string _senderId ;
      Side _side ;
      OrderType _orderType ;
      long _orderQty ;
      //OrderStatus _orderStatus ;
      TimeInForce _timeInForce ;


      //primary keys
      long _price ;
      long _stopPrice ;
      long _filledQty ;
      long _disclosedPendingQty ;
      long _avgPrice ;
      long _lastPrice ;
      long _lastShares ;
      long _disclosedQty ;

      void setPendingQty()
      {
        _disclosedPendingQty = ( _disclosedQty > 0 && _disclosedQty < getActualPendingQty() ) ?
                                   _disclosedQty : getActualPendingQty() ;
        //DEBUG_2( "getPendingQty()", getPendingQty() ) ;
      }
  };

  //inline bool Order::isFilled() const { return _orderStatus == OrderStatus_FILLED ;} 

  inline void Order::cancel ( const Order &order ) { 
    //_orderStatus = OrderStatus_CANCELLED ; 
    _originalClientOrderId = _clientOrderId ;
    _clientOrderId = order.getClientOrderId() ;
  }
  inline bool Order::replace ( const Order &order ) 
  {
    if( order.getOrderQty() <= _filledQty )
    {
      throw RejectReplace( "New order qty is less than filled qty" ) ;
    }

    // OrderPtr originalOrder( new Order( this ) ) ;

    _orderQty = order.getOrderQty() ;
    _disclosedQty = order.getDisclosedQty() ;
    setPendingQty() ;

    _originalClientOrderId = _clientOrderId ;
    _clientOrderId = order.getClientOrderId() ;
    _timeInForce = order.getTimeInForce() ;

    bool lostPriority = false ;
    //DEBUG_4( "Old price ", _price, " new price ", order.getPrice() ) ;
    if( order.getOrderType() == OrderType_MARKET || order.getOrderType() == OrderType_STOP )
    {
      lostPriority = true ;
      _orderType = order.getOrderType() ;
    }
    else if( _price != order.getPrice() )
    {
      lostPriority = true ;
      _price = order.getPrice() ;
    }

    if( _orderType != order.getOrderType() )
    {
      lostPriority = true ;
      _orderType = order.getOrderType() ;
    }

    if( _stopPrice != order.getStopPrice() )
    {
      lostPriority = true ;
      _stopPrice = order.getStopPrice() ;
    }
    //_orderStatus = OrderStatus_REPLACED ;

    if( lostPriority )
    {
      throw OrderHasChanged( ) ;
    }
    return true ;
  }

  inline void Order::fill( long price, long qty)
  {
    _avgPrice =   (  ( qty * price )
                    +( getAvgPrice() * getFilledQty() ) )
                / ( qty + getFilledQty() ) ;

    _lastPrice = price;
    _lastShares =  qty;
    _filledQty  += qty;

    //DEBUG_2( "getActualPendingQty()", getActualPendingQty() ) ;
    setPendingQty() ;

    /*
    if( getPendingQty() > 0 ) { 
      //DEBUG_1( "Partial fill order" ) ;
      //_orderStatus = OrderStatus_PARTIALLY_FILLED  ;
    } else {
      //DEBUG_1( "Filled order" ) ;
      //_orderStatus = OrderStatus_FILLED  ;
    }
    */
  }

  inline void Order::trigger() 
  {
    if( _orderType == OrderType_STOP_LIMIT ) {
      _orderType = OrderType_LIMIT ;
    } else {
      _orderType = OrderType_MARKET ;
    }
    //_orderStatus = OrderStatus_TRIGGERED ;
  }

  inline void Order::setMarketToLimit( long price )
  {
    //DEBUG_2( "Setting market to limit at : " , price ) ;
    _orderType = OrderType_LIMIT ;
    _price = price ;
    //_orderStatus = OrderStatus_MARKET_TO_LIMIT ;
  }

  inline void Order::print() 
  {
    std::cout << "ID: "       << std::left << std::setw(5)  << _orderId << "| " 
              << "OWNER: "    << std::left << std::setw(15) << _senderId  << "| "
              << "PRICE: "    << std::left << std::setw(10) << _price     << "| "
              << "QUANTITY: " << std::left << std::setw(10) << _orderQty  << "| "
              << "OPEN QTY: " << std::left << std::setw(10) << getActualPendingQty() << "|"
              << std::endl ;
  }

  class NewOrder : public Order
  {
    private :
      static UT::UniqueOrderId _uniqueOrderId ;



    public :
      NewOrder( const std::string &securityId,
                const std::string &clientOrderId,
                const std::string &senderId,
                Side side,
                OrderType orderType,
                long orderQty
           ) 
        : Order( _uniqueOrderId.get('0'),
                 securityId, 
                 clientOrderId, 
                 senderId, 
                 side, 
                 orderType, 
                 orderQty ) 
      {
      }
  };

  class CancelReplaceOrder : public Order
  {
    public :
      CancelReplaceOrder( const std::string &orderId,
                   const std::string &originalClientOrderId,
                   const std::string &securityId,
                   const std::string &clientOrderId,
                   const std::string &senderId,
                   Side side,
                   OrderType orderType,
                   long orderQty
              ) 
        : Order( orderId, securityId, clientOrderId, senderId, side, orderType, orderQty ) 
      {
        _originalClientOrderId = originalClientOrderId ;
      }
  };
  typedef CancelReplaceOrder CancelOrder ;
  typedef CancelReplaceOrder ReplaceOrder ;

  typedef boost::shared_ptr< Order > OrderPtr ;
  typedef boost::shared_ptr< NewOrder > NewOrderPtr ;
  typedef boost::shared_ptr< CancelOrder > CancelOrderPtr ;
  typedef boost::shared_ptr< ReplaceOrder > ReplaceOrderPtr ;

}

#endif
