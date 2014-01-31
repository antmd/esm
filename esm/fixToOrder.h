#ifndef ESM_FIX_TO_ORDER_H
#define ESM_FIX_TO_ORDER_H

#include <quickfix/Fields.h>
#include "structures.h"
#include "exceptions.h"

namespace ESM
{
  class ToFix
  {
    public :
    static FIX::Side convert( Side side )
    {
      switch( side )
      {
        case Side_BUY :
          return FIX::Side_BUY ;
        case Side_SELL :
          return FIX::Side_SELL ;
      }
      throw OrderError( "Unknown Side" ) ;
    }

    static FIX::OrdType convert( OrderType ordType )
    {
      switch( ordType )
      {
        case OrderType_MARKET :
          return FIX::OrdType_MARKET ;
        case OrderType_LIMIT :
          return FIX::OrdType_LIMIT ;
        case OrderType_STOP :
          return FIX::OrdType_STOP ;
        case OrderType_STOP_LIMIT:
          return FIX::OrdType_STOP_LIMIT ;
      }
      throw OrderTypeNotHandled( "" ) ;
    }

    /*
    static FIX::OrdStatus convert( OrderStatus orderStatus )
    {
      switch( orderStatus )
      {
        case OrderStatus_NEW :
          return FIX::OrdStatus_NEW ;
        case OrderStatus_REPLACED :
          return FIX::OrdStatus_REPLACED ;
        case OrderStatus_CANCELLED :
          return FIX::OrdStatus_CANCELED ;
        case OrderStatus_MARKET_TO_LIMIT :
          return FIX::ExecType_RESTATED ;
        case OrderStatus_TRIGGERED :
          return 'T' ;
        case OrderStatus_PARTIALLY_FILLED :
          DEBUG_1( "Sending partially filled " ) ;
          return FIX::OrdStatus_PARTIALLY_FILLED ;
        case OrderStatus_FILLED :
          DEBUG_1( "Sending filled " ) ;
          return FIX::OrdStatus_FILLED  ;
      }
      throw OrderStatusNotHandled( "" ) ;
    }
    */
  };

  class FromFix
  {
    public :
    static Side convert( const FIX::Side &side )
    {
      switch( side )
      {
        case FIX::Side_BUY :
          return Side_BUY ;
        case FIX::Side_SELL :
          return Side_SELL ;
      }
      throw SideNotHandled( side.getString() ) ;
    }

    static OrderType convert( const FIX::OrdType &ordType )
    {
      switch( ordType )
      {
        case FIX::OrdType_MARKET :
          return OrderType_MARKET ;
        case FIX::OrdType_LIMIT :
          return OrderType_LIMIT ;
        case FIX::OrdType_STOP :
          return OrderType_STOP ;
        case FIX::OrdType_STOP_LIMIT :
          return OrderType_STOP_LIMIT;
      }
      throw OrderTypeNotHandled( ordType.getString() ) ;
    }

    static TimeInForce convert( const FIX::TimeInForce &timeInForce )
    {
      switch( timeInForce )
      {
        case FIX::TimeInForce_DAY :
          return TimeInForce_DAY ;
        case FIX::TimeInForce_IMMEDIATE_OR_CANCEL :
          return TimeInForce_IOC ;
      }
      throw TimeInForceNotHandled( timeInForce.getString() ) ;
    }
  };

}

#endif // ESM_FIX_TO_ORDER_H
