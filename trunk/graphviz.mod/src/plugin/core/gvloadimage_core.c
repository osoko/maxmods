/* $Id: gvloadimage_core.c,v 1.16 2006/08/04 02:47:16 ellson Exp $ $Revision: 1.16 $ */
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

#include <stdlib.h>
#include <sys/types.h>
#ifdef WIN32
#include <io.h>
#endif
#include <sys/stat.h>
#if HAVE_UNISTD_H
#include <unistd.h>
#endif
#if HAVE_SYS_MMAN_H
#include <sys/mman.h>
#endif

#include "gvplugin_loadimage.h"

/* for n->name */
#include "graph.h"

extern void core_fputs(GVJ_t * job, char *s);
extern void core_printf(GVJ_t * job, const char *format, ...);

extern void epsf_emit_body(usershape_t *us, FILE *of);
extern shape_desc *find_user_shape(char *name);

typedef enum {
    FORMAT_PNG_SVG, FORMAT_GIF_SVG, FORMAT_JPEG_SVG,
    FORMAT_PNG_FIG, FORMAT_GIF_FIG, FORMAT_JPEG_FIG,
    FORMAT_PNG_VRML, FORMAT_GIF_VRML, FORMAT_JPEG_VRML,
    FORMAT_PS_PS, FORMAT__PS,
} format_type;

static void core_loadimage_svg(GVJ_t * job, usershape_t *us, boxf b, bool filled)
{
    assert(job);
    assert(us);
    assert(us->name);
    assert(us->f);

    core_fputs(job, "<image xlink:href=\"");
    core_fputs(job, us->name);
    if (job->rotation) {
        core_printf (job, "\" width=\"%gpx\" height=\"%gpx\" preserveAspectRatio=\"xMidYMid meet\" x=\"%g\" y=\"%g\"",
            b.UR.y - b.LL.y, b.UR.x - b.LL.x, b.LL.x, b.UR.y);
        core_printf (job, " transform=\"rotate(%d %g %g)\"",
            job->rotation, b.LL.x, b.UR.y);
    }
    else {
        core_printf (job, "\" width=\"%gpx\" height=\"%gpx\" preserveAspectRatio=\"xMidYMid meet\" x=\"%g\" y=\"%g\"",
            b.UR.x - b.LL.x, b.UR.y - b.LL.y, b.LL.x, b.LL.y);
    }
    core_fputs(job, "/>\n");
}

static void core_loadimage_fig(GVJ_t * job, usershape_t *us, boxf bf, bool filled)
{
    int object_code = 2;        /* always 2 for polyline */
    int sub_type = 5;           /* always 5 for image */
    int line_style = 0;		/* solid, dotted, dashed */
    int thickness = 0;
    int pen_color = 0;
    int fill_color = -1;
    int depth = 1;
    int pen_style = -1;         /* not used */
    int area_fill = 0;
    double style_val = 0.0;
    int join_style = 0;
    int cap_style = 0;
    int radius = 0;
    int forward_arrow = 0;
    int backward_arrow = 0;
    int npoints = 5;
    int flipped = 0;

    box b;

    assert(job);
    assert(us);
    assert(us->name);
    assert(us->f);

    BF2B(bf, b);

    core_printf(job, "%d %d %d %d %d %d %d %d %d %.1f %d %d %d %d %d %d\n %d %s\n",
            object_code, sub_type, line_style, thickness, pen_color,
            fill_color, depth, pen_style, area_fill, style_val, join_style,
            cap_style, radius, forward_arrow, backward_arrow, npoints,
            flipped, us->name);
    core_printf(job," %d %d %d %d %d %d %d %d %d %d\n",
	    b.LL.x, b.LL.y,
	    b.LL.x, b.UR.y,
	    b.UR.x, b.UR.y,
	    b.UR.x, b.LL.y,
	    b.LL.x, b.LL.y);
}

static void core_loadimage_vrml(GVJ_t * job, usershape_t *us, boxf b, bool filled)
{
    FILE *out;
    obj_state_t *obj;
    node_t *n;

    assert(job);

    out = job->output_file;
    obj = job->obj;
    assert(out);
    assert(obj);

    assert(us);
    assert(us->name);
    assert(us->f);

    n = job->obj->u.n;
    assert(n);

    fprintf(out, "Shape {\n");
    fprintf(out, "  appearance Appearance {\n");
    fprintf(out, "    material Material {\n");
    fprintf(out, "      ambientIntensity 0.33\n");
    fprintf(out, "        diffuseColor 1 1 1\n");
    fprintf(out, "    }\n");
    fprintf(out, "    texture ImageTexture { url \"%s\" }\n", us->name);
    fprintf(out, "  }\n");
    fprintf(out, "}\n");


}

static void ps_freeimage(usershape_t *us)
{
#if HAVE_SYS_MMAN_H
    munmap(us->data, us->datasize);
#else
    free(us->data);
#endif
}

/* usershape described by a postscript file */
static void core_loadimage_ps(GVJ_t * job, usershape_t *us, boxf b, bool filled)
{
    FILE *out;

    assert(job);
    assert(us);
    assert(us->name);
    assert(us->f);

    out = job->output_file;
    assert(out);

    if (us->data) {
        if (us->datafree != ps_freeimage) {
            us->datafree(us);        /* free incompatible cache data */
            us->data = NULL;
            us->datafree = NULL;
            us->datasize = 0;
        }
    }

    if (!us->data) { /* read file into cache */
        int fd = fileno(us->f);
	struct stat statbuf;

        fseek(us->f, 0, SEEK_SET);
        switch (us->type) {
            case FT_PS:
            case FT_EPS:
		fstat(fd, &statbuf);
		us->datasize = statbuf.st_size;
#if HAVE_SYS_MMAN_H
		us->data = mmap(0, statbuf.st_size, PROT_READ, MAP_SHARED, fd, 0);
#else
		us->data = malloc(statbuf.st_size);
		read(fd, us->data, statbuf.st_size);
#endif
		us->must_inline = true;
                break;
            default:
                break;
        }
        if (us->data)
            us->datafree = ps_freeimage;
    }

    if (us->data) {
        fprintf(out, "gsave %g %g translate newpath\n",
		b.LL.x - us->x, b.LL.y - us->y);
        if (us->must_inline)
            epsf_emit_body(us, out);
        else
            fprintf(out, "user_shape_%d\n", us->macro_id);
        fprintf(out, "grestore\n");
    }
}

/* usershape described by a member of a postscript library */
static void core_loadimage_pslib(GVJ_t * job, usershape_t *us, boxf b, bool filled)
{
    int i;
    pointf AF[4];
    FILE *out;
    shape_desc *shape;

    assert(job);
    assert(us);
    assert(us->name);
    assert(!(us->f));

    out = job->output_file;
    assert(out);

    if ((shape = (shape_desc*)us->data)) {
	AF[0] = b.LL;
	AF[2] = b.UR;
	AF[1].x = AF[0].x;
	AF[1].y = AF[2].y;
	AF[3].x = AF[2].x;
	AF[3].y = AF[0].y;
        if (filled) {
//            ps_begin_context();
//            ps_set_color(S[SP].fillcolor);
            fprintf(out, "[ ");
            for (i = 0; i < 4; i++)
                fprintf(out, "%g %g ", AF[i].x, AF[i].y);
            fprintf(out, "%g %g ", AF[0].x, AF[0].y);
            fprintf(out, "]  %d true %s\n", 4, us->name);
//            ps_end_context();
        }
        fprintf(out, "[ ");
        for (i = 0; i < 4; i++)
            fprintf(out, "%g %g ", AF[i].x, AF[i].y);
        fprintf(out, "%g %g ", AF[0].x, AF[0].y);
        fprintf(out, "]  %d false %s\n", 4, us->name);
    }
}

static gvloadimage_engine_t engine_svg = {
    core_loadimage_svg
};

static gvloadimage_engine_t engine_fig = {
    core_loadimage_fig
};

static gvloadimage_engine_t engine_vrml = {
    core_loadimage_vrml
};

static gvloadimage_engine_t engine_ps = {
    core_loadimage_ps
};

static gvloadimage_engine_t engine_pslib = {
    core_loadimage_pslib
};

gvplugin_installed_t gvloadimage_core_types[] = {
    {FORMAT_PNG_SVG, "png2svg", 1, &engine_svg, NULL},
    {FORMAT_GIF_SVG, "gif2svg", 1, &engine_svg, NULL},
    {FORMAT_JPEG_SVG, "jpeg2svg", 1, &engine_svg, NULL},
    {FORMAT_PNG_FIG, "png2fig", 1, &engine_fig, NULL},
    {FORMAT_GIF_FIG, "gif2fig", 1, &engine_fig, NULL},
    {FORMAT_JPEG_FIG, "jpeg2fig", 1, &engine_fig, NULL},
    {FORMAT_PNG_VRML, "png2vrml", 1, &engine_vrml, NULL},
    {FORMAT_GIF_VRML, "gif2vrml", 1, &engine_vrml, NULL},
    {FORMAT_JPEG_VRML, "jpeg2vrml", 1, &engine_vrml, NULL},
    {FORMAT_PS_PS, "ps2ps", 1, &engine_ps, NULL},
    {FORMAT__PS, "2ps", 1, &engine_pslib, NULL},
    {0, NULL, 0, NULL, NULL}
};
