// make #if conditions spanning files a warning...
// also unbalanced #endif statements....
#ifndef __GCC__
//#include <conio.h>
#endif
#if defined( _WIN32 )
 // getmodulefilename
#include <windows.h>
#include <direct.h>
#endif
#include <stdio.h>
#include <stdlib.h>
#ifndef FILEIO_DEFINED
#define FILEIO_DEFINED
#ifndef TEXT_SUPPORT
#define TEXT_SUPPORT
#include <string.h>
#ifndef MY_TYPES_INCLUDED
#define MY_TYPES_INCLUDED
#include <ctype.h>
#ifdef __LINUX__
#define DebugBreak() asm( WIDE("int $3\n") )
#else
#define DebugBreak()
#endif
#ifdef __WATCOMC__
#define CPROC _cdecl
#else
#define CPROC
#endif
#ifdef _MSC_VER
#define LONGEST_INT __int64
#else
#define LONGEST_INT long long
#endif
#define LONGEST_FLT double
// this is for passing FILE, LINE information to allocate
// useful during DEBUG phases only...
#ifdef _DEBUG
#define DBG_SRC         , __FILE__, __LINE__
#define DBG_VOIDSRC     __FILE__, __LINE__
#define DBG_VOIDPASS    char *pFile, int nLine
#define DBG_PASS        , char *pFile, int nLine
#define DBG_RELAY       , pFile, nLine
#define DBG_FORWARD     , pFile, nLine
#define DBG_FILELINEFMT "%s(%d)"
#else
#define DBG_SRC
#define DBG_VOIDSRC
#define DBG_VOIDPASS    void
#define DBG_PASS
#define DBG_RELAY
#define DBG_FORWARD     , __FILE__, __LINE__
#define DBG_FILELINEFMT
#endif
#ifdef UNICODE
#error unicode not defined.
#else
#define WIDE(s)  s
#endif
#ifndef FALSE
#define FALSE 0
#endif
#ifndef TRUE
#define TRUE (!FALSE)
#endif
//typedef void           _0;
typedef void *P_0;
#include <stdint.h>
/*
 refactors out - no more _xx types.
typedef unsigned char  uint8_t;
typedef uint8_t *uint8_t*;
typedef unsigned short uint16_t;
typedef uint16_t *uint16_t*;
typedef unsigned long  uint32_t;
typedef uint32_t *uint32_t*;
typedef signed   char  int8_t;
typedef signed   short int16_t;
typedef signed   long  int32_t;
*/
typedef const unsigned char *CTEXTSTR;
typedef unsigned char TEXTCHAR;
typedef TEXTCHAR *TEXTSTR;
#ifdef _WIN32
#ifndef CALLBACK
//#pragma message ("Setting CALLBACK to __stcall" )
#define CALLBACK    __stdcall
#endif
#else
#ifndef CALLBACK
//#pragma message ("Setting CALLBACK to c call" )
#define CALLBACK
#endif
#endif
//#define SOCKADDR    sockaddr
typedef size_t   INDEX;
#define INVALID_INDEX ((size_t)-1)
typedef void  *POINTER;
typedef const void *CPOINTER;
typedef uint32_t LOGICAL;
//typedef uint32_t uintptr_t;
#ifndef FALSE
#define FALSE 0
#endif
#ifndef TRUE
#define TRUE (!FALSE)
#endif
#define DECLDATA(name,sz) struct {uintptr_t size; uint8_t data[sz];} name
typedef struct DataBlock {
     // size is sometimes a pointer value...
   uintptr_t size;
                 // this means bad thing when we change platforms...
 // beginning of var data - this is created size+sizeof(VPA)
   uint8_t  data[1];
} DATA, *PDATA;
typedef struct LinkBlock
{
   size_t     Cnt;
   uint32_t     Lock;
   POINTER pNode[1];
} LIST, *PLIST;
typedef struct DataListBlock
{
	size_t     Cnt;
   size_t     Size;
   uint8_t      data[1];
} DATALIST, *PDATALIST;
typedef struct LinkStack
{
	size_t     Top;
   size_t     Cnt;
   POINTER pNode[1];
} LINKSTACK, *PLINKSTACK;
typedef struct DataListStack
{
 // next avail...
	size_t     Top;
	size_t     Cnt;
	size_t     Size;
   uint8_t      data[1];
} DATASTACK, *PDATASTACK;
typedef struct LinkQueue
{
   size_t     Top;
   size_t     Bottom;
   size_t     Cnt;
  // thread interlock using InterlockedExchange semaphore
   uint32_t     Lock;
 // need two to have distinct empty/full conditions
   POINTER pNode[2];
} LINKQUEUE, *PLINKQUEUE;
 // additional step function...
typedef struct LinkStackQueue
{
	size_t     Top;
   size_t     Bottom;
   size_t     Next;
   size_t     Cnt;
 // need two to have distinct empty/full conditions
   POINTER pNode[2];
} LINKSTACKQUEUE, *PLINKSTACKQUEUE;
//#undef NULL
//#define NULL ((BYTE FAR *)0)
#endif
#define DEFAULT_COLOR 0xF7
 // this does not change the color....
#define PRIOR_COLOR 0xF6
typedef struct format_info_tag
{
 // for restoration of spaces in strings?
	int spaces;
	int tabs;
} FORMAT, *PFORMAT;
   // declared in program data.... do NOT release
#define TF_STATIC    0x00000001
   // data field extually points at PTEXT
#define TF_INDIRECT  0x00000002
   // on release release indrect also...
#define TF_DEEP      0x00000004
  // don't expand - define substitution handling...
#define TF_NOEXPAND  0x00010000
// these values used originally for ODBC query construction....
// these values are flags stored on the indirect following a value
// label...
// flag combinatoin which represents actual data is present even with 0 size
#define IS_DATA_FLAGS (0)
#define DECLTEXTSZ( name, size ) struct {    uint32_t flags;    struct text_segment_tag *Next, *Prior;    FORMAT format;    DECLDATA(data, size); } name
typedef struct text_segment_tag
{
  // then here I could overlap with pEnt .bshadow, bmacro, btext ?
	uint32_t flags;
	struct text_segment_tag *Next, *Prior;
 // valid if TF_FORMAT is set...
	FORMAT format;
 // must be last since var character data is included
	DATA data;
} TEXT, *PTEXT;
#define DEFTEXT(str) {TF_STATIC,NULL,NULL,{0},{sizeof(str)-1,str}}
#define DECLTEXT(name, str) static DECLTEXTSZ( name, sizeof(str) ) = DEFTEXT(str)
extern TEXT newline;
//#define SETPRIORLINE(line,p) SetPriorLineEx( line, p DBG_SRC )
//#define SETNEXTLINE(line,p)  SetNextLineEx( line, p DBG_SRC )
#define SETPRIORLINE(line,p) ((line)?(((line)->Prior) = (PTEXT)(p)):0)
#define SETNEXTLINE(line,p)  ((line)?(((line)->Next ) = (PTEXT)(p)):0)
#define NEXTLINE(line)   ((PTEXT)(((PTEXT)line)?(((PTEXT)line)->Next):(NULL)))
#define PRIORLINE(line)  ((PTEXT)(((PTEXT)line)?(((PTEXT)line)->Prior):(NULL)))
#define SetStart(line)   do { PTEXT tmp;  for(; line && (tmp=PRIORLINE(line));line=tmp); } while(0)
#define SetEnd(line)    do { PTEXT tmp;  for(; line && (tmp=NEXTLINE(line)); line=tmp); } while (0)
// might also check to see if pseg is an indirect - setting this size would be BAD
#define SetTextSize(pseg, sz ) ((pseg)?((pseg)->data.size = (sz )):0)
PTEXT GetIndirect(PTEXT segment );
int GetTextFlags( PTEXT segment );
INDEX GetTextSize( PTEXT segment );
char *GetTextEx( PTEXT segment );
#define GetText(seg) ((seg)?((seg)->flags&TF_INDIRECT)?GetTextEx(seg):(char*)((PTEXT)(seg))->data.data:(char*)NULL)
#define SetIndirect(Seg,Where)  ( (Seg)->data.size = (int)(Where) )
#define SameText( l1, l2 )  ( strcmp( GetText(l1), GetText(l2) ) )
#ifdef _WIN32
#define strncasecmp strnicmp
#endif
#define LikeText( l1, l2 )  ( strncasecmp( GetText(l1), GetText(l2), ( (GetTextSize(l1)<GetTextSize(l2)) ?GetTextSize(l1):                                                                         GetTextSize(l2) ) ) )
#define TextIs(text,string) ( !stricmp( GetText(text), string ) )
#define TextLike(text,string) ( !stricmp( GetText(text), string ) )
PTEXT SegCreateEx( size_t nSize DBG_PASS );
#define SegCreate(s) SegCreateEx(s DBG_SRC)
PTEXT SegCreateFromTextEx( char *text DBG_PASS );
#define SegCreateFromText(t) SegCreateFromTextEx(t DBG_SRC)
PTEXT SegCreateIndirectEx( PTEXT pText DBG_PASS );
#define SegCreateIndirect(t) SegCreateIndirectEx(t DBG_SRC)
PTEXT SegDuplicateEx( PTEXT pText DBG_PASS);
#define SegDuplicate(pt) SegDuplicateEx( pt DBG_SRC )
PTEXT LineDuplicateEx( PTEXT pText DBG_PASS );
#define LineDuplicate(pt) LineDuplicateEx(pt DBG_SRC )
PTEXT TextDuplicateEx( PTEXT pText DBG_PASS );
#define TextDuplicate(pt) TextDuplicateEx(pt DBG_SRC )
PTEXT SegCreateFromIntEx( int value DBG_PASS );
#define SegCreateFromInt(v) SegCreateFromIntEx( v DBG_SRC )
PTEXT SegCreateFromFloatEx( float value DBG_PASS );
#define SegCreateFromFloat(v) SegCreateFromFloatEx( v DBG_SRC )
PTEXT SegAppend   ( PTEXT source, PTEXT other );
 // returns other instead of source
PTEXT SegAdd      (PTEXT source,PTEXT other);
PTEXT SegInsert   ( PTEXT what, PTEXT before );
  // add last node... blank space.
PTEXT SegExpandEx (PTEXT source, int nSize DBG_PASS );
#define SegExpand(s,n) SegExpandEx( s,n DBG_SRC );
void  LineReleaseEx (PTEXT *line DBG_PASS );
#define LineRelease(l) LineReleaseEx( &l DBG_SRC )
void SegReleaseEx( PTEXT seg DBG_PASS );
#define SegRelease(l) SegReleaseEx(l DBG_SRC )
PTEXT SegConcatEx   (PTEXT output,PTEXT input,int32_t offset,int32_t length DBG_PASS);
#define SegConcat(out,in,ofs,len) SegConcatEx(out,in,ofs,len DBG_SRC)
PTEXT SegUnlink   (PTEXT segment);
PTEXT SegBreak    (PTEXT segment);
 // removes seg from list, deletes seg.
PTEXT SegDeleteEx   (PTEXT *segment DBG_PASS);
#define SegDelete(s) SegDeleteEx(s DBG_SRC)
 // removes seg from list, returns seg.
PTEXT SegGrab     (PTEXT segment);
PTEXT SegSubst    ( PTEXT _this, PTEXT that );
PTEXT SegSubstRangeEx( PTEXT *_this, PTEXT end, PTEXT that DBG_PASS);
#define SegSubstRange(this,end,that) SegSubstRangeEx(this,end,that DBG_SRC)
PTEXT SegSplitEx( PTEXT *pLine, size_t nPos DBG_PASS);
#define SegSplit(line,pos) SegSplitEx( line, pos DBG_SRC )
size_t LineLength( PTEXT pt, int bSingle );
PTEXT BuildLineEx( PTEXT pt, int bSingle DBG_PASS );
#define BuildLine(from) BuildLineEx( from, FALSE DBG_SRC )
int CompareStrings( PTEXT pt1, int single1
                  , PTEXT pt2, int single2
                  , int bExact );
#define FORALLTEXT(start,var)  for(var=start;var; var=NEXTLINE(var))
//-----------------------------------------------------------------------
#define TYPELIB_PROC(t,n) t n
typedef struct vartext_tag {
	char *collect_text;
	INDEX collect_used;
	PTEXT collect;
	PTEXT commit;
} VARTEXT, *PVARTEXT;
TYPELIB_PROC( void, VarTextInitEx)( PVARTEXT pvt DBG_PASS);
#define VarTextInit(pvt) VarTextInitEx( (pvt) DBG_SRC )
TYPELIB_PROC( void, VarTextEmptyEx)( PVARTEXT pvt DBG_PASS);
#define VarTextEmpty(pvt) VarTextEmptyEx( (pvt) DBG_SRC )
TYPELIB_PROC( void, VarTextAddCharacterEx)( PVARTEXT pvt, char c DBG_PASS );
#define VarTextAddCharacter(pvt,c) VarTextAddCharacterEx( (pvt),(c) DBG_SRC )
// returns true if any data was added...
 // move any collected text to commit...
TYPELIB_PROC( PTEXT, VarTextEndEx)( PVARTEXT pvt DBG_PASS );
#define VarTextEnd(pvt) VarTextEndEx( (pvt) DBG_SRC )
TYPELIB_PROC( size_t, VarTextLength)( PVARTEXT pvt );
TYPELIB_PROC( PTEXT, VarTextGetEx)( PVARTEXT pvt DBG_PASS );
#define VarTextGet(pvt) VarTextGetEx( (pvt) DBG_SRC )
TYPELIB_PROC( void, VarTextExpandEx)( PVARTEXT pvt, int size DBG_PASS );
#define VarTextExpand(pvt, sz) VarTextExpandEx( (pvt), (sz) DBG_SRC )
//TYPELIB_PROC( int vtprintfEx( PVARTEXT pvt DBG_PASS, char *format, ... );
// note - don't include format - MUST have at least one parameter passed to ...
//#define vtprintf(pvt, ...) vtprintfEx( (pvt) DBG_SRC, __VA_ARGS__ )
TYPELIB_PROC( int, vtprintfEx)( PVARTEXT pvt, char *format, ... );
// note - don't include format - MUST have at least one parameter passed to ...
#define vtprintf vtprintfEx
#endif
#define __MAX_PATH__ 256
typedef struct file_tracking_tag
{
	int nLine;
 // if I use malloc this dynamic member failed ...
	char name[__MAX_PATH__];
 // if I use malloc this dynamic member failed ...
	char longname[__MAX_PATH__];
	FILE *file;
 // last line read...
	PTEXT line;
 // last line parsed
	PTEXT pParsed;
 // next token to be used...
	PTEXT pNextWord;
 // stack...
	struct file_tracking_tag *prior;
	struct file_dependancy_tag *pFileDep;
 // state remains multi-lines
	int  bBlockComment;
 // level of ifs started when this file is opened.
	int nIfLevel;
				  // -- state tracking per file --
				  /*
				  int nState;
				  int nIfLevels;  // count up and down always...
				  int nIfLevelElse; // what level to find the else on...
				  */
} FILETRACK, *PFILETRACK;
typedef struct file_dependancy_tag
{
	char full_name[__MAX_PATH__];
	char base_name[__MAX_PATH__];
	int bAllowMultipleInclude;
  // what file included this
	struct file_dependancy_tag *pDependedBy
 // first file this one depends on
		, *pDependsOn
  // next file which pDepended by depends on
		, *pAlso;
} FILEDEP, *PFILEDEP;
void SetCurrentPath( char *path );
uintptr_t OpenInputFile( char *basename, char *file );
uintptr_t OpenOutputFile( char *newfile );
uintptr_t OpenStdOutputFile( void );
uintptr_t OpenNewInputFile( char *basename, char *name, char *pFile, int nLine, int bDepend, int bNext );
void CloseInputFileEx( DBG_VOIDPASS );
#define CloseInputFile() CloseInputFileEx( DBG_VOIDSRC )
PFILEDEP AddFileDepend( PFILETRACK pft, char *basename, char *filename );
LOGICAL AlreadyLoaded( char *filename );
void SetIfBegin( void );
void ClearIfBegin( void );
void GetIfBegin( char **file, int *line );
FILE *GetCurrentOutput(void);
int GetCurrentLine( void );
char *GetCurrentFileName( void );
char *GetCurrentShortFileName( void );
void GetCurrentFileLine( char *name, int *line );
 // how many files deep we're processing
int CurrentFileDepth( void );
PTEXT GetCurrentWord( void );
PTEXT *GetCurrentTextLine( void );
PTEXT StepCurrentWord( void );
PTEXT GetNextWord( void );
void  SetCurrentWord( PTEXT word );
char *pathrchr( char *path );
PTEXT ReadLineEx( int Append DBG_PASS );
#define ReadLine(a) ReadLineEx(a DBG_SRC)
void WriteLineInfo( char *file, int line );
void WriteCurrentLineInfo( void );
void WriteLine( size_t len, char *line );
void DumpDepends( void );
void DestoyDepends( void );
char *pathrchr( char *path );
char *pathchr( char *path );
//---------- actually is args.c; but it's only the one function......
void ParseIntoArgs( char *lpCmdLine, int *pArgc, char ***pArgv );
#endif
#ifndef PPC_MEMORY_INTERFACE_DEFINED
#define PPC_MEMORY_INTERFACE_DEFINED
#if defined __WATCOMC__
//# include "sharemem.h"
#else
#ifndef MY_TYPES_INCLUDED
#define MY_TYPES_INCLUDED
#ifdef __LINUX__
#define DebugBreak() asm( WIDE("int $3\n") )
#else
#define DebugBreak()
#endif
#ifdef __WATCOMC__
#define CPROC _cdecl
#else
#define CPROC
#endif
#ifdef _MSC_VER
#define LONGEST_INT __int64
#else
#define LONGEST_INT long long
#endif
#define LONGEST_FLT double
// this is for passing FILE, LINE information to allocate
// useful during DEBUG phases only...
#ifdef _DEBUG
#define DBG_SRC         , __FILE__, __LINE__
#define DBG_VOIDSRC     __FILE__, __LINE__
#define DBG_VOIDPASS    char *pFile, int nLine
#define DBG_PASS        , char *pFile, int nLine
#define DBG_RELAY       , pFile, nLine
#define DBG_FORWARD     , pFile, nLine
#define DBG_FILELINEFMT "%s(%d)"
#else
#define DBG_SRC
#define DBG_VOIDSRC
#define DBG_VOIDPASS    void
#define DBG_PASS
#define DBG_RELAY
#define DBG_FORWARD     , __FILE__, __LINE__
#define DBG_FILELINEFMT
#endif
#ifdef UNICODE
#error unicode not defined.
#else
#define WIDE(s)  s
#endif
#ifndef FALSE
#define FALSE 0
#endif
#ifndef TRUE
#define TRUE (!FALSE)
#endif
//typedef void           _0;
typedef void *P_0;
/*
 refactors out - no more _xx types.
typedef unsigned char  uint8_t;
typedef uint8_t *uint8_t*;
typedef unsigned short uint16_t;
typedef uint16_t *uint16_t*;
typedef unsigned long  uint32_t;
typedef uint32_t *uint32_t*;
typedef signed   char  int8_t;
typedef signed   short int16_t;
typedef signed   long  int32_t;
*/
typedef const unsigned char *CTEXTSTR;
typedef unsigned char TEXTCHAR;
typedef TEXTCHAR *TEXTSTR;
#ifdef _WIN32
#ifndef CALLBACK
//#pragma message ("Setting CALLBACK to __stcall" )
#define CALLBACK    __stdcall
#endif
#else
#ifndef CALLBACK
//#pragma message ("Setting CALLBACK to c call" )
#define CALLBACK
#endif
#endif
//#define SOCKADDR    sockaddr
typedef size_t   INDEX;
#define INVALID_INDEX ((size_t)-1)
typedef void  *POINTER;
typedef const void *CPOINTER;
typedef uint32_t LOGICAL;
//typedef uint32_t uintptr_t;
#ifndef FALSE
#define FALSE 0
#endif
#ifndef TRUE
#define TRUE (!FALSE)
#endif
#define DECLDATA(name,sz) struct {uintptr_t size; uint8_t data[sz];} name
typedef struct DataBlock {
     // size is sometimes a pointer value...
   uintptr_t size;
                 // this means bad thing when we change platforms...
 // beginning of var data - this is created size+sizeof(VPA)
   uint8_t  data[1];
} DATA, *PDATA;
typedef struct LinkBlock
{
   size_t     Cnt;
   uint32_t     Lock;
   POINTER pNode[1];
} LIST, *PLIST;
typedef struct DataListBlock
{
	size_t     Cnt;
   size_t     Size;
   uint8_t      data[1];
} DATALIST, *PDATALIST;
typedef struct LinkStack
{
	size_t     Top;
   size_t     Cnt;
   POINTER pNode[1];
} LINKSTACK, *PLINKSTACK;
typedef struct DataListStack
{
 // next avail...
	size_t     Top;
	size_t     Cnt;
	size_t     Size;
   uint8_t      data[1];
} DATASTACK, *PDATASTACK;
typedef struct LinkQueue
{
   size_t     Top;
   size_t     Bottom;
   size_t     Cnt;
  // thread interlock using InterlockedExchange semaphore
   uint32_t     Lock;
 // need two to have distinct empty/full conditions
   POINTER pNode[2];
} LINKQUEUE, *PLINKQUEUE;
 // additional step function...
typedef struct LinkStackQueue
{
	size_t     Top;
   size_t     Bottom;
   size_t     Next;
   size_t     Cnt;
 // need two to have distinct empty/full conditions
   POINTER pNode[2];
} LINKSTACKQUEUE, *PLINKSTACKQUEUE;
//#undef NULL
//#define NULL ((BYTE FAR *)0)
#endif
void CPROC *AllocateEx( size_t nSize DBG_PASS );
# define Allocate(s) AllocateEx(s DBG_SRC)
void CPROC ReleaseExx( void ** DBG_PASS );
# if defined( __WATCOMC__ ) || defined( _MSC_VER )
#  ifdef _DEBUG
#   define ReleaseEx(p,f,l ) ReleaseExx( (void**)&p,f,l )
#  else
#   define ReleaseEx(p ) ReleaseExx( (void**)&p )
#  endif
# else
#  define ReleaseEx(... ) ReleaseExx( (void**)&__VA_ARGS__ )
# endif
#define Release(p) ReleaseExx( (void**)&p DBG_SRC)
void DumpMemory( void );
uint32_t CPROC LockedExchange( uint32_t *p, uint32_t val );
void CPROC MemSet( POINTER p, uint32_t v, size_t n);
void CPROC MemCpy( POINTER p, const void *p2, size_t n);
void DisableMemoryValidate( int bDisable );
char CPROC *StrDupEx( const char *original DBG_PASS );
#define StrDup(o) StrDupEx(o DBG_SRC )
#endif
#endif
#ifndef INPUT_DEFINED
#define INPUT_DEFINED
  // must be present just to process this
PTEXT burstEx( PTEXT input DBG_PASS );
#define burst(i) burstEx(i DBG_SRC )
PTEXT GatherLineEx( PTEXT *pOutput, int *pIndex, int bInsert, int bSaveCR, int bData, PTEXT pInput );
#define GatherLine( out,idx,ins,cr,in) GatherLineEx( (out),(idx),(ins),(cr),(FALSE),(in))
PTEXT get_line(FILE *source, int *line);
#endif
#ifndef LINKSTUFF
#define LINKSTUFF
//PDATA CreateData( uint32_t size );
//PDATA CreateDataFromText( char *pData );
//PDATA ExpandData( PDATA pData, uint32_t amount );
//PDATA DuplicateData( PDATA pData );
//void ReleaseData( PDATA pd );
PLIST       CreateListEx   ( DBG_VOIDPASS );
PLIST       DeleteListEx   ( PLIST *plist DBG_PASS );
PLIST       AddLinkEx      ( PLIST *pList, POINTER p DBG_PASS );
PLIST       SetLinkEx      ( PLIST *pList, INDEX idx, POINTER p DBG_PASS );
POINTER     GetLinkEx      ( PLIST *pList, INDEX idx );
INDEX       FindLink       ( PLIST *pList, POINTER value );
int         DeleteLinkEx   ( PLIST *pList, POINTER value );
#define CreateList()       ( CreateListEx( DBG_VOIDSRC ) )
#define DeleteList(p)      ( DeleteListEx( &(p) DBG_SRC ) )
#define AddLink(p,v)       ( AddLinkEx( &(p),v DBG_SRC ) )
#define SetLink(p,i,v)     ( SetLinkEx( &(p),i,v DBG_SRC ) )
#define GetLink(p,i)       ( GetLinkEx( &(p),i ) )
#define DeleteLink(p,v)    ( DeleteLinkEx( &(p), v ) )
#define FORALL( l, i, t, v ) if(l) for( (i)=0; (i) < ((l)->Cnt) &&                                          (((v)=(t)(l)->pNode[i]),1); (i)++ )  if( v )
 // sizeof data elements...
PDATASTACK  CreateDataStack( INDEX size );
void        DeleteDataStack( PDATASTACK *pds );
PDATASTACK  PushData       ( PDATASTACK *pds, POINTER pdata );
POINTER     PopData        ( PDATASTACK *pds );
 // keeps data on stack (can be used)
POINTER     PeekData       ( PDATASTACK *pds );
 // keeps data on stack (can be used)
POINTER     PeekDataEx     ( PDATASTACK *pds, int Item );
PLINKSTACK  CreateLinkStack( void );
void        DeleteLinkStack( PLINKSTACK pls );
PLINKSTACK  PushLink       ( PLINKSTACK pls, POINTER p );
#define PushLink(s,p)  ((s)=PushLink((s),(p)))
POINTER     PopLink        ( PLINKSTACK pls );
POINTER     PeekLink       ( PLINKSTACK pls );
PLINKQUEUE  CreateLinkQueue( void );
void        DeleteLinkQueueEx( PLINKQUEUE *pplq DBG_PASS );
#define     DeleteLinkQueue(pplq) DeleteLinkQueueEx( pplq DBG_SRC )
PLINKQUEUE  EnqueLinkEx    ( PLINKQUEUE *pplq, POINTER link DBG_PASS );
#define     EnqueLink(pplq, link) EnqueLinkEx( pplq, link DBG_SRC )
//PLINKQUEUE  EnqueLink      ( PLINKQUEUE *pplq, POINTER link );
POINTER     DequeLink      ( PLINKQUEUE *pplq );
int         IsQueueEmpty   ( PLINKQUEUE *pplq );
#endif
LONGEST_INT ProcessExpression( void );
typedef struct define_tag
{
	PTEXT pName;
 // DEFINE_FILE, COMMANDLINE, etc..
   int   nType;
 // list of parameter names
   PLIST pParams;
 // set if there was a ... parameter...
	int   bVarParams;
  // content which is to be substituted
   PTEXT pData;
  // set to avoid circular substitution
   int   bUsed;
   // file and line which originally made this define...
   char  pFile[__MAX_PATH__];
   int   nLine;
   struct define_tag *pLesser, *pGreater, *pSame, **me;
} DEF, *PDEF;
void InitDefines( void );
void DeinitDefines( void );
void CommitDefinesToCommandLine( void );
#define IGNORE_PARAMS 0x7fff
PDEF FindDefineName( PTEXT pName, int params );
#define DEFINE_ALL         0
#define DEFINE_COMMANDLINE 1
#define DEFINE_FILE        2
#define DEFINE_INTERNAL    3
void  DeleteDefine( PDEF *ppDef );
void  DeleteAllDefines( int type );
void  DefineDefine( char *name, char *value );
int   ProcessDefine( int type );
INDEX FindArg( PLIST pArgs, PTEXT pName );
void  EvalSubstitutions( PTEXT *subst, int more );
void FixQuoting( PTEXT test );
#define CPP_MAIN_SOURCE
#define stddbg g.dbgout
//stderr
#  if _MSC_VER > 1500
#    define mkdir _mkdir
#    define fileno _fileno
#    define stricmp _stricmp
#    define strdup _strdup
#  endif
typedef struct include_reference_tag {
	struct {
		uint32_t bMacros;
	} flags;
	char *name;
} INCLUDE_REF, *PINCLUDE_REF;
typedef struct global_tag
{
	struct {
		uint32_t do_trigraph : 1;
		uint32_t bWriteLine : 1;
		uint32_t bLineUsesLineKeyword : 1;
 // when -imacro is used...
		uint32_t bNoOutput : 1;
 // enable normally harmless warnings.
		uint32_t bAllWarnings : 1;
		uint32_t bEmitUnknownPragma : 1;
		uint32_t bForceBackslash : 1;
		uint32_t bForceForeslash : 1;
		uint32_t bStdout : 1;
		uint32_t keep_comments : 1;
		uint32_t keep_includes : 1;
		uint32_t bWriteLineInfo : 1;
		uint32_t load_once : 1;
// don't output system include headers
		uint32_t bSkipSystemIncludeOut : 1;
 // a status of the last processinclude
		uint32_t bIncludedLastFile : 1;
		uint32_t doing_system_file : 1;
		uint32_t skip_define_processing : 1;
		uint32_t skip_logic_processing : 1;
		uint32_t config_loaded : 1;
	} flags;
	FILE *output;
	int bDebugLog;
	char pExecPath[256];
	char pExecName[256];
   char pWorkPath[256];
   DECLTEXTSZ( pCurrentPath, 256 );
   uint32_t ErrorCount;
	/******************************/
 // list of paths to search includes for...
	PLIST pSysIncludePath;
	// the include path should have appended to it the default
	// system include file... this probably comes from an enviroment
	// environment will be an important thing to mimic in my operation
	// system...
	PLIST pUserIncludePath;
     // include 'system' dependancies
	int AllDependancies;
 // include 'system' dependancies
	int bAutoDepend;
	FILE *AutoDependFile;
 // safe junk buffer to print into...
	VARTEXT vt;
	unsigned char CurrentOutName[256];
	int nIfLevels;
	unsigned long nAllocates;
	unsigned long nReleases;
	size_t nAllocSize;
 // target name to reference when
	unsigned char AutoTargetName[256];
	                                   //building auto depend...
	PLINKSTACK pIncludeList;
	FILE *dbgout;
	PFILETRACK pAllFileStack;
	PFILETRACK pFileStack;
} GLOBAL;
// debug Log options....
#define DEBUG_SUBST 0x02
#define DEBUG_DEFINES 0x04
#define DEBUG_READING 0x08
#define DEBUG_MEMORY 0x10
#ifndef CPP_MAIN_SOURCE
extern
#endif
GLOBAL g;
void DumpSegs( PTEXT pOp );
// this module shall have provision to read a cpp.cnf
// which will indicate system include paths, and additional symbols
// which may be defined on a per-compiler basis....
#ifndef __GCC__
// this was good during development of infinite loops but bad in production...
// maybe ifdef _DEBUG the kbhit();
#define fprintf fprintf
#else
#define fprintf fprintf
#endif
#define ARG_UNKNOWN          0
#define ARG_INCLUDE_PATH     1
#define ARG_SYS_INCLUDE_PATH 2
#define ARG_AUTODEPEND_NAME  3
#define ARG_DEFINE_DEFINE    4
#define ARG_OUT_NAME         5
#define ARG_AUTOTARGET_NAME  6
#define ARG_INCLUDE_FILE     7
#define ARG_MACRO_FILE       8
#define ARG_GEN_STDOUT       9
/******************************
/* this portion is mainly for testing the CPP program
/* defines which are not used...
/* comments in various order
/* although these must succeed...
/******************************/
//----------------------------------------------------------------------
int KillQuotes( char *string )
{
	// this processing stage cannot be done at the pre-processor level
	// for things like "\x02" "4" which is actually
	// character to followed by ascii 4.
	//return strlen( string );
	// okay but yes it can be done for #pramga message
	// this routine removes leading and trailing quotes.
	// and only stores that which was within the quotes.
	char quote = 0;
	char *in = string, *out = string;
	if( !string )
		return 0;
	while( *string )
	{
		if( !quote )
		{
			if( *string == '\"' || *string == '\'' )
			{
				quote = *string;
			}
		}
		else
		{
			if( *string == quote )
			{
				quote = 0;
			}
			else
			{
				*out = *string;
				out++;
			}
		}
		string++;
	}
	*out = 0;
 // bad form - but in never changes so this is length out.
	return (int)(out - in);
}
//----------------------------------------------------------------------
int CollapseQuotes( char *string )
{
	// this routine takes "thing" "another" and makes "thinganother"
	// however "this" and "that" is still "this" and "that"
	char quote = 0, lastquote = 0, *lastquotepos = NULL;
	char *in = string, *out = string;
	if( !string )
		return 0;
	while( *string )
	{
		if( !quote )
		{
			if( lastquote == *string )
			{
				out = lastquotepos;
				quote = *string;
			}
			else
			{
				if( *string != ' ' && *string != '\t' )
				{
					lastquote = 0;
					lastquotepos = NULL;
				}
				if( *string == '\"' || *string == '\'' )
					quote = *string;
				*out = *string;
				out++;
			}
		}
		else
		{
			if( *string == quote )
			{
				lastquote = quote;
				lastquotepos = out;
				quote = 0;
			}
			*out = *string;
			out++;
		}
		string++;
	}
	*out = 0;
 // bad form - but in never changes so this is length out.
	return (int)(out - in);
}
//---------------------------------------------------------------------------
void DumpSegs( PTEXT pOp )
{
	PTEXT tmp = pOp;
	fprintf( stddbg, "SEG:%p", pOp );
	//if( !g.bDebugLog )
	//	return;
	while( tmp )
	{
		if( tmp->flags & TF_INDIRECT )
		{
			DumpSegs( GetIndirect( tmp ) );
		}
		else
		{
			fprintf( stddbg, WIDE("[%d%s]"), tmp->format.spaces,GetText( tmp ) );
		}
		tmp = NEXTLINE( tmp );
	}
}
//----------------------------------------------------------------------
int ProcessSystemIncludeFile( char *name, int bAllowAbsolute, int bNext )
{
	char Workname[__MAX_PATH__];
	PTEXT pPath;
	INDEX idx;
	if( bAllowAbsolute &&
		 OpenNewInputFile( name, name, GetCurrentFileName(), GetCurrentLine(), g.bAutoDepend, bNext ) )
		return TRUE;
	{
		FORALL( g.pUserIncludePath, idx, PTEXT, pPath )
		{
 // don't use auto path for 'system' includes.
			if( !idx )
				continue;
			sprintf( Workname, WIDE("%s/%s"), GetText( pPath ), name );
			if( g.bDebugLog )
			{
				fprintf( stddbg, WIDE("attempting <%s>\n") , Workname );
			}
			if( OpenNewInputFile( name, Workname, GetCurrentFileName(), GetCurrentLine(), TRUE, bNext ) )
			{
				if( idx )
					SetCurrentPath( GetText( pPath ) );
				return TRUE;
			}
		}
		FORALL( g.pSysIncludePath, idx, PTEXT, pPath )
		{
			sprintf( Workname, WIDE("%s/%s"), GetText( pPath ), name );
			if( g.bDebugLog )
			{
				fprintf( stddbg, WIDE("attempting <%s>\n") , Workname );
			}
			g.flags.doing_system_file = 1;
			if( OpenNewInputFile( name, Workname, GetCurrentFileName(), GetCurrentLine(), FALSE, bNext ) )
			{
				g.flags.doing_system_file = 0;
				SetCurrentPath( GetText( pPath ) );
				return TRUE;
			}
			g.flags.doing_system_file = 0;
		}
	}
	// at this point - offer to add another path...
	return FALSE;
}
//----------------------------------------------------------------------
int ProcessInclude( int bNext )
{
	char Workname[__MAX_PATH__];
	char basename[__MAX_PATH__];
	int i = 0, did_subst = 0;
	PTEXT pEnd, pWord;
	if( !( pEnd = pWord = GetCurrentWord() ) )
	{
		fprintf( stderr, WIDE("%s(%d) Error: #include without name.\n"), GetCurrentFileName(), GetCurrentLine() );
		g.ErrorCount++;
		return TRUE;
	}
	g.flags.bIncludedLastFile = 0;
	do
	{
		if( GetText( pWord )[0] == '\"' )
		{
			if( bNext )
			{
				fprintf( stderr, WIDE("Hmm warning : did not implement include next for 'user' headers.\n") );
				return FALSE;
			}
			pEnd = NEXTLINE( GetCurrentWord() );
			while( pEnd && GetText( pEnd )[0] != '\"' )
			{
				i += sprintf( basename + i, WIDE("%s"), GetText( pEnd ) );
				pEnd = NEXTLINE( pEnd );
			}
			basename[i] = 0;
			if( !pEnd )
			{
				fprintf( stderr, WIDE("%s(%d) Error: Invalid name end bounding for #include \"...\n")
						, GetCurrentFileName(), GetCurrentLine() );
				g.ErrorCount++;
				return TRUE;
			}
			strcpy( Workname, basename );
			if( g.bDebugLog )
			{
				fprintf( stddbg, WIDE("attempting: \"%s\"\n"), basename );
			}
			if( g.flags.load_once )
			{
				if( AlreadyLoaded( Workname ) ) {
					SetCurrentWord( NEXTLINE( pEnd ) );
					g.flags.bIncludedLastFile = 1;
					return TRUE;
				}
			}
			if( !OpenNewInputFile( basename, Workname, GetCurrentFileName(), GetCurrentLine(), g.bAutoDepend, bNext ) )
			{
				PTEXT pPath;
				INDEX idx;
				int count;
				char *dir = pathrchr( g.pFileStack->longname );
				if( dir )
					count = (int)(dir - g.pFileStack->longname);
				else
					count = 0;
#if( _MSC_VER && ( _MSC_VER < 1800 ) )
				_snprintf( Workname, __MAX_PATH__, WIDE( "%*.*s/%s" ), count, count, g.pFileStack->longname, basename );
#else
#if( _MSC_VER && ( _MSC_VER < 1800 ) )
				_snprintf( Workname, __MAX_PATH__, WIDE( "%*.*s/%s" ), count, count, g.pFileStack->longname, basename );
#else
				snprintf( Workname, __MAX_PATH__, WIDE( "%*.*s/%s" ), count, count, g.pFileStack->longname, basename );
#endif
#endif
				if( OpenNewInputFile( basename, Workname, GetCurrentFileName(), GetCurrentLine(), TRUE, bNext ) )
				{
					SetCurrentWord( NEXTLINE( pEnd ) );
					g.flags.bIncludedLastFile = 1;
					return TRUE;
				}
				FORALL( g.pUserIncludePath, idx, PTEXT, pPath )
				{
					sprintf( Workname, WIDE("%s/%s"), GetText( pPath ), basename );
					if( g.bDebugLog )
					{
						fprintf( stddbg, WIDE("attempting \"%s\"\n") , Workname );
					}
					/*1234*/
					if( g.flags.load_once )
					{
						if( AlreadyLoaded( Workname ) ) {
							SetCurrentWord( NEXTLINE( pEnd ) );
							g.flags.bIncludedLastFile = 1;
							return TRUE;
						}
					}
					if( OpenNewInputFile( basename, Workname, GetCurrentFileName(), GetCurrentLine(), TRUE, bNext ) )
					{
						if( idx )
							SetCurrentPath( GetText( pPath ) );
						g.flags.bIncludedLastFile = 1;
						return TRUE;
					}
				}
				fprintf( stderr, WIDE("%s(%d): Warning could not find include file \"%s\". try <%s>? I won't - but maybe...\n")
						, GetCurrentFileName()
						, GetCurrentLine()
						, basename, basename );
				return FALSE;
			}
			else
			{
				g.flags.bIncludedLastFile = 1;
				return TRUE;
			}
		}
		else if( GetText( pWord )[0] == '<' )
		{
			//PTEXT pPath;
			//INDEX idx;
			/*
			 if( GetText( GetCurrentWord() )[0] != '<' )
			 {
			 fprintf( stderr, WIDE("%s(%d) Error: Invalid name bounding for #INCLUDE %c\n")
			 , GetCurrentFileName(), GetCurrentLine()
			 , GetText( GetCurrentWord() )[0] );
			 g.ErrorCount++;
			 return TRUE;
			 }
			 */
			pEnd = NEXTLINE( pWord );
			while( pEnd && GetText( pEnd )[0] != '>' )
			{
				i += sprintf( basename + i, WIDE("%s"), GetText( pEnd ) );
				pEnd = NEXTLINE( pEnd );
			}
			basename[i] = 0;
			if( !pEnd )
			{
				fprintf( stderr, WIDE("%s(%d) Error: Invalid name end bounding for #INCLUDE <...\n")
						, GetCurrentFileName(), GetCurrentLine() );
				g.ErrorCount++;
				return TRUE;
			}
			if( g.flags.load_once )
			{
				if( AlreadyLoaded( basename ) ) {
					SetCurrentWord( NEXTLINE( pEnd ) );
					g.flags.bIncludedLastFile = 1;
					return TRUE;
				}
			}
			if( ProcessSystemIncludeFile( basename, FALSE, bNext ) ) {
				g.flags.bIncludedLastFile = 1;
				return TRUE;
			}
			break;
		}
		else
		{
			PTEXT pStart = pWord;
			EvalSubstitutions( &pWord, FALSE );
			if( pWord != pStart ) {
				SetCurrentWord( pWord );
			}
			else
				sprintf( basename, WIDE("%s"), GetText( pEnd ) );
			did_subst++;
		}
	} while( did_subst < 2 );
	if( g.flags.load_once )
	{
		AddFileDepend( g.pFileStack, basename, basename );
	}
	if( !g.flags.bSkipSystemIncludeOut )
		fprintf( stderr, WIDE("%s(%d) Warning could not process include file %c%s%c\n")
		       , GetCurrentFileName(), GetCurrentLine()
		       , (pEnd!= GetCurrentWord())?GetCurrentWord()->data.data[0]:' '
		       , basename
		       , (pEnd != GetCurrentWord()) ? pEnd->data.data[0] : ' '
		);
	//g.ErrorCount++;
	// at this point - offer to add another path...
	return FALSE;
}
//----------------------------------------------------------------------
// values for nState in FILETRACK
//#define CONTINUE_DEFINE	0x000002
// if a ELSE or ENDIF at level 0 is found...
// then this is satisfied... #if type statement increment if levels
// and endif decrements the levels....
#define FIND_ELSE			0x000008
// FIND_ENDIF ... statements between are ignored until ENDIF
// even #else and #elseif type
// although #if within this block may also have a paired ENDIF
// #if type statements will increment the if levels and
// #endif will decrement until level is 0 and is an end...
#define FIND_ENDIF		  0x000010
//----------------------------------------------------------------------
//----------------------------------------------------------------------
 // mark this for on close message....
static char *pFileIfStart;
static int nLineIfStart;
static int nState;
static int nIfLevelElse;
//----------------------------------------------------------------------
void SetIfBegin( void )
{
	g.nIfLevels++;
	if( g.bDebugLog )
		fprintf( stddbg, WIDE("%s(%d): Setting IF level %d finding %s%s\n")
				, GetCurrentFileName()
				, GetCurrentLine()
				, g.nIfLevels
				, nState & FIND_ELSE?"ELSE":""
				, nState & FIND_ENDIF?"ENDING":""
				 );
	if( !pFileIfStart )
	{
		if( g.bDebugLog )
			fprintf( stddbg, WIDE("Set if starting level: %d\n"), g.nIfLevels );
		pFileIfStart = StrDup( GetCurrentFileName() );
		nLineIfStart = GetCurrentLine();
	}
}
//----------------------------------------------------------------------
void ClearIfBegin( void )
{
	if( !g.nIfLevels )
	{
		fprintf( stddbg, WIDE("%s(%d): Extra #endif without an #if\n")
				 , GetCurrentFileName()
				 , GetCurrentLine() );
		return;
	}
	if( g.bDebugLog )
		fprintf( stddbg, WIDE("%s(%d): Clearing IF %d finding %s%s\n")
					, GetCurrentFileName()
					, GetCurrentLine()
					, g.nIfLevels
					, nState & FIND_ELSE?"ELSE":""
					, nState & FIND_ENDIF?"ENDING":""
					);
	g.nIfLevels--;
	if( !g.nIfLevels )
	{
		//fprintf( stderr, WIDE("--------------------------------------------\n") );
		if( pFileIfStart )
			Release( pFileIfStart );
		pFileIfStart = NULL;
		nLineIfStart = 0;
	}
}
//----------------------------------------------------------------------
void GetIfBegin( char**file, int*line)
{
	if( file )
		*file = pFileIfStart;
	if( line )
		*line = nLineIfStart;
}
//----------------------------------------------------------------------
int PreProcessLine( void )
{
	PTEXT pDirective = NULL;
	PTEXT pFirstWord;
	if( !( pFirstWord = GetCurrentWord() ) )
		return FALSE;
	if( g.bDebugLog )
	{
		fprintf( stddbg, WIDE("%s(%d): "), GetCurrentFileName(), GetCurrentLine() );
		DumpSegs( GetCurrentWord() );
		fprintf( stddbg, WIDE("\n") );
	}
	// pre-processor command processing....
	if( GetText( GetCurrentWord() )[0] == '#' )
	{
		// pre processor directive at start of line...
		pDirective = StepCurrentWord();
		if( !pDirective )
			return FALSE;
		StepCurrentWord();
//==== ENDIF =====================================================
		if( TextLike( pDirective, WIDE("endif") ) )
		{
			if( g.flags.skip_logic_processing || g.flags.skip_define_processing ) {
				SetCurrentWord( pFirstWord );
				return TRUE;
			}
			if( nState & FIND_ELSE )
			{
				if( g.nIfLevels == nIfLevelElse )
				{
					if( g.bDebugLog )
						fprintf( stddbg, WIDE("%s(%d): Looking for an else - found endif - correct level\n")
								 , GetCurrentFileName(), GetCurrentLine() );
					nState &= ~FIND_ELSE;
				}
				else if( g.bDebugLog )
					fprintf( stddbg, WIDE("%s(%d): Looking for an else - found endif - wrong level\n")
								 , GetCurrentFileName(), GetCurrentLine() );
			}
			if( nState & FIND_ENDIF )
			{
				if( g.nIfLevels == nIfLevelElse )
				{
					if( g.bDebugLog )
						fprintf( stddbg, WIDE("%s(%d): Looking for an endif - found endif - correct level\n")
								 , GetCurrentFileName(), GetCurrentLine() );
					nState &= ~FIND_ENDIF;
				}
				else if( g.bDebugLog )
					fprintf( stddbg, WIDE("%s(%d): Looking for an endif - found endif - wrong level\n")
								 , GetCurrentFileName(), GetCurrentLine() );
			}
			ClearIfBegin();
			  if( !g.nIfLevels )
			  {
				if( g.bDebugLog )
					fprintf( stddbg, WIDE("-------------------------------------\n") );
				  nState &= ~(FIND_ELSE | FIND_ENDIF);
			  }
			return FALSE;
		}
		if( nState & FIND_ENDIF )
		{
			if( TextLike( pDirective, WIDE("ifdef") ) ||
					  TextLike( pDirective, WIDE("ifndef") ) ||
					  TextLike( pDirective, WIDE("if") ) )
			{
				if( g.flags.skip_logic_processing || g.flags.skip_define_processing ) {
					SetCurrentWord( pFirstWord );
					return TRUE;
				}
				SetIfBegin();
				if( g.bDebugLog )
				{
					fprintf( stddbg, WIDE("%s(%d): Another level of ifs... coming up! (%d)\n")
							 , GetCurrentFileName(), GetCurrentLine()
							 , g.nIfLevels  );
				}
			}
			return FALSE;
		}
//==== ELSE =====================================================
		else if( TextLike( pDirective, WIDE("else") ) )
		{
			if( g.flags.skip_logic_processing || g.flags.skip_define_processing ) {
				SetCurrentWord( pFirstWord );
				return TRUE;
			}
			if( GetCurrentWord() )
			{
				fprintf( stderr, WIDE("%s(%d) Warning: harmless extra tokens after #ELSE\n")
						 , GetCurrentFileName(), GetCurrentLine() );
			}
			if( nState & FIND_ENDIF )
			{
				// if only looking for endif - continue....
				if( g.bDebugLog )
					fprintf( stddbg, WIDE("Still looking for endif... skipping else\n") );
				return FALSE;
			}
			if( nState & FIND_ELSE )
			{
				if( g.nIfLevels == nIfLevelElse )
				{
					if( g.bDebugLog )
						fprintf( stddbg, WIDE("%s(%d): Found an else on the correct level - let's process...\n")
								 , GetCurrentFileName(), GetCurrentLine() );
					// is the else that we seek....
					// otherwise probalby in a sub-if and need
					// to wait for that #endif to complete and
					// get us back to the  right level to find
					// and else....
					nState &= ~FIND_ELSE;
				}
				return FALSE;
			}
 // was in an if - and now need to find endif...
			else
			{
					if( g.bDebugLog )
						fprintf( stddbg, WIDE("%s(%d): else termination - next to find endif this level(%d)\n")
								 , GetCurrentFileName(), GetCurrentLine()
								 , g.nIfLevels );
				// if we ever hit an else that is actively processing
				// then find the else... otherwise
				// it would be skipped
				//fprintf( stderr, WIDE("Finding the endif of the current if...\n") );
				nIfLevelElse = g.nIfLevels;
				nState |= FIND_ENDIF;
			}
			return FALSE;
		}
//==== ELSEIFDEF ELIFDEF =====================================================
		else if( TextLike( pDirective, WIDE("elseifdef") ) ||
					TextLike( pDirective, WIDE("elifdef") ) )
		{
			if( g.flags.skip_logic_processing || g.flags.skip_define_processing ) {
				SetCurrentWord( pFirstWord );
				return TRUE;
			}
			if( !( nState & FIND_ELSE ) )
			{
				// if was processing, an else causes find endif...
				nState = FIND_ENDIF;
				nIfLevelElse = g.nIfLevels;
				return TRUE;
			}
			return FALSE;
		}
//==== ELSEIFNDEF ELIFNDEF =====================================================
		else if( TextLike( pDirective, WIDE("elseifndef") ) ||
					TextLike( pDirective, WIDE("elifndef") ) )
		{
			if( g.flags.skip_logic_processing || g.flags.skip_define_processing ) {
				SetCurrentWord( pFirstWord );
				return TRUE;
			}
			if( !( nState & FIND_ELSE ) )
			{
				// if was processing, an else causes find endif...
				nState = FIND_ENDIF;
				nIfLevelElse = g.nIfLevels;
				return TRUE;
			}
			// results in find_else... else continues...
			// unless
			return FALSE;
		}
		// nothing else is valid if I'm still looking for an else or endif and it was not handled
		// by the prior two conditions....
		if( nState & (FIND_ELSE | FIND_ENDIF) )
		{
			if( g.flags.skip_logic_processing || g.flags.skip_define_processing ) {
				SetCurrentWord( pFirstWord );
				return TRUE;
			}
			if( TextLike( pDirective, WIDE("elseif") ) ||
				TextLike( pDirective, WIDE("elif") ) )
			{
				goto SubstituteAndProcess;
			}
			else if( TextLike( pDirective, WIDE("ifdef") ) ||
					  TextLike( pDirective, WIDE("ifndef") ) ||
					  TextLike( pDirective, WIDE("if") ) )
			{
				SetIfBegin();
				if( g.bDebugLog )
				{
					fprintf( stddbg, WIDE("%s(%d): Another level of ifs... coming up! (%d)\n")
							 , GetCurrentFileName(), GetCurrentLine()
							 , g.nIfLevels  );
				}
			}
			//fprintf( stderr, WIDE("Failing line...\n") );
			return FALSE;
		}
//== INCLUDE =======================================================
		if( TextLike( pDirective, WIDE("include") ) )
		{
			//fprintf( stderr, WIDE("Include segments...") );
			//DumpSegs( pDirective );
			ProcessInclude( FALSE );
			if( g.flags.keep_includes && !g.flags.bIncludedLastFile )
				SetCurrentWord( pFirstWord );
			return g.flags.keep_includes;
		}
//== INCLUDE NEXT ==================================================
		else if( TextLike( pDirective, WIDE("include_next") ) )
		{
			//fprintf( stderr, WIDE("Include segments...") );
			//DumpSegs( pDirective );
			if( g.flags.keep_includes )
				SetCurrentWord( pFirstWord );
			else {
				ProcessInclude( TRUE );
				if( g.flags.keep_includes && !g.flags.bIncludedLastFile )
					SetCurrentWord( pFirstWord );
			}
			return g.flags.keep_includes;
		}
//== DEFINE =======================================================
		else if( TextLike( pDirective, WIDE("define") ) )
		{
			if( !NEXTLINE( pDirective ) )
			{
				fprintf( stderr, WIDE("\"#define\" keyword alone is NOT allowed...") );
 // can still continue....
				return FALSE;
			}
			if( g.flags.skip_define_processing ) {
				ProcessDefine( DEFINE_ALL );
				SetCurrentWord( pFirstWord );
				return TRUE;
			}
			ProcessDefine( DEFINE_FILE );
			if( g.flags.skip_logic_processing ) {
				SetCurrentWord( pFirstWord );
				return TRUE;
			}
			return FALSE;
		}
//== UNDEF  =======================================================
		else if( TextLike( pDirective, WIDE("undef") ) )
		{
			PDEF pDef;
			if( g.flags.skip_define_processing ) {
				SetCurrentWord( pFirstWord );
				return TRUE;
			}
			pDef = FindDefineName( GetCurrentWord(), IGNORE_PARAMS );
			if( pDef )
			{
				DeleteDefine( &pDef );
			}
			if( g.flags.skip_logic_processing ) {
				SetCurrentWord( pFirstWord );
				return TRUE;
			}
			return FALSE;
		}
//== IFDEF =======================================================
		else if( TextLike( pDirective, WIDE("ifdef") ) )
		{
			if( g.flags.skip_logic_processing || g.flags.skip_define_processing ) {
				SetCurrentWord( pFirstWord );
				return TRUE;
			}
			SetIfBegin();
			if( !FindDefineName( GetCurrentWord(), IGNORE_PARAMS ) )
			{
				if( g.bDebugLog )
				{
					fprintf( stddbg, WIDE("%s(%d): ifdef %s FAILED\n")
							, GetCurrentFileName()
							  , GetCurrentLine()
							, GetText( GetCurrentWord() ));
				}
				nState |= FIND_ELSE;
			}
			else
				if( g.bDebugLog )
				{
					fprintf( stddbg, WIDE("%s(%d): ifdef %s SUCCESS\n")
							, GetCurrentFileName()
							  , GetCurrentLine()
							, GetText( GetCurrentWord() ) );
				}
			nIfLevelElse = g.nIfLevels;
			return FALSE;
		}
//== IFNDEF =======================================================
		else if( TextLike( pDirective, WIDE("ifndef") ) )
		{
			if( g.flags.skip_logic_processing || g.flags.skip_define_processing ) {
				SetCurrentWord( pFirstWord );
				return TRUE;
			}
			SetIfBegin();
			if( FindDefineName( GetCurrentWord(), IGNORE_PARAMS ) )
			{
				if( g.bDebugLog )
				{
					fprintf( stddbg, WIDE("%s(%d): ifndef %s FAILED\n")
							, GetCurrentFileName()
							  , GetCurrentLine()
							, GetText( GetCurrentWord() ));
				}
				nState |= FIND_ELSE;
			}
			else
				if( g.bDebugLog )
					fprintf( stddbg, WIDE("%s(%d): ifndef %s SUCCESS\n")
							, GetCurrentFileName()
							  , GetCurrentLine()
							, GetText( GetCurrentWord() ) );
			nIfLevelElse = g.nIfLevels;
			// otherwise we can store these statements...
			return FALSE;
		}
		// have to go through all words and check vs current
		// defines to see if we need to substitute the data or not...
	SubstituteAndProcess:
		if( !g.flags.skip_define_processing && !g.flags.skip_logic_processing )
		{
			PTEXT line = GetCurrentWord();
			EvalSubstitutions( &line, FALSE );
			if( line != GetCurrentWord() )
				SetCurrentWord( line );
		}
//=== IF ======================================================
		if( TextLike( pDirective, WIDE("if") ) )
		{
			PTEXT dbg;
			if( g.flags.skip_logic_processing || g.flags.skip_define_processing ) {
				SetCurrentWord( pFirstWord );
				return TRUE;
			}
			SetIfBegin();
			if( !ProcessExpression() )
			{
				nState |= FIND_ELSE;
				nIfLevelElse = g.nIfLevels;
				if( g.bDebugLog )
				{
					dbg = BuildLine( pDirective );
					fprintf( stddbg, WIDE("%s(%d): %s FAILED\n")
									, GetCurrentFileName()
									, GetCurrentLine()
									, GetText(dbg) );
					LineRelease( dbg );
				}
			}
			else
			{
				if( g.bDebugLog )
				{
					dbg = BuildLine( pDirective );
					fprintf( stddbg, WIDE("%s(%d): %s SUCCESS\n")
									, GetCurrentFileName()
									, GetCurrentLine()
									, GetText(dbg) );
					LineRelease( dbg );
				}
			}
		}
//=== ELSEIF ELIF ======================================================
		else if( TextLike( pDirective, WIDE("elseif") ) ||
				  TextLike( pDirective, WIDE("elif") ) )
		{
			if( g.flags.skip_logic_processing || g.flags.skip_define_processing ) {
				SetCurrentWord( pFirstWord );
				return TRUE;
			}
			if( nState & FIND_ELSE )
			{
				PTEXT dbg;
				if( g.nIfLevels == nIfLevelElse &&
					 ProcessExpression() )
				{
					if( g.bDebugLog )
					{
						dbg = BuildLine( pDirective );
						fprintf( stddbg, WIDE("%s(%d): %s Success\n")
									, GetCurrentFileName()
									, GetCurrentLine()
								, GetText( dbg ) );
						LineRelease( dbg );
					}
					nState &= ~FIND_ELSE;
				}
				else if( g.bDebugLog )
				{
					dbg = BuildLine( pDirective );
					fprintf( stddbg, WIDE("%s(%d): %s Failure\n")
									, GetCurrentFileName()
									, GetCurrentLine()
							, GetText( dbg ) );
					LineRelease( dbg );
				}
			}
 // wasn't looking for else - else found - go to endif now.
			else
			{
				nState = FIND_ENDIF;
				nIfLevelElse = g.nIfLevels;
			}
		}
//==== PRAGMA =====================================================
		else if( TextLike( pDirective, WIDE("pragma") ) )
		{
			// pramga message seems to be a useful thing to have...
			// other pragmas need to be ignored
			// pragmas occur with all data on a single line.
			// evaluate substitutions... (already done)
			PTEXT pOp = GetCurrentWord();
			if( TextLike( pOp, WIDE( "multiinclude" ) ) )
			{
				g.pFileStack->pFileDep->bAllowMultipleInclude = TRUE;
			}
			else if( TextLike( pOp, WIDE( "message" ) ) )
			{
				PTEXT pOut;
				pOut = BuildLineEx( NEXTLINE( pOp ), FALSE DBG_SRC );
				pOut->data.size = CollapseQuotes( pOut->data.data );
				pOut->data.size = KillQuotes( pOut->data.data );
				fprintf( stderr, WIDE("%s\n"), GetText( pOut ) );
				//fprintf( stdout, WIDE("%s\n"), GetText( pOut ) );
				LineRelease( pOut );
				// dump the remaining segments...
			}
			else if( TextLike( pOp, WIDE("systemincludepath") ) )
			{
				PTEXT pOut;
				pOut = BuildLineEx( NEXTLINE( pOp ), FALSE DBG_SRC );
				AddLink( g.pSysIncludePath, pOut );
			}
			else if( TextLike( pOp, WIDE("includepath") ) )
			{
				PTEXT pOut;
				pOut = BuildLineEx( NEXTLINE( pOp ), FALSE DBG_SRC );
				AddLink( g.pUserIncludePath, pOut );
			}
			else if( TextLike( pOp, WIDE("pack") ) )
			{
				if( g.flags.skip_logic_processing || g.flags.skip_define_processing ) {
					SetCurrentWord( pFirstWord );
					return TRUE;
				}
				if( g.bDebugLog )
				{
					PTEXT pOut;
					pOut = BuildLineEx( pOp, FALSE DBG_SRC );
					fprintf( stderr, WIDE("%s(%d): %s Unknown pragma: %s\n")
							 , GetCurrentFileName()
							 , GetCurrentLine()
							 , g.flags.bEmitUnknownPragma?"emitting":"dropping"
							 , GetText( pOut ) );
					LineRelease( pOut );
				}
				SetCurrentWord( pFirstWord );
				return g.flags.bEmitUnknownPragma;
			}
			// watcom - inline assembly junk...
			else if( TextLike( pOp, WIDE("warning") )
					 ||  TextLike( pOp, WIDE("intrinsic") )
					  || TextLike( pOp, WIDE("aux") )
					  || TextLike( pOp, WIDE("function") )
					 || TextLike( pOp, WIDE("comment") ) )
			{
				if( g.bDebugLog )
				{
					PTEXT pOut;
					pOut = BuildLineEx( pOp, FALSE DBG_SRC );
					fprintf( stderr, WIDE("%s(%d): %s Unknown pragma: %s\n")
							 , GetCurrentFileName()
							 , GetCurrentLine()
							 , g.flags.bEmitUnknownPragma?"emitting":"dropping"
							 , GetText( pOut ) );
					LineRelease( pOut );
				}
				SetCurrentWord( pFirstWord );
				return g.flags.bEmitUnknownPragma;
			}
			// watcom - dependancy generation...
			else if( TextLike( pOp, WIDE("read_only_file") ) )
			{
				// can't see any usefulness when using ppc to preprocess...
				return FALSE;
			}
			else
			{
				PTEXT pOut;
				if( g.flags.skip_logic_processing || g.flags.skip_define_processing ) {
					SetCurrentWord( pFirstWord );
					return TRUE;
				}
				pOut = BuildLineEx( pOp, FALSE DBG_SRC );
				fprintf( stderr, WIDE("%s(%d): Unknown pragma: %s\n")
						 , GetCurrentFileName()
						 , GetCurrentLine()
						 , GetText( pOut ) );
				LineRelease( pOut );
				// hmm - gcc processing .i files fails this.
				SetCurrentWord( pFirstWord );
				return g.flags.bEmitUnknownPragma;
				//return TRUE; // emit this line - maybe the compiler knows...
				//return FALSE;
			}
		}
		else if( TextLike( pDirective, WIDE("warning") ) )
		{
			PTEXT pOut;
			pOut = BuildLineEx( GetCurrentWord(), FALSE DBG_SRC );
			fprintf( stderr, WIDE("%s(%d): Warning %s\n")
					 , GetCurrentFileName()
					 , GetCurrentLine()
					 , GetText( pOut ) );
			LineRelease( pOut );
		}
		else if( TextLike( pDirective, WIDE("error") ) )
		{
			PTEXT pOut;
			if( g.flags.skip_logic_processing || g.flags.skip_define_processing ) {
				SetCurrentWord( pFirstWord );
				return TRUE;
			}
			pOut = BuildLineEx( GetCurrentWord(), FALSE DBG_SRC );
			fprintf( stderr, WIDE("%s(%d): Error %s\n")
					 , GetCurrentFileName()
					 , GetCurrentLine()
					 , GetText( pOut ) );
			LineRelease( pOut );
			g.ErrorCount++;
		}
		else
		{
			PTEXT pOut;
			pOut = BuildLineEx( pDirective, FALSE DBG_SRC );
			fprintf( stderr, WIDE("%s(%d): Unknown prepcessing directive: %s\n")
					 , GetCurrentFileName()
					 , GetCurrentLine()
					 , GetText( pOut ) );
			LineRelease( pOut );
		}
		return FALSE;
	}
	if( nState & ( FIND_ELSE|FIND_ENDIF ) )
	{
		// ignore anything on this line for output
		return FALSE;
	}
	if( pDirective )
	{
		fprintf( stderr, WIDE("ERROR: Responding true to invoking a preprocessor command to output\n") );
	}
	if( !g.flags.skip_define_processing && !g.flags.skip_logic_processing )
	{
		PTEXT *line = GetCurrentTextLine();
		//PTEXT reset = GetCurrentWord();
		if( nState )
			fprintf( stderr, WIDE("ERROR: Substituting the line...bad state %d\n"), nState );
		EvalSubstitutions( line, TRUE );
		SetCurrentWord( pFirstWord );
	}
	return TRUE;
}
//----------------------------------------------------------------------------
int ProcessStatement( void )
{
	return TRUE;
	//ProcessEnum();  // snags enumeration symbols...
	//ProcessStructUnion(); // builds union/structure space...
	//ProcessArray(); // handles gathering and possible re-emmission of arrays...
}
//----------------------------------------------------------------------------
void RunProcessFile( void )
{
	while( ReadLine( FALSE ) )
	{
		int depth = CurrentFileDepth();
		if( PreProcessLine() )
		{
			//if( g.flags.keep_includes )
			{
			//	if( depth > 1 )
			//		continue;
			}
			if( ProcessStatement() )
			{
				PTEXT pOut;
				pOut = BuildLineEx( GetCurrentWord(), FALSE DBG_SRC );
				if( pOut )
				{
					if( g.flags.bWriteLineInfo )
					{
						WriteCurrentLineInfo();
					}
					WriteLine( GetTextSize( pOut ), GetText( pOut ) );
					LineRelease( pOut );
				}
			}
		}
	}
	if( nState || g.nIfLevels )
	{
		char *file;
		int line;
		GetIfBegin( &file, &line );
		fprintf( stderr, WIDE("Missing #endif starting at %s(%d)")
					, file, line );
	}
	// at this point we have dumped an output file....
	// the standard states
//	5. Each source character set member and escape sequence in character constants and
//string literals is converted to the corresponding member of the execution character
//set; if there is no corresponding member, it is converted to an implementationdefined
//member other than the null (wide) character.7)
	// this is done above... as we are handling substitutions...
	// though this will result in an inability to handle some things like...
	// "\33" "3"
// 6. Adjacent string literal tokens are concatenated.
// 7. 8. ... and done :)
}
void ProcessFile( char *file );
void loadConfig( void ) {
	{
		char file[256];
/*g.pExecPath*/
		sprintf( file, WIDE( "%s/config.ppc" ), g.pWorkPath );
		//printf( WIDE("loading defines from %s"), file );
#if defined( __WATCOMC__ ) || defined (__LCC__)
		{
			char *includepath = getenv( WIDE( "INCLUDE" ) );
			// %WATCOM%\H\NT;%WATCOM%\H;%INCLUDE%
			char *start, *end;
			start = includepath;
			while( start[0] && (end = strchr( start, ';' )) )
			{
				PTEXT pOut;
				end[0] = 0;
				//printf( WIDE("Adding include path: %s"), start );
				pOut = SegCreateFromText( start );
				AddLink( g.pSysIncludePath, pOut );
				start = end + 1;
			}
			if( start[0] )
			{
				PTEXT pOut;
				//printf( WIDE("Adding include path: %s"), start );
				pOut = SegCreateFromText( start );
				AddLink( g.pSysIncludePath, pOut );
			}
		}
#endif
		ProcessFile( file );
		CommitDefinesToCommandLine();
		DestoyDepends();
	}
}
void ProcessFile( char *file )
{
	char newname[__MAX_PATH__];
	char *filestart = pathrchr( file );
	if( !g.flags.config_loaded ) {
		g.flags.config_loaded = 1;;
		loadConfig();
	}
	if( !filestart )
		filestart = file;
	else
		filestart++;
	if( !OpenInputFile( filestart, file ) )
	{
		return;
	}
	if( g.CurrentOutName[0] != 0xFF )
	{
		if( !g.flags.bStdout )
		{
			if( g.CurrentOutName[0] )
				strcpy( newname, g.CurrentOutName );
			else
			{
				strcpy( newname, file );
 // replace last char with i...
				newname[strlen(newname)-1] = 'i';
			}
			if( !OpenOutputFile( newname ) )
			{
				CloseInputFile();
				return;
			}
		}
		else
		{
			if( !OpenStdOutputFile() )
			{
				CloseInputFile();
				return;
			}
		}
		g.CurrentOutName[0] = 0xFF;
		{
			PINCLUDE_REF pRef;
			while( pRef = PopLink( g.pIncludeList ) )
			{
				g.flags.bNoOutput = pRef->flags.bMacros;
				if( !ProcessSystemIncludeFile( pRef->name, TRUE, FALSE ) )
				{
					fprintf( stderr, WIDE("%s(%d): Warning could not process include file \'%s\'\n")
							, GetCurrentFileName(), GetCurrentLine()
							, pRef->name );
					//g.ErrorCount++;
					return;
				}
				Release( pRef );
			}
			g.flags.bNoOutput = 0;
		}
	}
 // all files should be closed once this returns.
	RunProcessFile();
}
void ReleaseIncludePaths( void )
{
	INDEX idx;
	PTEXT path;
	FORALL( g.pSysIncludePath, idx, PTEXT, path )
		Release( path );
	DeleteList( g.pSysIncludePath );
	FORALL( g.pUserIncludePath, idx, PTEXT, path )
	{
 // don't release user include directory 0 - internal use.
		if( idx )
			Release( path );
	}
	DeleteList( g.pUserIncludePath );
}
void usage( void )
{
	printf( WIDE("usage: %s (options) <files...>\n"), g.pExecName );
	printf( WIDE("\toptions to include\n")
			  "	------------------------------------------\n" );
	printf( WIDE("\t -[Ii]<path(s)>      add include path to default\n") );
	printf( WIDE("\t -[Ss][Ii]<path(s)>  add include path to system default\n") );
	printf( WIDE("\t -[Dd]<symbol>       define additional symbols\n") );
	printf( WIDE("\t -MF<file>           dump out auto-depend info\n") );
	printf( WIDE("\t -MT<file>           use (file) as name of target in depend file\n") );
	printf( WIDE("\t -L                  write file/line info prefixing output lines\n") );
	printf( WIDE("\t -l                  write file/line info prefixing output lines\n") );
	printf( WIDE( "	                           (without line directive)\n" ) );
	printf( WIDE("\t -K                  emit unknown pragmas into output\n") );
	printf( WIDE("\t -k                  do not emit unknown pragma (default)\n") );
	printf( WIDE("\t -c                  keep comments in output\n") );
	printf( WIDE("\t -p                  keep includes in output (don't output content of include)\n") );
	printf( WIDE("\t -f                  force / into \\ in include statements with paths\n" ) );
	printf( WIDE("\t -sd                 skip define processing (if,else,etc also skippped)\n" ) );
	printf( WIDE("\t -sl                 skip logic processing (if,else,endif skippped; process defines for include subst)\n" ) );
	printf( WIDE("\t -ssio               Skip System Include Out;try to keep #includes that are missing as #include\n" ) );
	printf( WIDE("\t -F                  force \\ into /\n") );
	printf( WIDE("\t -[Oo]<file>         specify the output filename; output filename must be set before input(s) are read\n") );
	printf( WIDE("\t                         -o output \"process this file into output.c\"\n" ) );
	printf( WIDE("\t -once               only load any include once\n") );
	printf( WIDE("\t -[Zz]#              debug info mode. where number is in ( 1, 2, 4 )\n") );
	printf( WIDE("\t @<file>              any option read from a file...\n") );
	printf( WIDE("  Any option prefixed with a - will force the option off...  --c to force not keeping comments\n") );
	printf( WIDE("  Option L is by default on. (line info with #line keyword)\n") );
	printf( WIDE("  output default is input name substituing the last character for an i...\n") );
	printf( WIDE("\t\t  test.cpp -> test.cpi  test.c -> test.i\n") );
	printf( WIDE("\t examples : \n" ) );
	printf( WIDE("\t\tppc source_file.c\n" ) );
	printf( WIDE("\t\t# the following is how to do an amalgamtion\n" ) );
	printf( WIDE("\t\tppc -sd -ssio -K -c -once -Iinclude -o file_all.c file1.c file2.c file3.c\n" ) );
	printf( WIDE("\t\tppc -sdssioKconce -Iinclude -o file_all.c file1.c file2.c file3.c\n" ) );
	printf( WIDE("\t -? for more help\n") );
	printf( WIDE(" (startup directory)/config.ppc is read first.  It is only read once.   Usage is intended to generate\n" ) );
	printf( WIDE(" one file at a time.   It IS possible to do -o file1.i file1.c -o file2.i file2.c but the config.ppc won't\n" ) );
	printf( WIDE(" be read the second time.  However, symbols meant to be kept in an amalgamtion output can be define here, and\n" ) );
   printf( WIDE(" those defines will be kept.\n" ) );
}
void longusage( void )
{
	printf( WIDE("Unimplemented yet... showing usage()\n") );
	usage();
}
int ispathchr( char c )
{
	if( c == '\\' || c == '/' )
		return TRUE;
	return FALSE;
}
char *nextchr( char *string, char *chars )
{
	char *test;
	if( !string || !chars )
		return NULL;
	while( string[0] )
	{
		test = chars;
		while( test[0] )
		{
			if( string[0] == test[0] )
				return string;
			test++;
		}
		string++;
	}
	return NULL;
}
int processArguments( int argc, char **argv ) {
	{
		int i=1;
		int nArgState = ARG_UNKNOWN;
		for( i = 1; i < argc; i++  )
		{
			if( argv[i][0] == '@' ) {
				FILE *file = fopen( argv[i]+1, "rt" );
				if( file ) {
					char buf[4096];
					while( fgets( buf, 4096, file ) )
					{
						int tmpargc;
						char **tmpargv;
						int len = (int)strlen(buf);
						if( buf[len-1] == '\n' )
							buf[len-1] = 0;
						ParseIntoArgs( buf, &tmpargc, &tmpargv );
						processArguments( tmpargc+1, tmpargv-1 );
						{
							int n;
							// be nice and cleanup memory.
							for( n = 0; n < tmpargc; n++ )
								Release( tmpargv[n] );
							Release( tmpargv );
						}
					}
				}
			}
			else if( argv[i][0] == '-' ||
				 //argv[i][0] == '/' ||
				 nArgState )
			{
				int n, done = 0, negarg = 0;
				for( n = 1;
					  !done && argv[i][n];
					  n++ )
				{
					switch( nArgState )
					{
					case ARG_MACRO_FILE:
						{
							PINCLUDE_REF pRef = Allocate( sizeof( INCLUDE_REF ) );
							pRef->flags.bMacros = 1;
							pRef->name = argv[i];
							PushLink( g.pIncludeList, pRef );
						}
						nArgState = ARG_UNKNOWN;
						done = 1;
						break;
					case ARG_INCLUDE_FILE:
						{
							PINCLUDE_REF pRef = Allocate( sizeof( INCLUDE_REF ) );
							pRef->flags.bMacros = 0;
							pRef->name = argv[i];
							PushLink( g.pIncludeList, pRef );
						}
						nArgState = ARG_UNKNOWN;
						done = 1;
						break;
					case ARG_AUTOTARGET_NAME:
						strcpy( g.AutoTargetName, argv[i] );
						nArgState = ARG_UNKNOWN;
						done = 1;
						break;
					case ARG_GEN_STDOUT:
						nArgState = ARG_UNKNOWN;
						done = 1;
						break;
					case ARG_OUT_NAME:
						strcpy( g.CurrentOutName, argv[i] );
						nArgState = ARG_UNKNOWN;
						done = 1;
						break;
					case ARG_AUTODEPEND_NAME:
						g.AutoDependFile = fopen( argv[i], WIDE("wt") );
						if( !g.AutoDependFile )
						{
							fprintf( stderr, WIDE("Failed to open %s for auto depend info."), argv[i] );
						}
						nArgState = ARG_UNKNOWN;
						done = 1;
						break;
					case ARG_INCLUDE_PATH:
						{
							char *arg, *next, *tmp;
							next = arg = argv[i];
							if( argv[i][0] != '-' )
							{
								while( ( next = nextchr( arg, WIDE(";,:") ) ) )
								{
 // terminate new string...
									*next = 0;
									next++;
									tmp = arg + ( strlen( arg ) - 1 );
									if( ispathchr( *tmp ) )
 // terminate prior;
										*tmp = 0;
									AddLink( g.pUserIncludePath, SegCreateFromText( arg ) );
									arg = next;
								}
								tmp = arg + ( strlen( arg ) - 1 );
								if( ispathchr( *tmp ) )
 // terminate prior;
									*tmp = 0;
								AddLink( g.pUserIncludePath, SegCreateFromText( arg ) );
							}
							else
								i--;
						}
						nArgState = 0;
						done = 1;
						break;
					case ARG_SYS_INCLUDE_PATH:
						{
							char *arg, *next, *tmp;
							next = arg = argv[i];
							while( ( next = nextchr( arg, WIDE(";,") ) ) )
							{
 // terminate new string...
								*next = 0;
								next++;
								tmp = arg + ( strlen( arg ) - 1 );
								if( ispathchr( *tmp ) )
 // terminate prior;
									*tmp = 0;
								AddLink( g.pSysIncludePath, SegCreateFromText( arg ) );
								arg = next;
							}
							tmp = arg + ( strlen( arg ) - 1 );
							if( ispathchr( *tmp ) )
 // terminate prior;
								*tmp = 0;
							AddLink( g.pSysIncludePath, SegCreateFromText( arg ) );
						}
						nArgState = 0;
						done = 1;
						break;
					case ARG_UNKNOWN:
					default:
						// some option to turn off/on write line info...
						if( argv[i][n] == '-' )
						{
							negarg = 1;
						}
						else if( argv[i][n] == 'c' )
						{
							g.flags.keep_comments = 1;
						}
						else if( argv[i][n] == 'p' )
						{
							g.flags.keep_includes = 1;
						}
						else if( argv[i][n] == 'I' )
						{
							char *arg, *next, *tmp;
							if( !argv[i][n+1] )
							{
								nArgState = ARG_INCLUDE_PATH;
								done = 1;
								break;
							}
							next = arg = argv[i] + n + 1;
							while( ( next = nextchr( arg, WIDE(";,") ) ) )
							{
 // terminate new string...
								*next = 0;
								next++;
								tmp = arg + ( strlen( arg ) - 1 );
								if( ispathchr( *tmp ) )
 // terminate prior;
									*tmp = 0;
								AddLink( g.pUserIncludePath, SegCreateFromText( arg ) );
								arg = next;
							}
							tmp = arg + ( strlen( arg ) - 1 );
							if( ispathchr( *tmp ) )
 // terminate prior;
								*tmp = 0;
							AddLink( g.pUserIncludePath, SegCreateFromText( arg ) );
							done = 1;
							break;
						}
						else if( argv[i][n] == 'i' )
						{
							if( strcmp( argv[i] + n, WIDE("include") ) == 0 )
							{
								//if( argv[i][n+7]
								nArgState = ARG_INCLUDE_FILE;
								done = 1;
								break;
							}
							else if( strcmp( argv[i] + n + 1, WIDE("macro") ) == 0 )
							{
								nArgState = ARG_MACRO_FILE;
								done = 1;
								break;
							}
							else
							{
								fprintf( stderr, WIDE("Argument error: %s\n"), argv[i] );
								usage();
								return 1;
							}
						}
						else if( (argv[i][n] == 's' &&
							argv[i][n + 1] == 'o') )
						{
							g.flags.bStdout = 1;
							n += 1;
							break;
						}
						else if( argv[i][n] == 's' && argv[i][n + 1] &&
							argv[i][n + 1] == 'd' ) {
							g.flags.skip_define_processing = 1;
							n += 1;
							break;
						}
						else if( argv[i][n] == 's' && argv[i][n + 1] &&
							argv[i][n + 1] == 'l' ) {
							g.flags.skip_logic_processing = 1;
							n += 1;
							break;
						}
						else if( argv[i][n] == 's' && argv[i][n + 1] &&
							argv[i][n + 1] == 's' && argv[i][n + 2] &&
							argv[i][n + 2] == 'i' && argv[i][n + 3] &&
							argv[i][n + 3] == 'o'
							)
						{
							g.flags.bSkipSystemIncludeOut = 1;
							n+=3;
							break;
						}
						else if( ( argv[i][n] == 's' ||
							  argv[i][n] == 'S' ) &&
							( argv[i][n+1] == 'I' ||
								argv[i][n+1] == 'i' ) )
						{
							char *arg, *next, *tmp;
							if( !argv[i][n+2] )
							{
								nArgState = ARG_SYS_INCLUDE_PATH;
								done = 1;
								break;
							}
							next = arg = argv[i] + n + 2;
							while( ( next = nextchr( arg, WIDE(";,") ) ) )
							{
 // terminate new string...
								*next = 0;
								next++;
								tmp = arg + ( strlen( arg ) - 1 );
								if( ispathchr( *tmp ) )
 // terminate prior;
									*tmp = 0;
								AddLink( g.pSysIncludePath, SegCreateFromText( arg ) );
								arg = next;
							}
							tmp = arg + ( strlen( arg ) - 1 );
							if( ispathchr( *tmp ) )
 // terminate prior;
								*tmp = 0;
							AddLink( g.pSysIncludePath, SegCreateFromText( arg ) );
						}
						else if( strncmp( argv[i]+n, "once", 4 ) == 0 )
						{
							g.flags.load_once = 1;
						}
						else if( argv[i][n] == 'M' )
						{
							if( argv[i][n+1] == 'F' )
							{
								if( argv[i][n+2] )
								{
									if( g.AutoDependFile )
									{
										fprintf( stderr, WIDE("Reopening auto depend file?\n") );
										fclose( g.AutoDependFile );
									}
									g.AutoDependFile = fopen( argv[i]+n+2, WIDE("wt") );
									if( !g.AutoDependFile )
									{
										fprintf( stderr, WIDE("Failed to open %s for auto depend info.\n"), argv[i]+n+2 );
									}
								}
								else
								{
									nArgState = ARG_AUTODEPEND_NAME;
								}
								g.bAutoDepend = TRUE;
							}
							else if( argv[i][n+1] == 'T' )
							{
								if( argv[i][n+2] ) strcpy( g.AutoTargetName, argv[i]+n+2 );
								else nArgState = ARG_AUTOTARGET_NAME;
							}
							else
								goto unknown_option;
						}
						else if( argv[i][n] == 'o' ||
								  argv[i][n] == 'O' )
						{
							printf( "output %s", argv[i] + 2 );
							if( negarg )
							{
								g.CurrentOutName[0] = 0xFF;
							}
							else
							{
								if( argv[i][n+1] )
								{
									strcpy( g.CurrentOutName, argv[i] + n + 1 );
									//printf( WIDE("Set output: %s\n"), argv[i] + n + 1 );
									done = 1;
								}
								else
								{
									nArgState = ARG_OUT_NAME;
								}
							}
						}
						else if( argv[i][n] == 'D' ||
								  argv[i][n] == 'd' )
						{
							if( argv[i][n+1] )
							{
								char *eq = strchr( argv[i]+n+1, '=' );
								if( eq )
								{
									*eq = 0;
									eq++;
								}
								// additional command line defines....
								DefineDefine( argv[i] + n+1, eq );
							}
							else
							{
								nArgState = ARG_DEFINE_DEFINE;
							}
						}
						else if( argv[i][n] == 'z' ||
								  argv[i][n] == 'Z' )
						{
							if( isdigit( argv[i][n+1] ) )
							{
								g.bDebugLog = atoi( argv[i] + n+1 );
								printf( WIDE("Debug set to %d\n"), g.bDebugLog );
								if( g.bDebugLog )
									g.dbgout = fopen( "debug.log", "wt" );
							}
							else
								g.bDebugLog = TRUE;
						}
						else if( argv[i][n] == 'L' )
						{
							g.flags.bLineUsesLineKeyword = TRUE;
							 if( negarg )
								g.flags.bWriteLine = FALSE;
							else
							{
								g.flags.bWriteLine = TRUE;
							}
						}
						else if( argv[i][n] == 'l' )
						{
							g.flags.bLineUsesLineKeyword = FALSE;
							if( negarg )
								g.flags.bWriteLine = FALSE;
							else
								g.flags.bWriteLine = TRUE;
						}
						else if( argv[i][n] == 'f' )
						{
							if( negarg )
								g.flags.bForceBackslash = FALSE;
							else
								g.flags.bForceBackslash = TRUE;
						}
						else if( argv[i][n] == 'F' )
						{
							if( negarg )
								g.flags.bForceForeslash = FALSE;
							else
								g.flags.bForceForeslash = TRUE;
						}
						else if( argv[i][n] == 'K' )
						{
							g.flags.bEmitUnknownPragma = TRUE;
						}
						else if( argv[i][n] == 'k' )
						{
							g.flags.bEmitUnknownPragma = FALSE;
						}
						else if( ( argv[i][n] == '?' ) || ( argv[i][n] == 'h' ) )
						{
							longusage();
							return 0;
						}
						else
						{
						unknown_option:
							fprintf( stderr, "unknown option: %s (+%d)\n", argv[i], n );
							usage();
							return 0;
						}
						done = 1;
						break;
					}
				}
			}
			else
			{
				static int process_count;
				process_count++;
				if( process_count > 1 )
				{
					//fprintf( stderr, WIDE("Probable error! -include, -imacro directives are lost.\nMultiple sources on command line.\n") );
				}
				ProcessFile( argv[i] );
				if( !g.flags.skip_logic_processing )
					DeleteAllDefines( DEFINE_FILE );
				//if(  )
				//g.CurrentOutName[0] = 0; // clear name.
			}
		}
	}
	return 2;
}
int main( int argc, char **argv, char **env )
{
#ifdef __LINUX__
	{
		/* #include unistd.h, stdio.h, string.h */
		{
			char buf[256], *pb;
			int n;
			n = readlink( WIDE("/proc/self/exe"), buf, 256 );
			if( n >= 0 )
			{
 //linux
				buf[n] = 0;
				if( !n )
				{
					strcpy( buf, WIDE(".") );
 // fbsd
					buf[ n = readlink( WIDE("/proc/curproc/"), buf, 256 ) ] = 0;
				}
			}
			else
				strcpy( buf, WIDE(".") );
			pb = strrchr( buf, '/' );
			if( pb )
			{
				pb[0]=0;
				pb++;
				strcpy( g.pExecName, pb );
			}
			strcpy( g.pExecPath, buf );
		}
	}
	getcwd( g.pWorkPath, sizeof( g.pWorkPath ) );
#elif defined( _WIN32 )
	 char *laststroke;
	 GetModuleFileName( NULL, g.pExecPath, sizeof(g.pExecPath) );
	 laststroke = pathrchr( g.pExecPath );
	 if( laststroke )
		 laststroke[0] = 0;
	//printf( WIDE("path: %s\n"), g.pExecPath );
	_getcwd( g.pWorkPath, sizeof( g.pWorkPath ) );
#else
	printf( WIDE("Path is not defined - probably will not work.") );
#endif
#ifdef __WATCOMC__
	SetMinAllocate( sizeof( TEXT ) + 16 );
#endif
	DisableMemoryValidate(TRUE);
	// should build this from execution path of this module
	g.flags.do_trigraph = 1;
	g.flags.bWriteLine = TRUE;
	g.flags.bLineUsesLineKeyword = TRUE;
	g.bDebugLog = FALSE;
	//g.dbgout = fopen( "debug.log", "wt" );
	g.CurrentOutName[0] = 0xFF;
	//AddLink( g.pSysIncludePath, SegCreateFromText( WIDE("m:\\lcc\\include") ) );
	AddLink( g.pUserIncludePath, (PTEXT)&g.pCurrentPath );
	SetCurrentPath( WIDE(".") );
	if( argc == 1 ) {
		usage(); return 0;
	}
 // set current date/time macros....
	InitDefines();
	if( 0 && !g.flags.skip_define_processing )
	{
		DefineDefine( WIDE( "TRUE" ), WIDE( "1" ) );
		DefineDefine( WIDE( "FALSE" ), WIDE( "0" ) );
		DefineDefine( WIDE( "true" ), WIDE( "1" ) );
		DefineDefine( WIDE( "false" ), WIDE( "0" ) );
		DefineDefine( WIDE( "__bool_true_false_are_defined" ), WIDE( "1" ) );
		DefineDefine( WIDE( "bool" ), WIDE( "unsigned char" ) );
		DefineDefine( WIDE( "__PPCCPP__" ), WIDE( "0x100" ) );
	}
	{
		int r = processArguments( argc, argv );
		if( r == 0 )
			return 0;
		if( r == 1 )
			 return 1;
	}
	VarTextEmpty( &g.vt );
	if( g.bAutoDepend )
	{
		DumpDepends();
	}
	{
		PINCLUDE_REF pRef;
		while( pRef = PopLink( g.pIncludeList ) )
			Release( pRef );
	}
	DestoyDepends();
	DeleteAllDefines( DEFINE_ALL );
	ReleaseIncludePaths();
	DeinitDefines();
	if( g.bDebugLog )
	{
		fprintf( stderr, WIDE("Allocates: %ld(%zd) Releases: %ld\n"), g.nAllocates, g.nAllocSize, g.nReleases );
		DumpMemory();
	}
	if( g.flags.skip_define_processing )
		return 0;
	return g.ErrorCount;
}
//#include <./types.h>
#define NewArray(a,n)  (a*)Allocate( sizeof( a ) * n )
#ifndef NULL
#  define NULL (void*)0
#endif
void ParseIntoArgs( char *lpCmdLine, int *pArgc, char ***pArgv )
{
	char *args = lpCmdLine;
	char  *p;
	char **pp;
 // result variable, count is a temp counter...
	char argc;
 // result variable, pp is a temp pointer
	char **argv;
	char quote = 0;
	int count = 0;
	int lastchar;
 // auto continue spaces...
	lastchar = ' ';
	//lprintf( WIDE("Got args: %s"), args );
	p = args;
	while( p && p[0] )
	{
		//lprintf( WIDE("check character %c %c"), lastchar, p[0] );
		if( quote )
		{
			if( p[0] == quote )
			{
				count++;
				quote = 0;
				lastchar = ' ';
			}
		}
		else
		{
			if( p[0] == '\"' || p[0] == '\'' )
				quote = p[0];
			else
			{
 // and there's a space
				if( lastchar != ' ' && p[0] == ' ' )
				{
					count++;
				}
				else if( lastchar == ' ' && p[0] != ' ' )
				{
				}
			}
			lastchar = p[0] ;
		}
		p++;
	}
	if( quote )
 // complete this argument
		count++;
	else if( p != args )
      count++;
	if( count )
	{
		char *start;
 // auto continue spaces...
		lastchar = ' ';
      //lprintf( "Array is %d (+2?)", count );
		pp = argv = NewArray( char*, count + 2 );
		argc = count - 2;
		p = args;
		quote = 0;
		count = 0;
		//pp[count++] = StrDup( pTask->pTask ); // setup arg to equal program (needed for linux stuff)
		start = NULL;
		while( p[0] )
		{
			//lprintf( WIDE("check character %c %c"), lastchar, p[0] );
			if( quote )
			{
				if( !start )
					start = p;
				if( p[0] == quote )
				{
					p[0] = 0;
					pp[count++] = StrDup( start );
					p[0] = quote;
					quote = 0;
					start = NULL;
					lastchar = ' ';
				}
			}
			else
			{
				if( p[0] == '\"' || p[0] == '\'' )
					quote = p[0];
				else
				{
 // and there's a space
					if( lastchar != ' ' && p[0] == ' ' )
					{
						p[0] = 0;
						pp[count++] = StrDup( start );
						start = NULL;
						p[0] = ' ';
					}
					else if( lastchar == ' ' && p[0] != ' ' )
					{
						if( !start )
							start = p;
					}
				}
				lastchar = p[0] ;
			}
			p++;
		}
		//lprintf( WIDE("Setting arg %d to %s"), count, start );
		if( start )
			pp[count++] = StrDup( start );
		pp[count] = NULL;
      if( pArgc )
			(*pArgc) = count;
      if( pArgv )
			(*pArgv) = argv;
	}
	else
	{
      if( pArgc )
			(*pArgc) = 0;
		if( pArgv )
		{
			(*pArgv) = Allocate( sizeof( char*) );
			(*pArgv)[0] = NULL;
		}
	}
}
#ifndef __MAC__
#  include <malloc.h>
#endif
#include <stddef.h>
#ifndef PPC_MEMORY_INTERFACE_DEFINED
#define PPC_MEMORY_INTERFACE_DEFINED
#if defined __WATCOMC__
//# include "sharemem.h"
#else
void CPROC *AllocateEx( size_t nSize DBG_PASS );
# define Allocate(s) AllocateEx(s DBG_SRC)
void CPROC ReleaseExx( void ** DBG_PASS );
# if defined( __WATCOMC__ ) || defined( _MSC_VER )
#  ifdef _DEBUG
#   define ReleaseEx(p,f,l ) ReleaseExx( (void**)&p,f,l )
#  else
#   define ReleaseEx(p ) ReleaseExx( (void**)&p )
#  endif
# else
#  define ReleaseEx(... ) ReleaseExx( (void**)&__VA_ARGS__ )
# endif
#define Release(p) ReleaseExx( (void**)&p DBG_SRC)
void DumpMemory( void );
uint32_t CPROC LockedExchange( uint32_t *p, uint32_t val );
void CPROC MemSet( POINTER p, uint32_t v, size_t n);
void CPROC MemCpy( POINTER p, const void *p2, size_t n);
void DisableMemoryValidate( int bDisable );
char CPROC *StrDupEx( const char *original DBG_PASS );
#define StrDup(o) StrDupEx(o DBG_SRC )
#endif
#endif
#define MEMLOG
//#define VALIDATE
//#pragma asm
typedef struct memblock
{
	short owners;
	short size;
#ifdef _DEBUG
	char *file;
	int   line;
#endif
	struct memblock **me, *next;
#ifdef _DEBUG
	unsigned long start_tag;
#endif
	char data[1];
} MEMBLOCK, *PMEMBLOCK;
PMEMBLOCK root;
int bDisableValidate;
#ifdef VALIDATE
void ValidateMemory( void )
{
	PMEMBLOCK mem = root;
	while( mem )
	{
		if( (mem->start_tag) != 0x12345678 )
		{
#ifdef _DEBUG
			fprintf( stddbg, WIDE("Block %s(%d) underflowed\n"), mem->file, mem->line );
#else
			 fprintf( stddbg, WIDE("Block %p underflowed\n"), mem );
#endif
			g.ErrorCount++;
			exit(g.ErrorCount);
		}
		if( *(long*)(mem->data + mem->size ) != 0x12345678 )
		{
#ifdef _DEBUG
			fprintf( stddbg, WIDE("Block %s(%d) overflowed\n"), mem->file, mem->line );
#else
			 fprintf( stddbg, WIDE("Block %p overflowed\n"), mem );
#endif
			g.ErrorCount++;
			exit(g.ErrorCount);
		}
		mem = mem->next;
	}
}
#endif
void DisableMemoryValidate( int bDisable )
{
	bDisableValidate = bDisable;
}
void *AllocateEx( size_t size DBG_PASS ) {
	PMEMBLOCK mem;
#ifdef VALIDATE
	ValidateMemory();
#endif
	g.nAllocates++;
	g.nAllocSize += size;
#ifdef VALIDATE
//                         long is the type used later
#  define EXTRA_SPACE sizeof( long )
#else
#  define EXTRA_SPACE 0
#endif
	mem = malloc(sizeof(MEMBLOCK) + EXTRA_SPACE + size);
	if( !mem )
	{
#ifdef _DEBUG
		fprintf( stddbg, WIDE("%s(%d) Out of memory.\n"), pFile, nLine );
#else
		fprintf( stddbg, WIDE("Out of memory.\n") );
#endif
		g.ErrorCount++;
		exit(g.ErrorCount);
	}
#ifdef _DEBUG
#ifdef MEMLOG
	if( g.bDebugLog & DEBUG_MEMORY ) {
		fprintf( stddbg, WIDE( "%s(%d): Allocate %zd %p\n" ), pFile, nLine, size, mem->data );
		fflush( stddbg );
	}
#endif
#endif
	if( mem->next = root )
		root->me = &mem->next;
	mem->me = &root;
	root = mem;
	mem->owners = 1;
	mem->size = (short)size;
#ifdef _DEBUG
	mem->file = pFile;
	mem->line = nLine;
#endif
#ifdef VALIDATE
	mem->start_tag = 0x12345678;
	*(long*)(mem->data + size) = 0x12345678;
	if( !bDisableValidate )
	{
		ValidateMemory( );
	}
#endif
	return &mem->data[0];
}
void ReleaseExx( void **pp DBG_PASS ) {
	void *p = *pp;
	PMEMBLOCK mem = (PMEMBLOCK)(((char*)p) - offsetof( MEMBLOCK, data ));
	g.nReleases++;
#ifdef MEMLOG
	if( g.bDebugLog & DEBUG_MEMORY ) {
#ifdef _DEBUG
		fprintf( stddbg, WIDE( "%s(%d): Release %p\n" )
			, pFile, nLine
			, p );
		fprintf( stddbg, WIDE( "%s(%d): %s(%d)Release %p\n" )
			, pFile, nLine
			, mem->file, mem->line
			, p );
		fflush( stddbg );
#else
		fprintf( stddbg, WIDE("Release %lp\n")
			, p );
#endif
	}
#endif
#ifdef VALIDATE
	if( !bDisableValidate )
	{
		ValidateMemory();
	}
#endif
	if( mem->owners != 1 )
	{
		fprintf( stddbg, WIDE("Block %p already free from: %s(%d) - or long ago freed (%d)...")
#ifdef _DEBUG
						" %s(%d)"
#endif
						, p
#ifdef _DEBUG
						, mem->file, mem->line
#endif
						, mem->owners
#ifdef _DEBUG
						, pFile, nLine
#endif
		);
		g.ErrorCount++;
		exit(g.ErrorCount);
	}
#ifdef _DEBUG
#ifdef VALIDATE
	if( ( *(long*)(mem->data + mem->size ) != 0x12345678 ||
		  mem->start_tag != 0x12345678 ) )
	{
		fprintf( stddbg, WIDE("Application overflowed memory.%p(%d) %s(%d)")
				 " %s(%d)"
				, mem->data
				, mem->size
				, mem->file, mem->line
				  DBG_RELAY );
		g.ErrorCount++;
		exit(g.ErrorCount);
	}
#endif
#endif
	if( *mem->me = mem->next )
		mem->next->me = mem->me;
#ifdef _DEBUG
	mem->file = pFile;
	mem->line = nLine;
#endif
	mem->owners = 0;
	free(mem);
	*pp = NULL;
}
void DumpMemory( void )
{
	PMEMBLOCK mem = root;
	while( mem )
	{
		fprintf( stddbg, WIDE("Block: %d %p ")
#ifdef _DEBUG
							"%s(%d)"
#endif
							"\n", mem->size, mem->data
#ifdef _DEBUG
				,mem->file, mem->line
#endif
				 );
		mem = mem->next;
	}
}
void CPROC MemSet( void *p, uint32_t v, size_t n) {memset(p,v,n);}
void CPROC MemCpy( void *p, const void *p2, size_t n) {memcpy(p,p2,n);}
uint32_t LockedExchange( uint32_t *p, uint32_t val )
{
	uint32_t x;
	x = *p;
	*p = val;
	return x;
/*
   long res;
   asm .386;
   asm les di, p;
   asm mov ecx, val;
   asm xchg es:[di], ecx ;
   asm mov res, ecx;
   return res;
*/
}
char *StrDupEx( const char *original DBG_PASS )
{
	size_t len = strlen( original ) + 1;
	char *result = AllocateEx( len DBG_RELAY );
	MemCpy( result, original, len );
	return result;
}
#if defined( __GNUC__ ) && !defined( _WIN32 )
int stricmp( char *one, char *two )
{
	return strcasecmp( one, two );
}
int strnicmp( char *one, char *two, int len )
{
	return strncasecmp( one, two, len );
}
#endif
#if defined( __WINTIME__ )
#endif
#include <time.h>
//#define DEFINE_STDC_VERSION
#define DEBUG_SUBST 0x02
#define DEBUG_DEFINES 0x04
static PDEF pDefineRoot, pCurrentDefine;
  // static symbol....
static DEF DefineLine
 // static symbol....
, DefineFile
 // 199901L
, DefineStdCVersion
        // "00:00:00.000"
, DefineTime
       // "mmm dd, yyyy"
, DefineDate;
static int nDefines;
//----------------------------------------------------------------------
#ifdef _DEBUG
void ValidateTree( PDEF *root )
{
	if( root && *root )
	{
		if( (*root)->me != root )
		{
			fprintf( stderr, WIDE("Invalid linking this->me is not itself!\n") );
			DebugBreak();
		}
		if( (*root)->pGreater )
		{
			if( (*root)->pGreater->me != &(*root)->pGreater )
			{
				fprintf( stderr, WIDE("Invalid linking this->greater does not reference me\n") );
				DebugBreak();
			}
			ValidateTree( &(*root)->pGreater );
		}
		if( (*root)->pLesser )
		{
			if( (*root)->pLesser->me != &(*root)->pLesser )
			{
				fprintf( stderr, WIDE("Invalid linking this->lesser does not reference me\n") );
				DebugBreak();
			}
			ValidateTree( &(*root)->pLesser );
		}
		if( (*root)->pSame )
		{
			if( (*root)->pSame->me != &(*root)->pSame )
			{
				fprintf( stderr, WIDE("Invalid linking this->same does not reference me\n") );
				DebugBreak();
			}
			ValidateTree( &(*root)->pSame );
		}
	}
}
#else
#define ValidateTree(r)
#endif
#define ValidateTree(r)
//----------------------------------------------------------------------
void FixQuoting( PTEXT test )
{
	while( test )
	{
		if( GetText( test )[0] == '\"' )
		{
			PTEXT insert = SegCreateFromText( WIDE("\\") );
			insert->format.spaces = test->format.spaces;
			test->format.spaces = 0;
			SegInsert( insert, test );
		}
		else if( GetText( test )[0] == '\'' )
		{
			PTEXT insert = SegCreateFromText( WIDE("\\") );
			insert->format.spaces = test->format.spaces;
			test->format.spaces = 0;
			SegInsert( insert, test );
		}
		else if( GetText( test )[0] == '\\' )
		{
			PTEXT insert = SegCreateFromText( WIDE("\\") );
			insert->format.spaces = test->format.spaces;
			test->format.spaces = 0;
			SegInsert( insert, test );
		}
		test = NEXTLINE( test );
	}
}
//----------------------------------------------------------------------
void DeleteDefineContent( PDEF p )
{
	if( p->pName )
		LineRelease( p->pName );
	if( p->pData )
		LineRelease( p->pData );
	{
		INDEX idx;
		PTEXT param;
		FORALL( p->pParams, idx, PTEXT, param )
		{
			LineRelease( param );
		}
		DeleteList( p->pParams );
	}
}
//----------------------------------------------------------------------
void DeleteStaticDefines( void )
{
	DeleteDefineContent( &DefineLine );
	DeleteDefineContent( &DefineFile );
#ifdef DEFINE_STDC_VERSION
	DeleteDefineContent( &DefineStdCVersion );
#endif
	DeleteDefineContent( &DefineDate );
	DeleteDefineContent( &DefineTime );
}
//----------------------------------------------------------------------
void InitDefines( void )
{
#if defined( __UNIXTIME__ )
	struct tm tm;
	time_t now;
	now = time( NULL );
	localtime_r( &now, &tm );
#elif defined( __WINTIME__ )
	SYSTEMTIME st;
	GetLocalTime( &st );
#endif
	{
		DECLTEXT( constname, WIDE("__LINE__") );
		DefineLine.pName = (PTEXT)&constname;
		DefineLine.pParams = NULL;
		DefineLine.bUsed = FALSE;
		DefineLine.pLesser = NULL;
		DefineLine.pGreater = NULL;
	}
	{
		DECLTEXT( constname, WIDE("__FILE__") );
		DefineFile.pName = (PTEXT)&constname;
		DefineFile.pParams = NULL;
		DefineFile.bUsed = FALSE;
		DefineFile.pLesser = NULL;
		DefineFile.pGreater = NULL;
	}
	//if( TextIs( pName, WIDE("__TIME__ ") ) ) // hh:mm:ss
	{
		DECLTEXT( constname, WIDE("__TIME__") );
		char time[15];
#if defined( __UNIXTIME__ )
		strftime( time, 15, WIDE("\"%H:%M:%S\""), &tm );
#elif defined( __WINTIME__ )
		snprintf( time, 15, WIDE("\"%2d:%02d:%02d.%03d\"")
				  , st.wHour, st.wMinute
				  , st.wSecond, st.wMilliseconds );
#endif
		DefineTime.pName = (PTEXT)&constname;
		DefineTime.pData = SegCreateFromText( time );
		DefineTime.pData->format.spaces = 1;
		DefineTime.pParams = NULL;
		DefineTime.bUsed = FALSE;
		DefineTime.pLesser = NULL;
		DefineTime.pGreater = NULL;
	}
	//if( TextIs( pName, WIDE("__DATE__ ") ) ) // Mmm dd yyyy dd = ' x' if <10
	{
		DECLTEXT( constname, WIDE("__DATE__") );
		char date[20];
#if defined( __UNIXTIME__ )
		strftime( date, 20, WIDE("\"%b %e %Y\""), &tm );
#elif defined( __WINTIME__ )
		snprintf( date, 20, WIDE("\"%02d/%02d/%04d\"")
				  , st.wMonth, st.wDay, st.wYear );
#endif
		DefineDate.pName = (PTEXT)&constname;
		DefineDate.pData = SegCreateFromText( date );
		DefineDate.pData->format.spaces = 1;
		DefineDate.pParams = NULL;
		DefineDate.bUsed = FALSE;
		DefineDate.pLesser = NULL;
		DefineDate.pGreater = NULL;
	}
	// on GCC - these end up being defined....
	//if( TextIs( pName, WIDE("__STDC__ ") ) ) // 1
	//if( TextIs( pName, WIDE("__STDC_HOSTED__ ") ) ) // ?? what's a hosted?
	// and this - well the compiler itself needs to support this - so
	// this should come in from the
#ifdef DEFINE_STDC_VERSION
	{
		DECLTEXT( constname, WIDE("__STDC_VERSION__") );
		DefineStdCVersion.pParams = NULL;
		DefineStdCVersion.pName = (PTEXT)&constname;
		DefineStdCVersion.pData = SegCreateFromInt( 199901L );
		DefineStdCVersion.pData->format.spaces = 1;
		DefineStdCVersion.bUsed = FALSE;
		DefineStdCVersion.pLesser = NULL;
		DefineStdCVersion.pGreater = NULL;
	}
#endif
}
//----------------------------------------------------------------------
void DeinitDefines( void )
{
	DeleteStaticDefines();
}
//----------------------------------------------------------------------
// if params are negative - the count is -(absolute count)
//
PDEF FindDefineName( PTEXT pName, int params )
{
	PDEF p;
	int levels = 1;
	if( TextIs( pName, WIDE("__LINE__") ) )
	{
		if( DefineLine.pData )
			LineRelease( DefineLine.pData );
		DefineLine.pData = SegCreateFromInt( GetCurrentLine() );
		DefineLine.bUsed = FALSE;
		return &DefineLine;
	}
	else if( TextIs( pName, WIDE("__FILE__") ) )
	{
		VARTEXT vt;
		VarTextInit( &vt );
		if( DefineFile.pData )
			LineRelease( DefineFile.pData );
		//printf( WIDE("Building result: %s\n"), GetCurrentFileName() );
		VarTextAddCharacter( &vt, '\"' );
		VarTextEnd( &vt );
		vtprintf( &vt, WIDE("%s"), GetCurrentShortFileName() );
		VarTextEnd( &vt );
		VarTextAddCharacter( &vt, '\"' );
		DefineFile.pData = VarTextGet( &vt );
		VarTextEmpty( &vt );
		DefineFile.bUsed = FALSE;
		return &DefineFile;
	}
	//if( TextIs( pName, WIDE("__TIME__ ") ) ) // hh:mm:ss
	else if( TextIs( pName, WIDE("__TIME__") ) )
	{
		DefineTime.bUsed = FALSE;
		return &DefineTime;
	}
	//if( TextIs( pName, WIDE("__DATE__ ") ) ) // Mmm dd yyyy dd = ' x' if <10
	else if( TextIs( pName, WIDE("__DATE__") ) )
	{
		DefineDate.bUsed = FALSE;
		return &DefineDate;
	}
	// This is probably compiler specific.... but let's see what
	// happens for now.
#ifdef DEFINE_STDC_VERSION
  // 199901L
	else if( TextIs( pName, WIDE("__STDC_VERSION__") ) )
	{
		return &DefineStdCVersion;
	}
#endif
	// all of these are compiler specific....
	//if( TextIs( pName, WIDE("__STDC__ ") ) ) // 1
	//if( TextIs( pName, WIDE("__STDC_HOSTED__ ") ) ) // ?? what's a hosted?
	//if( TextIs( pName, WIDE("__STDC_IEC_559__ ") ) ) // 1 if conform annex f
	//if( TextIs( pName, WIDE("__STDC_IEC_559_COMPLEX__ ") ) ) // 1 if conform annex g
	//if( TextIs( pName, WIDE("__STDC_ISO_10646__ ") ) ) // 199712L yyyymmL wchar_t encodings
	// do not allow __cplusplus to redefine...
	p = pDefineRoot;
	while( p )
	{
		int d = SameText( pName, p->pName );
		if(  d == 0 )
		{
			// just checking to see if defined...
			if( params == IGNORE_PARAMS &&
				 !p->bUsed )
				return p;
			do
			{
				if( params < 0 )
				{
					// looking for macro with var args...
					if( p->bVarParams &&
						p->pParams->Cnt == -params )
					{
 // same one...
						return p;
					}
				}
				if( p->pParams )
				{
					if( p->pParams->Cnt == params
						|| ( p->bVarParams
						 && ( (int)p->pParams->Cnt <= params ) )
					  )
					{
						if( !p->bUsed )
							return p;
						// otherwise - maybe we can use the next one?
					}
				}
				else if( !params )
				{
					if( !p->bUsed )
						return p;
				}
				p = p->pSame;
			}
			while( p );
			if( p )
				break;
		}
		else if( d > 0 )
			p = p->pGreater;
		else
			p = p->pLesser;
		levels++;
	}
	//if( g.bDebugLog )
	//   fprintf( stderr, WIDE("levels checked for name: %d/%d\n"), levels, nDefines );
	return NULL;
}
//----------------------------------------------------------------------
// inserts pDef where p is, pushing p to be under pDef as pSame
void InsertDefine( PDEF pDef, PDEF p )
{
	*p->me = pDef;
	pDef->me = p->me;
	if( pDef->pGreater = p->pGreater )
		pDef->pGreater->me = &pDef->pGreater;
	if( pDef->pLesser = p->pLesser )
		pDef->pLesser->me = &pDef->pLesser;
	pDef->pSame = p;
	p->me = &pDef->pSame;
	p->pGreater = NULL;
	p->pLesser = NULL;
}
//----------------------------------------------------------------------
void HangNode( PDEF *root, PDEF pDef );
void DeleteDefine( PDEF *ppDef )
{
	if( ppDef && *ppDef )
	{
		PDEF pDef = *ppDef;
		PDEF tmp;
		// this ends up clearing &pDef usually....
		tmp = pDef;
		// take me out of the tree...
		*pDef->me = NULL;
		if( pDef->pSame )
		{
			pDef->pSame->me = NULL;
			HangNode( &pDefineRoot, pDef->pSame );
			pDef->pSame = NULL;
		}
		if( pDef->pLesser )
		{
			pDef->pLesser->me = NULL;
			HangNode( &pDefineRoot, pDef->pLesser );
			pDef->pLesser = NULL;
		}
		if( pDef->pGreater )
		{
			pDef->pGreater->me = NULL;
			HangNode( &pDefineRoot, pDef->pGreater );
			pDef->pGreater = NULL;
		}
		DeleteDefineContent( pDef );
		Release( tmp );
		ValidateTree( &pDefineRoot );
		nDefines--;
	}
}
//----------------------------------------------------------------------
void HangNode( PDEF *root, PDEF pDef )
{
	PDEF p, prior = NULL;
	if( !pDef )
		return;
	// allow definition of internal __DATE__ and __TIME__
	if( TextIs( pDef->pName, WIDE("__DATE__") ) )
	{
		if( pDef->nType == DEFINE_COMMANDLINE )
		{
			LineRelease( DefineDate.pData );
			DefineDate.pData = pDef->pData;
			pDef->pData = NULL;
			DeleteDefine( &pDef );
		}
		else
		{
			fprintf( stderr, WIDE("%s(%d): May only define __DATE__ from a command line parameter\n")
					 , GetCurrentFileName()
					 , GetCurrentLine()
					 );
			DeleteDefine( &pDef );
		}
		return;
	}
	else if( TextIs( pDef->pName, WIDE("__TIME__") ) )
	{
		if( pDef->nType == DEFINE_COMMANDLINE )
		{
			LineRelease( DefineTime.pData );
			DefineTime.pData = pDef->pData;
			pDef->pData = NULL;
			DeleteDefine( &pDef );
		}
		else
		{
			fprintf( stderr, WIDE("%s(%d): May only define __TIME__ from a command line parameter\n")
					 , GetCurrentFileName()
					 , GetCurrentLine()
					 );
			DeleteDefine( &pDef );
		}
		return;
	}
	if( !*root )
	{
		*root = pDef;
		pDef->me = root;
		ValidateTree( &pDefineRoot );
		return;
	}
	p = *root;
	while( p )
	{
		int d = SameText( pDef->pName, p->pName );;
		if( d > 0 )
		{
			if( !p->pGreater )
			{
				pDef->me = &p->pGreater;
				p->pGreater = pDef;
				ValidateTree( &pDefineRoot );
				return;
			}
			else
			{
				prior = p;
				p = p->pGreater;
			}
		}
		else if( d < 0 )
		{
			if( !p->pLesser )
			{
				pDef->me = &p->pLesser;
				p->pLesser = pDef;
				ValidateTree( &pDefineRoot );
				return;
			}
			else
			{
				prior = p;
				p = p->pLesser;
			}
		}
		else
		{
			if( pDef->pParams )
  // has parameters () - may be 0, but still...
			{
				// nparams...
				do
				{
					if( p->pParams )
					{
						if( pDef->pParams->Cnt < p->pParams->Cnt )
						{
							InsertDefine( pDef, p );
							ValidateTree( &pDefineRoot );
							return;
						}
						else if( pDef->pParams->Cnt == p->pParams->Cnt )
						{
							if( p->bVarParams )
							{
								if( pDef->bVarParams )
								{
									fprintf( stderr, WIDE("%s(%d): Error attempt to redefine macro %s defined at %s(%d).\n")
											  , GetCurrentFileName()
											  , GetCurrentLine()
											  , GetText( pDef->pName )
											  , p->pFile, p->nLine );
									g.ErrorCount++;
									DeleteDefine( &pDef );
									ValidateTree( &pDefineRoot );
									return;
								}
								InsertDefine( pDef, p );
								ValidateTree( &pDefineRoot );
								return;
							}
							else
							{
								if( !pDef->bVarParams )
								{
									fprintf( stderr, WIDE("%s(%d): Error attempt to redefine macro %s defined at %s(%d).\n")
											  , GetCurrentFileName()
											  , GetCurrentLine()
											  , GetText( pDef->pName )
											  , p->pFile, p->nLine );
									g.ErrorCount++;
									DeleteDefine( &pDef );
									ValidateTree( &pDefineRoot );
									return;
								}
								// else step to next ( need to add after this)
							}
						}
					}
					prior = p;
					p = p->pSame;
				} while( p );
				pDef->me = &prior->pSame;
				prior->pSame = pDef;
				ValidateTree( &pDefineRoot );
				return;
			}
			else
			{
				// no paramters - symbol alone...
				if( !p->pParams )
				{
					/*
					if( !pDef->pParams )
					{
						fprintf( stderr, WIDE("%s(%d): WARNING Attempt to Redefine macro with no params - failed.!\n")
								, GetCurrentFileName()
								, GetCurrentLine() );
						DeleteDefine( &pDef );
						ValidateTree( &pDefineRoot );
						return;
					}
					else
					*/
						fprintf( stderr, WIDE("%s(%d): WARNING Redefining macro \'%s\'(overloading name alone with params)!\n")
								, GetCurrentFileName()
								, GetCurrentLine()
								, GetText( pDef->pName )
								);
				}
				InsertDefine( pDef, p );
				ValidateTree( &pDefineRoot );
				return;
			}
		}
	}
}
//----------------------------------------------------------------------
void DeleteDefineTree( PDEF *ppRoot, int type )
{
	if( ppRoot && *ppRoot )
	{
		PDEF root = *ppRoot;
		DeleteDefineTree( &(root->pLesser), type );
		DeleteDefineTree( &(root->pGreater), type );
		DeleteDefineTree( &(root->pSame), type );
		if( type == DEFINE_ALL ||
			 root->nType == type )
			DeleteDefine( ppRoot );
		ValidateTree( &pDefineRoot );
	}
}
//----------------------------------------------------------------------
void DeleteAllDefines( int type )
{
	// uhmm this works - but it's hideous...
	// should do something like delete bottom up
	DeleteDefineTree( &pDefineRoot, type );
}
//----------------------------------------------------------------------
void DefineDefine( char *name, char *value )
{
	PDEF pDefine = Allocate( sizeof( DEF ) );
	MemSet( pDefine, 0, sizeof( DEF ) );
	pDefine->nType = DEFINE_COMMANDLINE;
	pDefine->pName = SegCreateFromText( name );
	pDefine->pData = SegCreateFromText( value );
	if( pDefine->pData )
		pDefine->pData->format.spaces = 1;
	HangNode( &pDefineRoot, pDefine );
}
//----------------------------------------------------------------------
int ProcessDefine( int type )
{
	//PTEXT def;
	if( !pCurrentDefine )
	{
		PTEXT pWord = GetCurrentWord();
		if( TextIs( pWord, WIDE("__LINE__") )
			|| TextIs( pWord, WIDE("__FILE__") )
#ifdef DEFINE_STDC_VERSION
			|| TextIs( pWord, WIDE("__STDC_VERSION__") )
#endif
		  )
			 // none of the above constants mentioned may be redefined
			 // nor 'defined'
		{
			if( g.bDebugLog )
			{
				fprintf( stddbg, WIDE("%s(%d) Warning: Cannot define predefined symbols.")
									, GetCurrentFileName(), GetCurrentLine() );
			}
			fprintf( stderr, WIDE("%s(%d) Warning: Cannot define predefined symbols.")
								, GetCurrentFileName(), GetCurrentLine() );
 // just a warning
			return TRUE;
		}
		pCurrentDefine = Allocate( sizeof( DEF ) );
		MemSet(pCurrentDefine, 0, sizeof( DEF ) );
		strcpy( pCurrentDefine->pFile, GetCurrentFileName() );
		pCurrentDefine->nLine = GetCurrentLine();
		pCurrentDefine->nType = type;
		pWord = GetCurrentWord();
		if( g.bDebugLog & DEBUG_DEFINES )
		{
			fprintf( stddbg, WIDE("%s(%d) Defining macro: %s\n")
							, GetCurrentFileName(), GetCurrentLine()
							, GetText( pWord ) );
		}
		pCurrentDefine->pName = SegDuplicate( pWord );
		if( ( NEXTLINE( pWord ) &&
			 ( NEXTLINE( pWord )->format.spaces == 0 ) ) )
		{
			pWord = StepCurrentWord();
			if( GetText( pWord )[0] == '(' )
			{
				// these parameters are macros vars for define...
				// required count....
				pCurrentDefine->pParams = CreateList();
				StepCurrentWord();
				while( ( pWord = GetCurrentWord() ) &&
						 GetText( pWord )[0] != ')' )
				{
					if( GetText( pWord )[0] != ',' )
					{
						if( TextIs( pWord, WIDE("...") ) )
						{
							if( g.bDebugLog & DEBUG_DEFINES )
								fprintf( stderr, WIDE("Adding var args...\n") );
							if( pCurrentDefine->bVarParams )
							{
								fprintf( stderr, WIDE("%s(%d): Duplicate \'...\' used in define definition.\n")
											, GetCurrentFileName()
											, GetCurrentLine() );
							}
							else
								pCurrentDefine->bVarParams = TRUE;
						}
						else
						{
							PTEXT param = NULL;
							INDEX idx;
							if( !pCurrentDefine->bVarParams )
							{
								if( g.bDebugLog & DEBUG_DEFINES )
									fprintf( stddbg, WIDE("Adding argument: %s\n"), GetText( pWord ) );
								FORALL( pCurrentDefine->pParams, idx, PTEXT, param )
								{
									if( SameText( param, pWord ) == 0 )
									{
										fprintf( stderr, WIDE("%s(%d): Error same parameter name defined twice.\n")
												 , GetCurrentFileName()
												 , GetCurrentLine() );
										g.ErrorCount++;
									}
 // have to manual reset this...
									param = NULL;
								}
								if( !param )
								{
									AddLink( pCurrentDefine->pParams
											 , SegDuplicate( pWord ) );
								}
								else if( g.bDebugLog & DEBUG_DEFINES )
									fprintf( stddbg, WIDE("Parameter already existed????\n") );
							}
							else
							{
								fprintf( stderr, WIDE("%s(%d): regular parameters are not allowed to follow var args (...)\n")
										 , GetCurrentFileName()
										 , GetCurrentLine() );
							}
						}
					}
					StepCurrentWord();
				}
			}
		}
		  StepCurrentWord();
	}
	//----------------
	// add data to the current macro here...
	//----------------
	if( GetCurrentWord() )
	{
		PTEXT p;
		p = GetCurrentWord();
		while( p )
		{
			PTEXT newseg = SegDuplicate( p );
			if( p == GetCurrentWord() )
				newseg->format.spaces = 0;
			pCurrentDefine->pData = SegAppend( pCurrentDefine->pData
													  , newseg );
			p = NEXTLINE(p);
		}
		pCurrentDefine->pData->format.spaces = 0;
	}
	if( g.bDebugLog & DEBUG_DEFINES )
	{
		PTEXT out = BuildLine( pCurrentDefine->pData );
		fprintf( stddbg, WIDE("Define %s == %s\n"), GetText( pCurrentDefine->pName ), GetText( out ) );
		LineRelease( out );
	}
	if( g.bDebugLog & DEBUG_SUBST )
	{
		fprintf( stddbg, WIDE("searching for %s(%zd) ...\n")
				 ,GetText( pCurrentDefine->pName)
				 , pCurrentDefine->pParams
				  ? pCurrentDefine->bVarParams
				  ?-(int)pCurrentDefine->pParams->Cnt
				  :pCurrentDefine->pParams->Cnt
				  : 0
				);
	}
	{
		PDEF pOld = FindDefineName( pCurrentDefine->pName
										  , pCurrentDefine->pParams
											? pCurrentDefine->bVarParams
											?-(int)pCurrentDefine->pParams->Cnt
											:(int)pCurrentDefine->pParams->Cnt
											: 0 );
		if( pOld )
		{
			if( g.flags.bAllWarnings )
				fprintf( stderr, WIDE("%s(%d) Warning: redefining symbol: %s Previously defined at %s(%d).\n")
						, GetCurrentFileName(), GetCurrentLine()
						, GetText( pCurrentDefine->pName )
						, pOld->pFile, pOld->nLine );
			DeleteDefine( &pOld );
		}
		//else if( g.bDebugLog )
		//{
		//	fprintf( stderr, WIDE("Symbol not found - continue normall.\n") );
		//}
	}
	// completed the macro definition here....
	nDefines++;
	HangNode( &pDefineRoot, pCurrentDefine );
	pCurrentDefine = NULL;
	if( g.bDebugLog & DEBUG_DEFINES )
		fprintf( stddbg, WIDE("done with define...\n") );
	return TRUE;
}
//----------------------------------------------------------------------
PTEXT BuildSizeofArgs( PTEXT args )
{
	PTEXT arg = NULL
		 , trinary_then = NULL
		 , trinary_else = NULL;
	PTEXT result = NULL;
	char *text;
	int quote = 0
	  , paren = 0
	  , trinary_collect_then = 0
	  , trinary_collect_else = 0;
	for( ; args; args = NEXTLINE( args ) )
	{
		text = GetText( args );
		if( !quote )
		{
			if( text[0] == '\"' ||
				text[0] == '\'' )
			{
				quote = text[0];
				continue;
			}
			if( text[0] == '(' )
				paren++;
			else if( text[0] == ')' )
				paren--;
			if( paren )
			{
				if( trinary_collect_else )
					trinary_else = SegAppend( trinary_else, SegDuplicate( args ) );
				else if( trinary_collect_then )
					trinary_then = SegAppend( trinary_then, SegDuplicate( args ) );
				else
					arg = SegAppend( arg, SegDuplicate( args ) );
				continue;
			}
			if( text[0] == '?' )
			{
				trinary_collect_then = 1;
				continue;
			}
			if( trinary_collect_then && text[0] == ':' )
			{
				trinary_collect_else = 1;
				continue;
			}
		}
 // in quote...
		else
		{
			if( text[0] == quote )
			{
				if( trinary_collect_else )
					trinary_else = SegAppend( trinary_else, SegCreateFromText( WIDE("char*") ) );
				else if( trinary_collect_then )
					trinary_then = SegAppend( trinary_then, SegCreateFromText( WIDE("char*") ) );
				else
					arg = SegAppend( arg, SegCreateFromText( WIDE("char*") ) );
				quote = 0;
			}
			continue;
		}
		if( text[0] == ',' )
		{
			PTEXT out = arg;
			PTEXT tmp;
			trinary_collect_else = 0;
			trinary_collect_then = 0;
			vtprintf( &g.vt, WIDE("(") );
			VarTextEnd( &g.vt );
			vtprintf( &g.vt , WIDE(" ( (") );
			VarTextEnd( &g.vt );
			if( trinary_then && trinary_else )
			{
				vtprintf( &g.vt , WIDE(" ( sizeof( ") );
				VarTextEnd( &g.vt );
				out = trinary_then;
				while( out )
				{
					vtprintf( &g.vt, WIDE("%s"), GetText( out ) );
					tmp = VarTextEnd( &g.vt );
					tmp->flags |= out->flags & TF_NOEXPAND;
					tmp->format.spaces = out->format.spaces;
					out = NEXTLINE( out );
				}
				vtprintf( &g.vt, WIDE(" ) > ") );
				VarTextEnd( &g.vt );
				vtprintf( &g.vt , WIDE("sizeof( ") );
				VarTextEnd( &g.vt );
				out = trinary_else;
				while( out )
				{
					vtprintf( &g.vt, WIDE("%s"), GetText( out ) );
					tmp = VarTextEnd( &g.vt );
					tmp->flags |= out->flags & TF_NOEXPAND;
					tmp->format.spaces = out->format.spaces;
					out = NEXTLINE( out );
				}
				vtprintf( &g.vt, WIDE(" ) ? ") );
				VarTextEnd( &g.vt );
				vtprintf( &g.vt , WIDE("sizeof( ") );
				VarTextEnd( &g.vt );
				out = trinary_then;
				while( out )
				{
					vtprintf( &g.vt, WIDE("%s"), GetText( out ) );
					tmp = VarTextEnd( &g.vt );
					tmp->flags |= out->flags & TF_NOEXPAND;
					tmp->format.spaces = out->format.spaces;
					out = NEXTLINE( out );
				}
				vtprintf( &g.vt, WIDE(" ) : ") );
				VarTextEnd( &g.vt );
				vtprintf( &g.vt , WIDE("sizeof( ") );
				VarTextEnd( &g.vt );
				out = trinary_else;
				while( out )
				{
					vtprintf( &g.vt, WIDE("%s"), GetText( out ) );
					tmp = VarTextEnd( &g.vt );
					tmp->flags |= out->flags & TF_NOEXPAND;
					tmp->format.spaces = out->format.spaces;
					out = NEXTLINE( out );
				}
				vtprintf( &g.vt, WIDE(" ) ) ") );
				VarTextEnd( &g.vt );
				LineRelease( trinary_then );
				LineRelease( trinary_else );
				// would be the 'if' part of this expression - unused.
				LineRelease( arg );
			}
			else
			{
				if( ( trinary_then && !trinary_else )
					|| ( !trinary_then && trinary_else ) )
				{
					fprintf( stderr, WIDE("%s(%d): Badly formed trinary operator!\n")
							, GetCurrentFileName()
							, GetCurrentLine() );
					LineRelease( trinary_then );
					LineRelease( trinary_else );
				}
				vtprintf( &g.vt , WIDE(" sizeof( ") );
				VarTextEnd( &g.vt );
				out = arg;
				while( out )
				{
					vtprintf( &g.vt, WIDE("%s"), GetText( out ) );
					tmp = VarTextEnd( &g.vt );
					tmp->flags |= out->flags & TF_NOEXPAND;
					tmp->format.spaces = out->format.spaces;
					out = NEXTLINE( out );
				}
				vtprintf( &g.vt, WIDE(")") );
				VarTextEnd( &g.vt );
				LineRelease( arg );
			}
			vtprintf( &g.vt, WIDE(" + 3 ) / 4 ) * 4 ") );
			VarTextEnd( &g.vt );
			vtprintf( &g.vt, WIDE(")") );
			VarTextEnd( &g.vt );
			vtprintf( &g.vt, WIDE("+") );
			VarTextEnd( &g.vt );
			result = SegAppend( result, VarTextGet( &g.vt ) );
		}
		else
		{
			if( trinary_collect_else )
				trinary_else = SegAppend( trinary_else, SegDuplicate( args ) );
			else if( trinary_collect_then )
				trinary_then = SegAppend( trinary_then, SegDuplicate( args ) );
			else
				arg = SegAppend( arg, SegDuplicate( args ) );
		}
	}
	if( arg )
	{
		{
			PTEXT out = arg;
			PTEXT tmp;
			vtprintf( &g.vt, WIDE("(") );
			VarTextEnd( &g.vt );
			vtprintf( &g.vt , WIDE(" ( (") );
			VarTextEnd( &g.vt );
			if( trinary_then && trinary_else )
			{
				vtprintf( &g.vt , WIDE(" ( sizeof( ") );
				VarTextEnd( &g.vt );
				out = trinary_then;
				while( out )
				{
					vtprintf( &g.vt, WIDE("%s"), GetText( out ) );
					tmp = VarTextEnd( &g.vt );
					tmp->flags |= out->flags & TF_NOEXPAND;
					tmp->format.spaces = out->format.spaces;
					out = NEXTLINE( out );
				}
				vtprintf( &g.vt, WIDE(" ) > ") );
				VarTextEnd( &g.vt );
				vtprintf( &g.vt , WIDE("sizeof( ") );
				VarTextEnd( &g.vt );
				out = trinary_else;
				while( out )
				{
					vtprintf( &g.vt, WIDE("%s"), GetText( out ) );
					tmp = VarTextEnd( &g.vt );
					tmp->flags |= out->flags &TF_NOEXPAND;
					tmp->format.spaces = out->format.spaces;
					out = NEXTLINE( out );
				}
				vtprintf( &g.vt, WIDE(" ) ? ") );
				VarTextEnd( &g.vt );
				vtprintf( &g.vt , WIDE("sizeof( ") );
				VarTextEnd( &g.vt );
				out = trinary_then;
				while( out )
				{
					vtprintf( &g.vt, WIDE("%s"), GetText( out ) );
					tmp = VarTextEnd( &g.vt );
					tmp->flags |= out->flags & TF_NOEXPAND;
					tmp->format.spaces = out->format.spaces;
					out = NEXTLINE( out );
				}
				vtprintf( &g.vt, WIDE(" ) : ") );
				VarTextEnd( &g.vt );
				vtprintf( &g.vt , WIDE("sizeof( ") );
				VarTextEnd( &g.vt );
				out = trinary_else;
				while( out )
				{
					vtprintf( &g.vt, WIDE("%s"), GetText( out ) );
					tmp = VarTextEnd( &g.vt );
					tmp->flags |= out->flags & TF_NOEXPAND;
					tmp->format.spaces = out->format.spaces;
					out = NEXTLINE( out );
				}
				vtprintf( &g.vt, WIDE(" ) ) ") );
				VarTextEnd( &g.vt );
				LineRelease( trinary_then );
				LineRelease( trinary_else );
				// would be the 'if' part of this expression - unused.
				LineRelease( arg );
			}
			else
			{
				if( ( trinary_then && !trinary_else )
					|| ( !trinary_then && trinary_else ) )
				{
					fprintf( stderr, WIDE("%s(%d): Badly formed trinary operator!\n")
							, GetCurrentFileName()
							, GetCurrentLine() );
					LineRelease( trinary_then );
					LineRelease( trinary_else );
				}
				vtprintf( &g.vt , WIDE(" sizeof( ") );
				VarTextEnd( &g.vt );
				out = arg;
				while( out )
				{
					vtprintf( &g.vt, WIDE("%s"), GetText( out ) );
					tmp = VarTextEnd( &g.vt );
					tmp->flags |= out->flags & TF_NOEXPAND;
					tmp->format.spaces = out->format.spaces;
					out = NEXTLINE( out );
				}
				vtprintf( &g.vt, WIDE(" )") );
				VarTextEnd( &g.vt );
			}
			vtprintf( &g.vt, WIDE(" + 3 ) / 4 ) * 4 ") );
			VarTextEnd( &g.vt );
			vtprintf( &g.vt, WIDE(")") );
			VarTextEnd( &g.vt );
			//vtprintf( &g.vt, WIDE("+") );
			//VarTextEnd( &g.vt );
			LineRelease( arg );
			result = SegAppend( result, VarTextGet( &g.vt ) );
			arg = NULL;
		}
	}
	else
		result = SegAppend( result, SegCreateFromInt( 0 ) );
	return result;
}
//----------------------------------------------------------------------
INDEX FindArg( PLIST pArgs, PTEXT pName )
{
	INDEX i;
	PTEXT pTest;
	if( TextIs( pName, WIDE("...") )
		|| TextIs( pName, WIDE("__VA_ARGS__") )
		|| TextIs( pName, WIDE("__SZ_ARGS__") ) )
	{
		return pArgs->Cnt;
	}
	FORALL( pArgs, i, PTEXT, pTest )
	{
		if( SameText( pName, pTest ) == 0 )
		{
			return i;
		}
	}
	return INVALID_INDEX;
}
void EmptyArgList( PLIST *pArgVals )
{
	INDEX idx;
	PTEXT pDelete;
	FORALL( *pArgVals, idx, PTEXT, pDelete )
	{
		LineRelease( pDelete );
	}
	DeleteListEx( pArgVals DBG_SRC );
}
//----------------------------------------------------------------------
PDEF AddArgumentEx( PLIST *pArgVals, PTEXT *pVal, INDEX *pi, PDEF pDefine, int *pbVarArg DBG_PASS )
#define AddArgument(pav,v,i,d,bva) AddArgumentEx(pav,v,i,d,bva DBG_SRC)
{
	if( !*pbVarArg )
	{
		while( *pi >= pDefine->pParams->Cnt &&
				pDefine->pSame )
		{
			if( g.bDebugLog & DEBUG_SUBST )
				fprintf( stddbg, WIDE("Attempting to find a define with more arguments...\n") );
			pDefine = pDefine->pSame;
		}
		if( *pi >= pDefine->pParams->Cnt )
		{
			if( g.bDebugLog & DEBUG_SUBST )
				fprintf( stddbg, WIDE("Too many paramters for %s (%zd of %zd) - try var arg\n")
						 , GetText( pDefine->pName )
						 , *pi, pDefine->pParams->Cnt );
			if( !pDefine->bVarParams )
			{
				fprintf( stderr, WIDE("%s(%d): Warning: excessive parameters to macro... resulting no replacement\n")
						 , GetCurrentFileName(), GetCurrentLine() );
				EmptyArgList( pArgVals );
				return NULL;
			}
			if( g.bDebugLog & DEBUG_SUBST )
				fprintf( stddbg, WIDE("okay and vararg it is!\n") );
			if( !(*pbVarArg) )
			{
				*pbVarArg = 1;
				*pi = pDefine->pParams->Cnt;
				return pDefine;
			}
		}
	}
	if( GetLinkEx( pArgVals, *pi ) )
		fprintf( stderr, WIDE("Overwriting exisitng parameter with new parameter?!") );
	SetLinkEx( pArgVals, *pi, *pVal DBG_RELAY );
	*pVal = NULL;
	if( !*pbVarArg )
		(*pi)++;
	return pDefine;
}
	//----------------------------------------------------------------------
void EvalSubstitutions( PTEXT *subst, int more )
{
	// pWord may be associated with parameters...
	// EvanSubst( &"min(a,b)" ) or basically...
	PTEXT pStart, pWord, pReset;
	PDEF pDefine;
	int Quote = 0, Escape = 0;
	static int nSubstLevel;
	// get word first....
	if( !subst || !*subst )
		return;
	nSubstLevel++;
	if( g.bDebugLog & DEBUG_SUBST )
	{
		fprintf( stderr, WIDE("Looking to substitute:") );
		DumpSegs( *subst );
		fprintf( stderr, WIDE("\n") );
	}
	// start at the beginning of all symbols...
	for( pWord = *subst;
		 //= GetCurrentWord();
		  pWord;
		  pWord = pReset )
	{
		pReset = NEXTLINE( pWord );
		if( pWord->flags & (TF_INDIRECT|TF_NOEXPAND) )
			continue;
		if( Quote )
		{
			if( !Escape )
			{
				if( GetText( pWord )[0] == '\\' )
				{
					Escape = TRUE;
					continue;
				}
			}
			else
			{
				Escape = FALSE;
				continue;
			}
			if( GetText( pWord )[0] == Quote )
				Quote = 0;
			continue;
		}
		//fprintf( stderr, WIDE("Word is: %s\n"), GetText(pWord) );
	if( GetText( pWord )[0] == '\'' ||
		 GetText( pWord )[0] == '\"' )
	{
		Quote = GetText( pWord )[0];
		continue;
	}
		if( TextIs( pWord, WIDE("defined") ) )
		{
			PTEXT pNewWord = NULL, pEnd;
			pStart = pWord;
			pEnd = pWord = NEXTLINE( pWord );
			if( pWord &&
				 GetText( pWord )[0] == '(' )
			{
				pWord = NEXTLINE( pWord );
				if( pWord &&
					 GetText( pWord )[0] != ')' )
				{
					if( FindDefineName( pWord, IGNORE_PARAMS ) )
					{
						pNewWord = SegCreateFromText( WIDE("1") );
						pNewWord->format.spaces = pStart->format.spaces;
					}					else
					{
						pNewWord = SegCreateFromText( WIDE("0") );
						pNewWord->format.spaces = pStart->format.spaces;
					}
					pWord = NEXTLINE( pWord );
					if( GetText( pWord )[0] != ')' )
					{
						fprintf( stderr, WIDE("%s(%d): Error in parameter to 'defined' - more than one symbol?\n")
							 , GetCurrentFileName(), GetCurrentLine() );
						g.ErrorCount++;
					}
					pEnd = pWord;
				}
				else
				{
					fprintf( stderr, WIDE("%s(%d): Empty paranthesis to defined.\n")
							 , GetCurrentFileName(), GetCurrentLine() );
				}
			}
			else
			{
				if( pWord )
				{
					if( FindDefineName( pWord, IGNORE_PARAMS ) )
					{
						pNewWord = SegCreateFromText( WIDE("1") );
						pNewWord->format.spaces = pStart->format.spaces;
					}
					else
					{
						pNewWord = SegCreateFromText( WIDE("0") );
						pNewWord->format.spaces = pStart->format.spaces;
					}
				}
				else
					fprintf( stderr, WIDE("%s(%d): defined used with no parameter (last thing on line)\n")
							 , GetCurrentFileName(), GetCurrentLine() );
			}
			// okay having evaluated defined... do subst on that.
			if( pNewWord )
			{
				PTEXT pOrigin = pStart;
				pNewWord->flags |=TF_NOEXPAND;
				SegSubstRange( &pStart, pEnd, pNewWord );
 // already have a good idea that 0/1 will not subst...
				pReset = NEXTLINE( pNewWord );
				if( pOrigin == *subst )
				{
					if( g.bDebugLog & DEBUG_SUBST )
					{
						fprintf( stddbg, WIDE("Resetitng line begin 1\n") );
					}
					*subst = pNewWord;
				}
			}
			else
			{
				PTEXT pOrigin = pStart;
				pReset = NEXTLINE( pEnd );
				SegSubstRange( &pStart, pEnd, NULL );
				if( pOrigin == *subst )
				{
					if( g.bDebugLog & DEBUG_SUBST )
					{
						fprintf( stddbg, WIDE("Resetitng line begin 2\n") );
					}
					*subst = pReset;
				}
			}
			continue;
		}
		if( g.bDebugLog & DEBUG_SUBST )
		{
			fprintf( stddbg, WIDE("%s(%d): Consider word: %s next: %s\n")
					, GetCurrentFileName(), GetCurrentLine()
					, GetText( pWord )
					, GetText( NEXTLINE( pWord ) ) );
		}
 // mark this is the first word we're grabbing
		pStart = pWord;
		// just check to see if this word is anything defined
		// then later get the actual define for pDefine...
 // look up this symbol
		pDefine = FindDefineName( pWord, IGNORE_PARAMS );
 // if we found the name as a symbol...
		if( pDefine && !pDefine->bUsed )
		{
			PTEXT pSubst = NULL, p;
			PLIST pArgVals = NULL;
			if( g.bDebugLog & DEBUG_SUBST )
			{
				fprintf( stddbg, WIDE("Found substitution for %s params:%p\n"), GetText( pWord ), pDefine->pParams );
			}
			// don't use it yet....
			//pDefine->bUsed = TRUE;
			// does the define expect parameters?
			if( pDefine->pParams )
			{
				INDEX i = 0;
				int bVarArg = 0;
				int bNoArgs = 1;
				PTEXT pVal = NULL;
				char *file_start;
				int line_start;
				file_start = GetCurrentFileName();
				line_start = GetCurrentLine();
				if( !NEXTLINE( pWord ) && more )
					pReset = pWord = ReadLine( TRUE );
				else
					pWord = NEXTLINE( pWord );
				if( !pWord ||
					 GetText( pWord )[0] != '(' )
				{
					if( g.flags.bAllWarnings )
						fprintf( stderr, WIDE("%s(%d) Warning: No parameters for macro defined at %s(%d)\n")
								, GetCurrentFileName(), GetCurrentLine()
								, pDefine->pFile, pDefine->nLine
								 );
					continue;
				}
				// step to the next word after the leading (
				pWord = NEXTLINE( pWord );
				// need to gather the parameters specified
				// then find the right define result for number of paramters...
				while(1)
				{
					int quote = 0;
					int parenlevels = 0;
					int escape = 0;
					char *text;
					while( pWord || ( more && ( pWord = ReadLine( TRUE ) ) ) )
					{
						// while I have a word, get the text for the word,
						// if quote levels or paren levels continue collection
						// or if it's not a ','
						//fprintf( stddbg, WIDE(" stuff... %08x %08x %s\n"), pWord, GetText( pWord ), GetText( pWord ) );
						text = GetText( pWord );
						//fprintf( stddbg, WIDE("Consider word: %s\n"), text );
						if( !quote )
						{
							if( text[0] == '\"' || text[0] == '\'' )
								quote = text[0];
							if( ( text[0] == '(' )
 // otherwise we can assume the paring paren is included...
								&& ( GetTextSize( pWord ) == 1 ) )
							{
								parenlevels++;
							}
							else if( text[0] == ')' )
							{
								// last paren?
								if( !parenlevels )
									break;
								parenlevels--;
							}
							else if( !parenlevels && text[0] == ',' )
							{
								bNoArgs = FALSE;
								if( !bVarArg )
									break;
							}
						}
 // is quote
						else
						{
							if( !escape )
							{
								if( text[0] == '\\' )
									escape = TRUE;
								else if( text[0] == quote )
									quote = 0;
							}
 // was escape
							else
 // next character of course clears this
								escape = FALSE;
						}
						{
							PTEXT tmp = SegDuplicate(pWord);
							pVal = SegAppend( pVal, tmp );
							bNoArgs = FALSE;
						}
						pWord = NEXTLINE( pWord );
					}
					if( !pWord )
					{
						fprintf( stderr, WIDE("%s(%d): Error: Ran out of file data before end of macro params\n")
								 , GetCurrentFileName(), GetCurrentLine() );
						if( quote )
						{
							fprintf( stderr, WIDE("%s(%d) Error: Unterminated string - out of input.\n")
									 , GetCurrentFileName(), GetCurrentLine() );
							g.ErrorCount++;
							quote = 0;
						}
						if( parenlevels )
						{
							fprintf( stderr, WIDE("%s(%d) Error: Unterminated parenthized expression - out of input.\n")
									 , GetCurrentFileName(), GetCurrentLine() );
							g.ErrorCount++;
							parenlevels = 0;
						}
						EmptyArgList( &pArgVals );
						if( pVal )
							LineRelease( pVal );
						return;
					}
						//if( !bVarArg && text[0] == ',' )
						//{
						//	 pWord = NEXTLINE( pWord );
						//	if( !pWord )
						//      pWord = ReadLine( TRUE );
						//break; // end the read/gather loop also...
						//}
						//}
					if( GetText( pWord )[0] == ')' )
						break;
					if( !bVarArg )
					{
						if( pVal )
						{
							pVal->format.spaces = 0;
							if( g.bDebugLog & DEBUG_SUBST )
							{
								PTEXT tmp = BuildLine( pVal );
								fprintf( stddbg, WIDE("Adding parameter: %s\n"), GetText( tmp ) );
								LineRelease( tmp );
							}
						}
						else
						{
							if( g.bDebugLog & DEBUG_SUBST )
							{
								fprintf( stddbg, WIDE("Adding blank(empty,NIL) parameter\n") );
							}
						}
						//if( pVal )
						//{
							pDefine = AddArgument( &pArgVals, &pVal, &i, pDefine, &bVarArg );
							if( !pDefine )
							{
								if( pVal )
									LineRelease( pVal );
								return;
							}
							if( bVarArg && pVal )
								pVal = SegAppend( pVal, SegDuplicate( pWord ) );
						//}
					}
					else
					{
 // otherwise we'll have already collected the var arg in pVal...
						break;
					}
					pWord = NEXTLINE( pWord );
				}
				if( !bNoArgs )
				{
					// var args value is dangling when the above loop ends.
					//if( !pDefine->bVarParams )
					//{
					//   fprintf( stderr, WIDE("Adding var arg parameter to a macro without var args?\n") );
					//}
					if( pVal )
						pVal->format.spaces = 0;
					pDefine = AddArgument( &pArgVals, &pVal, &i, pDefine, &bVarArg );
					if( !pDefine )
					{
						if( pVal )
							LineRelease( pVal );
						return;
					}
					if( pVal )
						pDefine = AddArgument( &pArgVals, &pVal, &i, pDefine, &bVarArg );
					if( pVal )
						fprintf( stderr, WIDE("BLAH! Still have a parametner...\n") );
				}
				// hmm at this point the pDefine is auto updated as we find more arguments...
				// assuming that there have been a legal ordering of macros declared....
				//pDefine = FindDefineName( pDefine->pName
				//								, pArgVals?pArgVals->Cnt:0 );
				if( ( g.bDebugLog & DEBUG_SUBST )
 // could be useful to dump arguments....
					&& pDefine && pDefine->pParams )
				{
					//PTEXT arg;
					INDEX idx;
					if( g.bDebugLog & DEBUG_SUBST )
						fprintf( stddbg, WIDE("Macro Arguments: \n") );
					if( pArgVals )
					{
						for( idx = 0; idx < pArgVals->Cnt; idx++ )
						//FORALL( pArgVals, idx, PTEXT, arg )
						{
							PTEXT name = GetLink( pDefine->pParams, idx );
							PTEXT full = BuildLine( (PTEXT)pArgVals->pNode[idx] );
								fprintf( stddbg, WIDE("%s = %s (%p)\n")
										, name?GetText( name ):"..."
										, GetText( full )
										, pArgVals->pNode[idx] );
								LineRelease( full );
						}
					}
				}
				if( pArgVals && pDefine->pParams &&
					( pArgVals->Cnt < pDefine->pParams->Cnt ) )
				{
					fprintf( stderr, WIDE("%s(%d): Warning: parameters to macro are short... assuming NIL parameters.\n")
						 , GetCurrentFileName(), GetCurrentLine() );
				}
			// ok now we have gathered macro parameters, and the macro
				if( pDefine )
				{
					int MakeString = 0;
					int quote = 0;
					int escape = 0;
					INDEX idx;
					if( pArgVals )
					{
						for( idx = 0; idx < pArgVals->Cnt; idx++ )
						{
							EvalSubstitutions( (PTEXT*)(pArgVals->pNode + idx), FALSE );
						}
					}
 // is used. now...
					pDefine->bUsed = TRUE;
					for( p = pDefine->pData; p; p = NEXTLINE( p ) )
					{
						if( !quote )
						{
							if( GetText( p )[0] == '\'' )
								quote = '\'';
							if( GetText( p )[0] == '\"' )
								quote = '\"';
						}
						else
						{
							if( !escape )
							{
								if( GetText( p )[0] == '\\' )
									escape = TRUE;
								else if( GetText( p )[0] == quote )
									quote = 0;
							}
							else
								escape = 0;
						}
						if( quote )
						{
							pSubst = SegAppend( pSubst, SegDuplicate( p ) );
							continue;
						}
						if( GetText( p )[0] == '#' )
						{
							MakeString++;
							continue;
						}
						idx = FindArg( pDefine->pParams, p );
						if( idx == INVALID_INDEX )
						{
							PTEXT seg;
							if( TextIs( p, WIDE("__VA_ARGS__") ) ||
								TextIs( p, WIDE("...") ) )
							{
								fprintf( stderr, WIDE("%s(%d): Should NEVER be here!\n"), __FILE__, __LINE__ );
								exit(-1);
							}
							seg = SegDuplicate( p );
							if( MakeString == 2 )
							{
								if( seg )
								{
									PTEXT valnow = pSubst;
									PTEXT newseg;
									SetEnd( valnow );
									// just a concatenation - make sure we put these right next to each other...
									vtprintf( &g.vt, WIDE("%s%s"), GetText( valnow ), GetText( seg ) );
									newseg = VarTextGet( &g.vt );
									newseg->format.spaces = valnow->format.spaces;
									SegGrab( valnow );
									if( valnow == pSubst )
										pSubst = NULL;
									LineRelease( valnow );
									SegSubst( seg, newseg );
									seg = newseg;
								}
								MakeString = 0;
							}
							else if( MakeString == 1 )
							{
								if( seg )
								{
									PTEXT tmp;
									VarTextAddCharacter( &g.vt, '\"' );
									tmp = VarTextEnd( &g.vt );
									if( !(tmp->format.spaces = p->format.spaces ) )
										tmp->format.spaces++;
									vtprintf( &g.vt, WIDE("%s"), GetText( seg ) );
									VarTextEnd( &g.vt );
									VarTextAddCharacter( &g.vt, '\"' );
									LineRelease( seg );
									seg = VarTextGet( &g.vt );
								}
								MakeString = 0;
							}
							else
							{
								if( p == pDefine->pData )
									seg->format.spaces++;
							}
							pSubst = SegAppend( pSubst, seg );
						}
						else
						{
							PTEXT seg;
							if( idx == pDefine->pParams->Cnt )
							{
								if( TextIs( p, WIDE("__SZ_ARGS__") ) )
									seg = BuildSizeofArgs( GetLink( pArgVals, idx ) );
								else
								{
									seg = TextDuplicate( GetLink( pArgVals, idx ) );
									if( !GetLink( pArgVals, idx ) )
									{
										PTEXT prior = pSubst;
										SetEnd( prior );
										if( prior && GetText( prior )[0] == ',' )
										{
											SegDelete( &prior );
										}
										continue;
									}
								}
							}
							else
							{
								seg = TextDuplicate( GetLink( pArgVals, idx ) );
							}
							if( MakeString == 2 )
							{
								if( seg )
								{
									PTEXT valnow = pSubst;
									PTEXT newseg;
									SetEnd( valnow );
									// just a concatenation - make sure we put these right next to each other...
									vtprintf( &g.vt, WIDE("%s%s"), GetText( valnow ), GetText( seg ) );
									newseg = VarTextGet( &g.vt );
									newseg->format.spaces = valnow->format.spaces;
									SegGrab( valnow );
									if( valnow == pSubst )
										pSubst = NULL;
									LineRelease( valnow );
									SegSubst( seg, newseg );
									seg = newseg;
								}
								/*
								// don't check this for substitution
								if( seg )
								seg->format.spaces = 0;
								*/
								MakeString = 0;
							}
							else if( MakeString == 1 )
							{
								PTEXT text;
								if( seg )
								{
									PTEXT tmp;
									FixQuoting( seg );
									text = BuildLine( seg );
									VarTextAddCharacter( &g.vt, '\"' );
									tmp = VarTextEnd( &g.vt );
									if( !(tmp->format.spaces = p->format.spaces ) )
										tmp->format.spaces++;
									vtprintf( &g.vt, WIDE("%s"), GetText( text ) );
									VarTextEnd( &g.vt );
									VarTextAddCharacter( &g.vt, '\"' );
									LineRelease( text );
									LineRelease( seg );
									seg = VarTextGet( &g.vt );
								}
									// don't check this for substitution
							MakeString = 0;
						}
						else
							{
								// seg will always be a unique thing unto itself here.
								/*
								if( g.bDebugLog & DEBUG_SUBST )
								{
									fprintf( stddbg, WIDE("%s(%d): Doing substitution on substituted parameter: ")
											, GetCurrentFileName()
											, GetCurrentLine()
											 );
									DumpSegs( seg );
									fprintf( stddbg, WIDE("\n") );
								}
								EvalSubstitutions( &seg, ppReset );
								if( g.bDebugLog & DEBUG_SUBST )
								{
									fprintf( stddbg, WIDE("%s(%d): Did substitution: ")
											, GetCurrentFileName()
											, GetCurrentLine()
											 );
									DumpSegs( seg );
									fprintf( stddbg, WIDE("\n") );
								}
								*/
								if( seg )
								{
									seg->format.spaces = p->format.spaces;
									//if( p == pDefine->pData )
									seg->format.spaces++;
								}
								// check seg itself as a symbol...
							}
							pSubst = SegAppend( pSubst, seg );
						}
					}
					EmptyArgList( &pArgVals );
				}
				else
				{
					fprintf( stderr, WIDE("%s(%d): Could not match macro(%s) with specified (%zd) parameters...\n")
							 , GetCurrentFileName(), GetCurrentLine()
							 , GetText( pStart )
							 , pArgVals?pArgVals->Cnt:0 );
					EmptyArgList( &pArgVals );
					continue;
				}
			}
 // if !define->params...
			else
			{
				pDefine->bUsed = TRUE;
				// simple case - no names, no nothing, just literatal substitue
				if( pSubst = TextDuplicate( pDefine->pData ) )
				{
					if( g.bDebugLog & DEBUG_SUBST )
						fprintf( stddbg, WIDE("First subst word: %s\n"), GetText( pSubst ) );
					pSubst->format.spaces = 1;
				}
				else
				{
					if( g.bDebugLog & DEBUG_SUBST )
						fprintf( stddbg, WIDE("Symbol has no subst data...\n") );
				}
			}
			if( pSubst )
			{
				PTEXT pOrigin = pStart;
				EvalSubstitutions( &pSubst, FALSE );
				pReset = NEXTLINE( pWord );
				if( pReset )
					pReset->format.spaces = 1;
				if( pSubst )
					pReset = pSubst;
				SegSubstRange( &pStart, pWord, pSubst );
				if( pOrigin == *subst )
				{
					if( g.bDebugLog & DEBUG_SUBST )
					{
						fprintf( stddbg, WIDE("Resetting line begin 3\n") );
					}
					*subst = pStart;
				}
				// while current is still marked as used, process from HERE
				// forward... this will allow recursive defines to work.
				/*
				if( pStart == *subst )
				{
					if( g.bDebugLog & DEBUG_SUBST )
						fprintf( stddbg, WIDE("Doing subst from start of line...\n") );
					EvalSubstitutions( subst, FALSE ); // need recursion to keep defined substs from redefining...
					pReset = *ppReset;
					fprintf( stddbg, WIDE("Returning from doing start of line subst...\n") );
				}
				else
				{
					if( g.bDebugLog & DEBUG_SUBST )
						fprintf( stddbg, WIDE("Doing subst from current start\n") );
					EvalSubstitutions( &pStart, FALSE ); // need recursion to keep defined substs from redefining...
					pReset = *ppReset;
					fprintf( stddbg, WIDE("Returning from current spot subst...\n") );
				}
				*/
			}
			else
			{
				PTEXT pOrigin = pStart;
				// step to the next word... substitution with NO data
				// just continue on with current line.
				// we will be breaking out of this loop, so this sets
				// the initial condition of the next recursion path.
				pReset = NEXTLINE( pWord );
				if( pReset )
					pReset->format.spaces = 1;
				//if( ppReset )
				//	*ppReset = pReset;
				SegSubstRange( &pStart, pWord, NULL );
				if( pOrigin == *subst )
				{
					if( g.bDebugLog & DEBUG_SUBST )
					{
						fprintf( stddbg, WIDE("Resetitng line begin 4\n") );
					}
					*subst = pReset;
				}
			}
			if( g.bDebugLog & DEBUG_SUBST )
			{
				fprintf( stddbg, WIDE("Line Now:") );
				DumpSegs( *subst );
				fprintf( stddbg, WIDE("\n") );
			}
			// release symbol just substituted.
			if( pDefine )
					pDefine->bUsed = FALSE;
 // end if define && !used
		}
		else
		{
			pWord->flags |= TF_NOEXPAND;
		}
		//else if( pDefine ) // if used - perhaps we should return now and see if parent substitutions can handle this...
		//{
		//	*ppReset = pWord;
		//   return;
		//}
 // while there's a word...
	}
	if( g.bDebugLog & DEBUG_SUBST )
	{
		fprintf( stddbg, WIDE("Done substituting....\n") );
		if( !*subst )
		{
			fprintf( stddbg, WIDE("Resulting No content.\n") );
		}
	}
	nSubstLevel--;
	return;
}
//----------------------------------------------------------------------
void CommitDefinesToCommandLineTree( PDEF root )
{
	if( root )
	{
		CommitDefinesToCommandLineTree( root->pLesser );
		CommitDefinesToCommandLineTree( root->pSame );
		CommitDefinesToCommandLineTree( root->pGreater );
		root->nType = DEFINE_COMMANDLINE;
	}
}
//----------------------------------------------------------------------
void CommitDefinesToCommandLine( void )
{
	CommitDefinesToCommandLineTree( pDefineRoot );
}
//----------------------------------------------------------------------
//#include <windows.h>
//#include <stdio.h>
 // offsetof
//#include <string.h> // memset
#ifdef _DEBUG
#define DBG_PASS , char *pFile, int nLine
#define DBG_SRC , __FILE__, __LINE__
#else
#define DBG_PASS
#define DBG_SRC
#endif
//--------------------------------------------------------------------------
PLIST CreateListEx( DBG_VOIDPASS )
{
   PLIST pl;
   INDEX size;
   pl = AllocateEx( ( size = offsetof( LIST, pNode[0] ) ) DBG_RELAY );
   MemSet( pl, 0, size );
   return pl;
}
//--------------------------------------------------------------------------
PLIST DeleteListEx( PLIST *pList DBG_PASS )
{
   if( pList && *pList)
   {
		while( LockedExchange( &((*pList)->Lock), 1 ) )
		{
      //Sleep(0);
		}
		ReleaseExx( (void**)pList DBG_RELAY );
      *pList = NULL;
   }
   return NULL;
}
//--------------------------------------------------------------------------
PLIST ExpandListEx( PLIST *pList, size_t amount DBG_PASS )
{
   PLIST pl;
   INDEX size;
   if( !pList )
      return NULL;
   if( *pList )
      pl = AllocateEx( size = offsetof( LIST, pNode[(*pList)->Cnt+amount] ) DBG_RELAY );
   else
      pl = AllocateEx( size = offsetof( LIST, pNode[amount] ) DBG_RELAY );
 // assume a locked state...
	pl->Lock = TRUE;
   if( *pList )
   {
      // copy old list to new list
 /*don't include new link*/
      MemCpy( pl, *pList, size - (4*amount) );
      if( amount == 1 )
         pl->pNode[pl->Cnt++] = NULL;
      else
      {
         // clear the new additions to the list
         MemSet( pl->pNode + pl->Cnt, 0, amount*4 );
         pl->Cnt += amount;
      }
      // remove the old list...
      ReleaseExx( (void**)pList DBG_RELAY );
      *pList = NULL;
//      DeleteListEx( pList DBG_RELAY ); // bypass this cause it locks the list...
   }
   else
   {
 // clear whole structure on creation...
      MemSet( pl, 0, size );
  // one more ( always a free )
      pl->Cnt = amount;
   }
   *pList = pl;
   return pl;
}
//--------------------------------------------------------------------------
PLIST AddLinkEx( PLIST *pList, POINTER p DBG_PASS )
{
   INDEX i;
   if( !pList )
      return NULL;
	if( *pList )
		while( LockedExchange( &((*pList)->Lock), 1 ) )
		{
      //Sleep(0);
		}
   retry1:
      ExpandListEx( pList, 1 DBG_RELAY );
   for( i = 0; i < (*pList)->Cnt; i++ )
   {
      if( !(*pList)->pNode[i] )
      {
         (*pList)->pNode[i] = p;
         break;
      }
   }
   if( i == (*pList)->Cnt )
  // pList->Cnt changes - don't test in WHILE
      goto retry1;
	(*pList)->Lock = 0;
 // might be a NEW list...
   return *pList;
}
//--------------------------------------------------------------------------
PLIST SetLinkEx( PLIST *pList, INDEX idx, POINTER p DBG_PASS )
{
   INDEX sz;
   if( !pList )
      return NULL;
   if( *pList )
     while( LockedExchange( &((*pList)->Lock), 1 ) )
     {
        //Sleep(0);
     }
   if( idx == INVALID_INDEX )
 // not set...
      return *pList;
   sz = 0;
   while( !(*pList) || ( sz = (*pList)->Cnt ) <= idx )
      ExpandListEx( pList, (idx - sz) + 1 DBG_RELAY );
   (*pList)->pNode[idx] = p;
	(*pList)->Lock = 0;
 // might be a NEW list...
   return *pList;
}
//--------------------------------------------------------------------------
POINTER GetLinkEx( PLIST *pList, INDEX idx )
{
   // must lock the list so that it's not expanded out from under us...
	POINTER p;
   if( !pList || !(*pList) )
      return NULL;
   if( idx == INVALID_INDEX )
 // not set...
      return pList;
   while( LockedExchange( &((*pList)->Lock), 1 ) )
   {
      //Sleep(0);
   }
   if( (*pList)->Cnt <= idx )
	{
		(*pList)->Lock = 0;
      return NULL;
	}
	p = (*pList)->pNode[idx];
	(*pList)->Lock = 0;
   return p;
}
//--------------------------------------------------------------------------
INDEX FindLink( PLIST *pList, POINTER value )
{
   INDEX i, r;
   POINTER v;
	r = INVALID_INDEX;
	/*
   while( LockedExchange( &((*pList)->Lock), 1 ) )
   {
      //Sleep(0);
   }
	*/
   FORALL( (*pList), i, POINTER, v )
      if( v == value )
      {
			r = i;
			break;
      }
	//(*pList)->Lock = 0;
   return r;
}
//--------------------------------------------------------------------------
int DeleteLinkEx( PLIST *pList, POINTER value )
{
   INDEX idx;
   if( !pList )
      return 0;
   if( !(*pList ) )
      return 0;
   while( LockedExchange( &((*pList)->Lock), 1 ) )
   {
      //Sleep(0);
   }
   if( ( idx = FindLink( pList, value ) ) != INVALID_INDEX )
   {
      (*pList)->pNode[idx] = NULL;
		(*pList)->Lock = 0;
      return TRUE;
   }
	(*pList)->Lock = 0;
   return FALSE;
}
//--------------------------------------------------------------------------
PLINKSTACK CreateLinkStack( void )
{
   PLINKSTACK pls;
   pls = Allocate( sizeof( LINKSTACK ) );
   pls->Top = 0;
   pls->Cnt = 0;
   return pls;
}
//--------------------------------------------------------------------------
void DeleteLinkStack( PLINKSTACK pls )
{
   Release( pls );
}
//--------------------------------------------------------------------------
POINTER PeekLink( PLINKSTACK pls )
{
   POINTER p = NULL;
   if( pls && pls->Top )
      p = pls->pNode[pls->Top-1];
   return p;
}
//--------------------------------------------------------------------------
POINTER PopLink( PLINKSTACK pls )
{
	POINTER p = NULL;
	if( !pls )
      return NULL;
   if( pls->Top )
   {
      pls->Top--;
      p = pls->pNode[pls->Top];
      pls->pNode[pls->Top] = (POINTER)0x1BEDCAFE;
   }
   return p;
}
//--------------------------------------------------------------------------
PLINKSTACK ExpandStack( PLINKSTACK stack, size_t entries )
#define ExpandStack(s,n)  ((s)=ExpandStack((s),(n)))
{
   PLINKSTACK pNewStack;
   if( stack )
      entries += stack->Cnt;
   pNewStack = Allocate( offsetof( LINKSTACK, pNode[entries] ) );
   if( stack )
   {
      MemCpy( pNewStack->pNode, stack->pNode, stack->Cnt * sizeof(POINTER) );
      pNewStack->Top = stack->Top;
      Release( stack );
   }
   else
      pNewStack->Top = 0;
   pNewStack->Cnt = entries;
   return pNewStack;
}
//--------------------------------------------------------------------------
#undef PushLink
PLINKSTACK PushLink( PLINKSTACK pls, POINTER p )
#define PushLink(s,p)  ((s)=PushLink((s),(p)))
{
   if( !pls ||
       pls->Top == pls->Cnt )
   {
      ExpandStack( pls, 1 );
   }
   pls->pNode[pls->Top] = p;
   pls->Top++;
   return pls;
}
//--------------------------------------------------------------------------
//--------------------------------------------------------------------------
POINTER PopData( PDATASTACK *pds )
{
   POINTER p = NULL;
   if( (*pds)->Top )
   {
      (*pds)->Top--;
      if( (*pds)->Top )
      {
         p = (*pds)->data + ( (*pds)->Size * ((*pds)->Top-1) );
      }
   }
   return p;
}
//--------------------------------------------------------------------------
PDATASTACK ExpandDataStack( PDATASTACK *pds, size_t entries )
{
   PDATASTACK pNewStack;
   if( (*pds) )
      entries += (*pds)->Cnt;
   pNewStack = Allocate( sizeof( DATASTACK ) + ( (*pds)->Size * entries ) - 1 );
   MemCpy( pNewStack->data, (*pds)->data, (*pds)->Cnt * (*pds)->Size );
   pNewStack->Cnt = entries;
   pNewStack->Size = (*pds)->Size;
   pNewStack->Top = (*pds)->Top;
   Release( (*pds) );
   *pds = pNewStack;
   return pNewStack;
}
//--------------------------------------------------------------------------
PDATASTACK PushData( PDATASTACK *pds, POINTER pdata )
{
	if( pds && *pds )
   {
	   if( (*pds)->Top == (*pds)->Cnt )
	   {
	      ExpandDataStack( pds, 1 );
	   }
	   MemCpy( (*pds)->data + ((*pds)->Top * (*pds)->Size ), pdata, (*pds)->Size );
	   (*pds)->Top++;
	   return (*pds);
   }
   if( pds )
	   return *pds;
   return NULL;
}
//--------------------------------------------------------------------------
POINTER PeekDataEx( PDATASTACK *pds, int nBack )
{
   POINTER p = NULL;
   if( ( (int)((*pds)->Top) - nBack ) >= 0 )
      p = (*pds)->data + ( (*pds)->Size * ((*pds)->Top - nBack) );
   return p;
}
//--------------------------------------------------------------------------
POINTER PeekData( PDATASTACK *pds )
{
   POINTER p = NULL;
   if( (*pds)->Top )
      p = (*pds)->data + ( (*pds)->Size * ((*pds)->Top-1) );
   return p;
}
//--------------------------------------------------------------------------
PDATASTACK CreateDataStack( INDEX size )
{
   PDATASTACK pds;
   pds = Allocate( sizeof( DATASTACK ) );
   pds->Cnt = 0;
   pds->Top = 0;
   pds->Size = size;
   return pds;
}
//--------------------------------------------------------------------------
void DeleteDataStack( PDATASTACK *pds )
{
   Release( *pds );
   *pds = NULL;
}
//--------------------------------------------------------------------------
//--------------------------------------------------------------------------
PLINKQUEUE CreateLinkQueue( void )
{
   PLINKQUEUE plq;
   plq = Allocate( sizeof( LINKQUEUE ) );
   plq->Top      = 0;
   plq->Bottom   = 0;
   plq->Lock     = 0;
   plq->Cnt      = 2;
   plq->pNode[0] = NULL;
 // shrug
   plq->pNode[1] = NULL;
   return plq;
}
//--------------------------------------------------------------------------
void DeleteLinkQueueEx( PLINKQUEUE *pplq DBG_PASS )
{
   if( pplq )
   {
      if( *pplq )
         ReleaseExx( (void**)pplq DBG_RELAY );
      *pplq = NULL;
   }
}
//--------------------------------------------------------------------------
PLINKQUEUE ExpandLinkQueue( PLINKQUEUE *pplq, int entries )
{
   PLINKQUEUE plqNew = NULL;
   if( pplq )
   {
      PLINKQUEUE plq = *pplq;
      plqNew = Allocate( offsetof( LINKQUEUE, pNode[plq->Cnt + entries] ) );
      plqNew->Cnt = plq->Cnt + entries;
      plqNew->Bottom = 0;
      if( plq->Bottom > plq->Top )
      {
         uint32_t bottom_half;
         plqNew->Top = (bottom_half = plq->Cnt - plq->Bottom ) + plq->Top;
         MemCpy( plqNew->pNode, plq->pNode + plq->Bottom, sizeof(POINTER)*bottom_half );
         MemCpy( plqNew->pNode + bottom_half, plq->pNode, sizeof(POINTER)*plq->Top );
      }
      else
      {
         plqNew->Top = plq->Top - plq->Bottom;
         MemCpy( plqNew->pNode, plq->pNode + plq->Bottom, sizeof(POINTER)*plqNew->Top );
      }
      Release( plq );
   }
   return *pplq = plqNew;
}
//--------------------------------------------------------------------------
PLINKQUEUE EnqueLinkEx( PLINKQUEUE *pplq, POINTER link DBG_PASS )
{
   INDEX tmp;
   PLINKQUEUE plq;
   if( !pplq )
      return NULL;
   if( !(*pplq) )
      *pplq = CreateLinkQueue();
   // this is a single threaded task... shouldn't ever end up against a lock...
   while( LockedExchange( &(*pplq)->Lock, 1 ) )
   {
   }
   plq = *pplq;
   if( link )
   {
      tmp = plq->Top + 1;
      if( tmp >= plq->Cnt )
         tmp -= plq->Cnt;
 // collided with self...
      if( tmp == plq->Bottom )
      {
         plq = ExpandLinkQueue( &plq, 16 );
 // should be room at the end of phsyical array....
         tmp = plq->Top + 1;
      }
      plq->pNode[plq->Top] = link;
      plq->Top = tmp;
   }
   *pplq = plq;
   plq->Lock = 0;
   return plq;
}
//--------------------------------------------------------------------------
int IsQueueEmpty( PLINKQUEUE *pplq  )
{
   if( !pplq || !(*pplq) ||
       (*pplq)->Bottom == (*pplq)->Top )
      return TRUE;
   return FALSE;
}
//--------------------------------------------------------------------------
POINTER DequeLink( PLINKQUEUE *pplq )
{
   POINTER p;
   INDEX tmp;
   if( pplq && *pplq )
      while( LockedExchange( &((*pplq)->Lock), 1 ) )
      {
         //Sleep(0);
      }
   else
      return NULL;
   p = NULL;
   if( (*pplq)->Bottom != (*pplq)->Top )
   {
      tmp = (*pplq)->Bottom + 1;
      if( tmp >= (*pplq)->Cnt )
         tmp -= (*pplq)->Cnt;
      p = (*pplq)->pNode[(*pplq)->Bottom];
      (*pplq)->Bottom = tmp;
   }
   (*pplq)->Lock = 0;
   return p;
}
#include <stdarg.h>
//#include <stdio.h>
//#define RELEASE_LOG
static PTEXT last_vartext_result;
//#define STRICT_LINKING
//---------------------------------------------------------------------------
#ifdef STRICT_LINKING
PTEXT SetPriorLineEx( PTEXT seg, PTEXT newprior DBG_PASS )
{
	if( seg == newprior )
	{
		fprintf( stderr, WIDE("ERROR! Segment is same as new prior ") DBG_FILELINEFMT "\n" DBG_RELAY );
		DebugBreak();
	}
	if( seg )
	{
		PTEXT test, start;
		seg->Prior = newprior;
		start = seg;
		test = PRIORLINE( start );
		while( test && test != start )
		{
			test = PRIORLINE( test );
		}
		if( test )
		{
			fprintf( stderr, WIDE("ERROR! Resulting link causes circularity!") DBG_FILELINEFMT "\n" DBG_RELAY );
			DebugBreak();
		}
		test = NEXTLINE( start );
		while( test && test != start )
		{
			test = NEXTLINE( test );
		}
		if( test )
		{
			fprintf( stderr, WIDE("ERROR! Resulting link causes circularity!") DBG_FILELINEFMT "\n" DBG_RELAY );
			DebugBreak();
		}
		return newprior;
	}
	else
	{
		fprintf( stderr, WIDE("ERROR! Attempt to link prior to NULL ") DBG_FILELINEFMT "\n" DBG_RELAY );
		DebugBreak();
	}
	return NULL;
}
#else
PTEXT SetPriorLineEx( PTEXT seg, PTEXT newprior DBG_PASS )
{
	if( seg )
	{
		seg->Prior = newprior;
		return newprior;
	}
	return NULL;
}
#endif
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
#ifdef STRICT_LINKING
PTEXT SetNextLineEx( PTEXT seg, PTEXT newnext DBG_PASS )
{
	if( seg == newnext )
	{
		fprintf( stderr, WIDE("ERROR! Segment is same as new next ") DBG_FILELINEFMT "\n" DBG_RELAY );
	}
	if( seg )
	{
		PTEXT test, start;
		seg->Next = newnext;
		start = seg;
		test = NEXTLINE( start );
		while( test && test != start )
		{
			test = NEXTLINE( test );
		}
		if( test )
		{
			fprintf( stderr, WIDE("ERROR! Resulting link causes circularity!") DBG_FILELINEFMT "\n" DBG_RELAY );
			DebugBreak();
		}
		test = PRIORLINE( start );
		while( test && test != start )
		{
			test = PRIORLINE( test );
		}
		if( test )
		{
			fprintf( stderr, WIDE("ERROR! Resulting link causes circularity!") DBG_FILELINEFMT "\n" DBG_RELAY );
			DebugBreak();
		}
		return newnext;
	}
	else
		fprintf( stderr, WIDE("ERROR! Attempt to link prior to NULL ") DBG_FILELINEFMT "\n" DBG_RELAY );
	return NULL;
}
#else
PTEXT SetNextLineEx( PTEXT seg, PTEXT newnext DBG_PASS )
{
	if( seg )
	{
		seg->Next = newnext;
		return newnext;
	}
	return NULL;
}
#endif
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
PTEXT SegCreateEx( size_t size DBG_PASS )
{
	PTEXT pTemp;
 // good thing [1] is already counted.
	pTemp = AllocateEx( sizeof(TEXT) + size DBG_RELAY );
	MemSet( pTemp, 0, sizeof(TEXT) + size );
 // physical space IS one more....
	pTemp->data.size = size;
	return pTemp;
}
//---------------------------------------------------------------------------
PTEXT GetIndirect(PTEXT segment )
{
	if( !segment )
		return NULL;
	if( !(segment->flags&TF_INDIRECT) )
		return 0;
	return (PTEXT)segment->data.size;
}
//---------------------------------------------------------------------------
char *GetTextEx( PTEXT segment )
{
	if( !segment )
		return NULL;
	while( segment && segment->flags & TF_INDIRECT )
		segment = GetIndirect( segment );
	if( segment )
		return segment->data.data;
	return NULL;
}
//---------------------------------------------------------------------------
INDEX GetTextSize( PTEXT segment )
{
	int flags;
	if( !segment )
 // perhaps return -1, 0xFFFFFFFF
		return 0;
	if( segment->flags & TF_INDIRECT )
		return GetTextSize( GetIndirect( segment ) );
	if( !segment->data.size )
	{
		flags = *(int*)&segment->flags;
		if( flags & IS_DATA_FLAGS )
 // is data even if is not acurate....
			return 2;
	}
	return segment->data.size;
}
//---------------------------------------------------------------------------
int GetTextFlags( PTEXT segment )
{
	if( !segment )
		return 0;
	if( segment->flags & TF_INDIRECT )
		return GetTextFlags( GetIndirect( segment ) );
	return segment->flags;
}
//---------------------------------------------------------------------------
PTEXT SegDuplicateEx( PTEXT pText DBG_PASS )
{
	PTEXT t;
	size_t n;
	if( pText )
	{
		if( pText->flags & TF_INDIRECT )
		{
			t = SegCreateIndirect( GetIndirect( pText ) );
			t->flags = pText->flags;
		}
		else
		{
			t = SegCreateEx( n = GetTextSize( pText ) DBG_RELAY );
			t->format = pText->format;
			t->flags  = pText->flags;
			MemCpy( GetText(t), GetText(pText), n );
		}
		t->flags &= ~(TF_STATIC);
		pText = t;
	}
	return pText;
}
//---------------------------------------------------------------------------
PTEXT TextDuplicateEx( PTEXT pText DBG_PASS )
{
	PTEXT pt;
	PTEXT pDup = NULL, pNew;
	pt = pText;
	while( pt )
	{
		if( pt->flags & TF_INDIRECT )
		{
			pNew = SegCreateIndirectEx(
							TextDuplicateEx(
									GetIndirect( pt ) DBG_RELAY ) DBG_RELAY );
			pNew->format = pt->format;
			pNew->flags |= pt->flags&(IS_DATA_FLAGS);
			pNew->flags |= TF_DEEP;
		}
		else
			pNew = SegDuplicateEx( pt DBG_RELAY );
		pDup = SegAppend( pDup, pNew );
		pt = NEXTLINE( pt );
	}
	SetStart( pDup );
	return pDup;
}
//---------------------------------------------------------------------------
PTEXT SegCreateFromTextEx( char *text DBG_PASS )
{
	PTEXT pTemp;
	size_t   nSize;
	if( text )
	{
		pTemp = SegCreateEx( nSize = strlen( text ) DBG_RELAY );
		MemCpy( pTemp->data.data, text, nSize );
		return pTemp;
	}
	return NULL;
}
//---------------------------------------------------------------------------
PTEXT SegCreateFromIntEx( int value DBG_PASS )
{
	PTEXT pResult;
	pResult = SegCreateEx( 12 DBG_RELAY);
	pResult->data.size = sprintf( pResult->data.data, WIDE("%d"), value );
	return pResult;
}
//---------------------------------------------------------------------------
PTEXT SegCreateFromFloatEx( float value DBG_PASS )
{
	PTEXT pResult;
	pResult = SegCreateEx( 32 DBG_RELAY);
	pResult->data.size = sprintf( pResult->data.data, WIDE("%g"), value );
	return pResult;
}
//---------------------------------------------------------------------------
PTEXT SegCreateIndirectEx( PTEXT pText DBG_PASS )
{
	PTEXT pSeg;
 // no data content for indirect...
	pSeg = SegCreateEx( -1 DBG_RELAY );
	pSeg->flags |= TF_INDIRECT;
/*
	if( pText && !(pText->flags & TF_STATIC ) )
		HoldEx( pText DBG_RELAY );
*/
	pSeg->data.size = (uintptr_t)pText;
	return pSeg;
}
//---------------------------------------------------------------------------
  // remove leading segments.
PTEXT SegBreak(PTEXT segment)
    // return leading segments!  might be ORPHANED if not handled.
{
	PTEXT temp;
	if( !segment )
		return NULL;
	if( ( temp = PRIORLINE(segment) ) != NULL )
		SETNEXTLINE(temp, NULL );
	SETPRIORLINE( segment, NULL );
	return(temp);
}
//---------------------------------------------------------------------------
PTEXT SegAppend(PTEXT source,PTEXT other)
{
	PTEXT temp=source;
	if( temp )
	{
		if( other )
		{
			SetEnd(temp);
			SetStart( other );
			SETNEXTLINE( temp, other );
			SETPRIORLINE( other, temp );
		}
	}
	else
	{
  // nothing was before...
		source=other;
	}
	return(source);
}
//---------------------------------------------------------------------------
PTEXT SegAdd(PTEXT source,PTEXT other)
{
	PTEXT temp=source;
	if( temp )
	{
		if( other )
		{
			SetEnd(temp);
			SetStart( other );
			SETNEXTLINE( temp, other );
			SETPRIORLINE( other, temp );
 // return new addition...
			return other;
		}
	}
	else
	{
  // nothing was before...
		source=other;
	}
	return(source);
}
//---------------------------------------------------------------------------
PTEXT SegExpandEx(PTEXT source, int nSize DBG_PASS)
{
	PTEXT temp;
	temp = SegCreateEx( ( GetTextSize( source ) + nSize ) DBG_RELAY );
	if( source )
	{
		MemCpy( temp->data.data, source->data.data, GetTextSize( source ) );
		temp->flags = source->flags;
		temp->format = source->format;
		SegSubst( temp, source );
		SegRelease( source );
	}
	return temp;
}
//---------------------------------------------------------------------------
void SegReleaseEx( PTEXT seg DBG_PASS)
{
	if( seg )
		ReleaseExx( (void**)&seg DBG_RELAY );
}
//---------------------------------------------------------------------------
void LineReleaseEx(PTEXT *ppLine DBG_PASS )
{
	PTEXT line = *ppLine;
	PTEXT temp;
#ifdef RELEASE_LOG
	static int levels;
#endif
	if( !line )
		return;
#ifdef RELEASE_LOG
	levels++;
	printf( WIDE("Release...%d\n "), levels);
#endif
	SetStart(line);
	temp = line;
	while(line = temp)
	{
		temp=NEXTLINE(line);
		if( line == last_vartext_result )
			last_vartext_result = NULL;
		if( !(line->flags&TF_STATIC) )
		{
			if( (( line->flags & (TF_INDIRECT|TF_DEEP) ) == (TF_INDIRECT|TF_DEEP) ) )
			{
				LineReleaseEx( (PTEXT*)&line->data.size DBG_RELAY );
			}
			ReleaseExx( (void**)&line DBG_RELAY );
		}
		else
		{
			//Log( WIDE("Attempt to free static text...\n") );
		}
	}
#ifdef RELEASE_LOG
	levels--;
#endif
	*ppLine = NULL;
}
//---------------------------------------------------------------------------
PTEXT SegConcatEx(PTEXT output,PTEXT input,int32_t offset,int32_t length DBG_PASS )
{
	int32_t idx=0,len=0;
	output=SegExpandEx(output, length DBG_RELAY);
	GetText(output)[0]=0;
	while (input&&idx<length)
	{
		if( ((int32_t)GetTextSize( input ) - offset ) < (length - idx) )
			len = ((int32_t)GetTextSize( input ) - offset);
		else
			len = length-idx;
		MemCpy( GetText(output) + idx,
				  GetText(input) + offset,
				  len );
		idx += len;
		offset = 0;
		input=NEXTLINE(input);
	}
	GetText(output)[idx]=0;
	return(output);
}
//---------------------------------------------------------------------------
PTEXT SegUnlink(PTEXT segment)
{
	PTEXT temp;
	if (segment)
	{
		if( ( temp = PRIORLINE(segment) ) != NULL )
			SETNEXTLINE( temp, NEXTLINE(segment) );
		if( ( temp = NEXTLINE(segment) ) != NULL )
			SETPRIORLINE( temp, PRIORLINE(segment) );
		SETPRIORLINE(segment, NULL);
		SETNEXTLINE(segment, NULL);
	}
	return segment;
}
//---------------------------------------------------------------------------
PTEXT SegGrab( PTEXT segment )
{
	SegUnlink( segment );
	return segment;
}
//---------------------------------------------------------------------------
PTEXT SegDeleteEx( PTEXT *segment DBG_PASS )
{
	SegGrab( *segment );
	LineReleaseEx( segment DBG_RELAY );
	return NULL;
}
//---------------------------------------------------------------------------
PTEXT SegInsert( PTEXT what, PTEXT before )
{
	PTEXT that_start = what ,
			that_end= what;
	SetStart( that_start );
	SetEnd( that_end );
	if( before )
	{
		if( ( SETPRIORLINE( that_start, PRIORLINE(before) ) ) != NULL )
			SETNEXTLINE( PRIORLINE(that_start), that_start );
		if( ( SETNEXTLINE(that_end, before) ) != NULL )
			SETPRIORLINE( NEXTLINE( that_end ), that_end );
	}
	return what;
}
//---------------------------------------------------------------------------
PTEXT SegSubst( PTEXT _this, PTEXT that )
{
	PTEXT that_start = that ,
			that_end= that;
	SetStart( that_start );
	SetEnd( that_end );
	if( ( SETNEXTLINE(that_end, NEXTLINE(_this) ) ) != NULL )
		SETPRIORLINE(NEXTLINE(that_end),  that_end );
	if( ( SETPRIORLINE(that_start, PRIORLINE(_this))) != NULL )
		SETNEXTLINE(PRIORLINE(that_start), that_start );
	SETNEXTLINE(_this, NULL );
	SETPRIORLINE( _this, NULL );
	return _this;
}
//---------------------------------------------------------------------------
PTEXT SegSubstRangeEx( PTEXT *pp_this, PTEXT end, PTEXT that DBG_PASS )
{
	PTEXT _this = *pp_this;
	PTEXT after_end = NEXTLINE( end );
	if( !_this || !end )
	{
		fprintf( stderr, WIDE("%s(%d): returned early from segsubstrange:%p %p %p\n")
				, GetCurrentFileName()
				, GetCurrentLine()
				, _this, end, that );
		return NULL;
	}
	if( !that )
	{
		if( PRIORLINE( _this ) )
			SETNEXTLINE( PRIORLINE(_this), NEXTLINE(end) );
		if( NEXTLINE( end ) )
			SETPRIORLINE( NEXTLINE( end ), PRIORLINE( _this ) );
	}
	else
	{
		PTEXT that_start = that ,
				that_end= that;
		SetStart( that_start );
		SetEnd( that_end );
		if( ( SETNEXTLINE( that_end, NEXTLINE(end)) ) != NULL )
			SETPRIORLINE(NEXTLINE(that_end), that_end );
		if( ( SETPRIORLINE( that_start, PRIORLINE(_this))) != NULL )
			SETNEXTLINE(PRIORLINE(that_start), that_start );
	}
	SETNEXTLINE( end, NULL );
	SETPRIORLINE( _this, NULL );
	LineReleaseEx( pp_this DBG_RELAY );
	if( that )
		*pp_this = that;
	else
		*pp_this = after_end;
	return NULL;
}
//---------------------------------------------------------------------------
PTEXT SegSplitEx( PTEXT *pLine, size_t nPos  DBG_PASS)
{
	// there includes the character at nPos - so all calculations
	// on there are +1...
	PTEXT here, there;
	size_t nLen;
	nLen = GetTextSize( *pLine );
	if( nPos > nLen )
	{
		return NULL;
	}
	if( nPos == nLen )
		return *pLine;
	here = SegCreateEx( nPos DBG_RELAY );
	here->flags  = (*pLine)->flags;
	here->format = (*pLine)->format;
	there = SegCreateEx( (nLen - nPos) DBG_RELAY );
	there->flags  = (*pLine)->flags;
	there->format = (*pLine)->format;
 // pretty safe...
	there->format.spaces = 0;
 // pretty safe...
	there->format.tabs = 0;
	if( here == there )
	{
		fprintf( stderr, WIDE("Hmm - error in segpslit\n") );
#ifdef __LINUX__
		DebugBreak();
#endif
	}
	MemCpy( GetText( here ), GetText( *pLine ), nPos );
	if( nLen - nPos )
		MemCpy( GetText( there ), GetText( *pLine ) + nPos, (nLen - nPos) );
	if( PRIORLINE( *pLine ) )
		SETNEXTLINE( PRIORLINE( *pLine ), here );
	SETPRIORLINE( here, PRIORLINE( *pLine ) );
	SETNEXTLINE( here, there );
	SETPRIORLINE( there, here );
	SETNEXTLINE( there, NEXTLINE( *pLine ) );
	if( NEXTLINE( *pLine ) )
		SETPRIORLINE( NEXTLINE( *pLine ), there );
	SETNEXTLINE( *pLine, NULL );
	SETPRIORLINE( *pLine, NULL );
	LineRelease( *pLine );
	*pLine = here;
	return here;
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
size_t LineLength( PTEXT pt, int bSingle )
{
	int	TopSingle = bSingle;
	PTEXT pStack[32];
	int   nStack;
	int   skipspaces = ( PRIORLINE(pt) == NULL );
	size_t length = 0;
	nStack = 0;
	while( pt )
	{
		if( !(pt->flags & ( IS_DATA_FLAGS | TF_INDIRECT)) &&
			 !pt->data.size
		  )
 // full binary \r\n insertion assumed
			length += 2;
		else
		{
			if( skipspaces ) {
				skipspaces = FALSE;
				if( g.flags.keep_comments ) {
 // not-including NULL.
					length += pt->format.tabs;
 // not-including NULL.
					length += pt->format.spaces;
				}
			}
			else {
 // not-including NULL.
				length += pt->format.tabs;
 // not-including NULL.
				length += pt->format.spaces;
			}
			if( pt->flags&TF_INDIRECT )
			{
 // will be restored when we get back to top seg.
				bSingle = FALSE;
				pStack[nStack++] = pt;
				pt = GetIndirect( pt );
				//if( nStack >= 32 )
				//   DebugBreak();
				continue;
			}
			else
 // not-including NULL.
				length += GetTextSize( pt );
stack_resume: ;
		}
		if( bSingle )
		{
			bSingle = FALSE;
			break;
		}
		pt = NEXTLINE( pt );
	}
	if( nStack )
	{
		pt = pStack[--nStack];
		if( !nStack )
			bSingle = TopSingle;
		goto stack_resume;
	}
//	if( length > 60000 )
//		_asm int 3;
	return length;
}
//---------------------------------------------------------------------------
int levels = 0;
// attempts to build a solitary line segment from the text passed
// however, if there are color changes, or absolute position changes
// this cannot work... and it must provide multiple peices...
PTEXT BuildLineEx( PTEXT pt, int bSingle DBG_PASS )
{
	char *buf;
	int   TopSingle = bSingle;
	PTEXT pStack[32];
	int   nStack, spaces = 0, tabs = 0, firstadded;
	int   skipspaces = ( PRIORLINE(pt) == NULL );
	PTEXT pOut;
	uintptr_t ofs;
	//DebugBreak();
	{
		size_t len;
		len = LineLength( pt, bSingle );
		if( !len )
			return NULL;
		pOut = SegCreateEx( len DBG_RELAY );
		firstadded = TRUE;
		buf = GetText( pOut );
	}
	ofs = 0;
	nStack = 0;
	while( pt )
	{
		if( !(pt->flags& (TF_INDIRECT|IS_DATA_FLAGS)) &&
			 !pt->data.size
		  )
		{
			buf[ofs++] = '\r';
			buf[ofs++] = '\n';
		}
		else
		{
			if( skipspaces )
			{
				skipspaces = FALSE;
				if( g.flags.keep_comments ) {
					spaces = pt->format.tabs;
					// else we cannot collapse into single line (similar to colors.)
					while( spaces-- )
					{
						buf[ofs++] = '\t';
					}
					spaces = pt->format.spaces;
					// else we cannot collapse into single line (similar to colors.)
					while( spaces-- )
					{
						buf[ofs++] = ' ';
					}
				}
			}
			else
			{
				spaces = pt->format.tabs;
				// else we cannot collapse into single line (similar to colors.)
				while( spaces-- )
				{
					buf[ofs++] = '\t';
				}
				spaces = pt->format.spaces;
				// else we cannot collapse into single line (similar to colors.)
				while( spaces-- )
				{
					buf[ofs++] = ' ';
				}
			}
			// at this point spaces before tags, and after tags
			// which used to be expression level parsed are not
			// reconstructed correctly...
			if( pt->flags&TF_INDIRECT )
			{
 // will be restored when we get back to top.
				bSingle = FALSE;
				pStack[nStack++] = pt;
				pt = GetIndirect( pt );
				//if( nStack >= 32 )
				//	DebugBreak();
				continue;
			}
			else
			{
				 size_t len;
				 MemCpy( buf+ofs, GetText( pt ), len = GetTextSize( pt ) );
				 ofs += len;
			}
stack_resume: ;
		}
		if( bSingle )
		{
			bSingle = FALSE;
			break;
		}
		pt = NEXTLINE( pt );
	}
	if( nStack )
	{
		pt = pStack[--nStack];
		if( !nStack )
			bSingle = TopSingle;
		goto stack_resume;
	}
 // have to return length instead of new text seg...
	if( !pOut )
		return (PTEXT)ofs;
 // if formatting was inserted into the stream...
	SetStart( pOut );
	return pOut;
}
//---------------------------------------------------------------------------
int CompareStrings( PTEXT pt1, int single1
                  , PTEXT pt2, int single2
                  , int bExact )
{
	while( pt1 && pt2 )
	{
		if( !pt1 && pt2 )
			return FALSE;
		if( pt1 && !pt2 )
			return FALSE;
		if( bExact )
		{
			if( !SameText( pt1, pt2 ) )
				return FALSE;
		}
		else
		{
			// Like returns string compare function literal...
			if( LikeText( pt1, pt2 ) )
				return FALSE;
		}
		if( !single1 )
		{
			pt1 = NEXTLINE( pt1 );
			if( pt1
			  && !GetTextSize( pt1 ) && !(pt1->flags & IS_DATA_FLAGS))
				pt1 = NULL;
		}
		else
			pt1 = NULL;
		if( !single2 )
		{
			pt2 = NEXTLINE( pt2 );
			if( pt2 &&
			    !GetTextSize( pt2 ) &&
			    !(pt2->flags & IS_DATA_FLAGS))
				pt2 = NULL;
		}
		else
			pt2 = NULL;
	}
	if( !pt1 && !pt2 )
		return TRUE;
	return FALSE;
}
//---------------------------------------------------------------------------
#define COLLECT_LEN 32
void VarTextInitEx( PVARTEXT pvt DBG_PASS )
{
	pvt->commit = NULL;
	pvt->collect = SegCreateEx( COLLECT_LEN DBG_RELAY );
	pvt->collect_text = GetText( pvt->collect );
	pvt->collect_used = 0;
}
//---------------------------------------------------------------------------
void VarTextEmptyEx( PVARTEXT pvt DBG_PASS )
{
	LineReleaseEx( &pvt->collect DBG_RELAY );
	LineReleaseEx( &pvt->commit DBG_RELAY );
	MemSet( pvt, 0, sizeof( VARTEXT ) );
}
//---------------------------------------------------------------------------
void VarTextAddCharacterEx( PVARTEXT pvt, char c DBG_PASS )
{
	if( !pvt->collect )
		VarTextInitEx( pvt DBG_RELAY );
	//fprintf( stderr, WIDE("Adding character %c\n"), c );
	pvt->collect_text[pvt->collect_used++] = c;
	if( pvt->collect_used == GetTextSize( pvt->collect ) )
	{
		//fprintf( stderr, WIDE("Expanding segment to make sure we have room to extend...\n") );
		pvt->collect = SegExpandEx( pvt->collect, COLLECT_LEN DBG_RELAY );
		pvt->collect_text = GetText( pvt->collect );
	}
}
//---------------------------------------------------------------------------
PTEXT VarTextEndEx( PVARTEXT pvt DBG_PASS )
{
 // otherwise ofs will be 0...
	if( pvt->collect_used )
	{
		PTEXT segs;
		segs = SegSplitEx( &pvt->collect, pvt->collect_used DBG_RELAY );
		//fprintf( stderr, WIDE("Breaking collection adding... %s\n"), GetText( segs ) );
		// so now the remaining buffer( if any )
		// is assigned to collect into.
		// This results in...
		pvt->collect = NEXTLINE( pvt->collect );
 // used all of the line...
		if( !pvt->collect )
		{
			//fprintf( stderr, WIDE("Starting with new buffers\n") );
			pvt->collect = SegCreateEx( COLLECT_LEN DBG_RELAY );
			pvt->collect_text = GetText( pvt->collect );
			pvt->collect_used = 0;
		}
		else
		{
			//Log1( WIDE("Remaining buffer is %d"), GetTextSize( pvt->collect ) );
			SegBreak( pvt->collect );
			pvt->collect_text = GetText( pvt->collect );
			pvt->collect_used = 0;
		}
		pvt->commit = SegAppend( pvt->commit, segs );
		//fprintf( stderr, WIDE("Resulting string: \'%s\' newly added vartextend\n"), GetText( segs ) );
		return segs;
	}
	if( pvt->commit )
	{
		//fprintf( stderr, WIDE("Resulting exsiting commit output...\n") );
		return pvt->commit;
	}
	//fprintf( stderr, WIDE("Resulting no output... var text end\n") );
	return NULL;
}
//---------------------------------------------------------------------------
PTEXT VarTextGetEx( PVARTEXT pvt DBG_PASS )
{
	if( VarTextEndEx( pvt DBG_RELAY ) )
	{
		PTEXT result = pvt->commit;
		pvt->commit = NULL;
		if( last_vartext_result )
		{
#ifdef __LINUX__
			if( last_vartext_result == result )
				asm( WIDE("int $3;\n") );
#endif
		}
		last_vartext_result = result;
		return result;
	}
	return NULL;
}
//---------------------------------------------------------------------------
void VarTextExpandEx( PVARTEXT pvt, int size DBG_PASS)
{
	pvt->collect = SegExpandEx( pvt->collect, size DBG_RELAY );
	pvt->collect_text = GetText( pvt->collect );
}
//---------------------------------------------------------------------------
size_t VarTextLength( PVARTEXT pvt )
{
	//Log1( WIDE("Length is : %d"), pvt->collect_used );
	return pvt->collect_used;
}
//---------------------------------------------------------------------------
int vtprintfEx( PVARTEXT pvt , char *format, ... )
//int vtprintfEx( PVARTEXT pvt DBG_PASS, char *format, ... )
{
	//char valid_char;
	va_list args;
	//Log1( WIDE("vtprintf...%s"), format );
	va_start( args, format );
	{
#if defined( __LINUX__ )
		// len returns number of characters (not NUL)
		int len = vsnprintf( NULL, 0, format, args );
		// allocate +1 for length with NUL
//		VarTextExpandEx( pvt, len+1 DBG_RELAY );
		VarTextExpand( pvt, len+1  );
		//Log3( WIDE("Print Length: %d into %d after %s"), len, pvt->collect_used, pvt->collect_text );
		// include NUL in the limit of characters able to print...
		  vsnprintf( pvt->collect_text + pvt->collect_used, len+1, format, args );
#elif defined( __WATCOMC__ )
		int len, destlen;
		do {
			va_start( args, format );
			len = vsnprintf( pvt->collect_text + pvt->collect_used
			               , destlen = GetTextSize( pvt->collect ) - pvt->collect_used
			               , format, args );
			if( len > destlen )
				VarTextExpand( pvt, len - destlen + 1 );
		} while( len > destlen );
#else
#if defined( GCC ) || defined( _MSC_VER )
	#define vsnprintf _vsnprintf
#endif
		int len;
		do {
			len = vsnprintf( pvt->collect_text + pvt->collect_used
			                , GetTextSize( pvt->collect ) - pvt->collect_used
			                , format, args );
			if( len < 0 )
				VarTextExpand( pvt, 32 );
//				VarTextExpandEx( pvt, 32 DBG_SRC );
		} while( len < 0 );
		//Log1( WIDE("Print Length: %d"), len );
#endif
		pvt->collect_used += len;
		return len;
	}
}
//#include <windows.h>
 // FILE *
 // includes text.h...
#define Collapse(towhere) SegConcat(towhere,begin,beginoffset,total)
//----------------------------------------------------------------------
char NextCharEx( PTEXT input, INDEX idx )
{
	if( ( ++idx ) >= input->data.size )
	{
		idx -= input->data.size;
		input = NEXTLINE( input );
	}
	if( input )
		return input->data.data[idx];
	return 0;
}
#define NextChar() NextCharEx( input, index )
//----------------------------------------------------------------------
static PTEXT BreakAndAddEx( char character, PTEXT outdata, VARTEXT *out, uint32_t *spaces, uint32_t *tabs )
{
	PTEXT word;
	if( ( word = VarTextGetEx( out DBG_SRC ) ) )
	{
		outdata = SegAdd( outdata, word );
		word->format.spaces = (uint16_t)*spaces;
		word->format.tabs = (uint16_t)*tabs;
		*spaces = 0;
		*tabs = 0;
		VarTextAddCharacterEx( out, character DBG_SRC );
		word = VarTextGetEx( out DBG_SRC );
		outdata = SegAdd( outdata, word );
	}
	else
	{
		VarTextAddCharacterEx( out, character DBG_SRC );
		word = VarTextGetEx( out DBG_SRC );
		word->format.spaces = (uint16_t)*spaces;
		word->format.tabs = (uint16_t)*tabs;
		*spaces = 0;
		*tabs = 0;
		outdata = SegAdd( outdata, word );
	}
	return outdata;
}
#define BreakAndAdd(c) outdata = BreakAndAddEx( c, outdata, &out, &spaces, &tabs )
//----------------------------------------------------------------------------
// translation trigraphs.....
/*
allll occurances of the following three character sets are
replaced without regard.
??= #
??( [
??/ ??) ]
??' ^
??< {
??! |
??> }
??- ~
*/
//void junk(void ) { char test [5]; }
static union {
	struct {
		uint32_t bLesser  : 1;
		uint32_t bGreater : 1;
		uint32_t bColon   : 1;
		uint32_t bPercent : 1;
		uint32_t bQuestion1 : 1;
		uint32_t bQuestion2 : 1;
	};
	uint32_t dw;
} flags;
#define DBG_OVERRIDE DBG_RELAY
static PTEXT OutputDanglingCharsEx( PTEXT outdata, VARTEXT *out, uint32_t *spaces, uint32_t *tabs )
#define OutputDanglingChars() outdata = OutputDanglingCharsEx( outdata, &out, &spaces, &tabs )
{
	int n = 0;
	if( flags.bPercent )
	{
		n++;
		outdata = BreakAndAddEx( '%', outdata, out, spaces, tabs );
		flags.bPercent = 0;
	}
	if( flags.bColon )
	{
		n++;
		outdata = BreakAndAddEx( ':', outdata, out, spaces, tabs );
		flags.bColon = 0;
	}
	if( flags.bLesser )
	{
		n++;
		outdata = BreakAndAddEx( '<', outdata, out, spaces, tabs );
		flags.bLesser = 0;
	}
	if( flags.bGreater )
	{
		n++;
		outdata = BreakAndAddEx( '>', outdata, out, spaces, tabs );
		flags.bGreater = 0;
	}
	if( flags.bQuestion2 )
	{
		n++;
		outdata = BreakAndAddEx( '?', outdata, out, spaces, tabs );
		outdata = BreakAndAddEx( '?', outdata, out, spaces, tabs );
		flags.bQuestion2 = 0;
		flags.bQuestion1 = 0;
	}
	if( flags.bQuestion1 )
	{
		n++;
		outdata = BreakAndAddEx( '?', outdata, out, spaces, tabs );
		flags.bQuestion1 = 0;
	}
	if( n > 1 )
	{
		fprintf( stderr, WIDE("%s(%d): Fixed %d dangling character - perhaps misordered output\n")
		       , GetCurrentFileName(), GetCurrentLine()
		       , n
		);
	}
	return outdata;
}
PTEXT burstEx( PTEXT input DBG_PASS )
// returns a TEXT list of parsed data
{
//#define DBG_OVERRIDE DBG_SRC
	/* takes a line of input and creates a line equivalent to it, but
	   burst into its block peices.*/
	VARTEXT out;
	PTEXT outdata=(PTEXT)NULL,
	      word;
	char *tempText;
	uint32_t index;
	INDEX size;
	uint8_t character;
	uint32_t elipses = FALSE
	    , spaces = 0
	    , tabs= 0
	    , escape = 0
 // just used for bi-graph/tri-graph stuff...
	    , quote = 0;
	flags.dw = 0;
        // if nothing new to process- return nothing processed.
	if (!input)
		return((PTEXT)NULL);
	VarTextInitEx( &out DBG_OVERRIDE );
  // while there is data to process...
	while (input)
	{
  // point to the data to process...
		tempText = GetText(input);
		size = GetTextSize(input);
		if( spaces )
		{
			//Log( WIDE("Need to figure out - new word, new spaces? old word? new spaces?") );
			//outdata = Collapse( outdata );
			//outdata->format.spaces = spaces;
			//spaces = 0;
			//set_offset = TRUE;
		}
		if( input->format.spaces || input->format.tabs )
		{
			word = VarTextGetEx( &out DBG_OVERRIDE );
			if( word )
			{
				word->format.spaces = (uint16_t)spaces;
				word->format.tabs = (uint16_t)tabs;
				spaces = 0;
				tabs = 0;
				outdata = SegAdd( outdata, word );
			}
		}
		spaces += input->format.spaces;
		tabs += input->format.tabs;
		//Log1( WIDE("Assuming %d spaces... "), spaces );
		for (index=0;(character = tempText[index]),
 // while not at the
		             (index < size); index++)
		                                   // end of the line.
		{
			if( elipses && character != '.' )
			{
				if( VarTextEndEx( &out DBG_OVERRIDE ) )
				{
					PTEXT word = VarTextGetEx( &out DBG_OVERRIDE );
					if( word )
					{
						word->format.spaces = (uint16_t)spaces;
						word->format.tabs = (uint16_t)tabs;
						spaces = 0;
						tabs = 0;
						outdata = SegAdd( outdata, word );
					}
					//else
					//	Log( WIDE("VarTextGet Failed to result.") );
				}
				elipses = FALSE;
			}
 // elipses and character is . - continue
			else if( elipses )
			{
				VarTextAddCharacterEx( &out, character DBG_OVERRIDE );
				continue;
			}
			if( !quote )
			{
				if( character == '<' )
				{
					if( flags.bLesser )
					{
						BreakAndAdd( '<' );
					}
					else
					{
						OutputDanglingChars();
						flags.bLesser = 1;
					}
					continue;
				}
				else if( character == '>' )
				{
					if( flags.bGreater )
					{
						BreakAndAdd( '>' );
					}
					else if( flags.bColon )
					{
						BreakAndAdd( ']' );
						flags.bColon = 0;
					}
					else if( flags.bPercent )
					{
						BreakAndAdd( '}' );
						flags.bPercent = 0;
					}
					else
					{
						OutputDanglingChars();
						flags.bGreater = 1;
					}
					continue;
				}
				else if( character == ':' )
				{
					if( flags.bLesser )
					{
						BreakAndAdd( '[' );
						flags.bLesser = 0;
					}
					else if( flags.bPercent )
					{
						BreakAndAdd( '#' );
						flags.bPercent = 0;
					}
					else if( flags.bColon )
					{
						BreakAndAdd( ':' );
					}
					else
					{
						OutputDanglingChars();
						flags.bColon = 1;
					}
					continue;
				}
				else if( character == '%' )
				{
					if( flags.bLesser )
					{
						BreakAndAdd( '{' );
						flags.bLesser = 0;
					}
					else if( flags.bPercent )
					{
						BreakAndAdd( '%' );
					}
					else
					{
						OutputDanglingChars();
						flags.bPercent = 1;
					}
					continue;
				}
				else
					OutputDanglingChars();
			}
			else if( flags.bQuestion2 )
			{
				if( character == '<' )
				{
					BreakAndAdd( '{' );
					flags.bQuestion2 = 0;
					flags.bQuestion1 = 0;
				}
				else if( character == '>' )
				{
					BreakAndAdd( '}' );
					flags.bQuestion2 = 0;
					flags.bQuestion1 = 0;
				}
				else if( character == '=' )
				{
					BreakAndAdd( '#' );
					flags.bQuestion2 = 0;
					flags.bQuestion1 = 0;
					continue;
				}
				else if( character == '(' )
				{
					BreakAndAdd( '[' );
					flags.bQuestion2 = 0;
					flags.bQuestion1 = 0;
					continue;
				}
				else if( character == '/' )
				{
					BreakAndAdd( '\\' );
					flags.bQuestion2 = 0;
					flags.bQuestion1 = 0;
					continue;
				}
				else if( flags.bQuestion2
				       && character == ')' )
				{
					BreakAndAdd( ']' );
					flags.bQuestion2 = 0;
					flags.bQuestion1 = 0;
					continue;
				}
				else if( flags.bQuestion2 &&
				         character == '\'' )
				{
					BreakAndAdd( '^' );
					flags.bQuestion2 = 0;
					flags.bQuestion1 = 0;
					continue;
				}
				else if( flags.bQuestion2 &&
				         character == '<' )
				{
					BreakAndAdd( '{' );
					flags.bQuestion2 = 0;
					flags.bQuestion1 = 0;
					continue;
				}
				else if( flags.bQuestion2 &&
				         character == '!' )
				{
					BreakAndAdd( '|' );
					flags.bQuestion2 = 0;
					flags.bQuestion1 = 0;
					continue;
				}
				else if( flags.bQuestion2 &&
				         character == '>' )
				{
					BreakAndAdd( '}' );
					flags.bQuestion2 = 0;
					flags.bQuestion1 = 0;
					continue;
				}
				else if( flags.bQuestion2 &&
				         character == '-' )
				{
					BreakAndAdd( '~' );
					flags.bQuestion2 = 0;
					flags.bQuestion1 = 0;
					continue;
				}
				else if( character == '?' )
				{
					BreakAndAdd( '?' );
				}
				else
				{
					fprintf( stderr, WIDE("%s(%d): Error unrecognized trigraph sequence!\n")
							, GetCurrentFileName()
							, GetCurrentLine() );
					OutputDanglingChars();
				}
			}
			else if( g.flags.do_trigraph &&
			         character == '?' )
			{
				if( flags.bQuestion2 )
				{
					BreakAndAdd( '?' );
				}
				else if( flags.bQuestion1 )
				{
					flags.bQuestion2 = 1;
				}
				else
					flags.bQuestion1 = 1;
				continue;
			}
			else
			{
				OutputDanglingChars();
			}
			if( !quote )
			{
				if( character == '\'' ||
					character == '\"' )
					quote = character;
			}
			else
			{
				if( !escape && quote == character )
					quote = 0;
				else if( !escape )
					if( character == '\\' )
					{
						escape = 1;
					}
					else
						escape = 0;
				else
					escape = 0;
			}
			switch(character)
			{
			case '\n':
				if( ( word = VarTextGetEx( &out DBG_OVERRIDE ) ) )
				{
					word->format.spaces = (uint16_t)spaces;
					word->format.tabs = (uint16_t)tabs;
 // fake a space next line...
					spaces = 0;
 // fake a space next line...
					tabs = 0;
					outdata = SegAdd( outdata, word );
				}
 // add a line-break packet
				outdata = SegAdd( outdata, SegCreate( 0 ) );
				break;
			case ' ':
			case '\t':
				if( ( word = VarTextGetEx( &out DBG_OVERRIDE ) ) )
				{
					word->format.spaces = (uint16_t)spaces;
					word->format.tabs = (uint16_t)tabs;
					spaces = 0;
					tabs = 0;
					outdata = SegAdd( outdata, word );
				}
				if( character == ' ' )
					spaces++;
				else
					tabs++;
				break;
 // a space space character...
			case '\r':
				if( ( word = VarTextGetEx( &out DBG_OVERRIDE ) ) )
				{
					word->format.spaces = (uint16_t)spaces;
					word->format.tabs = (uint16_t)tabs;
					spaces = 0;
					tabs = 0;
					outdata = SegAdd( outdata, word );
				}
				break;
 // handle multiple periods grouped (elipses)
			case '.':
				//goto NormalPunctuation;
				{
					char c;
					if( ( !elipses &&
							( c = NextChar() ) &&
							( c == '.' ) ) )
					{
						if( ( word = VarTextGetEx( &out DBG_OVERRIDE ) ) )
						{
							outdata = SegAdd( outdata, word );
							word->format.spaces = (uint16_t)spaces;
							word->format.tabs = (uint16_t)tabs;
							spaces = 0;
							tabs = 0;
						}
						VarTextAddCharacterEx( &out, '.' DBG_OVERRIDE );
						elipses = TRUE;
						break;
					}
					if( ( c = NextChar() ) &&
					    ( c >= '0' && c <= '9' ) )
					{
						// gather together as a floating point number...
						VarTextAddCharacterEx( &out, '.' DBG_OVERRIDE );
						break;
					}
				}
 // single quote bound
			case '\'':
 // double quote bound
			case '\"':
 // escape next thingy... unusable in c processor
			case '\\':
 // expression bounders
			case '(':
			case '{':
			case '[':
 // expression closers
			case ')':
			case '}':
			case ']':
  // work seperations flaming-long-sword
			case '-':
  // email addresses
			case '@':
			case '/':
			case ',':
			case ';':
			case '!':
			case '?':
			case '=':
			case '+':
			case '*':
			case '&':
			case '|':
			case '$':
			case '^':
			case '~':
			case '#':
			case '`':
				BreakAndAdd( character );
				break;
			default:
				if( elipses )
				{
					if( ( word = VarTextGetEx( &out DBG_OVERRIDE ) ) )
					{
						outdata = SegAdd( outdata, word );
						word->format.spaces = (uint16_t)spaces;
						word->format.tabs = (uint16_t)tabs;
						spaces = 0;
						tabs = 0;
					}
					elipses = FALSE;
				}
				VarTextAddCharacterEx( &out, character DBG_OVERRIDE );
				break;
			}
		}
		input=NEXTLINE(input);
	}
	if( flags.bPercent )
	{
		BreakAndAdd( '%' );
		flags.bPercent = 0;
	}
	if( flags.bColon )
	{
		BreakAndAdd( ':' );
		flags.bColon = 0;
	}
	if( flags.bLesser )
	{
		BreakAndAdd( '<' );
		flags.bLesser = 0;
	}
	if( flags.bGreater )
	{
		BreakAndAdd( '>' );
		flags.bGreater = 0;
	}
	if( flags.bQuestion2 )
	{
		BreakAndAdd( '?' );
		flags.bQuestion2 = 0;
	}
	if( flags.bQuestion1 )
	{
		BreakAndAdd( '?' );
		flags.bQuestion1 = 0;
	}
 // any generic outstanding data?
	if( ( word = VarTextGetEx( &out DBG_OVERRIDE ) ) )
	{
		outdata = SegAdd( outdata, word );
		word->format.spaces = (uint16_t)spaces;
		word->format.tabs = (uint16_t)tabs;
		spaces = 0;
		tabs = 0;
	}
	SetStart(outdata);
	VarTextEmptyEx( &out DBG_OVERRIDE );
	if( g.bDebugLog & DEBUG_READING )
	{
		fprintf( stddbg, WIDE("Returning segments:") );
		DumpSegs( outdata );
		fprintf( stddbg, WIDE("\n") );
	}
	return(outdata);
}
PTEXT get_line(FILE *source, int *line)
{
  // characters for workspace
	#define WORKSPACE 512
	PTEXT workline=(PTEXT)NULL,pNew;
	uintptr_t length = 0;
	if( !source )
		return NULL;
	do
	{
	LineContinues:
		// create a workspace to read input from the file.
		workline=SegAdd(workline,pNew=SegCreate(WORKSPACE));
		//workline = pNew;
		// SetEnd( workline );
		// read a line of input from the file.
 // if no input read.
		if( !fgets( GetText(workline), WORKSPACE, source) )
		{
 // if we've read some.
			if (PRIORLINE(workline))
			{
				PTEXT t;
 // go back one.
				t=PRIORLINE(workline);
				SegBreak(workline);
  // destroy the current segment.
				LineRelease(workline);
				workline = t;
			}
			else
			{
				// destory only segment.
				LineRelease(workline);
				workline = NULL;
			}
  // get out of the loop- there is no more to read.
			break;
		}
		{
			// this section of code shall map character trigraphs into a single
			// character... this preprocessor should/shall be unicode in nature
			// the FUTURE man not the past!
		}
  // get the length of the line.
		length = strlen(GetText(workline));
		if( workline )
			workline->data.size = length;
	}
 //while not at the end of the line.
	while (GetText(workline)[length-1]!='\n');
	if( length > 2 )
	{
		// auto drop \r from \r\n ...
		// since Linux refuses to be kind to dumb animals...
		if( GetText(workline)[length-2] == '\r' )
		{
			GetText(workline)[length-2] = GetText(workline)[length-1];
			length--;
		}
	}
	(*line)++;
	if( workline && (GetText(workline)[length-1]=='\n' ) )
	{
		if( length > 1 && GetText(workline)[length-2] == '\\' )
		{
			workline->data.data[length-2] = 0;
			workline->data.size = length-2;
			goto LineContinues;
		}
		else
		{
			// consider the possibility of ignoring whitespace between a \ \n
			// this will ease some effort on editing to kill end of line spaces...
			// but as of yet is non standard - and is non comilant to iso9899:1999
			workline->data.data[length-1] = 0;
			workline->data.size = length-1;
		}
	}
  // if I got a line, and there was some length to it.
	if (workline)
   // set workline to the beginning.
		SetStart(workline);
      // return the line read from the file.
	return(workline);
}
#include <errno.h>
//----------------------------------------------------------------------
// all files in Root->pAlso are top level dependancies.
static PFILEDEP FileDependancyRoot;
void FixSlashes( char *path )
{
	if( g.flags.bForceForeslash )
	{
		while( path[0] )
		{
			if( path[0] == '\\' )
				path[0] = '/';
			path++;
		}
	}
	else if( g.flags.bForceBackslash )
	{
		while( path[0] )
		{
			if( path[0] == '/' )
				path[0] = '\\';
			path++;
		}
	}
}
//----------------------------------------------------------------------
int CurrentFileDepth( void )
{
	int n = 0;
	PFILETRACK pft;
	for( pft = g.pFileStack; pft; n++, pft = pft->prior );
	return n;
}
//----------------------------------------------------------------------
void SetCurrentPath( char *path )
{
	strcpy( g.pCurrentPath.data.data, path );
	g.pCurrentPath.data.size = strlen( path );
}
//----------------------------------------------------------------------
PFILEDEP FindDependFile( PFILEDEP root, char *filename )
{
	PFILEDEP pDep = root, next;
	while( pDep )
	{
		next = pDep->pAlso;
		if( (!strcmp( pDep->base_name, filename )) ||
		    ( pDep = FindDependFile( pDep->pDependsOn, filename ) ) )
		{
			return pDep;
		}
		pDep = next;
	}
	return NULL;
}
//----------------------------------------------------------------------
LOGICAL AlreadyLoaded( char *filename )
{
	PFILEDEP dep;
	if( dep = FindDependFile( FileDependancyRoot, filename ) ) {
		if( dep->bAllowMultipleInclude )
			return FALSE;
		return TRUE;
	}
	return FALSE;
}
//----------------------------------------------------------------------
PFILEDEP AddDepend( PFILEDEP root, char *basename, char *filename )
{
	PFILEDEP pfd = root;
	if( !root )
		root = FileDependancyRoot;
	//fprintf( stderr, WIDE("Adding dependancy for: %s %s\n"), root?root->full_name:"Base File", filename );
	while( pfd && pfd->pDependedBy )
		pfd = pfd->pDependedBy;
	if( !( pfd = FindDependFile( pfd, basename ) ) )
	{
		pfd = Allocate( sizeof( FILEDEP ) );
		strcpy( pfd->base_name, basename );
		strcpy( pfd->full_name, filename );
		pfd->bAllowMultipleInclude = FALSE;
		pfd->pAlso = NULL;
		pfd->pDependsOn = NULL;
		pfd->pDependedBy = NULL;
		if( root )
		{
			// this file is included by what?
			pfd->pDependedBy = root;
			// link this as another file depended file of root...
			pfd->pAlso = root->pDependsOn;
			root->pDependsOn = pfd;
		}
		else
		{
			pfd->pAlso = FileDependancyRoot;
			FileDependancyRoot = pfd;
		}
		{
			PFILEDEP pCheck = pfd->pDependedBy;
			int count = 1;
			while( pCheck )
			{
				if( strcmp( pCheck->full_name, pfd->full_name ) == 0 )
				{
					fprintf( stderr, WIDE("Check name matched...\n") );
					count++;
					if( count > 3 )
					{
						PFILEDEP pDump = pfd->pDependedBy;
						fprintf( stderr, WIDE("Possible header recursion: \'%s\'"), pfd->full_name );
						while( pDump && pDump != pCheck )
						{
							fprintf( stderr, WIDE(" included by \'%s\'"), pDump->full_name );
							pDump = pDump->pDependedBy;
						}
						fprintf( stderr, WIDE("\n") );
						fprintf( stderr, WIDE("Aborting processing.\n") );
						exit(0);
					}
				}
				pCheck = pCheck->pDependedBy;
			}
		}
		return pfd;
	}
	return pfd;
}
//----------------------------------------------------------------------
PFILEDEP AddFileDepend( PFILETRACK pft, char *basename, char *filename ) {
	return AddDepend( pft->pFileDep, basename, filename );
}
//----------------------------------------------------------------------
void DumpDependLevel( PFILEDEP pfd, int level )
{
	PFILEDEP pDep = pfd->pDependsOn;
	if( pDep )
	{
		if( !level && g.AutoTargetName[0] && !pfd->pDependedBy )
		{
			fprintf( g.AutoDependFile, WIDE("%s:%s "), g.AutoTargetName, pfd->full_name );
		}
		//else if( level )
		//	fprintf( g.AutoDependFile, WIDE("%s "), pfd->name );
		//fprintf( g.AutoDependFile, WIDE("%s:"), pfd->name );
		while( pDep )
		{
			fprintf( g.AutoDependFile, WIDE("%s "), pDep->full_name );
			pDep = pDep->pAlso;
		}
		// for all files which this one depended on,
		// dump the files those depend on...
		pDep = pfd->pDependsOn;
		while( pDep )
		{
			if( pDep->pDependsOn )
				DumpDependLevel( pDep, ++level );
			pDep = pDep->pAlso;
		}
		//fprintf( g.AutoDependFile, WIDE("\n") );
	}
}
//----------------------------------------------------------------------
void DumpDepends( void )
{
	int level = 0;
	// trace through root files....
	PFILEDEP pfd = FileDependancyRoot;
	if( !g.AutoDependFile )
		g.AutoDependFile = stdout;
	while( pfd )
	{
		// post increment to make sure we start at 0...
		DumpDependLevel( pfd, level++ );
		pfd = pfd->pAlso;
	}
	  fprintf( g.AutoDependFile, WIDE("\n") );
}
//----------------------------------------------------------------------
void DestroyDependLevel( PFILEDEP pfd )
{
	PFILEDEP pDep = pfd->pDependsOn, next;
	//if( pfd )
	//	fprintf( stderr, WIDE("destory level...%s \n"), pfd->name );
	if( pDep )
	{
		//pDep = pfd->pDependsOn;
		while( pDep )
		{
			next = pDep->pAlso;
			DestroyDependLevel( pDep );
			pDep = next;
		}
	}
	if( pfd )
		Release( pfd );
}
//----------------------------------------------------------------------
void DestoyDepends( void )
{
	PFILEDEP pfd = FileDependancyRoot, next;
	while( pfd )
	{
		next = pfd->pAlso;
		DestroyDependLevel( pfd );
		pfd = next;
	}
	FileDependancyRoot = NULL;
}
//----------------------------------------------------------------------
int GetCurrentLine( void )
{
	if( g.pFileStack )
		return g.pFileStack->nLine;
	return 0;
}
//----------------------------------------------------------------------
char *GetCurrentFileName( void )
{
	if( g.pFileStack )
		return g.pFileStack->longname;
	return "<Command Line>";
	//return NULL;
}
//----------------------------------------------------------------------
char *FixName( char *file )
{
	static char realname[__MAX_PATH__];
	if( file[0] != '/' && file[1] != ':' )
		snprintf( realname, __MAX_PATH__, WIDE("%s/%s"), g.pWorkPath, file );
	else
		strcpy( realname, file );
	{
		char *tmp;
		while( tmp = strstr( realname, ".." ) ) {
			if( tmp == realname ) {
				break;
			}
			if( tmp[-1] == '/' || tmp[-1] == '\\' ) {
				char *start;
				tmp[-1] = 0;
				start = pathrchr( realname );
				{ int n; for( n = 0; start[n] = tmp[2+n]; n++ ); }
			}
		}
	}
   //printf( "file %s becomes %s\n", file, realname );
	return realname;
}
//----------------------------------------------------------------------
char *GetCurrentShortFileName( void )
{
	if( g.pFileStack )
		return g.pFileStack->name;
	return NULL;
}
//----------------------------------------------------------------------
void GetCurrentFileLine( char *name, int *line )
{
	if( name )
		strcpy( name, GetCurrentFileName() );
	if( line )
		*line = GetCurrentLine();
}
//----------------------------------------------------------------------
void WriteLineInfo( char *name, int line )
{
	FILE *out = GetCurrentOutput();
	static char  LastFileWritten[__MAX_PATH__];
	static int	LastLineWritten;
	if( out )
	{
		LastLineWritten++;
 // not match
		if( strcmp( name, LastFileWritten ) ||
		    line != LastLineWritten )
		{
			strcpy( LastFileWritten, GetCurrentFileName() );
			LastLineWritten = line;
			if( g.flags.bWriteLineInfo )
			{
			if( g.flags.bLineUsesLineKeyword )
			{
				fprintf( out, WIDE("#line %d \"%s\"\n")
				       //"//line %s(%d)\n"
				       , LastLineWritten
				       , LastFileWritten
				       );
			}
			else
			{
				// gcc is wonderful, eh?
				fprintf( out, WIDE("# %d \"%s\"\n")
				       //"//line %s(%d)\n"
				       , LastLineWritten
				       , LastFileWritten
				       );
			}
			}
		}
	}
}
//----------------------------------------------------------------------
void WriteCurrentLineInfo( void )
{
	WriteLineInfo( GetCurrentFileName(), GetCurrentLine() );
}
//----------------------------------------------------------------------
void WriteLine( size_t len, char *line )
{
	FILE *out = GetCurrentOutput();
	if( out )
	{
		fwrite( line, len, 1, out );
		fputc( '\n', out );
		//fflush( out );
	}
	//fprintf( out, WIDE("%s\n"), line );
}
//----------------------------------------------------------------------
PTEXT GetCurrentWord( void )
{
	if( g.pFileStack )
		return g.pFileStack->pNextWord;
	return NULL;
}
//----------------------------------------------------------------------
PTEXT *GetCurrentTextLine( void )
{
	if( g.pFileStack )
		return &g.pFileStack->pParsed;
	return NULL;
}
//----------------------------------------------------------------------
PTEXT GetNextWord( void )
{
	if( g.pFileStack )
		return g.pFileStack->pNextWord = NEXTLINE( g.pFileStack->pNextWord );
	return NULL;
}
//----------------------------------------------------------------------
void SetCurrentWord( PTEXT word )
{
	if( g.pFileStack->pParsed )
	if( g.pFileStack->pNextWord == g.pFileStack->pParsed )
		g.pFileStack->pParsed = word;
	g.pFileStack->pNextWord = word;
}
//----------------------------------------------------------------------
FILE *GetCurrentOutput(void)
{
	if( !g.flags.bNoOutput )
	{
		return g.output;
	}
	return NULL;
}
//----------------------------------------------------------------------
PTEXT StepCurrentWord( void )
{
	if( g.pFileStack )
		return g.pFileStack->pNextWord = NEXTLINE( g.pFileStack->pNextWord );
	return NULL;
}
//----------------------------------------------------------------------
// root level open.
uintptr_t OpenInputFile( char *basename, char *file )
{
	PFILETRACK pft;
	FILE *fp;
	char *tmp;
	if( g.pFileStack )
	{
			fprintf( stderr, WIDE("warning: Already have a root level file open.") );
	}
	if( AlreadyLoaded( basename ) )
	{
		return 0;
	}
	fp = fopen( tmp = FixName(file), WIDE("rt") );
	if( fp )
	{
		pft = (PFILETRACK)Allocate( sizeof( FILETRACK ) );
		pft->bBlockComment = 0;
		pft->nLine = 0;
		pft->file = fp;
		pft->nIfLevel = g.nIfLevels;
		strcpy( pft->name, file );
		strcpy( pft->longname, tmp );
		FixSlashes( pft->longname );
		pft->line = NULL;
		//pft->output = NULL;
		pft->pParsed = NULL;
		pft->pNextWord = NULL;
		pft->prior = g.pFileStack;
		//fprintf( stderr, WIDE("Add in OpenInputFile\n") );
		pft->pFileDep = AddDepend( NULL, basename, tmp );
		g.pFileStack = pft;
	}
	else
		pft = NULL;
	return (uintptr_t)pft;
}
//----------------------------------------------------------------------
uintptr_t OpenNewInputFile( char *basename, char *name, char *pFile, int nLine, int bDepend, int bNext )
{
	PFILETRACK pft = g.pFileStack;
	PFILETRACK pftNew = NULL;
	FILE *fp;
	char *tmp;
	if( bNext )
	{
		PFILETRACK pftTest = g.pFileStack;
		while( pftTest )
		{
			if( strcmp( name, pftTest->name ) == 0 )
				return FALSE;
			pftTest = pftTest->prior;
		}
	}
	fp = fopen( tmp = FixName(name), WIDE("rt") );
	if( fp )
	{
		pftNew = (PFILETRACK)Allocate( sizeof( FILETRACK ) );
		pftNew->bBlockComment = 0;
		pftNew->nLine = 0;
		pftNew->file = fp;
		pftNew->nIfLevel = g.nIfLevels;
		strcpy( pftNew->name, name );
		strcpy( pftNew->longname, tmp );
		FixSlashes( pftNew->longname );
		// move the current line to the current file... (so we can log #include?)
		pftNew->line = NULL;
		pftNew->pNextWord = pft->pNextWord;
		pft->pNextWord = NULL;
		//pftNew->output = pft->output;
		pftNew->pParsed = NULL;
		pftNew->pNextWord = NULL;
		pftNew->prior = g.pFileStack;
		if( bDepend && ( pft->pFileDep ) )
		{
			//fprintf( stderr, WIDE("Add in OpenNewInputFile\n") );
			pftNew->pFileDep = AddDepend( pft->pFileDep, basename, tmp );
		}
		else
			pftNew->pFileDep = NULL;
		g.pFileStack = pftNew;
	}
	return (uintptr_t)pftNew;
}
//----------------------------------------------------------------------
uintptr_t OpenOutputFile( char *newfile )
{
	//PFILETRACK pft = g.pFileStack;
	//if( pft )
	{
		g.output = fopen( FixName( newfile ), WIDE("wb") );
		if( g.output )
		{
			return 1;
		}
	}
	return 0;
}
//----------------------------------------------------------------------
uintptr_t OpenStdOutputFile( void )
{
	PFILETRACK pft = g.pFileStack;
	if( pft )
	{
		g.output = stdout;
		//if( pft->output )
		{
			return 1;
		}
	}
	return 0;
}
//----------------------------------------------------------------------
void CloseInputFileEx( DBG_VOIDPASS )
{
	PFILETRACK pft = g.pFileStack;
	if( pft->nIfLevel != g.nIfLevels )
	{
		fprintf( stderr, WIDE("Warning: Unmatched #if/#endif in %s (%d extra #if)\n")
		       , pft->longname
		       , g.nIfLevels - pft->nIfLevel );
	}
	if( pft->file )
	{
		fclose( pft->file );
		pft->file = NULL;
	}
	if( !pft->prior )
	{
		//if( pft->output )
		{
			//fclose( pft->output );
			//pft->output = NULL;
		}
	}
	if( pft->line )
		LineRelease( pft->line );
	if( pft->pParsed )
		LineRelease( pft->pParsed );
	pft->line = NULL;
	pft->pParsed = NULL;
	g.pFileStack = pft->prior;
	ReleaseExx( (void**)&pft DBG_RELAY );
}
//----------------------------------------------------------------------
void CloseAllFiles( void )
{
	while( g.pFileStack )
		CloseInputFile();
}
//----------------------------------------------------------------------
PTEXT ReadLineEx( int Append DBG_PASS )
{
	PFILETRACK pft;
	PTEXT pNew;
Restart:
	pft = g.pFileStack;
	if( !pft  )
		return NULL;
	do
	{
		int bContinue;
		PTEXT current;
 // loop this far when comments consume entire line...
	GetNewLine:
		if( pft->line && (pft->pParsed == pft->line) )
			DebugBreak();
		if( pft->line )
			LineReleaseEx( &pft->line DBG_RELAY );
		pft->line = NULL;
		if( !Append && ( pft->pParsed != pft->line ) )
		{
			current = pft->pParsed;
			do {
				if( ( ( (uintptr_t)current)&0xFFFF0000) == (uintptr_t)0xDDDD0000U )
				{
					DebugBreak();
				}
				current = NEXTLINE( current );
			} while( current );
			if( pft->pParsed )
			{
				current = pft->pParsed;
				LineReleaseEx( &pft->pParsed DBG_RELAY );
			}
			pft->pNextWord = NULL;
		}
		bContinue = 0;
		do
		{
			pft->line = SegAppend( pft->line, current = get_line( pft->file, &pft->nLine ) );
			if( !current )
			{
				if( bContinue )
				{
					fprintf( stderr, WIDE("%s(%d) Warning: Continuation(\\) at end of file will continue to next file...\n"),
									GetCurrentFileName(), GetCurrentLine() );
				}
				CloseInputFile();
				goto Restart;
			}
			else
			{
				if( !current->format.spaces && pft->line != current )
					current->format.spaces = 1;
			}
			if( current->data.size > 0 && current->data.data[current->data.size-1] == '\\' )
			{
				current->data.data[current->data.size = (current->data.size-1)] = 0;
				bContinue = 1;
			}
			else
				bContinue = 0;
		}while( pft && !pft->line && !bContinue );
		if( !pft || !pft->line )
		{
			if( g.bDebugLog & DEBUG_READING )
			{
				fprintf( stddbg, WIDE("Returning NULL line...\n") );
			}
			return NULL;
		}
		pNew = burst( pft->line );
		// strip blank lines...
		if( pNew && !GetTextSize( pNew ) )
		{
			if( g.bDebugLog & DEBUG_READING )
			{
				printf( WIDE("No content...") );
			}
			LineRelease( pNew );
			goto GetNewLine;
		}
		{
			PTEXT p, pStart = NULL;
 // set to current quote to match ... " or '
			int quote  = 0;
 // if(quote) and prior == '\' skip " or ' chars
			int escape = 0;
			int nSlash = 0;
			int nStar  = 0;
			int nLessthan = 0;
			int nGreaterthan = 0;
			int nPercent = 0;
			for( p = pNew; p; p = NEXTLINE( p ) )
			{
				char *pText;
			ContinueNoIncrement:
				pText = GetText( p );
				if( !pft->bBlockComment )
				{
					if( !quote )
					{
						if( pText[0] == '\'' )
						{
							quote = '\'';
							continue;
						}
						else if( pText[0] == '\"' )
						{
							quote = '\"';
							continue;
						}
					}
				}
				if( quote )
				{
					if( !escape )
					{
						if( pText[0] == '\\' )
							escape = 1;
						else if( pText[0] == quote )
							quote = 0;
					}
					else
						escape = 0;
				}
				else if( pText[0] == '/'  )
				{
					if( g.bDebugLog & DEBUG_READING )
					{
						fprintf( stddbg, WIDE("Have a slash...\n") );
					}
 // leading stars up to close...
					if( nStar )
					{
						if( g.bDebugLog & DEBUG_READING )
						{
							fprintf( stddbg, WIDE("ending comment...\n") );
						}
						if( p->format.spaces )
						{
							nStar = 0;
							continue;
						}
						nStar = 0;
						if( !pft->bBlockComment )
						{
							// this may be the case - may also be a case of invalid paramters....
							// */ is an illegal operator combination anyhow....
							fprintf( stderr, WIDE("%s(%d) Warning: close block comment which was not started.\n")
											, pft->name, pft->nLine );
						}
						pft->bBlockComment = 0;
 // began on this line.... ending here also
						if( pStart )
						{
							if( g.bDebugLog & DEBUG_READING )
							{
								fprintf( stddbg, WIDE("had a start of comment...\n") );
							}
							if( NEXTLINE( p ) )
							{
								p = NEXTLINE( p );
								SegBreak( p );
								if( g.flags.keep_comments )
								{
									PTEXT pOut;
									pOut = BuildLineEx( pStart, FALSE DBG_SRC );
									if( pOut )
									{
										if( g.flags.bWriteLine )
										{
											WriteCurrentLineInfo();
										}
										WriteLine( GetTextSize( pOut ), GetText( pOut ) );
										LineRelease( pOut );
									}
								}
								if( pStart != pNew )
									SegAppend( SegBreak( pStart ), p );
								else
								{
									pNew = p;
								}
								LineRelease( pStart );
								pStart = NULL;
								goto ContinueNoIncrement;
							}
							else
							{
								if( g.bDebugLog & DEBUG_READING )
								{
									fprintf( stddbg, WIDE("Trailing part of line was block comment...\n") );
								}
								// whole line is a block comment...
								if( pStart == pNew )
								{
									if( g.bDebugLog & DEBUG_READING )
									{
										fprintf( stddbg, WIDE("while line In block comment...") );
									}
									if( g.flags.keep_comments
 /*&&
									   ( !g.flags.bSkipSystemIncludeOut && !g.flags.doing_system_file )*/
									   )
									{
										PTEXT pOut;
										pOut = BuildLineEx( pNew, FALSE DBG_SRC );
										if( pOut )
										{
											if( g.flags.bWriteLine )
											{
												WriteCurrentLineInfo();
											}
											WriteLine( GetTextSize( pOut ), GetText( pOut ) );
											LineRelease( pOut );
										}
									}
									LineRelease( pNew );
									goto GetNewLine;
								}
								// else there is something before left...
								SegBreak( pStart );
								LineRelease( pStart );
 // loop ends anyway...
								break;
							}
						}
						else
						{
							// up to this point we have been in a block comment
							if( NEXTLINE( p ) )
							{
								p = NEXTLINE( p );
								SegBreak( p );
								if( g.flags.keep_comments )
								{
									PTEXT pOut;
									pOut = BuildLineEx( pNew, FALSE DBG_SRC );
									if( pOut )
									{
										if( g.flags.bWriteLine )
										{
											WriteCurrentLineInfo();
										}
										WriteLine( GetTextSize( pOut ), GetText( pOut ) );
										LineRelease( pOut );
									}
								}
								LineRelease( pNew );
								pNew = p;
								goto ContinueNoIncrement;
							}
							else
							{
								// entire line within block comment...
								//printf( WIDE("in block comment... ") );
								if( g.flags.keep_comments )
								{
									PTEXT pOut;
									pOut = BuildLineEx( pNew, FALSE DBG_SRC );
									if( pOut )
									{
										if( g.flags.bWriteLine )
										{
											WriteCurrentLineInfo();
										}
										WriteLine( GetTextSize( pOut ), GetText( pOut ) );
										LineRelease( pOut );
									}
								}
								LineRelease( pNew );
								goto GetNewLine;
							}
						}
					}
					if( !nSlash && !nStar &&
						( !pft->bBlockComment ) )
					{
						if( g.bDebugLog & DEBUG_READING )
						{
							fprintf( stddbg, WIDE("Marking begin...\n") );
						}
						pStart = p;
					}
					else
					{
						if( g.bDebugLog & DEBUG_READING )
						{
							fprintf( stddbg, WIDE("Pending states: %s%s%s\n")
									, nSlash?"nSlash ":""
									, nStar?"nStar ":""
									, pft->bBlockComment?"In block": "" );
						}
					}
					if( !(pft->bBlockComment ) )
					{
						if( nSlash )
						{
							if( p->format.spaces )
							{
 // reset/set count...
								nSlash = 1;
								continue;
							}
						}
						nSlash++;
						if( nSlash >= 2 )
						{
							if( pStart == pNew )
							{
								// releasing the whole line...
								//printf( WIDE("Whole line commented...\n") );
								if( g.flags.keep_comments )
								{
									PTEXT pOut;
									// throw in a newline, comments end up above the actual line
									// should force a #line indicator also?
									//SegAppend( pNew, SegCreate(0));
									pOut = BuildLineEx( pNew, FALSE DBG_SRC );
									if( pOut )
									{
										if( g.flags.bWriteLine )
										{
											WriteCurrentLineInfo();
										}
										WriteLine( GetTextSize( pOut ), GetText( pOut ) );
										LineRelease( pOut );
									}
								}
								// internally we keep pParsed which is what pNew is also...
								// pParsed will delete pNew
								//LineRelease( pNew );
								goto GetNewLine;
							}
							SegBreak( pStart );
							if( g.flags.keep_comments )
							{
								PTEXT pOut;
								// throw in a newline, comments end up above the actual line
								// should force a #line indicator also?
								pOut = BuildLineEx( pStart, FALSE DBG_SRC );
								if( pOut )
								{
									if( g.flags.bWriteLine )
									{
											WriteCurrentLineInfo();
									}
									WriteLine( GetTextSize( pOut ), GetText( pOut ) );
									LineRelease( pOut );
								}
							}
							LineRelease( pStart );
							break;
						}
					}
				}
				else if( pText[0] == '*' )
				{
					if( g.bDebugLog & DEBUG_READING )
					{
						fprintf( stddbg, WIDE("found a star... was there a slash?\n") );
					}
 // begin block comment
					if( nSlash == 1 )
					{
						if( p->format.spaces )
						{
							nSlash = 0;
 // set/reset count.
							nStar = 1;
							continue;
						}
						if( g.bDebugLog & DEBUG_READING )
						{
							fprintf( stddbg, WIDE("okay defineatly block comment...\n") );
						}
						if( pft->bBlockComment )
							nStar++;
						else
							pft->bBlockComment = TRUE;
					// pStart should point to the beginning '/' already
					// /*/ is not a valid comment but /**/ is.
					}
					else
					{
						if( p->format.spaces )
						{
 // set/reset count.
							nStar = 1;
							continue;
						}
						if( g.bDebugLog & DEBUG_READING )
						{
							fprintf( stddbg, WIDE("Adding another star...\n") );
						}
 // this is beginning of end block comment maybe
						nStar++;
					}
					// begin block comment....
				}
 // character is neither a '/' or a '*'
				else
				{
					nSlash = 0;
					nStar = 0;
				}
			}
 // fell off end of line without a close on this.
			if( pft->bBlockComment )
			{
				if( g.bDebugLog & DEBUG_READING )
				{
					fprintf( stddbg, WIDE("Daning block comment - continue reading...\n") );
				}
				if( pStart )
				{
					// began a block comment, but it continues....
					if( pStart == pNew )
					{
						//printf( WIDE("In Block comment(3)...\n") );
						if( g.flags.keep_comments )
						{
							PTEXT pOut;
							pOut = BuildLineEx( pNew, FALSE DBG_SRC );
							if( pOut )
							{
								if( g.flags.bWriteLine )
								{
									WriteCurrentLineInfo();
								}
								WriteLine( GetTextSize( pOut ), GetText( pOut ) );
								LineRelease( pOut );
							}
						}
						LineRelease( pNew );
 // this block started here and was whole line
						goto GetNewLine;
					}
					else
					{
						PTEXT pOut;
						SegBreak( pStart );
						pOut = BuildLineEx( pNew, FALSE DBG_SRC );
						if( pOut )
						{
							if( g.flags.bWriteLine )
							{
								WriteCurrentLineInfo();
							}
							WriteLine( GetTextSize( pOut ), GetText( pOut ) );
							LineRelease( pOut );
						}
						LineRelease( pNew );
						pNew = pStart;
					}
				if( !g.flags.keep_comments ) {
					SegBreak( pStart );
					LineRelease( pStart );
				}
				/*
					if( g.flags.keep_comments )
					{
						PTEXT pOut;
						pOut = BuildLineEx( pStart, FALSE DBG_SRC );
						if( pOut )
						{
							if( g.flags.bWriteLine )
							{
								WriteCurrentLineInfo();
							}
							WriteLine( GetTextSize( pOut ), GetText( pOut ) );
							LineRelease( pOut );
						}
					}
					*/
				}
				else
				{
					//printf( WIDE("In Block comment(3)...\n") );
					// ignore this line completely!
					if( g.flags.keep_comments )
					{
						PTEXT pOut = BuildLineEx( pNew, FALSE DBG_SRC );
						if( pOut )
						{
							if( g.flags.bWriteLine )
							{
								WriteCurrentLineInfo();
							}
							WriteLine( GetTextSize( pOut ), GetText( pOut ) );
							LineRelease( pOut );
						}
					}
					LineRelease( pNew );
					goto GetNewLine;
				}
			}
		}
	}while( !pNew );
	//printf( WIDE("Adding %lp to %lp\n"), pNew, pft->pParsed );
	pft->pParsed = SegAppend( pft->pParsed, pNew );
	if( !Append )
		pft->pNextWord = pNew;
	if( g.bDebugLog & DEBUG_READING )
	{
		fprintf(stddbg, WIDE("Readline result: ") );
		DumpSegs( pNew );
		fprintf( stddbg, WIDE("\n") );
	}
	return pNew;
}
char *pathrchr( char *path )
{
	char *end1, *end2;
	end1 = strrchr( path, '\\' );
	end2 = strrchr( path, '/' );
	if( end1 > end2 )
		return end1;
	return end2;
}
//-----------------------------------------------------------------------
char *pathchr( char *path )
{
	char *end1, *end2;
	end1 = strchr( path, '\\' );
	end2 = strchr( path, '/' );
	if( end1 && end2 )
	{
		if( end1 < end2 )
			return end1;
		return end2;
	}
	else if( end1 )
		return end1;
	else if( end2 )
		return end2;
	return NULL;
}
//----------------------------------------------------------------------
// Expressions parser, processor
//   Limitation - handles only constant expressions
//   Limitation - expects expression to be on one continuous line
//                which is acceptable for the cpp layer.
//----------------------------------------------------------------------
#define C_PRE_PROCESSOR
 // debug only...
typedef struct opnode {
	int op;
	union {
		LONGEST_INT i;
		LONGEST_FLT f;
		PTEXT string;
		struct opnode *sub;
	} data;
	struct opnode *left, *right;
} OPNODE, *POPNODE;
static char pHEX[] = "0123456789ABCDEF";
static char phex[] = "0123456789abcdef";
/*
 Section Category Operators
7.5 Primary           x.y  f(x)  a[x]  x++  x--  new typeof  checked  unchecked
7.6 Unary             +  -  !  ~  ++x  --x  (T)x
7.7 Multiplicative    *  /  %
7.7 Additive          +  -
7.8 Shift             <<  >>
7.9 Relational and type testing <  >  <=  >=  is  as
7.9 Equality          ==  !=
7.10 Logical      AND &
7.10 Logical      XOR ^
7.10 Logical      OR  |
7.11 Conditional  AND &&
7.11 Conditional  OR ||
// both of these are right-associative
7.12 Conditional     ?:
7.13 Assignment      =  *=  /=  %=  +=  -=  <<=  >>=  &=  ^=  |=
*/
/*
 Section Category Operators (relevant to preprocessor)
 7.5 Primary           a[x] // should apply to const strings
                            // (results in an operand anyhow)
7.6 Unary             +  -  !  ~  // typecast? (T)x
7.7 Multiplicative    *  /  %
7.7 Additive          +  -
7.8 Shift             <<  >>
7.9 Relational and type testing <  >  <=  >=  is  as
7.9 Equality          ==  !=
7.10 Logical      AND &
7.10 Logical      XOR ^
7.10 Logical      OR  |
7.11 Conditional  AND &&
7.11 Conditional  OR ||
// both of these are right-associative
7.12 Conditional     ?:
*/
 // used to indicate prior op complete, please hang on tree
enum { OP_HANG = -1
		// after hanging, please re-check current symbol
     , OP_NOOP = 0
 // (...)
     , OP_SUBEXPRESSION
     , OP_INT_OPERAND_8
     , OP_INT_OPERAND_16
     , OP_INT_OPERAND_32
     , OP_INT_OPERAND_64
     , OP_SINT_OPERAND_8
     , OP_SINT_OPERAND_16
     , OP_SINT_OPERAND_32
     , OP_SINT_OPERAND_64
     , OP_FLT_OPERAND_32
     , OP_FLT_OPERAND_64
     , OP_CHARACTER_STRING
     , OP_CHARACTER_CONST
                     // =  equality
     , OP_SETEQUAL
                      // == comparison
     , OP_ISEQUAL
                         // +
     , OP_PLUS
                    // ++
     , OP_INCREMENT
                    // +=
     , OP_PLUSEQUAL
                        // -
     , OP_MINUS
                    // --
     , OP_DECREMENT
                   // -=
     , OP_MINUSEQUAL
                     // *
     , OP_MULTIPLY
                // *=
     , OP_MULTIPLYEQUAL
                          // %
     , OP_MOD
                     // %=
     , OP_MODEQUAL
                       // /
     , OP_DIVIDE
                  // /=
     , OP_DIVIDEEQUAL
                          // ^
     , OP_XOR
                     // ^=
     , OP_XOREQUAL
                    // ~
     , OP_BINARYNOT
                   // !
     , OP_LOGICALNOT
                     // !=
     , OP_NOTEQUAL
                      // >
     , OP_GREATER
                   // >>
     , OP_SHIFTRIGHT
                 // >=
     , OP_GREATEREQUAL
                     // >>=
     , OP_SHREQUAL
                       // <
     , OP_LESSER
                    // <<
     , OP_SHIFTLEFT
                  // <=
     , OP_LESSEREQUAL
                     // <<=
     , OP_SHLEQUAL
                    // &
     , OP_BINARYAND
                   // &&
     , OP_LOGICALAND
                     // &=
     , OP_ANDEQUAL
                     // |
     , OP_BINARYOR
                    // ||
     , OP_LOGICALOR
                      // |=
     , OP_OREQUAL
                   // ?
     , OP_COMPARISON
					// :
     , OP_ELSE_COMPARISON
     , OP_COMMA
     //, OP_DOT
     //, OP_
};
char *fullopname[] = { "noop", WIDE("sub-expr")
 // unsigned int
                     ,  "uint8_t",  "uint16_t",  "uint32_t",  "uint64_t"
 // signed int
                     , WIDE("int8_t"), WIDE("int16_t"), WIDE("int32_t"), WIDE("int64_t")
 // float ops
                     , WIDE("float"), WIDE("double")
                     , WIDE("string"), WIDE("character")
                     , WIDE("="), WIDE("==")
                     , WIDE("+"), WIDE("++"), WIDE("+=")
                     , WIDE("-"), WIDE("--"), WIDE("-=")
                     , WIDE("*"), WIDE("*=")
                     , WIDE("%"), WIDE("%=")
                     , WIDE("/"), WIDE("/=")
                     , WIDE("^"), WIDE("^=")
                     , WIDE("~")
                     , WIDE("!"), WIDE("!=")
                     , WIDE(">"), WIDE(">>"), WIDE(">="), WIDE(">>=")
                     , WIDE("<"), WIDE("<<"), WIDE("<="), WIDE("<<=")
                     , WIDE("&"), WIDE("&&"), WIDE("&=")
                     , WIDE("|"), WIDE("||"), WIDE("|=")
                     , WIDE("?"), WIDE(":"), WIDE(",")
                     };
typedef struct relation RELATION, *PRELATION;
struct relation {
	int thisop;
	struct {
		char ch;
		int becomes;
	}trans[16];
};
#define NUM_RELATIONS (sizeof(Relations)/sizeof(RELATION))
RELATION Relations[] = { { OP_NOOP      , { { '=', OP_SETEQUAL }
                                          , { '<', OP_LESSER }
                                          , { '>', OP_GREATER }
                                          , { '+', OP_PLUS }
                                          , { '-', OP_MINUS }
                                          , { '*', OP_MULTIPLY }
                                          , { '/', OP_DIVIDE }
                                          , { '%', OP_MOD }
                                          , { '^', OP_XOR }
                                          , { '~', OP_BINARYNOT }
                                          , { '!', OP_LOGICALNOT }
                                          , { '&', OP_BINARYAND }
                                          , { '|', OP_BINARYOR }
                                          , { '?', OP_COMPARISON }
                                          , { ':', OP_ELSE_COMPARISON }
                                          , { ',', OP_COMMA } } }
                       , { OP_SETEQUAL  , { { '=', OP_ISEQUAL } } }
                       , { OP_PLUS      , { { '+', OP_INCREMENT }
                                          , { '=', OP_PLUSEQUAL } } }
                       , { OP_MINUS     , { { '-', OP_DECREMENT }
                                          , { '=', OP_MINUSEQUAL } } }
                       , { OP_MULTIPLY  , { { '=', OP_MULTIPLYEQUAL } } }
                       , { OP_MOD       , { { '=', OP_MODEQUAL } } }
                       , { OP_DIVIDE    , { { '=', OP_DIVIDEEQUAL } } }
                       , { OP_XOR       , { { '=', OP_XOREQUAL } } }
                       , { OP_LOGICALNOT, { { '=', OP_NOTEQUAL } } }
                       , { OP_GREATER   , { { '>', OP_SHIFTRIGHT }
                                          , { '=', OP_GREATEREQUAL } } }
                       , { OP_SHIFTRIGHT, { { '=', OP_SHREQUAL } } }
                       , { OP_LESSER    , { { '<', OP_SHIFTLEFT }
                                          , { '=', OP_LESSEREQUAL } } }
                       , { OP_SHIFTLEFT , { { '=', OP_SHLEQUAL } } }
                       , { OP_BINARYAND , { { '&', OP_LOGICALAND }
                                          , { '=', OP_ANDEQUAL } } }
                       , { OP_BINARYOR  , { { '|', OP_LOGICALOR }
                                          , { '=', OP_OREQUAL } } }
                       };
//--------------------------------------------------------------------------
static POPNODE GetOpNodeEx( DBG_VOIDPASS )
#define GetOpNode() GetOpNodeEx( DBG_VOIDSRC )
{
	POPNODE pOp = AllocateEx( sizeof( OPNODE ) DBG_RELAY );
	memset( pOp, 0, sizeof( OPNODE ) );
	pOp->op     = OP_NOOP;
	return pOp;
}
//--------------------------------------------------------------------------
void DestroyExpressionEx( POPNODE root DBG_PASS );
#define DestroyExpression(r) DestroyExpressionEx(r DBG_SRC )
void DestroyOpNodeEx( POPNODE node DBG_PASS )
#define DestroyOpNode(n) DestroyOpNodeEx(n DBG_SRC)
{
	// delete any allocated content...
	if( node->op == OP_CHARACTER_STRING )
		LineRelease( node->data.string );
	else if( node->op == OP_SUBEXPRESSION )
		DestroyExpressionEx( node->data.sub DBG_RELAY );
	if( node->left )
		node->left->right = node->right;
	if( node->right )
		node->right->left = node->left;
	ReleaseExx( (void**)&node DBG_RELAY );
}
//--------------------------------------------------------------------------
void DestroyExpressionEx( POPNODE root DBG_PASS )
{
	POPNODE next;
	// go to the start of the expression...
	if( !root )
		return;
	while( root->left )
		root = root->left;
	next = root;
	while( root = next )
	{
		next = root->right;
		DestroyOpNodeEx( root DBG_RELAY );
	}
}
//--------------------------------------------------------------------------
void ExpressionBreak( POPNODE breakbefore )
{
	if( breakbefore->left )
	{
		breakbefore->left->right = NULL;
		breakbefore->left = NULL;
	}
}
//--------------------------------------------------------------------------
POPNODE SubstNodes( POPNODE _this_left, POPNODE _this_right, POPNODE that )
{
	if( _this_left && _this_right && that )
	{
		POPNODE that_left = that;
		POPNODE that_right = that;
		while( that_left->left )
			that_left = that_left->left;
		while( that_right->right )
			that_right = that_right->right;
		if( _this_left->left )
			_this_left->left->right = that_left;
		that_left->left = _this_left->left;
		_this_left->left = NULL;
		if( _this_right->right )
			_this_right->right->left = that_right;
		that_right->right = _this_right->right;
		_this_right->right = NULL;
		return _this_left;
	}
	return NULL;
}
//--------------------------------------------------------------------------
POPNODE SubstNode( POPNODE _this, POPNODE that )
{
	return SubstNodes( _this, _this, that );
}
//--------------------------------------------------------------------------
POPNODE GrabNodes( POPNODE start, POPNODE end )
{
	if( start->left )
		start->left->right = end->right;
	if( end->right )
		end->right->left = start->left;
	end->right = NULL;
	start->left = NULL;
	return start;
}
//--------------------------------------------------------------------------
POPNODE GrabNode( POPNODE _this )
{
	return GrabNodes( _this, _this );
}
//--------------------------------------------------------------------------
static int RelateOpNode( POPNODE *root, POPNODE node )
{
	if( !node )
	{
		fprintf( stderr, WIDE("Fatal Error: cannot relate a NULL node\n") );
		return 0;
	}
	if( !root )
	{
		fprintf( stderr, WIDE("Fatal error: Cannot build expression tree with NULL root.\n") );
		return 0;
	}
#ifdef C_PRE_PROCESSOR
	switch( node->op )
	{
	case OP_FLT_OPERAND_32:
	case OP_FLT_OPERAND_64:
	case OP_SETEQUAL:
	case OP_INCREMENT:
	case OP_PLUSEQUAL:
	case OP_DECREMENT:
	case OP_MINUSEQUAL:
	case OP_MULTIPLYEQUAL:
	case OP_MODEQUAL:
	case OP_XOREQUAL:
	case OP_SHREQUAL:
	case OP_SHLEQUAL:
	case OP_ANDEQUAL:
	case OP_OREQUAL:
		fprintf( stderr, WIDE("%s(%d) Error: preprocessor expression may not use operand %s\n")
		       , GetCurrentFileName(), GetCurrentLine(), fullopname[ node->op ] );
		DestroyOpNode( node );
		return 0;
		break;
	}
#endif
	if( !*root )
		*root = node;
	else
	{
		POPNODE last = *root;
		while( last && last->right )
		{
			last = last->right;
		}
		if( last )
		{
			node->left = last;
			last->right = node;
		}
	}
	return 1;
}
//--------------------------------------------------------------------------
// result : 0 = okay value
//          1 = float number ?
//          2 = invalid number...
static int GetInteger( LONGEST_INT *result, int *length )
{
	unsigned char *p = GetText( GetCurrentWord() );
	LONGEST_INT accum = 0;
	int neg = 0;
	int unsigned_value = 0;
	int long_value = 0;
	if( p[0] >= '0' && p[0] <= '9' )
	{
		  accum = 0;
		  if( p[0] == '0' && p[1] && ( p[1] == 'x' || p[1] == 'X' ) )
		  {
			  char *hexchar;
			  int okay = 1;
			  p += 2;
			  while( p[0] && okay )
			  {
				  if( hexchar = strchr( pHEX, p[0] ) )
				{
					  accum *= 16;
					  accum += hexchar - pHEX;
				  }
				  else if( hexchar = strchr( phex, p[0] ) )
				  {
					  accum *= 16;
					  accum += hexchar - phex;
				  }
				  else
				  {
					  okay = 0;
					  if( *p == '.' )
					  {
						  fprintf( stderr, WIDE("%s(%d) Error: Hexadecimal may not be used to define a float.\n"), GetCurrentFileName(), GetCurrentLine() );
 // invalid number.
						  return 2;
					  }
				  }
				p++;
			}
		  }
		  else if( p[0] == '0' )
		  {
			  // octal
			while( p[0] >= '0' && p[0] <= '7' )
			  {
				  accum *= 8;
				  accum += p[0] - '0';
				 p++;
			 }
			 if( p[0] == '.' )
			 {
				 return 1;
			 }
			 else if( p[0] )
			 {
				 if( p[0] < 32 )
					 fprintf( stderr, WIDE("%s(%d) Error: Octal constant has invalid character 0x%02x\n"), GetCurrentFileName(), GetCurrentLine() , p[0] );
				else
					 fprintf( stderr, WIDE("%s(%d) Error: Octal constant has invalid character '%c'\n"), GetCurrentFileName(), GetCurrentLine() , p[0] );
				 return 2;
			 }
		  }
		  else
		  {
			while( p[0] >= '0' && p[0] <= '9' )
			  {
				  accum *= 10;
				  accum += p[0] - '0';
				 p++;
			 }
			  if( *p == '.' )
 // invalid number... should consider as float after.
				  return 1;
		}
		  while( *p )
		  {
			if( *p == 'U' || *p == 'u' )
			{
				if( unsigned_value )
				{
					fprintf( stderr, WIDE("%s(%d) Error: U or u qualifiers specifed more than once on a constant.\n"), GetCurrentFileName(), GetCurrentLine()  );
					return 2;
				}
				unsigned_value = 1;
				p++;
			}
			else if( p[0] == 'l' || p[0] == 'L' )
			{
				if( long_value )
				{
					fprintf( stderr, WIDE("%s(%d) Error: too many L or l qualifiers specifed on a constant.\n"), GetCurrentFileName(), GetCurrentLine()  );
					return 2;
				}
				if( p[1] && ( p[1] == 'l' || p[1] == 'L' ) )
				{
					long_value = 2;
					p++;
				}
				else
					long_value = 1;
				p++;
			}
			else
			{
				if( p[0] < 32 )
					fprintf( stderr, WIDE("%s(%d) Error: Invalid type specification 0x%02x.\n")
					       , GetCurrentFileName(), GetCurrentLine(), p[1] );
				else
					fprintf( stderr, WIDE("%s(%d) Error: Invalid type specification '%c'.\n")
					       , GetCurrentFileName(), GetCurrentLine(), p[1] );
				return 2;
			}
		}
	}
	if( result )
		*result = accum;
	if( length )
		*length = long_value;
 // valid result now.
	return 0;
}
//--------------------------------------------------------------------------
// result 0: float value okay
//	     1: invalid conversion
//  this may require multiple tokens to resolve... '.' '-' '+' are all
// seperate symbols.
static int GetFloat( LONGEST_FLT *result, int *length )
{
	LONGEST_FLT accum = 0;
	//fprintf( stderr, WIDE("At this time 'expr.c' does not do float conversion...\n") );
	return 0;
}
//--------------------------------------------------------------------------
void LogExpression( POPNODE root )
{
	static int level;
	level++;
	while( root )
	{
		if( root->op == OP_SUBEXPRESSION )
		{
			fprintf( stderr, WIDE("( ") );
			LogExpression( root->data.sub );
			fprintf( stderr, WIDE(" )") );
		}
		else
		{
			fprintf( stderr, WIDE("(%s = %lld)"), fullopname[root->op],root->data.i );
		}
#ifdef __LINUX__
		if( root->right )
			if( root->right->left != root )
				asm( WIDE("int $3\n") );
#endif
		root = root->right;
	}
	level--;
	if( !level )
		fprintf( stderr, WIDE("\n") );
}
//--------------------------------------------------------------------------
// one might suppose that
// expressions are read ... left, current, right....
// and things are pushed off to the left and right of myself, and or rotated
// appropriately....
//
//     NULL
//     (op)+/-/##/(
//--------------------------------------------------------------------------
 // expression is queued
POPNODE BuildExpression( void )
{
	char *pExp;
	int nLastLogical = 0;
	int nResult = 0;
	int quote = 0;
	int overflow = 0;
	POPNODE ThisOp = GetOpNode();
	POPNODE branch = NULL;
	PTEXT thisword;
	//return 0; // force false output ... needs work on substitutions...
	//if( g.bDebugLog )
	//{
	//	fprintf( stddbg, WIDE("Build expression for: ") );
	//	DumpSegs( GetCurrentWord() );
	//}
	while( ( thisword = GetCurrentWord() ) )
	{
		int n;
		pExp = GetText( thisword );
		//printf( WIDE("word: %s\n"), pExp );
		if( pExp[0] == '\'' )
		{
			if( quote == '\'' )
			{
				overflow = 0;
				RelateOpNode( &branch, ThisOp );
				  ThisOp = GetOpNode();
				quote = 0;
			}
			else if( !quote )
			{
				ThisOp->op = OP_CHARACTER_CONST;
				quote = pExp[0];
			}
			StepCurrentWord();
			continue;
		}
		else if( pExp[0] == '\"' )
		{
			if( quote == '\"' )
			{
				PTEXT tmp = BuildLine( ThisOp->data.string );
				LineRelease( ThisOp->data.string );
				ThisOp->data.string = tmp;
				RelateOpNode( &branch, ThisOp );
				  ThisOp = GetOpNode();
				quote = 0;
			}
			else if( !quote )
			{
				ThisOp->op = OP_CHARACTER_STRING;
				quote = pExp[0];
			}
			StepCurrentWord();
			continue;
		}
		if( quote )
		{
			if( ThisOp->op == OP_CHARACTER_STRING )
			{
				ThisOp->data.string =
					SegAppend( ThisOp->data.string
					         , SegDuplicate( thisword ) );
			}
			else if( ThisOp->op == OP_CHARACTER_CONST )
			{
				int n, len = (int)GetTextSize( thisword );
				for( n = 0; n < thisword->format.spaces; n++ )
				{
					if( !overflow &&
						 (ThisOp->data.i & 0xFF00000000000000LL) )
					{
						overflow = 1;
						fprintf( stderr, WIDE("%s(%d): warning character constant overflow.\n")
						       , GetCurrentFileName(), GetCurrentLine() );
					}
					ThisOp->data.i *= 256;
					ThisOp->data.i += ' ';
				}
				for( n = 0; n < len; n++ )
				{
					ThisOp->data.i *= 256;
					ThisOp->data.i += pExp[n];
				}
			}
			StepCurrentWord();
			continue;
		}
		if( pExp[0] == '(' )
		{
			POPNODE subexpression;
			if( ThisOp->op != OP_NOOP )
			{
			//if( g.bDebugLog )
			//{
			//	fprintf( stddbg, WIDE("Adding operation: ") );
			//	LogExpression( ThisOp );
			//}
				RelateOpNode( &branch, ThisOp );
				ThisOp = GetOpNode();
			}
			StepCurrentWord();
			subexpression = BuildExpression();
			pExp = GetText( GetCurrentWord() );
			if( pExp && pExp[0] != ')' )
			{
				fprintf( stderr, WIDE("(%s)%d Error: Invalid expression\n"), GetCurrentFileName(), GetCurrentLine() );
				DestroyExpression( branch );
				DestroyOpNode( ThisOp );
				return NULL;
				// invalid pairing of parens in expression
			}
			ThisOp->op = OP_SUBEXPRESSION;
			ThisOp->data.sub = subexpression;
			RelateOpNode( &branch, ThisOp );
			  ThisOp = GetOpNode();
			// pExp = GetText( GetCurrentWord() );
			// on return check current token as ')'
		}
		else if( pExp[0] == ')' )
		{
			if( ThisOp->op != OP_NOOP )
			{
				RelateOpNode( &branch, ThisOp );
			}
			else
				DestroyOpNode( ThisOp );
			//if( g.bDebugLog )
			//{
			//	fprintf( stddbg, WIDE("Built Expression: ")) ;
			//	LogExpression( branch );
			//}
			return branch;
		}
		else if( ( pExp[0] >= '0' && pExp[0] <= '9' ) ||
					( pExp[0] == '.' ) )
		{
			LONGEST_INT i;
			  LONGEST_FLT f;
			int len;
			switch( GetInteger( &i, &len ) )
			{
 // good integer.
			case 0:
				if( ThisOp->op != OP_NOOP )
				{
					RelateOpNode( &branch, ThisOp );
					ThisOp = GetOpNode();
				}
				ThisOp->op = OP_INT_OPERAND_64;
				ThisOp->data.i = i;
				RelateOpNode( &branch, ThisOp );
				ThisOp = GetOpNode();
				break;
 // might be a float...
			case 1:
				switch( GetFloat( &f, &len ) )
				{
				case 0:
 // invalid conversion (invalid number)
				case 1:
 // also if preprocessor - this always must fail
					DestroyExpression( branch );
					DestroyOpNode( ThisOp );
					//if( g.bDebugLog )
					//{
					//	fprintf( stddbg, WIDE("Built Expression 2: ")) ;
					//	LogExpression( branch );
					//}
					return branch;
				}
				break;
 // invalid number
			case 2:
				break;
			}
		}
		else if( pExp[0] == '_'
		       || ( pExp[0] >= 'A' && pExp[0] <= 'Z' )
		       || ( pExp[0] >= 'a' && pExp[0] <= 'z' )  )
		{
			// this is unsubstituted, is not a predefined thing, etc,
			// therefore this is a 0.
			if( quote )
			{
			}
			else
			{
				if( ThisOp->op != OP_NOOP )
				{
					RelateOpNode( &branch, ThisOp );
					ThisOp = GetOpNode();
				}
				ThisOp->op = OP_INT_OPERAND_64;
				ThisOp->data.i = 0;
				RelateOpNode( &branch, ThisOp );
				ThisOp = GetOpNode();
			}
		}
		else {
			if( !thisword->format.spaces || ThisOp->op == OP_NOOP )
			{
			retry_this_operator:
				for( n = 0; n < NUM_RELATIONS; n++ )
				{
					 if( Relations[n].thisop == ThisOp->op )
					 {
						 int o;
						 for( o = 0; Relations[n].trans[o].ch; o++ )
						 {
							 if( Relations[n].trans[o].ch == pExp[0] )
							{
								//if( g.bDebugLog )
								//{
								//	fprintf( stddbg, WIDE("%s becomes %s\n"),
								//			  ThisOp->op<0?"????":fullopname[ThisOp->op], fullopname[Relations[n].trans[o].becomes] );
								//}
								 ThisOp->op = Relations[n].trans[o].becomes;
								 break;
							 }
						 }
						 if( !Relations[n].trans[o].ch )
						 {
							 //fprintf( stddbg, WIDE("Invalid expression addition\n") );
							fprintf( stderr, WIDE("%s(%d): Error invalid operator: %s\n")
							       , GetCurrentFileName()
							       , GetCurrentLine()
							       , pExp );
							 // invalid expression addition....
							 n = NUM_RELATIONS;
						 }
						 break;
					 }
				}
			}
 // spaces seperate operators.
			else
				n = NUM_RELATIONS;
			// then this operator does not add to the prior operator...
			// therefore hang the old, create the new...
 // unfound
			if( n == NUM_RELATIONS )
			{
				if( ThisOp->op != OP_NOOP )
				{
					RelateOpNode( &branch, ThisOp );
					ThisOp = GetOpNode();
					goto retry_this_operator;
				}
				DestroyExpression( branch );
				return NULL;
			}
		}
		StepCurrentWord();
	}
	//if( g.bDebugLog )
	//{
	//	fprintf( stddbg, WIDE("Deleting: ") );
	//	LogExpression( ThisOp );
	//}
	DestroyOpNode( ThisOp );
	//if( g.bDebugLog )
	//{
	//	fprintf( stddbg, WIDE("Built Expression: ")) ;
	//	LogExpression( branch );
	//}
	return branch;
}
//--------------------------------------------------------------------------
POPNODE ResolveExpression( POPNODE *expr );
//--------------------------------------------------------------------------
int IsValue( POPNODE *node, int collapse_sub )
{
	POPNODE temp;
	if( !node )
		return FALSE;
	switch( (*node)->op )
	{
	case OP_INT_OPERAND_8:
	case OP_INT_OPERAND_16:
	case OP_INT_OPERAND_32:
	case OP_INT_OPERAND_64:
	case OP_SINT_OPERAND_8:
	case OP_SINT_OPERAND_16:
	case OP_SINT_OPERAND_32:
	case OP_SINT_OPERAND_64:
		return TRUE;
	case OP_FLT_OPERAND_32:
	case OP_FLT_OPERAND_64:
		fprintf( stderr, WIDE("%s(%d): Floating point operand is not supported\n")
		       , GetCurrentFileName(), GetCurrentLine() );
		return FALSE;
	case OP_SUBEXPRESSION:
		if( collapse_sub )
		{
			temp = ResolveExpression( &(*node)->data.sub );
			(*node)->data.sub = NULL;
			DestroyOpNode( SubstNode( *node, temp ) );
			*node = temp;
		}
		return TRUE;
	}
	return FALSE;
}
//--------------------------------------------------------------------------
void ApplyBinaryNot( POPNODE node )
{
	switch( node->op )
	{
	case OP_INT_OPERAND_8:
	case OP_INT_OPERAND_16:
	case OP_INT_OPERAND_32:
	case OP_INT_OPERAND_64:
	case OP_SINT_OPERAND_8:
	case OP_SINT_OPERAND_16:
	case OP_SINT_OPERAND_32:
	case OP_SINT_OPERAND_64:
		node->data.i = ~node->data.i;
		break;
	default:
		fprintf( stderr, WIDE("Dunno how we got here...\n") );
	}
}
//--------------------------------------------------------------------------
void ApplyLogicalNot( POPNODE node )
{
	switch( node->op )
	{
	case OP_INT_OPERAND_8:
	case OP_INT_OPERAND_16:
	case OP_INT_OPERAND_32:
	case OP_INT_OPERAND_64:
	case OP_SINT_OPERAND_8:
	case OP_SINT_OPERAND_16:
	case OP_SINT_OPERAND_32:
	case OP_SINT_OPERAND_64:
		node->data.i = !node->data.i;
		break;
	default:
		fprintf( stderr, WIDE("Dunno how we got here...\n") );
	}
}
//--------------------------------------------------------------------------
void ApplyNegative( POPNODE node )
{
	switch( node->op )
	{
	case OP_INT_OPERAND_8:
	case OP_INT_OPERAND_16:
	case OP_INT_OPERAND_32:
	case OP_INT_OPERAND_64:
	case OP_SINT_OPERAND_8:
	case OP_SINT_OPERAND_16:
	case OP_SINT_OPERAND_32:
	case OP_SINT_OPERAND_64:
		node->data.i = -node->data.i;
		break;
	default:
		fprintf( stderr, WIDE("Dunno how we got here...\n") );
	}
}
//--------------------------------------------------------------------------
POPNODE ApplyMultiply( POPNODE node1, POPNODE node2 )
{
	POPNODE result = GetOpNode();
	result->op = OP_SINT_OPERAND_64;
	result->data.i = node1->data.i * node2->data.i;
	return result;
}
//--------------------------------------------------------------------------
POPNODE ApplyDivide( POPNODE node1, POPNODE node2 )
{
	POPNODE result = GetOpNode();
	result->op = OP_SINT_OPERAND_64;
	if( node2->data.i != 0 )
		result->data.i = node1->data.i * node2->data.i;
	else
	{
		fprintf( stderr, WIDE("Right hand operator of divide is 0! - returning MAXINT\n") );
#if defined( _MSC_VER ) || defined( __WATCOMC__ )
		result->data.i = 0xFFFFFFFFFFFFFFFFU;
#else
		result->data.i = 0xFFFFFFFFFFFFFFFFULL;
#endif
	}
	return result;
}
//--------------------------------------------------------------------------
POPNODE ApplyModulus( POPNODE node1, POPNODE node2 )
{
	POPNODE result = GetOpNode();
	result->op = OP_SINT_OPERAND_64;
	result->data.i = node1->data.i % node2->data.i;
	return result;
}
//--------------------------------------------------------------------------
POPNODE ApplyShiftRight( POPNODE node1, POPNODE node2 )
{
	POPNODE result = GetOpNode();
	result->op = OP_SINT_OPERAND_64;
	result->data.i = node1->data.i >> node2->data.i;
	return result;
}
//--------------------------------------------------------------------------
POPNODE ApplyShiftLeft( POPNODE node1, POPNODE node2 )
{
	POPNODE result = GetOpNode();
	result->op = OP_SINT_OPERAND_64;
	result->data.i = node1->data.i << node2->data.i;
	return result;
}
//--------------------------------------------------------------------------
POPNODE ApplyGreater( POPNODE node1, POPNODE node2 )
{
	POPNODE result = GetOpNode();
	result->op = OP_SINT_OPERAND_64;
	if( node1->data.i > node2->data.i )
		result->data.i = 1;
	else
		result->data.i = 0;
	return result;
}
//--------------------------------------------------------------------------
POPNODE ApplyLesser( POPNODE node1, POPNODE node2 )
{
	POPNODE result = GetOpNode();
	result->op = OP_SINT_OPERAND_64;
	if( node1->data.i < node2->data.i )
		result->data.i = 1;
	else
		result->data.i = 0;
	return result;
}
//--------------------------------------------------------------------------
POPNODE ApplyGreaterEqual( POPNODE node1, POPNODE node2 )
{
	POPNODE result = GetOpNode();
	result->op = OP_SINT_OPERAND_64;
	if( node1->data.i >= node2->data.i )
		result->data.i = 1;
	else
		result->data.i = 0;
	return result;
}
//--------------------------------------------------------------------------
POPNODE ApplyLesserEqual( POPNODE node1, POPNODE node2 )
{
	POPNODE result = GetOpNode();
	result->op = OP_SINT_OPERAND_64;
	if( node1->data.i <= node2->data.i )
		result->data.i = 1;
	else
		result->data.i = 0;
	return result;
}
//--------------------------------------------------------------------------
POPNODE ApplyIsEqual( POPNODE node1, POPNODE node2 )
{
	POPNODE result = GetOpNode();
	result->op = OP_SINT_OPERAND_64;
	if( node1->data.i == node2->data.i )
		result->data.i = 1;
	else
		result->data.i = 0;
	return result;
}
//--------------------------------------------------------------------------
POPNODE ApplyIsNotEqual( POPNODE node1, POPNODE node2 )
{
	POPNODE result = GetOpNode();
	result->op = OP_SINT_OPERAND_64;
	if( node1->data.i != node2->data.i )
		result->data.i = 1;
	else
		result->data.i = 0;
	return result;
}
//--------------------------------------------------------------------------
POPNODE ApplyBinaryAnd( POPNODE node1, POPNODE node2 )
{
	POPNODE result = GetOpNode();
	result->op = OP_SINT_OPERAND_64;
	result->data.i = node1->data.i & node2->data.i;
	return result;
}
//--------------------------------------------------------------------------
POPNODE ApplyBinaryOr( POPNODE node1, POPNODE node2 )
{
	POPNODE result = GetOpNode();
	result->op = OP_SINT_OPERAND_64;
	result->data.i = node1->data.i | node2->data.i;
	return result;
}
//--------------------------------------------------------------------------
POPNODE ApplyXor( POPNODE node1, POPNODE node2 )
{
	POPNODE result = GetOpNode();
	result->op = OP_SINT_OPERAND_64;
	result->data.i = node1->data.i ^ node2->data.i;
	return result;
}
//--------------------------------------------------------------------------
POPNODE ApplyLogicalAnd( POPNODE node1, POPNODE node2 )
{
	POPNODE result = GetOpNode();
	result->op = OP_SINT_OPERAND_64;
	result->data.i = node1->data.i && node2->data.i;
	//if( g.bDebugLog )
	//{
	//	fprintf( stddbg, WIDE("%Ld && %Ld == %Ld\n"), node1->data.i, node2->data.i, result->data.i );
	//}
	return result;
}
//--------------------------------------------------------------------------
POPNODE ApplyLogicalOr( POPNODE node1, POPNODE node2 )
{
	POPNODE result = GetOpNode();
	result->op = OP_SINT_OPERAND_64;
	result->data.i = node1->data.i || node2->data.i;
	return result;
}
//--------------------------------------------------------------------------
POPNODE ApplyAddition( POPNODE node1, POPNODE node2 )
{
	POPNODE result = GetOpNode();
	result->op = OP_SINT_OPERAND_64;
	result->data.i = node1->data.i + node2->data.i;
	return result;
}
//--------------------------------------------------------------------------
POPNODE ResolveExpression( POPNODE *expr )
{
	// find highest operand... next next next next....
	POPNODE node;
	node = (*expr);
	//if( g.bDebugLog )
	//	LogExpression( node );
	while( node )
	{
		 // first loop - handle ! and ~
		if( node->op == OP_SUBEXPRESSION )
		{
			POPNODE sub;
			ResolveExpression( &node->data.sub );
			SubstNode( node, sub = node->data.sub );
			node->data.sub = NULL;
			DestroyExpression( node );
			if( node == (*expr) )
				(*expr) = sub;
			node = (*expr);
			continue;
		}
		else if( node->op == OP_BINARYNOT )
		{
			if( !node->right )
			{
				fprintf( stderr, WIDE("%s(%d): Error binary not operator(~) with no right hand operand\n")
				       , GetCurrentFileName()
				       , GetCurrentLine() );
				g.ErrorCount++;
				return NULL;
			}
			{
				POPNODE right = node->right;
				if( IsValue( &right, TRUE ) )
				{
					ApplyBinaryNot( right );
					DestroyOpNode( GrabNode( node ) );
					if( node == (*expr) )
						(*expr) = right;
					node = (*expr);
				}
				else
				{
					fprintf( stderr, WIDE("%s(%d): Error binary not(~) is not followed by an integer...\n")
					       , GetCurrentFileName()
					       , GetCurrentLine() );
					g.ErrorCount++;
				}
			}
			continue;
		}
		else if( node->op == OP_LOGICALNOT )
		{
			if( !node->right )
			{
				fprintf( stderr, WIDE("%s(%d): Error logical not operator with no right hand operand\n")
				       , GetCurrentFileName(), GetCurrentLine() );
				g.ErrorCount++;
				return NULL;
			}
			{
				POPNODE right = node->right;
				if( IsValue( &right, TRUE ) )
				{
					ApplyLogicalNot( right );
					DestroyOpNode( GrabNode( node ) );
					if( node == (*expr) )
						(*expr) = right;
					node = (*expr);
				}
				else
				{
					fprintf( stderr, WIDE("%s(%d): Logical not is not followed by an integer...\n")
					       , GetCurrentFileName()
					       , GetCurrentLine() );
					g.ErrorCount++;
				}
			}
			continue;
		}
		else if( node->op == OP_PLUS )
		{
			POPNODE right = node->right;
			DestroyOpNode( node );
			if( node == (*expr) )
				(*expr) = right;
			node = (*expr);
			continue;
		}
		else if( node->op == OP_MINUS )
		{
			POPNODE right = node->right;
			if( IsValue( &right, TRUE ) )
			{
				ApplyNegative( right );
				DestroyOpNode( node );
				if( node == (*expr) )
					(*expr) = right;
				node = (*expr);
				continue;
			}
			else
			{
				fprintf( stderr, WIDE("%s(%d): Negative operator is not followed by a value\n")
				       , GetCurrentFileName()
				       , GetCurrentLine() );
				g.ErrorCount++;
				return NULL;
			}
		}
		node = node->right;
	}
	//if( g.bDebugLog )
	//	fprintf( stddbg, WIDE("Done with unary +,-,!,~,()") );
	node = (*expr);
	//if( g.bDebugLog )
	//	LogExpression(node);
	while( node )
	{
		// Second loop handle * / %
		if( node->op == OP_MULTIPLY )
		{
			POPNODE left, right;
			left = node->left;
			right = node->right;
			if( IsValue( &left, TRUE )
				&& IsValue( &right, TRUE ) )
			{
				POPNODE result;
				result = ApplyMultiply( left, right );
				DestroyExpression( SubstNodes( left, right, result ) );
				if( (*expr) == left )
					(*expr) = result;
				node = (*expr);
				continue;
			}
			else
			{
				fprintf( stderr, WIDE("%s(%d): Error invalid operands to multiply?\n")
				       , GetCurrentFileName()
				       , GetCurrentLine() );
				g.ErrorCount++;
			}
		}
		if( node->op == OP_DIVIDE )
		{
			POPNODE left, right;
			left = node->left;
			right = node->right;
			if( IsValue( &left, TRUE )
				&& IsValue( &right, TRUE ) )
			{
				POPNODE result;
				result = ApplyDivide( left, right );
				DestroyExpression( SubstNodes( left, right, result ) );
				if( (*expr) == left )
					(*expr) = result;
				node = (*expr);
				continue;
			}
			else
			{
				fprintf( stderr, WIDE("%s(%d): Error invalid operands to divide?\n")
				       , GetCurrentFileName()
				       , GetCurrentLine() );
				g.ErrorCount++;
			}
		}
		if( node->op == OP_MOD )
		{
			POPNODE left, right;
			left = node->left;
			right = node->right;
			if( IsValue( &left, TRUE )
				&& IsValue( &right, TRUE ) )
			{
				POPNODE result;
				result = ApplyModulus( left, right );
				DestroyExpression( SubstNodes( left, right, result ) );
				if( (*expr) == left )
					(*expr) = result;
				node = (*expr);
				continue;
			}
			else
			{
				fprintf( stderr, WIDE("%s(%d): Error invalid operands to mod?\n")
				       , GetCurrentFileName()
				       , GetCurrentLine() );
				g.ErrorCount++;
			}
		}
		node = node->right;
	}
	// +/- additive operators would be next - but already done as unary.
	node = (*expr);
	//if( g.bDebugLog )
	//	LogExpression(node);
	while( node )
	{
		// third loop handle >> <<
		if( node->op == OP_SHIFTRIGHT )
		{
			POPNODE left, right;
			left = node->left;
			right = node->right;
			if( IsValue( &left, TRUE )
				&& IsValue( &right, TRUE ) )
			{
				POPNODE result;
				result = ApplyShiftRight( left, right );
				DestroyExpression( SubstNodes( left, right, result ) );
				if( (*expr) == left )
					(*expr) = result;
				node = (*expr);
				continue;
			}
			else
			{
				fprintf( stderr, WIDE("%s(%d): Error invalid operands to shift right?\n")
				       , GetCurrentFileName()
				       , GetCurrentLine() );
				g.ErrorCount++;
			}
		}
		if( node->op == OP_SHIFTLEFT )
		{
			POPNODE left, right;
			left = node->left;
			right = node->right;
			if( IsValue( &left, TRUE )
				&& IsValue( &right, TRUE ) )
			{
				POPNODE result;
				result = ApplyShiftLeft( left, right );
				DestroyExpression( SubstNodes( left, right, result ) );
				if( (*expr) == left )
					(*expr) = result;
				node = (*expr);
				continue;
			}
			else
			{
				fprintf( stderr, WIDE("%s(%d): Error invalid operands to shift left?\n")
				       , GetCurrentFileName()
				       , GetCurrentLine() );
				g.ErrorCount++;
			}
		}
		node = node->right;
	}
	node = (*expr);
	while( node )
	{
		// 4th loop handle > < >= <= comparisons (result in 0/1)
		if( node->op == OP_GREATER )
		{
			POPNODE left, right;
			left = node->left;
			right = node->right;
			if( IsValue( &left, TRUE )
				&& IsValue( &right, TRUE ) )
			{
				POPNODE result;
				result = ApplyGreater( left, right );
				DestroyExpression( SubstNodes( left, right, result ) );
				if( (*expr) == left )
					(*expr) = result;
				node = (*expr);
				continue;
			}
			else
			{
				fprintf( stderr, WIDE("%s(%d): Error invalid operands to greater?\n")
				       , GetCurrentFileName()
				       , GetCurrentLine() );
				g.ErrorCount++;
			}
		}
		if( node->op == OP_LESSER )
		{
			POPNODE left, right;
			left = node->left;
			right = node->right;
			if( IsValue( &left, TRUE )
				&& IsValue( &right, TRUE ) )
			{
				POPNODE result;
				result = ApplyLesser( left, right );
				DestroyExpression( SubstNodes( left, right, result ) );
				if( (*expr) == left )
					(*expr) = result;
				node = (*expr);
				continue;
			}
			else
			{
				fprintf( stderr, WIDE("%s(%d): Error invalid operands to lesser?\n")
				       , GetCurrentFileName()
				       , GetCurrentLine() );
				g.ErrorCount++;
			}
		}
		if( node->op == OP_GREATEREQUAL )
		{
			POPNODE left, right;
			left = node->left;
			right = node->right;
			if( IsValue( &left, TRUE )
				&& IsValue( &right, TRUE ) )
			{
				POPNODE result;
				result = ApplyGreaterEqual( left, right );
				DestroyExpression( SubstNodes( left, right, result ) );
				if( (*expr) == left )
					(*expr) = result;
				node = (*expr);
				continue;
			}
			else
			{
				fprintf( stderr, WIDE("%s(%d): Error invalid operands to greater equal?\n")
				       , GetCurrentFileName()
				       , GetCurrentLine() );
				LogExpression( *expr );
				g.ErrorCount++;
			}
		}
		if( node->op == OP_LESSEREQUAL )
		{
			POPNODE left, right;
			left = node->left;
			right = node->right;
			if( IsValue( &left, TRUE )
				&& IsValue( &right, TRUE ) )
			{
				POPNODE result;
				result = ApplyLesserEqual( left, right );
				DestroyExpression( SubstNodes( left, right, result ) );
				if( (*expr) == left )
					(*expr) = result;
				node = (*expr);
				continue;
			}
			else
			{
				fprintf( stderr, WIDE("%s(%d): Invalid operands to lesser equal?\n")
				       , GetCurrentFileName()
				       , GetCurrentLine() );
				g.ErrorCount++;
			}
		}
		node = node->right;
	}
	node = (*expr);
	//if( g.bDebugLog )
	//	LogExpression(node);
	while( node )
	{
		// 5th loop handle == !=
		if( node->op == OP_ISEQUAL )
		{
			POPNODE left, right;
			left = node->left;
			right = node->right;
			if( IsValue( &left, TRUE )
				&& IsValue( &right, TRUE ) )
			{
				POPNODE result;
				result = ApplyIsEqual( left, right );
				DestroyExpression( SubstNodes( left, right, result ) );
				if( (*expr) == left )
					(*expr) = result;
				node = (*expr);
				continue;
			}
			else
			{
				fprintf( stderr, WIDE("%s(%d): Error invalid operands to equal?\n")
				       , GetCurrentFileName()
				       , GetCurrentLine() );
				g.ErrorCount++;
			}
		}
		if( node->op == OP_NOTEQUAL )
		{
			POPNODE left, right;
			left = node->left;
			right = node->right;
			if( IsValue( &left, TRUE )
				&& IsValue( &right, TRUE ) )
			{
				POPNODE result;
				result = ApplyIsNotEqual( left, right );
				DestroyExpression( SubstNodes( left, right, result ) );
				if( (*expr) == left )
					(*expr) = result;
				node = (*expr);
				continue;
			}
			else
			{
				fprintf( stderr, WIDE("%s(%d): Error invalid operands to not equal?\n")
				       , GetCurrentFileName()
				       , GetCurrentLine() );
				LogExpression( *expr );
				g.ErrorCount++;
			}
		}
		node = node->right;
	}
	node = (*expr);
	//if( g.bDebugLog )
	//	LogExpression(node);
	while( node )
	{
		// 6th loop
		if( node->op == OP_BINARYAND )
		{
			POPNODE left, right;
			left = node->left;
			right = node->right;
			if( IsValue( &left, TRUE )
				&& IsValue( &right, TRUE ) )
			{
				POPNODE result;
				result = ApplyBinaryAnd( left, right );
				DestroyExpression( SubstNodes( left, right, result ) );
				if( (*expr) == left )
					(*expr) = result;
				node = (*expr);
				continue;
			}
			else
			{
				fprintf( stderr, WIDE("%s(%d): Error invalid operands to not equal?\n")
				       , GetCurrentFileName()
				       , GetCurrentLine() );
				g.ErrorCount++;
			}
		}
		node = node->right;
	}
	node = (*expr);
	//if( g.bDebugLog )
	//	LogExpression(node);
	while( node )
	{
		// 7th loop
		if( node->op == OP_XOR )
		{
			POPNODE left, right;
			left = node->left;
			right = node->right;
			if( IsValue( &left, TRUE )
				&& IsValue( &right, TRUE ) )
			{
				POPNODE result;
				result = ApplyXor( left, right );
				DestroyExpression( SubstNodes( left, right, result ) );
				if( (*expr) == left )
					(*expr) = result;
				node = (*expr);
				continue;
			}
			else
			{
				fprintf( stderr, WIDE("%s(%d): Error invalid operands to not equal?\n")
				       , GetCurrentFileName()
				       , GetCurrentLine() );
				g.ErrorCount++;
			}
		}
		node = node->right;
	}
	node = (*expr);
	//if( g.bDebugLog )
	//	LogExpression(node);
	while( node )
	{
		// 8th loop
		if( node->op == OP_BINARYOR )
		{
			POPNODE left, right;
			left = node->left;
			right = node->right;
			if( IsValue( &left, TRUE )
				&& IsValue( &right, TRUE ) )
			{
				POPNODE result;
				result = ApplyBinaryOr( left, right );
				DestroyExpression( SubstNodes( left, right, result ) );
				if( (*expr) == left )
					(*expr) = result;
				node = (*expr);
				continue;
			}
			else
			{
				fprintf( stderr, WIDE("%s(%d): Error invalid operands to not equal?\n")
				       , GetCurrentFileName()
				       , GetCurrentLine() );
				g.ErrorCount++;
			}
		}
		node = node->right;
	}
	node = (*expr);
	//if( g.bDebugLog )
	//	LogExpression(node);
	while( node )
	{
		// 8th loop
		if( node->op == OP_LOGICALAND )
		{
			POPNODE left, right;
			left = node->left;
			right = node->right;
			if( IsValue( &left, TRUE )
				&& IsValue( &right, TRUE ) )
			{
				POPNODE result;
				result = ApplyLogicalAnd( left, right );
				DestroyExpression( SubstNodes( left, right, result ) );
				if( (*expr) == left )
					(*expr) = result;
				node = (*expr);
				continue;
			}
			else
			{
				fprintf( stderr, WIDE("%s(%d): Error invalid operands to not equal?\n")
				       , GetCurrentFileName()
				       , GetCurrentLine() );
				g.ErrorCount++;
			}
		}
		node = node->right;
	}
	node = (*expr);
	//if( g.bDebugLog )
	//	LogExpression(node);
	while( node )
	{
		// 9th loop
		if( node->op == OP_LOGICALOR )
		{
			POPNODE left, right;
			left = node->left;
			right = node->right;
			if( IsValue( &left, TRUE )
				&& IsValue( &right, TRUE ) )
			{
				POPNODE result;
				result = ApplyLogicalOr( left, right );
				DestroyExpression( SubstNodes( left, right, result ) );
				if( (*expr) == left )
					(*expr) = result;
				node = (*expr);
				continue;
			}
			else
			{
				fprintf( stderr, WIDE("%s(%d): Error invalid operands to not equal?\n")
				       , GetCurrentFileName()
				       , GetCurrentLine() );
				g.ErrorCount++;
			}
		}
		node = node->right;
	}
	node = (*expr);
	while( node )
	{
		// and finally - add all subsequent operators...
		POPNODE right;
		right = node->right;
		if( node && right )
		{
			POPNODE result;
			result = ApplyAddition( node, right );
			DestroyExpression( SubstNodes( node, right, result ) );
			(*expr) = result;
			node = (*expr);
			continue;
		}
		node = node->right;
	}
	//if( g.bDebugLog )
	//	LogExpression(*expr);
	return *expr;
}
//--------------------------------------------------------------------------
int IsValidExpression( POPNODE *ppexpr )
{
	// check to see if any operands are next to any other operands...
	// like 3 4 2 is not valid 3 + 4 + 2 is though
	// though the processing will cause the +'s to dissappear and
	// subsequently when done - any operands next to each other are
	// implied +'s
	POPNODE node = *ppexpr;
	int prior_operand = 0;
	while( node )
	{
		if( node->op == OP_COMMA )
		{
			*ppexpr = node->right;
			ExpressionBreak( node->right );
			DestroyExpression( node );
			node = *ppexpr;
			prior_operand = 0;
			continue;
		}
		if( node->op == OP_SUBEXPRESSION )
		{
			if( !IsValidExpression( &node->data.sub ) )
				return FALSE;
			prior_operand = 1;
		}
		else if( IsValue( &node, FALSE ) )
		{
			if( prior_operand )
			{
				LogExpression( *ppexpr );
				fprintf( stderr, WIDE("%s(%d): Multiple operands with no operator!\n")
				       , GetCurrentFileName(), GetCurrentLine() );
				return FALSE;
			}
			prior_operand = 1;
		}
		else
			prior_operand = 0;
		node = node->right;
	}
	return TRUE;
}
//--------------------------------------------------------------------------
LONGEST_INT ProcessExpression( void )
{
	POPNODE tree = BuildExpression();
	if( IsValidExpression( &tree ) )
	{
		ResolveExpression( &tree );
		if( tree->left || tree->right )
		{
			fprintf( stderr, WIDE("%s(%d): Expression failed to resolve completely...\n")
			       , GetCurrentFileName(), GetCurrentLine() );
		}
		{
			LONGEST_INT resultval = 0;
			if( tree )
			{
				resultval = tree->data.i;
			}
			DestroyExpression( tree );
			return resultval;
		}
	}
	DestroyExpression( tree );
	return 0;
}
