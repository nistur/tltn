#include "tltn_internal.h"

#include "util/stb.h"

#include <errno.h>

#define MAX(A, B) ( (A) > (B) ? (A) : (B) )

tltnReturn tltnListen(tltnContext** contextBase, tltnPort port)
{
    struct sockaddr_in address;
    
    TLTN_NULL_CHECK(contextBase, NO_CONTEXT);

    struct _tltnContext_posix* context = tltnMalloc(struct _tltnContext_posix);
    *contextBase = &context->m_Context;

    if(TLTN_FAILED(tltnClearContext(*contextBase)))
    {
	tltnReturn();
    }
    
    if( (context->m_ListeningSocket = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        tltnReturnCode(NO_SOCKET);
    }

    memset(&address, 0, sizeof(address));
    address.sin_family       = AF_INET;
    address.sin_addr.s_addr  = htonl(INADDR_ANY);
    address.sin_port         = htons(port);

    if(bind(context->m_ListeningSocket, (struct sockaddr*)&address, sizeof(address)) < 0)
    {
	tltnReturnCode(NO_SOCKET);
    }

    if(listen(context->m_ListeningSocket, 1024) < 0)
    {
	tltnReturnCode(NO_SOCKET);
    }

    FD_ZERO(&(context->m_Connections));
    FD_SET(context->m_ListeningSocket, &(context->m_Connections));
    context->m_MaxSocket = MAX(context->m_MaxSocket, context->m_ListeningSocket);
    
    tltnReturnCode(SUCCESS);
}

tltnReturn tltnStop(tltnContext* contextBase)
{
    struct _tltnContext_posix* context = (struct _tltnContext_posix*)contextBase;
    
    TLTN_NULL_CHECK(context, NO_CONTEXT);
    
    close(context->m_ListeningSocket);
    context->m_ListeningSocket = -1;
    
    tltnReturnCode(SUCCESS);
}

/* borrowed from beej */
void* get_in_addr(struct sockaddr* sa)
{
    if(sa->sa_family == AF_INET)
    {
	return &(((struct sockaddr_in*)sa)->sin_addr);
    }
    else
    {
	return &(((struct sockaddr_in6*)sa)->sin6_addr);
    }
}

tltnReturn tltnUpdate(tltnContext* contextBase)
{
    fd_set readfs;
    struct timeval tv;

    struct _tltnContext_posix* context = (struct _tltnContext_posix*)contextBase;
        
    TLTN_NULL_CHECK(context, NO_CONTEXT);

    tv.tv_sec = 0;
    tv.tv_usec = 5000;

    readfs = context->m_Connections;
    
    if(select(context->m_MaxSocket+1, &readfs, NULL, NULL, &tv) < 0 )
    {
	tltnReturnCode(NO_SOCKET);
    }

    if(FD_ISSET(context->m_ListeningSocket, &readfs))
    {
//	char remoteIP[INET6_ADDRSTRLEN];
	struct sockaddr_storage remoteaddr;
	socklen_t addrlen = sizeof(remoteaddr);
	int newfd = accept(context->m_ListeningSocket, (struct sockaddr*)&remoteaddr, &addrlen);
	if( newfd < 0 )
	{
	    tltnReturnCode(NO_SOCKET);
	}

	FD_SET(newfd, &(context->m_Connections));

	context->m_MaxSocket = MAX(context->m_MaxSocket, newfd);
	sbpush(context->m_ConnectionSockets, newfd);

	struct _tltnSession_posix session;
	session.m_SessionSocket = newfd;
	session.m_Context = context;
	
	contextBase->m_EventHandlers[TLTN_EVT_OPEN](&session.m_Session, "", 0);
    }

    if(context->m_ConnectionSockets)
    {
	for(int i = 0; i < sbcount(context->m_ConnectionSockets); ++i)
	{
	    if(FD_ISSET(context->m_ConnectionSockets[i], &readfs))
	    {
		char buffer[256];
		memset(buffer, 0, 256);
		int n = recv(context->m_ConnectionSockets[i], buffer, 256, 0);
		buffer[n] = 0;
		if( n > 0 )
		{
		    struct _tltnSession_posix session;
		    session.m_SessionSocket = context->m_ConnectionSockets[i];
		    contextBase->m_EventHandlers[TLTN_EVT_MSG](&session.m_Session, buffer, n);
		}
	    }
	}
    }
    
    tltnReturnCode(SUCCESS);
}

tltnReturn tltnSendMessage(tltnSession* sessionBase, tltnConstMsg message, tltnSize size)
{
    struct _tltnSession_posix* session = (struct _tltnSession_posix*)sessionBase;
    TLTN_NULL_CHECK(session, NO_CONTEXT);

    send(session->m_SessionSocket, message, size, 0);
    
    tltnReturnCode(SUCCESS);
}

tltnReturn tltnCloseSession(tltnSession* sessionBase)
{
    struct _tltnSession_posix* session = (struct _tltnSession_posix*)sessionBase;
    TLTN_NULL_CHECK(session, NO_CONTEXT);

    FD_CLR(session->m_SessionSocket, &session->m_Context->m_Connections);
    
    close(session->m_SessionSocket);
    
    tltnReturnCode(SUCCESS);
}
