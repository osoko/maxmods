/* $Id: usershape.h,v 1.4 2006/06/20 14:36:10 ellson Exp $ $Revision: 1.4 $ */
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

#ifndef USERSHAPE_H
#define USERSHAPE_H

#ifdef __cplusplus
extern "C" {
#endif

    typedef enum { FT_NULL,
		FT_BMP, FT_GIF, FT_PNG, FT_JPEG,
		FT_PDF, FT_PS, FT_EPS
    } imagetype_t;

    typedef struct usershape_s usershape_t;

    struct usershape_s {
	Dtlink_t link;
	char *name;
	int macro_id;
	bool must_inline;
	FILE *f;
	imagetype_t type;
	char *stringtype;
	unsigned int x, y, w, h, dpi;
	void *data;                   /* data loaded by a renderer */
	size_t datasize;              /* size of data (if mmap'ed) */
	void (*datafree)(usershape_t *us); /* renderer's function for freeing data */
    };

#ifdef __cplusplus
}
#endif
#endif
