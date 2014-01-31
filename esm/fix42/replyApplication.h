#ifndef ESM_NSE_REPLY_APPLICATION_H
#define ESM_NSE_REPLY_APPLICATION_H

#include "../replyApplication.h"

namespace ESM { namespace NSE
{
  class ReplyApplication
    : public ESM::ReplyApplication
  {
    public :
      void sendNewConfirm( OrderPtr order ) ;
      void sendReplaceConfirm( OrderPtr order ) ;
      void sendCancelConfirm( OrderPtr order, const std::string &reason ) ;

      void sendNewReject( OrderPtr order, const std::string &reason );
      void sendReplaceReject( OrderPtr order, const std::string &reason );
      void sendCancelReject( OrderPtr order, const std::string &reason );

      void sendMarketToLimit( OrderPtr order ) ;
      void sendTriggered( OrderPtr order ) ;
      void sendFillConfirm( OrderPtr order ) ;
  };
}}
#endif // ESM_NSE_REPLY_APPLICATION_H
