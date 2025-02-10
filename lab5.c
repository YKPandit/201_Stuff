#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

struct header {
  uint64_t size;
  struct header *next;
  int id;
};

void initialize_block(struct header *block, uint64_t size, struct header *next,
                      int id) {
  block->size = size;
  block->next = next;
  block->id = id;
}

int find_first_fit(struct header *free_list_ptr, uint64_t size) {
  struct header *trav = free_list_ptr;
  while (trav) {
    if (trav->size > size) {
      return trav->id;
    }
    trav = trav->next;
  }
  return -1;
}

int find_best_fit(struct header *free_list_ptr, uint64_t size) {
  int best_fit_id = -1;
  // TODO: Implement best fit
  struct header *trav = free_list_ptr;
  int save = 1000;
  while (trav) {
    if (trav->size >= size && trav->size < save) {
      save = trav->size;
      best_fit_id = trav->id;
    }
    trav = trav->next;
  }

  return best_fit_id;
}

int find_worst_fit(struct header *free_list_ptr, uint64_t size) {
  int worst_fit_id = -1;
  // TODO: Implement worst fit
  struct header *trav = free_list_ptr;
  int save = 0;
  while (trav) {
    if (trav->size >= size && trav->size > save) {
      save = trav->size;
      worst_fit_id = trav->id;
    }
    trav = trav->next;
  }

  return worst_fit_id;
}

int main(void) {

  struct header *free_block1 = (struct header *)malloc(sizeof(struct header));
  struct header *free_block2 = (struct header *)malloc(sizeof(struct header));
  struct header *free_block3 = (struct header *)malloc(sizeof(struct header));
  struct header *free_block4 = (struct header *)malloc(sizeof(struct header));
  struct header *free_block5 = (struct header *)malloc(sizeof(struct header));

  initialize_block(free_block1, 6, free_block2, 1);
  initialize_block(free_block2, 12, free_block3, 2);
  initialize_block(free_block3, 24, free_block4, 3);
  initialize_block(free_block4, 8, free_block5, 4);
  initialize_block(free_block5, 4, NULL, 5);

  struct header *free_list_ptr = free_block1;

  int first_fit_id = find_first_fit(free_list_ptr, 7);
  int best_fit_id = find_best_fit(free_list_ptr, 7);
  int worst_fit_id = find_worst_fit(free_list_ptr, 7);

  // TODO: Print out the IDs
  printf("%d\n", first_fit_id);
  printf("%d\n", best_fit_id);
  printf("%d\n", worst_fit_id);

  return 0;
}

/*
 * second
 * previous node
 * while( you havent hit the end of the linked list)
 *  compare the addresses of the  2 blocks
 *  merge them
 *
 * done
 *
 * */
