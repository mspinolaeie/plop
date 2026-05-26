#ifdef __BORLANDC__
#include <alloc.h>
#endif

#include <stdlib.h>

#include <stdio.h>

#include "global.h"
#include "plate_global.h"

#ifdef gui_plop
extern void DebugMsg (char *);
#endif

#ifdef log_malloc
FILE *malloc_log_file = NULL;
#endif

void *malloc_or_die (
	int n,
	char *why)
{	char *p;

#ifdef gui_plop
	char str [100];
#endif


	p = (char *) malloc (n);
	total_mem_alloced += n;
	if (p == (char *) NULL)
	{	fprintf (stderr, "malloc for %s failed; time to die\n", why);
		exit (1);
	}
#ifdef log_malloc
	if (malloc_log_file == NULL) {
		malloc_log_file = fopen ("malloc_log.txt", "wb");
	}
	fprintf (malloc_log_file, "malloc %s %d\n", why, n);
#endif

#ifdef gui_plop
	sprintf (str, "malloc %s %d\n", why, n);
	DebugMsg (str);
#endif
	return (p);
}

void set_max_points (int n)
{	max_points = n;
	max_triangles = max_points * 2;
	max_quads = n;			/* merge pairs of triangles into quads */
//	max_z88_points = max_points * max_z88_depth;
}

void alloc_plate_globals ()
{	int i;

	plate_point_x = (double *) malloc_or_die (max_points * sizeof (double),
			"plate_point_x");
 	plate_point_y = (double *) malloc_or_die (max_points * sizeof (double),
			"plate_point_y");
	plate_forces = (double *) malloc_or_die (max_points * sizeof (double),
			"plate_forces");
	plate_force_points = (int *) malloc_or_die (max_points * sizeof (int),
			"plate_force_points");
	plate_triangle_points = (tri_int_corners *) malloc_or_die (max_triangles * sizeof (tri_int_corners),
			"plate_force_points");
	plate_tri_x_cg = (tri_dbl_corners *) malloc_or_die (max_triangles * sizeof (tri_dbl_corners),
			"plate_tri_x_cg");
	plate_tri_y_cg = (tri_dbl_corners *) malloc_or_die (max_triangles * sizeof (tri_dbl_corners),
			"plate_tri_y_cg");
	plate_thickness = (double *) malloc_or_die (max_triangles * sizeof (double),
			"plate_triangles");
	plate_tri_pressure = (double *) malloc_or_die (max_triangles * sizeof (double),
			"plate_tri_pressure");
	plate_area = (double *) malloc_or_die (max_triangles * sizeof (double),
			"plate_area");
	plate_mx = (double *) malloc_or_die (max_triangles * sizeof (double),
	  		"plate_mx");
	plate_my = (double *) malloc_or_die (max_triangles * sizeof (double),
			"plate_my");
	plate_mxy = (double *) malloc_or_die (max_triangles * sizeof (double),
			"plate_mxy");
	plate_xcg = (double *) malloc_or_die (max_triangles * sizeof (double),
			"plate_xcg");
	plate_ycg = (double *) malloc_or_die (max_triangles * sizeof (double),
			"plate_ycg");
	plate_rhs = (double *) malloc_or_die (max_eqn * sizeof (double),
			"plate_rhs");
	plate_result = (double *) malloc_or_die (max_eqn * sizeof (double),
			"plate_result");
	plate_z_displacement = (double *) malloc_or_die (max_points * sizeof (double),
			"plate_z_displacement");
 	plate_plot_point_x = (double *) malloc_or_die (max_points * sizeof (double),
			"plate_plot_point_x");
 	plate_plot_point_y = (double *) malloc_or_die (max_points * sizeof (double),
			"plate_plot_point_y");
	plate_plot_triangle_points = (tri_int_corners *) malloc_or_die (max_triangles * sizeof (tri_int_corners),
			"plate_plot_force_points");
	plate_plot_z_displacement = (double *) malloc_or_die (max_points * sizeof (double),
			"plate_plot_z_displacement");
 	z88_plot_point_x = (double *) malloc_or_die (max_points * sizeof (double),
			"z88_plot_point_x");
	z88_plot_point_y = (double *) malloc_or_die (max_points * sizeof (double),
			"z88_plot_point_y");
	z88_plot_triangle_points = (tri_int_corners *) malloc_or_die (max_triangles * sizeof (tri_int_corners),
			"z88_plot_force_points");
	z88_plot_z_displacement = (double *) malloc_or_die (max_points * sizeof (double),
			"z88_plot_z_displacement");

	for (i = 0; i < max_refocus_distortion_order; i++) {
		tmp_function_vals [i] = (double *) NULL;
	}
}
