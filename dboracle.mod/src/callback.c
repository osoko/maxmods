/*
    +-----------------------------------------------------------------------------------------+
    |                                                                                         |
    |                               OCILIB - C Driver for Oracle                              |
    |                                                                                         |
    |                                (C Wrapper for Oracle OCI)                               |
    |                                                                                         |
    |                              Website : http://www.ocilib.net                            |
    |                                                                                         |
    |             Copyright (c) 2007-2013 Vincent ROGIER <vince.rogier@ocilib.net>            |
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
 * $Id: callback.c, Vincent Rogier $
 * --------------------------------------------------------------------------------------------- */

#include "ocilib_internal.h"

/* ********************************************************************************************* *
 *                             PRIVATE FUNCTIONS
 * ********************************************************************************************* */

/* --------------------------------------------------------------------------------------------- *
 * OCI_ProcInBind
 * --------------------------------------------------------------------------------------------- */

sb4 OCI_ProcInBind
(
    dvoid   *ictxp,
    OCIBind *bindp,
    ub4      iter,
    ub4      index,
    dvoid  **bufpp,
    ub4     *alenp,
    ub1     *piecep,
    dvoid  **indp
)
{
    OCI_Bind * bnd = (OCI_Bind *) ictxp;
    sb2 *ind       = (sb2 *) bnd->buf.inds;
    ub4 i          = 0;

    /* those checks may be not necessary but they keep away compilers warning
       away if the warning level is set to maximum !
    */

    OCI_NOT_USED(index);
    OCI_NOT_USED(bindp);

    /* check objects and bounds */

    OCI_CHECK(bnd  == NULL, OCI_ERROR);
    OCI_CHECK(iter >= bnd->buf.count, OCI_ERROR);

    /* indicators must be set to -1 depending on datatype,
       so let's do it for all */

    for (i = 0; i < bnd->buf.count; i++, ind++)
    {
        *ind = -1;
    }

    /* setup bind index because OCI_RegisterXXX() might not have been called
       in the same order than the variables in the returning clause */

    if (iter == 0)
    {
        bnd->dynpos = bnd->stmt->dynidx++;
    }

    /* we do not need to do anything here except setting indicators */

    *bufpp  = (dvoid *) 0;
    *alenp  = (ub4    ) 0;
    *indp   = (dvoid *) bnd->buf.inds;
    *piecep = (ub1    ) OCI_ONE_PIECE;

    return OCI_CONTINUE;
}

/* --------------------------------------------------------------------------------------------- *
 * OCI_ProcOutBind
 * --------------------------------------------------------------------------------------------- */

sb4 OCI_ProcOutBind
(
    dvoid   *octxp,
    OCIBind *bindp,
    ub4      iter,
    ub4      index,
    dvoid  **bufpp,
    ub4    **alenp,
    ub1     *piecep,
    dvoid  **indp,
    ub2    **rcodep
)
{
    OCI_Bind * bnd    = (OCI_Bind *) octxp;
    OCI_Define *def   = NULL;
    OCI_Resultset *rs = NULL;
    boolean res       = TRUE;
    ub4 rows          = 0;

    /* those checks may be not necessary but they keep away compilers warning
       away if the warning level is set to maximum !
    */

    OCI_NOT_USED(bindp);

    /* check objects and bounds */

    OCI_CHECK(bnd  == NULL, OCI_ERROR);
    OCI_CHECK(iter >= bnd->buf.count, OCI_ERROR);

    /* update statmement status */

    bnd->stmt->status |= OCI_STMT_EXECUTED;

    /* create resultset on the first row processed for each iteration */

    if (index == 0)
    {
        bnd->stmt->nb_rs  = bnd->stmt->nb_iters;
        bnd->stmt->cur_rs = 0;

        /* allocate resultset handles array */

        if (bnd->stmt->rsts == NULL)
        {
            bnd->stmt->rsts = (OCI_Resultset **) OCI_MemAlloc(OCI_IPC_RESULTSET_ARRAY,
                                                              sizeof(*bnd->stmt->rsts),
                                                              (size_t) bnd->stmt->nb_rs, TRUE);

            if (bnd->stmt->rsts == NULL)
            {
                res = FALSE;
            }
        }

        /* create resultset as needed */

        if (res == TRUE && bnd->stmt->rsts[iter] == NULL)
        {
            OCI_CALL1
            (
                res, bnd->stmt->con, bnd->stmt,

                OCIAttrGet(bnd->buf.handle, (ub4) OCI_HTYPE_BIND, (void *) &rows, (ub4 *) NULL,
                           (ub4) OCI_ATTR_ROWS_RETURNED, bnd->stmt->con->err)
            )

            if (res == TRUE)
            {
                bnd->stmt->rsts[iter] = OCI_ResultsetCreate(bnd->stmt, rows);

                if (bnd->stmt->rsts[iter] != NULL)
                {
                    bnd->stmt->rsts[iter]->row_count = rows;
                }
            }
        }
    }

    OCI_CHECK(bnd->stmt->rsts == NULL, OCI_ERROR);

    rs = bnd->stmt->rsts[iter];

    OCI_CHECK(rs == NULL, OCI_ERROR);

    /* ok.. let's Oracle update its buffers */

    if (res == TRUE)
    {
        /* update pointers contents */

        def = &rs->defs[bnd->dynpos];

        switch (def->col.type)
        {
            case OCI_CDT_CURSOR:
            case OCI_CDT_TIMESTAMP:
            case OCI_CDT_INTERVAL:
            case OCI_CDT_LOB:
            case OCI_CDT_FILE:
            {
                *bufpp = def->buf.data[index];
                break;
            }
            default:
            {
                *bufpp = (((ub1*)def->buf.data) + (size_t) (def->col.bufsize * index));
                break;
            }
        }

        *alenp  = (ub4   *) (((ub1 *) def->buf.lens) + (size_t) ((ub4) def->buf.sizelen * index));
        *indp   = (dvoid *) (((ub1 *) def->buf.inds) + (size_t) ((ub4) sizeof(sb2)      * index));
        *piecep = (ub1    ) OCI_ONE_PIECE;
        *rcodep = (ub2   *) NULL;
    }

    return ((res == TRUE) ? OCI_CONTINUE : OCI_ERROR);
}

/* --------------------------------------------------------------------------------------------- *
 * OCI_ProcNotifyMessages
 * --------------------------------------------------------------------------------------------- */

ub4 OCI_ProcNotifyMessages
(
    void            *ctx,
    OCISubscription *subscrhp,
    void            *payload,
    ub4              paylen,
    void            *desc,
    ub4              mode
)
{
    OCI_Dequeue *dequeue = (OCI_Dequeue *) ctx;

    OCI_NOT_USED(paylen);
    OCI_NOT_USED(payload);
    OCI_NOT_USED(mode);
    OCI_NOT_USED(subscrhp);
    OCI_NOT_USED(desc);

    OCI_CHECK(dequeue == NULL, OCI_SUCCESS);
  
    dequeue->callback(dequeue);
    
    return OCI_SUCCESS;
}

/* --------------------------------------------------------------------------------------------- *
 * OCI_ProcNotifyChanges
 * --------------------------------------------------------------------------------------------- */

ub4 OCI_ProcNotifyChanges
(
    void            *ctx,
    OCISubscription *subscrhp,
    void            *payload,
    ub4              paylen,
    void            *desc,
    ub4              mode
)
{
    OCI_Subscription *sub = (OCI_Subscription *) ctx;
    boolean res           = TRUE;
    void *ostr            = NULL;
    int osize             = 0;
    ub4 type              = 0;

    OCI_NOT_USED(paylen);
    OCI_NOT_USED(payload);
    OCI_NOT_USED(mode);
    OCI_NOT_USED(subscrhp);

    OCI_CHECK(sub == NULL, OCI_SUCCESS);

    OCI_EventReset(&sub->event);

#if OCI_VERSION_COMPILE >= OCI_10_2

    /* get database that generated the notification */

    OCI_CALL3
    (
        res, sub->err,

        OCIAttrGet((dvoid *) desc, (ub4) OCI_DTYPE_CHDES, (dvoid *) &ostr, (ub4 *) &osize,
                   (ub4) OCI_ATTR_CHDES_DBNAME, sub->err)
    )

    if ((res == TRUE) && (osize > (int) sub->event.dbname_size))
    {
        /* buffer is ANSI  */

        sub->event.dbname = (dtext *) OCI_MemRealloc(sub->event.dbname,  OCI_IPC_STRING,
                                                     sizeof(dtext), (size_t) (osize + 1));

        sub->event.dbname_size = osize;
    }

    OCI_CopyString(ostr, sub->event.dbname, &osize, sizeof(char), sizeof(dtext));

    /* get notification type */

    OCI_CALL3
    (
        res, sub->err,

        OCIAttrGet((dvoid *) desc, (ub4) OCI_DTYPE_CHDES,
                   (dvoid *) &type, (ub4 *) NULL,
                   (ub4) OCI_ATTR_CHDES_NFYTYPE, sub->err)
    )

    switch(type)
    {
        case OCI_EVENT_STARTUP:
        case OCI_EVENT_SHUTDOWN:
        case OCI_EVENT_SHUTDOWN_ANY:
        {
            if (sub->type & OCI_CNT_DATABASES)
            {
                sub->event.type = type;
            }

            break;
        }
        case OCI_EVENT_DEREG:
        {
            sub->event.type = type;
            break;
        }
        case OCI_EVENT_OBJCHANGE:
        {
            if (sub->type & OCI_CNT_OBJECTS)
            {
                sub->event.type = type;
            }

            break;
        }
        default:
        {
            break;
        }
    }

    /* for object, much work to do for retrieving data */

    if (sub->event.type == OCI_EVENT_OBJCHANGE)
    {
        OCIColl *tables = 0;

        /* get collection of modified tables */

        OCI_CALL3
        (
            res, sub->err,

            OCIAttrGet((dvoid *) desc, (ub4) OCI_DTYPE_CHDES, (dvoid *) &tables,
                       (ub4   *) NULL, (ub4) OCI_ATTR_CHDES_TABLE_CHANGES,  sub->err)
        )

        if (tables != NULL)
        {
            dvoid **tbl_elem  = NULL;
            dvoid  *tbl_ind   = NULL;
            boolean tbl_exist = FALSE;
            sb4     nb_tables = 0;
            sb4     nb_rows   = 0;
            sb4     i;
            
            /* get number of tables in the collection */

            OCI_CALL3
            (
                res, sub->err,

                OCICollSize(sub->env, sub->err, tables, &nb_tables)
            )

            for (i = 0; i < nb_tables; i++)
            {
                nb_rows = 0;

                /* partial reset of the event object  */

                if (sub->event.objname != NULL)
                {
                    sub->event.objname[0] = 0;
                }

                if (sub->event.rowid != NULL)
                {
                    sub->event.rowid[0] = 0;
                }

                /* get table element */

                OCI_CALL3
                (
                    res, sub->err,

                    OCICollGetElem(sub->env, sub->err,  tables, i, &tbl_exist,
                                   (dvoid**) (dvoid*) &tbl_elem, (dvoid**) &tbl_ind)
                )

                /* get table name */

                OCI_CALL3
                (
                    res, sub->err,

                    OCIAttrGet((dvoid *) *tbl_elem,
                               (ub4) OCI_DTYPE_TABLE_CHDES,
                               (dvoid *) &ostr, (ub4 *) &osize,
                               (ub4) OCI_ATTR_CHDES_TABLE_NAME,
                               sub->err)
                )

                if(osize > (int) sub->event.objname_size)
                {
                    /* buffer is ANSI  */

                    sub->event.objname = (dtext *) OCI_MemRealloc(sub->event.objname,
                                                                  OCI_IPC_STRING, sizeof(dtext),
                                                                  (size_t) (osize + 1));

                    sub->event.objname_size = osize;
                }

                OCI_CopyString(ostr, sub->event.objname, &osize, sizeof(char), sizeof(dtext));

                /* get table modification type */

                OCI_CALL3
                (
                    res, sub->err,

                    OCIAttrGet((dvoid *) *tbl_elem, (ub4) OCI_DTYPE_TABLE_CHDES,
                               (dvoid *) &sub->event.op, (ub4*) NULL,
                               (ub4) OCI_ATTR_CHDES_TABLE_OPFLAGS, sub->err)
                )

                sub->event.op = sub->event.op & (~OCI_OPCODE_ALLROWS);
                sub->event.op = sub->event.op & (~OCI_OPCODE_ALLOPS);

                /* if requested, get row details */

                if (sub->type & OCI_CNT_ROWS)
                {
                    OCIColl *rows = 0;

                    /* get collection of modified rows */

                    OCI_CALL3
                    (
                        res, sub->err,

                        OCIAttrGet((dvoid *) *tbl_elem, (ub4) OCI_DTYPE_TABLE_CHDES,
                                   (dvoid *) &rows, (ub4 *) NULL,
                                   (ub4    ) OCI_ATTR_CHDES_TABLE_ROW_CHANGES, sub->err)
                    )

                    if (rows != NULL)
                    {
                        dvoid **row_elem  = NULL;
                        dvoid  *row_ind   = NULL;
                        boolean row_exist = FALSE;
                        sb4 j;

                        /* get number of rows */

                        OCI_CALL3
                        (
                            res, sub->err,

                            OCICollSize(sub->env, sub->err, rows, &nb_rows)
                        )

                        for (j = 0; j < nb_rows; j++)
                        {
                            /* partial reset of the event  */

                            if (sub->event.rowid != NULL)
                            {
                                sub->event.rowid[0] = 0;
                            }

                            /* get row element */

                            OCI_CALL3
                            (
                                res, sub->err,

                                OCICollGetElem(sub->env, sub->err, rows, j, &row_exist,
                                               (dvoid**) (dvoid*) &row_elem, (dvoid**) &row_ind)
                            )

                            /* get rowid  */

                            OCI_CALL3
                            (
                                res, sub->err,

                                OCIAttrGet((dvoid *) *row_elem, (ub4) OCI_DTYPE_ROW_CHDES,
                                           (dvoid *) &ostr, (ub4 *) &osize,
                                           (ub4) OCI_ATTR_CHDES_ROW_ROWID, sub->err)
                            )

                            /* get opcode  */

                            OCI_CALL3
                            (
                                res, sub->err,

                                OCIAttrGet((dvoid *) *row_elem, (ub4) OCI_DTYPE_ROW_CHDES,
                                           &sub->event.op, (ub4*) NULL,
                                           (ub4) OCI_ATTR_CHDES_ROW_OPFLAGS, sub->err)
                            )

                            if(osize > (int) sub->event.rowid_size)
                            {
                                /* buffer is ANSI  */

                                sub->event.rowid = (dtext *) OCI_MemRealloc(sub->event.rowid,
                                                                            OCI_IPC_STRING,
                                                                            sizeof(dtext),
                                                                            (size_t) (osize + 1));

                                sub->event.rowid_size = osize;
                            }

                            OCI_CopyString(ostr, sub->event.rowid, &osize,
                                           sizeof(char), sizeof(dtext));

                            sub->handler(&sub->event);
                        }
                    }
                }

                if (nb_rows == 0)
                {
                    sub->handler(&sub->event);
                }
            }
        }
    }
    else if (sub->event.type > 0)
    {
        sub->handler(&sub->event);
    }

#else

    OCI_NOT_USED(ctx);
    OCI_NOT_USED(desc);
    OCI_NOT_USED(subscrhp);

    OCI_NOT_USED(res);
    OCI_NOT_USED(type);
    OCI_NOT_USED(ostr);
    OCI_NOT_USED(osize);

#endif

    return OCI_SUCCESS;
}

/* --------------------------------------------------------------------------------------------- *
 * OCI_ProcFailOver
 * --------------------------------------------------------------------------------------------- */

sb4 OCI_ProcFailOver
(
    dvoid *svchp,
    dvoid *envhp,
    dvoid *fo_ctx,
    ub4    fo_type,
    ub4    fo_event
)
{
    OCI_Connection *cn = (OCI_Connection *) fo_ctx;
    sb4 ret = OCI_FOC_OK;

    OCI_NOT_USED(envhp);
    OCI_NOT_USED(svchp);

    if ((cn != NULL) && (cn->taf_handler != NULL))
    {
        ret = (sb4) cn->taf_handler(cn, fo_type, fo_event);
    }

    return ret;
}

/* --------------------------------------------------------------------------------------------- *
 * OCI_ProcHAEvent
 * --------------------------------------------------------------------------------------------- */

void OCI_ProcHAEvent
(
    dvoid     *evtctx,
    dvoid     *eventptr
)
{
    OCI_List       *list  = OCILib.cons;
    OCI_Item       *item  = NULL;
    OCIServer      *srvhp = NULL;

    OCI_NOT_USED(evtctx);

#if OCI_VERSION_COMPILE >= OCI_10_2

    if ((list == NULL) || (OCILib.ha_handler == NULL))
    {
        return;    
    }    
    
    if (OCILib.version_runtime >= OCI_10_2)
    {
        OCIEvent        *eventhp = (OCIEvent *) eventptr;
        OCI_Timestamp   *tmsp    = NULL;
        sword            ret;
 
        ret = OCIAttrGet((dvoid **) eventhp, (ub4) OCI_HTYPE_SERVER, (dvoid *) &srvhp,
                         (ub4 *) NULL, (ub4) OCI_ATTR_HA_SRVFIRST, OCILib.err);

        while ((ret == OCI_SUCCESS) && (srvhp != NULL))
        {
            if (list->mutex != NULL)
            {
                OCI_MutexAcquire(list->mutex);
            }

            item = list->head;

            /* for each item in the list, check the connection */

            while (item != NULL)
            {
                OCI_Connection *con  = (OCI_Connection *) item->data;        
                OCIDateTime    *dth  = NULL;

                ub4 event  = OCI_HA_STATUS_DOWN;
                ub4 source = OCI_HA_SOURCE_INSTANCE;

                if ((con != NULL) && (con->svr == srvhp))
                {
                    boolean res  = TRUE;
 
                    /* get event timestamp */

                    OCI_CALL2
                    (
                        res, con,

                        OCIAttrGet((dvoid **) eventhp, (ub4) OCI_HTYPE_SERVER, (dvoid *) &dth,
                                   (ub4 *) NULL,  (ub4) OCI_ATTR_HA_TIMESTAMP, con->err)

                    )

                    if (res == TRUE)
                    {
                        res = (OCI_TimestampInit(con, &tmsp, dth, OCI_TIMESTAMP) != NULL);
                    }

                    /* get status */

                    if (res == TRUE)
                    {
                        OCI_CALL2
                        (
                            res, con,

                            OCIAttrGet((dvoid **) eventhp, (ub4) OCI_HTYPE_SERVER, (dvoid *) &event,
                                       (ub4 *) NULL,  (ub4) OCI_ATTR_HA_STATUS, con->err)

                        )
                    }

                    /* get source */

                    if (res == TRUE)
                    {
                        OCI_CALL2
                        (
                            res, con,

                            OCIAttrGet((dvoid **) eventhp, (ub4) OCI_HTYPE_SERVER, (dvoid *) &source,
                                       (ub4 *) NULL,  (ub4) OCI_ATTR_HA_SOURCE, con->err)

                        )
                    }

                    /* on success, call the user callback */

                    if (res == TRUE)
                    {
                        OCILib.ha_handler(con, (unsigned int) source, (unsigned int) event, tmsp);
                    }

                    item = item->next;
                }
            }

            if (list->mutex != NULL)
            {
                OCI_MutexRelease(list->mutex);
            }

            ret = OCIAttrGet((dvoid **) srvhp, (ub4) OCI_HTYPE_SERVER, (dvoid *) &srvhp,
                             (ub4 *) NULL,  (ub4) OCI_ATTR_HA_SRVNEXT, OCILib.err);

        }

        /* free temporary timestamp object */

        if (tmsp != NULL)
        {
            tmsp->hstate = OCI_OBJECT_FETCHED_DIRTY;
            OCI_TimestampFree(tmsp);
        }
    }

#else

    OCI_NOT_USED(eventptr);
    OCI_NOT_USED(list);
    OCI_NOT_USED(item);
    OCI_NOT_USED(srvhp);

#endif

}
