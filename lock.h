#ifndef LOCK_H_INCLUDED
#define LOCK_H_INCLUDED

#include <X11/Xlib.h>

#include "config.h"

extern struct lock {
	int screen;
	Window root, win;
	Pixmap pmap;
	unsigned long colors[NUMCOLS];
};

extern struct xrandr {
	int active;
	int evbase;
	int errbase;
};

extern struct lock *
lockscreen(Display *dpy, struct xrandr *rr, int screen);

extern void
readpw(Display *dpy, struct xrandr *rr, struct lock **locks, int nscreens,
       const char *hash);

#endif