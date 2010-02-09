/*
   +----------------------------------------------------------------------+   
   |                                                                      |
   |                     OCILIB - C Driver for Oracle                     |
   |                                                                      |
   |                      (C Wrapper for Oracle OCI)                      |
   |                                                                      |
   +----------------------------------------------------------------------+
   |                      Website : http://www.ocilib.net                 |
   +----------------------------------------------------------------------+
   |               Copyright (c) 2007-2010 Vincent ROGIER                 |
   +----------------------------------------------------------------------+
   | This library is free software; you can redistribute it and/or        |
   | modify it under the terms of the GNU Lesser General Public           |
   | License as published by the Free Software Foundation; either         |
   | version 2 of the License, or (at your option) any later version.     |
   |                                                                      |
   | This library is distributed in the hope that it will be useful,      |
   | but WITHOUT ANY WARRANTY; without even the implied warranty of       |
   | MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU    |
   | Lesser General Public License for more details.                      |
   |                                                                      |
   | You should have received a copy of the GNU Lesser General Public     |
   | License along with this library; if not, write to the Free           |
   | Software Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.   |
   +----------------------------------------------------------------------+
   |          Author: Vincent ROGIER <vince.rogier@gmail.com>             |
   +----------------------------------------------------------------------+ 
*/

/* ------------------------------------------------------------------------ *
 * $Id: ocilib_defs.h, v 3.5.1 2010-02-03 18:00 Vincent Rogier $
 * ------------------------------------------------------------------------ */

#ifndef OCILIB_OCILIB_DEFS_H_INCLUDED
#define OCILIB_OCILIB_DEFS_H_INCLUDED

#include "ocilib.h"
#include "oci_import.h"

/* ************************************************************************ *
                           ORACLE VERSION DETECTION
 * ************************************************************************ */

#ifdef OCI_IMPORT_RUNTIME

  /* for runtime loading, set compile time version to the highest minimum
     version needed by OCILIB encapsulation of OCI */
  #define OCI_VERSION_COMPILE OCI_11_1
  /* set runtime version to unknown, it will be guessed from symbols loading */
  #define OCI_VERSION_RUNTIME OCI_UNKNOWN

#else

  #if   defined(OCI_LOB_OPT_COMPRESS)       /* = OCI_11_1 */

    #define OCI_VERSION_COMPILE OCI_11_1
    #define OCI_VERSION_RUNTIME OCI_11_1

  #elif defined(OCI_DBSHUTDOWN_ABORT)       /* = OCI_10_2 */

    #define OCI_VERSION_COMPILE OCI_10_2
    #define OCI_VERSION_RUNTIME OCI_10_2

  #elif defined(OCI_ATTR_DB_CHARSET_ID)     /* = OCI_10_1 */

    #define OCI_VERSION_COMPILE OCI_10_1
    #define OCI_VERSION_RUNTIME OCI_10_1

  #elif defined(OCI_ATTR_STMTCACHESIZE)     /* = OCI_9_2 */

    #define OCI_VERSION_COMPILE OCI_9_2
    #define OCI_VERSION_RUNTIME OCI_9_2

  #elif defined(SQLT_PNTY)                  /* = OCI_9_0 */

    #define OCI_VERSION_COMPILE OCI_9_0
    #define OCI_VERSION_RUNTIME OCI_9_0

  #elif defined(OCIThreadHandle)             /* = OCI_8_1 */

    #define OCI_VERSION_COMPILE OCI_8_1
    #define OCI_VERSION_RUNTIME OCI_8_1

  #elif defined(OCIEnv)                      /* = OCI_8_0 */

    #define OCI_VERSION_COMPILE OCI_8_0
    #define OCI_VERSION_RUNTIME OCI_8_0

  #else                                      /* OCI_UNKNOWN */

    #define OCI_VERSION_COMPILE OCI_UNKNOWN
    #define OCI_VERSION_RUNTIME OCI_UNKNOWN

  #endif

#endif

/* tries to enable Oracle 10g support for lobs > 4Go with OCILobxxx2() calls */

#if defined(OCI_BIG_UINT_ENABLED) && defined(ORAXB8_DEFINED)
  #define OCI_LOB2_API_ENABLED
#endif

/* ************************************************************************ *
                     CHARSET AND STRING TYPES DETECTION
 * ************************************************************************ */

/* mtext and dtext are public character types for meta and user string types
   We need to handle as well internal string types because :
   
   - wchar_t is not the same type on all platforms (that is such a pain !),
   - OCI, in Unicode mode, uses Fixed length UTF16 encoding (2 bytes)
   
   So, omtext and odtext were added to represent internal meta and user string
   types.

   The following checks find out the real types and sizes of omtext and odtext
*/
   
#ifdef OCI_CHARSET_ANSI

  /* easy ! */
  #define omtext mtext
  #define odtext dtext

#else

  #define WCHAR_2_BYTES 0xFFFF
  #define WCHAR_4_BYTES 0x7FFFFFFF

  /* 
     Actually, the only need to use string conversion is when using wchar_t
     on unixes systems. This test will probably change in future releases to
     handle internally UTF8, by example
  */

  #if WCHAR_MAX == WCHAR_4_BYTES
    /* so, input/output conversion will be needed */
    #define OCI_CHECK_STRINGS
  #endif

  #ifdef OCI_METADATA_UNICODE

    #ifdef OCI_CHECK_STRINGS
      /* conversion for meta string needed */
      #define OCI_CHECK_METASTRINGS
    #endif

    /* internal meta string type is UTF16 (2 bytes) */
    #define omtext unsigned short

  #else

    /* internal meta string type is char */
    #define omtext char

  #endif

  #ifdef OCI_USERDATA_UNICODE

    #ifdef OCI_CHECK_STRINGS
      /* conversion for data string needed */
      #define OCI_CHECK_DATASTRINGS
    #endif

    /* internal data string type is UTF16 (2 bytes) */
    #define odtext unsigned short

  #else

    /* internal data string type is char */
    #define odtext char

  #endif

#endif


/* ************************************************************************ *
                            INTERNAL  CONSTANTS
 * ************************************************************************ */

/* ------------------------------------------------------------------------ *
 * DEfault environnement mode
 * ------------------------------------------------------------------------ */

#ifdef OCI_METADATA_UNICODE
    #define OCI_ENV_MODE    OCI_UTF16 
#else
    #define OCI_ENV_MODE    OCI_DEFAULT
#endif

/* ------------------------------------------------------------------------ *
 * Internal Pointer Codes
 * ------------------------------------------------------------------------ */

 /* -- external C pointers ---- */

#define OCI_IPC_VOID             1
#define OCI_IPC_SHORT            2
#define OCI_IPC_INT              3
#define OCI_IPC_BIGINT           4
#define OCI_IPC_DOUBLE           5
#define OCI_IPC_STRING           6
#define OCI_IPC_PROC             7

/* -- external OCILIB handles - */

#define OCI_IPC_ERROR            8
#define OCI_IPC_TYPE_INFO        9
#define OCI_IPC_CONNECTION       10
#define OCI_IPC_CONNPOOL         11
#define OCI_IPC_TRANSACTION      12
#define OCI_IPC_STATEMENT        13 
#define OCI_IPC_RESULTSET        14
#define OCI_IPC_COLUMN           15
#define OCI_IPC_DATE             16
#define OCI_IPC_TIMESTAMP        17
#define OCI_IPC_INTERVAL         18
#define OCI_IPC_LOB              19
#define OCI_IPC_FILE             20
#define OCI_IPC_LONG             21
#define OCI_IPC_OBJECT           22
#define OCI_IPC_COLLECTION       23
#define OCI_IPC_ITERATOR         24
#define OCI_IPC_ELEMENT          25
#define OCI_IPC_HASHTABLE        26
#define OCI_IPC_THREAD           27
#define OCI_IPC_MUTEX            28
#define OCI_IPC_BIND             29
#define OCI_IPC_REF              30
#define OCI_IPC_DIRPATH          31
#define OCI_IPC_NOTIFY           32
#define OCI_IPC_EVENT            33

/* ---- Internal pointers ----- */
 
#define OCI_IPC_LIST             34
#define OCI_IPC_LIST_ITEM        35
#define OCI_IPC_BIND_ARRAY       36
#define OCI_IPC_DEFINE           37
#define OCI_IPC_DEFINE_ARRAY     38
#define OCI_IPC_HASHENTRY        39
#define OCI_IPC_HASHENTRY_ARRAY  40
#define OCI_IPC_HASHVALUE        41
#define OCI_IPC_THREADKEY        42
#define OCI_IPC_OCIDATE          43
#define OCI_IPC_TM               44
#define OCI_IPC_RESULTSET_ARRAY  45
#define OCI_IPC_PLS_SIZE_ARRAY   46
#define OCI_IPC_PLS_RCODE_ARRAY  47
#define OCI_IPC_SERVER_OUPUT     48
#define OCI_IPC_INDICATOR_ARRAY  49
#define OCI_IPC_LEN_ARRAY        50
#define OCI_IPC_BUFF_ARRAY       51
#define OCI_IPC_LONG_BUFFER      52
#define OCI_IPC_TRACE_INFO       53
#define OCI_IPC_DP_COL_ARRAY     54
#define OCI_IPC_BATCH_ERRORS     55

/* ------------------------------------------------------------------------ *
 * Oracle conditionnal features 
 * ------------------------------------------------------------------------ */

#define OCI_FEATURE_UNICODE_USERDATA    1
#define OCI_FEATURE_TIMESTAMP           2
#define OCI_FEATURE_DIRPATH_DATE_CACHE  3
#define OCI_FEATURE_SCROLLABLE_CURSOR   4
#define OCI_FEATURE_DATABASE_NOTIFY     5
#define OCI_FEATURE_REMOTE_DBS_CONTROL  6

/* ------------------------------------------------------------------------ *
 * Oracle conditionnal features 
 * ------------------------------------------------------------------------ */

#define OCI_HDLE_HANDLE                 1
#define OCI_HDLE_DESCRIPTOR             2
#define OCI_HDLE_OBJECT                 3

/* ------------------------------------------------------------------------ *
 * statement status
 * ------------------------------------------------------------------------ */

#define OCI_STMT_CLOSED                 1
#define OCI_STMT_PREPARED               2
#define OCI_STMT_EXECUTED               3

/* ------------------------------------------------------------------------ *
 * connection states
 * ------------------------------------------------------------------------ */

#define OCI_CONN_ALLOCATED              1
#define OCI_CONN_ATTACHED               2
#define OCI_CONN_LOGGED                 3

/* ------------------------------------------------------------------------ *
 * objects status
 * ------------------------------------------------------------------------ */

#define OCI_OBJECT_ALLOCATED            1
#define OCI_OBJECT_FETCHED_CLEAN        2
#define OCI_OBJECT_FETCHED_DIRTY        3

/* ------------------------------------------------------------------------ *
 * bind type
 * ------------------------------------------------------------------------ */

#define OCI_BIND_INPUT                  1
#define OCI_BIND_OUTPUT                 2

/* ------------------------------------------------------------------------ *
 * Type of schema describing
 * ------------------------------------------------------------------------ */

#define OCI_DESC_RESULTSET              1
#define OCI_DESC_COLUMN                 2
#define OCI_DESC_TABLE                  3
#define OCI_DESC_TYPE                   4
#define OCI_DESC_COLLECTION             5

/* ------------------------------------------------------------------------ *
 * Direct path object status
 * ------------------------------------------------------------------------ */

#define OCI_DPS_NOT_PREPARED            1
#define OCI_DPS_PREPARED                2
#define OCI_DPS_CONVERTED               3
#define OCI_DPS_TERMINATED              4

/* ------------------------------------------------------------------------ *
 * internal statement fetch direction
 * ------------------------------------------------------------------------ */

#define OCI_SFD_NEXT                    0x02
#define OCI_SFD_FIRST                   0x04
#define OCI_SFD_LAST                    0x08
#define OCI_SFD_PREV                    0x10

/* ------------------------------------------------------------------------ *
 * internal direct path column types
 * ------------------------------------------------------------------------ */

#define OCI_DDT_TEXT                    1
#define OCI_DDT_BINARY                  2
#define OCI_DDT_NUMBER                  3
#define OCI_DDT_OTHERS                  4

/* ------------------------------------------------------------------------ *
 * internal integer types
 * ------------------------------------------------------------------------ */

#define OCI_NUM_UNSIGNED               2
#define OCI_NUM_SHORT                  4
#define OCI_NUM_INT                    8
#define OCI_NUM_BIGINT                 16
#define OCI_NUM_NUMBER                 32
#define OCI_NUM_DOUBLE                 64

#define OCI_NUM_USHORT                 (OCI_NUM_SHORT  | OCI_NUM_UNSIGNED)
#define OCI_NUM_UINT                   (OCI_NUM_INT    | OCI_NUM_UNSIGNED)
#define OCI_NUM_BIGUINT                (OCI_NUM_BIGINT | OCI_NUM_UNSIGNED)

/* ------------------------------------------------------------------------ *
 *  output buffer server line size
 * ------------------------------------------------------------------------ */

#define OCI_OUPUT_LSIZE                 255
#define OCI_OUPUT_LSIZE_10G             32767

/* ------------------------------------------------------------------------ *
 *  string functions mapping
 * ------------------------------------------------------------------------ */

#ifdef OCI_METADATA_UNICODE
  #define mttoupper           towupper
  #define mtisdigit           iswdigit
  #define mtsscanf            swscanf
#else
  #define mttoupper           toupper
  #define mtisdigit           isdigit
  #define mtsscanf            sscanf
#endif

/* ------------------------------------------------------------------------ *
 *  Unicode constants
 * ------------------------------------------------------------------------ */

/* OCI unicode flag */

#ifndef OCI_UTF16ID
  #define OCI_UTF16ID                   OCI_UCS2ID
#endif

/* unicode constants */

#define UNI_SHIFT             ((int) 10 )
#define UNI_BASE              ((unsigned int) 0x0010000UL)
#define UNI_MASK              ((unsigned int) 0x3FFUL)
#define UNI_REPLACEMENT_CHAR  ((unsigned int) 0x0000FFFD)
#define UNI_MAX_BMP           ((unsigned int) 0x0000FFFF)
#define UNI_MAX_UTF16         ((unsigned int) 0x0010FFFF)
#define UNI_MAX_UTF32         ((unsigned int) 0x7FFFFFFF)
#define UNI_MAX_LEGAL_UTF32   ((unsigned int) 0x0010FFFF)
#define UNI_SUR_HIGH_START    ((unsigned int) 0xD800)
#define UNI_SUR_HIGH_END      ((unsigned int) 0xDBFF)
#define UNI_SUR_LOW_START     ((unsigned int) 0xDC00)
#define UNI_SUR_LOW_END       ((unsigned int) 0xDFFF)

/* ------------------------------------------------------------------------ *
 * Local helper macros
 * ------------------------------------------------------------------------ */

/* check OCI status */

#define OCI_NO_ERROR(res)   ((res) == OCI_SUCCESS)


/* memory management helpers */

#define OCI_FREE(ptr)                   OCI_MemFree(ptr), ptr = NULL;

/* indicator and nullity handlers */

#define OCI_IND(exp)                    (sb2) ((exp) ? 0 : -1)

#define OCI_NOT_NULL(def)                                   \
    ((def != NULL) &&                                       \
     (rs->row_cur > 0) &&                                   \
     ((sb2) ((sb2*)def->buf.inds)[rs->row_cur-1] != -1))


#define OCI_NOT_USED(p)                 (p) = (p);

/* miscellaneaous */

#define OCI_NB_ARG_VERSION              3

#define OCI_LIB_THREADED                (OCILib.env_mode & OCI_ENV_THREADED)

#define OCI_LIB_CONTEXT                 (OCILib.env_mode & OCI_ENV_CONTEXT)


#define OCI_RESULT(res)                                                        \
                                                                               \
        if (OCI_LIB_CONTEXT)                                                   \
            OCI_SetStatus(res);                                                \

#ifdef _WINDOWS
  #define OCI_CVT_CHAR                  1
#else
  #define OCI_CVT_CHAR                  0
#endif

#define OCI_SQLCMD_COUNT                126

#define OCI_ERR_MSG_SIZE                512

#define DEF_ALIGN sizeof(size_t)

#define ROUNDUP(amount) (((unsigned long)(amount)+((DEF_ALIGN)-1))&~((DEF_ALIGN)-1))

#define OCI_SIZEOF_NUMBER               22
#define OCI_SIZEOF_DATE                 7


#endif    /* OCILIB_OCILIB_DEFS_H_INCLUDED */

