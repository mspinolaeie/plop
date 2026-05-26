#include <stdio.h>
#include <stdlib.h>

#include "plop_debug.h"

void prompt_exit (void)
{
	exit (1);
}

void err_msg (const char *msg)
{
	fputs (msg, stderr);
}

void warn_msg (const char *msg)
{
	fputs (msg, stderr);
}
