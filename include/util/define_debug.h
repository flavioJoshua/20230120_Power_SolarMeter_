//#include <Arduino.h>
#ifndef define_Debug_H
    #define define_Debug_H
#endif



//////////////////////////////////////////
/// TODO: per fare il debug su una porta di rete invece che su Serial parte non implementata T
#ifdef UTIL_DEBUG_PORT
  #define UTIL_PRINT_DBG_PORT      UTIL_DEBUG_PORT
#else
///definizione alias per Serial 
  #define UTIL_PRINT_DBG_PORT      Serial
#endif

//////////////////////////////////////////

// Change _UTIL_LOGLEVEL_ to set tracing and logging verbosity
// 0: DISABLED: no logging
// 1: ERROR: errors
// 2: WARN: errors and warnings
// 3: INFO: errors, warnings and informational (default)
// 4: DEBUG: errors, warnings, informational and debug

#ifndef _UTIL_LOGLEVEL_
  #define _UTIL_LOGLEVEL_       0
#endif

//////////////////////////////////////////

const char WM_MARK[] = "Util:  ";
const char WM_SP[]   = " ";

#define UTIL_PRINT        UTIL_PRINT_DBG_PORT.print
#define UTIL_PRINTLN      UTIL_PRINT_DBG_PORT.println

#define WM_PRINT_MARK   UTIL_PRINT(WM_MARK)
#define WM_PRINT_SP     UTIL_PRINT(WM_SP)

////////////////////////////////////////////////////

/// Log Util
#define LOGERROR(x)         if(_UTIL_LOGLEVEL_>0) { WM_PRINT_MARK; UTIL_PRINTLN(x); }
#define LOGERROR0(x)        if(_UTIL_LOGLEVEL_>0) { UTIL_PRINT(x); }
#define LOGERROR1(x,y)      if(_UTIL_LOGLEVEL_>0) { WM_PRINT_MARK; UTIL_PRINT(x); WM_PRINT_SP; UTIL_PRINTLN(y); }
#define LOGERROR2(x,y,z)    if(_UTIL_LOGLEVEL_>0) { WM_PRINT_MARK; UTIL_PRINT(x); WM_PRINT_SP; UTIL_PRINT(y); WM_PRINT_SP; UTIL_PRINTLN(z); }
#define LOGERROR3(x,y,z,w)  if(_UTIL_LOGLEVEL_>0) { WM_PRINT_MARK; UTIL_PRINT(x); WM_PRINT_SP; UTIL_PRINT(y); WM_PRINT_SP; UTIL_PRINT(z); WM_PRINT_SP; UTIL_PRINTLN(w); }

////////////////////////////////////////////////////

#define LOGWARN(x)          if(_UTIL_LOGLEVEL_>1) { WM_PRINT_MARK; UTIL_PRINTLN(x); }
#define LOGWARN0(x)         if(_UTIL_LOGLEVEL_>1) { UTIL_PRINT(x); }
#define LOGWARN1(x,y)       if(_UTIL_LOGLEVEL_>1) { WM_PRINT_MARK; UTIL_PRINT(x); WM_PRINT_SP; UTIL_PRINTLN(y); }
#define LOGWARN2(x,y,z)     if(_UTIL_LOGLEVEL_>1) { WM_PRINT_MARK; UTIL_PRINT(x); WM_PRINT_SP; UTIL_PRINT(y); WM_PRINT_SP; UTIL_PRINTLN(z); }
#define LOGWARN3(x,y,z,w)   if(_UTIL_LOGLEVEL_>1) { WM_PRINT_MARK; UTIL_PRINT(x); WM_PRINT_SP; UTIL_PRINT(y); WM_PRINT_SP; UTIL_PRINT(z); WM_PRINT_SP; UTIL_PRINTLN(w); }

////////////////////////////////////////////////////

#define LOGINFO(x)          if(_UTIL_LOGLEVEL_>2) { WM_PRINT_MARK; UTIL_PRINTLN(x); }
#define LOGINFO0(x)         if(_UTIL_LOGLEVEL_>2) { UTIL_PRINT(x); }
#define LOGINFO1(x,y)       if(_UTIL_LOGLEVEL_>2) { WM_PRINT_MARK; UTIL_PRINT(x); WM_PRINT_SP; UTIL_PRINTLN(y); }
#define LOGINFO2(x,y,z)     if(_UTIL_LOGLEVEL_>2) { WM_PRINT_MARK; UTIL_PRINT(x); WM_PRINT_SP; UTIL_PRINT(y); WM_PRINT_SP; UTIL_PRINTLN(z); }
#define LOGINFO3(x,y,z,w)   if(_UTIL_LOGLEVEL_>2) { WM_PRINT_MARK; UTIL_PRINT(x); WM_PRINT_SP; UTIL_PRINT(y); WM_PRINT_SP; UTIL_PRINT(z); WM_PRINT_SP; UTIL_PRINTLN(w); }

////////////////////////////////////////////////////

#define LOGDEBUG(x)         if(_UTIL_LOGLEVEL_>3) { WM_PRINT_MARK; UTIL_PRINTLN(x); }
#define LOGDEBUG0(x)        if(_UTIL_LOGLEVEL_>3) { UTIL_PRINT(x); }
#define LOGDEBUG1(x,y)      if(_UTIL_LOGLEVEL_>3) { WM_PRINT_MARK; UTIL_PRINT(x); WM_PRINT_SP; UTIL_PRINTLN(y); }
#define LOGDEBUG2(x,y,z)    if(_UTIL_LOGLEVEL_>3) { WM_PRINT_MARK; UTIL_PRINT(x); WM_PRINT_SP; UTIL_PRINT(y); WM_PRINT_SP; UTIL_PRINTLN(z); }
#define LOGDEBUG3(x,y,z,w)  if(_UTIL_LOGLEVEL_>3) { WM_PRINT_MARK; UTIL_PRINT(x); WM_PRINT_SP; UTIL_PRINT(y); WM_PRINT_SP; UTIL_PRINT(z); WM_PRINT_SP; UTIL_PRINTLN(w); }

////////////////////////////////////////////////////


///call    LOGERROR1(F("netMask ="), in_WM_STA_IPconfig._sta_static_sn);
