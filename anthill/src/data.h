#include "defs.h"

#ifndef _extern
#define _extern extern
#endif

_extern FILE *Infile;
_extern FILE *Outfile;

_extern int Token;
_extern char Text[TEXTLEN+1];
_extern int Value;
_extern int Line;
_extern int Errors;
_extern int Syntoken;
_extern int Putback;
_extern int Rejected;
_extern int Rejval;
_extern char Rejtext[TEXTLEN+1];

_extern char *File;
_extern char *Basefile;

_extern char *Macp[MAXNMAC];
_extern int Macc[MAXNMAC];
_extern int Mp;
_extern int Expandmac;

_extern int Ifdefstk[MAXIFDEF], Isp;
_extern int Inclev;

_extern int Textseg;

_extern char *Names[NSYMBOLS];
_extern char Prims [NSYMBOLS];
_extern char Types [NSYMBOLS];
_extern char Stcls [NSYMBOLS];
_extern int Sizes [NSYMBOLS];
_extern int Vals [NSYMBOLS];
_extern char *Mtext[NSYMBOLS];

_extern int Globs;
_extern int Locs;

_extern int Thisfn;

_extern char Nlist[POOLSIZE];
_extern int Nbot;
_extern int Ntop;

_extern char Nlist[POOLSIZE];
_extern int Nbot;
_extern int Ntop;



_extern int Breakstk[MAXBREAK], Bsp;
_extern int Contstk[MAXBREAK], Csp;
_extern int Retlab;

_extern int LIaddr[MAXLOCINIT];
_extern int LIval[MAXLOCINIT];
_extern int Nli;

_extern char *Files[MAXFILES];
_extern int Nf;

_extern int O_verbose;
_extern int O_componly;
_extern int O_asmonly;
_extern int O_testonly;
_extern char *O_outfile;
_extern int O_debug;