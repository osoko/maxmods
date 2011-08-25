/*
    +-----------------------------------------------------------------------------------------+
    |                                                                                         |
    |                               OCILIB - C Driver for Oracle                              |
    |                                                                                         |
    |                                (C Wrapper for Oracle OCI)                               |
    |                                                                                         |
    |                              Website : http://www.ocilib.net                            |
    |                                                                                         |
    |             Copyright (c) 2007-2011 Vincent ROGIER <vince.rogier@ocilib.net>            |
    |                                                                                         |
    +-----------------------------------------------------------------------------------------+
    |                                                                                         |
    |             This library is free software; you can redistribute it and/or               |
    |             modify it under the terms of the GNU Lesser General Public                  |
    |             License as published by the Free Software Foundation; either                |
    |             version 2 of the License, or (at your option) any later version.            |
    |                                                                                         |
    |             This library is distributed in the hope that it will be useful,             |
    |             but WITHOUT ANY WARRANTY; without even the implied warranty of              |
    |             MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU           |
    |             Lesser General Public License for more details.                             |
    |                                                                                         |
    |             You should have received a copy of the GNU Lesser General Public            |
    |             License along with this library; if not, write to the Free                  |
    |             Software Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.          |
    |                                                                                         |
    +-----------------------------------------------------------------------------------------+
*/

/* --------------------------------------------------------------------------------------------- *
 * $Id: exception.c, v 3.9.2 2011-07-13 00:00 Vincent Rogier $
 * --------------------------------------------------------------------------------------------- */

#include "ocilib_internal.h"

/* ********************************************************************************************* *
 *                            STRINGS MESSAGES
 * ********************************************************************************************* */

static mtext * OCILib_TypeNames[] =
{
    MT("generic pointer"),
    MT("short pointer"),
    MT("int pointer"),
    MT("big_int pointer"),
    MT("double pointer"),
    MT("string pointer"),
    MT("function callback"),

    MT("Error handle"),
    MT("Schema handle"),
    MT("Connection handle"),
    MT("Pool handle"),
    MT("Transaction handle"),
    MT("Statement handle"),
    MT("Resultset handle"),
    MT("Column handle"),
    MT("Date handle"),
    MT("Timestamp handle"),
    MT("Interval handle"),
    MT("Lob handle"),
    MT("File handle"),
    MT("Long handle"),
    MT("Object handle"),
    MT("Collection handle"),
    MT("Collection iterator handle"),
    MT("Collection element handle"),
    MT("Hash Table handle"),
    MT("Thread handle"),
    MT("Mutex handle"),
    MT("Bind handle"),
    MT("Ref handle"),
    MT("Direct Path handle"),
    MT("Subscription handle"),
    MT("Event handle"),
    MT("Array handle"),
    MT("Message handle"),
    MT("Enqueue handle"),
    MT("Dequeue handle"),
    MT("Agent handle"),

    MT("Internal list handle"),
    MT("Internal list item handle"),
    MT("Internal array of bind handles"),
    MT("Internal define handle"),
    MT("Internal array of define handles"),
    MT("Internal hash entry handle"),
    MT("Internal array of hash entry handles"),
    MT("Internal hash value handle"),
    MT("Internal thread key handle"),
    MT("Internal Oracle date handle"),
    MT("Internal C tm structure"),
    MT("Internal array of resultset handles"),
    MT("Internal array of PL/SQL sizes integers"),
    MT("Internal array of PL/SQL return codes integers"),
    MT("Internal server output handle"),
    MT("Internal array of indicator integers"),
    MT("Internal array of buffer length integers"),
    MT("Internal array of data buffers"),
    MT("Internal Long handle data buffer"),
    MT("Internal trace info structure"),
    MT("Internal array of direct path columns"),
    MT("Internal array of batch error objects")
};

#if defined(OCI_CHARSET_WIDE) && !defined(_MSC_VER)

static mtext * OCILib_ErrorMsg[] =
{
    MT("No error"),
    MT("OCILIB has not been initialized"),
    MT("Cannot load OCI shared library (%ls)"),
    MT("Cannot load OCI symbols from shared library"),
    MT("OCILIB has not been initialized in multithreaded mode"),
    MT("Memory allocation failure (type %ls, size : %d)"),
    MT("Feature not available (%ls) "),
    MT("A null %ls has been provided"),
    MT("Oracle datatype (sqlcode %d) not supported for this operation "),
    MT("Unknown identifier %c while parsing SQL"),
    MT("Unknown argument %d while retrieving data"),
    MT("Index %d out of bounds"),
    MT("Found %d unfreed %ls"),
    MT("Maximum number of binds (%d) already reached"),
    MT("Object attribute '%ls' not found"),
    MT("The integer parameter value must be at least %d"),
    MT("Elements are not compatible"),
    MT("The statement must be %ls to perform this operation"),
    MT("The statement is not scrollable"),
    MT("Name or position '%ls' already binded to the statement"),
    MT("Invalid new size for bind arrays (initial %d, current %d, new %d)"),
    MT("Column '%ls' not find in table '%ls'"),
    MT("Unable to perform this operation on a %ls direct path process"),
    MT("Cannot create OCI environment"),
    MT("Name or position '%ls' previously binded with different datatype")
};

#else

static mtext * OCILib_ErrorMsg[] =
{
    MT("No error"),
    MT("OCILIB has not been initialized"),
    MT("Cannot load OCI shared library (%s)"),
    MT("Cannot load OCI symbols from shared library"),
    MT("OCILIB has not been initialized in multithreaded mode"),
    MT("Memory allocation failure (type %s, size : %d)"),
    MT("Feature not available (%s) "),
    MT("A null %s has been provided"),
    MT("Oracle datatype (sqlcode %d) not supported for this operation "),
    MT("Unknown identifier %c while parsing SQL : "),
    MT("Unknown argument %d while retrieving data"),
    MT("Index %d out of bounds"),
    MT("Found %d unfreed %s"),
    MT("Maximum number of binds (%d) already reached"),
    MT("Object attribute '%s' not found"),
    MT("The integer parameter value must be at least %d"),
    MT("Elements are not compatible"),
    MT("The statement must be %s to perform this operation"),
    MT("The statement is not scrollable"),
    MT("Name or position '%s' already binded to the statement"),
    MT("Invalid new size for bind arrays (initial %d, current %d, new %d)"),
    MT("Column '%s' not find in table '%s'"),
    MT("Unable to perform this operation on a %s direct path process"),
    MT("Cannot create OCI environment"),
    MT("Name or position '%ls' previously binded with different datatype")
};

#endif

static mtext * OCILib_OraFeatures[] =
{
    MT("Oracle 9.0 support for Unicode data"),
    MT("Oracle 9.0 Timestamps and Intervals"),
    MT("Oracle 9.2 Direct path date caching"),
    MT("Oracle 9.2 Statement caching"),
    MT("Oracle 10g R1 LOBs size extensions"),
    MT("Oracle 10g R2 Database change notification"),
    MT("Oracle 10g R2 remote database startup/shutdown"),
    MT("Oracle 10g R2 High Availability")
};

typedef struct OCI_StmtStateTable
{
    int    state;
    mtext *name;
} OCI_StmtStateTable;

static OCI_StmtStateTable OCILib_StmtStates[] =
{
    { OCI_STMT_CLOSED,    MT("closed")        },
    { OCI_STMT_PARSED,    MT("parsed")        },
    { OCI_STMT_PREPARED,  MT("prepared")      },
    { OCI_STMT_DESCRIBED, MT("described")     },
    { OCI_STMT_EXECUTED,  MT("executed")      }
};

static mtext * OCILib_DirPathStates[] =
{
    MT("non prepared"),
    MT("prepared"),
    MT("converted"),
    MT("terminated")
};

static mtext * OCILib_HandleNames[] =
{
    MT("OCI handle"),
    MT("OCI descriptors"),
    MT("OCI Object handles")
};

/* ********************************************************************************************* *
 *                             PRIVATE FUNCTIONS
 * ********************************************************************************************* */

/* --------------------------------------------------------------------------------------------- *
 * OCI_ExceptionGetError
 * --------------------------------------------------------------------------------------------- */

OCI_Error * OCI_ExceptionGetError
(
    boolean warning
)
{
    OCI_Error *err = OCI_ErrorGet(TRUE, warning);

    if (err != NULL)
    {
        OCI_ErrorReset(err);

        err->active  = TRUE;
        err->warning = warning;
    }

    return err;
}

/* --------------------------------------------------------------------------------------------- *
 * OCI_ExceptionRaise
 * --------------------------------------------------------------------------------------------- */

void OCI_ExceptionRaise
(
    OCI_Error *err
)
{
    if (err != NULL)
    {
        if (OCILib.error_handler != NULL)
        {
            OCILib.error_handler(err);
        }

        err->active = FALSE;
    }
}

/* --------------------------------------------------------------------------------------------- *
 * OCI_ExceptionOCI
 * --------------------------------------------------------------------------------------------- */

void OCI_ExceptionOCI
(
    OCIError       *p_err,
    OCI_Connection *con,
    OCI_Statement  *stmt,
    boolean         warning
)
{
    OCI_Error *err = OCI_ExceptionGetError(warning);

    if (err != NULL)
    {
        int osize  = -1;
        void *ostr = NULL;

        err->type = (warning ? OCI_ERR_WARNING : OCI_ERR_ORACLE);
        err->con  = con;
        err->stmt = stmt;

        /* get oracle description */

        osize = (int) (msizeof(err->str) - (size_t) 1);
        ostr  = OCI_GetInputMetaString(err->str, &osize);

        OCIErrorGet((dvoid *) p_err, (ub4) 1, (OraText *) NULL, &err->ocode,
                    (OraText *) ostr, (ub4) osize, (ub4) OCI_HTYPE_ERROR);

        OCI_GetOutputMetaString(ostr, err->str, &osize);
        OCI_ReleaseMetaString(ostr);
    }

    OCI_ExceptionRaise(err);
}

/* --------------------------------------------------------------------------------------------- *
 * OCI_ExceptionNotInitialized
 * --------------------------------------------------------------------------------------------- */

void OCI_ExceptionNotInitialized
(
    void
)
{
    OCI_Error *err = OCI_ExceptionGetError(FALSE);

    if (err != NULL)
    {
        err->type  = OCI_ERR_OCILIB;
        err->icode = OCI_ERR_NOT_INITIALIZED;

        mtsncat(err->str,  OCILib_ErrorMsg[OCI_ERR_NOT_INITIALIZED], msizeof(err->str) - (size_t) 1);
    }

    OCI_ExceptionRaise(err);
}

/* --------------------------------------------------------------------------------------------- *
 * OCI_ExceptionLoadingShareLib
 * --------------------------------------------------------------------------------------------- */

void OCI_ExceptionLoadingSharedLib
(
    void
)
{
#ifdef OCI_IMPORT_RUNTIME

    OCI_Error *err = OCI_ExceptionGetError(FALSE);

    if (err != NULL)
    {
        err->type  = OCI_ERR_OCILIB;
        err->icode = OCI_ERR_LOADING_SHARED_LIB;

        mtsprintf(err->str, msizeof(err->str) - (size_t) 1,
                  OCILib_ErrorMsg[OCI_ERR_LOADING_SHARED_LIB],
                  OCI_DL_META_NAME);
    }

    OCI_ExceptionRaise(err);

#endif
}

/* --------------------------------------------------------------------------------------------- *
 * OCI_ExceptionLoadingSymbols
 * --------------------------------------------------------------------------------------------- */

void OCI_ExceptionLoadingSymbols
(
    void
)
{
    OCI_Error *err = OCI_ExceptionGetError(FALSE);

    if (err != NULL)
    {
        err->type  = OCI_ERR_OCILIB;
        err->icode = OCI_ERR_LOADING_SYMBOLS;

        mtsncat(err->str, OCILib_ErrorMsg[OCI_ERR_LOADING_SYMBOLS], msizeof(err->str) - (size_t) 1);
    }

    OCI_ExceptionRaise(err);
}

/* --------------------------------------------------------------------------------------------- *
 * OCI_ExceptionNotMultithreaded
 * --------------------------------------------------------------------------------------------- */

void OCI_ExceptionNotMultithreaded
(
    void
)
{
    OCI_Error *err = OCI_ExceptionGetError(FALSE);

    if (err != NULL)
    {
        err->type  = OCI_ERR_OCILIB;
        err->icode = OCI_ERR_MULTITHREADED;

        mtsncat(err->str, OCILib_ErrorMsg[OCI_ERR_MULTITHREADED], msizeof(err->str) - (size_t) 1);
    }

    OCI_ExceptionRaise(err);
}

/* --------------------------------------------------------------------------------------------- *
 * OCI_ExceptionNullPointer
 * --------------------------------------------------------------------------------------------- */

void OCI_ExceptionNullPointer
(
    int type
)
{
    OCI_Error *err = OCI_ExceptionGetError(FALSE);

    if (err != NULL)
    {
        err->type  = OCI_ERR_OCILIB;
        err->icode = OCI_ERR_NULL_POINTER;

        mtsprintf(err->str, msizeof(err->str) - (size_t) 1,
                  OCILib_ErrorMsg[OCI_ERR_NULL_POINTER],
                  OCILib_TypeNames[type-1]);
    }

    OCI_ExceptionRaise(err);
}

/* --------------------------------------------------------------------------------------------- *
 * OCI_ExceptionMemory
 * --------------------------------------------------------------------------------------------- */

void OCI_ExceptionMemory
(
    int             type,
    size_t          nb_bytes,
    OCI_Connection *con,
    OCI_Statement  *stmt
)
{
    OCI_Error *err = OCI_ExceptionGetError(FALSE);

    if (err != NULL)
    {
        err->type  = OCI_ERR_OCILIB;
        err->icode = OCI_ERR_MEMORY;
        err->con   = con;
        err->stmt  = stmt;

        mtsprintf(err->str,
                  msizeof(err->str) - (size_t) 1,
                  OCILib_ErrorMsg[OCI_ERR_MEMORY],
                  OCILib_TypeNames[type-1],
                  nb_bytes);
    }

    OCI_ExceptionRaise(err);
}

/* --------------------------------------------------------------------------------------------- *
 * OCI_ExceptionNotAvailable
 * --------------------------------------------------------------------------------------------- */

void OCI_ExceptionNotAvailable
(
    OCI_Connection *con,
    int             feature
)
{
    OCI_Error *err = OCI_ExceptionGetError(FALSE);

    if (err != NULL)
    {
        err->type  = OCI_ERR_OCILIB;
        err->icode = OCI_ERR_NOT_AVAILABLE;
        err->con   = con;

        mtsprintf(err->str,
                  msizeof(err->str) - (size_t) 1,
                  OCILib_ErrorMsg[OCI_ERR_NOT_AVAILABLE],
                  OCILib_OraFeatures[feature-1]);
    }

    OCI_ExceptionRaise(err);
}

/* --------------------------------------------------------------------------------------------- *
 * OCI_ExceptionDatatypeNotSupported
 * --------------------------------------------------------------------------------------------- */

void OCI_ExceptionDatatypeNotSupported
(
    OCI_Connection *con,
    OCI_Statement  *stmt,
    int             code
)
{
    OCI_Error *err = OCI_ExceptionGetError(FALSE);

    if (err != NULL)
    {
        err->type  = OCI_ERR_OCILIB;
        err->icode = OCI_ERR_DATATYPE_NOT_SUPPORTED;
        err->con   = con;
        err->stmt  = stmt;

        mtsprintf(err->str,
                  msizeof(err->str) - (size_t) 1,
                  OCILib_ErrorMsg[OCI_ERR_DATATYPE_NOT_SUPPORTED],
                  code);
    }

    OCI_ExceptionRaise(err);
}

/* --------------------------------------------------------------------------------------------- *
 * OCI_ExceptionParsingError
 * --------------------------------------------------------------------------------------------- */

void OCI_ExceptionParsingToken
(
    OCI_Connection *con,
    OCI_Statement  *stmt,
    mtext           token
)
{
    OCI_Error *err = OCI_ExceptionGetError(FALSE);

    if (err != NULL)
    {
        err->type  = OCI_ERR_OCILIB;
        err->icode = OCI_ERR_PARSE_TOKEN;
        err->con   = con;
        err->stmt  = stmt;

        mtsprintf(err->str,
                  msizeof(err->str) - (size_t) 1,
                  OCILib_ErrorMsg[OCI_ERR_PARSE_TOKEN],
                  token);
    }

    OCI_ExceptionRaise(err);
}

/* --------------------------------------------------------------------------------------------- *
 * OCI_ExceptionMappingArgument
 * --------------------------------------------------------------------------------------------- */

void OCI_ExceptionMappingArgument
(
    OCI_Connection *con,
    OCI_Statement  *stmt,
    int             arg
)
{
    OCI_Error *err = OCI_ExceptionGetError(FALSE);

    if (err != NULL)
    {
        err->type  = OCI_ERR_OCILIB;
        err->icode = OCI_ERR_MAP_ARGUMENT;
        err->con   = con;
        err->stmt  = stmt;

        mtsprintf(err->str,
                  msizeof(err->str) - (size_t) 1,
                  OCILib_ErrorMsg[OCI_ERR_MAP_ARGUMENT],
                  arg);
    }

    OCI_ExceptionRaise(err);
}

/* --------------------------------------------------------------------------------------------- *
 * OCI_ExceptionOutOfBounds
 * --------------------------------------------------------------------------------------------- */

void OCI_ExceptionOutOfBounds
(
    OCI_Connection *con,
    int             value
)
{
    OCI_Error *err = OCI_ExceptionGetError(FALSE);

    if (err != NULL)
    {
        err->type  = OCI_ERR_OCILIB;
        err->icode = OCI_ERR_OUT_OF_BOUNDS;
        err->con   = con;

        mtsprintf(err->str,
                  msizeof(err->str) - (size_t) 1,
                  OCILib_ErrorMsg[OCI_ERR_OUT_OF_BOUNDS],
                  value);
    }

    OCI_ExceptionRaise(err);
}

/* --------------------------------------------------------------------------------------------- *
* OCI_ExceptionUnfreedData
* --------------------------------------------------------------------------------------------- */

void OCI_ExceptionUnfreedData
(
    int type_elem,
    int nb_elem
)
{
    OCI_Error *err = OCI_ExceptionGetError(FALSE);

    if (err != NULL)
    {
        err->type  = OCI_ERR_OCILIB;
        err->icode = OCI_ERR_UNFREED_DATA;

        mtsprintf(err->str,
                  msizeof(err->str) - (size_t) 1,
                  OCILib_ErrorMsg[OCI_ERR_UNFREED_DATA],
                  nb_elem, OCILib_HandleNames[type_elem-1]);
    }

    OCI_ExceptionRaise(err);
}

/* --------------------------------------------------------------------------------------------- *
 * OCI_ExceptionRuntimeLoading
 * --------------------------------------------------------------------------------------------- */

void OCI_ExceptionMaxBind
(
    OCI_Statement *stmt
)
{
    OCI_Error *err = OCI_ExceptionGetError(FALSE);

    if (err != NULL)
    {
        err->type  = OCI_ERR_OCILIB;
        err->icode = OCI_ERR_MAX_BIND;
        err->stmt  = stmt;

        if (stmt != NULL)
            err->con =  stmt->con;

        mtsprintf(err->str,
                  msizeof(err->str) - (size_t) 1,
                  OCILib_ErrorMsg[OCI_ERR_MAX_BIND],
                  OCI_BIND_MAX);
    }

    OCI_ExceptionRaise(err);
}

/* --------------------------------------------------------------------------------------------- *
 * OCI_ExceptionAttributeNotFound
 * --------------------------------------------------------------------------------------------- */

void OCI_ExceptionAttributeNotFound
(
    OCI_Connection *con,
    const mtext    *attr
)
{
    OCI_Error *err = OCI_ExceptionGetError(FALSE);

    if (err != NULL)
    {
        err->type  = OCI_ERR_OCILIB;
        err->icode = OCI_ERR_ATTR_NOT_FOUND;
        err->con   = con;

        mtsprintf(err->str,
                  msizeof(err->str) - (size_t) 1,
                  OCILib_ErrorMsg[OCI_ERR_ATTR_NOT_FOUND],
                  attr);
    }

    OCI_ExceptionRaise(err);
}

/* --------------------------------------------------------------------------------------------- *
 * OCI_ExceptionMinimumValue
 * --------------------------------------------------------------------------------------------- */

void OCI_ExceptionMinimumValue
(
    OCI_Connection *con,
    OCI_Statement  *stmt,
    int             min
)
{
    OCI_Error *err = OCI_ExceptionGetError(FALSE);

    if (err != NULL)
    {
        err->type  = OCI_ERR_OCILIB;
        err->icode = OCI_ERR_MIN_VALUE;
        err->con   = con;
        err->stmt  = stmt;

        mtsprintf(err->str, msizeof(err->str) - (size_t) 1, OCILib_ErrorMsg[OCI_ERR_MIN_VALUE], min);
    }

    OCI_ExceptionRaise(err);
}

/* --------------------------------------------------------------------------------------------- *
 * OCI_ExceptionTypeNotCompatible
 * --------------------------------------------------------------------------------------------- */

void OCI_ExceptionTypeNotCompatible
(
    OCI_Connection *con
)
{
    OCI_Error *err = OCI_ExceptionGetError(FALSE);

    if (err != NULL)
    {
        err->type  = OCI_ERR_OCILIB;
        err->icode = OCI_ERR_NOT_COMPATIBLE;
        err->con   = con;

        mtsncat(err->str, OCILib_ErrorMsg[OCI_ERR_NOT_COMPATIBLE], msizeof(err->str) - (size_t) 1);
    }

    OCI_ExceptionRaise(err);
}

/* --------------------------------------------------------------------------------------------- *
 * OCI_ExceptionStatementState
 * --------------------------------------------------------------------------------------------- */

void OCI_ExceptionStatementState
(
    OCI_Statement *stmt,
    int            state
)
{
    OCI_Error *err = OCI_ExceptionGetError(FALSE);

    if (err != NULL)
    {
        int i, index;

        index      = 0;

        err->type  = OCI_ERR_OCILIB;
        err->icode = OCI_ERR_STMT_STATE;
        err->stmt  = stmt;
        err->con   =  stmt->con;

        for(i = 0; i < OCI_STMT_STATES_COUNT; i++)
        {
            if (state == OCILib_StmtStates[i].state)
            {
                index = i;
                break;
            }
        }

        mtsprintf(err->str,
                  msizeof(err->str) - (size_t) 1,
                  OCILib_ErrorMsg[OCI_ERR_STMT_STATE],
                  OCILib_StmtStates[index].name);
    }

    OCI_ExceptionRaise(err);
}

/* --------------------------------------------------------------------------------------------- *
 * OCI_ExceptionStatementNotScrollable
 * --------------------------------------------------------------------------------------------- */

void OCI_ExceptionStatementNotScrollable
(
    OCI_Statement *stmt
)
{
    OCI_Error *err = OCI_ExceptionGetError(FALSE);

    if (err != NULL)
    {
        err->type  = OCI_ERR_OCILIB;
        err->icode = OCI_ERR_STMT_NOT_SCROLLABLE;
        err->stmt  = stmt;

        if (stmt != NULL)
        {
            err->con =  stmt->con;
        }

        mtsncat(err->str, OCILib_ErrorMsg[OCI_ERR_STMT_NOT_SCROLLABLE], msizeof(err->str) - (size_t) 1);

    }

    OCI_ExceptionRaise(err);
}

/* --------------------------------------------------------------------------------------------- *
 * OCI_ExceptionBindAlreadyUsed
 * --------------------------------------------------------------------------------------------- */

void OCI_ExceptionBindAlreadyUsed
(
    OCI_Statement *stmt,
    const mtext  * bind
)
{
    OCI_Error *err = OCI_ExceptionGetError(FALSE);

    if (err != NULL)
    {
        err->type  = OCI_ERR_OCILIB;
        err->icode = OCI_ERR_BIND_ALREADY_USED;
        err->stmt  = stmt;

        if (stmt != NULL)
        {
            err->con =  stmt->con;
        }

        mtsprintf(err->str,
                  msizeof(err->str) - (size_t) 1,
                  OCILib_ErrorMsg[OCI_ERR_BIND_ALREADY_USED],
                  bind);
    }

    OCI_ExceptionRaise(err);
}

/* --------------------------------------------------------------------------------------------- *
 * OCI_ExceptionBindArraySize
 * --------------------------------------------------------------------------------------------- */

void OCI_ExceptionBindArraySize
(
    OCI_Statement *stmt,
    unsigned int   maxsize,
    unsigned int   cursize,
    unsigned int   newsize
)
{
    OCI_Error *err = OCI_ExceptionGetError(FALSE);

    if (err != NULL)
    {
        err->type  = OCI_ERR_OCILIB;
        err->icode = OCI_ERR_BIND_ARRAY_SIZE;
        err->stmt  = stmt;

        if (stmt != NULL)
        {
            err->con =  stmt->con;
        }

        mtsprintf(err->str,
                  msizeof(err->str) - (size_t) 1,
                  OCILib_ErrorMsg[OCI_ERR_BIND_ARRAY_SIZE],
                  maxsize, cursize, newsize);
    }

    OCI_ExceptionRaise(err);
}

/* --------------------------------------------------------------------------------------------- *
 * OCI_ExceptionDirPathColNotFound
 * --------------------------------------------------------------------------------------------- */

void OCI_ExceptionDirPathColNotFound
(
    OCI_DirPath  *dp,
    const mtext * column,
    const mtext  *table
)
{
    OCI_Error *err = OCI_ExceptionGetError(FALSE);

    if (err != NULL)
    {
        err->type  = OCI_ERR_OCILIB;
        err->icode = OCI_ERR_DIRPATH_STATE;
        err->stmt  = NULL;

        if (dp != NULL)
        {
            err->con =  dp->con;
        }

        mtsprintf(err->str,
                  msizeof(err->str) - (size_t) 1,
                  OCILib_ErrorMsg[OCI_ERR_COLUMN_NOT_FOUND],
                  column,
                  table);
    }

    OCI_ExceptionRaise(err);
}

/* --------------------------------------------------------------------------------------------- *
 * OCI_ExceptionDirPathState
 * --------------------------------------------------------------------------------------------- */

void OCI_ExceptionDirPathState
(
    OCI_DirPath *dp,
    int          state
)
{
    OCI_Error *err = OCI_ExceptionGetError(FALSE);

    if (err != NULL)
    {
        err->type  = OCI_ERR_OCILIB;
        err->icode = OCI_ERR_DIRPATH_STATE;
        err->stmt  = NULL;

        if (dp != NULL)
        {
            dp->con =  dp->con;
        }

        mtsprintf(err->str,
                  msizeof(err->str) - (size_t) 1,
                  OCILib_ErrorMsg[OCI_ERR_DIRPATH_STATE],
                  OCILib_DirPathStates[state-1]);
    }

    OCI_ExceptionRaise(err);
}

/* --------------------------------------------------------------------------------------------- *
 * OCI_ExceptionOCIEnvironment
 * --------------------------------------------------------------------------------------------- */

void OCI_ExceptionOCIEnvironment
(
    void
)
{
    OCI_Error *err = OCI_ExceptionGetError(FALSE);

    if (err != NULL)
    {
        err->type  = OCI_ERR_OCILIB;
        err->icode = OCI_ERR_CREATE_OCI_ENVIRONMENT;

        mtsncat(err->str,  OCILib_ErrorMsg[OCI_ERR_CREATE_OCI_ENVIRONMENT], msizeof(err->str) - (size_t) 1);
    }

    OCI_ExceptionRaise(err);
}

/* --------------------------------------------------------------------------------------------- *
 * OCI_ExceptionRebindBadDatatype
 * --------------------------------------------------------------------------------------------- */

void OCI_ExceptionRebindBadDatatype
(
    OCI_Statement *stmt,
    const mtext  * bind
)
{
    OCI_Error *err = OCI_ExceptionGetError(FALSE);

    if (err != NULL)
    {
        err->type  = OCI_ERR_OCILIB;
        err->icode = OCI_ERR_REBIND_BAD_DATATYPE;
        err->stmt  = stmt;

        if (stmt != NULL)
        {
            err->con =  stmt->con;
        }

        mtsprintf(err->str,
                  msizeof(err->str) - (size_t) 1,
                  OCILib_ErrorMsg[OCI_ERR_REBIND_BAD_DATATYPE],
                  bind);
    }

    OCI_ExceptionRaise(err);
}

