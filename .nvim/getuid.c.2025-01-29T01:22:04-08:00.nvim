#include <pwd.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
  uid_t id;
  struct passwd *p;

  p = getpwuid(id = getuid());

  printf("%s", p->pw_dir);
}
