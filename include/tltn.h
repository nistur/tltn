#pragma once
#ifndef __TEMPLATE_H__
#define __TEMPLATE_H__
#ifdef __cplusplus
extern "C" {
#endif/*__cplusplus*/

#ifdef TLTN_DYNAMIC
# ifdef WIN32
#  ifdef TLTN_BUILD
#   define TLTN_EXPORT __declspec( dllexport )
#  else
#   define TLTN_EXPORT __declspec( dllimport )
#  endif
# endif
#endif
 
#ifndef TLTN_EXPORT
# define TLTN_EXPORT
#endif

//typedef int tltnReturn;
typedef short int tltnPort;
typedef char* tltnStr;
typedef const tltnStr tltnConstStr;
    
typedef struct _tltnContext tltnContext;
typedef struct _tltnSession tltnSession;

typedef void(*tltnEventCb)(tltnSession* session, tltnConstStr message);

#ifdef TLTN_UNSAFE
typedef void tltnReturn;
#else/*TLTN_UNSAFE*/
typedef enum
{
    TLTN_SUCCESS,
    TLTN_NO_CONTEXT,
    TLTN_NO_SESSION,
    TLTN_NO_SOCKET,
} tltnReturn;
#endif/*TLTN_UNSAFE*/

typedef enum
{
    TLTN_EVT_OPEN,
    TLTN_EVT_MSG,
    TLTN_EVT_CLOSE,

    TLTN_EVT_MAX
} tltnEvent;

TLTN_EXPORT tltnReturn   tltnInitContext     (tltnContext** context, tltnPort port);
TLTN_EXPORT tltnReturn   tltnTerminateContext(tltnContext** context);

TLTN_EXPORT tltnReturn   tltnAddEventHandler (tltnContext* context, tltnEvent event, tltnEventCb handler);
TLTN_EXPORT tltnReturn   tltnSendEvent       (tltnSession* session, tltnEvent event, tltnConstStr message);
    
TLTN_EXPORT tltnReturn   tltnUpdate          (tltnContext* context);


#ifndef TLTN_UNSAFE
TLTN_EXPORT const char*  tltnError();
#endif/*TLTN_UNSAFE*/
    
#ifdef __cplusplus
}
#endif/*__cplusplus*/
#endif/*__TEMPLATE_H__*/
