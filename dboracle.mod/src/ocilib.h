/*
   +----------------------------------------------------------------------+   
   |                 OCILIB - C Wrapper for Oracle OCI                    |
   +----------------------------------------------------------------------+
   |              Website : http://orclib.sourceforge.net                 |
   +----------------------------------------------------------------------+
   |               Copyright (c) 2007-2008 Vincent ROGIER                 |
   +----------------------------------------------------------------------+
   | This library is free software; you can redistribute it and/or        |
   | modify it under the terms of the GNU Library General Public          |
   | License as published by the Free Software Foundation; either         |
   | version 2 of the License, or (at your option) any later version.     |
   |                                                                      |
   | This library is distributed in the hope that it will be useful,      |
   | but WITHOUT ANY WARRANTY; without even the implied warranty of       |
   | MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU    |
   | Library General Public License for more details.                     |
   |                                                                      |
   | You should have received a copy of the GNU Library General Public    |
   | License along with this library; if not, write to the Free           |
   | Software Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.   |
   +----------------------------------------------------------------------+
   |          Author: Vincent ROGIER <vince.rogier@gmail.com>             |
   +----------------------------------------------------------------------+ 
*/

/* ------------------------------------------------------------------------ *
 * $Id: ocilib.h, v 2.5.1 00:21 24/07/2008 Vince $
 * ------------------------------------------------------------------------ */

#ifndef OCILIB_H_INCLUDED 
#define OCILIB_H_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif  /* __cplusplus */

/**
 * @mainpage
 * 
 * @section s_intro Introduction 
 *
 * OCILIB  is a free, open source and platform independant library, written in C,
 * that access Oracle Databases.
 *
 * The OCILIB library :    
 *
 *   - Encapsulates OCI  (Oracle Call Interface which is powerful but complex)
 *   - Hides OCI complexity
 *   - Proposes instead a simple, readable and reusable API
 *   - Offers up to <b>360</b> simple and straightforward APIs.
 *
 * @section s_intro Version information
 *
 * <b>Current version : 2.5.1 (2008-07-23)</b>
 * 
 * @section s_feats Main features
 *
 * - Data binding
 * - Integrated smart define and fetch mecanisms
 * - Full Unicode support on all platorms
 * - Multi row fetching
 * - Binding array Interface for fast and massive bulk operations
 * - Reusable Statements
 * - Connection Pooling
 * - Global Transactions
 * - Returning DML feature support
 * - ROWIDs support
 * - Named Types (Object types) support (User or Builtin)
 * - Cursors
 * - PL/SQL blocks
 * - PL/SQL Tables
 * - PL/SQL Ref cursors and Nested tables
 * - LOB (BLOBs/ FILEs)
 * - Supports lobs > 4Go
 * - Long datatype (piecewise operations)
 * - Provides "All in one" Formatted functions (printf's like)
 * - Smallest possible memory usage
 * - Date/time management
 * - Timestamps and Intervals support 
 * - Error handling
 * - Describe database schema objects
 * - Access columns by index or name
 * - Hash tables API
 * - Portable Threads and mutexes API
 * - Supports static / shared oracle linkage
 * - Support runtime loading (no OCI libs required at compile / time)
 * - Great performances (straight OCI encapsulation)
 *
 * @section s_down Download
 *
 * Get OCILIB from <a href="http://orclib.sourceforge.net">OCILIB Project page</a>
 * at Sourceforge Website
 *
 * @section s_author Author
 *
 * OCILIB is developped by <a href="mailto:vince.rogier@gmail.com">Vincent Rogier</a>
 *
 * @section s_changelog ChangeLog
 *
 * @include ChangeLog.txt
 *
 */

/* ------------------------------------------------------------------------ *
 * Platform config
 * ------------------------------------------------------------------------ */

#ifdef HAVE_CONFIG_H
  #include <config.h>
#endif

/* ------------------------------------------------------------------------ *
 * C headers
 * ------------------------------------------------------------------------ */

#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <ctype.h>
#include <string.h>
#include <time.h>
#include <errno.h>

/* ------------------------------------------------------------------------ *
 * MS Windows plaform detection 
 * ------------------------------------------------------------------------ */

#ifndef _WINDOWS
  #if defined(_WIN32) || defined(_WIN64) ||defined(_WIN32_WINNT)
    #define _WINDOWS
  #endif
#endif

/* ------------------------------------------------------------------------ *
 * OCILIB version information
 * ------------------------------------------------------------------------ */
 
#define OCILIB_MAJOR_VERSION     2
#define OCILIB_MINOR_VERSION     5
#define OCILIB_REVISION_VERSION  1

/* ------------------------------------------------------------------------ *
 * Installing OCILIB
 * ------------------------------------------------------------------------ */

/**
 * @defgroup g_install Installing OCILIB
 * @{
 *
 *
 * @par Compatibilities
 *
 * Actual version of OCILIB has been validated on :
 *
 * - Platforms : Windows, HP/UX, Linux, Mac OS, Solaris, AIX, OpenVMS 
 * - Architectures : 32/64bits
 * - Compilers : GCC / MinGW, MS Compilers, XLC, CCs, LabView 
 * - Oracle versions : 8i, 9i, 10g, 11g 
 *
 * Please, contact the author if you have validated OCILIB on platforms or
 * compilers not listed here.
 *
 * @par Installing OCIB on Unix like systems
 *
 * OCILIB uses GNU tools for deployment and installation on Unix like platforms
 *
 * Uncompress the archive (ocilib-x.y.z-gnu.tar.gz)
 *  - $ cd ocilib-x.y.z
 *  - $ ./configure
 *  - $ ./make
 *  - $ ./make install (this step might require admin rights)
 *
 * Check the shared library path environment variable (LD_LIBRARY_PATH, 
 * LD_PATH, ..) :
 *  - it must include $ORACLE_HOME\lib 
 *  - it must include the path where OCILIB has been installed 
 *    (by example, typically /usr/local/lib under linux)
 *
 * In order to get thoses values loaded at login time, export thoses values in
 * your .profile confifuration file :
 *  - > export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$ORACLE_HOME/lib:/usr/local/lib
 *
 * <b>GNU Installation options </b>:
 *
 * OCILIB supports some optionss that are not needed for most common
 * configurations.
 * 
 * List of available options :
 *
 *   - --with-oracle-import=(linkage|runtime)
 *   - --with-oracle-charset=(ansi|unicode|mixed)
 *   - --with-oracle-home=(custom oracle regular client directory)
 *   - --with-oracle-lib64=(yes|no - check out folders on mixed 32/64bits plaforms)
 *   - --with-oracle-header-path=(oracle header files directory)
 *   - --with-oracle-lib-path=(oracle shared lib directory)
 *   - --with-oracle-lib-name=(oracle shared lib name)
 *
 * @par Installing OCILIB on Microsoft Windows 
 *
 * 32bits and 64bits DLLs are provided. 
 * Visual .NET (2005/2008) solutions are also provided to recompile the Dlls and 
 * demo.
 *
 * - Uncompress the archive (ocilib-x.y.z-windows.zip)
 * - Copy ocilib\src\ocilib.h to a folder listed in the compiler headers folders
 * - Copy ocilib\lib[32|64]\ocilib[x].lib to a folder listed in the linker 
 *   libraries folders
 * - Copy ocilib\lib[32|64]\ocilib[x].dll to a folder included in the PATH
 *   environement variable
 *
 * [x] is the compiled version of OCILIB ("a" -> ansi, "w" -> unicode, "m" -> mixed)
 *
 * @par Oracle Instant Client Support
 *
 * OCILIB supports ORacle Instant Client
 * 
 * On Microsoft Windows, there is no difference between using a regular Oracle
 * client and an Instant Client with OCILIB
 *
 * On Unix-like systems, the Instant Client is divised in different packages.
 * 
 * Public headers and shared libs are not part of the same package. 
 *
 * So, you must provide the following options to the configure command :
 *
 * - with-oracle-header-path : location the public header files
 * - with-oracle-lib-path : location the oracle shared lib
 *
 * If your instant client package containing the shared libs does not have a
 * symbolic link 'libclntsh.[shared lib extension]' to the fully qualified 
 * shared lib real name, you must create it :
 * 
 * Example on Linux :
 *
 * - $ ln $ORALIBPATH/libclntsh.so $ORALIBPATH/libclntsh.so.10.1
 *
 * @}
 */

/* ------------------------------------------------------------------------ *
 * OCILIB configuration
 * ------------------------------------------------------------------------ */

/**
 * @defgroup g_build Build options 
 * @{
 *
 * OCILIB supports 3 builds options 
 *
 * - Oracle import : 
 *
 *     - OCI_IMPORT_LINKAGE for linkage at compile time <b>(default)</b>
 *     - OCI_IMPORT_RUNTIME for runtime loading
 * 
 * - Oracle charset
 *
 *     - OCI_CHARSET_ANSI for ansi <b>(default)</b>
 *     - OCI_CHARSET_UNICODE for unicode
 *     - OCI_CHARSET_MIXED (ansi for metadata, unicode for userdata)
 *
 * - Calling convention (WINDOWS ONLY)
 *
 *     - OCI_API = __cdecl or blank for C/C++ only ! <b>(default)</b>
 *     - OCI_API = __sdtcall to link OCILIB for langage independance
 *
 * @note
 * <b>On Windows, OCI_API MUST be set to use prebuilt libraries</b>
 *
 */

/* Import mode */

#ifdef OCI_IMPORT_RUNTIME
#undef OCI_IMPORT_LINKAGE
#endif

#ifdef OCI_IMPORT_LINKAGE
#undef OCI_IMPORT_RUNTIME
#endif

#if !defined(OCI_IMPORT_RUNTIME) && !defined(OCI_IMPORT_LINKAGE)
#define OCI_IMPORT_LINKAGE
#endif

/* Charset mode */

#ifdef OCI_CHARSET_UNICODE
#undef OCI_CHARSET_ANSI
#undef OCI_CHARSET_MIXED
#endif

#ifdef OCI_CHARSET_MIXED
#undef OCI_CHARSET_ANSI
#undef OCI_CHARSET_UNICODE
#endif

#ifdef OCI_CHARSET_ANSI
#undef OCI_CHARSET_MIXED
#undef OCI_CHARSET_UNICODE
#endif

#if !defined(OCI_CHARSET_ANSI) && !defined(OCI_CHARSET_MIXED) && !defined(OCI_CHARSET_UNICODE)
#define OCI_CHARSET_ANSI
#endif

/* Calling convention */

#ifndef OCI_API
#define OCI_API 
#endif

/* Build mode */

#ifndef OCI_EXPORT
#define OCI_EXPORT 
#endif

/**
 * @}
 */

/**
 * @defgroup g_charset Charset support
 * @{
 *
 * OCILIB supports Ansi and Unicode charset
 *
 * Oracle started a real Unicode support with Oracle8i but only for user data.
 * All DML, metadata string, database objects names, etc, ... were still only
 * supported in Ansi.
 *  
 * With Oracle 9i, Oracle provides a full unicode support.
 * 
 * So depending on the compile time Oracle library or the runtime loaded 
 * library, the unicode support differs.
 *
 * OCILIB supports :
 *
 * - ansi (char)
 * - unicode (wchar_t)
 * - mixed charset : ansi for metadata, unicode for userdata
 *
 * OCILIB uses two types of strings :
 * 
 * - mtext : for meta data, SQL strings, object attributes.
 * - dtext : for input binds and outout data
 * 
 * mtext and text are declared as defines around char and wchar_t 
 * depending ont the charset option
 * 
 * @par Text macro
 *
 *   - MT() macro : "meta text" -> meta data and strings passed to OCI calls
 *   - DT() macro : "data text" -> user input/output data
 *
 * @par Option OCI_CHARSET_ANSI
 *
 *  - dtext	-->	char
 *  - DT(x)	-->	x
 *
 *  - mtext	-->	char
 *  - MT(x)	-->	x
 *
 * @par Option OCI_CHARSET_UNICODE
 *
 *  - dtext	-->	wchar_t
 *  - DT(x)	-->	L ## x
 *
 *  - mtext	-->	wchar_t
 *  --MT(x)	-->	L ## x
 *
 * @par Option OCI_CHARSET_MIXED
 *
 *  - dtext	-->	wchar_t
 *  - DT(x)	-->	L ## x
 *
 *  - mtext	-->	char
 *  - MT(x)	-->	x
 *
 * 
 * @par Unicode and ISO C
 *
 * Well, ISO C :
 * - doesn't know anything about Unicode.
 * - makes wide characters support tricky because the size of a wide character
 * is not defined and is freely adaptable by implementations.
 * 
 * OCILIB uses char/wchar_t strings for public interface and internal storage.
 *
 * OCILIB, for unicode builds, initialize OCI in UTF16 Unicode mode. Oracle 
 * implements this mode with a 2 bytes (fixed length) UTF16 encoding.
 * 
 * So, on systems implementing wchar_t as 2 bytes based UTF16 (eg. Ms Windows), 
 * input strings are directly passed to Oracle and taken back from it.
 *
 * On other systems (most of the unixes) that use UTF32 as encoding 
 * (4 bytes based wchar_t), OCILIB uses :
 * - temporary buffers to pass string to OCI for metadata strings
 * - buffer expansion from UTF16 to UTF32 for user data string :
 *     - allocation based on sizeof(wchar_t)
 *     - data filling based on sizeof(UTF16 2 bytes) 
 *     - data expansion to sizeof(wchar_t). 
 *
 * The buffer expansion is done inplace and has the advantage of not requiring 
 * extra buffer.
 * That reduces the cost of the Unicode/ISO C handling overhead on unixes.
 *
**/

/* Unicode mode */

#ifdef OCI_CHARSET_UNICODE
    #define OCI_METADATA_UNICODE
    #define OCI_USERDATA_UNICODE
    #define OCI_INCLUDE_WCHAR
#endif

#ifdef OCI_CHARSET_MIXED
    #define OCI_USERDATA_UNICODE
    #define OCI_INCLUDE_WCHAR
#endif

/* include wchar header if needed */

#ifdef OCI_INCLUDE_WCHAR
#include <wctype.h>
#include <wchar.h>
#endif

/* Charset macros */

#ifdef OCI_METADATA_UNICODE
    #define MT(x)           L ## x
    #define OCI_ENV_MODE    OCI_UTF16 
    #define mtext           wchar_t
#else
    #define OCI_ENV_MODE    OCI_DEFAULT
    #define MT(x)           x
    #define mtext           char
#endif

#ifdef OCI_USERDATA_UNICODE
    #define DT(x)           L ## x
    #define dtext           wchar_t
#else
    #define DT(x)           x
    #define dtext           char
#endif

/**
 * @}
 */

/* Charset mapping. 

   For ISO conformance, strdup/wcsdup/stricmp/strncasecmp are not used.
   All wide char routines are "officialy" C99.  
   but we weed an ansi equivalent to swprintf => ocisprintf 

*/

OCI_EXPORT int       ocisprintf(char *str, int size, const char *format, ...);
OCI_EXPORT char    * ocistrdup(const char * src);
OCI_EXPORT int       ocistrcasecmp(const char *str1, const char *str2);

#ifdef OCI_INCLUDE_WCHAR
OCI_EXPORT wchar_t * ociwcsdup(const wchar_t * src);
OCI_EXPORT int       ociwcscasecmp(const wchar_t *str1, const wchar_t *str2);
#endif

/* special defines for Microsoft C runtime that is not C ISO compliant   */

#ifdef _MSC_VER
  #define vsnprintf         _vsnprintf
  #ifdef OCI_INCLUDE_WCHAR
    #define vsnwprintf      _vsnwprintf
  #endif
#endif

/* mapping macros */

#ifdef OCI_METADATA_UNICODE
    #define mtsdup          ociwcsdup
    #define mtslen          wcslen
    #define mtstol          wcstol
    #define mtscpy          wcscpy
    #define mtsncpy         wcsncpy
    #define mtscmp          wcscmp
    #define mtscasecmp      ociwcscasecmp
    #define mtsprintf       swprintf
    #define mtsvprintf      vsnwprintf
#else
    #define mtsdup          ocistrdup
    #define mtscpy          strcpy
    #define mtsncpy         strncpy
    #define mtslen          strlen
    #define mtstol          strtol
    #define mtscmp          strcmp
    #define mtscasecmp      ocistrcasecmp
    #define mtsprintf       ocisprintf
    #define mtsvprintf      vsnprintf
#endif

#ifdef OCI_USERDATA_UNICODE
    #define dtslen          wcslen
    #define dtscpy          wcscpy
    #define dtsncpy         wcsncpy
    #define dtstol          wcstol
    #define dtstod          wcstod
    #define dtscmp          wcscmp
    #define dtscasecmp      ociwcscasecmp
    #define dtsprintf       swprintf
#else
    #define dtslen          strlen
    #define dtscpy          strcpy
    #define dtsncpy         strncpy
    #define dtstol          strtol
    #define dtstod          strtod
    #define dtscmp          strcmp
    #define dtscasecmp      ocistrcasecmp
    #define dtsprintf       ocisprintf
#endif

/* string size macros */

#define mtextsize(s) (mtslen(s) * sizeof(mtext))
#define dtextsize(s) (dtslen(s) * sizeof(dtext))

#define msizeof(s) (sizeof(s) / sizeof(mtext))
#define dsizeof(s) (sizeof(s) / sizeof(dtext))


/**
 * @defgroup g_objects Library objects
 * @{
 *
 * The public OCILIB library interface implements encapsulation for
 * representing database objects (such as connections , statements, ...) through
 * opaque structures (pointers to structures whose definition is kept private)
 *
 * Instead of directly manipulating the structures and their members, the library
 * offers functions to access the underlying members.
 *
 * It's designed to make the user code as more independant of the library details 
 * as possible.
 *
**/

/**
 * @struct OCI_ConnPool
 *
 * @brief
 * Oracle Connection Pool
 *
 * A Connection pool is a set of connections
 *
 */

typedef struct OCI_ConnPool OCI_ConnPool;

/**
 * @struct OCI_Connection
 *
 * @brief 
 * Oracle physical connection.
 *
 * It holds all information about a connection such as error handling, 
 * associated statements, ...
 * Error handling and transactions are embedded within a connection object.  
 *
 * Multithreaded applications that use multiple connections should
 * use one connection per thread as all statements associated with a
 * connection share the same context.
 *
 */

typedef struct OCI_Connection OCI_Connection;

/**
 * @struct OCI_Statement
 *
 * @brief
 * Oracle SQL or PL/SQL statement.
 *
 * A Statement object allows users to prepare, execute SQL orders or PL/SQL blocks
 *
 */

typedef struct OCI_Statement OCI_Statement;

/**
 * @struct OCI_Resultset
 *
 * @brief
 * Collection of output columns from a select statement.
 * 
 * A resultset object is the result of 'select' SQL Statement.  
 * 
 * It's a set of data (ordered in columns) that can be fetched row by row 
 * to get data returned by the SQL statement
 *
 */

typedef struct OCI_Resultset OCI_Resultset;

/**
 * @struct OCI_Column 
 *
 * @brief 
 * Internal SQL Column representation.
 *
 * A column object reppresents an ouptut column from a select statement
 *
 */

typedef struct OCI_Column OCI_Column;

/**
 * @struct OCI_Lob
 *
 * @brief
 * Oracle Internal Large objects :
 * 
 * The following internal Larges Objects are supported : 
 *
 * - BLOBs           : Binary large objects
 * - CLOBs / NCLOBs  : Charater large objects
 *
 * LOB were introduced by OCI8 to replace Long datatypes.
 * 
 * It's designed to store really larges objects (buffer, files) inside the database 
 * 
 * Oracle encourages programmers to use those objects instead of LONG, LONG RAW, ...
 * 
 * OCILIB supports both LOBs and LONGs
 *
 */

typedef struct OCI_Lob OCI_Lob;

/**
 * @struct OCI_File
 *
 * @brief
 * Oracle External Large objects :
 * 
 * The following external Larges Objects are supported : 
 *
 * - BFILEs : Binary files
 * - CFILEs : Charater files
 *
 * FILEs were introduced by OCI8 in order to store references to files located
 * ouside the database .
 *
 * @warning
 * Only Readonly access is allowed on BFILEs
 * 
 * Two way to use FILEs :
 *
 * - within statement context (query, binding)
 * - without statement context (server files reading) through OCI_File properties
 * functions
 *
 */

typedef struct OCI_File OCI_File;

/**
 * @struct OCI_Transaction
 *
 * @brief
 * Oracle Transaction.
 *
 * A transaction can be :
 *
 * - Local  : it's implicitly created by OCILIB
 * - Global : it's explictily created by the program 
 *
 */

typedef struct OCI_Transaction  OCI_Transaction;

/**
 * @struct OCI_Long
 *
 * @brief Oracle Long datatype.
 *
 * The following long Objects are supported : 
 *
 * - LONG RAW : Binary long objects
 * - LONG     : Charater long objects
 *
 * Those types were used in older versions of Oracle (before Oracle8i) to store
 * large chunks of data in the database.
 * 
 * It's now depreciated by Oracle that recommends to use LOBs
 *
 * Many databases and applications are still designed to use LONGs that's why 
 * OCILIB supports Long Objects and piecewise operations
 *
 */

typedef struct OCI_Long OCI_Long;

/**
 * @struct OCI_Date
 *
 * @brief
 * Oracle internal date representation.
 *
 */

typedef struct OCI_Date OCI_Date;

/**
 * @struct OCI_Timestamp
 *
 * @brief
 * Oracle internal timespamp representation.
 *
 */

typedef struct OCI_Timestamp OCI_Timestamp;

/**
 * @struct OCI_Interval
 *
 * @brief
 * Oracle internal interval representation.
 *
 */

typedef struct OCI_Interval OCI_Interval;


/**
 * @struct OCI_Object
 *
 * @brief
 * Oracle Named types representation.
 *
 */

typedef struct OCI_Object OCI_Object;

/**
 * @struct OCI_Schema
 *
 * @brief
 * Schema metadata handle.
 *
 */

typedef struct OCI_Schema OCI_Schema;

/**
 * @struct OCI_HashTable
 *
 * @brief
 * OCILIB implementation of hash tables.
 *
 */

typedef struct OCI_HashTable OCI_HashTable;

/**
 * @struct OCI_Error
 *
 * @brief
 * Encapsulates an Oracle or OCILIB exception.
 *
 * The error object is used to raise internal or oracle errors. 
 * When an error occurs, if the application has provided an error handler, an
 * error object is constructed and passed to the handler
 * 
 */

typedef struct OCI_Error OCI_Error;

/**
 * @struct OCI_Mutex
 *
 * @brief
 * OCILIB encapsulation of OCI mutexes.
 *
 */

typedef struct OCI_Mutex OCI_Mutex;

/**
 * @struct OCI_Thread
 *
 * @brief
 * OCILIB encapsulation of OCI Threads.
 *
 */

typedef struct OCI_Thread OCI_Thread;

/**
 * @}
 */

/**
 * @typedef POCI_ERROR
 *
 * @brief
 * Error procedure prototype
 *
 */

typedef void (*POCI_ERROR) (OCI_Error *err);

/**
 * @typedef POCI_THREAD
 *
 * @brief
 * Thread procedure prototype
 *
 */

typedef void (*POCI_THREAD) (OCI_Thread *thread, void *arg);

/**
 * @typedef POCI_THREADKEYDEST
 *
 * @brief
 * Thread key destructor prototype. 
 * 
 * @note
 * data is the thread key value
 *
 */

typedef void (*POCI_THREADKEYDEST) (void *data);

/* public structures */

/**
 * @struct OCI_XID
 *
 * @brief
 * Global transaction identifier
 *
 */

typedef struct OCI_XID {
	long formatID;			
	long gtrid_length;			
	long bqual_length;	
	char data[128];
} OCI_XID;

/**
 * @union OCI_Variant 
 *
 * @brief 
 * Internal Variant type based on union C type.
 * Extremely helpful for generic buffer.
 * It reduces the amount of casts
 *
 */

typedef union OCI_Variant {
    /* integers */
    int           num;
    /* raw data */
    unsigned char *p_bytes;
    /* pointer to c natives types */
    void          *p_void;
    int           *p_int;
    double        *p_double;
    dtext         *p_dtext;
    mtext         *p_mtext;
    /* ocilib object types */
    OCI_Date      *p_date;
    OCI_Interval  *p_interval;
    OCI_Timestamp *p_timestamp;
    OCI_Long      *p_long;
    OCI_Lob       *p_lob;
    OCI_File      *p_file;
    OCI_Statement *p_stmt;
    OCI_Column    *p_col;
} OCI_Variant; 
    
 /**
 * @struct OCI_HashValue
 *
 * @brief
 * Hash table entry value
 *
 * OCILIB implementation of hash tables uses chaining method for
 * dealing with collisions
 *
 */

typedef struct OCI_HashValue {
    OCI_Variant           value;
    struct OCI_HashValue *next;
} OCI_HashValue;

/**
 * @struct OCI_HashEntry
 *
 * @brief
 * Hash table entry
 *
 */

typedef struct OCI_HashEntry {
    mtext                *key;
    struct OCI_HashValue *values;
    struct OCI_HashEntry  *next;
} OCI_HashEntry;

/**
 * @typedef big_int
 *
 * @brief
 * big_int is a C scalar integer type (32 or 64 bits) depending on
 * compiler support for 64bits integers
 * big_uint is an usigned big_int
 *
 */

/* check for long long support */
#if defined(LLONG_MAX) 
    /* C99 long long supported */
    typedef long long big_int;
    typedef unsigned  long long big_uint;
   #define OCI_BIG_UINT_ENABLED
#elif defined(_WINDOWS)
    /* Microsoft extension supported */
    typedef __int64  big_int;
    typedef unsigned __int64 big_uint;
    #define OCI_BIG_UINT_ENABLED
#else
    typedef int big_int;
    typedef unsigned int big_uint;
#endif

/* boolean balues */

#ifndef TRUE
# define TRUE                   1
# define FALSE                  0
#endif

#ifndef boolean
# define boolean int
#endif 

/* oracle versions*/

#define OCI_UNKNOWN             0
#define OCI_8                   8
#define OCI_9                   9
#define OCI_10                  10
#define OCI_11                  11

/* binding */

#define OCI_BIND_BY_POS         0
#define OCI_BIND_BY_NAME        1
#define OCI_BIND_SIZE           6
#define OCI_BIND_MAX            256

/* fetching */

#define OCI_FETCH_SIZE          20   
#define OCI_PREFETCH_SIZE       1
#define OCI_LONG_EXPLICIT       1   
#define OCI_LONG_IMPLICIT       2 

/* unkown value */

#define OCI_UNKNOWN             0

/* C Data Type mapping */

#define OCI_CDT_INTEGER         1        
#define OCI_CDT_DOUBLE          2        
#define OCI_CDT_DATETIME        3        
#define OCI_CDT_TEXT            4        
#define OCI_CDT_LONG            5        
#define OCI_CDT_CURSOR          6        
#define OCI_CDT_LOB             7    
#define OCI_CDT_FILE            8
#define OCI_CDT_TIMESTAMP       9
#define OCI_CDT_INTERVAL        10
#define OCI_CDT_RAW             11
#define OCI_CDT_OBJECT          12

/* Data Type codes for OCI_ImmediateXXX() calls */

#define OCI_ARG_SHORT           1        
#define OCI_ARG_USHORT          2 
#define OCI_ARG_INT             3        
#define OCI_ARG_UINT            4        
#define OCI_ARG_BIGINT          5        
#define OCI_ARG_BIGUINT         6        
#define OCI_ARG_DOUBLE          7        
#define OCI_ARG_DATETIME        8        
#define OCI_ARG_TEXT            9        
#define OCI_ARG_LOB             10    
#define OCI_ARG_FILE            11
#define OCI_ARG_TIMESTAMP       12
#define OCI_ARG_INTERVAL        13
#define OCI_ARG_RAW             14

/* statement types */

#define OCI_CST_SELECT          1                        
#define OCI_CST_UPDATE          2                           
#define OCI_CST_DELETE          3                              
#define OCI_CST_INSERT          4                             
#define OCI_CST_CREATE          5                             
#define OCI_CST_DROP            6                              
#define OCI_CST_ALTER           7                              
#define OCI_CST_BEGIN           8                   
#define OCI_CST_DECLARE         9        

/* environnement modes */

#define OCI_ENV_DEFAULT         0
#define OCI_ENV_THREADED        1

    /* sessions modes */

#define OCI_SESSION_DEFAULT     0
#define OCI_SESSION_SYSDBA      2
#define OCI_SESSION_SYSOPER     4

/* charsetform types */

#define OCI_CSF_NONE            0
#define OCI_CSF_CHARSET         1
#define OCI_CSF_NATIONAL        2

/* timestamp types */

#define OCI_TIMESTAMP           1
#define OCI_TIMESTAMP_TZ        2
#define OCI_TIMESTAMP_LTZ       3

/* interval types */

#define OCI_INTERVAL_YM         1
#define OCI_INTERVAL_DS         2

/* long types */

#define OCI_BLONG               1
#define OCI_CLONG               2

/* lLob types */

#define OCI_BLOB                1
#define OCI_CLOB                2
#define OCI_NCLOB               3

/* lob opening mode */

#define OCI_LOB_READONLY        1  
#define OCI_LOB_READWRITE       2 

/* file types */

#define OCI_BFILE               1
#define OCI_CFILE               2

/* lob browing mode */

#define OCI_SEEK_SET            1
#define OCI_SEEK_END            2
#define OCI_SEEK_CUR            3

/* schema types */

#define OCI_SCHEMA_TABLE        1
#define OCI_SCHEMA_VIEW         2
#define OCI_SCHEMA_TYPE         3

/* size constants */

#define OCI_SIZE_FORMAT         64
#define OCI_SIZE_BUFFER         512
#define OCI_SIZE_LONG           (64*1024)-1
#define OCI_SIZE_DATE           44
#define OCI_SIZE_TIMESTAMP      60
#define OCI_SIZE_FORMAT_TODATE  14
#define OCI_SIZE_NULL           4 
#define OCI_SIZE_PRECISION      10
#define OCI_SIZE_ROWID          23
#define OCI_SIZE_DIRECTORY      30
#define OCI_SIZE_FILENAME       255
#define OCI_SIZE_FORMAT_NUM     24

/* hash tables support */

#define OCI_HASH_STRING         1
#define OCI_HASH_INTEGER        2
#define OCI_HASH_POINTER        3

#define OCI_HASH_DEFAULT_SIZE   256

/* Trancsaction types */

#define OCI_TRS_NEW             0x00000001
#define OCI_TRS_READONLY        0x00000100
#define OCI_TRS_READWRITE       0x00000200
#define OCI_TRS_SERIALIZABLE    0x00000400
#define OCI_TRS_LOOSE           0x00010000
#define OCI_TRS_TIGHT           0x00020000

/* OCILIB Error types */

#define OCI_ERR_API             1
#define OCI_ERR_MEMORY          2
#define OCI_ERR_NOT_AVAILABLE   3
#define OCI_ERR_NOT_SUPPORTED   4
#define OCI_ERR_ARG_INVALID     5
#define OCI_ERR_SQL_PARSING     6
#define OCI_ERR_NULL_POINTER    7
#define OCI_ERR_THREAD_MODE     8

/* string constants */

#define OCI_STRING_NULL         MT("NULL")            
#define OCI_STRING_FORMAT_DATE  MT("YYYY-MM-DD")
#define OCI_STRING_DEFAULT_PREC 3
#define OCI_STRING_FORMAT_NUM   MT("FM9999999999999999999999")

/**
 * @defgroup g_init Initializing the library
 * @{
 *
 * To use OCILIB, it first needs to be initialized through a call to 
 * OCI_Initialize().
 *
 * Then, the application connects to server, executes queries, ....
 *
 * Finally, OCILIB resources must be released by OCI_Cleanup()
 * 
 * @note
 * The following objects are automatically freed by the library :
 * - Connections
 * - Connection pools
 * - Statements
 *
 * @warning
 * All other standalone object instances (mutexes, threads, dates, lobs, ...)
 * <b>ARE NOT</b> freed.
 *
 * @par Example
 * @include init.c
 *
 */

/**
 * @brief 
 * Initializes the library
 *
 * @param err_handler  - Pointer to error handler procedure (optional)
 * @param home         - Oracle home path (optional)
 * @param mode         - Environnement mode
 * 
 * Possible values for parameter mode :
 * - OCI_ENV_DEFAULT
 * 
 * @note
 * This function must be called before any OCILIB library function.
 *
 * - It installs the error handler
 * - It loads the Oracle shared library located in the path pointed by 'home'
 *
 * @warning
 * If the parameter 'home' is NULL, the Oracle library is loaded from system 
 * environnement variables
 *
 * @return
 * TRUE on success otherwise FALSE (only with Oracle runtime loading mode
 * if the oracle shared libraries can't be loaded)
 * 
 */

OCI_EXPORT boolean OCI_API OCI_Initialize
(
    POCI_ERROR err_handler, 
    const mtext *home,
    int mode
);

/**
 * @brief 
 * Clean up all resources allocated by the library
 * 
 * @note
 * This function must be the last OCILIB library function call.
 *
 * - It deallocates objects not explicitly freed by the program (connections,
 *  statements, ...)
 * - It unloads the Oracle shared library 
 *
 * @return TRUE
 */

OCI_EXPORT boolean OCI_API OCI_Cleanup(void);

/**
 * @brief 
 * Return the major version of OCI used for compilation
 * 
 * @note
 * - with linkage build option, the version is determined from the oci.h header
 *   through differents ways
 * - with runtime loading buid option, the version is set to the highest version
 *   of OCI needed by OCILIB, not necessarily the real OCI version
 *
 */

OCI_EXPORT int OCI_API OCI_GetOCICompileVersion(void);

/**
 * @brief 
 * Return the major version of OCI used for compilation
 * 
 * @note
 * - with linkage build option, the version is determined from the oci.h header
 *   through differents ways
 * - with runtime loading buid option, the version determined from the symbols 
 *   dynamically loaded.
 *
 */

OCI_EXPORT int OCI_API OCI_GetOCIRuntimeVersion(void);

/**
 * @}
 */

/**
 * @defgroup g_error Error handling
 * @{
 *
 * OCI provides error handling support through callback.
 *
 * Exceptions are raised :
 * 
 * - On Oracle OCI API call error
 * - On Oracle SQL statement error
 * - Internal OCILIB memory allocation failure
 *
 * If an error handler was provided to OCI_Initialize(), when an error occurs, the 
 * library creates an OCI_Error object and passes its handle to the error handler.
 *
 * Exception properties are accessible through a set of functions
 *
 * @par Example
 * @include err.c
 *
 */

/**
 * @brief 
 * Retrieve error message from error handle
 *
 * @param err * error handle
 *
 */

OCI_EXPORT const mtext * OCI_API OCI_ErrorGetString
(
    OCI_Error *err
);

/**
 * @brief 
 * Retrieve the type of error from error handle
 *
 * @param err * error handle
 *
 * @note
 * Returns one of the following values :
 *
 * - OCI_ERR_API
 * - OCI_ERR_MEMORY
 * - OCI_ERR_NOT_AVAILABLE
 * - OCI_ERR_NOT_SUPPORTED
 *
 * @return
 * Object type or OCI_UNKNOWN the input handle is NULL
 *
 */

OCI_EXPORT int OCI_API OCI_ErrorGetType
(
    OCI_Error *err
);

/**
 * @brief 
 * Retrieve Oracle Error code from error handle
 *
 * @param err * error handle
 *
 */

OCI_EXPORT int OCI_API OCI_ErrorGetOCICode
(
    OCI_Error *err
);

/**
 * @brief 
 * Retrieve iInternal Error code from error handle
 *
 * @param err * error handle
 *
 */

OCI_EXPORT int OCI_API OCI_ErrorGetInternalCode
(
    OCI_Error *err
);

/**
 * @brief 
 * Retrieve connection handle within the error occured
 *
 * @param err * error handle
 *
 */

OCI_EXPORT OCI_Connection * OCI_API OCI_ErrorGetConnection
(   
    OCI_Error *err
);

/**
 * @brief 
 * Retrieve statement handle within the error occured
 *
 * @param err * error handle
 * 
 * @note
 * If the error occured out of a statement context, it returns NULL
 *
 */

OCI_EXPORT OCI_Statement * OCI_API OCI_ErrorGetStatement
(   
    OCI_Error *err
);

/**
 * @}
 */

/**
 * @defgroup g_connect Connecting to Database
 * @{
 *
 * Connecting to a database server is done with one call to
 * OCI_ConnectionCreate().
 * 
 * OCI_ConnectionFree() closes the established connection
 *
 * Connection properties are accessible through a set of functions
 *
 * @par Example
 * @include conn.c
 *
 */

/**
 * @brief 
 * Create a physical connection to an Oracle database server
 *
 * @param db   - Oracle Service Name
 * @param user - Oracle User name
 * @param pwd  - Oracle User password
 * @param mode - Session mode
 * 
 * Possible values for parameter mode :
 * - OCI_SESSION_DEFAULT
 * - OCI_SESSION_SYSDBA
 * - OCI_SESSION_SYSOPER
 * 
 * @note
 * On success, a transaction is automatically created and started
 *
 * @return 
 * Connection handle on succes or NULL on failure
 *
 */

OCI_EXPORT OCI_Connection * OCI_API OCI_ConnectionCreate
(
    const mtext *db, 
    const mtext *user, 
    const mtext *pwd,
    int mode
);

/**
 * @brief 
 * Close a physical connection to an Oracle database server
 *
 * @param con - Connection handle
 * 
 * @return 
 * TRUE on success otherwise FALSE
 *
 */

OCI_EXPORT boolean OCI_API OCI_ConnectionFree
(
    OCI_Connection *con
);

/**
 * @brief 
 * Returns TRUE is the given connection is still connected otherwise FALSE
 *
 * @param con - Connection handle
 * 
 */

OCI_EXPORT boolean OCI_API OCI_IsConnected
(
    OCI_Connection *con
);

/**
 * @brief 
 * Return the previously pointer to user data associated with the connection
 *
 * @param con - Connection handle
 * 
 */

OCI_EXPORT const void * OCI_API OCI_GetUserData
(
    OCI_Connection *con
);

/**
 * @brief 
 * Associate to the given connection a pointer to user data
 *
 * @param con  - Connection handle
 * @param data - user data pointer
 *
 * @return 
 * TRUE on success otherwise FALSE
 *
 */

OCI_EXPORT boolean OCI_API OCI_SetUserData
(
    OCI_Connection *con,
    const void * data
);

/**
 * @brief 
 * Return the name of the connected database/service name
 *
 * @param con - Connection handle
 * 
 */

OCI_EXPORT const mtext * OCI_API OCI_GetDatabase
(
    OCI_Connection *con
);

/**
 * @brief 
 * Return the current logged user name
 *
 * @param con - Connection handle
 * 
 */

OCI_EXPORT const mtext * OCI_API OCI_GetUserName
(
    OCI_Connection *con
);

/**
 * @brief 
 * Return the current logged user password
 *
 * @param con - Connection handle
 * 
 */

OCI_EXPORT const mtext * OCI_API OCI_GetPassword
(
    OCI_Connection *con
);

/**
 * @brief 
 * Change the password of the logged user
 *
 * @param con      - Connection handle
 * @param password - New password
 *
 * @return 
 * TRUE on success otherwise FALSE
 *
 */

OCI_EXPORT boolean OCI_API OCI_SetPassword
(
    OCI_Connection *con,
    const mtext *password
);

/**
 * @brief 
 * Return the current session mode
 *
 * @param con - Connection handle
 * 
 * @note
 * See OCI_ConnectionCreate() for possible values 
 * 
 */

OCI_EXPORT int OCI_API OCI_GetSessionMode
(
    OCI_Connection *con
);

/**
 * @brief 
 * Return the connected database server version
 *
 * @param con - Connection handle
 * 
 */

OCI_EXPORT const mtext * OCI_API OCI_GetVersionServer
(
    OCI_Connection *con
);

/**
 * @brief 
 * Return the major version number of the connected database server
 *
 * @param con - Connection handle
 * 
 * @return
 * version number or 0 on failure
 * 
 */

OCI_EXPORT int OCI_API OCI_GetServerMajorVersion
(
    OCI_Connection *con
);
 
/**
 * @brief 
 * Return the minor version number of the connected database server
 *
 * @param con - Connection handle
 * 
 * @return
 * version number or 0 on failure
 * 
 */

OCI_EXPORT int OCI_API OCI_GetServerMinorVersion
(
    OCI_Connection *con
);

/**
 * @brief 
 * Return the revision version number of the connected database server
 *
 * @param con - Connection handle
 * 
 * @return
 * version number or 0 on failure
 * 
 */

OCI_EXPORT int OCI_API OCI_GetServerRevisionVersion
(
    OCI_Connection *con
);

/**
 * @brief 
 * Return the current transaction of the connection
 *
 * @param con - Connection handle
 * 
 */

OCI_EXPORT OCI_Transaction * OCI_API OCI_GetTransaction
(
    OCI_Connection *con
);

/**
 * @brief 
 * Return the current transaction attached to the connection
 *
 * @param con   - Connection handle
 * @param trans - Transaction handle to assign
 *
 * @note
 * The current transaction is automatically stopped but the newly assigned
 * is not started or resumed.
 * 
 */

OCI_EXPORT boolean OCI_API OCI_SetTransaction
(
    OCI_Connection *con,
    OCI_Transaction *trans
);

/**
 * @brief 
 * Return the highest Oracle version is supported by the connection
 *
 * @param con - connection handle
 * 
 * @note
 * The highest supported version is the lower version between client and server:
 *
 * @note
 * Returns one of the following values :
 *
 * - OCI_UNKNOWN
 * - OCI_8
 * - OCI_9
 * - OCI_10
 * - OCI_8
 * - OCI_11
 *
 */

OCI_EXPORT boolean OCI_API OCI_GetVersionConnection
(
    OCI_Connection *con
);

/**
 * @brief 
 * Enable the server output
 *
 * @param con     - Connection handle
 * @param bufsize - server buffer max size (server side)
 * @param arrsize - number of lines to retreive per server roundtrip
 * @param lnsize  - maximum size of one line
 *
 * @note
 * This call is equivalent to the command 'set serveroutput on' in SQL*PLUS
 *
 * @note
 * 'bufsize' minimum value is 2000, maximum 1000000 with Oracle < 10.2g and can
 * be unlimited above
 *
 * @note
 * 'lnsize' maximum value is 255 with Oracle < 10.2g and 32767 above
 *
 * @warning
 * If OCI_ServerEnableOutput() is not called, OCI_ServerGetOutput() will return 
 * NULL
 * 
 * @return 
 * TRUE on success otherwise FALSE
 *
 */

OCI_EXPORT boolean OCI_ServerEnableOutput
(
    OCI_Connection *con, 
    unsigned int bufsize,
    unsigned int arrsize,
    unsigned int lnsize
);

/**
 * @brief 
 * Disable the server output
 *
 * @param con - Connection handle
 *
 * @note
 * After this call, OCI_ServerGetOutput() will return NULL.
 * 
 * @return 
 * TRUE on success otherwise FALSE
 *
 */

OCI_EXPORT boolean OCI_ServerDisableOutput
(
    OCI_Connection *con
);

/**
 * @brief 
 * Retreive one line the of server buffer
 *
 * @param con   - Connection handle
 *
 * @note
 * The current transaction is automatically stopped but the newly assigned
 * is not started or resumed.
 *
 * @note
 * Internally, OCILIB gets the server buffer through an array of lines in 
 * order to minimize roundtrips with the server
 * 
 * @return 
 * return a server ouput buffer line or NULL if the server buffer is empty
 *
 */

OCI_EXPORT const dtext * OCI_API OCI_ServerGetOutput
(
    OCI_Connection *con
);

/**
 * @}
 */

/**
 * @defgroup g_connpool Connection Pools
 * @{
 *
 * OCILIB support the OCI features Connection pooling introduced in Oracle 9i.
 *
 * @note
 * OCILIB implements its own pooling mechanism for Oracle 8i.
 *
 * @par Example
 * @include pool.c
 *
 */

/**
 * @brief 
 * Create a Connection pool
 *
 * @param db       - Oracle Service Name
 * @param user     - Oracle User name
 * @param pwd      - Oracle User password
 * @param mode     - Session mode
 * @param min_con  - minimum number of connections that can be opened.
 * @param max_con  - maximum number of connections that can be opened.
 * @param incr_con - next increment for connections to be opened
 * 
 * Possible values for parameter mode :
 * - OCI_SESSION_DEFAULT
 * - OCI_SESSION_SYSDBA
 * - OCI_SESSION_SYSOPER
 * 
 * @note
 *
 * @return 
 * Connection pool handle on succes or NULL on failure
 *
 */

OCI_EXPORT OCI_ConnPool * OCI_API OCI_ConnPoolCreate
(
    const mtext *db, 
    const mtext *user, 
    const mtext *pwd,
    int mode,
    int min_con,
    int max_con,
    int incr_con
);

/**
 * @brief 
 * Destroy a Connection pool object
 *
 * @param pool - Connection pool handle
 *
 * @return 
 * TRUE on success otherwise FALSE
 *
 */

OCI_EXPORT boolean OCI_API OCI_ConnPoolFree
(
    OCI_ConnPool *pool
);

/**
 * @brief 
 * Get a connection from the pool
 *
 * @param pool - Connection pool handle
 *
 * @note
 * 
 * @return
 * Connection handle otherwise NULL on failure
 */

OCI_EXPORT OCI_Connection * OCI_API OCI_ConnPoolGetConnection
(
    OCI_ConnPool *pool
);

/**
 * @brief 
 * Get the idle connection timeout 
 *
 * @param pool - Connection pool handle
 *
 * @note
 * Connections idle for more than this time value (in seconds) are terminated
 *
 * @note
 * Timeout is not available for internal pooling implementation (client < 9i)
 * 
 * @return
 *
 */

OCI_EXPORT int OCI_API OCI_ConnPoolGetTimeout
(
    OCI_ConnPool *pool
);

/**
 * @brief 
 * Set the idle connection timeout 
 *
 * @param pool  - Connection pool handle
 * @param value - Timeout value
 *
 * @note
 * Connections idle for more than this time value (in seconds) are terminated
 *
 * @note
 * this call has no effect if pooling is internally implemented (client < 9i)
 * 
 * @return
 *
 */

OCI_EXPORT boolean OCI_API OCI_ConnPoolSetTimeout
(
    OCI_ConnPool *pool,
    int value
);

/**
 * @brief 
 * Get the waiing mode used when no more connections are available from the 
 * pool
 *
 * @param pool - Connection pool handle
 *
 * @return
 * - FALSE to wait for an available connection if the pool is saturated
 * - TRUE to not wait for an available connection
 *
 */

OCI_EXPORT boolean OCI_API OCI_ConnPoolGetlGetNoWait
(
    OCI_ConnPool *pool
);

/**
 * @brief 
 * Set the waiing mode used when no more connections are available from the 
 * pool
 *
 * @param pool  - connection pool handle
 * @param value - wait for connection
 *
 * @note
 * Pass :
 * - FALSE to wait for an available connection if the pool is saturated
 * - TRUE to not wait for an available connection
 *
 * @return
 *
 */

OCI_EXPORT boolean OCI_API OCI_ConnPoolSetNoWait
(
    OCI_ConnPool *pool,
    boolean value
);

/**
 * @brief 
 * Return the current number of busy connections
 *
 * @param pool - Connection pool handle
 *
 */

OCI_EXPORT int OCI_API OCI_ConnPoolGetBusyCount
(
    OCI_ConnPool *pool
);

/**
 * @brief 
 * Return the current number of opened connections
 *
 * @param pool - Connection pool handle
 *
 */

OCI_EXPORT int OCI_API OCI_ConnPoolGetOpenedCount
(
    OCI_ConnPool *pool
);

/**
 * @brief 
 * Return the minimum number of connections that can be opened to the database
 *
 * @param pool - Connection pool handle
 *
 */

OCI_EXPORT int OCI_API OCI_ConnPoolGetMin
(
    OCI_ConnPool *pool
);

/**
 * @brief 
 * Return the maximum number of connections that can be opened to the database
 *
 * @param pool - Connection pool handle
 *
 */

OCI_EXPORT int OCI_API OCI_ConnPoolGetMax
(
    OCI_ConnPool *pool
);

/**
 * @brief 
 * Return the increment for connections to be opened to the database when the 
 * pool is not full
 *
 * @param pool - Connection pool handle
 *
 */

OCI_EXPORT int OCI_API OCI_ConnPoolGetIncrement
(
    OCI_ConnPool *pool
);

/**
 * @}
 */

/**
 * @defgroup g_transac Managing transactions
 * @{
 *
 * OCILIB supports local and global transactions.
 *
 * Local transactions are implicit within connection objects and there is no 
 * specific call or programming step for using it.
 * 
 * In order to control changes made in the database :
 * 
 * - OCI_Commit() validates current pending modifications
 * - OCI_Rollback() discards current pending modifications
 *
 * OCILIB supports a feature called 'AutoCommit' that performs an implicit and 
 * automatic commit call after every execute call
 *
 * @note
 * Those actions are executed within a connection context and not directly to
 * a transaction.
 *
 * @warning
 * Global transactions are optionnal and are designed for distributed or global
 * transaction environments. 
 *
 * OCILIB supports them by :
 * 
 * - Creating/Destroying explicitly a transaction object
 * - Starting/Stopping/Resuming explicitly the transaction
 * - Preparing the transaction for specific calls
 *
 */

/**
 * @brief 
 * Commit current pending changes
 *
 * @param con - Connection handle
 * 
 * @return 
 * TRUE on success otherwise FALSE
 *
 */

OCI_EXPORT boolean OCI_API OCI_Commit
(
    OCI_Connection *con
);

/**
 * @brief 
 * Cancel current pending changes
 *
 * @param con - Connection handle
 * 
 * @return 
 * TRUE on success otherwise FALSE
 *
 */

OCI_EXPORT boolean OCI_API OCI_Rollback
(
    OCI_Connection *con
);

/**
 * @brief 
 * Enable / disable auto commit mode
 *
 * The auto commit mode allows commit changes after every executed SQL order 
 *
 * @param con    - Connection handle
 * @param enable - Enable (TRUE) or disable (FALSE)
 * 
 * @return 
 * TRUE on success otherwise FALSE
 *
 */

OCI_EXPORT boolean OCI_API OCI_SetAutoCommit
(
    OCI_Connection *con,
    boolean enable
);

/**
 * @brief 
 * Get current auto commit mode status
 *
 * @param con - Connection handle
 * 
 * @return 
 * TRUE if auto commit mode is activated otherwise FALSE
 *
 */

OCI_EXPORT boolean OCI_API OCI_GetAutoCommit
(
    OCI_Connection *con
);

/**
 * @brief 
 * Create a new global transaction or a serializable/read-only local transaction
 *
 * @param con     - Connection handle
 * @param timeout - Time that a transaction stays inactive after being stopped
 * @param mode    - Connection mode
 * @param pxid    - pointer to a global transaction identifier stucture
 *
 *
 * @note 
 * The parameter 'mode' can be one of the following values :
 *
 * - Global transactions :
 *      - OCI_TRS_NEW : By default starts a new, tightly coupled and
 *                      migratable branch.
 *      - OCI_TRS_TIGHT : explicitly specifies a tightly coupled branch
 *      - OCI_TRS_LOOSE : specifies a loosely coupled branch
 *
 * - Global and local transactions :
 *      - OCI_TRS_READONLY - start a read-only transaction
 *      - OCI_TRS_READWRITE - start a read-write transaction
 *      - OCI_TRS_SERIALIZABLE : start a serializable transaction
 *
 * @note 
 * For local transaction :
 * - pass a NULL value for pxid
 *
 */

OCI_EXPORT OCI_Transaction * OCI_API OCI_TransactionCreate
(
    OCI_Connection *con,
    int timeout,
    int mode,
    OCI_XID *pxid
);

/**
 * @brief 
 * Free current transaction
 *
 * @param trans - Connection handle
 * 
 * @return 
 * TRUE on success otherwise FALSE
 *
 */

OCI_EXPORT boolean OCI_API OCI_TransactionFree
(
    OCI_Transaction * trans
);

/**
 * @brief 
 * Start global transaction
 *
 * @param trans - Connection handle
 * 
 * @return 
 * TRUE on success otherwise FALSE
 *
 */

OCI_EXPORT boolean OCI_API OCI_TransactionStart
(
    OCI_Transaction * trans
);

/**
 * @brief 
 * Stop current global transaction
 *
 * @param trans - Connection handle
 * 
 * @return 
 * TRUE on success otherwise FALSE
 *
 */

OCI_EXPORT boolean OCI_API OCI_TransactionStop
(
    OCI_Transaction * trans
);

/**
 * @brief 
 * Resume a stoppped global transaction
 *
 * @param trans - Global transaction handle
 * 
 * @return 
 * TRUE on success otherwise FALSE
 */

OCI_EXPORT boolean OCI_API OCI_TransactionResume
(
    OCI_Transaction * trans
);

/**
 * @brief 
 * Prepare a global transaction validation
 *
 * @param trans - Global transaction handle
 * 
 * @return 
 * TRUE on success otherwise FALSE
 *
 */

OCI_EXPORT boolean OCI_API OCI_TransactionPrepare
(
    OCI_Transaction * trans
);

/**
 * @brief 
 * Cancel the prepared global transaction validation
 *
 * @param trans - Global transaction handle
 * 
 * @return 
 * TRUE on success otherwise FALSE
 *
 */

OCI_EXPORT boolean OCI_API OCI_TransactionForget
(
    OCI_Transaction * trans
);

/**
 * @brief 
 * Return global transaction mode.
 *
 * @note:
 * see OCI_TransactionCreate() for possible values
 *
 * @param trans - Global transaction handle
 *
 * @return
 * Transaction mode or OCI_ERROR if trans is NULL
 *
 */

OCI_EXPORT int OCI_API OCI_TransactionGetMode
(
    OCI_Transaction * trans
);

/**
 * @brief 
 * Return global transaction Timeout
 *
 * @param trans - Global transaction handle
 *
 * @return
 * Transaction timeout or OCI_ERROR if trans is NULL
 *
 */

OCI_EXPORT int OCI_API OCI_TransactionGetTimeout
(
    OCI_Transaction * trans
);

/**
 * @}
 */

/**
 * @defgroup g_exec Executing statements
 * @{
 *
 * Executing SQL statements or PL/SQL blocks is really simple with OCILIB.
 *
 * First, call OCI_StatementCreate() to allocate a statement handle. Then :
 *
 * - Parse the SQL with OCI_Prepare()
 * - Execute it with OCI_Execute()
 *
 * These two steps can be done together by calling OCI_ExecuteStmt() that 
 * Parse and executes in one go.
 * 
 * To find out if the statement has affected any rows, call OCI_GetAffectedRows()
 * 
 * Finally, release the statement and its resources with OCI_StatementFree()
 *
 * @note
 * A statement can be parsed once and executed as many times as needed (see 
 * Binding variables section)
 *
 * @note
 * A OCI_Statement can be used to prepare and/or execute different SQL and PL/SQL 
 * statements as many times as needed.
 * for example, if the SQL processsing of an application is sequential, only
 * one statement handle is required
 *
 * @note
 * OCILIB supports nested levels of SQL statement processing. 
 * An application can loop through the resultset of the statement handle A,
 * executing statement B and fetching statement C at every loop, and so on ...
 *
 * @par Example
 * @include exec.c
 *
 */

/**
 * @brief 
 * Create a statement object and return its handle
 *
 * @param con - Connection handle
 * 
 * @return 
 * A statement handle on success otherwise NULL
 *
 */

OCI_EXPORT OCI_Statement * OCI_API OCI_StatementCreate
(
    OCI_Connection *con
);

/**
 * @brief 
 * Free a statement and all resources associated to it (resultsets, ....)
 *
 * @param stmt - Connection handle
 * 
 * @return 
 * TRUE on success otherwise FALSE
 *
 */

OCI_EXPORT boolean OCI_API OCI_StatementFree
(
    OCI_Statement *stmt
);

/**
 * @brief 
 * Prepare a SQL statement or PL/SQL block.
 *
 * @param stmt - Statement handle
 * @param sql  - SQL order or PL/SQL block
 * 
 * @note
 * With version 1.3.0 and above, do not call this function for fetched
 * statement handle (REF cursors)
 *
 * @return 
 * TRUE on success otherwise FALSE
 */

OCI_EXPORT boolean OCI_API OCI_Prepare
(
    OCI_Statement *stmt, 
    const mtext *sql
);

/**
 * @brief 
 * Execute a prepared SQL statement or PL/SQL block.
 *
 * @param stmt - Statement handle
 *
 * @return 
 * TRUE on success otherwise FALSE
 */

OCI_EXPORT boolean OCI_API OCI_Execute
(
    OCI_Statement *stmt
);

/**
 * @brief 
 * Parse and execute a SQL statement or PL/SQL block.
 *
 * @param stmt - Statement handle
 * @param sql  - SQL order - PL/SQL block
 *
 * @return 
 * TRUE on success otherwise FALSE
 */

OCI_EXPORT boolean OCI_API OCI_ExecuteStmt
(
    OCI_Statement *stmt, 
    const mtext *sql
);

/**
 * @brief 
 * Return the last SQL or PL/SQL statement parsed by the statement
 *
 * @param stmt - Statement handle
 * 
 */

OCI_EXPORT const mtext * OCI_API OCI_GetSql
(
    OCI_Statement *stmt
);

/**
 * @brief 
 * Return the number of rows affected by the SQL statement
 *
 * @param stmt - Statement handle
 *
 * The returned value is :
 *
 *  - For UPDATEs : number of rows updated 
 *  - For INSERTs : number of rows inserted 
 *  - For DELETEs : number of rows deleted 
 * 
 * @note
 * For SELECTs  statement, use OCI_GetRowCount() instead
 *
 */

OCI_EXPORT int OCI_API OCI_GetAffectedRows
(
    OCI_Statement *stmt
);

/**
 * @}
 */

/**
 * @defgroup g_bind Binding variables and arrays
 * @{
 *
 * OCILIB supports OCI data binding APIs
 *
 * Programs variables can be binded to an Oracle SQL PL/SQL statement in order to :
 * 
 * - Provide input data for SQL statement
 * - Provide input/outpout data for PL/SQL blocks
 * 
 * OCILIB provides a set of binding functions to use with :
 *
 * - Basic datatypes  : string (char/wchar_t *), int, double, raw
 * - Object datatypes : lobs, files,longs, dates, cursors, statements,
 *                      timestamps, intervals, objects
 *
 * To use binding :
 * 
 * - Prepare a statement with OCI_Prepare() (see Executing statements)
 * - Bind variables by calling one if the OCI_Bindxxxxx() function for every 
 *   input variable referenced by the SQL statement
 * - Setup up values of the program variables
 * - Call OCI_Execute() as many times as needed 
 * - Each OCI_Execute() call may be preceeded by an update of the program
 *   variables (for INSERTs for example) 
 *
 * OCILIB supports the OCI array Interface by binding arrays of C scalar types
 * and OCILIB object types.
 *
 * - all types supported the library can be used for array binding except 
 *   OCI_Statement and OCI_Long
 * - Array binding is really fast for massive DML operations
 * - For string/RAW arrays, the input array MUST BE a contiguous block of data 
 *   and not an array of pointers. So to bind an array of 10 elements for a 
 *   varchar2(30) column, binded variable must be a like array[10][31]
 *
 * OCILIB does not pre-parse statements (like other frameworks such as jdbc, ...)
 * and lets Oracle recognize input variables embedded within the SQL statements. 
 * 
 * Bind variables must be precedeed in the SQL code by the character ':'.
 *
 * Oracle and OCILIB supports two ways of binding :
 * 
 * - by name (default mode in OCILIB) : Oracle looks for variables in the SQL
 *   statement  by searching their names provided to the binding function.
 *   So a variable can be binded once and used many times in the statement
 * - by position : Oracle binds variables by position, so every variable is 
 *   binded with a position number
 *
 * @par Basic input bind Example
 * @include bind.c
 *
 * @par Pl/Sql output bind Example
 * @include plsql.c
 *
 * @par Array interface Example
 * @include array.c
 *
 */

/**
 * @brief 
 * Set the input array size for bulk operations
 *
 * @param stmt - Statement handle
 * @param size - Array size
 * 
 * @return 
 * TRUE on success otherwise FALSE
 */

OCI_EXPORT boolean OCI_API OCI_BindArraySetSize
(
    OCI_Statement *stmt, 
    int size
);

/**
 * @brief 
 * Return the input array size for bulk operations
 *
 * @param stmt - Statement handle
 * 
 * @return 
 * Array size value or 0 if OCI_BindArraySetSize() has not been called
 *
 */

OCI_EXPORT int OCI_API OCI_BindArrayGetSize
(
    OCI_Statement *stmt
);

/**
 * @brief 
 * Bind an short variable
 *
 * @param stmt - Statement handle
 * @param name - Variable name
 * @param data - Pointer to short variable
 * 
 * @return 
 * TRUE on success otherwise FALSE
 */

OCI_EXPORT boolean OCI_API OCI_BindShort
(
    OCI_Statement *stmt, 
    const mtext *name,
    short *data
);

/**
 * @brief 
 * Bind an array of shorts
 *
 * @param stmt   - Statement handle
 * @param name   - Variable name
 * @param data   - Array of shorts
 * @param nbelem - Number of element in the array
 * 
 * @return 
 * TRUE on success otherwise FALSE
 */

OCI_EXPORT boolean OCI_API OCI_BindArrayOfShorts
(
    OCI_Statement *stmt, 
    const mtext *name,
    short *data,
    unsigned int nbelem
);

/**
 * @brief 
 * Bind an unsigned short variable
 *
 * @param stmt - Statement handle
 * @param name - Variable name
 * @param data - Pointer to unsigned short variable
 * 
 * @return 
 * TRUE on success otherwise FALSE
 */

OCI_EXPORT boolean OCI_API OCI_BindUnsignedShort
(
    OCI_Statement *stmt, 
    const mtext *name,
    unsigned short *data
);

/**
 * @brief 
 * Bind an array of unsigned shorts
 *
 * @param stmt   - Statement handle
 * @param name   - Variable name
 * @param data   - Array of unsigned shorts
 * @param nbelem - Number of element in the array
 * 
 * @return 
 * TRUE on success otherwise FALSE
 */

OCI_EXPORT boolean OCI_API OCI_BindArrayOfUnsignedShorts
(
    OCI_Statement *stmt, 
    const mtext *name,
    unsigned short *data,
    unsigned int nbelem
);

/**
 * @brief 
 * Bind an integer variable
 *
 * @param stmt - Statement handle
 * @param name - Variable name
 * @param data - Pointer to int variable
 * 
 * @return 
 * TRUE on success otherwise FALSE
 */

OCI_EXPORT boolean OCI_API OCI_BindInt
(
    OCI_Statement *stmt, 
    const mtext *name,
    int *data
);

/**
 * @brief 
 * Bind an array of integers
 *
 * @param stmt   - Statement handle
 * @param name   - Variable name
 * @param data   - Array of int
 * @param nbelem - Number of element in the array
 *
 * @return 
 * TRUE on success otherwise FALSE
 */

OCI_EXPORT boolean OCI_API OCI_BindArrayOfInts
(
    OCI_Statement *stmt, 
    const mtext *name,
    int *data,
    unsigned int nbelem
);

/**
 * @brief 
 * Bind an unsigned integer variable
 *
 * @param stmt - Statement handle
 * @param name - Variable name
 * @param data - Pointer to unsigned int variable
 * 
 * @return 
 * TRUE on success otherwise FALSE
 */

OCI_EXPORT boolean OCI_API OCI_BindUnsignedInt
(
    OCI_Statement *stmt, 
    const mtext *name,
    unsigned int *data
);

/**
 * @brief 
 * Bind an array of unsigned integers
 *
 * @param stmt   - Statement handle
 * @param name   - Variable name
 * @param data   - Array of unsigned int
 * @param nbelem - Number of element in the array
 *
 * @return 
 * TRUE on success otherwise FALSE
 */

OCI_EXPORT boolean OCI_API OCI_BindArrayOfUnsignedInts
(
    OCI_Statement *stmt, 
    const mtext *name,
    unsigned int *data,
    unsigned int nbelem
);

/**
 * @brief 
 * Bind an big integer variable
 *
 * @param stmt - Statement handle
 * @param name - Variable name
 * @param data - Pointer to big int variable
 * 
 * @return 
 * TRUE on success otherwise FALSE
 */

OCI_EXPORT boolean OCI_API OCI_BindBigInt
(
    OCI_Statement *stmt, 
    const mtext *name,
    big_int *data
);

/**
 * @brief 
 * Bind an array of big integers
 *
 * @param stmt   - Statement handle
 * @param name   - Variable name
 * @param data   - Array of big int
 * @param nbelem - Number of element in the array
 *
 * @return 
 * TRUE on success otherwise FALSE
 */

OCI_EXPORT boolean OCI_API OCI_BindArrayOfBigInts
(
    OCI_Statement *stmt, 
    const mtext *name,
    big_int *data,
    unsigned int nbelem
);

/**
 * @brief 
 * Bind an unsigned big integer variable
 *
 * @param stmt - Statement handle
 * @param name - Variable name
 * @param data - Pointer to unsigned big int variable
 * 
 * @return 
 * TRUE on success otherwise FALSE
 */

OCI_EXPORT boolean OCI_API OCI_BindUnsignedBigInt
(
    OCI_Statement *stmt, 
    const mtext *name,
    big_uint *data
);

/**
 * @brief 
 * Bind an array of unsigned big integers
 *
 * @param stmt - Statement handle
 * @param name - Variable name
 * @param data - Array of unsigned big int
 * @param nbelem - Number of element in the array
 *
 * @return 
 * TRUE on success otherwise FALSE
 */

OCI_EXPORT boolean OCI_API OCI_BindArrayOfUnsignedBigInts
(
    OCI_Statement *stmt, 
    const mtext *name,
    big_uint *data,
    unsigned int nbelem
);

/**
 * @brief 
 * Bind a string variable
 *
 * @param stmt - Statement handle
 * @param name - Variable name
 * @param data - String to bind
 * @param len  - Max length of the string (in character without 
 *               the zero null terminal character)
 * 
 * @note
 * if len <= 0, len is set to the string size
 *
 * @return 
 * TRUE on success otherwise FALSE
 */

OCI_EXPORT boolean OCI_API OCI_BindString
(
    OCI_Statement *stmt, 
    const mtext *name,
    dtext *data, 
    int len
);

/**
 * @brief 
 * Bind an array of strings
 *
 * @param stmt   - Statement handle
 * @param name   - Variable name
 * @param data   - Array of string
 * @param len    - Max length of a single string element (in character without 
 *                 the zero null terminal character)
 * @param nbelem - Number of element in the array
 *
 * @note
 * if len <= 0, it returns FALSE
 *
 * @return 
 * TRUE on success otherwise FALSE
 */

OCI_EXPORT boolean OCI_API OCI_BindArrayOfStrings
(
    OCI_Statement *stmt, 
    const mtext *name,
    dtext *data, 
    int len,
    unsigned int nbelem
);

/**
 * @brief 
 * Bind a raw buffer
 *
 * @param stmt - Statement handle
 * @param name - Variable name
 * @param data - buffer to bind
 * @param len  - Max length of the buffer
 * 
 * @note
 * if len <= 0, it returns false
 *
 * @return 
 * TRUE on success otherwise FALSE
 */

OCI_EXPORT boolean OCI_API OCI_BindRaw
(
    OCI_Statement *stmt, 
    const mtext *name,
    void *data, 
    int len
);

/**
 * @brief 
 * Bind an array of raw buffers
 *
 * @param stmt   - Statement handle
 * @param name   - Variable name
 * @param data   - Array of buffers
 * @param len    - Size in bytes on a single RAW array element
 * @param nbelem - Number of element in the array
 *
 * @note
 * the buffer must be a contiguous block of data elements
 *
 * @note
 * if len <= 0, it returns FALSE
 *
 * @return 
 * TRUE on success otherwise FALSE
 */

OCI_EXPORT boolean OCI_API OCI_BindArrayOfRaws
(
    OCI_Statement *stmt, 
    const mtext *name,
    void *data, 
    int len,
    unsigned int nbelem
);

/**
 * @brief 
 * Bind a double variable
 *
 * @param stmt - Statement handle
 * @param name - Variable name
 * @param data - Pointer to double variable
 * 
 * @return 
 * TRUE on success otherwise FALSE
 */

OCI_EXPORT boolean OCI_API OCI_BindDouble
(
    OCI_Statement *stmt, 
    const mtext *name,
    double *data
);

/**
 * @brief 
 * Bind an array of doubles
 *
 * @param stmt   - Statement handle
 * @param name   - Variable name
 * @param data   - Array of double
 * @param nbelem - Number of element in the array
 *
 * @return 
 * TRUE on success otherwise FALSE
 */

OCI_EXPORT boolean OCI_API OCI_BindArrayOfDoubles
(
    OCI_Statement *stmt, 
    const mtext *name,
    double *data,
    unsigned int nbelem
);

/**
 * @brief 
 * Bind a date variable
 *
 * @param stmt - Statement handle
 * @param name - Variable name
 * @param data - Date handle
 * 
 * @return 
 * TRUE on success otherwise FALSE
 */

OCI_EXPORT boolean OCI_API OCI_BindDate
(
    OCI_Statement *stmt, 
    const mtext *name,
    OCI_Date *data
);

/**
 * @brief 
 * Bind an array of dates
 *
 * @param stmt   - Statement handle
 * @param name   - Variable name
 * @param data   - Array of date handle
 * @param nbelem - Number of element in the array
 *
 * @return 
 * TRUE on success otherwise FALSE
 */

OCI_EXPORT boolean OCI_API OCI_BindArrayOfDates
(
    OCI_Statement *stmt, 
    const mtext *name,
    OCI_Date **data,
    unsigned int nbelem
);

/**
 * @brief 
 * Bind a timestamp variable
 *
 * @param stmt - Statement handle
 * @param name - Variable name
 * @param data - Timestamp handle
 * 
 * @return 
 * TRUE on success otherwise FALSE
 */

OCI_EXPORT boolean OCI_API OCI_BindTimestamp
(
    OCI_Statement *stmt, 
    const mtext *name,
    OCI_Timestamp *data
);

/**
 * @brief 
 * Bind an array of timestamp handles
 *
 * @param stmt   - Statement handle
 * @param name   - Variable name
 * @param data   - Array of Timestamp handle
 * @param type   - Timestamp type
 * @param nbelem - Number of element in the array
 * 
 * @note
 * See OCI_TimestampCreate() for possible values of parameter 'type'
 *
 * @return 
 * TRUE on success otherwise FALSE
 */

OCI_EXPORT boolean OCI_API OCI_BindArrayOfTimestamps
(
    OCI_Statement *stmt, 
    const mtext *name,
    OCI_Timestamp **data,
    int type,
    unsigned int nbelem
);

/**
 * @brief 
 * Bind an interval variable
 *
 * @param stmt - Statement handle
 * @param name - Variable name
 * @param data - Interval handle
 *
 * @return 
 * TRUE on success otherwise FALSE
 *
 */

OCI_EXPORT boolean OCI_API OCI_BindInterval
(
    OCI_Statement *stmt, 
    const mtext *name,
    OCI_Interval *data
);

/**
 * @brief 
 * Bind an array of interval handles
 *
 * @param stmt   - Statement handle
 * @param name   - Variable name
 * @param data   - Array of Interval handle
 * @param type   - Interval type
 * @param nbelem - Number of element in the array
 * 
 * @note
 * See OCI_IntervalCreate() for possible values of parameter 'type'
 *
 * @return 
 * TRUE on success otherwise FALSE
 *
 */

OCI_EXPORT boolean OCI_API OCI_BindArrayOfIntervals
(
    OCI_Statement *stmt, 
    const mtext *name,
    OCI_Interval **data,
    int type,
    unsigned int nbelem
);

/**
 * @brief 
 * Bind a Lob variable
 *
 * @param stmt - Statement handle
 * @param name - Variable name
 * @param data - Lob handle
 * 
 * @return 
 * TRUE on success otherwise FALSE
 */

OCI_EXPORT boolean OCI_API OCI_BindLob
(
    OCI_Statement *stmt, 
    const mtext *name,
    OCI_Lob *data
);

/**
 * @brief 
 * Bind an array of Lob handles
 *
 * @param stmt   - Statement handle
 * @param name   - Variable name
 * @param data   - Array of Lob handle
 * @param type   - Lob type
 * @param nbelem - Number of element in the array
 * 
 * @note
 * See OCI_LobCreate() for possible values of parameter 'type'
 *
 * @return 
 * TRUE on success otherwise FALSE
 */

OCI_EXPORT boolean OCI_API OCI_BindArrayOfLobs
(
    OCI_Statement *stmt, 
    const mtext *name,
    OCI_Lob **data,
    int type,
    unsigned int nbelem
);

/**
 * @brief 
 * Bind a File variable
 *
 * @param stmt - Statement handle
 * @param name - Variable name
 * @param data - File handle
 * 
 * @return 
 * TRUE on success otherwise FALSE
 */

OCI_EXPORT boolean OCI_API OCI_BindFile
(
    OCI_Statement *stmt, 
    const mtext *name,
    OCI_File *data
);

/**
 * @brief 
 * Bind an array of File handles
 *
 * @param stmt   - Statement handle
 * @param name   - Variable name
 * @param data   - Array of File handle
 * @param type   - File type
 * @param nbelem - Number of element in the array
 * 
 * @note
 * See OCI_FileCreate() for possible values of parameter 'type'
 *
 * @return 
 * TRUE on success otherwise FALSE
 */

OCI_EXPORT boolean OCI_API OCI_BindArrayOfFiles
(
    OCI_Statement *stmt, 
    const mtext *name,
    OCI_File **data,
    int type,
    unsigned int nbelem
);

/**
 * @brief 
 * Bind an object (named type) variable
 *
 * @param stmt - Statement handle
 * @param name - Variable name
 * @param data - Object handle
 *
 * @return 
 * TRUE on success otherwise FALSE
 *
 */

OCI_EXPORT boolean OCI_API OCI_BindObject
(
    OCI_Statement *stmt, 
    const mtext *name,
    OCI_Object *data
);


/**
 * @brief 
 * Bind an array of object handles
 *
 * @param stmt   - Statement handle
 * @param name   - Variable name
 * @param data   - Array of object handle
 * @param schema - type schema handle
 * @param nbelem - Number of element in the array
 *
 * @return 
 * TRUE on success otherwise FALSE
 *
 */
OCI_EXPORT boolean OCI_API OCI_BindArrayOfObjects
(
    OCI_Statement *stmt, 
    const mtext *name,
    OCI_Object **data,
    OCI_Schema *schema,
    unsigned int nbelem
);

/**
 * @brief 
 * Bind a Statement variable (PL/SQL Ref Cursor)
 *
 * @param stmt - Statement handle
 * @param name - Variable name
 * @param data - Statement handle to bind
 * 
 * @return 
 * TRUE on success otherwise FALSE
 */

OCI_EXPORT boolean OCI_API OCI_BindStatement
(
    OCI_Statement *stmt, 
    const mtext *name,
    OCI_Statement *data
);

/**
 * @brief 
 * Bind a Long variable
 *
 * @param stmt - Statement handle
 * @param name - Variable name
 * @param data - Long handle
 * @param size - Size of the long buffer in bytes or characters
 *
 * @note
 * Size is expressed in :
 * - Bytes for BLONGs
 * - Characters for CLONGs
 * 
 * @return 
 * TRUE on success otherwise FALSE
 */


OCI_EXPORT boolean OCI_API OCI_BindLong
(
    OCI_Statement *stmt, 
    const mtext *name,
    OCI_Long *data, 
    unsigned int size
);

/**
 * @brief 
 * Set the bind variable at the given position to null
 *
 * @param stmt  - Statement handle
 * @param index - Index of the bind variable
 * 
 * @note
 * There is no notion of null value in C. 
 * it's necessary to explicitly tell Oracle that the bind has a null value. 
 * It must be done before an OCI_Execute() call
 *
 * @note
 * For handled based datatypes (non scalar types), OCILIB performs an extra 
 * check on handles and set the bind status to null is the handle is null
 *
 * @return 
 * TRUE on success otherwise FALSE
 */

OCI_EXPORT boolean OCI_API OCI_SetNull
(
    OCI_Statement *stmt, 
    int index
);

/**
 * @brief 
 * Set to null the bind variable at the given position in an input array
 *
 * @param stmt     - Statement handle
 * @param index    - Index of the bind variable
 * @param position - Position in the array
 * 
 * @note
 * There is no notion of null value in C. 
 * it's necessary to explicitly tell Oracle that the bind has a null value. 
 * It must be done before an OCI_Execute() call
 *
 * @note
 * For handled based datatypes (non scalar types), OCILIB performs an extra 
 * check on handles and set the bind status to null is the handle is null 
 *
 * @return 
 * TRUE on success otherwise FALSE
 */

OCI_EXPORT boolean OCI_API OCI_SetNullAtPos
(
    OCI_Statement *stmt, 
    int index,
    int position
);

/**
 * @}
 */

/**
 * @defgroup g_fetch Fetching data
 * @{
 *
 * OCILIB offers a really easy and smart mecanism to fetch data from a SQL 
 * Statement.
 * It looks like what's found in JDBC and other object oriented databases
 * frameworks.
 * 
 * Only SELECTs statement, DML with returning clause and some PL/SQL blocks 
 * return a cursor that can be fetched by host programs. 
 * That cursor, or resultset, is encapsulated in OCILIB by the OCI_Resultset
 * object.
 *
 * So, after any successful call to an OCI_Executexxx() function that executed
 * a fetchable statement or filled output bind variables, the resultset can be 
 * retrieved by calling OCI_GetResultset()
 *
 *
 * The creation of a OCI_Resultset object consists in :
 *
 * - Describing the output columns of the resultset
 * - Allocating memory to hold the content data
 * 
 * OCILIB supports multi-row fetching for increasing performances. Instead of 
 * fetching data row by row from the server (thart induces lots of roundtrips 
 * between the client and the server), the library prefetches data chunk by 
 * chunk (default is 20 rows). 
 * So, less network traffic and better performances.
 * These mecanisms are completely hidden from the application which fetches the 
 * resultset row by row.
 *
 * Once the Resultset handle is retrieved :
 *
 * - It can be fetched by calling OCI_FetchNext() as long as it returns TRUE. 
 * - To retrieve the value of a column, call OCI_GetXXXX() where XXXX is the 
 *   type of data you want to fetch.
 * 
 * @note
 * If the column internal data does not match the requested type, OCILIB tries
 * to convert the data when it's possible and throws an error if not.
 *
 * At this time, OCILIB only supports forward fetching (Oracle introduced 
 * bidirectionnal fetching with Oracle 9i but it requires more memory, more 
 * complicated mecanisms, ...)
 *
 * The properties (columns names, types, ...) of the resultset are accessible 
 * through a set of APIs.
 *
 * @par Fetch Example
 * @include fetch.c
 *
 * @par Metadata Example
 * @include meta.c
 *
 * @par Ref cursor Example
 * @include cursor.c
 *
 */

/**
 * @brief 
 * Retrieve the resultset handle from an executed statement
 *
 * @param stmt - Statement handle 
 * 
 * @note
 * On a successful SELECT execution, OCI_GetResultset() always allocates a 
 * resultset wherever it contains rows.
 *
 * @note
 * If a DML statement includes an returning clause, a resultset is implicitly
 * created at the SQL statement execution time
 *
 * @warning
 * If the statement has not been prepared and executed, no resultset will be 
 * returned
 * 
 * @return
 * A resultset handle on success otherwise NULL
 *
 */

OCI_EXPORT OCI_Resultset * OCI_API OCI_GetResultset
(
    OCI_Statement *stmt
);

/**
 * @brief 
 * Free the statement resulsets
 *
 * @param stmt - Statement handle 
 * 
 * @note
 * This call is optionnal. Resulsets are automatically freed where the
 * statement is destroyed or when it's reused.
 *
 * @note
 * This function has been introduced for releasing big resultsets when the 
 * application wants to keep the statement alive and doesn't know when it
 * will be destroyed.
 * 
 * @return 
 * TRUE on success otherwise FALSE
 *
 */

OCI_EXPORT boolean OCI_API OCI_ReleaseResultsets
(
    OCI_Statement *stmt
);
 
/**
 * @brief 
 * Fetch the next row of the resultset
 *
 * @param rs - Resultset handle
 * 
 * @return 
 * TRUE on success otherwise FALSE if :
 * - Empty resulset
 * - Last row fetched
 * - An error occured
 *
 */

OCI_EXPORT boolean OCI_API OCI_FetchNext
(
    OCI_Resultset *rs
);

/**
 * @brief 
 * Retrieve the number of rows fetched so far
 *
 * @param rs - Resultset handle
 * 
 */

OCI_EXPORT int OCI_API OCI_GetRowCount
(
    OCI_Resultset *rs
);

/**
 * @brief 
 * Return the number of columns in the resulset 
 *
 * @param rs - Resultset handle
 * 
 */

OCI_EXPORT int OCI_API OCI_GetColumnCount
(
    OCI_Resultset *rs
);

/**
 * @brief 
 * Return the column object handle at the given index in the resultset
 *
 * @param rs    - Resultset handle
 * @param index - Column position
 * 
 * @return 
 * - Column handle on success 
 * - NULL if index is out of bounds or on error
 * 
 */

OCI_EXPORT OCI_Column * OCI_API OCI_GetColumn
(
    OCI_Resultset *rs,
    int index
);

/**
 * @brief 
 * Return the column object handle from its name in the resultset
 *
 * @param rs    - Resultset handle
 * @param name  - Column name
 * 
 * @note
 * The column name is case insensitive
 *
 * @return 
 * - Column handle on success or 
 * - NULL if no column found with the given name or on error
 * 
 */

OCI_EXPORT OCI_Column * OCI_API OCI_GetColumn2
(
    OCI_Resultset *rs,
    const mtext *name
);
/**
 * @brief 
 * Return the index of the column in the result from its name
 *
 * @param rs    - Resultset handle
 * @param name  - Column name
 * 
 * @note
 * The column name is case insensitive
 *
 * @return 
 * Column index on success or -1 on error
 * 
 */

OCI_EXPORT int OCI_API OCI_GetColumnIndex
(
    OCI_Resultset *rs,
    const mtext *name
);

/**
 * @brief 
 * Return the name of the given column
 *
 * @param col   - Column handle
 * 
 */

OCI_EXPORT const mtext * OCI_API OCI_GetColumnName
(
    OCI_Column *col
);

/**
 * @brief 
 * Return the type of the given column
 *
 * @param col   - Column handle
 *
 * @note
 * Possibles values are :
 *
 * - OCI_CDT_INTEGER     : int
 * - OCI_CDT_DOUBLE      : double 
 * - OCI_CDT_TEXT        : dtext *
 * - OCI_CDT_RAW         : void *
 * - OCI_CDT_DATETIME    : OCI_Date *
 * - OCI_CDT_LONG        : OCI_Long *      
 * - OCI_CDT_CURSOR      : OCI_Statement *
 * - OCI_CDT_LOB         : OCI_Lob  *
 * - OCI_CDT_FILE        : OCI_File *
 * - OCI_CDT_TIMESTAMP   : OCI_Timestamp *
 * - OCI_CDT_INTERVAL    : OCI_Interval *
 * - OCI_CDT_OBJECT      : OCI_Object *
 *
 * @return 
 * The column type or OCI_CDT_UNKNOWN if index is out of bounds
 * 
 */

OCI_EXPORT int OCI_API OCI_GetColumnType
(
    OCI_Column *col
);

/**
 * @brief 
 * Return the charset form of the given column
 *
 * @param col   - Column handle
 *
 * @note
 * Possibles values are :
 * - OCI_CSF_NONE     : the column is not an character or lob column
 * - OCI_CSF_CHARSET  : the column has server default charset
 * - OCI_CSF_NATIONAL : the columns has national server charset
 */

OCI_EXPORT int OCI_API OCI_GetColumnCharsetForm
(
    OCI_Column *col
);

/**
 * @brief 
 * Return the Oracle SQL type name of the column datatype
 *
 * @param col   - Column handle
 *
 * @note
 * For possibles values, consults Oracle Documentation
 * 
 */

OCI_EXPORT const mtext * OCI_API OCI_GetColumnSQLType
(
    OCI_Column *col
);


/**
 * @brief 
 * Return the Oracle SQL Full name including precision and size of the
 * column datatype
 *
 * @param col    - Column handle
 * @param buffer - buffer to store the full column type name and size
 * @param len    - max size of the buffer in characters
 *
 * @note
 * this function returns a description that matches the one given by SQL*Plus

 * @note
 * Return the number of characters written into the buffer
 * 
 */

OCI_EXPORT int OCI_API OCI_GetColumnFullSQLType
(
    OCI_Column *col,
    mtext *buffer,
    int len
);

/**
 * @brief 
 * Return the size of the column
 *
 * @note
 * For all types, the size is expressed is bytes, excepted for character 
 * based columns that were created with a character based size or 
 * of type NCHAR/NVARCHAR
 *
 * @param col   - Column handle
 *
 */

OCI_EXPORT int OCI_API OCI_GetColumnSize
(
    OCI_Column *col
);

/**
 * @brief 
 * Return the scale of the column for numeric columns
 *
 * @param col   - Column handle
 *
 */

OCI_EXPORT int OCI_API OCI_GetColumnScale
(
    OCI_Column *col
);

/**
 * @brief 
 * Return the precision of the column for numeric columns
 *
 * @param col   - Column handle
 *
 */

OCI_EXPORT int OCI_API OCI_GetColumnPrecision
(
    OCI_Column *col
);

/**
 * @brief 
 * Return the fractionnal precision of the column for timestamp and 
 * interval columns
 *
 * @param col   - Column handle
 *
 */

OCI_EXPORT int OCI_API OCI_GetColumnFractionnalPrecision
(
    OCI_Column *col
);

/**
 * @brief 
 * Return the leading precision of the column for interval columns
 *
 * @param col   - Column handle
 *
 */

OCI_EXPORT int OCI_API OCI_GetColumnLeadingPrecision
(
    OCI_Column *col
);

/**
 * @brief 
 * Return the nullable attribute of the column
 *
 * @param col   - Column handle
 *
 * @return
 * Return TRUE if the column is nullable otherwise FALSE
 */

OCI_EXPORT boolean OCI_API OCI_GetColumnNullable
(
    OCI_Column *col
);

/**
 * @brief 
 * Return TRUE if the length of the column is character-length or  FALSE if 
 * it is byte-length
 *
 * @note
 * This was introduced in Oracle 9i. So for version that are not supporting this
 * property, it always return FALSE
 *
 * @param col - Column handle
 *
 */

OCI_EXPORT boolean OCI_API OCI_GetColumnCharUsed
(
    OCI_Column *col
);

/**
 * @brief 
 * Return the current short value of the column at the given index 
 * in the resultset
 *
 * @param rs    - Resultset handle
 * @param index - Column position
 * 
 * @note
 * Column position starts at 1.
 *
 * @return 
 * The column current row value or 0 if index is out of bounds
 * 
 */

OCI_EXPORT short OCI_API OCI_GetShort
(
    OCI_Resultset *rs,
    int index
);

/**
 * @brief 
 * Return the current short value of the column from its name
 * in the resultset
 *
 * @param rs    - Resultset handle
 * @param name  - Column name
 * 
 * @note
 * The column name is case insensitive
 *
 * @return 
 * The column current row value or 0 if no column found with the given name
 * 
 */

OCI_EXPORT short OCI_API OCI_GetShort2
(
    OCI_Resultset *rs,
    const mtext *name
);

/**
 * @brief 
 * Return the current unsigned short value of the column at the given index 
 * in the resultset
 *
 * @param rs    - Resultset handle
 * @param index - Column position
 * 
 * @note
 * Column position starts at 1.
 *
 * @return 
 * The column current row value or 0 if index is out of bounds
 * 
 */

OCI_EXPORT unsigned short OCI_API OCI_GetUnsignedShort
(
    OCI_Resultset *rs,
    int index
);

/**
 * @brief 
 * Return the current unsigned short value of the column from its name
 * in the resultset
 *
 * @param rs    - Resultset handle
 * @param name  - Column name
 * 
 * @note
 * The column name is case insensitive
 *
 * @return 
 * The column current row value or 0 if no column found with the given name
 * 
 */

OCI_EXPORT unsigned short OCI_API OCI_GetUnsignedShort2
(
    OCI_Resultset *rs,
    const mtext *name
);

/**
 * @brief 
 * Return the current integer value of the column at the given index 
 * in the resultset
 *
 * @param rs    - Resultset handle
 * @param index - Column position
 * 
 * @note
 * Column position starts at 1.
 *
 * @return 
 * The column current row value or 0 if index is out of bounds
 * 
 */

OCI_EXPORT int OCI_API OCI_GetInt
(
    OCI_Resultset *rs,
    int index
);

/**
 * @brief 
 * Return the current integer value of the column from its name
 * in the resultset
 *
 * @param rs    - Resultset handle
 * @param name  - Column name
 * 
 * @note
 * The column name is case insensitive
 *
 * @return 
 * The column current row value or 0 if no column found with the given name
 * 
 */

OCI_EXPORT int OCI_API OCI_GetInt2
(
    OCI_Resultset *rs,
    const mtext *name
);

/**
 * @brief 
 * Return the current unsigned integer value of the column at the given index 
 * in the resultset
 *
 * @param rs    - Resultset handle
 * @param index - Column position
 * 
 * @note
 * Column position starts at 1.
 *
 * @return 
 * The column current row value or 0 if index is out of bounds
 * 
 */

OCI_EXPORT unsigned int OCI_API OCI_GetUnsignedInt
(
    OCI_Resultset *rs,
    int index
);

/**
 * @brief 
 * Return the current unsigned integer value of the column from its name
 * in the resultset
 *
 * @param rs    - Resultset handle
 * @param name  - Column name
 * 
 * @note
 * The column name is case insensitive
 *
 * @return 
 * The column current row value or 0 if no column found with the given name
 * 
 */

OCI_EXPORT unsigned int OCI_API OCI_GetUnsignedInt2
(
    OCI_Resultset *rs,
    const mtext *name
);

/**
 * @brief 
 * Return the current big integer value of the column at the given index 
 * in the resultset
 *
 * @param rs    - Resultset handle
 * @param index - Column position
 * 
 * @note
 * Column position starts at 1.
 *
 * @return 
 * The column current row value or 0 if index is out of bounds
 * 
 */

OCI_EXPORT big_int OCI_API OCI_GetBigInt
(
    OCI_Resultset *rs,
    int index
);

/**
 * @brief 
 * Return the current big integer value of the column from its name
 * in the resultset
 *
 * @param rs    - Resultset handle
 * @param name  - Column name
 * 
 * @note
 * The column name is case insensitive
 *
 * @return 
 * The column current row value or 0 if no column found with the given name
 * 
 */

OCI_EXPORT big_int OCI_API OCI_GetBigInt2
(
    OCI_Resultset *rs,
    const mtext *name
);

/**
 * @brief 
 * Return the current unsigned big integer value of the column at the given index 
 * in the resultset
 *
 * @param rs    - Resultset handle
 * @param index - Column position
 * 
 * @note
 * Column position starts at 1.
 *
 * @return 
 * The column current row value or 0 if index is out of bounds
 * 
 */

OCI_EXPORT big_uint OCI_API OCI_GetUnsignedBigInt
(
    OCI_Resultset *rs,
    int index
);

/**
 * @brief 
 * Return the current unsigned big integer value of the column from its name
 * in the resultset
 *
 * @param rs    - Resultset handle
 * @param name  - Column name
 * 
 * @note
 * The column name is case insensitive
 *
 * @return 
 * The column current row value or 0 if no column found with the given name
 * 
 */

OCI_EXPORT big_uint OCI_API OCI_GetUnsignedBigInt2
(
    OCI_Resultset *rs,
    const mtext *name
);

/**
 * @brief 
 * Return the current string value of the column at the given index 
 * in the resultset
 *
 * @param rs    - Resultset handle
 * @param index - Column position
 * 
 * @note
 * Column position starts at 1.
 *
 * @return 
 * The column current row value or NULL if index is out of bounds
 * 
 */

OCI_EXPORT const dtext * OCI_API OCI_GetString
(
    OCI_Resultset *rs,
    int index
);

/**
 * @brief 
 * Return the current string value of the column from its name
 * in the resultset
 *
 * @param rs    - Resultset handle
 * @param name  - Column name
 * 
 * @note
 * The column name is case insensitive
 * 
 * @return 
 * The column current row value or NULL if no column found with the given name
 * 
 */

OCI_EXPORT const dtext * OCI_API OCI_GetString2
(
    OCI_Resultset *rs,
    const mtext *name
);

/**
 * @brief 
 * Copy the current raw value of the column at the given index into the 
 * specified buffer
 *
 * @param rs     - Resultset handle
 * @param index  - Column position
 * @param buffer - Buffer that receive the raw value
 * @param len    - Max size of the input buffer in bytes
 * 
 * @note
 * Column position starts at 1.
 *
 * @return 
 * Number of bytes copied into the buffer on SUCCESS otherwise 0
 * 
 */

OCI_EXPORT int OCI_API OCI_GetRaw
(
    OCI_Resultset *rs,
    int index,
    void *buffer,
    int len
);

/**
 * @brief 
 * Copy the current raw value of the column from its name into the specified buffer
 *
 * @param rs     - Resultset handle
 * @param name   - Column name
 * @param buffer - Buffer that receive the raw value
 * @param len    - Max size of the input buffer
 * 
 * @note
 * The column name is case insensitive
 * 
 * @return 
 * Number of bytes copied into the buffer on SUCCESS otherwise 0
 * 
 */

OCI_EXPORT int OCI_API OCI_GetRaw2
(
    OCI_Resultset *rs,
    const mtext *name,
    void *buffer,
    int len
);


/**
 * @brief 
 * Return the current double value of the column at the given index 
 * in the resultset
 *
 * @param rs    - Resultset handle
 * @param index - Column position
 * 
 * @note
 * Column position starts at 1.
 *
 * @return 
 * The column current row value or 0.O if index is out of bounds
 * 
 */

OCI_EXPORT double OCI_API OCI_GetDouble
(
    OCI_Resultset *rs,
    int index
);

/**
 * @brief 
 * Return the current double value of the column from its name
 * in the resultset
 *
 * @param rs    - Resultset handle
 * @param name  - Column name
 * 
 * @note
 * The column name is case insensitive
 *
 * @return 
 * The column current row value or 0.0 if no column found with the given name
 * 
 */

OCI_EXPORT double OCI_API OCI_GetDouble2
(
    OCI_Resultset *rs,
    const mtext *name
);

/**
 * @brief 
 * Return the current date value of the column at the given index 
 * in the resultset
 *
 * @param rs    - Resultset handle
 * @param index - Column position
 * 
 * @note
 * Column position starts at 1.
 *
 * @return 
 * The column current row value or NULL if index is out of bounds
 * 
 */

OCI_EXPORT OCI_Date * OCI_API OCI_GetDate
(
    OCI_Resultset *rs,
    int index
);

/**
 * @brief 
 * Return the current date value of the column from its name
 * in the resultset
 *
 * @param rs    - Resultset handle
 * @param name  - Column name
 * 
 * @return 
 * The column current row value or NULL if no column found with the given name
 * 
 */

OCI_EXPORT OCI_Date * OCI_API OCI_GetDate2
(
    OCI_Resultset *rs,
    const mtext *name
);

/**
 * @brief 
 * Return the current timestamp value of the column at the given index 
 * in the resultset
 *
 * @param rs    - Resultset handle
 * @param index - Column position
 * 
 * @note
 * Column position starts at 1.
 *
 * @return 
 * The column current row value or NULL if index is out of bounds
 * 
 */

OCI_EXPORT OCI_Timestamp * OCI_API OCI_GetTimestamp
(
    OCI_Resultset *rs,
    int index
);

/**
 * @brief 
 * Return the current timestamp value of the column from its name
 * in the resultset
 *
 * @param rs    - Resultset handle
 * @param name  - Column name
 * 
 * @return 
 * The column current row value or NULL if no column found with the given name
 * 
 */

OCI_EXPORT OCI_Timestamp * OCI_API OCI_GetTimestamp2
(
    OCI_Resultset *rs,
    const mtext *name
);

/**
 * @brief 
 * Return the current interval value of the column at the given index 
 * in the resultset
 *
 * @param rs    - Resultset handle
 * @param index - Column position
 * 
 * @note
 * Column position starts at 1.
 *
 * @return 
 * The column current row value or NULL if index is out of bounds
 * 
 */

OCI_EXPORT OCI_Interval * OCI_API OCI_GetInterval
(
    OCI_Resultset *rs,
    int index
);

/**
 * @brief 
 * Return the current interval value of the column from its name
 * in the resultset
 *
 * @param rs    - Resultset handle
 * @param name  - Column name
 * 
 * @return 
 * The column current row value or NULL if no column found with the given name
 * 
 */

OCI_EXPORT OCI_Interval * OCI_API OCI_GetInterval2
(
    OCI_Resultset *rs,
    const mtext *name
);

/**
 * @brief 
 * Return the current cursor value (Nested table) of the column at the given 
 * index in the resultset
 *
 * @param rs    - Resultset handle
 * @param index - Column position
 * 
 * @note
 * Column position starts at 1.
 *
 * @return 
 * The column current row value or NULL if index is out of bounds
 * 
 */

OCI_EXPORT OCI_Statement * OCI_API OCI_GetStatement
(
    OCI_Resultset *rs,
    int index
);

/**
 * @brief 
 * Return the current cursor value (Nested table) of the column from its name
 * in the resultset
 *
 * @param rs    - Resultset handle
 * @param name  - Column name
 * 
 * @return 
 * The column current row value or NULL if no column found with the given name
 * 
 */

OCI_EXPORT OCI_Statement * OCI_API OCI_GetStatement2
(
    OCI_Resultset *rs,
    const mtext *name
);

/**
 * @brief 
 * Return the current lob value of the column at the given index 
 * in the resultset
 *
 * @param rs    - Resultset handle
 * @param index - Column position
 * 
 * @note
 * Column position starts at 1.
 *
 * @return 
 * The column current row value or NULL if index is out of bounds
 * 
 */

OCI_EXPORT OCI_Lob * OCI_API OCI_GetLob
(
    OCI_Resultset *rs,
    int index
);

/**
 * @brief 
 * Return the current lob value of the column from its name
 * in the resultset
 *
 * @param rs    - Resultset handle
 * @param name  - Column name
 * 
 * @return 
 * The column current row value or NULL if no column found with the given name
 * 
 */

OCI_EXPORT OCI_Lob * OCI_API OCI_GetLob2
(
    OCI_Resultset *rs,
    const mtext *name
);

/**
 * @brief 
 * Return the current File value of the column at the given index 
 * in the resultset
 *
 * @param rs    - Resultset handle
 * @param index - Column position
 * 
 * @note
 * Column position starts at 1.
 *
 * @return 
 * The column current row value or NULL if index is out of bounds
 * 
 */

OCI_EXPORT OCI_File * OCI_API OCI_GetFile
(
    OCI_Resultset *rs,
    int index
);

/**
 * @brief 
 * Return the current File value of the column from its name
 * in the resultset
 *
 * @param rs    - Resultset handle
 * @param name  - Column name
 * 
 * @return 
 * The column current row value or NULL if no column found with the given name
 * 
 */

OCI_EXPORT OCI_File * OCI_API OCI_GetFile2
(
    OCI_Resultset *rs,
    const mtext *name
);

/**
 * @brief 
 * Return the current Object value of the column at the given index 
 * in the resultset
 *
 * @param rs    - Resultset handle
 * @param index - Column position
 * 
 * @note
 * Column position starts at 1.
 *
 * @return 
 * The column current row value or NULL if index is out of bounds
 * 
 */

OCI_EXPORT OCI_Object * OCI_API OCI_GetObject
(
    OCI_Resultset *rs,
    int index
);

/**
 * @brief 
 * Return the current Object value of the column from its name
 * in the resultset
 *
 * @param rs    - Resultset handle
 * @param name  - Column name
 * 
 * @return 
 * The column current row value or NULL if no column found with the given name
 * 
 */

OCI_EXPORT OCI_Object * OCI_API OCI_GetObject2
(
    OCI_Resultset *rs,
    const mtext *name
);

/**
 * @brief 
 * Return the current Long value of the column at the given index 
 * in the resultset
 *
 * @param rs    - Resultset handle
 * @param index - Column position
 * 
 * @note
 * Column position starts at 1.
 *
 * @return 
 * The column current row value or NULL if index is out of bounds
 * 
 */

OCI_EXPORT OCI_Long * OCI_API OCI_GetLong
(
    OCI_Resultset *rs,
    int index
);

/**
 * @brief 
 * Return the current Long value of the column from its name
 * in the resultset
 *
 * @param rs    - Resultset handle
 * @param name  - Column name
 *
 * @return 
 * The column current row value or NULL if no column found with the given name
 * 
 */

OCI_EXPORT OCI_Long * OCI_API OCI_GetLong2
(
    OCI_Resultset *rs,
    const mtext *name
);

/**
 * @brief 
 * Check if the current row value is null for the column at the given index 
 * in the resultset
 *
 * @param rs    - Resultset handle
 * @param index - Column position
 * 
 * @note
 * Column position starts at 1.
 *
 * @return 
 * TRUE if it's null otherwise FALSE
 * 
 */

OCI_EXPORT boolean OCI_API OCI_IsNull
(
    OCI_Resultset *rs,
    int index
);

/**
 * @}
 */

/**
 * @defgroup g_ora_ret Oracle Returning feature
 * @{
 *
 * OCILIB supports the Oracle feature "Returning into" for DML statements.
 * 
 * Let's Oracle talk about this features :
 * 
 * @par
 * "Using the RETURNING clause with a DML statement allows you to essentially
 * combine two SQL statements into one, possibly saving you a server round-trip.
 * This is accomplished by adding an extra clause to the traditional UPDATE,
 * INSERT, and DELETE statements. The extra clause effectively adds a query to 
 * the DML statement. In the OCI, the values are returned to the application 
 * through the use of OUT bind variables."
 * 
 * OCILIB implements this features by providing a set of functions that allows 
 * to register output placeholders for the returned values.
 * Once the DML is executed with OCI_Execute(), the output returned data is 
 * available through a regular resultset object that can be fetched.
 * 
 * @note
 * Array binding interface is also supported with "returning into" DML statement.
 * Every iteration (or row of given arrays) generates an resultset object. 
 * Once a resulset is fetched, the next on can be retrieved with
 * OCI_GetNextResultset()
 *
 * @par
 *
 * @note
 * OCI_Long are not supported for "returning into" clause .This is a limitation 
 * imposed by Oracle.
 *
 * @par
 *
 * @note
 * OCI_Column objects retrieved from output OCI_Resultset have the following 
 * particularities:
 * 
 * - their names are the provided bind names to the DML statement
 *   (by example, ":out1"). So any call to the functions OCI_GetXXX2() 
 *   should be aware of it
 * - The columns detailed SQL attributes might be not all set or accurate. By 
 *   example, the scale and precision are not set, the SQL type is the one 
 *   choosen by OCILIB regarding the OCILIB object datatype and might be 
 *   slightly different from the real one.
 *
 * @par Example
 * @include returning.c
 *
 */

/**
 * @brief 
 * Retrieve the next resulset from an executed DML statement using a 
 * "SQL returning" clause
 *
 * @param stmt - Statement handle 
 * 
 * @note
 * SQL statements with a "returning" clause can return multiple resultsets.
 * When arrays of program variables are binded to the statment, Oracle will
 * execute the statement for every row (iteration). 
 * Each iteration generates a resultset that can be fetched like regular ones. 
 * 
 * @return
 * A resultset handle on success otherwise NULL
 *
 */

OCI_EXPORT OCI_Resultset * OCI_API OCI_GetNextResultset
(
    OCI_Statement *stmt
);

/**
 * @brief 
 * Register an short output bind placeholder
 *
 * @param stmt - Statement handle
 * @param name - Output bind name
 * 
 * @return 
 * TRUE on success otherwise FALSE
 *
 */

OCI_EXPORT boolean OCI_API OCI_RegisterShort
(
    OCI_Statement *stmt, 
    const mtext *name
);

/**
 * @brief 
 * Register an unsigned short output bind placeholder
 *
 * @param stmt - Statement handle
 * @param name - Output bind name
 * 
 * @return 
 * TRUE on success otherwise FALSE
 *
 */

OCI_EXPORT boolean OCI_API OCI_RegisterUnsignedShort
(
    OCI_Statement *stmt, 
    const mtext *name
);

/**
 * @brief 
 * Register an integer output bind placeholder
 *
 * @param stmt - Statement handle
 * @param name - Output bind name
 * 
 * @return 
 * TRUE on success otherwise FALSE
 *
 */

OCI_EXPORT boolean OCI_API OCI_RegisterInt
(
    OCI_Statement *stmt, 
    const mtext *name
);

/**
 * @brief 
 * Register an unsigned integer output bind placeholder
 *
 * @param stmt - Statement handle
 * @param name - Output bind name
 * 
 * @return 
 * TRUE on success otherwise FALSE
 *
 */

OCI_EXPORT boolean OCI_API OCI_RegisterUnsignedInt
(
    OCI_Statement *stmt, 
    const mtext *name
);

/**
 * @brief 
 * Register a big integer output bind placeholder
 *
 * @param stmt - Statement handle
 * @param name - Output bind name
 * 
 * @return 
 * TRUE on success otherwise FALSE
 *
 */

OCI_EXPORT boolean OCI_API OCI_RegisterBigInt
(
    OCI_Statement *stmt, 
    const mtext *name
);

/**
 * @brief 
 * Register an unsigned big integer output bind placeholder
 *
 * @param stmt - Statement handle
 * @param name - Output bind name
 * 
 * @return 
 * TRUE on success otherwise FALSE
 *
 */

OCI_EXPORT boolean OCI_API OCI_RegisterUnsignedBigInt
(
    OCI_Statement *stmt, 
    const mtext *name
);

/**
 * @brief 
 * Register a string output bind placeholder
 *
 * @param stmt - Statement handle
 * @param name - Output bind name
 * @param len  - Max length of single string (in characters)
 * 
 * @return 
 * TRUE on success otherwise FALSE
 *
 */

OCI_EXPORT boolean OCI_API OCI_RegisterString
(
    OCI_Statement *stmt, 
    const mtext *name,
    int len
);

/**
 * @brief 
 * Register an raw output bind placeholder
 *
 * @param stmt - Statement handle
 * @param name - Output bind name
 * @param len  - Max length of the buffer (in bytes)
 * 
 * @return 
 * TRUE on success otherwise FALSE
 */

OCI_EXPORT boolean OCI_API OCI_RegisterRaw
(
    OCI_Statement *stmt, 
    const mtext *name,
    int len
);

/**
 * @brief 
 * Register a double output bind placeholder
 *
 * @param stmt - Statement handle
 * @param name - Output bind name
 * 
 * @return 
 * TRUE on success otherwise FALSE
 */

OCI_EXPORT boolean OCI_API OCI_RegisterDouble
(
    OCI_Statement *stmt, 
    const mtext *name
);

/**
 * @brief 
 * Register a date output bind placeholder
 *
 * @param stmt - Statement handle
 * @param name - Output bind name
 * 
 * @return 
 * TRUE on success otherwise FALSE
 */

OCI_EXPORT boolean OCI_API OCI_RegisterDate
(
    OCI_Statement *stmt, 
    const mtext *name
);

/**
 * @brief 
 * Register a timestamp output bind placeholder
 *
 * @param stmt - Statement handle
 * @param name - Output bind name
 * @param type - Timestamp type
 * 
 * @note
 * See OCI_TimestampCreate() for possible values of parameter 'type'
 *
 * @return 
 * TRUE on success otherwise FALSE
 */

OCI_EXPORT boolean OCI_API OCI_RegisterTimestamp
(
    OCI_Statement *stmt, 
    const mtext *name, 
    int type
);

/**
 * @brief 
 * Register an interval output bind placeholder
 *
 * @param stmt - Statement handle
 * @param name - Output bind name
 * @param type - Interval type
 * 
 * @note
 * See OCI_IntervalCreate() for possible values of parameter 'type'
 *
 * @return 
 * TRUE on success otherwise FALSE
 */

OCI_EXPORT boolean OCI_API OCI_RegisterInterval
(
    OCI_Statement *stmt, 
    const mtext *name, 
    int type
);

/**
 * @brief 
 * Register an object output bind placeholder
 *
 * @param stmt   - Statement handle
 * @param name   - Output bind name
 * @param schema - Type schema handle
 *
 * @return 
 * TRUE on success otherwise FALSE
 */

OCI_EXPORT boolean OCI_API OCI_RegisterObject
(
    OCI_Statement *stmt, 
    const mtext *name, 
    OCI_Schema *schema
);

/**
 * @brief 
 * Register a lob output bind placeholder
 *
 * @param stmt - Statement handle
 * @param name - Output bind name
 * @param type - Lob type
 * 
 * @note
 * See OCI_LobCreate() for possible values of parameter 'type'
 *
 * @return 
 * TRUE on success otherwise FALSE
 */

OCI_EXPORT boolean OCI_API OCI_RegisterLob
(
    OCI_Statement *stmt, 
    const mtext *name,
    int type
);

/**
 * @brief 
 * Register a file output bind placeholder
 *
 * @param stmt - Statement handle
 * @param name - Output bind name
 * @param type - File type
 * 
 * @note
 * See OCI_FileCreate() for possible values of parameter 'type'
 *
 * @return 
 * TRUE on success otherwise FALSE
 */

OCI_EXPORT boolean OCI_API OCI_RegisterFile
(
    OCI_Statement *stmt, 
    const mtext *name, 
    int type
);

/**
 * @}
 */

/**
 * @defgroup g_rowid Oracle Rowids
 * @{
 *
 * OCILIB supports the Oracle ROWID type through C scalar string types (dtext).
 * 
 * - ROWIDs can be retrieved from resultset with OCI_GetString()
 * - ROWIDs can be binded to statements with OCI_BindString()
 *
 * The maximum size of an ROWID buffer is defined by the constant OCI_SIZE_ROWID
 *
 * @par Example
 * @include rowid.c
 *
 * @}
 */

/**
 * @defgroup g_stmt Statements control
 * @{
 *
 * Those functions give extra informations about OCILIB statements and can
 * modify their behavior.
 *
 */

/**
 * @brief 
 * Return the type of a SQL statement
 *
 * @param stmt - Statement handle
 *
 * @note
 * Possibles values are :
 *
 * - OCI_CST_SELECT  : select statement
 * - OCI_CST_UPDATE  : update statement 
 * - OCI_CST_DELETE  : delete statement
 * - OCI_CST_INSERT  : insert statement
 * - OCI_CST_CREATE  : create statement       
 * - OCI_CST_DROP    : drop statement
 * - OCI_CST_ALTER   : alter statement
 * - OCI_CST_BEGIN   : begin (pl/sql) statement
 * - OCI_CST_DECLARE : declare (pl/sql) statement  
 *
 * @return 
 * The statement type on success or OCI_CST_UNDEFINED on error
 * 
 */

OCI_EXPORT int OCI_API OCI_GetStatementType
(
    OCI_Statement *stmt
);

/**
 * @brief 
 * Set the binding mode of a SQL statement
 *
 * @param stmt - Statement handle
 * @param mode - binding mode value
 *
 * @note
 * Possibles values are :
 *
 *  - OCI_BIND_BY_POS  : position binding
 *  - OCI_BIND_BY_NAME : name binding
 *
 */

OCI_EXPORT boolean OCI_API OCI_SetBindMode
(
    OCI_Statement *stmt, int mode
);

/**
 * @brief 
 * Return the binding mode of a SQL statement
 *
 * @param stmt - Statement handle
 *
 * @note
 * See OCI_SetBindMode() for possible values
 * Default value is OCI_BIND_BY_NAME
 *
 */

OCI_EXPORT int OCI_API OCI_GetBindMode
(
    OCI_Statement *stmt
);

/**
 * @brief 
 * Set the number of rows fetched per internal server fetch call
 *
 * @param stmt - Statement handle
 * @param size - number of rows to fetch
 *
 * @return
 * TRUE on success otherwise FALSE
 *
 */

OCI_EXPORT boolean OCI_API OCI_SetFetchSize
(
    OCI_Statement *stmt, 
    int size
);

/**
 * @brief 
 * Return the number of rows fetched per internal server fetch call
 *
 * @note
 * Default value is set to constant OCI_FETCH_SIZE
 *
 * @param stmt - Statement handle
 *
 */

OCI_EXPORT int OCI_API OCI_GetFetchSize
(
    OCI_Statement *stmt
);

/**
 * @brief 
 * Set the number of rows prefetched by OCI Client 
 *
 * @param stmt - Statement handle
 * @param size - number of rows to fetch
 *
 * @note
 * To turn off prefetching, set both attributes (size and memory) to 0.
 *
 * @return
 * TRUE on success otherwise FALSE
 *
 */

OCI_EXPORT boolean OCI_API OCI_SetPrefetchSize
(
    OCI_Statement *stmt, 
    int size
);

/**
 * @brief 
 * Return the number of rows prefetched by OCI Client 
 *
 * @note
 * Default value is set to constant OCI_PREFETCH_SIZE
 *
 * @param stmt - Statement handle
 *
 */

OCI_EXPORT int OCI_API OCI_GetPrefetchSize
(
    OCI_Statement *stmt
);

/**
 * @brief 
 * Set the number of rows prefetched by OCI Client 
 *
 * @param stmt - Statement handle
 * @param size - amount of memory to fetch
 *
 * @note
 * Default value is 0 and the prefetch size attribute is used instead.
 * When both attributes are set (prefecth size and memory) and prefetch memory 
 * value can hold more rows than specified by prefecth size, OCI uses prefetch
 * size instead.
 *
 * @note
 * OCILIB set prefetch attribute to OCI_PREFETCH_SIZE when a statment is created.
 * To setup a big value for OCI_SetPrefetchMemory(), you must call 
 * OCI_SetPrefetchSize() to 0 to make OCI condiser this attribute.
 *
 * @return
 * TRUE on success otherwise FALSE
 *
 */

OCI_EXPORT boolean OCI_API OCI_SetPrefetchMemory
(
    OCI_Statement *stmt, 
    int size
);

/**
 * @brief 
 * Return the amount of memory used to retreive rows prefetched by OCI Client 
 *
 * @param stmt - Statement handle
 *
 * @note
 * Default value is 0 
 *
 */

OCI_EXPORT int OCI_API OCI_GetPrefetchMemory
(
    OCI_Statement *stmt
);

/**
 * @brief 
 * Set the LONG datatype piece buffer size
 *
 * @param stmt - Statement handle
 * @param size - maximum size for long buffer
 *
 * @return
 * TRUE on success otherwise FALSE
 *
 */

OCI_EXPORT boolean OCI_API OCI_SetLongMaxSize
(
    OCI_Statement *stmt,
    int size
);

/**
 * @brief 
 * Return the LONG datatype piece buffer size
 *
 * @note
 * Default value is set to constant OCI_SIZE_LONG
 *
 * @param stmt - Statement handle
 *
 */

OCI_EXPORT int OCI_API OCI_GetLongMaxSize
(
    OCI_Statement *stmt
);

/**
 * @brief 
 * Set the long datatype handling mode of a SQL statement
 *
 * @param stmt - Statement handle
 * @param mode - binding mode value
 *
 * @note
 * Possibles values are :
 *
 * - OCI_LONG_EXPLICIT : LONGs are explicitly handled by OCI_Long type
 * - OCI_LONG_IMPLICIT : LONGs are implicitly mapped to string type in the
 *   limits of VARCHAR2 size capacity
 *
 *  LONG RAWs can't be handled with OCI_LONG_IMPLICIT
 */

OCI_EXPORT boolean OCI_API OCI_SetLongMode
(
    OCI_Statement *stmt,
    int mode
);

/**
 * @brief 
 * Return the long datatype handling mode of a SQL statement
 *
 * @param stmt - Statement handle
 *
 * @note
 *  See OCI_SetLongMode() for possible values
 *
 */

OCI_EXPORT int OCI_API OCI_GetLongMode
(
    OCI_Statement *stmt
);

/**
 * @brief 
 * Set the date format for implicit string / date conversions
 *
 * @param stmt   - Statement handle
 * @param format - Date format
 *
 * @note
 * Possible values are the string date format supported by Oracle.
 * See documentation of Oracle SQL to_date() function for more details
 *
 */
 
OCI_EXPORT boolean OCI_API OCI_SetFormatDate
(
    OCI_Statement *stmt, 
    const mtext *format
);

/**
 * @brief 
 * Return the current date format for implicit string / date conversions
 *
 * @param stmt - Statement handle
 *
 * @note
 *  See OCI_SetFormatDate() for possible values
 *
 */

OCI_EXPORT const mtext * OCI_API OCI_GetFormatDate
(
    OCI_Statement *stmt
);

/**
 * @}
 */

/**
 * @defgroup g_lob Internal Large Objects (LOBs)
 * @{
 *
 * Large Objects (LOBs) were introduced with Oracle 8i to replace LONGs
 * 
 * Oracle OCI supplies a set APIs to manipulate this datatype.
 *
 * OCILIB encapsulates this API by supplying :
 * 
 * - An OCI_Lob C type 
 * - A set of really easy APIs to manipulate OCI_Lob objects
 *
 * OCIB currently supports 3 types of Lobs :
 * 
 * - BLOB  : Binary LOBs (replacement for LONG RAW datatype)
 * - CLOB  : Character LOBs (replacement for LONG datatype)
 * - NCLOB : National Character LOBs
 *
 * OCI_Lob objects can be :
 *
 * - Created as standalone instances
 * - Used for in/out binding
 * - Retrieved from select statements
 * - Manipulated (copy, append, ...)
 *
 * @par Lobs > 4 Go
 *
 * Oracle 10g extended lobs by increasing maximum size from 4Go to 128 To.
 *
 * OCILIB, with version 2.1.0, supports now this new limit.
 * For Handling sizes and offsets up to 128 To, 64 bit integers are requested.
 *
 * So, A new scalar integer type has been introduced  : big_uint (olderly lobsize_t).
 * This type can be a 32 bits or 64 bits integer depending on :
 * - Compiler support for 64 bits integers (C99 compiler, MS compilers)
 * - Oracle client version
 * 
 * big_uint will be a 64 bits integer :
 * - if the compiler supports it
 * - if OCILIB is build with option OCI_IMPORT_LINKAGE and the Oracle version is >= 10.1
 * - or OCILIB is build with option OCI_IMPORT_RUNTIME (oracle version is not known at compilation stage)
 *
 * @par Example
 * @include lob.c
 *
 */

/**
 * @brief 
 * Create a local temporary Lob instance
 *
 * @param con  - Connection handle
 * @param type - Lob type
 *
 * Supported lob types :
 * 
 * - OCI_BLOB  : Binary Lob
 * - OCI_CLOB  : Character Lob 
 * - OCI_NCLOB ! National Character Lob
 * 
 * @return 
 * Return the lob handle on success otherwise NULL on failure
 *
 */

OCI_EXPORT OCI_Lob * OCI_API OCI_LobCreate
(
    OCI_Connection *con, 
    int type
);

/**
 * @brief 
 * Free a local temporary lob
 *
 * @param lob - Lob handle
 *
 * @warning
 * Only lobs created with OCI_LobCreate() should be freed by OCI_LobFree()
 *
 * @return 
 * TRUE on success otherwise FALSE
 * 
 */

OCI_EXPORT boolean OCI_API OCI_LobFree
(
    OCI_Lob *lob
);

/**
 * @brief 
 * Return the type of the given Lob object
 *
 * @param lob - Lob handle
 *
 * @note
 * For possibles values, see OCI_LobCreate()
 *
 * @return
 * Object type or OCI_UNKNOWN the input handle is NULL
 *
 */

OCI_EXPORT int OCI_API OCI_LobGetType
(
    OCI_Lob *lob
);

/**
 * @brief 
 * Perfom a seek operation on the OCI_lob content buffer
 *
 * @param lob    - Lob handle
 * @param offset - Offset from current position (bytes or characters)
 * @param mode   - Seek mode
 *
 * Parameter 'mode' can be one of the following value :
 *
 * - OCI_SEEK_SET : set the lob current offset to the given absolute offset
 * - OCI_SEEK_END : set the lob current offset to the end of the lob 
 * - OCI_SEEK_CUR : move the lob current offset to the number of bytes or
 *                  characters given by parameter 'offset' 
 *
 * @note
 * - For CLOB and CLOB, offset in in characters 
 * - For BLOB and BFILE, offset is in bytes
 *
 * @return 
 * TRUE on success otherwise FALSE
 * 
 */

OCI_EXPORT boolean OCI_API OCI_LobSeek
(
    OCI_Lob *lob, 
    big_uint offset, 
    int mode
); 

/**
 * @brief 
 * Return the current position in the Lob content buffer
 *
 * @param lob - Lob handle
 * 
 * @return 
 * Lob position (starting with 0) or 0 on failure
 */

OCI_EXPORT big_uint OCI_API OCI_LobGetOffset
(
    OCI_Lob *lob
);

/**
 * @brief 
 * Read a portion of a lob into the given buffer
 *
 * @param lob    - Lob handle
 * @param buffer - Pointer to a buffer
 * @param len    - Length of the buffer (in bytes or characters)
 * 
 * @note
 * Length is expressed in :
 * - Bytes for BLOBs
 * - Characters for CLOBs/NCLOBS
 * 
 * @return 
 * Number of bytes/characters read on success otherwise 0 on failure
 * 
 */

OCI_EXPORT unsigned int OCI_API OCI_LobRead
(
    OCI_Lob *lob, 
    void *buffer,
    unsigned int len
);

/**
 * @brief 
 * Write a buffer into a LOB
 *
 * @param lob    - Lob handle
 * @param buffer - Pointer to a buffer
 * @param len    - Length of the buffer (in bytes or characters)
 * 
 * @note
 * Length is expressed in :
 * - Bytes for BLOBs
 * - Characters for CLOBs/NCLOBs
 * 
 * @return 
 * Number of bytes / characters written on success otherwise 0 on failure
 * 
 */

OCI_EXPORT unsigned int OCI_API OCI_LobWrite
(
    OCI_Lob *lob, 
    void *buffer,
    unsigned int len
);

/**
 * @brief 
 * Truncate the given lob to a shorter length
 *
 * @param lob  - Lob handle
 * @param size - New lenght (in bytes or characters)
 * 
 * @note
 * Length is expressed in :
 * - Bytes for BLOBs
 * - Characters for CLOBs/NCLOBs
 * 
 * 
 * @return 
 * TRUE on success otherwise FALSE
 *
 */

OCI_EXPORT boolean OCI_API OCI_LobTruncate
(
    OCI_Lob *lob, 
    big_uint size
);

/**
 * @brief 
 * Return the actual lenght of a lob
 *
 * @param lob - Lob handle
 *
 * @note
 * The returned value is in bytes for BLOBS and characters for CLOBS/NCLOBs
 * 
 */

OCI_EXPORT big_uint OCI_API OCI_LobGetLength
(
    OCI_Lob *lob
);

/**
 * @brief 
 * Erase a portion of the lob at a given position
 *
 * @param lob    - Lob handle
 * @param offset - Absolute position in source lob
 * @param len    - Number of bytes or characters to erase
 * 
 * @note
 * Absolute position start at 1.
 *
 * @return 
 * Number of bytes (BLOB) or characters (CLOB/NCLOB) erased on success 
 * otherwise 0 on failure
 *
 */

OCI_EXPORT big_uint OCI_API OCI_LobErase
(
    OCI_Lob *lob,
    big_uint offset,
    big_uint len
);

/**
 * @brief 
 * Append a buffer at the end of a LOB
 *
 * @param lob    - Lob handle
 * @param buffer - Pointer to a buffer
 * @param len    - Length of the buffer (in bytes or characters)
 * 
 * @note
 * Length is expressed in :
 * - Bytes for BLOBs
 * - Characters for CLOBs
 * 
 * @return 
 * Number of bytes / characters written on success otherwise 0 on failure
 * 
 */

OCI_EXPORT unsigned int OCI_API OCI_LobAppend
(
    OCI_Lob *lob, 
    void *buffer,
    unsigned int len
);

/**
 * @brief 
 * Append a source LOB at the end of a destination LOB 
 *
 * @param lob        - Destination Lob handle
 * @param lob_src    - Source Lob handle
 * 
 * @return 
 * TRUE on success otherwise FALSE
 *
 */

OCI_EXPORT boolean OCI_API OCI_LobAppendLob
(
    OCI_Lob *lob, 
    OCI_Lob *lob_src
);

/**
 * @brief 
 * Check if the given lob is a temporary lob
 * 
 * @param lob - Lob handle
 * 
 * @return 
 * TRUE if it's a temporary lob otherwise FALSE
 *
 */

OCI_EXPORT boolean OCI_API OCI_LobIsTemporary
(
    OCI_Lob *lob
);

/**
 * @brief 
 * Copy a portion of a source LOB into a destination LOB 
 *
 * @param lob        - Destination Lob handle
 * @param lob_src    - Source Lob handle
 * @param offset_dst - Absolute position in destination lob
 * @param offset_src - Absolute position in source lob
 * @param count      - Number of bytes or character to copy
 * 
 * @note
 * For character LOB (CLOB/NCLOBS) the parameters count, offset_dst and 
 * offset_src are expressed in characters and not in bytes.
 *
 * @note
 * Absolute position start at 1.
 * 
 */

OCI_EXPORT boolean OCI_API OCI_LobCopy
(
    OCI_Lob *lob,
    OCI_Lob *lob_src, 
    big_uint offset_dst,
    big_uint offset_src,
    big_uint count
);

/**
 * @brief 
 * Copy a portion of a source FILE into a destination LOB 
 *
 * @param lob        - Destination Lob handle
 * @param file       - Source File handle
 * @param offset_dst - Absolute position in destination lob
 * @param offset_src - Absolute position in source file
 * @param count      - Number of bytes to copy
 * 
 * @note
 * - For character LOB (CLOB/NCLOB) the parameter offset_src are expressed in 
 *   characters and not in bytes. 
 * - Offset_src is always in bytes
 *
 * @note
 * Absolute position start at 1.
 * 
 */

OCI_EXPORT boolean OCI_API OCI_LobCopyFromFile
(
    OCI_Lob *lob,
    OCI_File *file, 
    big_uint offset_dst,
    big_uint offset_src,
    big_uint count
);

/**
 * @brief 
 * Open explicitly a Lob
 * 
 * @param lob  - Lob handle
 * @param mode - open mode 
 * 
 * Possible values for mode are :
 * 
 * - OCI_LOB_READONLY  : read onluy access 
 * - OCI_LOB_READWRITE : read/write access
 *
 * @note
 * - A call to OCI_LobOpen is not necessary to manipulate a Lob. 
 * - If a lob hasn't been opened explicitly,  triggers are fired and
 *   indexes updated at every read/write/append operation
 *
 * @return 
 * TRUE on success otherwise FALSE
 *
 */

OCI_EXPORT boolean OCI_API OCI_LobOpen
(
    OCI_Lob *lob,
    int mode
);

/**
 * @brief 
 * Close explicitly a Lob
 * 
 * @param lob - Lob handle
 * 
 * @note
 * - A call to OCI_LobClose is not necessary to manipulate a Lob. 
 *
 * @return 
 * TRUE on success otherwise FALSE
 *
 */

OCI_EXPORT boolean OCI_API OCI_LobClose
(
    OCI_Lob *lob
);

/**
 * @brief 
 * Compare two lob handles for equality
 * 
 * @param lob  - Lob handle
 * @param lob2 - Lob2 handle
 * 
 * @note
 *
 * @return 
 * TRUE is the lobs are not null and equal otherwise FALSE
 *
 */

OCI_EXPORT boolean OCI_API OCI_LobIsEqual
(
    OCI_Lob *lob,
    OCI_Lob *lob2
);

/**
 * @brief 
 * Assign a lob to another one
 * 
 * @param lob     - Destination Lob handle
 * @param lob_src - Source Lob handle
 *
 * @return 
 * TRUE on success otherwise FALSE
 *
 */

OCI_EXPORT boolean OCI_API OCI_LobAssign
(
    OCI_Lob *lob,
    OCI_Lob *lob_src
);

/**
 * @}
 */

/**
 * @defgroup g_file External Large Objects (FILEs)
 * @{
 *
 * External Large Objects (FILEs) were introduced with Oracle 8i
 * 
 * Oracle OCI supplies a set APIs to manipulate this datatype.
 *
 * OCILIB encapsulates this API by supplying :
 * 
 * - An OCI_File C type 
 * - A set of really easy APIs to manipulate OCI_File objects
 *
 * OCIB currently supports 2 types of Lobs :
 * 
 * - BFILE : Binary files
 * - CFILE : Character files
 *
 * @warning
 * FILEs are readonly.
 *
 * OCI_Lob objects can be :
 *
 * - Created as standalone instances
 * - Used for in/out binding
 * - Retrieved from select statements
 * - Used for reading server files content
 * 
 * @par Files > 4 Go
 *
 * - New maximum file size limit (128 To) applies to OCI_Files objects.
 * - See Internal Large Objects (LOBs) section for Files > 4 Go information
 *
 * @par Example
 * @include file.c
 *
 */

/**
 * @brief 
 * Create a file object instance
 *
 * @param con  - Connection handle
 * @param type - File type
 *
 * Supported file types :
 * 
 * - OCI_BFILE : Binary file 
 * - OCI_CFILE : Character file 
 * 
 * @return 
 * Return the lob handle on success otherwise NULL on failure
 *
 */

OCI_EXPORT OCI_File * OCI_API OCI_FileCreate
(
    OCI_Connection *con, 
    int type
);

/**
 * @brief 
 * Free a local File object
 *
 * @param file - File handle
 *
 * @warning
 * Only Files created with OCI_FileCreate() should be freed by OCI_FileFree()
 *
 * @return 
 * TRUE on success otherwise FALSE
 * 
 */

OCI_EXPORT boolean OCI_API OCI_FileFree
(
    OCI_File *file
);

/**
 * @brief 
 * Return the type of the given File object
 *
 * @param file - File handle
 *
 * @note
 * For possibles values, see OCI_FileCreate()
 *
 * @return
 * Object type or OCI_UNKNOWN the input handle is NULL
 *
 */

OCI_EXPORT int OCI_API OCI_FileGetType
(
    OCI_File *file
);

/**
 * @brief 
 * Perfom a seek operation on the OCI_File content buffer
 *
 * @param file    - File handle
 * @param offset  - Offset from current position
 * @param mode    - Seek mode
 *
 * Mode parameter can be one of the following value :
 *
 * - OCI_SEEK_SET : set the file current offset to the given absolute offset
 * - OCI_SEEK_END : set the file current offset to the end of the lob 
 * - OCI_SEEK_CUR : move the file current offset to the number of bytes given by
 *                  parameter 'offset' 
 *
 * @return 
 * TRUE on success otherwise FALSE
 * 
 */

OCI_EXPORT boolean OCI_API OCI_FileSeek
(
    OCI_File *file, 
    big_uint offset, 
    int mode
); 

/**
 * @brief 
 * Return the current position in the file
 *
 * @param file - File handle
 * 
 * @return 
 * File position (starting with 0) or 0 on failure
 */

OCI_EXPORT big_uint OCI_API OCI_FileGetOffset
(
    OCI_File *file
);

/**
 * @brief 
 * Read a portion of a file into the given buffer
 *
 * @param file   - File handle
 * @param buffer - Pointer to a buffer
 * @param len    - Length of the buffer in bytes
 * 
 * @return 
 * Number of bytes read on success otherwise 0 on failure
 * 
 */

OCI_EXPORT unsigned int OCI_API OCI_FileRead
(
    OCI_File *file, 
    void *buffer,
    unsigned int len
);

/**
 * @brief 
 * Return the size in bytes of a file
 *
 * @param file - File handle
 * 
 */

OCI_EXPORT big_uint OCI_API OCI_FileGetSize
(
    OCI_File *file
);

/**
 * @brief 
 * Check if the given file exists on server
 *
 * @param file - File handle
 *
 * @note
 * for local FILEs object, OCI_LobFileSetName() must be called before to set
 * the filename to check
 * 
 * @return
 * TRUE on success otherwise FALSE
 *
 */

OCI_EXPORT boolean OCI_API OCI_FileExists
(
   OCI_File *file
);

/**
 * @brief 
 * Set the directory and file name of FILE handle
 *
 * @param file  - File handle
 * @param dir   - File directory
 * @param name  - File name
 *
 * @note
 * - For local FILEs only
 * - Files fetched from resultset can't be assigned a new directory and name
 * 
 * @return
 * TRUE on success otherwise FALSE
 *
 */

OCI_EXPORT boolean OCI_API OCI_FileSetName
(
    OCI_File *file,
    const mtext *dir,
    const mtext *name
);

/**
 * @brief 
 * Return the directory of the given file
 *
 * @param file  - File handle
 *
 */

OCI_EXPORT const mtext * OCI_API OCI_FileGetDirectory
(
    OCI_File *file
);

/**
 * @brief 
 * Return the name of the given file
 *
 * @param file  - File handle
 *
 */

OCI_EXPORT const mtext * OCI_API OCI_FileGetName
(
    OCI_File *file
);

/**
 * @brief 
 * Open a file for reading
 * 
 * @param file  - File handle
 *
 * @return 
 * TRUE on success otherwise FALSE
 *
 */

OCI_EXPORT boolean OCI_API OCI_FileOpen
(
    OCI_File *file
);

/**
 * @brief 
 * Check if the specified file is opened within the file handle
 * 
 * @param file  - File handle
 *
 * @return 
 * TRUE if the file was opened with this handle otherwise FALSE
 *
 */

OCI_EXPORT boolean OCI_API OCI_FileIsOpen
(
    OCI_File *file
);
/**
 * @brief 
 * Close a file
 * 
 * @param file  - File handle
 *
 * @return 
 * TRUE on success otherwise FALSE
 *
 */

OCI_EXPORT boolean OCI_API OCI_FileClose
(
    OCI_File *file
);

/**
 * @brief 
 * Compare two file handle for equality
 * 
 * @param file  - File handle
 * @param file2 - File2 handle
 * 
 * @note
 *
 * @return 
 * TRUE is the lobs are not null and equal otherwise FALSE
 *
 */

OCI_EXPORT boolean OCI_API OCI_FileIsEqual
(
    OCI_File *file,
    OCI_File *file2
);

/**
 * @brief 
 * Assign a file to another one
 * 
 * @param file     - Destination File handle
 * @param file_src - Source File handle
 *
 * @return 
 * TRUE on success otherwise FALSE
 *
 */

OCI_EXPORT boolean OCI_API OCI_FileAssign
(
    OCI_File *file,
    OCI_File *file_src
);

/**
 * @}
 */

/**
 * @defgroup g_long Long objects
 * @{
 *
 * Long Objects encapsulate Oracle LONGs datatypes and were used to store large
 * buffers in Oracle database.
 * 
 * They're still supported but are depreciated. Oracle now provides a 
 * newer and better way to deal with data that needs large storage : LOBs
 *
 * OCILIB supports this datatype because it was and still is widely used 
 *
 * OCILIB provides a set of API for manipulating LONGs that is really close to 
 * the one provided for LOBs.
 *
 * OCIB currently supports 3 types of Long Objects :
 * 
 * - OCI_BLONG : LONG RAW columns
 * - OCI_CLONG : LONG columns
 *
 * OCI_Lob objects can be :
 *
 * - Created as standalone instances
 * - Used for in/out binding
 * - Retrieved from select statement 
 *
 * @par Example
 * @include long.c
 *
 */

/**
 * @brief 
 * Create a local temporary Long instance
 *
 * @param stmt - Statement handle
 * @param type - Long type
 *
 * Supported lob types :
 * 
 * - OCI_BLONG : Binary Long
 * - OCI_CLONG : Character Long 
 * 
 * @return 
 * Return the long handle on success otherwise NULL on failure
 *
 */

OCI_EXPORT OCI_Long * OCI_API OCI_LongCreate
(
    OCI_Statement *stmt, 
    int type
);

/**
 * @brief 
 * Free a local temporary long
 *
 * @param lg - Long handle
 *
 * @warning
 * Only lobs created with OCI_LongCreate() should be freed by OCI_LongFree()
 *
 * @return 
 * TRUE on success otherwise FALSE
 * 
 */

OCI_EXPORT boolean OCI_API OCI_LongFree
(
    OCI_Long *lg
);

/**
 * @brief 
 * Return the type of the given Long object
 *
 * @param lg - Long handle
 *
 * @note
 * For possibles values, see OCI_LobCreate()
 *
 * @return
 * Object type or OCI_UNKNOWN the input handle is NULL
 *
 */

OCI_EXPORT int OCI_API OCI_LongGetType
(
    OCI_Long *lg
);

/**
 * @brief 
 * Read a portion of a long into the given buffer [Obsolete]
 *
 * @param lg     - Long handle
 * @param buffer - Pointer to a buffer
 * @param len    - Length of the buffer in bytes / characters
 * 
 * @note
 * - From version 2.0.0, this function is obsolete because OCILIB fetches now
 *   all data during OCIFetchNext() call
 * - So, this call reads now the internal OCI_Long object allocated buffer
 * - The internal buffer can be directly accessed with OCI_LongGetBuffer()
 *
 * @note
 * - For OCI_CLONG, parameter 'len' and returned value are expressed in characters 
 * - For OCI_BLONG, parameter 'len' and returned value are expressed in bytes
 * 
 * @return 
 * - Number of bytes/characters read on success
 * - 0 if there is nothing more to read
 * - 0 on failure
 * 
 */

OCI_EXPORT unsigned int OCI_API OCI_LongRead
(
    OCI_Long *lg, 
    void *buffer, 
    unsigned int len
);

/**
 * @brief 
 * Write a buffer into a Long
 *
 * @param lg     - Long handle
 * @param buffer - the pointer to a buffer
 * @param len    - the length of the buffer in bytes (OCI_BLONG) or
 *                  character (OCI_CLONG)
 * 
 * @return 
 * Number of bytes (OCI_BLONG) / character (OCI_CLONG) written on success
 * - 0 if there is nothing more to read
 * - 0 on failure
 * 
 */

OCI_EXPORT unsigned int OCI_API OCI_LongWrite
(
    OCI_Long *lg, 
    void *buffer, 
    unsigned int len
);

/**
 * @brief 
 * Return the buffer size of a long object in bytes (OCI_BLONG) or
 * character (OCI_CLONG)
 *
 * @param lg - Long handle
 * 
 */

OCI_EXPORT unsigned int OCI_API OCI_LongGetSize
(
    OCI_Long *lg
);

/**
 * @brief 
 * Return the internal buffer of an OCI_Long object read from a fetch sequence
 *
 * @param lg - Long handle
 * 
 */

OCI_EXPORT void * OCI_API OCI_LongGetBuffer
(
    OCI_Long *lg
);


/**
 * @}
 */

/**
 * @defgroup g_date Date/time manipulation
 * @{
 *
 * OCILIB encapsulates Oracle SQL Date datatype within OCI_Date structure 
 * 
 * Basically, the OCI_Date routines are wrappers around the Oracle OCIDate APIs
 *
 * @par Example
 * @include date.c
 *
 */

/**
 * @brief 
 * Create a local date object
 *
 * @param con - Connection handle
 * 
 * @note
 * From version 2.5.0, parameter 'con' can be NULL in order to manipulate dates
 * independently from database connections
 *
 * @return 
 * Return the date handle on success otherwise NULL on failure
 *
 */

OCI_EXPORT OCI_Date * OCI_API OCI_DateCreate
(
    OCI_Connection *con
); 

/**
 * @brief 
 * Free an OCI_Date handle
 *
 * @param date - Date handle
 *
 * @warning
 * Only dates created with OCI_DateCreate() should be freed by OCI_DateFree()
 *
 * @return 
 * TRUE on success otherwise FALSE
 * 
 */

OCI_EXPORT boolean OCI_API OCI_DateFree
(
    OCI_Date *date
);

/**
 * @brief 
 * Add or subtract days to a date handle
 *
 * @param date - Date handle
 * @param nb   - Number of days to add/remove
 * 
 * @return 
 * TRUE on success otherwise FALSE
 *
 */

OCI_EXPORT boolean OCI_API OCI_DateAddDays
(
    OCI_Date *date, 
    int nb
);

/**
 * @brief 
 * Add or subtract months to a date handle
 *
 * @param date - Date handle
 * @param nb   - Number of months to add/remove
 * 
 * @return 
 * TRUE on success otherwise FALSE
 *
 */

OCI_EXPORT boolean OCI_API OCI_DateAddMonths
(
    OCI_Date *date, 
    int nb
);

/**
 * @brief 
 * Assign the value of a date handle to another one
 *
 * @param date  - Destination Date handle
 * @param date2 - Source Date handle
 * 
 * @return 
 * TRUE on success otherwise FALSE
 * 
 */

OCI_EXPORT int OCI_API OCI_DateAssign
(
    OCI_Date *date, 
    OCI_Date *date2
);

/**
 * @brief 
 * Check if the given date is valid
 *
 * @param date - Date handle
 * 
 * @return 
 * - Zero if date is valid 
 * - Any other value means the date is invalid
 *
 */

OCI_EXPORT int OCI_API OCI_DateCheck
(
    OCI_Date *date
);

/**
 * @brief 
 * Compares two date handles
 *
 * @param date  - Date1 handle
 * @param date2 - Date2 handle
 * 
 * @return 
 * - -1 if date1 is smaller than date2,
 * -  0 if they are equal
 * -  1 if date1 is greater than date2.
 *
 */

OCI_EXPORT int OCI_API OCI_DateCompare
(
    OCI_Date *date, 
    OCI_Date *date2
);

/**
 * @brief 
 * Return the number of days betWeen two dates
 *
 * @param date  - Date1 handle
 * @param date2 - Date2 handle
 * 
 * @return 
 * Number of days on success otherwise OCI_ERROR on failure
 *
 */

OCI_EXPORT int OCI_API OCI_DateDaysBetween
(
    OCI_Date *date, 
    OCI_Date *date2
);

/**
 * @brief 
 * Convert a string to a date and store it in the given date handle
 *
 * @param date - Destination Date handle
 * @param str  - Source date string
 * @param fmt  - Date format
 * 
 * @return 
 * TRUE on success otherwise FALSE
 * 
 */

OCI_EXPORT boolean OCI_API OCI_DateFromText
(
    OCI_Date *date, 
    const mtext *str,
    const mtext *fmt
);

/**
 * @brief 
 * Convert a Date value from the given date handle to a string
 *
 * @param date - source Date handle
 * @param fmt  - Date format
 * @param size - Destination string size in characters
 * @param str  - Destination date string
 * 
 * @return 
 * TRUE on success otherwise FALSE
 * 
 */

OCI_EXPORT boolean OCI_API OCI_DateToText
(
    OCI_Date *date, 
    const mtext *fmt, 
    int size,
    mtext *str
);

/**
 * @brief 
 * Extract the date part from a date handle
 *
 * @param date  - Date handle
 * @param year  - Place holder for year value
 * @param month - Place holder for month value
 * @param day   - Place holder for day value
 * 
 * @return 
 * TRUE on success otherwise FALSE
 * 
 */

OCI_EXPORT boolean OCI_API OCI_DateGetDate
(
    OCI_Date *date, 
    int *year, 
    int *month,
    int *day
);

/**
 * @brief 
 * Extract the time part from a date handle
 *
 * @param date  - Date handle
 * @param hour  - Place holder for hour value
 * @param min   - Place holder for minute value
 * @param sec   - Place holder for second value
 * 
 * @return 
 * TRUE on success otherwise FALSE
 * 
 */

OCI_EXPORT boolean OCI_API OCI_DateGetTime
(
    OCI_Date *date, 
    int *hour, 
    int *min,
    int *sec
);

/**
 * @brief 
 * Extract the date and time parts from a date handle
 *
 * @param date  - Date handle
 * @param year  - Place holder for year value
 * @param month - Place holder for month value
 * @param day   - Place holder for day value
 * @param hour  - Place holder for hour value
 * @param min   - Place holder for minute value
 * @param sec   - Place holder for second value
 * 
 * @return 
 * TRUE on success otherwise FALSE
 * 
 */

OCI_EXPORT boolean OCI_API OCI_DateGetDateTime
(
    OCI_Date *date, 
    int *year, 
    int *month,
    int *day,
    int *hour, 
    int *min,
    int *sec
);

/**
 * @brief 
 * Set the date portion if the given date handle
 *
 * @param date  - Date handle
 * @param year  - Year value
 * @param month - Month value
 * @param day   - Day value
 * 
 * @return 
 * TRUE on success otherwise FALSE
 * 
 */

OCI_EXPORT boolean OCI_API OCI_DateSetDate
(
    OCI_Date *date, 
    int year, 
    int month,
    int day
);

/**
 * @brief 
 * Set the time portion if the given date handle
 *
 * @param date  - Date handle
 * @param hour  - Hour value
 * @param min   - Minute value
 * @param sec   - Second value
 * 
 * @return 
 * TRUE on success otherwise FALSE
 * 
 */

OCI_EXPORT boolean OCI_API OCI_DateSetTime
(
    OCI_Date *date, 
    int hour, 
    int min,
    int sec
);

/**
 * @brief 
 * Set the date and time portions if the given date handle
 *
 * @param date  - Date handle
 * @param year  - Year value
 * @param month - Month value
 * @param day   - Day value
 * @param hour  - Hour value
 * @param min   - Minute value
 * @param sec   - Second value
 * 
 * @return 
 * TRUE on success otherwise FALSE
 * 
 */

OCI_EXPORT boolean OCI_API OCI_DateSetDateTime
(
    OCI_Date *date, 
    int year, 
    int month,
    int day,
    int hour, 
    int min,
    int sec
);

/**
 * @brief 
 * Place the last day of month (from the given date) into the given date
 *
 * @param date  - Date handle
 * 
 * @return 
 * TRUE on success otherwise FALSE
 * 
 */

OCI_EXPORT boolean OCI_API OCI_DateLastDay
(
    OCI_Date *date
);

/**
 * @brief 
 * Gets the date of next day of the week, after a given date
 *
 * @param date  - Date handle
 * @param day   - Day of the week
 * 
 * @return 
 * TRUE on success otherwise FALSE
 * 
 */

OCI_EXPORT boolean OCI_API OCI_DateNextDay
(
    OCI_Date *date, 
    const mtext *day
);

/**
 * @brief 
 * Return the current system date/time into the date handle
 *
 * @param date  - Date handle
 * 
 * @return 
 * TRUE on success otherwise FALSE
 * 
 */

OCI_EXPORT boolean OCI_API OCI_DateSysDate
(
    OCI_Date *date
);

/**
 * @brief 
 * Convert a date from one zone to another zone
 *
 * @param date  - Date handle
 * @param zone1 - Source zone
 * @param zone2 - Destination zone
 * 
 * @return 
 * TRUE on success otherwise FALSE
 * 
 */

OCI_EXPORT boolean OCI_API OCI_DateZoneToZone
(
    OCI_Date *date, 
    const mtext *zone1,
    const mtext *zone2
);

/**
 * @brief 
 * Affect an OCI_Date handle value to ISO C time datatypes
 *
 * @param date  - Date handle
 * @param ptm   - Pointer to a structure tm to receive date/time values
 * @param pt    - Pointer to a time_t to hold the date/time in the time_t format
 * 
 * @note
 * Both parameters 'ptm' and 'p' are optionnal but one of them has to be provided.
 * 
 * @return 
 * TRUE on success otherwise FALSE
 * 
 */

OCI_EXPORT boolean OCI_API OCI_DateToCTime
(
    OCI_Date *date,    
    struct tm *ptm,
    time_t *pt
);

/**
 * @brief 
 * Affect ISO C time datatypes values to an OCI_Date handle 
 *
 * @param date  - Date handle
 * @param ptm   - Pointer to a structure tm that hold the date/time value
 * @param t     - Value (time_t) that hold the date/time in the time_t format
 * 
 * @note
 *
 * Both parameters 'ptm' and 'p' are optionnal but one of them has to be provided.
 * If 'ptm' is not null, its value is affected to the OCI_Timestamp handle, 
 * otherwise the value of 't' is used.
 *
 * @return 
 * TRUE on success otherwise FALSE
 * 
 */

OCI_EXPORT boolean OCI_API OCI_DateFromCTime
(
    OCI_Date *date,    
    struct tm *ptm,
    time_t t
);

/**
 * @}
 */

/**
 * @defgroup g_timestamp Timestamps and intervals manipulation
 * @{
 *
 * OCILIB encapsulates Oracle  :
 * 
 * - SQL timestamp datatype within OCI_Timestamp structure
 * - SQL interval  datatype within OCI_Interval  structure
 * 
 * Basically, the OCI_Timestamp and OCI_Interval routines are wrappers around
 *  the Oracle OCIDatetime and OCIInterval APIs
 *
 * @par Examples
 * @include timestamp.c
 *
 */

/**
 * @brief 
 * Create a local Timestamp instance
 *
 * @param con  - Connection handle
 * @param type - Timestamp type
 * 
 * @note
 * From version 2.5.0, parameter 'con' can be NULL in order to manipulate 
 * timestamps independently from database connections
 *
 * @note
 * Timestamp type can be : 
 *
 * - OCI_TIMESTAMP : timestamp
 * - OCI_TIMESTAMP_TZ : timestamp with time zone
 * - OCI_TIMESTAMP_LTZ : timestamp with local time zone
 *
 * @return 
 * Return the Timestamp handle on success otherwise NULL on failure
 *
 */

OCI_EXPORT OCI_Timestamp * OCI_API OCI_TimestampCreate
(
    OCI_Connection *con,
    int type
); 

/**
 * @brief 
 * Free an OCI_Timestamp handle
 *
 * @param tmsp - Timestamp handle
 *
 * @warning
 * Only Timestamp created with OCI_TimestampCreate() should be freed by 
 * OCI_IntervalFree()
 *
 * @return 
 * TRUE on success otherwise FALSE
 * 
 */

OCI_EXPORT boolean OCI_API OCI_TimestampFree
(
    OCI_Timestamp *tmsp
);

/**
 * @brief 
 * Return the type of the given Timestamp object
 *
 * @param tmsp - Timestamp handle
 *
 * @note
 * For possibles values, see OCI_TimestampCreate()
 *
 * @return
 * Object type or OCI_UNKNOWN the input handle is NULL
 *
 */

OCI_EXPORT int OCI_API OCI_TimestampGetType
(
    OCI_Timestamp *tmsp
);

/**
 * @brief 
 * Assign the value of a timestamp handle to another one
 *
 * @param tmsp  - Destination Timestamp handle
 * @param tmsp2 - Source Timestamp handle
 * 
 * @return 
 * TRUE on success otherwise FALSE
 * 
 */

OCI_EXPORT boolean OCI_API OCI_TimestampAssign
(
    OCI_Timestamp *tmsp,
    OCI_Timestamp *tmsp2 
);

/**
 * @brief 
 * Check if the given timestamp is valid
 *
 * @param tmsp - Timestamp handle
 * 
 * @return 
 * - Zero if the timestamp value is valid 
 * - Any other value means the timestamp value is invalid
 *
 */

OCI_EXPORT int OCI_API OCI_TimestampCheck 
(
    OCI_Timestamp *tmsp
);

/**
 * @brief 
 * Compares two tTimestamp handles
 *
 * @param tmsp  - Timestamp1 handle
 * @param tmsp2 - Timestamp2 handle
 * 
 * @return 
 * - -1 if Timestamp1 is smaller than Timestamp2,
 * -  0 if they are equal
 * -  1 if Timestamp1 is greater than Timestamp2.
 *
 */

OCI_EXPORT int OCI_API OCI_TimestampCompare
( 
    OCI_Timestamp *tmsp,
    OCI_Timestamp *tmsp2
);

/**
 * @brief 
 * Set a timestamp handle value
 *
 * @param tmsp     - Timestamp handle
 * @param year     - Year value
 * @param month    - Month value
 * @param day      - Day value
 * @param hour     - hour value
 * @param min      - minutes value
 * @param sec      - seconds value
 * @param fsec     - fractional part of seconds value
 * @param timezone - name of a time zone to use [optionnal]
 * 
 * @return 
 * TRUE on success otherwise FALSE
 * 
 */

OCI_EXPORT boolean OCI_API OCI_TimestampConstruct 
( 
    OCI_Timestamp *tmsp,
    int year,
    int month,
    int day,
    int hour,
    int min,
    int sec,
    int fsec,
    const mtext *timezone
);

/**
 * @brief 
 * Convert one timestamp value from one type to another.
 *
 * @param tmsp  - Timestamp handle to convert
 * @param tmsp2 - Timestamp handle to use for the type conversion
 * 
 * @return 
 * TRUE on success otherwise FALSE
 * 
 */

OCI_EXPORT boolean OCI_API OCI_TimestampConvert
(
    OCI_Timestamp *tmsp,
    OCI_Timestamp *tmsp2
);

/**
 * @brief 
 * Convert a string to a timestamp and store it in the given timestamp handle
 *
 * @param tmsp - Destination Timestamp handle
 * @param str  - Source date string
 * @param fmt  - Date format
 * 
 * @return 
 * TRUE on success otherwise FALSE
 * 
 */

OCI_EXPORT boolean OCI_API OCI_TimestampFromText
( 	
    OCI_Timestamp *tmsp,
    const mtext *str,
    const mtext *fmt 
);

/**
 * @brief 
 * Convert a timestamp value from the given timestamp handle to a string
 *
 * @param tmsp      - source Timestamp handle
 * @param fmt       - Timestamp format
 * @param size      - Destination string size in characters
 * @param str       - Destination date string
 * @param precision - Precision for fractionnal part of the seconds
 * 
 * @return 
 * TRUE on success otherwise FALSE
 * 
 */

OCI_EXPORT boolean OCI_API OCI_TimestampToText
(
    OCI_Timestamp *tmsp,
    const mtext *fmt, 
    int size,
    mtext *str,
    int precision
);

/**
 * @brief 
 * Extract the date part from a timestamp handle
 *
 * @param tmsp  - Timestamp handle
 * @param year  - Place holder for year value
 * @param month - Place holder for month value
 * @param day   - Place holder for day value
 * 
 * @return 
 * TRUE on success otherwise FALSE
 * 
 */

OCI_EXPORT boolean OCI_API OCI_TimestampGetDate
( 
    OCI_Timestamp *tmsp,
    int *year,
    int *month,
    int *day
);

/**
 * @brief 
 * Set the time portion of the given timestamp handle
 *
 * @param tmsp  - Timestamp handle
 * @param hour  - Hour value
 * @param min   - Minute value
 * @param sec   - Second value
 * @param fsec  - fractionnal part of second value
 * 
 * @return 
 * TRUE on success otherwise FALSE
 * 
 */

OCI_EXPORT boolean OCI_API OCI_TimestampGetTime
( 
    OCI_Timestamp *tmsp,
    int *hour,
    int *min,
    int *sec,
    int *fsec 
);

/**
 * @brief 
 * Return the time zone name of a timestamp handle
 *
 * @param tmsp - Timestamp handle
 * @param size - Destination string size in characters
 * @param str  - Destination zone name string
 * 
 * @return 
 * TRUE on success otherwise FALSE
 * 
 */

OCI_EXPORT boolean OCI_API OCI_TimestampGetTimeZoneName 
(
    OCI_Timestamp *tmsp,
    int size,
    mtext *str
);

/**
 * @brief 
 * Return the time zone (hour, minute) portion of a timestamp handle
 *
 * @param tmsp  - Timestamp handle
 * @param hour  - Place holder for hour value
 * @param min   - Place holder for min value
 * 
 * @return 
 * TRUE on success otherwise FALSE
 * 
 */

OCI_EXPORT boolean OCI_API OCI_TimestampGetTimeZoneOffset
(
    OCI_Timestamp *tmsp,
    int *hour,
    int *min
);

/**
 * @brief 
 * Add an interval value to a timestamp value of a timestamp handle
 *
 * @param tmsp  - Timestamp handle
 * @param itv   - Interval handle
 * 
 * @return 
 * TRUE on success otherwise FALSE
 * 
 */

OCI_EXPORT boolean OCI_API OCI_TimestampIntervalAdd
( 
    OCI_Timestamp *tmsp,
    OCI_Interval *itv 
);

/**
 * @brief 
 * Subtract an interval value from a timestamp value of a timestamp handle
 *
 * @param tmsp  - Timestamp handle
 * @param itv   - Interval handle
 * 
 * @return 
 * TRUE on success otherwise FALSE
 * 
 */

OCI_EXPORT boolean OCI_API OCI_TimestampIntervalSub
(
    OCI_Timestamp *tmsp,
    OCI_Interval *itv
);

/**
 * @brief 
 * Store the difference of two timestamp handles into an interval handle
 *
 * @param tmsp  - Timestamp handle (subtrahend)
 * @param tmsp2 - Timestamp2 handle (minuend)
 * @param itv   - Interval handle
 * 
 * @note
 * the fonction atc like tmsp - tmsp2 = itv 
 *
 * @return 
 * TRUE on success otherwise FALSE
 * 
 */

OCI_EXPORT boolean OCI_API OCI_TimestampSubtract
(	
    OCI_Timestamp *tmsp,
    OCI_Timestamp *tmsp2,
    OCI_Interval *itv 
);

/**
 * @brief 
 * Stores the system current date and time as a timestamp value with time zone
 * into the timestamp handle.
 *
 * @param tmsp  - Timestamp handle
 *
 * @return 
 * TRUE on success otherwise FALSE
 * 
 */

OCI_EXPORT boolean OCI_API OCI_TimestampSysTimeStamp
(
    OCI_Timestamp *tmsp
);

/**
 * @brief 
 * Affect an OCI_Timestamp handle value to ISO C time datatypes
 *
 * @param tmsp  - Timestamp handle
 * @param ptm   - Pointer to a structure tm to receive date/time values
 * @param pt    - Pointer to a time_t to hold the date/time in the time_t format
 * 
 * @note
 * Both parameters 'ptm' and 'p' are optionnal but one of them has to be provided.
 * 
 * @return 
 * TRUE on success otherwise FALSE
 * 
 */

OCI_EXPORT boolean OCI_API OCI_TimestampToCTime
(
    OCI_Timestamp *tmsp,    
    struct tm *ptm,
    time_t *pt
);

/**
 * @brief 
 * Affect ISO C time datatypes values to an OCI_Timestamp handle 
 *
 * @param tmsp  - Timestamp handle
 * @param ptm   - Pointer to a structure tm that hold the date/time value
 * @param t     - Value (time_t) that hold the date/time in the time_t format
 * 
 * @note
 *
 * Both parameters 'ptm' and 'p' are optionnal but one of them has to be provided.
 * If 'ptm' is not null, its value is affected to the OCI_Timestamp handle, 
 * otherwise the value of 't' is used.
 *
 * @return 
 * TRUE on success otherwise FALSE
 * 
 */

OCI_EXPORT boolean OCI_API OCI_TimestampFromCTime
(
    OCI_Timestamp *tmsp,    
    struct tm *ptm,
    time_t t
);

/**
 * @brief 
 * Create a local interval object
 *
 * @param con  - Connection handle
 * @param type - Type of Interval
 * 
 * @note
 * From version 2.5.0, parameter 'con' can be NULL in order to manipulate 
 * intervals independently from database connections
 *
 * @note
 * Interval type can be : 
 *
 * - OCI_INTERVAL_YM : year / month interval
 * - OCI_INTERVAL_DS : date/ time interval
 * 
 * @return 
 * Return the Interval handle on success otherwise NULL on failure
 *
 */

OCI_EXPORT OCI_Interval * OCI_API OCI_IntervalCreate
(
    OCI_Connection *con,
    int type
); 

/**
 * @brief 
 * Free an OCI_Interval handle
 *
 * @param itv - Interval handle
 *
 * @warning
 * Only Intervals created with OCI_IntervalCreate() should be freed by 
 * OCI_IntervalFree()
 *
 * @return 
 * TRUE on success otherwise FALSE
 * 
 */

OCI_EXPORT boolean OCI_API OCI_IntervalFree
(
    OCI_Interval *itv
);

/**
 * @brief 
 * Return the type of the given Interval object
 *
 * @param itv - Interval handle
 *
 * @note
 * For possibles values, see OCI_IntervalCreate()
 *
 * @return
 * Object type or OCI_UNKNOWN the input handle is NULL
 *
 */

OCI_EXPORT int OCI_API OCI_IntervalGetType
(
    OCI_Interval *itv
);

/**
 * @brief 
 * Assign the value of a interval handle to another one
 *
 * @param itv  - Destination interval handle
 * @param itv2 - Source interval handle
 * 
 * @return 
 * TRUE on success otherwise FALSE
 * 
 */

OCI_EXPORT boolean OCI_API OCI_IntervalAssign 
( 
    OCI_Interval *itv,
    OCI_Interval *itv2
);

/**
 * @brief 
 * Check if the given interval is valid
 *
 * @param itv - Interval handle
 * 
 * @return 
 * - Zero if the interval value is valid 
 * - Any other value means the interval value is invalid
 *
 */

OCI_EXPORT int OCI_API OCI_IntervalCheck 
(
    OCI_Interval *itv
);

/**
 * @brief 
 * Compares two interval handles
 *
 * @param itv  - Interval1 handle
 * @param itv2 - Interval2 handle
 * 
 * @return 
 * - -1 if interval1 is smaller than interval2,
 * -  0 if they are equal
 * -  1 if interval1 is greater than interval2.
 *
 */

OCI_EXPORT int OCI_API OCI_IntervalCompare
(   
    OCI_Interval *itv,
    OCI_Interval *itv2
);

/**
 * @brief 
 * Convert a string to an interval and store it in the given interval handle
 *
 * @param itv  - Destination interval handle
 * @param str  - Source date string
 * 
 * @return 
 * TRUE on success otherwise FALSE
 * 
 */

OCI_EXPORT boolean OCI_API OCI_IntervalFromText
(     
    OCI_Interval *itv,
    const mtext *str
);

/**
 * @brief 
 * Convert an interval value from the given interval handle to a string
 *
 * @param itv           - source Interval handle
 * @param leading_prec  - Precision of the leading part
 * @param fraction_prec - Precision of the fractionnal part
 * @param size          - Destination string size in characters
 * @param str           - Destination date string
 * 
 * @return 
 * TRUE on success otherwise FALSE
 * 
 */

OCI_EXPORT boolean OCI_API OCI_IntervalToText
( 
    OCI_Interval *itv,
    int leading_prec,
    int fraction_prec,
    int size,
    mtext *str
);

/**
 * @brief 
 * Correct an interval handle value with the given time zone
 *
 * @param itv - Interval handle
 * @param str - Time zone name
 * 
 * @return 
 * TRUE on success otherwise FALSE
 * 
 */

OCI_EXPORT boolean OCI_API OCI_IntervalFromTimeZone
(
    OCI_Interval *itv,
    const mtext *str
);

/**
 * @brief 
 * Return the day / time portion of an interval handle
 *
 * @param itv  - Interval handle
 * @param day  - Place holder for day value
 * @param hour - Place holder for hours value
 * @param min  - Place holder for minutes value
 * @param sec  - Place holder for seconds value
 * @param fsec - Place holder for fractionnal part of seconds value
 * 
 * @return 
 * TRUE on success otherwise FALSE
 * 
 */

OCI_EXPORT boolean OCI_API OCI_IntervalGetDaySecond 
(
    OCI_Interval *itv,
    int *day,
    int *hour,
    int *min,
    int *sec,
    int *fsec
);

/**
 * @brief 
 * Return the year / month portion of an interval handle
 *
 * @param itv   - Interval handle
 * @param year  - Place holder for year value
 * @param month - Place holder for month value
 * 
 * @return 
 * TRUE on success otherwise FALSE
 * 
 */

OCI_EXPORT boolean OCI_API OCI_IntervalGetYearMonth 
(  
    OCI_Interval *itv,
    int *year,
    int *month
);

/**
 * @brief 
 * Set the day / time portion if the given interval handle
 *
 * @param itv   - Interval handle
 * @param day   - day value
 * @param hour  - Hour value
 * @param min   - Minute value
 * @param sec   - Second value
 * @param fsec  - Fractional part of the seconds
 * 
 * @return 
 * TRUE on success otherwise FALSE
 * 
 */

OCI_EXPORT boolean OCI_API OCI_IntervalSetDaySecond 
(
    OCI_Interval *itv,
    int day,
    int hour,
    int min,
    int sec,
    int fsec
);

/**
 * @brief 
 * Set the year / month portion if the given Interval handle
 *
 * @param itv    - Interval handle
 * @param year   - Year value
 * @param month  - Month value
 * 
 * @return 
 * TRUE on success otherwise FALSE
 * 
 */

OCI_EXPORT boolean OCI_API OCI_IntervalSetYearMonth
( 
    OCI_Interval *itv,
    int year,
    int month
);

/**
 * @brief 
 * Adds an interval handle value to another
 * 
 * @param itv   - Interval handle from witch to add
 * @param itv2  - Interval handle to add
 * 
 * @return 
 * TRUE on success otherwise FALSE
 * 
 */

OCI_EXPORT boolean OCI_API OCI_IntervalAdd 
( 
    OCI_Interval *itv,
    OCI_Interval *itv2
);

/**
 * @brief 
 * Subtract an interval handle value from another
 * 
 * @param itv   - Interval handle from witch to remove
 * @param itv2  - Interval handle to remove
 * 
 * @return 
 * TRUE on success otherwise FALSE
 * 
 */

OCI_EXPORT boolean OCI_API OCI_IntervalSubtract
(
    OCI_Interval *itv,
    OCI_Interval *itv2
);

/**
 * @}
 */

/**
 * @defgroup g_usertypes Oracle Named Types (Oracle OBJECTs)
 * @{
 *
 * OCILIB implements Oracle Named types (user types and builtin types) through 
 * OCI_Object type.
 * 
 * OTT and C structures are not required to use objects. 
 * In order to manipulate objects attributes, OCILIB proposes a set of function
 * to get/set properties for various supported types.
 * 
 * Objects can be :
 * - Created as standalone instances
 * - Used for binding
 * - Retrieved from select statements
 *
 * @warning
 * Apparently, there is a bug in Oracle when setting an object attribute if
 * OCI is initialized in unicode mode (UTF16).
 * So, DO NOT try to set Objects attributes in Unicode builds because OCI will
 * overwrite internal buffers and later calls to object attributes handles will
 * lead to an OCI crash.
 *
 * @par Example
 * @include object.c
 *
 */

/**
 * @brief 
 * Create a local object instance
 *
 * @param con  - Connection handle
 * @param type - Object type
 * 
 * @return 
 * Return the object handle on success otherwise NULL on failure
 *
 */

OCI_EXPORT OCI_Object * OCI_API OCI_ObjectCreate
(
    OCI_Connection *con, 
    OCI_Schema *type
);

/**
 * @brief 
 * Free a local object
 *
 * @param obj - Object handle
 *
 * @warning
 * Only object created with OCI_ObjectCreate() should be freed 
 * by OCI_ObjectFree()
 *
 * @return 
 * TRUE on success otherwise FALSE
 * 
 */

OCI_EXPORT boolean OCI_API OCI_ObjectFree
(
    OCI_Object *obj
);

/**
 * @brief 
 * Return the short value of the given object attribute 
 *
 * @param obj  - Object handle
 * @param attr - Attribute name
 *
 * @note
 * If the attribute is found in the object descriptor attributes list, then a 
 * datatype check is performed for integrity.
 * OCI_ObjectGetShort() returns a valid value only for integer and number based 
 * attributes 
 * 
 * @return 
 * Attribute value or 0 on failure or wrong attribute type
 * 
 */

OCI_EXPORT short OCI_API OCI_ObjectGetShort
(
    OCI_Object *obj,
    const mtext *attr
);

/**
 * @brief 
 * Return the unsigned short value of the given object attribute 
 *
 * @param obj  - Object handle
 * @param attr - Attribute name
 *
 * @note
 * If the attribute is found in the object descriptor attributes list, then a 
 * datatype check is performed for integrity.
 * OCI_ObjectGetUnsignedShort() returns a valid value only for integer and 
 * number based attributes 
 * 
 * @return 
 * Attribute value or 0 on failure or wrong attribute type
 * 
 */

OCI_EXPORT unsigned short OCI_API OCI_ObjectGetUnsignedShort
(
    OCI_Object *obj,
    const mtext *attr
);

/**
 * @brief 
 * Return the integer value of the given object attribute 
 *
 * @param obj  - Object handle
 * @param attr - Attribute name
 *
 * @note
 * If the attribute is found in the object descriptor attributes list, then a 
 * datatype check is performed for integrity.
 * OCI_ObjectGetInt() returns a valid value only for integer and number based 
 * attributes 
 * 
 * @return 
 * Attribute value or 0 on failure or wrong attribute type
 * 
 */

OCI_EXPORT int OCI_API OCI_ObjectGetInt
(
    OCI_Object *obj,
    const mtext *attr
);

/**
 * @brief 
 * Return the unsigned integer value of the given object attribute 
 *
 * @param obj  - Object handle
 * @param attr - Attribute name
 *
 * @note
 * If the attribute is found in the object descriptor attributes list, then a 
 * datatype check is performed for integrity.
 * OCI_ObjectGetUnsignedInt() returns a valid value only for integer and 
 * number based attributes 
 * 
 * @return 
 * Attribute value or 0 on failure or wrong attribute type
 * 
 */

OCI_EXPORT unsigned int OCI_API OCI_ObjectGetUnsignedInt
(
    OCI_Object *obj,
    const mtext *attr
);

/**
 * @brief 
 * Return the big integer value of the given object attribute 
 *
 * @param obj  - Object handle
 * @param attr - Attribute name
 *
 * @note
 * If the attribute is found in the object descriptor attributes list, then a 
 * datatype check is performed for integrity.
 * OCI_ObjectGetBigInt() returns a valid value only for integer and number based 
 * attributes 
 * 
 * @return 
 * Attribute value or 0 on failure or wrong attribute type
 * 
 */

OCI_EXPORT big_int OCI_API OCI_ObjectGetBigInt
(
    OCI_Object *obj,
    const mtext *attr
);

/**
 * @brief 
 * Return the unsigned big integer value of the given object attribute 
 *
 * @param obj  - Object handle
 * @param attr - Attribute name
 *
 * @note
 * If the attribute is found in the object descriptor attributes list, then a 
 * datatype check is performed for integrity.
 * OCI_ObjectGetUnsignedBigInt() returns a valid value only for integer
 * and number based attributes 
 * 
 * @return 
 * Attribute value or 0 on failure or wrong attribute type
 * 
 */

OCI_EXPORT big_uint OCI_API OCI_ObjectGetUnsignedBigInt
(
    OCI_Object *obj,
    const mtext *attr
);

/**
 * @brief 
 * Return the double value of the given object attribute 
 *
 * @param obj  - Object handle
 * @param attr - Attribute name
 *
 * @note
 * If the attribute is found in the object descriptor attributes list, then a 
 * datatype check is performed for integrity.
 * OCI_ObjectGetDouble() returns a valid value only for integer and number based 
 * attributes 
 * 
 * @return 
 * Attribute value or 0.0 on failure or wrong attribute type
 * 
 */

OCI_EXPORT double OCI_API OCI_ObjectGetDouble
(
    OCI_Object *obj,
    const mtext *attr
);

/**
 * @brief 
 * Return the string value of the given object attribute 
 *
 * @param obj  - Object handle
 * @param attr - Attribute name
 *
 * @note
 * If the attribute is found in the object descriptor attributes list, then a 
 * datatype check is performed for integrity.
 * OCI_ObjectGetString() returns a valid value only for string based 
 * attributes 
 * 
 * @return 
 * Attribute value or NULL on failure or wrong attribute type
 * 
 */

OCI_EXPORT const mtext * OCI_API OCI_ObjectGetString
(
    OCI_Object *obj,
    const mtext *attr
);

/**
 * @brief 
 * Return the raw attribute value of the given object attribute into the
 * given buffer
 *
 * @param obj   - Object handle
 * @param attr  - Attribute name
 * @param value - Destination buffer
 * @param len   - Max size to write into buffer

 * @note
 * If the attribute is found in the object descriptor attributes list, then a 
 * datatype check is performed for integrity.
 * OCI_ObjectGetRaw() copies data into the buffer only for raw based 
 * attributes 
 * 
 * @return 
 * Number of bytes written to the buffer or 0 on failure or wrong attribute type
 * 
 */

OCI_EXPORT int OCI_API OCI_ObjectGetRaw
(
    OCI_Object *obj,
    const mtext *attr,
    void *value,
    int len
);

/**
 * @brief 
 * Return the date value of the given object attribute 
 *
 * @param obj  - Object handle
 * @param attr - Attribute name
 *
 * @note
 * If the attribute is found in the object descriptor attributes list, then a 
 * datatype check is performed for integrity.
 * OCI_ObjectGetDate() returns a valid value only for date based 
 * attributes 
 * 
 * @return 
 * Attribute value or NULL on failure or wrong attribute type
 * 
 */

OCI_EXPORT OCI_Date * OCI_API OCI_ObjectGetDate
(
    OCI_Object *obj,
    const mtext *attr
);

/**
 * @brief 
 * Return the timestamp value of the given object attribute 
 *
 * @param obj  - Object handle
 * @param attr - Attribute name
 *
 * @note
 * If the attribute is found in the object descriptor attributes list, then a 
 * datatype check is performed for integrity.
 * OCI_ObjectGetTimestamp() returns a valid value only for timestamps based 
 * attributes 
 * 
 * @return 
 * Attribute value or NULL on failure or wrong attribute type
 * 
 */

OCI_EXPORT OCI_Timestamp * OCI_API OCI_ObjectGetTimeStamp
(
    OCI_Object *obj,
    const mtext *attr
);

/**
 * @brief 
 * Return the interval value of the given object attribute 
 *
 * @param obj  - Object handle
 * @param attr - Attribute name
 *
 * @note
 * If the attribute is found in the object descriptor attributes list, then a 
 * datatype check is performed for integrity.
 * OCI_ObjectGetInterval() returns a valid value only for intervals based 
 * attributes 
 * 
 * @return 
 * Attribute value or NULL on failure or wrong attribute type
 * 
 */

OCI_EXPORT OCI_Interval * OCI_API OCI_ObjectGetInterval
(
    OCI_Object *obj,
    const mtext *attr
);

/**
 * @brief 
 * Return the object value of the given object attribute 
 *
 * @param obj  - Object handle
 * @param attr - Attribute name
 *
 * @note
 * If the attribute is found in the object descriptor attributes list, then a 
 * datatype check is performed for integrity.
 * OCI_ObjectGetObject() returns a valid value only for object based 
 * attributes 
 * 
 * @return 
 * Attribute value or NULL on failure or wrong attribute type
 * 
 */

OCI_EXPORT OCI_Object * OCI_API OCI_ObjectGetObject
(
    OCI_Object *obj, 
    const mtext *attr
);

/**
 * @brief 
 * Return the lob value of the given object attribute 
 *
 * @param obj  - Object handle
 * @param attr - Attribute name
 *
 * @note
 * If the attribute is found in the object descriptor attributes list, then a 
 * datatype check is performed for integrity.
 * OCI_ObjectGetLob() returns a valid value only for lobs based 
 * attributes 
 * 
 * @return 
 * Attribute value or NULL on failure or wrong attribute type
 * 
 */

OCI_EXPORT OCI_Lob * OCI_API OCI_ObjectGetLob
(
    OCI_Object *obj,
    const mtext *attr
);

/**
 * @brief 
 * Return the file value of the given object attribute 
 *
 * @param obj  - Object handle
 * @param attr - Attribute name
 *
 * @note
 * If the attribute is found in the object descriptor attributes list, then a 
 * datatype check is performed for integrity.
 * OCI_ObjectGetFile() returns a valid value only for files based 
 * attributes 
 * 
 * @return 
 * Attribute value or NULL on failure or wrong attribute type
 * 
 */

OCI_EXPORT OCI_File * OCI_API OCI_ObjectGetFile
(
    OCI_Object *obj,
    const mtext *attr
);

/**
 * @brief 
 * Set an object attribute of type short
 *
 * @param obj    - Object handle
 * @param attr   - Attribute name
 * @param value  - Int value 
 *
 * @return 
 * TRUE on success otherwise FALSE
 * 
 */

OCI_EXPORT boolean OCI_API OCI_ObjectSetShort
(
    OCI_Object *obj, 
    const mtext *attr, 
    short value
);

/**
 * @brief 
 * Set an object attribute of type unsigned short
 *
 * @param obj    - Object handle
 * @param attr   - Attribute name
 * @param value  - Unsigned int value 
 *
 * @return 
 * TRUE on success otherwise FALSE
 * 
 */

OCI_EXPORT boolean OCI_API OCI_ObjectSetUnsignedShort
(
    OCI_Object *obj, 
    const mtext *attr, 
    unsigned short value
);

/**
 * @brief 
 * Set an object attribute of type int
 *
 * @param obj    - Object handle
 * @param attr   - Attribute name
 * @param value  - Int value 
 *
 * @return 
 * TRUE on success otherwise FALSE
 * 
 */

OCI_EXPORT boolean OCI_API OCI_ObjectSetInt
(
    OCI_Object *obj, 
    const mtext *attr, 
    int value
);

/**
 * @brief 
 * Set an object attribute of type unsigned int
 *
 * @param obj    - Object handle
 * @param attr   - Attribute name
 * @param value  - Unsigned int value 
 *
 * @return 
 * TRUE on success otherwise FALSE
 * 
 */

OCI_EXPORT boolean OCI_API OCI_ObjectSetUnsignedInt
(
    OCI_Object *obj, 
    const mtext *attr, 
    unsigned int value
);

/**
 * @brief 
 * Set an object attribute of type big int
 *
 * @param obj    - Object handle
 * @param attr   - Attribute name
 * @param value  - Unsigned big int value 
 *
 * @return 
 * TRUE on success otherwise FALSE
 * 
 */

OCI_EXPORT boolean OCI_API OCI_ObjectSetBigInt
(
    OCI_Object *obj, 
    const mtext *attr, 
    big_int value
);

/**
 * @brief 
 * Set an object attribute of type unsigned big int
 *
 * @param obj    - Object handle
 * @param attr   - Attribute name
 * @param value  - Unsigned big int value 
 *
 * @return 
 * TRUE on success otherwise FALSE
 * 
 */

OCI_EXPORT boolean OCI_API OCI_ObjectSetUnsignedBigInt
(
    OCI_Object *obj, 
    const mtext *attr, 
    big_uint value
);

/**
 * @brief 
 * Set an object attribute of type double
 *
 * @param obj    - Object handle
 * @param attr   - Attribute name
 * @param value  - Double value 
 *
 * @return 
 * TRUE on success otherwise FALSE
 * 
 */

OCI_EXPORT boolean OCI_API OCI_ObjectSetDouble
(
    OCI_Object *obj, 
    const mtext *attr, 
    double value
);

/**
 * @brief 
 * Set an object attribute of type string
 *
 * @param obj    - Object handle
 * @param attr   - Attribute name
 * @param value  - String value 
 *
 * @note
 * passing a null pointer for value calls OCI_ObjectSetNull()
 *
 * @return 
 * TRUE on success otherwise FALSE
 * 
 */

OCI_EXPORT boolean OCI_API OCI_ObjectSetString
(
    OCI_Object *obj, 
    const mtext *attr, 
    const dtext *value
);

/**
 * @brief 
 * Set an object attribute of type RAW
 *
 * @param obj    - Object handle
 * @param attr   - Attribute name
 * @param value  - Raw value 
 * @param len    - Size of the raw value 
 *
 * @note
 * passing a null pointer for value calls OCI_ObjectSetNull()
 *
 * @return 
 * TRUE on success otherwise FALSE
 * 
 */

OCI_EXPORT boolean OCI_API OCI_ObjectSetRaw
(
    OCI_Object *obj, 
    const mtext *attr, 
    void *value,
    int len
);

/**
 * @brief 
 * Set an object attribute to null
 *
 * @param obj    - Object handle
 * @param attr   - Attribute name
 *
 * @return 
 * TRUE on success otherwise FALSE
 * 
 */

OCI_EXPORT boolean OCI_API OCI_ObjectSetNull
(
    OCI_Object *obj, 
    const mtext *attr
);

/**
 * @}
 */

/**
 * @defgroup g_abort Aborting long operations
 * @{
 *
 * The Oracle OCI provides the ability to establish a server connection in :
 *
 * - blocking mode : each call to an OCI function returns control to the 
 *   application when the call completes
 * - non-blocking mode (based on polling paradigm) : the application have to 
 *   call each function until its has completed its job 
 *
 * OCILIB immplements OCI in blocking mode. The application has to wait for OCI
 * calls to complete to continue.
 * 
 * Some operations can be long to be processed by the server. 
 * 
 * In order to cancel the current pending call, OCILIB provides OCI_Break() that
 * cancel the last internal OCI Call and then raise an OCI abortion error code.
 * 
 * @note
 * Any call to OCI_Break() has to be done from a separate thread because the 
 * thread that has executed a long OCI call is waiting for its OCI call to 
 * complete.
 *
 * @par Example
 * @include abort.c
 *
 */

/**
 * @brief 
 * Perform an immediate abort of any currently Oracle OCI call
 *
 * @param con - connection handle
 * 
 * @note
 * The current call will abort and generate an error
 * 
 * @return
 * Returns FALSE if connection handle is NULL otherwise TRUE
 */

OCI_EXPORT boolean OCI_API OCI_Break
(
    OCI_Connection *con
);

/**
 * @}
 */

/**
 * @defgroup g_desc Describing Schema Metadatas and Objects
 * @{
 *
 *
 * @par Example
 * @include desc.c
 *
 */

/**
 * @brief 
 * Retrieve the available schema information
 *
 * @param con  - Connection handle
 * @param name - Table/view name to query for
 * @param type - Type of object
 * 
 * @note
 * Possible values for parameter type are :
 *
 * - OCI_SCHEMA_UNKNOWN
 * - OCI_SCHEMA_TABLE
 * - OCI_SCHEMA_VIEW
 * - OCI_SCHEMA_TYPE
 *
 * @return 
 * - Schema handle on success
 = - NULL if the object does not exist 
 * - NULL on failure
 * 
 */

OCI_EXPORT OCI_Schema * OCI_API OCI_SchemaGet
(
    OCI_Connection *con, 
    const mtext *name, 
    int type
);

/**
 * @brief 
 * Return the type schema object
 *
 * @param schema - Schema handle
 * 
 * @note
 * Possible values for parameter type are :
 *
 * - OCI_SCHEMA_UNKNOWM
 * - OCI_SCHEMA_TABLE
 * - OCI_SCHEMA_VIEW
 * - OCI_SCHEMA_TYPE
 *
 * @return
 * Object type or OCI_UNKNOWN the input handle is NULL
 *
 */

OCI_EXPORT int OCI_API OCI_SchemaGetType
(
    OCI_Schema *schema
);

/**
 * @brief 
 * Free a schema object
 *
 * @param schema  - Schema object handle
 * 
 * @return 
 * TRUE on success otherwise FALSE
 *
 */

OCI_EXPORT boolean OCI_API OCI_SchemaFree
(
    OCI_Schema *schema
);

/**
 * @brief 
 * Retruns the number of columns of a table/view/object
 *
 * @param schema - Schema handle
 * 
 */

OCI_EXPORT int OCI_API OCI_SchemaGetColumnCount
(
    OCI_Schema *schema
);

/**
 * @brief 
 * Return the column object handle at the given index in the table
 *
 * @param schema - Schema handle
 * @param index  - Column position
 * 
 * @return 
 * - Column handle on success 
 * - NULL if index is out of bounds or on error
 * 
 */

OCI_EXPORT OCI_Column * OCI_API OCI_SchemaGetColumn
(
    OCI_Schema *schema,
    int index
);

/**
 * @brief 
 * Return the name described by the schema object
 *
 * @param schema - Schema handle
 * 
 * @return 
 * 
 */

OCI_EXPORT const mtext * OCI_API OCI_SchemaGetName
(
    OCI_Schema *schema
);

/**
 * @}
 */

/**
 * @defgroup g_format Formatted functions
 * @{
 *
 * OCILIB offers some smart routines that takes a variable number of arguments 
 * in order to minimize OCILIB function calls and reduce the amount of code lines
 * 
 * On Windows platforms, the target programming langage must support the __cdecl
 * calling convention
 *
 * @note
 * OCI_Immediate() and OCI_ImmediateFmt() support all OCILIB supported types
 * for output result, except :
 * - OCI_Long 
 * - OCI_Statement
 * If a query output result contains one of these unsupported types, the 
 * function returns FALSE
 *
 * @note
 * In the parameter list, every output placeholder MUST be precedeed by 
 * an integer parameter that indicates the type of the placeholder 
 * in order to handle correctly the given pointer.
 *
 * Possible values for indicating placeholders type :
 *
 * - OCI_ARG_SHORT ------> short *  
 * - OCI_ARG_USHORT -----> unsigned short *
 * - OCI_ARG_INT --------> int *   
 * - OCI_ARG_UINT -------> unsigned int*    
 * - OCI_ARG_BIGINT -----> big_int *   
 * - OCI_ARG_BIGUINT ----> unsignedbig_int *   
 * - OCI_ARG_DOUBLE  ----> double *   
 * - OCI_ARG_TEXT -------> dtext *  
 * - OCI_ARG_RAW --------> void *    
 * - OCI_ARG_DATETIME ---> OCI_Date *       
 * - OCI_ARG_LOB --------> OCI_Lob *   
 * - OCI_ARG_FILE -------> OCI_File *    
 * - OCI_ARG_TIMESTAMP --> OCI_Timstamp *
 * - OCI_ARG_INTERVAL ---> OCI_Interval *
 * 
 * @note 
 * For output strings and Raws, returned data is copied to the given buffer 
 * instead of returning a pointer the real data.
 * So theses buffers must be big enought to hold column content. No size check 
 * is performed.
 *
 * - For strings, only the real string is copied.
 * - For Raws, the number of bytes copied is the column size
 * 
 * @warning
 * Input parameters for formatted function only support a restricted set of
 * datatypes !
 *
 * Supported input identifiers :
 * 
 * - '%s'  : (dtext *) ----------> input string (quotes are added)
 * - '%m'  : (dtext *) ----------> metadata string (no quotes added)
 * - '%t'  : (OCI_Date *) -------> Date
 * - '%p'  : (OCI_Timestamp *) --> timestamp
 * - '%v'  : (OCI_Interval *) ---> Interval
 * - '%i'  : (int) --------------> signed 32 bits integer
 * - '%u'  : (unsigned int) -----> unsigned 32 bits integer
 * - '%li' : (big_int) ----------> signed 64 bits integer
 * - '%lu' : (big_uint) ---------> unsigned 64 bits integer
 * - '%hi' : (short) ------------> signed 16 bits integer
 * - '%hu' : (unsigned short) ---> unsigned 16 bits integer
 * - '%g'  : (double ) ----------> Numerics    
 *
 * @par Example
 * @include format.c
 *
 */

/**
 * @brief 
 * Perform 3 calls (prepare+execute+fetch) in 1 call 
 *
 * @param con  - Connection handle
 * @param sql  - SQL statement
 * @param ...  - List of program variables address to store the result of 
 * fetch operation
 *
 * @note
 * Every output parameter MUST be precedeed by an integer
 * parameter that indicates the type of the placeholder in order
 * to handle correctly the given pointer.
 * 
 * TRUE on success otherwise FALSE
 * 
 */

OCI_EXPORT boolean OCI_Immediate
(
    OCI_Connection *con, 
    const mtext *sql, 
    ...
);

/**
 * @brief 
 * Performs 4 call (prepare+bind+execute+fetch) in 1 call 
 *
 * @param con  - Connection handle
 * @param sql  - SQL statement
 * @param ...  - List of program values to format the SQL followed by the
 * output variables adresses for the fetch operation
 * 
 * TRUE on success otherwise FALSE
 * 
 */

OCI_EXPORT boolean OCI_ImmediateFmt
(
    OCI_Connection *con, 
    const mtext *sql, 
    ...
);

/**
 * @brief 
 * Prepare a formatted SQL statement or PL/SQL block.
 *
 * @param stmt - Statement handle
 * @param sql  - SQL statement
 * @param ...  - List of program values to format the SQL
 * 
 * @return 
 * TRUE on success otherwise FALSE
 */

OCI_EXPORT boolean OCI_PrepareFmt
(
    OCI_Statement *stmt, 
    const mtext *sql, 
    ...
);

/**
 * @brief 
 * Parse and execute a formatted SQL statement or PL/SQL block.
 *
 * @param stmt - Statement handle
 * @param sql  - SQL statement
 * @param ...  - List of program values to format the SQL
 *
 * @return 
 * TRUE on success otherwise FALSE
 *
 */

OCI_EXPORT boolean OCI_ExecuteStmtFmt
(
    OCI_Statement *stmt, 
    const mtext *sql, 
    ...
);

/**
 * @}
 */

/**
 * @defgroup g_hash Hash tables
 * @{
 *
 * OCILIB uses hash tables internally for index/name columns mapping.
 *
 * OCILIB makes public its hash tables implementation public for general purpose
 * uses.
 *
 * OCI_HashTable objects manage string keys / values that can be :
 * 
 * - integers
 * - strings
 * - pointers
 *
 * This hash table implementation :
 * 
 * - handle collisions
 * - allows multiple values per key
 *
 * @par Internal conception

 * - The hash table is composed of an array of slots.
 * - Each slot can hold a linked list of entries (one per key)
 * - Each entry can hold a linked list of values
 *
 * @note
 * - The internal hash function computes the index in the array where the entry
 *   has to be inserted/looked up.
 *
 *
 * @note
 * Collisions are handled by chaining method.
 *
 * @include hash.c
 *
 */

/**
 * @brief 
 * Create a hash table
 *
 * @param size     - size of the hash table
 * @param type     - type of the hash table
 * 
 * @note
 * Parameter can be one of the following values : 
 *
 * - OCI_HASH_STRING  : string values
 * - OCI_HASH_INTEGER : integer values
 * - OCI_HASH_POINTER : pointer values
 *
 * @return 
 * Hash handle on succes or NULL on failure
 *
 */

OCI_EXPORT OCI_HashTable * OCI_API OCI_HashCreate
(
    int size, 
    int type
);

/**
 * @brief 
 * Destroy a hash table
 *
 * @param table - Table handle
 *
 * @return 
 * TRUE on success otherwise FALSE
 *
 */

OCI_EXPORT boolean OCI_API OCI_HashFree
(
    OCI_HashTable *table
);

/**
 * @brief 
 * Return the size of the hash table
 *
 * @param table  - Table handle
 * 
 */

OCI_EXPORT int OCI_API OCI_HashGetSize
(
    OCI_HashTable *table
);

/**
 * @brief 
 * Return the type of the hash table
 *
 * @param table  - Table handle
 *  
 * @note
 * the return value can be one of the following values : 
 *
 * - OCI_HASH_STRING  : string values
 * - OCI_HASH_INTEGER : integer values
 * - OCI_HASH_POINTER : pointer values
 *
 * @return
 * Hashtable datatype or OCI_UNKNOWN the input handle is NULL
 *
 */

OCI_EXPORT int OCI_API OCI_HashGetType
(
    OCI_HashTable *table
);

/**
 * @brief 
 * Add a pair string key / string value to the hash table
 *
 * @param table  - Table handle
 * @param key    - String key 
 * @param value  - string value
 *
 * @return 
 * TRUE on success otherwise FALSE
 * 
 */

OCI_EXPORT boolean OCI_API OCI_HashAddString
(
    OCI_HashTable *table, 
    const mtext *key, 
    const mtext *value
);

/**
 * @brief 
 * Return the string value associated to the given key
 *
 * @param table  - Table handle
 * @param key    - String key 
 * 
 * @return 
 * Stored string associated with the key otherwise NULL
 * 
 */

OCI_EXPORT const mtext * OCI_API OCI_HashGetString
(
    OCI_HashTable *table, 
    const mtext *key
);

/**
 * @brief 
 * Adds a pair string key / integer value to the hash table
 *
 * @param table  - Table handle
 * @param key    - String key 
 * @param value  - Integer value
 *
 * @return 
 * TRUE on success otherwise FALSE
 * 
 */

OCI_EXPORT boolean OCI_API OCI_HashAddInt
(
    OCI_HashTable *table, 
    const mtext *key, 
    int value
);

/**
 * @brief 
 * Return the integer value associated to the given key
 *
 * @param table  - Table handle
 * @param key    - String key 
 *
 * @return 
 * Stored integer associated with the key otherwise 0
 * 
 */

OCI_EXPORT int OCI_API OCI_HashGetInt
(
    OCI_HashTable *table, 
    const mtext *key
);

/**
 * @brief 
 * Adds a pair string key / pointer value to the hash table
 * 
 * @param table  - Table handle
 * @param key    - String key 
 * @param value  - Pointer value
 *
 * @return 
 * TRUE on success otherwise FALSE
 *
 */

OCI_EXPORT boolean OCI_API OCI_HashAddPointer
(
    OCI_HashTable *table, 
    const mtext *key, 
    void *value
);

/**
 * @brief 
 * Return a pointer associated with the given key
 *
 * @param table  - Table handle
 * @param key    - String key 
 *
 * @return 
 * Stored pointer associated with the key otherwise NULL
 *
 */

OCI_EXPORT void * OCI_API OCI_HashGetPointer
(
    OCI_HashTable *table, 
    const mtext *key
);

/**
 * @brief 
 * Lookup for an entry matching the key in the table
 *
 * @param table  - Table handle
 * @param key    - String key 
 * @param create - Do create the entry if not exists
 *
 * @return 
 * Entry handle if key found/added otherwise NULL
 * 
 */

OCI_EXPORT OCI_HashEntry * OCI_API OCI_HashLookup
(
    OCI_HashTable *table, 
    const mtext *key, 
    boolean create
);

/**
 * @brief 
 * Return the first hash slot that matches the key
 *
 * @param table - Table handle
 * @param key   - String key 
 *
 * @return 
 * Slot handle if key found otherwise NULL
 * 
 */

OCI_EXPORT OCI_HashValue * OCI_API OCI_HashGetValue
(
    OCI_HashTable *table, 
    const mtext *key
);

/**
 * @brief 
 * Return the entry slot of the hash table internal list at the given position
 *
 * @param table - Table handle
 * @param index - index
 *
 * @return 
 * Slot handle otherwise NULL
 * 
 */

OCI_EXPORT OCI_HashEntry * OCI_API OCI_HashGetEntry
(
    OCI_HashTable *table, 
    int index
);

/**
 * @}
 */

/**
 * @defgroup g_threads Threads and mutexes
 * @{
 *
 * Oracle proposes a portable implementation of Mutex and Thread objects
 *
 * OCILIB implements these OCI features for portable multithreading support.
 *
 * Mutexes are designed for mutual exclusion between thread in order to lock
 * resources temporarily 
 *
 * Thread keys can be seen as process-wide variables that have a thread-specific 
 * values. It allows to create a unique key identified by a name (string) that
 * can store values specific to each thread.
 *
 * OCILIB exposes the types OCI_Mutex, OCI_Thread
 *
 * @warning
 * OCILIB MUST be initialized with OCI_ENV_THREADED to enable threads support
 *
 * @warning
 * OCI_Thread relies on Oracle API which uses natives threading capabilities of
 * the supported platform
 *
 * @warning
 * Using OCI_Mutex :
 * - On Microsoft Windows, a thread can call OCI_MutexAcquire() more than once 
 * wihtout any blocking. Just be sure that there is an OCI_MutexRelease() for 
 * every OCI_MutexAcquire() call 
 * - On Unixes, a thread MUST call OCI_MutexRelease() after every call to 
 * OCI_MutexAcquire() in order to be able to call OCI_MutexAcquire() again. If 
 * not, it will be blocked...
 *
 * @par Example
 * @include thread.c
 *
 */

/**
 * @brief 
 * Create a Mutex object
 * 
 * @return 
 * Mutex handle on succes or NULL on failure
 *
 */

OCI_EXPORT OCI_Mutex * OCI_API OCI_MutexCreate(void);

/**
 * @brief 
 * Destroy a mutex object
 *
 * @param mutex - Mutex handle
 *
 * @return 
 * TRUE on success otherwise FALSE
 *
 */

OCI_EXPORT boolean OCI_API OCI_MutexFree
(
    OCI_Mutex *mutex
);

/**
 * @brief 
 * Acquire a mutex lock
 *
 * @param mutex - Mutex handle
 *
 * @return 
 * TRUE on success otherwise FALSE
 *
 */

OCI_EXPORT boolean OCI_API OCI_MutexAcquire
(
    OCI_Mutex *mutex
);

/**
 * @brief 
 * Release a mutex lock
 *
 * @param mutex - Mutex handle
 *
 * @return 
 * TRUE on success otherwise FALSE
 *
 */

OCI_EXPORT boolean OCI_API OCI_MutexRelease
(
    OCI_Mutex *mutex
);

/**
 * @brief 
 * Create a Thread object
 * 
 * @return 
 * Thread handle on succes or NULL on failure
 *
 */

OCI_EXPORT OCI_Thread * OCI_API OCI_ThreadCreate(void);

/**
 * @brief 
 * Destroy a thread object
 *
 * @param thread - Thread handle
 *
 * @return 
 * TRUE on success otherwise FALSE
 *
 */

OCI_EXPORT boolean OCI_API OCI_ThreadFree
(
    OCI_Thread *thread
);

/**
 * @brief 
 * Execute the given routine within the given thread object
 *
 * @param thread - Thread handle
 * @param proc   - routine to execute
 * @param arg    - parameter to pass to the routine
 *
 * @return 
 * TRUE on success otherwise FALSE
 *
 */

OCI_EXPORT boolean OCI_API OCI_ThreadRun
(
    OCI_Thread *thread,
    POCI_THREAD proc, 
    void *arg
);

/**
 * @brief 
 * Join the given thread
 *
 * @param thread - Thread handle
 *
 * @note
 * This function waits for the given thread to finish

 * @return 
 * TRUE on success otherwise FALSE
 *
 */

OCI_EXPORT boolean OCI_API OCI_ThreadJoin
(
    OCI_Thread *thread
);

/**
 * @brief 
 * Create a thread key object
 *
 * @param name     - Thread key name
 * @param destfunc - Thread key value destructor function
 * 
 * @note
 * parameter proc is optionnal. It's called when the thread terminates to allow
 * the program to deal with the thread specific value of the key
 *
 * @return 
 * TRUE on success otherwise FALSE
 *
 */

OCI_EXPORT boolean OCI_API OCI_ThreadKeyCreate
(
    mtext *name,
    POCI_THREADKEYDEST destfunc
);

/**
 * @brief 
 * Set a thread key value
 *
 * @param name  - Thread key name
 * @param value - user value to set
 *
 * @return 
 * TRUE on success otherwise FALSE
 *
 */

OCI_EXPORT boolean OCI_API OCI_ThreadKeySetValue
(
    mtext *name,
    void *value
);

/**
 * @brief 
 * Get a thread key value
 *
 * @param name - Thread key name
 *
 * @return 
 * Thread key value on success otherwise FALSE
 *
 */

OCI_EXPORT void * OCI_API OCI_ThreadKeyGetValue
(
    mtext *name
);

/**
 * @}
 */

/**
 * @defgroup g_handles Using OCI Handles directly
 * @{
 *
 * OCILIB conception was focused on a full but closed encapsulation of OCI.
 * 
 * All OCI headers, datatypes, prototypes are imported internally
 * (linkage or runtime import).
 * 
 * OCILIB public interface exposes only ISO C scalar types and OCILIB objects
 *
 * OCI is a wide and rich API that can deals with hundreds of options !
 * 
 * OCILIB tries to implements most of it. But, sometimes in really specific 
 * contexts, it might be necessary to directly call OCI APIs in order to use
 * uncovered OCI functionalities or options
 *
 * OCILIB proposes now a set of functions to retrieve its internal OCI handles
 *
 * @warning
 *
 * The OCILIB author strongly <b>advises</b> against the use of internal handles,
 * unless there is no other way to accomplish the task
 *
 * @warning
 *
 * Using these handles for direct application calls to OCI might lead
 * to OCILIB instability or crash if handles are incorrectly used !
 *
 */

/**
 * @brief 
 * Return the OCI Environment Handle (OCIEnv *) of OCILIB livrary 
 *
 * @return 
 * OCI Environment handle otherwise NULL
 * 
 */

OCI_EXPORT const void * OCI_API OCI_HandleGetEnvironment(void);

/**
 * @brief 
 * Return the OCI Context Handle (OCISvcCtx *) of an OCILIB OCI_Connection
 * object
 *
 * @param con - Connection handle
 *
 * @return 
 * OCI Context handle otherwise NULL
 * 
 */

OCI_EXPORT const void * OCI_API OCI_HandleGetContext
(
    OCI_Connection *con
);

/**
 * @brief 
 * Return the OCI Server Handle (OCIServer *) of an OCILIB OCI_Connection object
 *
 * @param con - Connection handle
 *
 * @return 
 * OCI Server handle otherwise NULL
 * 
 */

OCI_EXPORT const void * OCI_API OCI_HandleGetServer
(
    OCI_Connection *con
);

/**
 * @brief 
 * Return the OCI Error Handle (OCIError *) of an OCILIB OCI_Connection object
 *
 * @param con - Connection handle
 *
 * @return 
 * OCI Error handle otherwise NULL
 * 
 */

OCI_EXPORT const void * OCI_API OCI_HandleGetError
(
    OCI_Connection *con
);

/**
 * @brief 
 * Return the OCI Session Handle (OCISession *) of an OCILIB OCI_Connection
 * object
 *
 * @param con - Connection handle
 *
 * @return 
 * OCI Session handle otherwise NULL
 * 
 */

OCI_EXPORT const void * OCI_API OCI_HandleGetSession
(
    OCI_Connection *con
);

/**
 * @brief 
 * Return the OCI Trasanction Handle (OCITrans *) of an OCILIB OCI_Transaction 
 * object
 *
 * @param trans - Trasanction handle
 *
 * @return 
 * OCI Trasanction handle otherwise NULL
 * 
 */

OCI_EXPORT const void * OCI_API OCI_HandleGetTransaction
(
    OCI_Transaction *trans
);

/**
 * @brief 
 * Return the OCI Statement Handle (OCIStmt *) of an OCILIB OCI_Statement object
 *
 * @param stmt - Statement handle
 *
 * @return 
 * OCI Statement handle otherwise NULL
 * 
 */

OCI_EXPORT const void * OCI_API OCI_HandleGetStatement
(
    OCI_Statement *stmt
);

/**
 * @brief 
 * Return the OCI LobLocator Handle (OCILobLocator *) of an OCILIB OCI_Lob
 * object
 *
 * @param lob - Lob handle
 *
 * @return 
 * OCI LobLocator handle otherwise NULL
 * 
 */

OCI_EXPORT const void * OCI_API OCI_HandleGetLob
(
    OCI_Lob *lob
);

/**
 * @brief 
 * Return the OCI LobLocator Handle (OCILobLocator *) of an OCILIB OCI_File 
 * object
 *
 * @param file - File handle
 *
 * @return 
 * OCI LobLocator handle otherwise NULL
 * 
 */

OCI_EXPORT const void * OCI_API OCI_HandleGetFile
(
    OCI_File *file
);

/**
 * @brief 
 * Return the OCI Date Handle (OCIDate *) of an OCILIB OCI_Date object
 *
 * @param date - Date handle
 *
 * @return 
 * OCI Date handle otherwise NULL
 * 
 */

OCI_EXPORT const void * OCI_API OCI_HandleGetDate
(
    OCI_Date *date
);

/**
 * @brief 
 * Return the OCI Datetime Handle (OCIDatetime *) of an OCILIB OCI_Timestamp
 *  object
 *
 * @param tmsp - Timesstamp handle
 *
 * @return 
 * OCI Datetime handle otherwise NULL
 * 
 */

OCI_EXPORT const void * OCI_API OCI_HandleGetTimestamp
(
    OCI_Timestamp *tmsp
);

/**
 * @brief 
 * Return OCI Interval Handle (OCIInterval *) of an OCILIB OCI_Interval object
 *
 * @param itv - Interval handle
 *
 * @return 
 * OCI Interval handle otherwise NULL
 * 
 */

OCI_EXPORT const void * OCI_API OCI_HandleGetInterval
(
    OCI_Interval *itv
);

/**
 * @brief 
 * Return OCI Object Handle (void *) of an OCILIB OCI_Object object
 *
 * @param obj - Object handle
 *
 * @return 
 * OCI Object handle otherwise NULL
 * 
 */

OCI_EXPORT const void * OCI_API OCI_HandleGetObject
(
    OCI_Object *obj
);

/**
 * @brief 
 * Return OCI Mutex handle (OCIThreadMutex *) of an OCILIB OCI_Mutex object
 *
 * @param mutex - Mutex handle
 *
 * @return 
 * OCI Mutex handle otherwise NULL
 * 
 */

OCI_EXPORT const void * OCI_API OCI_HandleGetMutex
(
    OCI_Mutex *mutex
);

/**
 * @brief 
 * Return OCI Thread ID (OCIThreadId *) of an OCILIB OCI_Thread object
 *
 * @param thread - Thread handle
 *
 * @return 
 * OCI Thread ID otherwise NULL
 * 
 */

OCI_EXPORT const void * OCI_API OCI_HandleGetThreadID
(
    OCI_Thread *thread
 );

/**
 * @brief 
 * Return OCI Thread handle (OCIThreadHandle *) of an OCILIB OCI_Thread object
 *
 * @param thread - Thread handle
 *
 * @return 
 * OCI Thread handle otherwise NULL
 * 
 */

OCI_EXPORT const void * OCI_API OCI_HandleGetThread
(
    OCI_Thread *thread
);

/**
 * @}
 */

#ifdef  __cplusplus
}
#endif

/**
 * @defgroup g_demo OCILIB main demo application code
 * @{
 *
 * Portable Main demo application header
 * @include ocilib_demo.h
 *
 * Portable Main demo application source
 * @include ocilib_demo.c
 *
 * @}
 */

/* Compatibility with sources built with older versiovn of OCILIB */

#define OCI_CreateConnection        OCI_ConnectionCreate
#define OCI_FreeConnection          OCI_ConnectionFree
#define OCI_CreateStatement         OCI_StatementCreate
#define OCI_FreeStatement           OCI_StatementFree
#define OCI_CreateTransaction       OCI_TransactionCreate
#define OCI_FreeTransaction         OCI_TransactionFree
#define OCI_CreateHashTable         OCI_HashCreate
#define OCI_FreeHashTable           OCI_HashFree

#endif    /* OCILIB_H_INCLUDED */

