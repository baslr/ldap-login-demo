#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <lber.h>
#include <ldap.h>

#define RCSID "$Id: ldap_add.c,v 1.3 2003/07/14 15:21:56 rory Exp $"

// from http://www.linuxdevcenter.com/pub/a/linux/2003/08/14/libldap.html
// compile: gcc -o ldap_login ldap.c -lldap -llber

int main( int argc, char *argv[] ) {
  LDAP *ld;
  int  result;
  int  auth_method = LDAP_AUTH_SIMPLE;
  int desired_version = LDAP_VERSION3;
  char *ldap_host = "ldap.forumsys.com";
  char *root_dn = "uid=euler,dc=example,dc=com";
  char *root_pw = "password";

/*
OPTS = {
  server: {
    url: 'ldap://ldap.forumsys.com:389',
    bindDn: 'cn=read-only-admin,dc=example,dc=com',
    bindCredentials: 'password',
    searchBase: 'dc=example,dc=com',
    searchFilter: '(uid={{username}})'
  }
};
*/

  if ((ld = ldap_init(ldap_host, LDAP_PORT)) == NULL ) {
    perror( "ldap_init failed" );
    exit( EXIT_FAILURE );
  }

  /* set the LDAP version to be 3 */
  if (ldap_set_option(ld, LDAP_OPT_PROTOCOL_VERSION, &desired_version) != LDAP_OPT_SUCCESS)
   {
      ldap_perror(ld, "ldap_set_option");
      exit(EXIT_FAILURE);
   }
   
  if (ldap_bind_s(ld, root_dn, root_pw, auth_method) != LDAP_SUCCESS ) {
    ldap_perror( ld, "ldap_bind" );
    exit( EXIT_FAILURE );
  }

  result = ldap_unbind_s(ld);
  
  if (result != 0) {
    fprintf(stderr, "ldap_unbind_s: %s\n", ldap_err2string(result));
    exit( EXIT_FAILURE );
  }

  return EXIT_SUCCESS;
}
