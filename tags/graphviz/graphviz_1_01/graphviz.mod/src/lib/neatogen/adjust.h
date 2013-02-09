/* $Id: adjust.h,v 1.7 2006/05/11 21:47:36 erg Exp $ $Revision: 1.7 $ */
/* vim:set shiftwidth=4 ts=8: */

/**********************************************************
*      This software is part of the graphviz package      *
*                http://www.graphviz.org/                 *
*                                                         *
*            Copyright (c) 1994-2004 AT&T Corp.           *
*                and is licensed under the                *
*            Common Public License, Version 1.0           *
*                      by AT&T Corp.                      *
*                                                         *
*        Information and Software Systems Research        *
*              AT&T Research, Florham Park NJ             *
**********************************************************/



#ifndef ADJUST_H
#define ADJUST_H

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    AM_NONE, AM_VOR, AM_COMPRESS,
    AM_SCALE, AM_NSCALE, AM_SCALEXY, AM_PUSH, AM_PUSHPULL,
    AM_ORTHO, AM_ORTHO_YX, AM_ORTHOXY, AM_ORTHOYX,
    AM_PORTHO, AM_PORTHO_YX, AM_PORTHOXY, AM_PORTHOYX,
    AM_VPSC, AM_IPSEP
} adjust_mode;

typedef struct {
    adjust_mode mode;
    char *attrib;
    char *print;
} adjust_data;

    extern double expFactor(graph_t * G);
    extern int adjustNodes(graph_t * G);
    extern void normalize(graph_t * g);
    extern int removeOverlap(graph_t * G);
    extern int removeOverlapAs(graph_t*, char*);
    extern int cAdjust(graph_t *, int);
    extern int scAdjust(graph_t *, int);
    extern adjust_data *graphAdjustMode(graph_t *G);

#ifdef __cplusplus
}
#endif
#endif
