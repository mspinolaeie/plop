#include <stdio.h>

#include "plop_debug.h"

int debugs [ndebugs];

const char *debug_strings [] = {
	"grid_gen",
	"opt",
	"basis",
	"triangle",
	"interpolate",
	"matrix",
    "fem",
	"plate_load",
	"displacement",
	"locale",
    ""};


void err_msg_s (const char *msg, const char *arg1)
{	char str [max_line_len];

	sprintf (str, msg, arg1);
	err_msg (str);
}

void warn_msg_s (const char *msg, const char *arg1)
{	char str [max_line_len];

	sprintf (str, msg, arg1);
	warn_msg (str);
}

void err_msg_ss (const char *msg, const char *arg1, const char *arg2)
{	char str [max_line_len];

	sprintf (str, msg, arg1, arg2);
	err_msg (str);
}

void err_msg_d (const char *msg, int arg1)
{	char str [max_line_len];

	sprintf (str, msg, arg1);
	err_msg (str);
}

void err_msg_dd (const char *msg, int arg1, int arg2)
{	char str [max_line_len];

	sprintf (str, msg, arg1, arg2);
	err_msg (str);
}

void err_msg_ds (const char *msg, int arg1, const char *arg2)
{	char str [max_line_len];

	sprintf (str, msg, arg1, arg2);
	err_msg (str);
}

void err_msg_g (const char *msg, double arg1)
{	char str [max_line_len];

	sprintf (str, msg, arg1);
	err_msg (str);
}

void err_msg_dg (const char *msg, int arg1, double arg2)
{	char str [max_line_len];

	sprintf (str, msg, arg1, arg2);
	err_msg (str);
}

void err_msg_gd (const char *msg, double arg1, int arg2)
{	char str [max_line_len];

	sprintf (str, msg, arg1, arg2);
	err_msg (str);
}


 
