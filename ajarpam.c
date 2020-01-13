#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define PAM_SM_AUTH

#include <security/pam_modules.h>
#include <security/pam_ext.h>

#define PASS_CHARS_LIMIT 50


const char* parse_args(int argc, const char **argv);

PAM_EXTERN int pam_sm_authenticate(pam_handle_t *handle, int flags, int argc, const char **argv)
{

	int pam_code;
	const char *username = NULL;
	const char *password = NULL;
	const char *chosen_pass;


	chosen_pass = parse_args(argc, argv);

	if (!chosen_pass) {
		fprintf(stderr, "Password was not set up\n");
		return PAM_PERM_DENIED;
	}


	pam_code = pam_get_user(handle, &username, "Username: ");
	if (pam_code != PAM_SUCCESS) {
		fprintf(stderr, "Could not get username\n");
		return PAM_PERM_DENIED;
	}


	pam_code = pam_get_authtok(handle, PAM_AUTHTOK, &password, "Password: ");
	if (pam_code != PAM_SUCCESS) {
		fprintf(stderr, "Could not get password");
		return PAM_PERM_DENIED;
	}


	/* if flag PAM_DISALLOW_NULL_AUTHTOK flag is on, we don't accept empty passwords */
	if (flags & PAM_DISALLOW_NULL_AUTHTOK) {
		if (password == NULL || strcmp(password, "") == 0) {
			fprintf(stderr,
				"Null authentication token is not allowed!.");
			return PAM_PERM_DENIED;
		}
	}

	if (strncmp(password, chosen_pass, PASS_CHARS_LIMIT) == 0) {
		return PAM_SUCCESS;
	}

	return PAM_PERM_DENIED;
}


/* return pointer to password string */
const char* parse_args(int argc, const char **argv)
{

	const char *chosen_pass = NULL;

	int i;
	for (i = 0; i < argc; i++) {
		if (strncmp(argv[i], "pass=", 5) == 0) {
			chosen_pass = argv[i] + 5;
		}

	}

	return chosen_pass;
}

