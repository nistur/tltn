#include "tltn_internal.h"

tltnReturn tltnClearContext(tltnContext* context)
{
    tltnReturnCode(SUCCESS);
}

tltnReturn tltnInitContext(tltnContext** context, tltnPort port)
{
    TLTN_NULL_CHECK(context, NO_CONTEXT);
    
    *context = tltnMalloc(tltnContext);

    if(TLTN_FAILED(tltnClearContext(*context)) ||
	TLTN_FAILED(tltnListen(*context, port)))
    {
	   tltnTerminateContext(context);
	   tltnReturn();
    }
    
    tltnReturnCode(SUCCESS);
}

tltnReturn tltnTerminateContext(tltnContext** context)
{
    TLTN_NULL_CHECK(context, NO_CONTEXT);

    tltnFree(*context);
    *context = 0;
    tltnReturnCode(SUCCESS);
}

tltnReturn tltnAddEventHandler(tltnContext* context, tltnEvent event, tltnEventCb handler)
{
    TLTN_NULL_CHECK(context, NO_CONTEXT);
    
    tltnReturnCode(SUCCESS);
}

tltnReturn tltnSendEvent(tltnSession* session, tltnEvent event, tltnConstStr message)
{
    TLTN_NULL_CHECK(session, NO_SESSION);
    
    tltnReturnCode(SUCCESS);
}

tltnReturn tltnUpdate(tltnContext* context)
{
    TLTN_NULL_CHECK(context, NO_CONTEXT);

    tltnReturnCode(SUCCESS);
}

#ifndef TLTN_UNSAFE
const char* tltnError()
{
    return g_tltnErrors[g_tltnError];
}
#endif/*TLTN_UNSAFE*/
