#ifndef UT_CONVERTER_H
#define UT_CONVERTER_H

#include "types.h"

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <errno.h>



/*
#define STR_TO_INT16( VAL ) atoi( VAL.c_str() ) 
#define STR_TO_SHORT( VAL ) STR_TO_INT16( VAL )

#define STR_TO_INT32( VAL ) atoi( VAL.c_str() ) 
#define STR_TO_INT( VAL ) STR_TO_INT32( VAL )
#define STR_TO_LONG( VAL ) STR_TO_INT32( VAL )

#define STR_TO_INT64( VAL ) atol( VAL.c_str() ) 
#define STR_TO_LONGLONG( VAL ) STR_TO_INT64( VAL )

#define STR_TO_DOUBLE( VAL ) atof( VAL.c_str() ) 
#define STR_TO_FLOAT( VAL ) STR_TO_DOUBLE( VAL )

#define INT32_TO_STR( INT_VAL, STR_VAL ) \
    char cValue##INT_VALUE[20] ; \
    sprintf( cValue##INT_VALUE, "%d", INT_VAL ) ; \
    STR_VAL.assign( cValue##INT_VALUE )

#define INT64_TO_STR( INT_VAL, STR_VAL ) \
    char cValue##INT_VALUE[20] ; \
    sprintf( cValue##INT_VALUE, "%ld", INT_VAL ) ; \
    STR_VAL.assign( cValue##INT_VALUE )

// Need to find alternative solution here 
#define DOUBLE_TO_STR( DOUBLE_VAL, STR_VAL ) \
    LONGLONG longlongValue = DOUBLE_VAL ; \
    INT64_TO_STR( longlongValue, STR_VAL ) 
    */

namespace UT
{

  class IntConverter
  {
    public:

      static INT toInt16( const std::string &strValue ) {
        return atoi( strValue.c_str() ) ;
      }

      static INT toIntShort( const std::string &strValue ) {
        return atoi( strValue.c_str() ) ;
      }

      static INT toInt( const std::string &strValue ) {
        return atoi( strValue.c_str() ) ;
      }

      static INT toInt32( const std::string &strValue ) {
        return atoi( strValue.c_str() ) ;
      }

      static LONG toLong( const std::string &strValue ) {
        return atoi( strValue.c_str() ) ;
      }

      static LONGLONG toLongLong( const std::string &strValue ) {
        return toInt64( strValue ) ;
      }

      static ULONGLONG toULongLong( const std::string &strValue ) {
#if defined(WIN32)
        return _strtoui64( strValue.c_str(), NULL, 10 ) ;
#else
        return atol( strValue.c_str() ) ;
#endif
      }

      static LONGLONG toInt64( const std::string &strValue ) {
#if defined(WIN32)
        return _atoi64( strValue.c_str() ) ;
#else
        return atol( strValue.c_str() ) ;
#endif
      }

      static double toDouble( const std::string &strValue ) {
        return atof( strValue.c_str() ) ;
      }

      static double toFloat( const std::string &strValue ) {
        return atof( strValue.c_str() ) ;
      }
  };

  class StringConverter 
  {
    public:

      static void toString( LONG lValue, std::string &strValue )
      {
        char cValue[20] ;
        //sprintf( cValue, "%ld", lValue ) ;
        sprintf( cValue, "%d", lValue ) ;
        strValue.assign( cValue ) ;
      }

      static std::string toString( const LONG &lValue ) {
        std::string strValue ;
        toString( lValue, strValue ) ;
        return strValue ;
      }

      static void toString( LONGLONG lValue, std::string &strValue ) {
        char cValue[20] ;
#ifdef WIN32
        sprintf( cValue, "%lld", lValue ) ; // In windows ld = int32
#else
        sprintf( cValue, "%ld", lValue ) ; // Linux gives a warning on lld
#endif
        strValue.assign( cValue ) ;
      }

      static std::string toString( LONGLONG lValue ) {
        std::string strValue ;
        toString( lValue, strValue ) ;
        return strValue ;
      }
      
      static void toString( ULONGLONG lValue, std::string &strValue ) {
        char cValue[20] ;
        //sprintf( cValue, "%lld", lValue ) ;
        sprintf( cValue, "%llu", ( long long unsigned int ) lValue ) ;
        strValue.assign( cValue ) ;
      }

      static std::string toString( ULONGLONG lValue ) {
        std::string strValue ;
        toString( lValue, strValue ) ;
        return strValue ;
      }

      static void toString( double lValue, std::string &strValue )
      {
        toString( (LONGLONG) lValue, strValue ) ;
      }

      static std::string toString( double lValue ) {
        std::string strValue ;
        toString( lValue, strValue ) ;
        return strValue ;
      }

  };

}
#endif
