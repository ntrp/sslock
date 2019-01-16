#ifndef PAM_H_INCLUDED
#define PAM_H_INCLUDED

extern int 
sslock_pam_conv(int num_msg, const struct pam_message **msgm,
		     struct pam_response **response, void *appdata_ptr);

#endif