#include "tltn.h"

#include <unistd.h>

#define PROMPT "tltn>"

void handleConnect(tltnSession* session, tltnConstStr message)
{
    tltnSendEvent(session, TLTN_EVT_MSG, PROMPT);
}

void handleMessage(tltnSession* session, tltnConstStr message)
{
    tltnSendEvent(session, TLTN_EVT_MSG, message);
    tltnSendEvent(session, TLTN_EVT_MSG, PROMPT);
}

int main(int argc, char** argv)
{
    tltnContext* ctx;
    tltnInitContext(&ctx, 23);

    tltnAddEventHandler(ctx, TLTN_EVT_OPEN, handleConnect);
    tltnAddEventHandler(ctx, TLTN_EVT_MSG, handleMessage);

    while(1)
    {
	tltnUpdate(ctx);
	sleep(1);
    }

    tltnTerminateContext(&ctx);
}
