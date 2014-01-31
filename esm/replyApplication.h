#ifndef ESM_RESPONSE_APP_H
#define ESM_RESPONSE_APP_H

#include <boost/thread.hpp>
#include "order.h"

namespace ESM
{
  class ReplyApplication
  {
    public :
      virtual void sendNewConfirm( OrderPtr order ) = 0 ;
      virtual void sendReplaceConfirm( OrderPtr order ) = 0 ;
      virtual void sendCancelConfirm( OrderPtr order, const std::string &reason ) = 0 ;

      virtual void sendNewReject( OrderPtr order, const std::string &reason )= 0 ;
      virtual void sendReplaceReject( OrderPtr order, const std::string &reason )= 0 ;
      virtual void sendCancelReject( OrderPtr order, const std::string &reason )= 0 ;

      virtual void sendMarketToLimit( OrderPtr order ) = 0 ;
      virtual void sendTriggered( OrderPtr order ) = 0 ;
      virtual void sendFillConfirm( OrderPtr order ) = 0 ;
  };
};
#endif // ESM_RESPONSE_APP_H
