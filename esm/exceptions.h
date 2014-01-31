#ifndef ESM_EXCEPTIONS_H
#define ESM_EXCEPTIONS_H

#include <string>
#include "order.h"

namespace ESM
{
  class Exception : public std::exception
  {
    public :
      Exception() {} 

      Exception(const std::string errorType, const std::string &what )
               : _type ( errorType), _message ( what ) 
      { }

      ~Exception() throw() {}

      virtual const char* what() const
        throw()
      {
        std::string msg( _type ) ;
        msg.append( " : " ) ;
        msg.append( _message ) ;

        return msg.c_str() ;
      }

    private :
      std::string _type;
      std::string _message;
  };

  class RejectReplace : public Exception
  {
    public :
      RejectReplace( const std::string &what )
        : Exception( "Reject Replace ", what )
      {}
  };

  class OrderError : public Exception
  {
    public :
      OrderError( const std::string &what )
        : Exception( "Order Error", what )
      {}
  };

  class ListIsEmpty : public Exception 
  {
    public :
      ListIsEmpty( )
        : Exception( "Error ", "List is empty" ) 
      {}
  };

  class OrderHasChanged : public Exception 
  {
    public :
      OrderHasChanged( )
        : Exception ( "Order Has Changed ", "Lost Priority" )
      {
      }
  };

  class OrderIdNotFound : public Exception 
  {
    public :
      OrderIdNotFound( const std::string &what )
        : Exception( "Cannot find order ", what )
      {}
  };

  class SecurityIdNotFound : public Exception 
  {
    public :
      SecurityIdNotFound ( const std::string &what )
        : Exception( "Cannot find securityId ", what )
      {}
  };

  class SideNotHandled : public Exception 
  {
    public :
      SideNotHandled( const std::string &what)
        : Exception( "Side not handled", what )
      {}
  };

  class OrderStatusNotHandled : public Exception 
  {
    public :
      OrderStatusNotHandled ( const std::string &what)
        : Exception( "Order Status Not handled", what )
      {}
  };

  class OrderTypeNotHandled : public Exception 
  {
    public :
      OrderTypeNotHandled( const std::string &what)
        : Exception( "Order Type Not Handled ", what )
      {}
  };

  class TimeInForceNotHandled : public Exception 
  {
    public :
      TimeInForceNotHandled( const std::string &what)
        : Exception( "TimeInForce Not Handled ", what )
      {}
  };
}

#endif // ESM_EXCEPTIONS_H

