/* $Id: geometry.h,v 1.2 2005/02/24 00:57:33 ellson Exp $ $Revision: 1.2 $ */
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

#ifdef __cplusplus
extern "C" {
#endif



#ifndef GEOMETRY_H
#define GEOMETRY_H

    typedef struct Point {
	double x, y;
    } Point;

    extern Point origin;

    extern double xmin, xmax, ymin, ymax;	/* extreme x,y values of sites */
    extern double deltax, deltay;	/* xmax - xmin, ymax - ymin */

    extern int nsites;		/* Number of sites */
    extern int sqrt_nsites;

    extern void geominit(void);
    extern double dist_2(Point *, Point *);	/* Distance squared between two points */
    extern void subPt(Point * a, Point b, Point c);
    extern void addPt(Point * a, Point b, Point c);
    extern double area_2(Point a, Point b, Point c);
    extern int leftOf(Point a, Point b, Point c);
    extern int intersection(Point a, Point b, Point c, Point d, Point * p);

#endif


#ifdef __cplusplus
}
#endif
