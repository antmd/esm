
#ifndef UT_DEFINES_FOR_CREATE_ENDIANLESS_H
#define UT_DEFINES_FOR_CREATE_ENDIANLESS_H

//#include <endian.h>
#include "converter.h"
#include "types.h"
#include "definesForString.h"

/****************************************************
* Create a Set Function For the field               *
****************************************************/
// Needed so that the size is dynamically taken from types.h
#define UT_DEFINE_SET_CONVERT_FROM_STRING_FINAL( NAME, TYPE, SIZE ) \
  public : \
  void set##NAME( const std::string &value ) { \
    set##NAME( UT::IntConverter::toInt##SIZE( value )) ; }

#define UT_DEFINE_SET_CONVERT_FROM_STRING( NAME, TYPE, SIZE ) \
  UT_DEFINE_SET_CONVERT_FROM_STRING_FINAL( NAME, TYPE, SIZE )

/****************************************************
*  Defines for creating field                       *
****************************************************/
#define UT_CREATE_FIELD( NAME, TYPE ) \
  public : UT::TYPE get##NAME() const {  return _##NAME ; } \
  public : UT::TYPE &getRef##NAME() {  return _##NAME ; } \
  public : void set##NAME( UT::TYPE value ) { _##NAME = value ; } \
  UT_DEFINE_SET_CONVERT_FROM_STRING( NAME, TYPE, UT_##TYPE##_SIZE  ) \
  private : UT::TYPE _##NAME 

#define UT_CREATE_LONG( NAME ) \
  UT_CREATE_FIELD( NAME, LONG )

#define UT_CREATE_SHORT( NAME ) \
  UT_CREATE_FIELD( NAME, SHORT )

#define UT_CREATE_INT( NAME ) \
  UT_CREATE_FIELD( NAME, INT )

#define UT_CREATE_UINT( NAME ) \
  UT_CREATE_FIELD( NAME, UINT )

#define UT_CREATE_LONGLONG( NAME ) \
  UT_CREATE_FIELD( NAME, LONGLONG )

#define UT_CREATE_ULONGLONG( NAME ) \
  UT_CREATE_FIELD( NAME, ULONGLONG )

#define UT_CREATE_DOUBLE( NAME ) \
  public : double get##NAME() const { return _##NAME.value ; } \
  public : void set##NAME( double value ) { _##NAME.value = value ; } \
  public : void set##NAME( const std::string &value ) { _##NAME.value = UT::IntConverter::toDouble( value ) ; } \
  private: DOUBLE _##NAME 

/*
#define UT_CREATE_PRICE( NAME ) \
  UT_CREATE_FIELD( NAME, PRICE )
  */
#define UT_CREATE_PRICE( NAME ) \
  UT_CREATE_DOUBLE( NAME )

#endif
