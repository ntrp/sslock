#include <security/pam_appl.h>
#include <security/pam_misc.h>

#include "pam.h"

char passwd[256];

struct pam_conv pamc = {sslock_pam_conv, NULL};

int 
sslock_pam_conv(int num_msg, const struct pam_message **msg,
		struct pam_response **resp, void *appdata_ptr) 
{
    int retval = PAM_CONV_ERR;
    for(int i=0; i<num_msg; i++) {
        if (msg[i]->msg_style == PAM_PROMPT_ECHO_OFF) {
            struct pam_response *resp_msg = malloc(sizeof(struct pam_response));
            fprintf(stderr, "debug: %s\n", passwd);
            if (strlen(passwd) > 0) {
                char *password = malloc(strlen(passwd) + 1);
                memset(password, 0, strlen(passwd) + 1);
			    strcpy(password, passwd); 
                resp_msg->resp_retcode = 0;
			    resp_msg->resp = password;
			    resp[i] = resp_msg;
			    retval = PAM_SUCCESS;
            }
        }
    }
	return retval;
}