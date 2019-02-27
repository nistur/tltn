#include "tltn_internal.h"

#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

tltnReturn tltnListen(tltnContext* context, tltnPort port)
{
    struct sockaddr_in address;
    
    TLTN_NULL_CHECK(context, NO_CONTEXT);

    if( (context->m_ListeningSocket = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        tltnReturnCode(NO_SOCKET);
    }

    memset(&address, 0, sizeof(address));
    address.sin_family       = AF_INET;
    address.sin_addr.s_addr  = htonl(INADDR_ANY);
    address.sin_port         = htons(port);
    tltnReturnCode(SUCCESS);

    if(bind(context->m_ListeningSocket, (struct sockaddr*)&address, sizeof(address)) < 0)
    {
	tltnReturnCode(NO_SOCKET);
    }

    if(listen(context->m_ListeningSocket, 1024) < 0)
    {
	tltnReturnCode(NO_SOCKET);
    }

    tltnReturnCode(SUCCESS);
}
