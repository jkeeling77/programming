
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"

#define LIST_SIZE 10

void destroy_list_entry(void* data) {
    if( data != NULL) {
        free(data);
    }
}

void print_list_entry(void* data) {
   if( data != NULL ) {
      printf("%s ", (char*)data);
   }
}

int match_list_entry(const void* dataa, const void* datab) {
   int match;

   if( dataa == NULL && datab == NULL) {
      match = 0;
   }
   else if( dataa == NULL || datab == NULL) {
   	  match = 1;
   }
   else {
      match = strcmp( (char*)dataa, (char*)datab);
   }

   return match;
}

int main(void) {
	List* list;
   unsigned int data_length;
	char* data;
	char* name_list[LIST_SIZE] = {"larry", "curly", "elderly", "legs", "Eli",
	                              "blix", "hans", "Moasedlri", "Flynn", "Barfo"};

    list = (List*)malloc(sizeof(List));
    list_init(list, destroy_list_entry, print_list_entry, match_list_entry);

    for(int i = 0; i < LIST_SIZE; i++) {
      data_length = strlen(name_list[i]);
    	data = (char*)malloc(data_length+1);
    	if( !data ) {
         printf("ERROR: failed to malloc data, i[%d]\n", i);
    	}
    	else {
         strncpy(data, name_list[i], data_length);
         data[data_length] = '\0';
         //list_ins_next(list, NULL, data);
         list_insert(list, data);
    	}
    }

    printf("pre sort:\n");
    list_print(list);
    list_sort(list);
    printf("post sort:\n");
    list_print(list);

    return 0;
}
