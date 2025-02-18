#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define PREFIX 'C'
#define LPREFIX 'L'
#ifndef SCCDIR
#define SCCDIR "."
#endif
#define ASCMD "as -o %s %s"
#define LDCMD "ld -o %s %s/lib/crt0.o"
#define SCCLIBC "%s/lib/libscc.a"
#define SYSLIBC "/usr/lib/libc.a"
#define INTSIZE 2
#define PTRSIZE INTSIZE
#define CHARSIZE 1
#define CHAROFF 0
#define TEXTLEN 729
#define NAMELEN 27
#define MAXFILES 27
#define MAXIFDEF 27
#define MAXNMAC 27
#define MAXCASE 243
#define MAXBREAK 27
#define MAXLOCINIT 27
#define MAXFNARGS 27
#define NSYMBOLS 729
#define POOLSIZE 6561
#define TVARIABLE 1
#define TARRAY 2
#define TFUNCTION 3
#define TCONSTANT 4
#define TMACRO 5
#define PCHAR 1 /* char */
#define PINT 2 /* int */
#define CHARPTR 3 /* char * */
#define INTPTR 4 /* int * */
#define CHARPP 5 /* char ** */
#define INTPP 6 /* int ** */
#define PVOID 7 /* void */
#define VOIDPTR 8 /* void * */
#define VOIDPP 9 /* void ** */
#define FUNPTR 10 /* int (*)() */
#define CPUBLIC 1
#define CEXTERN 2
#define CSTATIC 3
#define CLSTATC 4
#define CAUTO 5
#define LVSYM 0
#define LVPRIM 1
#define LV 2
#define D_LSYM 1
#define D_GSYM 2
#define D_STAT 4

enum {
    SLASH, STAR, MOD, PLUS, MINUS, LSHIFT, RSHIFT,
    GREATER, GTEQ, LESS, LTEQ, EQUAL, NOTEQ, AMPER,
    CARET, PIPE, LOGAND, LOGOR,
    __ARGC, ASAND, ASXOR, ASLSHIFT, ASMINUS, ASMOD, ASOR,
    ASPLUS, ASRSHIFT, ASDIV, ASMUL, ASSIGN, BREAK, CASE,
    CHAR, COLON, COMMA, CONTINUE, DECR, DEFAULT, DO,
    ELLIPSIS, ELSE, ENUM, EXTERN, FOR, IDENT, IF, INCR,
    INT, INTLIT, LBRACE, LBRACK, LPAREN, NOT, QMARK,
    RBRACE, RBRACK, RETURN, RPAREN, SEMI, SIZEOF, STATIC,
    STRLIT, SWITCH, TILDE, VOID, WHILE, XEOF, XMARK,
    P_INCLUDE, P_DEFINE, P_ENDIF, P_ELSE, P_ELSENOT,
    P_IFDEF, P_IFNDEF, P_UNDEF
    };

