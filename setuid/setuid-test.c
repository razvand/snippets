#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>

static void print_current_uid(void)
{
	uid_t uid = getuid();
	uid_t euid = geteuid();
	struct passwd *uid_pw;
	struct passwd *euid_pw;
	struct passwd buf_uid_pw, buf_euid_pw;

	uid_pw = getpwuid(uid);
	memcpy(&buf_uid_pw, uid_pw, sizeof(struct passwd));
	euid_pw = getpwuid(euid);
	memcpy(&buf_euid_pw, euid_pw, sizeof(struct passwd));

	printf("uid: %d (%s); euid: %d (%s)\n",
			buf_uid_pw.pw_uid, buf_uid_pw.pw_name,
			buf_euid_pw.pw_uid, buf_euid_pw.pw_name);
}

static void drop_privilege(uid_t uid, uid_t euid)
{
#ifdef _POSIX_SAVED_IDS
	seteuid(uid);
#else
	setreuid(euid, uid);
#endif
}

static void restore_privilege(uid_t uid, uid_t euid)
{
#ifdef _POSIX_SAVED_IDS
	seteuid(euid);
#else
	setreuid(uid, euid);
#endif
}

int main(void)
{
	uid_t uid = getuid();
	uid_t euid = geteuid();

	printf("initial values:\n");
	print_current_uid();

#if 0
	drop_privilege(uid, euid);
	printf("after privilege drop\n");
	print_current_uid();

	restore_privilege(uid, euid);
	printf("after privilege restore\n");
	print_current_uid();
#endif

	return 0;
}
