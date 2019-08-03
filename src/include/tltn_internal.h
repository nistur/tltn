#pragma once
#ifndef __TLTN_INTERNAL_H__
#define __TLTN_INTERNAL_H__

#include "tltn.h"

struct _tltnContext
{
    tltnEventCb m_EventHandlers[TLTN_EVT_MAX];
};

struct _tltnSession
{
};

/***************************************
 * Network interface
 ***************************************/
tltnReturn tltnListen(tltnContext** context, tltnPort port);
tltnReturn tltnStop(tltnContext* context);
tltnReturn tltnSendMessage(tltnSession* session, tltnConstMsg message, tltnSize size);
tltnReturn tltnCloseSession(tltnSession* session);

tltnReturn tltnClearContext(tltnContext* context);
/***************************************
 * Some basic memory management wrappers
 ***************************************/
#include <stdlib.h>
#define tltnMalloc(x) (x*)malloc(sizeof(x))
#define tltnFree(x)   free(x)

/***************************************
 * Error handling
 ***************************************/
#ifdef TLTN_UNSAFE

# define tltnReturnCode(x) return
# define tltnReturn() return
# define TLTN_NULL_CHECK(val, ret) {}
# define TLTN_FAILED(fn)  0){} fn; if(0

#else/*TLTN_UNSAFE*/
extern tltnReturn  g_tltnError;
extern const char* g_tltnErrors[];
# define tltnReturnCode(x)	       		\
    {						\
	g_tltnError = TLTN_##x;			\
	return TLTN_##x;			\
    }

# define tltnReturn()				\
    {						\
	return g_tltnError;			\
    }


# define TLTN_NULL_CHECK(val, ret)		\
    {						\
	if(val == 0)				\
	{					\
	    tltnReturnCode(ret);		\
	}					\
    }

# define TLTN_FAILED(fn) (fn != TLTN_SUCCESS)
#endif/*TLTN_UNSAFE*/

#include "tltn_internal_posix.h"

#endif/*__TLTN_INTERNAL_H__*/
