/* $Id: dot_builtins.c,v 1.9 2006/06/19 14:37:35 ellson Exp $ $Revision: 1.9 $ */
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

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "gvplugin.h"

extern gvplugin_library_t *gvplugin_dot_layout_LTX_library;
extern gvplugin_library_t *gvplugin_neato_layout_LTX_library;
#ifdef HAVE_LIBGD
extern gvplugin_library_t *gvplugin_gd_LTX_library;
#endif
#ifdef HAVE_PANGOCAIRO
extern gvplugin_library_t *gvplugin_pango_LTX_library;
#endif
extern gvplugin_library_t *gvplugin_core_LTX_library;
extern gvplugin_library_t *gvplugin_bmx_LTX_library;

const lt_symlist_t lt_preloaded_symbols[] = {
	{ "gvplugin_dot_layout_LTX_library", (void*)(&gvplugin_dot_layout_LTX_library) },
	{ "gvplugin_neato_layout_LTX_library", (void*)(&gvplugin_neato_layout_LTX_library) },
#ifdef HAVE_PANGOCAIRO
	{ "gvplugin_pango_LTX_library", (void*)(&gvplugin_pango_LTX_library) },
#endif
#ifdef HAVE_LIBGD
	{ "gvplugin_gd_LTX_library", (void*)(&gvplugin_gd_LTX_library) },
#endif
	{ "gvplugin_core_LTX_library", (void*)(&gvplugin_core_LTX_library) },
	{ "gvplugin_bmx_LTX_library", (void*)(&gvplugin_bmx_LTX_library) }, /* BaH */
	{ 0, 0 }
};
