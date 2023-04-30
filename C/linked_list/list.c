
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "list.h"

/******************************************************************
 *                                                                *
 *                                                                *
 ******************************************************************/

static void swap(ListElmt* a, ListElmt* b) { 
    void* temp = a->data; 
    a->data = b->data; 
    b->data = temp; 
} 

/******************************************************************/

void list_init(List* pList,
	           void (*destroy)(void* data),
	           void (*print)(void* data),
	           int (*match)(const void* dataA, const void* dataB)) {

	pList->size = 0;
	pList->destroy = destroy;
	pList->print = print;
	pList->match = match;
	pList->head = NULL;
	pList->tail = NULL;
}

/******************************************************************/

void list_destroy(List* list) {
	void* data;
    printf("IN:  list_destroy()\n");
	while( list_size(list) > 0 ) {
		if( list_rem_next(list, NULL, (void**)&data) == 0 && list->destroy != NULL) {
			list->destroy(data);
		}
	}

	memset(list, 0, sizeof(List));
    printf("IN:  list_destroy()\n\n");

	return;
}

/******************************************************************
 *                                                                *
 *                                                                *
 ******************************************************************/

void list_print(List* list) {
	void* data;
    ListElmt* list_entry = list_head(list);

    //while( !list_is_tail(list_entry)) {
    while( list_entry != NULL ) {
    	list->print(list_data(list_entry));
    	list_entry = list_next(list_entry);
	}

    printf("\n");

	return;
}

/******************************************************************
 *                                                                *
 *                                                                *
 ******************************************************************/

int list_insert(List* pList, const void* data) {
	ListElmt* pListElmt = NULL;
	int retval = 1;

	printf("IN:  list_insert()\n");

    if( data != NULL ) {
    	printf("  data: ");
    	pList->print((void*)data);
    	printf("\n");

        if( (pListElmt = (ListElmt*)malloc(sizeof(ListElmt))) != NULL) {
        	pListElmt->data = (void*)data;
        	pListElmt->next = NULL;

        	if(list_size(pList) == 0) {
        		pList->tail = pListElmt;
        	}
        	
        	pListElmt->next = list_head(pList);
        	pList->head = pListElmt;
        	pList->size++;
        }
    }

    printf("OUT: list_insert()\n");

    return retval;
}

/******************************************************************
 *                                                                *
 *                                                                *
 ******************************************************************/

int list_remove(List* pList, const void* data) {
    int retval = 0;

    return retval;
}

/******************************************************************
 *                                                                *
 *                                                                *
 ******************************************************************/


int list_ins_next(List* list, ListElmt* element, const void* data) {
	ListElmt* new_element;

    printf("IN:  list_ins_next()\n");
    if( data != NULL ) {
    	printf("  data: ");
    	list->print((void*)data);
    	printf("\n");
    }
	if( (new_element = (ListElmt*)malloc(sizeof(ListElmt))) == NULL) {
		return -1;
	}

	new_element->data = (void*)data;

	if( element == NULL ) {
		if(list_size(list) == 0) {
           list->tail = new_element;
	    }	

	    new_element->next = list->head;
		list->head = new_element;
	}
	else {
		if(element->next == NULL) {
			list->tail = new_element;
		}

		new_element->next = element->next;
		element->next = new_element;
	}
	
	list->size++;

    printf("OUT: list_ins_next()\n\n");
	return 0;
}

/******************************************************************
 *                                                                *
 *                                                                *
 ******************************************************************/

int list_rem_next(List* list, ListElmt* element, void** data) {
	ListElmt* old_element;

	if( list_size(list) == 0 ) {
		return -1;
	}

	if( element == NULL ) {
		*data = list->head->data;
		old_element = list->head;
		list->head = list->head->next;

		if( list_size(list) == 1) {
			list->tail = NULL;
		}
	}
    else {
    	if( element->next == NULL) {
    		return -1;
    	}

    	*data = element->next->data;
    	old_element = element->next;
    	element->next = element->next->next;

    	if( element->next == NULL ) {
    		list->tail = element;
    	}
    }

    free(old_element);
    list->size--;
    return 0;
}

/******************************************************************
 *                                                                *
 *                                                                *
 ******************************************************************/
int list_size(List* pList) {
   int list_length = 0;

   if( pList != NULL ) {
      list_length = pList->size;
   }

   return list_length;
}

/******************************************************************
 *                                                                *
 *                                                                *
 ******************************************************************/

ListElmt* list_head(List* pList) {
	ListElmt* pListElmt = NULL;

	if( pList != NULL) {
		pListElmt = pList->head;
	}

	return pListElmt;
}

/******************************************************************
 *                                                                *
 *                                                                *
 ******************************************************************/

ListElmt* list_tail(List* pList) {
	ListElmt* pListElmt = NULL;

	if( pList != NULL) {
		pListElmt = pList->tail;
	}

	return pListElmt;
}

/******************************************************************
 *                                                                *
 *                                                                *
 ******************************************************************/

int list_is_head(List* pList, ListElmt* pListElmt) {
	int head = 0;

	if( pList != NULL && pListElmt != NULL ) {
		if(pListElmt == pList->head) {
			head = 1;
		}
	}

    return head;
}

/******************************************************************
 *                                                                *
 *                                                                *
 ******************************************************************/

int list_is_tail(ListElmt* pListElmt) {
	int tail = 0;

	if( pListElmt != NULL ) {
		if(pListElmt->next == NULL) {
			tail = 1;
		}
	}
	return tail;
}

/******************************************************************
 *                                                                *
 *                                                                *
 ******************************************************************/

void* list_data(ListElmt* pListElmt) {
    void* pData = NULL;

    if( pListElmt != NULL ) {
        pData = pListElmt->data;
    }

    return pData;
}

/******************************************************************
 *                                                                *
 *                                                                *
 ******************************************************************/

ListElmt* list_next(ListElmt* pListElmt_in) {
    ListElmt* pListElmt = NULL;

    if( pListElmt_in != NULL ) {
        pListElmt = pListElmt_in->next;
    }

    return pListElmt;
}

/******************************************************************
 *                                                                *
 *                                                                *
 ******************************************************************/

void list_sort(List* pList) {
    int swapped, i; 
    ListElmt* ptr1; 
    ListElmt* lptr = NULL; 
    ListElmt* pHead;
  
    if (pList != NULL) {
        pHead = list_head(pList);

        do { 
            swapped = 0; 
            ptr1 = pHead; 
  
            while (ptr1->next != lptr) { 
                if( pList->match(ptr1->data, ptr1->next->data) > 0) { 
                    swap(ptr1, ptr1->next); 
                    swapped = 1; 
                } 
                ptr1 = ptr1->next; 
            } 
            lptr = ptr1; 
        } 
        while (swapped);
    } 
}