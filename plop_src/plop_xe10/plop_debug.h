

#ifndef plop_debug_h
#define plop_debug_h

#include "global.h"


#define ndebugs	10


extern int debugs [ndebugs];

extern const char *debug_strings [];

extern FILE *debug_file;

void err_msg_s (const char *msg, const char *arg1);
void warn_msg_s (const char *msg, const char *arg1);
void err_msg_ss (const char *msg, const char *arg1, const char *arg2);
void err_msg_d (const char *msg, int arg1);
void err_msg_dd (const char *msg, int arg1, int arg2);
void err_msg_ds (const char *msg, int arg1, const char *arg2);
void err_msg_g (const char *msg, double arg1);
void err_msg_dg (const char *msg, int arg1, double arg2);
void err_msg_gd (const char *msg, double arg1, int arg2);

void add_debug (const char *s);

/* depending on gui or standalone will implement appropriately */
void err_msg (const char *s);
void warn_msg (const char *s);
void prompt_exit (void);

#define debug_grid_gen		debugs [0]
#define debug_opt			debugs [1]
#define debug_basis_gen		debugs [2]
#define debug_triangle		debugs [3]
#define debug_interpolate	debugs [4]
#define debug_matrix		debugs [5]
#define debug_fem			debugs [6]
#define debug_plate_load   	debugs [7]
#define debug_displacement	debugs [8]


#endif
