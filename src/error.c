#include "tltn.h"

#ifndef TLTN_UNSAFE
tltnReturn g_tltnError;
const char* g_tltnErrors[] = 
{
    "Success",
    "Null context",
    "Invalid session",
    "Error creating socket"
};
#endif/*TLTN_UNSAFE*/
