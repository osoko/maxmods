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
 * $Id: interval.c, v 3.9.0 2011-04-20 00:00 Vincent Rogier $
 * --------------------------------------------------------------------------------------------- */

#include "ocilib_internal.h"

/* ********************************************************************************************* *
 *                             PRIVATE FUNCTIONS
 * ********************************************************************************************* */

/* --------------------------------------------------------------------------------------------- *
 *                         OCI_Interval functions
 * --------------------------------------------------------------------------------------------- */

OCI_Interval * OCI_IntervalInit
(
    OCI_Connection *con,
    OCI_Interval  **pitv,
    OCIInterval    *buffer,
    ub4             type
)
{
    OCI_Interval *itv = NULL;

#if OCI_VERSION_COMPILE >= OCI_9_0

    boolean res = TRUE;

    OCI_CHECK(pitv == NULL, NULL);

    if (*pitv == NULL)
    {
        *pitv = (OCI_Interval *) OCI_MemAlloc(OCI_IPC_INTERVAL, sizeof(*itv), (size_t) 1, TRUE);
    }

    if (*pitv != NULL)
    {
        itv = *pitv;

        itv->con    = con;
        itv->handle = buffer;
        itv->type   = type;

        /* get the right error handle */

        if (con != NULL)
        {
            itv->err = con->err;
            itv->env = con->env;
        }
        else
        {
            itv->err = OCILib.err;
            itv->env = OCILib.env;
        }

        /* allocate buffer if needed */

        if ((itv->handle == NULL) || (itv->hstate == OCI_OBJECT_ALLOCATED_ARRAY))
        {
            ub4 htype = 0;

            if (itv->type == OCI_INTERVAL_YM)
            {
                htype = OCI_DTYPE_INTERVAL_YM;
            }
            else if (itv->type == OCI_INTERVAL_DS)
            {
                htype = OCI_DTYPE_INTERVAL_DS;
            }

            if (itv->hstate != OCI_OBJECT_ALLOCATED_ARRAY)
            {
                res = (OCI_SUCCESS == OCI_DescriptorAlloc((dvoid  *) itv->env,
                                                          (dvoid **) (void *) &itv->handle,
                                                          (ub4     ) htype, (size_t) 0,
                                                          (dvoid **) NULL));

                itv->hstate = OCI_OBJECT_ALLOCATED;
            }
        }
        else
        {
            itv->hstate = OCI_OBJECT_FETCHED_CLEAN;
        }
    }
    else
    {
        res = FALSE;
    }

    /* check for failure */

    if (res == FALSE)
    {
        OCI_IntervalFree(itv);
        itv = NULL;
    }

#else

    OCI_NOT_USED(con);
    OCI_NOT_USED(pitv);
    OCI_NOT_USED(type);
    OCI_NOT_USED(buffer);

#endif

    return itv;
}

/* ********************************************************************************************* *
 *                            PUBLIC FUNCTIONS
 * ********************************************************************************************* */

/* --------------------------------------------------------------------------------------------- *
 * OCI_IntervalCreate
 * --------------------------------------------------------------------------------------------- */

OCI_Interval * OCI_API OCI_IntervalCreate
(
    OCI_Connection *con,
    unsigned int    type
)
{
    OCI_Interval *itv = NULL;

    OCI_CHECK_INITIALIZED(NULL);

    OCI_CHECK_INTERVAL_ENABLED(con, NULL);

#if OCI_VERSION_COMPILE >= OCI_9_0

    itv = OCI_IntervalInit(con, &itv, NULL, type);

#else

    OCI_NOT_USED(type);

#endif

    OCI_RESULT(itv != NULL);

    return itv;
}

/* --------------------------------------------------------------------------------------------- *
 * OCI_IntervalFree
 * --------------------------------------------------------------------------------------------- */

boolean OCI_API OCI_IntervalFree
(
    OCI_Interval *itv
)
{
    OCI_CHECK_PTR(OCI_IPC_INTERVAL, itv, FALSE);

    OCI_CHECK_INTERVAL_ENABLED(itv->con, FALSE);

#if OCI_VERSION_COMPILE >= OCI_9_0

    OCI_CHECK_OBJECT_FETCHED(itv, FALSE);

    if (itv->hstate == OCI_OBJECT_ALLOCATED)
    {
        ub4 htype = 0;

        if (itv->type == OCI_INTERVAL_YM)
        {
            htype = OCI_DTYPE_INTERVAL_YM;
        }
        else if (itv->type == OCI_INTERVAL_DS)
        {
            htype = OCI_DTYPE_INTERVAL_DS;
        }

        OCI_DescriptorFree((dvoid *) itv->handle, htype);
    }

    if (itv->hstate != OCI_OBJECT_ALLOCATED_ARRAY)
    {
        OCI_FREE(itv);
    }

 #endif

    OCI_RESULT(TRUE);

    return TRUE;
}

/* --------------------------------------------------------------------------------------------- *
 * OCI_IntervalArrayCreate
 * --------------------------------------------------------------------------------------------- */

OCI_Interval ** OCI_API OCI_IntervalArrayCreate
(
    OCI_Connection *con,
    unsigned int    type,
    unsigned int    nbelem
)
{
    OCI_Array *arr      = NULL;
    OCI_Interval **itvs = NULL;
    unsigned int htype  = 0;

    if (type == OCI_INTERVAL_YM)
    {
        htype = OCI_INTERVAL_YM;
    }
    else if (type == OCI_INTERVAL_DS)
    {
        htype = OCI_INTERVAL_DS;
    }

    arr = OCI_ArrayCreate(con, nbelem, OCI_CDT_INTERVAL, type, sizeof(OCIInterval *),
                          sizeof(OCI_Interval), htype, NULL);

    if (arr != NULL)
    {
        itvs = (OCI_Interval **) arr->tab_obj;
    }

    return itvs;
}

/* --------------------------------------------------------------------------------------------- *
 * OCI_IntervalArrayFree
 * --------------------------------------------------------------------------------------------- */

boolean OCI_API OCI_IntervalArrayFree
(
    OCI_Interval **itvs
)
{
    return OCI_ArrayFreeFromHandles((void **) itvs);
}

/* --------------------------------------------------------------------------------------------- *
 * OCI_IntervalGetType
 * --------------------------------------------------------------------------------------------- */

unsigned int OCI_API OCI_IntervalGetType
(
    OCI_Interval *itv
)
{
    OCI_CHECK_PTR(OCI_IPC_INTERVAL, itv, OCI_UNKNOWN);

    OCI_CHECK_INTERVAL_ENABLED(itv->con, OCI_UNKNOWN);

    OCI_RESULT(TRUE);

    return itv->type;
}

/* --------------------------------------------------------------------------------------------- *
 * OCI_IntervalAssign
 * --------------------------------------------------------------------------------------------- */

boolean OCI_API OCI_IntervalAssign
(
    OCI_Interval *itv,
    OCI_Interval *itv_src
)
{
    boolean res = TRUE;

    OCI_CHECK_PTR(OCI_IPC_INTERVAL, itv,     FALSE);
    OCI_CHECK_PTR(OCI_IPC_INTERVAL, itv_src, FALSE);

    OCI_CHECK_INTERVAL_ENABLED(itv->con, FALSE);

 #if OCI_VERSION_COMPILE >= OCI_9_0

    OCI_CALL4
    (
        res, itv->err, itv->con,

        OCIIntervalAssign((dvoid *) itv->env, itv->err, itv_src->handle, itv->handle)
    )

 #endif

    OCI_RESULT(res);

    return res;
}

/* --------------------------------------------------------------------------------------------- *
 * OCI_IntervalCheck
 * --------------------------------------------------------------------------------------------- */

int OCI_API OCI_IntervalCheck
(
    OCI_Interval *itv
)
{
    ub4 value   = (ub4) OCI_ERROR;
    boolean res = TRUE;

    OCI_CHECK_PTR(OCI_IPC_INTERVAL, itv, OCI_ERROR);

    OCI_CHECK_INTERVAL_ENABLED(itv->con, OCI_ERROR);

 #if OCI_VERSION_COMPILE >= OCI_9_0

    OCI_CALL4
    (
        res, itv->err, itv->con,

        OCIIntervalCheck((dvoid *) itv->env, itv->err, itv->handle, &value)
    )

 #endif

    OCI_RESULT(res);

    return (int) value;

}

/* --------------------------------------------------------------------------------------------- *
 * OCI_IntervalCompare
 * ----------------------------------------------------------------------- */

int OCI_API OCI_IntervalCompare
(
    OCI_Interval *itv,
    OCI_Interval *itv2
)
{
    sword value = OCI_ERROR;
    boolean res = TRUE;

    OCI_CHECK_PTR(OCI_IPC_INTERVAL, itv,  value);
    OCI_CHECK_PTR(OCI_IPC_INTERVAL, itv2, value);

    OCI_CHECK_INTERVAL_ENABLED(itv->con, value);

 #if OCI_VERSION_COMPILE >= OCI_9_0

    OCI_CALL4
    (
        res, itv->err, itv->con,

        OCIIntervalCompare((dvoid *) itv->env, itv->err, itv2->handle, itv2->handle, &value)
    )

 #endif

    OCI_RESULT(res);

    return (int) value;
}

/* --------------------------------------------------------------------------------------------- *
 * OCI_IntervalFromText
 * --------------------------------------------------------------------------------------------- */

boolean OCI_API OCI_IntervalFromText
(
    OCI_Interval *itv,
    const mtext * str
)
{
    boolean res = TRUE;
    void *ostr  = NULL;
    int osize   = -1;

    OCI_CHECK_PTR(OCI_IPC_INTERVAL, itv, FALSE);
    OCI_CHECK_PTR(OCI_IPC_STRING, str, FALSE);

    OCI_CHECK_INTERVAL_ENABLED(itv->con, FALSE);

 #if OCI_VERSION_COMPILE >= OCI_9_0

    ostr = OCI_GetInputMetaString(str, &osize);

    OCI_CALL4
    (
        res, itv->err, itv->con,

        OCIIntervalFromText((dvoid *) itv->env, itv->err, (OraText *) ostr, (size_t) osize, itv->handle)
    )

    OCI_ReleaseMetaString(ostr);

 #else

    OCI_NOT_USED(str);
    OCI_NOT_USED(ostr);
    OCI_NOT_USED(osize);

#endif

    OCI_RESULT(res);

    return res;
}

/* --------------------------------------------------------------------------------------------- *
 * OCI_IntervalToText
 * --------------------------------------------------------------------------------------------- */

boolean OCI_API OCI_IntervalToText
(
    OCI_Interval *itv,
    int           leading_prec,
    int           fraction_prec,
    int           size,
    mtext        *str
)
{
    boolean res = TRUE;
    void *ostr  = NULL;
    int osize   = size * (int)   sizeof(mtext);
    size_t len  = 0;

    OCI_CHECK_PTR(OCI_IPC_INTERVAL, itv, FALSE);
    OCI_CHECK_PTR(OCI_IPC_STRING, str, FALSE);

    OCI_CHECK_INTERVAL_ENABLED(itv->con, FALSE);

    /* init output buffer in case of OCI failure */

    str[0] = 0;

 #if OCI_VERSION_COMPILE >= OCI_9_0

    ostr = OCI_GetInputMetaString(str, &osize);

    len = (size_t) osize;

    OCI_CALL4
    (
        res, itv->err, itv->con,

        OCIIntervalToText((dvoid *) itv->env, itv->err,
                          (OCIInterval *) itv->handle,
                          (ub1) leading_prec, (ub1) fraction_prec,
                          (OraText *) ostr, (size_t) osize,
                          (size_t *) &len)
    )

    osize = (int) len;

    OCI_GetOutputMetaString(ostr, str, &osize);
    OCI_ReleaseMetaString(ostr);

    /* set null string terminator */

    str[osize/ (int) sizeof(mtext)] = 0;

 #else

    OCI_NOT_USED(str);
    OCI_NOT_USED(ostr);
    OCI_NOT_USED(size);
    OCI_NOT_USED(osize);
    OCI_NOT_USED(leading_prec);
    OCI_NOT_USED(fraction_prec);
    OCI_NOT_USED(len);

 #endif

    OCI_RESULT(res);

    return res;
}

/* --------------------------------------------------------------------------------------------- *
 * OCI_IntervalFromTimeZone
 * --------------------------------------------------------------------------------------------- */

boolean OCI_API OCI_IntervalFromTimeZone
(
    OCI_Interval *itv,
    const mtext * str
)
{
    boolean res = TRUE;
    void *ostr  = NULL;
    int osize   = -1;

    OCI_CHECK_PTR(OCI_IPC_INTERVAL, itv, FALSE);
    OCI_CHECK_PTR(OCI_IPC_STRING, str, FALSE);

    OCI_CHECK_INTERVAL_ENABLED(itv->con, FALSE);

#if OCI_VERSION_COMPILE >= OCI_9_0

    ostr = OCI_GetInputMetaString(str, &osize);

    OCI_CALL4
    (
        res, itv->err, itv->con,

        OCIIntervalFromTZ((dvoid *) itv->env, itv->err, (CONST OraText *) ostr,
                          (size_t) osize, itv->handle)
    )

    OCI_ReleaseMetaString(ostr);

#else

    OCI_NOT_USED(str);
    OCI_NOT_USED(ostr);
    OCI_NOT_USED(osize);

#endif

    OCI_RESULT(res);

    return res;
}

/* --------------------------------------------------------------------------------------------- *
 * OCI_IntervalGetDaySecond
 * --------------------------------------------------------------------------------------------- */

boolean OCI_API OCI_IntervalGetDaySecond
(
    OCI_Interval *itv,
    int          *day,
    int          *hour,
    int          *min,
    int          *sec,
    int          *fsec
)
{
    boolean res = TRUE;

    OCI_CHECK_PTR(OCI_IPC_INTERVAL, itv, FALSE);
    OCI_CHECK_PTR(OCI_IPC_INT, hour, FALSE);
    OCI_CHECK_PTR(OCI_IPC_INT, min, FALSE);
    OCI_CHECK_PTR(OCI_IPC_INT, sec,  FALSE);
    OCI_CHECK_PTR(OCI_IPC_INT, fsec, FALSE);

    OCI_CHECK_INTERVAL_ENABLED(itv->con, FALSE);

    *day  = 0;
    *hour = 0;
    *min  = 0;
    *sec  = 0;
    *fsec = 0;

#if OCI_VERSION_COMPILE >= OCI_9_0

    OCI_CALL4
    (
        res, itv->err, itv->con,

        OCIIntervalGetDaySecond((dvoid *) itv->env, itv->err,
                                (sb4 *) day, (sb4 *) hour, (sb4 *) min,
                                (sb4 *) sec, (sb4 *) fsec, itv->handle)
    )

#else

    OCI_NOT_USED(day);
    OCI_NOT_USED(hour);
    OCI_NOT_USED(min);
    OCI_NOT_USED(sec);
    OCI_NOT_USED(fsec);

#endif

    OCI_RESULT(res);

    return res;
}

/* --------------------------------------------------------------------------------------------- *
 * OCI_IntervalGetYearMonth
 * --------------------------------------------------------------------------------------------- */

boolean OCI_API OCI_IntervalGetYearMonth
(
    OCI_Interval *itv,
    int          *year,
    int          *month
)
{
    boolean res = FALSE;

    OCI_CHECK_PTR(OCI_IPC_INTERVAL, itv, FALSE);
    OCI_CHECK_PTR(OCI_IPC_INT, year,  FALSE);
    OCI_CHECK_PTR(OCI_IPC_INT, month, FALSE);

    OCI_CHECK_INTERVAL_ENABLED(itv->con, FALSE);

    *year  = 0;
    *month = 0;

#if OCI_VERSION_COMPILE >= OCI_9_0

    OCI_CALL4
    (
        res, itv->err, itv->con,

        OCIIntervalGetYearMonth((dvoid *) itv->env, itv->err,
                                (sb4 *) year, (sb4 *) month, itv->handle)
    )

#else

    OCI_NOT_USED(year);
    OCI_NOT_USED(month);

#endif

    OCI_RESULT(res);

    return res;
}

/* --------------------------------------------------------------------------------------------- *
 * OCI_IntervalSetDaySecond
 * --------------------------------------------------------------------------------------------- */

boolean OCI_API OCI_IntervalSetDaySecond
(
    OCI_Interval *itv,
    int           day,
    int           hour,
    int           min,
    int           sec,
    int           fsec
)
{
    boolean res = TRUE;

    OCI_CHECK_PTR(OCI_IPC_INTERVAL, itv, FALSE);

    OCI_CHECK_INTERVAL_ENABLED(itv->con, FALSE);

#if OCI_VERSION_COMPILE >= OCI_9_0

    OCI_CALL4
    (
        res, itv->err, itv->con,

        OCIIntervalSetDaySecond((dvoid *) itv->env, itv->err,
                                (sb4) day, (sb4) hour, (sb4) min,
                                (sb4) sec, (sb4) fsec, itv->handle)
    )

#else

    OCI_NOT_USED(day);
    OCI_NOT_USED(hour);
    OCI_NOT_USED(min);
    OCI_NOT_USED(sec);
    OCI_NOT_USED(fsec);

#endif

    OCI_RESULT(res);

    return res;
}

/* --------------------------------------------------------------------------------------------- *
 * OCI_IntervalSetYearMonth
 * --------------------------------------------------------------------------------------------- */

boolean OCI_API OCI_IntervalSetYearMonth
(
    OCI_Interval *itv,
    int           year,
    int           month
)
{
    boolean res = TRUE;

    OCI_CHECK_PTR(OCI_IPC_INTERVAL, itv, FALSE);

    OCI_CHECK_INTERVAL_ENABLED(itv->con, FALSE);

#if OCI_VERSION_COMPILE >= OCI_9_0

    OCI_CALL4
    (
        res, itv->err, itv->con,

        OCIIntervalSetYearMonth((dvoid *) itv->env, itv->err, (sb4) year, (sb4) month, itv->handle)
    )

#else

    OCI_NOT_USED(year);
    OCI_NOT_USED(month);

#endif

    OCI_RESULT(res);

    return res;
}

/* --------------------------------------------------------------------------------------------- *
 * OCI_IntervalAdd
 * --------------------------------------------------------------------------------------------- */

boolean OCI_API OCI_IntervalAdd
(
    OCI_Interval *itv,
    OCI_Interval *itv2
)
{
    boolean res = FALSE;

    OCI_CHECK_PTR(OCI_IPC_INTERVAL, itv,  FALSE);
    OCI_CHECK_PTR(OCI_IPC_INTERVAL, itv2, FALSE);

    OCI_CHECK_INTERVAL_ENABLED(itv->con, FALSE);

#if OCI_VERSION_COMPILE >= OCI_9_0

    OCI_CALL4
    (
        res, itv->err, itv->con,

        OCIIntervalAdd((dvoid *) itv->env, itv->err, itv->handle, itv2->handle, itv->handle)
    )

#endif

    OCI_RESULT(res);

    return res;
}

/* --------------------------------------------------------------------------------------------- *
 * OCI_IntervalSubtract
 * --------------------------------------------------------------------------------------------- */

boolean OCI_API OCI_IntervalSubtract
(
    OCI_Interval *itv,
    OCI_Interval *itv2
)
{
    boolean res = FALSE;

    OCI_CHECK_PTR(OCI_IPC_INTERVAL, itv,  FALSE);
    OCI_CHECK_PTR(OCI_IPC_INTERVAL, itv2, FALSE);

    OCI_CHECK_INTERVAL_ENABLED(itv->con, FALSE);

#if OCI_VERSION_COMPILE >= OCI_9_0

    OCI_CALL4
    (
        res, itv->err, itv->con,

        OCIIntervalSubtract((dvoid *) itv->env, itv->err, itv->handle, itv2->handle, itv->handle)
    )

#endif

    OCI_RESULT(res);

    return res;
}
