/* $Id: gvcproc.h,v 1.23 2006/08/01 21:19:59 ellson Exp $ $Revision: 1.23 $ */
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

/* This is the public header for the callers of libgvc */

#ifndef GVCPROC_H
#define GVCPROC_H

#ifdef __cplusplus
extern "C" {
#endif

/* these are intended to be private entry points - see gvc.h for the public ones */

/* configuration */

    extern char *gvconfig_libdir(void);
    extern void gvconfig(GVC_t * gvc, bool rescan);
    extern char *gvhostname(void);

/* plugins */

    extern bool gvplugin_install(GVC_t * gvc, api_t api,
		    char *typestr, int quality, char *packagename, char *path,
		    gvplugin_installed_t * typeptr);
    extern gvplugin_available_t *gvplugin_load(GVC_t * gvc, api_t api, char *type);
    extern gvplugin_library_t *gvplugin_library_load(GVC_t *gvc, char *path);
    extern const char *gvplugin_list(GVC_t * gvc, api_t api, char *str);
    extern api_t gvplugin_api(char *str);
    extern char * gvplugin_api_name(api_t api);
    extern void gvplugin_write_status(GVC_t * gvc);

/* job */

    extern void gvjobs_output_filename(GVC_t * gvc, char *name);
    extern bool gvjobs_output_langname(GVC_t * gvc, char *name);
    extern GVJ_t *gvjobs_first(GVC_t * gvc);
    extern GVJ_t *gvjobs_next(GVC_t * gvc);
    extern void gvjobs_delete(GVC_t * gvc);

/* emit */
    extern void gvemit_graph(GVC_t * gvc, graph_t * g);

/* textlayout */

    extern int gvtextlayout_select(GVC_t * gvc);
    extern bool gvtextlayout(GVC_t *gvc, textpara_t *para, char **fontpath);

/* loadimage */
    extern void gvloadimage(GVJ_t *job, usershape_t *us, boxf b, bool filled, char *target);
    
/* usershapes */
    extern point gvusershape_size(graph_t *g, char *name);
    extern usershape_t *gvusershape_find(char *name);

/* device */

    extern void gvdevice_initialize(GVJ_t * job);
    extern void gvdevice_finalize(GVJ_t * job);

/* render */

    extern pointf gvrender_ptf(GVJ_t *job, pointf p);
    extern pointf* gvrender_ptf_A(GVJ_t *job, pointf *af, pointf *AF, int n);

    extern void gvrender_begin_job(GVJ_t * job);
    extern void gvrender_end_job(GVJ_t * job);
    extern int gvrender_select(GVJ_t * job, char *lang);
    extern int gvrender_features(GVJ_t * job);
    extern void gvrender_begin_graph(GVJ_t * job, graph_t * g);
    extern void gvrender_end_graph(GVJ_t * job);
    extern void gvrender_begin_page(GVJ_t * job);
    extern void gvrender_end_page(GVJ_t * job);
    extern void gvrender_begin_layer(GVJ_t * job);
    extern void gvrender_end_layer(GVJ_t * job);
    extern void gvrender_begin_cluster(GVJ_t * job, graph_t * sg);
    extern void gvrender_end_cluster(GVJ_t * job, graph_t *g);
    extern void gvrender_begin_nodes(GVJ_t * job);
    extern void gvrender_end_nodes(GVJ_t * job);
    extern void gvrender_begin_edges(GVJ_t * job);
    extern void gvrender_end_edges(GVJ_t * job);
    extern void gvrender_begin_node(GVJ_t * job, node_t * n);
    extern void gvrender_end_node(GVJ_t * job);
    extern void gvrender_begin_edge(GVJ_t * job, edge_t * e);
    extern void gvrender_end_edge(GVJ_t * job);
    extern void gvrender_begin_context(GVJ_t * job);
    extern void gvrender_end_context(GVJ_t * job);
    extern void gvrender_begin_anchor(GVJ_t * job, char *href,
			char *tooltip, char *target);
    extern void gvrender_end_anchor(GVJ_t * job);
    extern void gvrender_set_font(GVJ_t * job, char *fontname,
			double fontsize);
    extern void gvrender_textpara(GVJ_t * job, pointf p, textpara_t * para);
    extern void gvrender_set_pencolor(GVJ_t * job, char *name);
    extern void gvrender_set_fillcolor(GVJ_t * job, char *name);
    extern void gvrender_set_style(GVJ_t * job, char **s);
    extern void gvrender_ellipse(GVJ_t * job, pointf p,
	    		double rx, double ry, bool filled);
    extern void gvrender_polygon(GVJ_t * job, pointf * AF, int n, bool filled);
    extern void gvrender_box(GVJ_t * job, boxf BF, bool filled);
    extern void gvrender_beziercurve(GVJ_t * job, pointf * AF, int n,
			int arrow_at_start, int arrow_at_end, bool filled);
    extern void gvrender_polyline(GVJ_t * job, pointf * AF, int n);
    extern void gvrender_comment(GVJ_t * job, char *str);
    extern void gvrender_usershape(GVJ_t * job, char *name, pointf * AF, int n, bool filled);

/* layout */

    extern int gvlayout_select(GVC_t * gvc, char *str);
    extern int gvFreeLayout(GVC_t * gvc, graph_t * g);
    extern int gvLayoutJobs(GVC_t * gvc, graph_t * g);

/* argvlist */
    extern gv_argvlist_t *gvNEWargvlist(void);
    extern void gv_argvlist_set_item(gv_argvlist_t *list, int index, char *item);
    extern void gv_argvlist_reset(gv_argvlist_t *list);
    extern void gv_argvlist_free(gv_argvlist_t *list);

#ifdef __cplusplus
}
#endif
#endif				/* GVCPROC_H */
