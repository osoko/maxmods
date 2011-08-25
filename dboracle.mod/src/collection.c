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
 * $Id: collection.c, v 3.9.2 2011-07-13 00:00 Vincent Rogier $
 * --------------------------------------------------------------------------------------------- */

#include "ocilib_internal.h"

/* ********************************************************************************************* *
 *                             PRIVATE FUNCTIONS
 * ********************************************************************************************* */

/* --------------------------------------------------------------------------------------------- *
 * OCI_CollInit
 * --------------------------------------------------------------------------------------------- */

OCI_Coll * OCI_CollInit
(
    OCI_Connection *con,
    OCI_Coll      **pcoll,
    void           *handle,
    OCI_TypeInfo   *typinf
)
{
    OCI_Coll *coll = NULL;
    boolean res    = TRUE;

    OCI_CHECK(pcoll == NULL, NULL);

    if (*pcoll == NULL)
    {
        *pcoll = (OCI_Coll *) OCI_MemAlloc(OCI_IPC_COLLECTION, sizeof(*coll), (size_t) 1, TRUE);
    }

    if (*pcoll != NULL)
    {
        coll = *pcoll;

        coll->con    = con;
        coll->handle = handle;
        coll->typinf = typinf;

        if ((coll->handle == NULL) || (coll->hstate == OCI_OBJECT_ALLOCATED_ARRAY))
        {
            /* allocates handle for non fetched collection */

            if (coll->hstate != OCI_OBJECT_ALLOCATED_ARRAY)
            {
                coll->hstate = OCI_OBJECT_ALLOCATED;
            }

            OCI_CALL2
            (
                res, con,

                OCI_ObjectNew(coll->con->env, coll->con->err, coll->con->cxt,
                              typinf->ccode, typinf->tdo, (void *) NULL,
                              OCI_DURATION_SESSION, TRUE, (dvoid **) &coll->handle)
            )
        }
        else
        {
            coll->hstate = OCI_OBJECT_FETCHED_CLEAN;
        }
    }
    else
    {
        res = FALSE;
    }

    /* check for failure */

    if (res == FALSE)
    {
        OCI_CollFree(coll);
        coll = NULL;
    }

    return coll;
}

/* ********************************************************************************************* *
 *                             PUBLIC FUNCTIONS
 * ********************************************************************************************* */

/* --------------------------------------------------------------------------------------------- *
 * OCI_CollCreate
 * --------------------------------------------------------------------------------------------- */

OCI_Coll * OCI_API OCI_CollCreate
(
    OCI_TypeInfo *typinf
)
{
    OCI_Coll *coll = NULL;

    OCI_CHECK_INITIALIZED(NULL);

    OCI_CHECK_PTR(OCI_IPC_TYPE_INFO, typinf, NULL);
    OCI_CHECK(typinf->ccode == OCI_UNKNOWN, NULL)

    coll = OCI_CollInit(typinf->con, &coll, (OCIColl *) NULL, typinf);

    OCI_RESULT(coll != NULL);

    return coll;
}

/* --------------------------------------------------------------------------------------------- *
 * OCI_CollFree
 * --------------------------------------------------------------------------------------------- */

boolean OCI_API OCI_CollFree
(
    OCI_Coll *coll
)
{
    OCI_CHECK_PTR(OCI_IPC_COLLECTION, coll, FALSE);
    OCI_CHECK_OBJECT_FETCHED(coll, FALSE);

    /* free data element accessor */

    if (coll->elem != NULL)
    {
        coll->elem->hstate = OCI_OBJECT_FETCHED_DIRTY;
        OCI_ElemFree(coll->elem);
        coll->elem = NULL;
    }

    /* free collection for local object */

    if ((coll->hstate == OCI_OBJECT_ALLOCATED      ) ||
        (coll->hstate == OCI_OBJECT_ALLOCATED_ARRAY))
    {
        OCI_OCIObjectFree(coll->con->env, coll->typinf->con->err, coll->handle, OCI_OBJECTFREE_NONULL);
    }

    if (coll->hstate != OCI_OBJECT_ALLOCATED_ARRAY)
    {
        OCI_FREE(coll);
    }

    OCI_RESULT(TRUE);

    return TRUE;
}

/* --------------------------------------------------------------------------------------------- *
 * OCI_CollArrayCreate
 * --------------------------------------------------------------------------------------------- */

OCI_Coll ** OCI_API OCI_CollArrayCreate
(
    OCI_Connection *con,
    OCI_TypeInfo   *typinf,
    unsigned int    nbelem
)
{
    OCI_Array *arr   = NULL;
    OCI_Coll **colls = NULL;

    arr = OCI_ArrayCreate(con, nbelem, OCI_CDT_COLLECTION, 0, sizeof(OCIColl *),
                          sizeof(OCI_Coll), 0, typinf);

    if (arr != NULL)
    {
        colls = (OCI_Coll **) arr->tab_obj;
    }

    return colls;
}

/* --------------------------------------------------------------------------------------------- *
 * OCI_CollArrayFree
 * --------------------------------------------------------------------------------------------- */

boolean OCI_API OCI_CollArrayFree
(
    OCI_Coll **colls
)
{
    return OCI_ArrayFreeFromHandles((void **) colls);
}

/* --------------------------------------------------------------------------------------------- *
 * OCI_CollAssign
 * --------------------------------------------------------------------------------------------- */

boolean OCI_API OCI_CollAssign
(
    OCI_Coll *coll,
    OCI_Coll *coll_src
)
{
    boolean res = TRUE;

    OCI_CHECK_PTR(OCI_IPC_COLLECTION, coll,     FALSE);
    OCI_CHECK_PTR(OCI_IPC_COLLECTION, coll_src, FALSE);

    OCI_CHECK_COMPAT(coll->con, coll->typinf->cols[0].icode == coll_src->typinf->cols[0].icode, FALSE);

    OCI_CALL2
    (
        res, coll->con,

        OCICollAssign(coll->con->env, coll->con->err, coll_src->handle, coll->handle)
    )

    OCI_RESULT(res);

    return res;
}

/* --------------------------------------------------------------------------------------------- *
 * OCI_CollGetType
 * --------------------------------------------------------------------------------------------- */

unsigned int OCI_API OCI_CollGetType
(
    OCI_Coll *coll
)
{
    unsigned int type = OCI_UNKNOWN;

    OCI_CHECK_PTR(OCI_IPC_COLLECTION, coll, OCI_UNKNOWN);

    if (coll->typinf->ccode == OCI_TYPECODE_TABLE)
    {
        type = OCI_COLL_NESTED_TABLE;
    }
    else if(coll->typinf->ccode == OCI_TYPECODE_VARRAY)
    {
        type = OCI_COLL_VARRAY;
    }

    OCI_RESULT(TRUE);

    return type;
}

/* --------------------------------------------------------------------------------------------- *
 * OCI_CollGetMax
 * --------------------------------------------------------------------------------------------- */

unsigned int OCI_API OCI_CollGetMax
(
    OCI_Coll *coll
)
{
    int max = 0;

    OCI_CHECK_PTR(OCI_IPC_COLLECTION, coll, 0);

    max = OCICollMax(coll->con->env, coll->handle);

    OCI_RESULT(TRUE);

    return (unsigned int) max;
}

/* --------------------------------------------------------------------------------------------- *
 * OCI_CollGetSize
 * --------------------------------------------------------------------------------------------- */

unsigned int OCI_API OCI_CollGetSize
(
    OCI_Coll *coll
)
{
    boolean res = TRUE;
    sb4 size    = 0;

    OCI_CHECK_PTR(OCI_IPC_COLLECTION, coll, 0);

    OCI_CALL2
    (
        res, coll->con,

        OCICollSize(coll->con->env, coll->con->err, coll->handle, &size)
    )

    OCI_RESULT(res);

    return (unsigned int) size;
}

/* --------------------------------------------------------------------------------------------- *
 * OCI_CollTrim
 * --------------------------------------------------------------------------------------------- */

boolean OCI_API OCI_CollTrim
(
    OCI_Coll    *coll,
    unsigned int nb_elem
)
{
    boolean res       = TRUE;
    unsigned int size = 0;

    OCI_CHECK_PTR(OCI_IPC_COLLECTION, coll, FALSE);

    size = OCI_CollGetSize(coll);

    OCI_CHECK_BOUND(coll->con, (sb4) nb_elem, (sb4) 0, (sb4) size, FALSE);

    OCI_CALL2
    (
        res, coll->con,

        OCICollTrim(coll->con->env, coll->con->err, (sb4) nb_elem, coll->handle)
    )

    OCI_RESULT(res);

    return res;
}

/* --------------------------------------------------------------------------------------------- *
 * OCI_CollGetAt
 * --------------------------------------------------------------------------------------------- */

OCI_Elem * OCI_API OCI_CollGetAt
(
    OCI_Coll    *coll,
    unsigned int index
)
{
    boolean res    = TRUE;
    boolean exists = FALSE;
    void *data     = NULL;
    OCIInd *p_ind  = NULL;
    OCI_Elem *elem = NULL;

    OCI_CHECK_PTR(OCI_IPC_COLLECTION, coll, NULL);

    OCI_CALL2
    (
        res, coll->con,

        OCICollGetElem(coll->con->env, coll->con->err, coll->handle, (sb4) index-1,
                       &exists, &data, (dvoid **) (dvoid *) &p_ind)
    )

    if (res == TRUE && exists == TRUE && data != NULL)
    {
        elem = coll->elem = OCI_ElemInit(coll->con, &coll->elem, data, p_ind, coll->typinf);
    }

    OCI_RESULT(res);

    return elem;
}

/* --------------------------------------------------------------------------------------------- *
 * OCI_CollGetAt2
 * --------------------------------------------------------------------------------------------- */

boolean OCI_API OCI_CollGetAt2
(
    OCI_Coll    *coll,
    unsigned int index,
    OCI_Elem    *elem
)
{
    boolean res    = TRUE;
    boolean exists = FALSE;
    void *data     = NULL;
    OCIInd *p_ind  = NULL;

    OCI_CHECK_PTR(OCI_IPC_COLLECTION, coll, FALSE);
    OCI_CHECK_PTR(OCI_IPC_ELEMENT, elem, FALSE);

    OCI_CHECK_COMPAT(coll->con, elem->typinf->cols[0].type == coll->typinf->cols[0].type, FALSE);

    OCI_CALL2
    (
        res, coll->con,

        OCICollGetElem(coll->con->env, coll->con->err, coll->handle, (sb4) index-1,
                       &exists, &data, (dvoid **) (dvoid *) &p_ind)
    )

    if (res == TRUE && exists == TRUE && data != NULL)
    {
        res = (OCI_ElemInit(coll->con, &elem, data, p_ind, coll->typinf) != NULL);
    }
    else
    {
        OCI_ElemSetNullIndicator(elem, OCI_IND_NULL);
    }

    OCI_RESULT(res);

    return res;
}

/* --------------------------------------------------------------------------------------------- *
 * OCI_CollSetAt
 * --------------------------------------------------------------------------------------------- */

boolean OCI_API OCI_CollSetAt
(
    OCI_Coll    *coll,
    unsigned int index,
    OCI_Elem    *elem
)
{
    boolean res = TRUE;

    OCI_CHECK_PTR(OCI_IPC_COLLECTION, coll, FALSE);
    OCI_CHECK_PTR(OCI_IPC_ELEMENT, elem, FALSE);

    OCI_CHECK_COMPAT(coll->con, elem->typinf->cols[0].type == coll->typinf->cols[0].type, FALSE);

    OCI_CALL2
    (
        res, coll->con,

        OCICollAssignElem(coll->con->env, coll->con->err, (sb4) index-1, elem->handle,
                          elem->pind, coll->handle)
    )

    OCI_RESULT(res);

    return res;
}

/* --------------------------------------------------------------------------------------------- *
 * OCI_CollAppend
 * --------------------------------------------------------------------------------------------- */

boolean OCI_API OCI_CollAppend
(
    OCI_Coll *coll,
    OCI_Elem *elem
)
{
    boolean res = TRUE;

    OCI_CHECK_PTR(OCI_IPC_COLLECTION, coll, FALSE);
    OCI_CHECK_PTR(OCI_IPC_ELEMENT, elem, FALSE);

    OCI_CHECK_COMPAT(coll->con, elem->typinf->cols[0].type == coll->typinf->cols[0].type, FALSE);

    OCI_CALL2
    (
        res, coll->con,

        OCICollAppend(coll->con->env, coll->con->err, elem->handle, elem->pind, coll->handle)
    )

    OCI_RESULT(res);

    return res;
}

/* --------------------------------------------------------------------------------------------- *
 * OCI_CollGetTypeInfo
 * --------------------------------------------------------------------------------------------- */

OCI_TypeInfo * OCI_API OCI_CollGetTypeInfo
(
    OCI_Coll *coll
)
{
    OCI_CHECK_PTR(OCI_IPC_COLLECTION, coll, NULL);

    OCI_RESULT(TRUE);

    return coll->typinf;
}

/* --------------------------------------------------------------------------------------------- *
 * OCI_CollClear
 * --------------------------------------------------------------------------------------------- */

boolean OCI_API OCI_CollClear
(
    OCI_Coll *coll
)
{
    boolean res = TRUE;

    unsigned int size = OCI_CollGetSize(coll);

    if (size > 0)
    {
        res = OCI_CollTrim(coll, size);
    }

    OCI_RESULT(res);

    return res;
}

