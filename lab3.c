#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main() {
  char inputs[5][32] = {"", "", "", "", ""};
  int current = 0;
  size_t line = 0;
  int size = 0;

  while (1 == 1) {
    printf("Enter input: ");
    char *temp;

    getline(&temp, &line, stdin);
    strcpy(inputs[current], strtok(temp, "\n"));

    if (strcmp(temp, "print") == 0) {
      for (int i = current; i >= 0; i--) {
        printf("%s\n", inputs[i]);
      }
      for (int i = size - 2; i > current; i--) {
        printf("%s\n", inputs[i]);
      }
    }

    current++;
    if (current >= 5) {
      current = 0;
    }

    if (size < 6)
      size++;
  }
  return 0;
}
