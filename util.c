/*
 *
 *   SwitchRes (C) 2010 Chris Kennedy <c@groovy.org>
 * 
 *   This program is Free Software under the GNU Public License
 *
 *   SwitchRes is a modeline generator based off of Calamity's 
 *   Methods of generating modelines
 *
 */

#include "switchres.h"
#include <stdio.h>
#include <stdarg.h>
#include "math.h"

double Normalize(double a, double b) {
	double c, e;
	int d;

	c = (double)a / (double)b;
	d = a / b;
	e = c - (double)d;
	if (e > 0.0)
		d++;
	a = d * b;

	return a;
}

int RunProgram(ConfigSettings *cs, char *temp) {
        int c1=0;
        FILE *pi;
        char c;

        if (cs->verbose > 2)
                sr_fprintf(stderr, "Running: %s\n", temp);

        pi=popen(temp, "r");
        if(pi != NULL) {
                int i = 0;
                c=fgetc(pi);
                while(c != '\xff' && i < 20000) {
                        temp[c1]=c;
                        c=fgetc(pi);
                        c1++;
                }
                temp[c1]='\x00';
                pclose(pi);
        } else
                return -1;

        if (cs->verbose > 4)
                sr_fprintf(stderr, "Output from command is:\n '%s'\n", temp);

        return 0;
}

void sr_fprintf(FILE *fd, const char *fmt, ...) {
        va_list vl;

        va_start(vl, fmt);

	if (logfd) 
        	vfprintf(logfd, fmt, vl);
	else
        	vfprintf(fd, fmt, vl);

        va_end(vl);

        return;
}

