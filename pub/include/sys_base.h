#ifndef  _SYS_BASE_H
#define  _SYS_BASE_H

#include <stdlib.h>
#include <string.h>


#if	(!defined(TRUE) || (TRUE!=1))
#undef TRUE
#define TRUE    1
#endif

#if	(!defined(FALSE) || (FALSE!=0))
#undef FALSE
#define FALSE   0
#endif

#if	(!defined(YES) || (YES!=1))
#undef YES
#define YES     (BYTE)1
#endif

#if	(!defined(NO) || (NO!=0))
#undef NO
#define NO      (BYTE)0
#endif

#ifndef NULL
#define NULL ((void *)0)
#endif

/***********************************************************
 *                     全局数据类型                        *
***********************************************************/

typedef int              INT;
typedef char             CHAR;
typedef unsigned char    BYTE;
typedef signed   char    SBYTE;
typedef unsigned char    BOOLEAN;
typedef unsigned char    T_PAD;
typedef void*            LPVOID;
typedef int              SOCKET;
typedef unsigned short      WORD16;
typedef unsigned short      WORD;
typedef signed short        SWORD16;
typedef unsigned int        WORD32;
typedef signed int          SWORD32;
typedef unsigned long long  WORD64;
typedef long long           SWORD64;
typedef unsigned int        DWORD;
typedef int RESULT;
#define SUCCESS (BYTE)0
#define FAILURE (BYTE)0xff



typedef struct
{
    DWORD dwSCHNo;//���̺�
    DWORD dwDevID;//�豸���
}T_SCH_OPERID;


typedef struct
{
    T_SCH_OPERID tSender;
    T_SCH_OPERID tReceiver;
    WORD32 dwMsgID;
    WORD32 dwMsgLen;
    BYTE   byMsgType;
    BYTE   resever[3];
}T_SCH_Message_Head;

#endif