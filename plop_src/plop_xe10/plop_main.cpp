#ifdef gui_plop
#include <vcl.h>
#endif
#pragma hdrstop


#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include <math.h>

#include "global.h"

#include "plate_global.h"

#include "plot.h"

#include "plop_parms.h"

#include "plop_debug.h"
#include "grid_gen.h"



#ifdef use_gd_graphics
#include "gd.h"
#endif
                                                      


/*
 * Some limit checks and bug checks that need to be done:
 *
 * Check that n_basis_rings > 0 if using basis
 * Check basis_ring_min > 0 or mesh screws up
 * Check that n_mesh_rings <= max_mesh_perim
 *
*/

int check_part_descrs (void);
void init_plop (void);

#ifndef standalone
void plate_setup (void);
void pload (void);
void formk (void);
void solve (void);
void out (void);
void alloc_globals (void);
void alloc_plate_globals (void);
void read_info (char *s);
void init_default_basis (void);
void run_plate (void);


void calculate_zernike (void);

void refocus_mirror (void);
void calc_rms (void);

void init_global_graphics (void);
void plate_init (void);
void init_graphics (void);
void calculate_plop_plot (int, double *, double *, double *, double *);
void write_picture (char *, plop_cmap *);
void print_plate (char *);
void print_pic (int, char *);

void copy_plot_data (void);

void getwords (
	char *line,
	char wordtable [maxwords] [wordlen],
	int *wordsfound,
	int wtabsize);


#endif
void set_max_points (int);

#ifndef __BORLANDC__
#define abs(x)		((x) > 0 ? (x) : -(x))
#endif


#ifdef gui_plop
extern void UpdateCellEditOptVars ();
extern void UpdateRunOptStatus (int, double);
extern void UpdateMonteDisplay (int, double, double);

/* must acquire lock to access support points, mesh, and z displacement */

extern void LockPlopData (int);
extern void UnlockPlopData (void);

extern void DebugMsg (const char *);

#endif


#define toggle(x)		x = 1 - x;

void alloc_plate_globals (void);

void *malloc_or_die (int, const char *);





#ifdef standalone_grid_gen
int main (
	int argc,
	char *argv [])
{
	deg_to_rad = 2 * M_PI / degrees;

	while (argc > 1 && argv [1] [0] == '-' )
	{	switch (argv [1] [1])
		{	case 'd':
				add_debug (argv [1] + 2);
				break;
		}
		argc--;
		argv++;
	}

	if (argc < 3)
	{	err_msg ("Usage: grid_gen params output_file [pic_file]\n");
		exit (1);
	}
    set_max_points (default_max_points);
	alloc_globals ();
	alloc_plate_globals ();

    read_info (argv [1]);

	gen_mesh (1);

	order_nodes ();

	print_plate (argv [2]);

	if (argc > 3)
		print_pic (have_pic_mesh, argv [3]);

	return 0;
}
#else

int parse_arg (int argc, char *argv [], int describe)
{	int n;
	int i;
    int dash;
    static char off_on_names [2] [4] = {"off", "on"};

	n = 1;
    if (argv [0] [0] == '-')
    	dash = 1;
    else
    	dash = 0;
  	switch (argv [0] [dash])
    {
    	case 'a':
         	if (argc < 2 || sscanf (argv [1], "%d", &i) != 1)
            	err_msg_s ("Can't make sense of -a arg %s\n", argv [1]);
        	set_max_points (i);
            if (describe)
            	printf ("max points set to %d\n", i);
            n++;
            break;

        case 'b':
        	toggle (verbose);
            if (describe)
            	printf ("verbose turned %s\n", off_on_names [verbose]);
            break;

        case 'c':
        	have_contour_plot = 1;
            strcpy (contourplotfile, argv [1]);
			n++;
            if (describe)
            	printf ("contour plot file set to %s\n", contourplotfile);
            break;

        case 'd':
        	have_dat = 1;
            strcpy (datfile, argv [1]);
            n++;
            if (describe)
            	printf ("will save dat in %s\n", datfile);
            break;

        case 'e':
        	if (argc > 1)
            {	sscanf (argv [1], "%d", &n_monte_tests);
            	n++;
            	if (describe)
            		printf ("number of monte carlo tests set to %d\n", n_monte_tests);
            }
			break;

        case 'g':
			grid_gen_using_basis = 1;
			n++;
			if (describe)
				printf ("grid strategy set to basis\n");
            break;

        case 'm':
        	have_pic = 1;
            if (argv [0] [1] == 's')
            	have_pic_mesh = 0;
            else
            	have_pic_mesh = 1;
            strcpy (picfile, argv [1]);
			n++;
            if (describe)
            	printf ("save picture of mesh in %s\n", picfile);
            break;

        case 'n':
        	if (argc > 1)
            {	if (argv [0] [dash + 1] == 'c')
                {	sscanf (argv [1], "%d", &n_contours);
                    n++;
                	if (describe)
            			printf ("contour map with %d contours\n", n_contours);
                }
                else
                {   sscanf (argv [1], "%d", &n_colors);
                    n++;
                    if (describe)
                        printf ("number of colors set to %d\n", n_colors);
                }
            }
            break;

        case 'o':
        	toggle (trace_opt);
            if (describe)
            	printf ("trace of optimization turned %s\n", off_on_names [trace_opt]);
            break;

        case 'p':
        	have_plot = 1;
            strcpy (plotfile, argv [1]);
			n++;
            if (describe)
            	printf ("plot file set to %s\n", plotfile);
            break;

        case 'q':
			toggle (quiet);
            if (describe)
            	printf ("quiet mode turned %s\n", off_on_names [quiet]);
            break;

		case 'r':
			toggle (refocus_flag);
            if (describe)
            	printf ("refocusing turned %s\n", off_on_names [refocus_flag]);
            break;

        case 's':
        	if (argc > 1)
            {	sscanf (argv [1], "%d", &pic_size);
				n++;
            	if (describe)
            		printf ("picture size set to %d\n", pic_size);
            }
            break;

        case 'u':
        	toggle (reuse_best_opt);
            if (describe)
            	printf ("reuse best optimization turned %s\n", off_on_names [reuse_best_opt]);
            break;

        case 'v':
        	toggle (use_p_v_error);
            if (describe)
            	printf ("peak-valley error turned %s\n", off_on_names [use_p_v_error]);
            break;

    	case 'w':
        	if (argc > 1)
            {	if (argv [0] [dash + 1] == 'p')
                {	strcpy (opt_phys_gr_file, argv [1]);
                    have_opt_phys_gr = 1;
                    n++;
                    if (describe)
                        printf ("save file for physical result of optimization set to %s\n", opt_phys_gr_file);
                }
                else
                {	strcpy (opt_gr_file, argv [1]);
                    have_opt_gr = 1;
                    n++;
                    if (describe)
                        printf ("save file for result of optimization set to %s\n", opt_gr_file);
                }
            }
            break;

     	case 'z':
    		if (argc > 1)
            {	if (argv [0] [dash + 1] == 'c')
                {   sscanf (argv [1], "%lg", &contour_space);
                    n++;
                    printf ("picture contour spacing set to %g\n", contour_space);
            	}
                else
                {   sscanf (argv [1], "%lg", &pic_z_range);
                    n++;
                    printf ("picture z range set to %g\n", pic_z_range);
            	}
            }
            break;

        case 'D':
        	if (argv [0] [dash + 1] == 'f')
            {   debug_file = fopen (argv [1], "w");
                if (debug_file == NULL)
                {   err_msg_s ("Can't open file %s\n", argv [1]);
                }
                n++;
            }
            else
            {   if (argc == 1)
            		add_debug ("");
            	else
            	{	add_debug (argv [1]);
                	n++;
                }
            }
            break;

        case '?':
            printf ("\n");
            printf ("Plop options\n");
            printf ("c plotfile     contour plot\n");
            printf ("p plotfile     plot\n");
            printf ("n[c] num       number of colors [contours]\n");
            printf ("z[c] num       z range for plot of surface [contour spacing]\n");
            printf ("e num			set number of monte carlo tests\n");
            printf ("r              refocus\n");
            printf ("s              size of plot\n");
            printf ("m[s] picfile   print picture of mesh [s = suuports only]\n");
            printf ("d datfile      save input to plate\n");
            printf ("o              print intermediate results of optimizer\n");
            printf ("q              quiet\n");
            printf ("u              reuse previous best from optimizer\n");
            printf ("v              use peak-valley error in optimizer\n");
            printf ("g [never|always|once|twice|first|basis]        grid gen strategy\n");
            printf ("a num          allocate for num points\n");
            printf ("b              verbose mode\n");
            printf ("D name         debug\n");
            printf ("Df name        debug file\n");
            printf ("x              run Plop\n");
            printf ("w[p] file			save [physical] optimum in file\n");
            printf ("\n");
            break;

        default:
        	err_msg_s ("Don't understand arg %s\n", argv [0]);
	}
    return (n);
}


void prompt_for_command (void)
{	char line [max_line_len];
	char words [maxwords] [wordlen];
    char *argv [maxwords];
	int n_words;
    int i;


	int more;

    printf ("Welcome to Plop! Use ? for help\n");

	for (i = 0; i < maxwords; i++)
    	argv [i] = words [i];

    more = 1;
    while (more)
    {	printf ("Enter the name of the Plop control file (.gr file)\n");
    	printf ("File: ");
    	gets (line);
    	if (sscanf (line, "%s", grfile) != 1)
    		err_msg ("Can't interpret the file name\n");
    	else
	    	more = 0;
    }

    more = 1;
    while (more)
    {

        printf ("Command: ");
        gets (line);

        getwords (line, words, &n_words, maxwords);

        if (strcmp (words [0], "x"))
        	parse_arg (n_words, argv, 1);
        else
        	more = 0;

    }
}

/*
 * main routine for plop
 *
 * plop [args] gridfile
 *
 * args are:
 *
 * plotting related:
 * -c plotfile		contour plot
 * -n num			contour plot, specify number of colors
 * -nc num			number of colors
 * -r				refocus
 * -p plotfile		plot
 * -s				size of plot
 * -z[c] num		z range for plot of surface [contour spacing]
 *
 * intermediate results:
 *
 * -m[s] picfile		print PIC file of mesh [no mesh]
 * -d datfile		save input to plate
 *
 * optimizer related:
 *
 * -o 				print intermediate results of optimizer
 * -q				quiet
 * -u				reuse previous best from optimizer
 * -v				use peak-valley error in optimizer
 *
 * optimization strategies:
 *
 * -g never			grid gen once, never regrid
 * -g always		grid gen every eval
 * -g once			grid gen once per optimization
 * -g twice			grid gen twice per opt; on entry, then reoptimize
 * -g first			grid gen twice on first opt, never after
 *
 * -a np			allocate for np points
 * -Dname			debug
 */

int main (
	int argc,
	char **argv)
{	int i;

    output_file = stdout;
    debug_file = stdout;

	init_plop ();
    
    if (argc == 1)
    	prompt_for_command ();

	argc--;
    argv++;
    while (argc > 0 && argv [0] [0] == '-' )
	{	i = parse_arg (argc, argv, 0);
		argc -= i;
		argv += i;
	}

   	init_graphics (); /* used to store some error calculation info */

	alloc_globals ();
	alloc_plate_globals ();

    if (argc > 0)
		read_info (argv [0]);
	else
    	read_info (grfile);

	init_default_basis ();

	plate_init ();

	run_plate ();

	if (have_dat)
		print_plate (datfile);

	if (have_pic)
	{	print_pic (have_pic_mesh, picfile);
    }

    if (have_plot || have_contour_plot)
    	copy_plot_data ();

	if (have_plot)
	{  	calculate_plop_plot (0, &plate_plot_z_min, &plate_plot_z_max, &plate_err_vis_rms, &plate_err_vis_p_v);
		write_picture (plotfile, &color_cmap);
    }

    if (have_contour_plot)
	{  	calculate_plop_plot (1, &plate_plot_z_min, &plate_plot_z_max, &plate_err_vis_rms, &plate_err_vis_p_v);
        write_picture (contourplotfile, &contour_cmap);
    }

	if (verbose)
    	printf ("memory usage: %d\n", total_mem_alloced);

	return 0;
}
#endif
