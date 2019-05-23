#include "tltn_internal.h"

#include <stdio.h>

tltnReturn tltnClearContext(tltnContext* context)
{
    tltnReturnCode(SUCCESS);
}

tltnReturn tltnInitContext(tltnContext** context, tltnPort port)
{
    TLTN_NULL_CHECK(context, NO_CONTEXT);

    if(TLTN_FAILED(tltnListen(context, port)))
    {
	   tltnTerminateContext(context);
	   tltnReturn();
    }
    
    tltnReturnCode(SUCCESS);
}

tltnReturn tltnTerminateContext(tltnContext** context)
{
    TLTN_NULL_CHECK(context, NO_CONTEXT);

    if(TLTN_FAILED(tltnStop(*context)))
    {
	tltnReturn();
    }
    
    tltnFree(*context);
    *context = 0;
    tltnReturnCode(SUCCESS);
}

tltnReturn tltnAddEventHandler(tltnContext* context, tltnEvent event, tltnEventCb handler)
{
    TLTN_NULL_CHECK(context, NO_CONTEXT);

    context->m_EventHandlers[event] = handler;
    
    tltnReturnCode(SUCCESS);
}

tltnReturn tltnSendEvent(tltnSession* session, tltnEvent event, tltnConstStr message)
{
    TLTN_NULL_CHECK(session, NO_SESSION);

    if( event == TLTN_EVT_MSG )
    {
	if( TLTN_FAILED(tltnSendMessage(session, message)) )
	{
	    tltnReturn();
	}
    }	
	
    
    tltnReturnCode(SUCCESS);
}

#ifndef TLTN_UNSAFE
const char* tltnError()
{
    return g_tltnErrors[g_tltnError];
}
#endif/*TLTN_UNSAFE*/
