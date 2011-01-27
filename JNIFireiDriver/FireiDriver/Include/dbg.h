
#ifndef _DBG_H
#define _DBG_H

#include <stdarg.h>

#ifdef __cplusplus
extern "C" {
#endif

void FaPrintf(char *format, ...);
void FaPrintfMsg(char *format, ...);

#define KdPrintMsg(a)  FaPrintfMsg a

#if defined(_DEBUG)
#define KdPrintTale(a)  FaPrintf a
#else
#define KdPrintTale(a)  (void *)0
#endif

char *inform(char *fmt, ...);
char *DDErrorString(HRESULT a_hResult);

#ifdef DBG_MSG_PREFIX
#undef DBG_MSG_PREFIX 
#endif
#define DBG_MSG_PREFIX "Fire-I"

#ifdef __cplusplus
}
#endif

#endif // _DBG_H
