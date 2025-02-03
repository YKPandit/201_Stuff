#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

#define BUF_SIZE 128

struct header {
  uint64_t size;
  struct header *next;
};

void print_out(char *format, void *data, size_t data_size) {
  char buf[BUF_SIZE];
  ssize_t len = snprintf(buf, BUF_SIZE, format,
                         data_size == sizeof(uint64_t) ? *(uint64_t *)data
                                                       : *(void **)data);
  if (len < 0) {
    // handle_error("snprintf");
  }
  write(STDOUT_FILENO, buf, len);
}

int main() {
  struct header *struct1 = (struct header *)sbrk(128);
  struct header *struct2 = (struct header *)sbrk(128);
  print_out("first block: %p\n", &struct1, sizeof(struct1));
  print_out("second block: %p\n", &struct2, sizeof(struct2));

  struct2->next = struct1;
  struct2->size = 128;
  print_out("first block size: %d\n", &(struct1->size), sizeof(struct1->size));
  print_out("first block next: %p\n", &(struct1->next), sizeof(struct1->next));

  struct1->next = NULL;
  struct1->size = 128;
  print_out("second block size: %d\n", &(struct2->size), sizeof(struct2->size));
  print_out("second block next: %p\n", &(struct2->next), sizeof(struct2->next));

  uint64_t data = 1;
  uint8_t *dataset2 = (uint8_t *)(&struct2 + sizeof(struct header));
  memset(dataset2, data, (struct2->size - sizeof(struct header)));

  for (int i = 0; i < struct2->size - sizeof(struct header); i++) {
    printf("%d\n", dataset2[i]);
  }
  write(1, "-----------\n", strlen("-----------\n"));
  data = 0;
  uint8_t *dataset1 = (uint8_t *)(&struct1 + sizeof(struct header));
  memset(dataset1, data, (struct1->size - sizeof(struct header)));

  for (int i = 0; i < struct2->size - sizeof(struct header); i++) {
    printf("%d\n", dataset1[i]);
  }
}
