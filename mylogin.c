/*
 * Shows user info from local pwfile.
 *
 * Usage: userinfo username
 */

#define _XOPEN_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pwdblib.h"   /* include header declarations for pwdblib.c */

/* Define some constants. */
#define USERNAME_SIZE (32)
#define NOUSER (-1)
#define SALT_SIZE (2)


int print_info(const char *username)
{
  struct pwdb_passwd *p = pwdb_getpwnam(username);
  if (p != NULL) {
    printf("Name: %s\n", p->pw_name);
    //printf("Passwd: %s\n", p->pw_passwd);
    printf("Uid: %u\n", p->pw_uid);
    printf("Gid: %u\n", p->pw_gid);
    printf("Real name: %s\n", p->pw_gecos);
    printf("Home dir: %s\n",p->pw_dir);
    printf("Shell: %s\n", p->pw_shell);
	return 0;
  } else {
    return NOUSER;
  }
}

void read_username(char *username)
{
  printf("login: ");
  fgets(username, USERNAME_SIZE, stdin);

  /* remove the newline included by getline() */
  username[strlen(username) - 1] = '\0';
}

void read_password(char *password)
{
  password=getpass("password: ");
  //printf("password: ");
  //fgets(password, USERNAME_SIZE, stdin);

  /* remove the newline included by getline() */
  password[strlen(password) - 1] = '\0';
}

int checkPassword(char username[], char password[]) {
  char salt[SALT_SIZE];
  struct pwdb_passwd *p = pwdb_getpwnam(username);
  if (p==NULL) {
    return 0;
  }
  strncpy(salt, p->pw_passwd, SALT_SIZE);

  int equa = strcmp(p->pw_passwd,crypt(password,salt));

  if (equa==0) {

    //printf("User authenticated successfully");
    return 1;
  } else {
    //printf("fail");
    return 0;
  }

}

int main(int argc, char **argv)
{
  while(1) {
    char username[USERNAME_SIZE];
    char password[USERNAME_SIZE];

    /*
     * Write "login: " and read user input. Copies the username to the
     * username variable.
     */
    read_username(username);
    read_password(password);

    if (checkPassword(username,password)) {
      printf("User authenticated successfully \n");
      return 1;
    } else {
      printf("Unknown username or incorrect password \n");
    }


    //if (print_info(username) == NOUSER) {
    //    /* if there are no user with that usename... */
    //    printf("\nFound no user with name: %s\n", username);
    //    return 0;
    //}
  }

  /* Show user info from our local pwfile. */

}
