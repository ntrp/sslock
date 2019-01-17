#ifndef CONFIG_H_INCLUDED
#define CONFIG_H_INCLUDED

static const char *user  = "nobody";
static const char *group = "nogroup";

static const char *pam_service = "login";

static const int failonclear = 1;

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