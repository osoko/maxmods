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
 * $Id: oci_api.h, v 2.5.1 09:05 24/07/2008 Vince $
 * ------------------------------------------------------------------------ */

#ifndef OCILIB_OCI_API_H_INCLUDED 
#define OCILIB_OCI_API_H_INCLUDED 

#include "oci_def.h"

/* oci api protoptypes */

typedef sword (*OCIENVCREATE) 
(
    OCIEnv **envhpp,
    ub4 mode, 
    void *ctxp,
    void *(*malocfp)(void *ctxp, size_t size),
    void *(*ralocfp)(void *ctxp, void *memptr, size_t newsize),
    void  (*mfreefp)(void *ctxp, void *memptr),
    size_t xtramem_sz,
    void **usrmempp
);

typedef sword (*OCIHANDLEALLOC) 
(
    const void *parenth,
    void **hndlpp,
    const ub4 type,
    const size_t xtramem_sz,
    void **usrmempp
);

typedef sword (*OCIHANDLEFREE) 
(
    void *hndlp, 
    const ub4 type
);


typedef sword (*OCIDESCRIPTORALLOC)
(
    const void *parenth, 
    void **descpp, 
    const ub4 type, 
    const size_t xtramem_sz,
    void **usrmempp
);

typedef sword (*OCIDESCRIPTORFREE)
(
    void *descp, 
    const ub4 type
);

typedef sword (*OCIENVINIT) 
(
    OCIEnv **envp, ub4 mode, 
    size_t xtramem_sz,
    void **usrmempp
);

typedef sword (*OCISERVERATTACH) 
(
    OCIServer *srvhp, 
    OCIError *errhp,
    const OraText *dblink,
    sb4 dblink_len, 
    ub4 mode
);

typedef sword (*OCISERVERDETACH) 
(
    OCIServer *srvhp,
    OCIError *errhp, 
    ub4 mode
);

typedef sword (*OCISESSIONBEGIN)  
(
    OCISvcCtx *svchp,
    OCIError *errhp,
    OCISession *usrhp,
    ub4 credt,
    ub4 mode
);

typedef sword (*OCISESSIONEND)  
(
    OCISvcCtx *svchp, 
    OCIError *errhp, 
    OCISession *usrhp, 
    ub4 mode
);

typedef sword (*OCIPASSWORDCHANGE)
(
    OCISvcCtx *svchp, 
    OCIError *errhp, 
    CONST OraText *user_name, 
    ub4 usernm_len, 
    CONST OraText *opasswd,
    ub4 opasswd_len, 
    CONST OraText *npasswd,
    ub4 npasswd_len,
    ub4 mode
);

typedef sword (*OCISTMTPREPARE) 
(
    OCIStmt *stmtp,
    OCIError *errhp, 
    const OraText *stmt,
    ub4 stmt_len, 
    ub4 language,
    ub4 mode
);

typedef sword (*OCIBINDBYPOS) 
(
    OCIStmt *stmtp,
    OCIBind **bindp,
    OCIError *errhp,
    ub4 position, 
    void *valuep, 
    sb4 value_sz,
    ub2 dty, 
    void *indp, 
    ub2 *alenp, 
    ub2 *rcodep,
    ub4 maxarr_len, 
    ub4 *curelep, 
    ub4 mode
);

typedef sword (*OCIBINDBYNAME)   
(
    OCIStmt *stmtp, 
    OCIBind **bindp, 
    OCIError *errhp,
    const OraText *placeholder, 
    sb4 placeh_len, 
    void *valuep, 
    sb4 value_sz, 
    ub2 dty, 
    void *indp, 
    ub2 *alenp, 
    ub2 *rcodep, 
    ub4 maxarr_len, 
    ub4 *curelep, 
    ub4 mode
);

typedef sword (*OCIBINDDYNAMIC)
(
    OCIBind *bindp, 
    OCIError *errhp, 
    dvoid *ictxp,                         
    sb4 (*icbfp)(dvoid *ictxp, OCIBind *bindp, ub4 iter,  ub4 index, 
                 dvoid **bufpp, ub4 *alenp, ub1 *piecep, dvoid **indp),
    dvoid *octxp,                          
    sb4 (*ocbfp)(dvoid *octxp, OCIBind *bindp, ub4 iter, ub4 index, 
                 dvoid **bufpp, ub4 **alenp,   ub1 *piecep, dvoid **indp,
                 ub2 **rcodep)
 );

typedef sword (*OCIBINDOBJECT)
(
    OCIBind *bindp, 
    OCIError *errhp, 
    CONST OCIType *type, 
    dvoid **pgvpp, 
    ub4 *pvszsp,
    dvoid **indpp, 
    ub4 *indszp
);

typedef sword (*OCISTMTGETPIECEINFO)   
(
    OCIStmt *stmtp,
    OCIError *errhp, 
    void **hndlpp,
    ub4 *typep,
    ub1 *in_outp, 
    ub4 *iterp, 
    ub4 *idxp, 
    ub1 *piecep
);

typedef sword (*OCISTMTSETPIECEINFO) 
(
    void *hndlp, 
    ub4 type, 
    OCIError *errhp, 
    const void *bufp, 
    ub4 *alenp, 
    ub1 piece, 
    const void *indp, 
    ub2 *rcodep
);

typedef sword (*OCISTMTEXECUTE) 
(
    OCISvcCtx *svchp,
    OCIStmt *stmtp,
    OCIError *errhp, 
    ub4 iters, 
    ub4 rowoff,
    const OCISnapshot *snap_in, 
    OCISnapshot *snap_out,
    ub4 mode
);

typedef sword (*OCIDEFINEBYPOS) 
(
    OCIStmt *stmtp, 
    OCIDefine **defnp, 
    OCIError *errhp,
    ub4 position, 
    void *valuep, 
    sb4 value_sz, 
    ub2 dty,
    void *indp, 
    ub2 *rlenp, 
    ub2 *rcodep, 
    ub4 mode
);

typedef sword (*OCIDEFINEOBJECT)
(
    OCIDefine *defnp,
    OCIError *errhp,
    CONST OCIType *type,
    dvoid **pgvpp,
    ub4 *pvszsp,
    dvoid **indpp,
    ub4 *indszp 
);

typedef sword (*OCISTMTFETCH ) 
(
    OCIStmt *stmtp, 
    OCIError *errhp,
    ub4 nrows, 
    ub2 orientation, 
    ub4 mode
);

typedef sword (*OCIPARAMGET)
(
    const void *hndlp,
    ub4 htype,
    OCIError *errhp, 
    void **parmdpp, 
    ub4 pos
);

typedef sword (*OCIPARAMSET)
(
    void *hdlp, 
    ub4 htyp,
    OCIError *errhp, 
    const void *dscp,
    ub4 dtyp, 
    ub4 pos
);

typedef sword (*OCITRANSSTART) 
(
    OCISvcCtx *svchp,
    OCIError *errhp, 
    uword timeout,
    ub4 flags
);

typedef sword (*OCITRANSDETACH)
(
    OCISvcCtx    *svchp, 
    OCIError     *errhp,
    ub4          flags
);

typedef sword (*OCITRANSPREPARE)
(
    OCISvcCtx    *svchp, 
    OCIError     *errhp,
    ub4          flags
);

typedef sword (*OCITRANSFORGET)
(
    OCISvcCtx     *svchp, 
    OCIError      *errhp,
    ub4           flags
);

typedef sword (*OCITRANSCOMMIT) 
(
    OCISvcCtx *svchp, 
    OCIError *errhp,
    ub4 flags
);

typedef sword (*OCITRANSROLLBACK)
(
    OCISvcCtx *svchp, 
    OCIError *errhp,
    ub4 flags
);

typedef sword (*OCIERRORGET) 
(
    void *hndlp,
    ub4 recordno,
    OraText *sqlstate,
    sb4 *errcodep,
    OraText *bufp,
    ub4 bufsiz,
    ub4 type
);

typedef sword (*OCILOBCREATETEMPORARY)
(
    OCISvcCtx          *svchp,
    OCIError           *errhp,
    OCILobLocator      *locp,
    ub2                 csid,
    ub1                 csfrm,
    ub1                 lobtype,
    boolean             cache,
    OCIDuration         duration
);

typedef sword (*OCILOBFREETEMPORARY)
(
    OCISvcCtx *svchp,
    OCIError *errhp,
    OCILobLocator *locp
);

typedef sword (*OCILOBISTEMPORARY)
(
    OCIEnv *envp,
    OCIError *errhp,
    OCILobLocator *locp,
    boolean *is_temporary
);

typedef sword (*OCILOBAPPEND)
(
    OCISvcCtx *svchp, 
    OCIError *errhp, 
    OCILobLocator *dst_locp,
    OCILobLocator *src_locp
);

typedef sword (*OCILOBCOPY)
(
    OCISvcCtx *svchp,
    OCIError *errhp, 
    OCILobLocator *dst_locp,
    OCILobLocator *src_locp, 
    ub4 amount,
    ub4 dst_offset, 
    ub4 src_offset
);

typedef sword (*OCILOBREAD)  
(
    OCISvcCtx *svchp,
    OCIError *errhp,
    OCILobLocator *locp,
    ub4 *amtp, 
    ub4 offset, 
    void *bufp,
    ub4 bufl, 
    void *ctxp, 
    sb4 (*cbfp)(void *ctxp, const void *bufp, ub4 len, ub1 piece),
    ub2 csid,
    ub1 csfrm
);

typedef sword (*OCILOBTRIM) 
(
    OCISvcCtx *svchp,
    OCIError *errhp, 
    OCILobLocator *locp,
    ub4 newlen
);

typedef sword (*OCILOBERASE)
(
    OCISvcCtx *svchp, 
    OCIError *errhp, 
    OCILobLocator *locp,
    ub4 *amount, 
    ub4 offset
);

typedef sword (*OCILOBWRITE)  
(
    OCISvcCtx *svchp, 
    OCIError *errhp,
    OCILobLocator *locp,
    ub4 *amtp, 
    ub4 offset, 
    void *bufp, 
    ub4 buflen, 
    ub1 piece,
    void *ctxp, 
    sb4 (*cbfp)(void *ctxp, void *bufp, ub4 *len,  ub1 *piece),
    ub2 csid,
    ub1 csfrm
);

typedef sword (*OCILOBGETLENGTH)  
(
    OCISvcCtx *svchp, 
    OCIError *errhp, 
    OCILobLocator *locp,
    ub4 *lenp
);

typedef sword (*OCILOBOPEN)
( 
    OCISvcCtx *svchp,
    OCIError *errhp,
    OCILobLocator *locp,
    ub1 mode
);

typedef sword (*OCILOBCLOSE)
(
    OCISvcCtx *svchp,
    OCIError *errhp,
    OCILobLocator *locp 
);

typedef sword (*OCILOBLOCATORASSIGN)
(
    OCISvcCtx *svchp, 
    OCIError *errhp, 
    CONST OCILobLocator *src_locp, 
    OCILobLocator **dst_locpp
);

typedef sword (*OCILOBASSIGN)
(
    OCIEnv *envhp, 
    OCIError *errhp, 
    CONST OCILobLocator *src_locp, 
    OCILobLocator **dst_locpp
);

typedef sword (*OCILOBCOPY2)
(
    OCISvcCtx *svchp, 
    OCIError *errhp, 
    OCILobLocator *dst_locp,                
    OCILobLocator *src_locp,
    oraub8 amount, 
    oraub8 dst_offset, 
    oraub8 src_offset
);

typedef sword (*OCILOBERASE2)
(
    OCISvcCtx *svchp, 
    OCIError *errhp, 
    OCILobLocator *locp,
    oraub8 *amount, 
    oraub8 offset
);

typedef sword (*OCILOBGETLENGTH2)
(
    OCISvcCtx *svchp, 
    OCIError *errhp, 
    OCILobLocator *locp, 
    oraub8 *lenp
);

typedef sword (*OCILOBLOADFROMFILE2)
(
    OCISvcCtx *svchp, 
    OCIError *errhp, 
    OCILobLocator *dst_locp,
    OCILobLocator *src_filep, 
    oraub8 amount, 
    oraub8 dst_offset, 
    oraub8 src_offset
);

typedef sword (*OCILOBREAD2)
(
    OCISvcCtx *svchp, 
    OCIError *errhp, 
    OCILobLocator *locp,
    oraub8 *byte_amtp, 
    oraub8 *char_amtp, 
    oraub8 offset,
    dvoid *bufp, 
    oraub8 bufl,
    ub1 piece, 
    dvoid *ctxp,
    sb4 (*cbfp)(dvoid *ctxp, CONST dvoid *bufp, oraub8 len, ub1 piece, 
                dvoid **changed_bufpp, oraub8 *changed_lenp),
    ub2 csid, 
    ub1 csfrm
);

typedef sword (*OCILOBTRIM2) 
(
    OCISvcCtx *svchp, 
    OCIError *errhp, 
    OCILobLocator *locp,
    oraub8 newlen
);

typedef sword (*OCILOBWRITE2) 
(
    OCISvcCtx *svchp, 
    OCIError *errhp, 
    OCILobLocator *locp,
    oraub8 *byte_amtp, 
    oraub8 *char_amtp, 
    oraub8 offset,
    dvoid *bufp, 
    oraub8 buflen, 
    ub1 piece, 
    dvoid *ctxp, 
    sb4 (*cbfp)(dvoid *ctxp, CONST dvoid *bufp, oraub8 len, ub1 piece, 
                dvoid **changed_bufpp, oraub8 *changed_lenp),
    ub2 csid, 
    ub1 csfrm
);

typedef sword (*OCILOBWRITEAPPEND2)
(
    OCISvcCtx *svchp, 
    OCIError *errhp, 
    OCILobLocator *lobp,
    oraub8 *byte_amtp, 
    oraub8 *char_amtp, 
    dvoid *bufp,
    oraub8 bufl, 
    ub1 piece, 
    dvoid *ctxp,
    sb4 (*cbfp)(dvoid *ctxp, dvoid *bufp, oraub8 *lenp, ub1 *piece, 
                dvoid **changed_bufpp, oraub8 *changed_lenp),
    ub2 csid, 
    ub1 csfrm
);

typedef sword (*OCILOBFILEOPEN) 
(
    OCISvcCtx *svchp, 
    OCIError *errhp, 
    OCILobLocator *filep,
    ub1 mode
);

typedef sword (*OCILOBFILECLOSE)
(
    OCISvcCtx *svchp, 
    OCIError *errhp, 
    OCILobLocator *filep
);

typedef sword (*OCILOBFILECLOSEALL) 
(
    OCISvcCtx *svchp, 
    OCIError *errhp
);

typedef sword (*OCILOBFILEISOPEN) 
(
    OCISvcCtx *svchp, 
    OCIError *errhp, 
    OCILobLocator *filep,
    boolean *flag
);


typedef sword (*OCILOBFILEEXISTS) 
(
    OCISvcCtx *svchp, 
    OCIError *errhp, 
    OCILobLocator *filep,
    boolean *flag
);

typedef sword (*OCILOBFIELGETNAME)
(
    OCIEnv *envhp, 
    OCIError *errhp, 
    CONST OCILobLocator *filep, 
    OraText *dir_alias, 
    ub2 *d_length, 
    OraText *filename, 
    ub2 *f_length
);

typedef sword (*OCILOBFILESETNAME)
(
    OCIEnv *envhp, OCIError *errhp, 
    OCILobLocator **filepp, 
    CONST OraText *dir_alias, 
    ub2 d_length, 
    CONST OraText *filename, 
    ub2 f_length
);

typedef sword (*OCILOBLOADFROMFILE)
(
    OCISvcCtx *svchp, 
    OCIError *errhp, 
    OCILobLocator *dst_locp,
    OCILobLocator *src_filep, 
    ub4 amount, 
    ub4 dst_offset, 
    ub4 src_offset
);

typedef sword (*OCILOBWRITEAPPEND)
(
    OCISvcCtx *svchp, 
    OCIError *errhp, 
    OCILobLocator *lobp,
    ub4 *amtp, 
    dvoid *bufp, 
    ub4 bufl, 
    ub1 piece, 
    dvoid *ctxp,
    sb4 (*cbfp)(void *ctxp, void *bufp, ub4 *len,  ub1 *piece),
    ub2 csid, 
    ub1 csfrm
);

typedef sword (*OCILOBISEQUAL)
(
    OCIEnv *envhp, 
    CONST OCILobLocator *x, 
    CONST OCILobLocator *y, 
    boolean *is_equal
);

typedef sword (*OCISERVERVERSION)  
(
    void *hndlp, 
    OCIError *errhp,
    OraText *bufp, 
    ub4 bufsz,
    ub1 hndltype
);

typedef sword (*OCIBREAK)
(    
    dvoid *hndlp, 
    OCIError *errhp  
);

typedef sword (*OCIATTRGET) 
(
    const void *trgthndlp,
    ub4 trghndltyp, 
    void *attributep, 
    ub4 *sizep, ub4 attrtype, 
    OCIError *errhp
);

typedef sword (*OCIATTRSET) 
(
    void *trgthndlp,
    ub4 trghndltyp, 
    void *attributep,
    ub4 size, 
    ub4 attrtype, 
    OCIError *errhp
);

typedef sword (*OCIDATEASSIGN)
(
    OCIError *err, 
    CONST OCIDate *from, 
    OCIDate *to 
);

typedef sword (*OCIDATETOTEXT)
( 
    OCIError *err, 
    CONST OCIDate *date, 
    CONST text *fmt,
    ub1 fmt_length, 
    CONST text *lang_name,
    ub4 lang_length, 
    ub4 *buf_size,
    text *buf 
);

typedef sword (*OCIDATEFROMTEXT)
( 
    OCIError *err,
    CONST text *date_str, 
    ub4 d_str_length, 
    CONST text *fmt,
    ub1 fmt_length, 
    CONST text *lang_name, 
    ub4 lang_length, 
    OCIDate *date  
);

typedef sword (*OCIDATECOMPARE)
(  
    OCIError *err, 
    CONST OCIDate *date1, 
    CONST OCIDate *date2, 
    sword *result  
);

typedef sword (*OCIDATEADDMONTHS)
(   
    OCIError *err, 
    CONST OCIDate *date, 
    sb4 num_months,
    OCIDate *result   
);

typedef sword (*OCIDATEADDDAYS)
( 
    OCIError *err,
    CONST OCIDate *date, 
    sb4 num_days,
    OCIDate *result  
);

typedef sword (*OCIDATELASTDAY)
(  
    OCIError *err, 
    CONST OCIDate *date, 
    OCIDate *last_day 
);

typedef sword (*OCIDATEDAYSBETWEEN)
(  
    OCIError *err,
    CONST OCIDate *date1, 
    CONST OCIDate *date2, 
    sb4 *num_days  
);

typedef sword (*OCIDATEZONETOZONE)
(  
    OCIError *err, 
    CONST OCIDate *date1,
    CONST text *zon1,
    ub4 zon1_length,
    CONST text *zon2,
    ub4 zon2_length,
    OCIDate *date2 
);

typedef sword (*OCIDATENEXTDAY)
(   
    OCIError *err,
    CONST OCIDate *date,
    CONST text *day_p, 
    ub4 day_length,
    OCIDate *next_day  
);

typedef sword (*OCIDATECHECK)
(   
    OCIError *err,
    CONST OCIDate *date, 
    uword *valid  
);

typedef sword (*OCIDATESYSDATE)
(   
    OCIError *err,
    OCIDate *sys_date  
);

typedef sword (*OCIDESCRIBEANY)
(
    OCISvcCtx *svchp, 
    OCIError *errhp, 
    dvoid *objptr,
    ub4 objnm_len, 
    ub1 objptr_typ, 
    ub1 info_level,
    ub1 objtyp, 
    OCIDescribe *dschp
);

typedef sword (*OCIINTERVALASSIGN) 
( 
    dvoid *hndl,
    OCIError *err,
    CONST OCIInterval *inpinter,
    OCIInterval *outinter
);

typedef sword (*OCIINTERVALCHECK) 
(
    dvoid *hndl,
    OCIError *err,
    CONST OCIInterval *interval,
    ub4 *valid 
);

typedef sword (*OCIINTERVALCOMPARE)
( 
    dvoid *hndl,
    OCIError *err,
    OCIInterval *inter1,
    OCIInterval *inter2,
    sword *result 
);

typedef sword (*OCIINTERVALTOTEXT) 
( 
    dvoid *hndl,
    OCIError *err,
    CONST OCIInterval *interval,
    ub1 lfprec,
    ub1 fsprec,
    OraText *buffer,
    size_t buflen,
    size_t *resultlen 
);

typedef sword (*OCIINTERVALFROMTEXT)
(
    dvoid *hndl,
    OCIError *err,
    CONST OraText *inpstring,
    size_t str_len,
    OCIInterval *result
);

typedef sword (*OCIINTERVALFROMTZ)
(
    dvoid *hndl,
    OCIError *err,
    CONST oratext *inpstring,
    size_t str_len,
    OCIInterval *result 
) ;

typedef sword (*OCIINTERVALGETDAYSECOND) 
(
    dvoid *hndl,
    OCIError *err,
    sb4 *dy,
    sb4 *hr,
    sb4 *mm,
    sb4 *ss,
    sb4 *fsec,
    CONST OCIInterval *interval 
);

typedef sword (*OCIINTERVALGETYEARMONTH) 
( 
    dvoid *hndl,
    OCIError *err,
    sb4 *yr,
    sb4 *mnth,
    CONST OCIInterval *interval 
);

typedef sword (*OCIINTERVALSETDAYSECOND) 
( 
    dvoid *hndl,
    OCIError *err,
    sb4 dy,
    sb4 hr,
    sb4 mm,
    sb4 ss,
    sb4 fsec,
    OCIInterval *result 
);

typedef sword (*OCIINTERVALSETYEARMONTH)
( 
    dvoid *hndl,
    OCIError *err,
    sb4 yr,
    sb4 mnth,
    OCIInterval *result 
);

typedef sword (*OCIINTERVALADD) 
( 
    dvoid *hndl,
    OCIError *err,
    OCIInterval *addend1,
    OCIInterval *addend2,
    OCIInterval *result 
);

typedef sword (*OCIINTERVALSUBTRACT)
( 
    dvoid *hndl,
    OCIError *err,
    OCIInterval *minuend,
    OCIInterval *subtrahend,
    OCIInterval *result
);

typedef sword (*OCIDATETIMEASSIGN) 
(
    dvoid *hndl,
    OCIError *err,
    CONST OCIDateTime *from,
    OCIDateTime *to 
);

typedef sword (*OCIDATETIMECHECK) 
(
    dvoid *hndl,
    OCIError *err,
    CONST OCIDateTime *date,
    ub4 *valid 
);

typedef sword (*OCIDATETIMECOMPARE) 
( 
    dvoid *hndl,
    OCIError *err,
    CONST OCIDateTime *date1,
    CONST OCIDateTime *date2,
    sword *result 
);

typedef sword (*OCIDATETIMECONSTRUCT) 
( 
    dvoid *hndl,
    OCIError *err,
    OCIDateTime *datetime,
    sb2 year,
    ub1 month,
    ub1 day,
    ub1 hour,
    ub1 min,
    ub1 sec,
    ub4 fsec,
    OraText *timezone,
    size_t timezone_length
);

typedef sword (*OCIDATETIMECONVERT) 
(
    dvoid *hndl,
    OCIError *err,
    OCIDateTime *indate,
    OCIDateTime *outdate
);

typedef sword (*OCIDATETIMEFROMARRAY)
( 
    dvoid *hndl,
    OCIError *err,
    CONST ub1 *inarray,
    ub4 *len,
    ub1 type,
    OCIDateTime *datetime,
    CONST OCIInterval *reftz,
    ub1 fsprec 
);

typedef sword (*OCIDATETIMETOARRAY) 
( 
    dvoid *hndl,
    OCIError *err,
    CONST OCIDateTime *datetime,
    CONST OCIInterval *reftz,
    ub1 *outarray,
    ub4 *len,
    ub1 fsprec 
);

typedef sword (*OCIDATETIMEFROMTEXT) 
( 	
    dvoid *hndl,
    OCIError *err,
    CONST OraText *date_str,
    size_t dstr_length,
    CONST OraText *fmt,
    ub1 fmt_length,
    CONST OraText *lang_name,
    size_t lang_length,
    OCIDateTime *datetime 
);

typedef sword (*OCIDATETIMETOTEXT)
(
    dvoid *hndl,
    OCIError *err,
    CONST OCIDateTime *date,
    CONST OraText *fmt,
    ub1 fmt_length,
    ub1 fsprec,
    CONST OraText *lang_name,
    size_t lang_length,
    ub4 *buf_size,
    OraText *buf 
);

typedef sword (*OCIDATETIMEGETDATE) 
( 
    dvoid *hndl,
    OCIError *err,
    CONST OCIDateTime *datetime,
    sb2 *year,
    ub1 *month,
    ub1 *day
);

typedef sword (*OCIDATETIMEGETTIME) 
( 
    dvoid *hndl,
    OCIError *err,
    OCIDateTime *datetime,
    ub1 *hour,
    ub1 *min,
    ub1 *sec,
    ub4 *fsec 
);

typedef sword (*OCIDATETIMEGETTIMEZONENAME)
(
    dvoid *hndl,
    OCIError *err,
    CONST OCIDateTime *datetime,
    ub1 *buf,
    ub4 *buflen
);

typedef sword (*OCIDATETIMEGETTIMEZONEOFFSET) 
(
    dvoid *hndl,
    OCIError *err,
    CONST OCIDateTime *datetime,
    sb1 *hour,
    sb1 *min
);

typedef sword (*OCIDATETIMEINTERVALADD)
( 
    dvoid *hndl,
    OCIError *err,
    OCIDateTime *datetime,
    OCIInterval *inter,
    OCIDateTime *outdatetime 
);

typedef sword (*OCIDATETIMEINTERVALSUB) 
(
    dvoid *hndl,
    OCIError *err,
    OCIDateTime *datetime,
    OCIInterval *inter,
    OCIDateTime *outdatetime
);

typedef sword (*OCIDATETIMESUBTRACT) 
(	
    dvoid *hndl,
    OCIError *err,
    OCIDateTime *indate1,
    OCIDateTime *indate2,
    OCIInterval *inter 
);

typedef sword (*OCIDATETIMESYSTIMESTAMP)
(
    dvoid *hndl,
    OCIError *err,
    OCIDateTime *sys_date
);

/* Oracle 10g test */

typedef void (*OCICLIENTVERSION)
(
    sword *major_version,
    sword *minor_version,
    sword *update_num,
    sword *patch_num,
    sword *port_update_num
);

/* Oracle 11g test */

typedef sword (*OCIARRAYDESCRIPTORFREE)
(
    void  **descp, 
    const ub4 type
);

typedef sword (*OCITYPEBYNAME)
( 
    OCIEnv *env,
    OCIError *err, 
    CONST OCISvcCtx *svc, 
    CONST text *schema_name,
    ub4 s_length, 
    CONST text *type_name, 
    ub4 t_length, 
    CONST text *version_name,
    ub4 v_length,
    OCIDuration pin_duration,
    OCITypeGetOpt get_option,
    OCIType **tdo
);

typedef sword (*OCIOBJECTNEW)
(
    OCIEnv *env,
    OCIError *err,
    CONST OCISvcCtx *svc,
    OCITypeCode typecode,
    OCIType *tdo,
    dvoid *table,
    OCIDuration duration,
    boolean value,
    dvoid **instance 
);

typedef sword (*OCIOBJECTFREE)
(
    OCIEnv *env,
    OCIError *err,
    dvoid *instance,
    ub2 flags 
);

typedef sword (*OCIOBJECTGETATTR)
( 
    OCIEnv *env,
    OCIError *err,
    dvoid *instance,
    dvoid *null_struct,
    struct OCIType *tdo,
    CONST text **names,
    CONST ub4 *lengths,
    CONST ub4 name_count,
    CONST ub4 *indexes,
    CONST ub4 index_count,
    OCIInd *attr_null_status,
    dvoid **attr_null_struct,
    dvoid **attr_value,
    struct OCIType **attr_tdo 
);

typedef sword (*OCIOBJECTSETATTR)
(    
    OCIEnv *env, 
    OCIError *err, 
    dvoid *instance, 
    dvoid *null_struct, 
    struct OCIType *tdo, 
    CONST text **names, 
    CONST ub4 *lengths, 
    CONST ub4 name_count,
    CONST ub4 *indexes, 
    CONST ub4 index_count, 
    CONST OCIInd null_status, 
    CONST dvoid *attr_null_struct,
    CONST dvoid *attr_value    
);

typedef sword (*OCINUMBERTOINT)
(
    OCIError *err, 
    CONST OCINumber *number,
    uword rsl_length, 
    uword rsl_flag, 
    dvoid *rsl    
);
    
typedef sword (*OCINUMBERFROMINT)
(
    OCIError *err, 
    CONST dvoid *inum, 
    uword inum_length,
    uword inum_s_flag, 
    OCINumber *number   
);

typedef sword (*OCINUMBERFROMREAL)
(
    OCIError *err, 
    CONST dvoid *rnum,
    uword rnum_length, 
    OCINumber *number    
);

typedef sword (*OCINUMBERTOREAL)  
(
    OCIError *err, 
    CONST OCINumber *number,
    uword rsl_length, 
    dvoid *rsl    
);

typedef sword (*OCINUMBERTOTEXT)  
(
    OCIError *err,
    CONST OCINumber *number, 
    CONST text *fmt,
    ub4 fmt_length,
    CONST text *nls_params,
    ub4 nls_p_length,
    ub4 *buf_size, 
    text *buf  
);

typedef oratext * (*OCISTRINGPTR)
(    
    OCIEnv *env, 
    CONST OCIString *vs
);

typedef sword (*OCISTRINGASSIGNTEXT)
(
    OCIEnv *env, 
    OCIError *err, 
    CONST oratext *rhs,
    ub4 rhs_len, 
    OCIString **lhs
);

typedef ub1 * (*OCIRAWPTR)
(    
    OCIEnv * env, 
    CONST OCIRaw *raw    
);

typedef sword (*OCIRAWASSIGNBYTES)
(    
    OCIEnv *env, 
    OCIError *err, 
    CONST ub1 *rhs,
    ub4 rhs_len, 
    OCIRaw **lhs    
);

typedef sword (*OCIRAWALLOCSIZE)
(    
    OCIEnv *env, 
    OCIError *err, 
    CONST OCIRaw *raw,
    ub4 *allocsize    
);

typedef void (*OCITHREADPROCESSINIT)();

typedef sword (*OCITHREADINIT)
(
    dvoid *hndl, 
    OCIError *err
);

typedef sword (*OCITHREADTERM)
(
    dvoid *hndl, 
    OCIError *err
);

typedef sword (*OCITHREADIDINIT)
(
    dvoid *hndl, 
    OCIError *err, 
    OCIThreadId **tid
);

typedef sword (*OCITHREADIDDESTROY)
(
    dvoid *hndl, 
    OCIError *err, 
    OCIThreadId **tid
);

typedef sword (*OCITHREADHNDINIT)
(
    dvoid *hndl, 
    OCIError *err, 
    OCIThreadHandle **thnd
);

typedef sword (*OCITHREADHNDDESTROY)
(
    dvoid *hndl, 
    OCIError *err, 
    OCIThreadHandle **thnd
);

typedef sword (*OCITHREADCREATE)
(
    dvoid *hndl, 
    OCIError *err,
    void (*start)(dvoid *), 
    dvoid *arg,
    OCIThreadId *tid, 
    OCIThreadHandle *tHnd
);

typedef sword (*OCITHREADJOIN)
(
    dvoid *hndl, 
    OCIError *err, 
    OCIThreadHandle *tHnd
);

typedef sword (*OCITHREADCLOSE)
(
    dvoid *hndl, 
    OCIError *err, 
    OCIThreadHandle *tHnd
);

typedef sword (*OCITHREADMUTEXINIT)
(
    dvoid *hndl, 
    OCIError *err,  
    OCIThreadMutex **mutex
); 

typedef sword (*OCITHREADMUTEXDESTROY)
(
    dvoid *hndl, 
    OCIError *err, 
    OCIThreadMutex **mutex
);

typedef sword (*OCITHREADMUTEXACQUIRE)
(
    dvoid *hndl, 
    OCIError *err,
    OCIThreadMutex *mutex
);

typedef sword (*OCITHREADMUTEXRELEASE)
(
    dvoid *hndl, 
    OCIError *err,
    OCIThreadMutex *mutex
);

typedef sword (*OCITHREADKEYINIT)
(
    dvoid *hndl, 
    OCIError *err, 
    OCIThreadKey **key,
    void (*destFn) (void *)
); 

typedef sword (*OCITHREADKEYDESTROY)
(
    dvoid *hndl, 
    OCIError *err, 
    OCIThreadKey **key
);

typedef sword (*OCITHREADKEYSET)
(
    dvoid *hndl, 
    OCIError *err, 
    OCIThreadKey *key,
    dvoid **pValue
);

typedef sword (*OCITHREADKEYGET)
(
    dvoid *hndl, 
    OCIError *err, 
    OCIThreadKey *key,
    dvoid *value
);

typedef sword (*OCICONNECTIONPOOLCREATE)
(
    OCIEnv *envhp, 
    OCIError *errhp, 
    OCICPool *poolhp,
    OraText **poolName, 
    sb4 *poolNameLen,  
    CONST OraText *dblink, 
    sb4 dblinkLen,
    ub4 connMin, 
    ub4 connMax, 
    ub4 connIncr,
    CONST OraText *poolUserName, 
    sb4 poolUserLen,
    CONST OraText *poolPassword, 
    sb4 poolPassLen,
    ub4 mode
);

typedef sword (*OCICONNECTIONPOOLDESTROY)
(
    OCICPool *poolhp,
    OCIError *errhp, 
    ub4 mode
);


#endif    /* OCILIB_OCI_API_H_INCLUDED */

