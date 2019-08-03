#pragma once
#ifndef __TLTN_INTERNAL_POSIX_H__
#define __TLTN_INTERNAL_POSIX_H__

#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdlib.h>

/***************************************
 * Library context
 * - holds current state
 ***************************************/
struct _tltnContext_posix
{
    struct _tltnContext m_Context;
    int m_ListeningSocket;
    fd_set m_Connections;
    int* m_ConnectionSockets;
    int m_MaxSocket;
};

struct _tltnSession_posix
{
    struct _tltnSession m_Session;

    int m_SessionSocket;
};

#endif/*__TLTN_INTERNAL_POSIX_H__*/

