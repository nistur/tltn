#include "tltn.h"

#include <string.h>

#define MSG(X) X, strlen(X)

#define PROMPT "tltn> "

#define EOT 0x04

void handleConnect(tltnSession* session, tltnConstMsg message, tltnSize size)
{
    tltnSendEvent(session, TLTN_EVT_MSG, MSG(PROMPT));
}

void handleMessage(tltnSession* session, tltnConstMsg message, tltnSize size)
{
    if(size == 1 && message[0] == EOT)
    {
	tltnSendEvent(session, TLTN_EVT_CLOSE, MSG("Bye\n"));
    }
    else
    {
	tltnSendEvent(session, TLTN_EVT_MSG, message, size);
	tltnSendEvent(session, TLTN_EVT_MSG, MSG(PROMPT));
    }
}

int main(int argc, char** argv)
{
    tltnContext* ctx;
    tltnInitContext(&ctx, 2323);

    tltnAddEventHandler(ctx, TLTN_EVT_OPEN, handleConnect);
    tltnAddEventHandler(ctx, TLTN_EVT_MSG, handleMessage);

    while(1)
    {
	tltnUpdate(ctx);
	//sleep(1);
    }

    tltnTerminateContext(&ctx);
}
