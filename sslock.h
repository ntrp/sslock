#ifndef SSLOCK_H_INCLUDED
#define SSLOCK_H_INCLUDED

enum {
	INIT,
	INPUT,
	FAILED,
	PAM,
	NUMCOLS
};

static const char *colorname[NUMCOLS] = {
	[INIT] =   "black",     /* after initialization */
	[INPUT] =  "#005577",   /* during input */
	[FAILED] = "#CC3333",   /* wrong password */
	[PAM] =    "#9400D3",   /* waiting for PAM */
};

#endif