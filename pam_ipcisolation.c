#include <security/_pam_types.h>
#define _GNU_SOURCE
#include <security/pam_modules.h>
#include <security/pam_ext.h>
#include <sched.h>
#include <syslog.h>

PAM_EXTERN int pam_sm_open_session(pam_handle_t *pamh, int flags, int argc, const char **argv) {
	(void) flags, (void) argc, (void) argv;
	if (unshare(CLONE_NEWIPC)) {
		pam_syslog(pamh, LOG_ERR, "Could not unshare IPC namespace: %m");
		return PAM_SESSION_ERR;
	}
	return PAM_SUCCESS;
}

PAM_EXTERN int pam_sm_close_session(pam_handle_t *pamh, int flags, int argc, const char** argv) {
	(void) pamh, (void) flags, (void) argc, (void) argv;
	return PAM_SUCCESS;
}
