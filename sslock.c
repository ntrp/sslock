#include <stdio.h>
#include <errno.h>
#include <grp.h>
#include <pwd.h>
#include <security/pam_appl.h>
#include <security/pam_misc.h>
#include <X11/Xlib.h>
#include <X11/extensions/Xrandr.h>

#include "config.h"
#include "utils.h"
#include "oom.h"
#include "pam.h"
#include "lock.h"

int main(int argc, char *argv[]) {

    struct xrandr rr;
	struct lock **locks;
    struct passwd *pwd;
	struct group *grp;
	uid_t duid;
	gid_t dgid;
	Display *dpy;
	int s, nlocks, nscreens;

    /* validate drop-user and -group */
	errno = 0;
	if (!(pwd = getpwnam(user)))
		die("slock: getpwnam %s: %s\n", user,
		    errno ? strerror(errno) : "user entry not found");
	duid = pwd->pw_uid;
	errno = 0;
	if (!(grp = getgrnam(group)))
		die("slock: getgrnam %s: %s\n", group,
		    errno ? strerror(errno) : "group entry not found");
	dgid = grp->gr_gid;

#ifdef __linux__
	dontkillme();
#endif
        
    if (!(dpy = XOpenDisplay(NULL)))
		die("slock: cannot open display\n");

	/* drop privileges 
	*/
	if (setgroups(0, NULL) < 0)
		die("slock: setgroups: %s\n", strerror(errno));
	if (setgid(dgid) < 0)
		die("slock: setgid: %s\n", strerror(errno));
	if (setuid(duid) < 0)
		die("slock: setuid: %s\n", strerror(errno));

	/* check for Xrandr support */
	rr.active = XRRQueryExtension(dpy, &rr.evbase, &rr.errbase);

	/* get number of screens in display "dpy" and blank them */
	nscreens = ScreenCount(dpy);
	if (!(locks = calloc(nscreens, sizeof(struct lock *))))
		die("slock: out of memory\n");
	for (nlocks = 0, s = 0; s < nscreens; s++) {
		if ((locks[s] = lockscreen(dpy, &rr, s)) != NULL)
			nlocks++;
		else
			break;
	}
	XSync(dpy, 0);

	/* did we manage to lock everything? */
	if (nlocks != nscreens)
		return 1;

	/* run post-lock command */
	if (argc > 0) {
		switch (fork()) {
		case -1:
			die("slock: fork failed: %s\n", strerror(errno));
		case 0:
			if (close(ConnectionNumber(dpy)) < 0)
				die("slock: close: %s\n", strerror(errno));
			execvp(argv[0], argv);
			fprintf(stderr, "slock: execvp %s: %s\n", argv[0], strerror(errno));
			_exit(1);
		}
	}

	readpw(dpy, &rr, locks, nscreens, "ntrp");

    return 0;
}