/*
 * slist.h
 *
 *  Created on: Oct 1, 2023
 *      Author: kellytran
 */

#ifndef slist_h
#define slist_h
#include <stdio.h>
#define ROWS 6
#define COLS 7

struct Node {
	int row;
	int col;

	char player;
	struct Node* next;
};

struct singlylinkedlist {
	struct Node* head;
	struct Node* tail;
};

typedef struct singlylinkedlist slist;

void insertTail(slist* list, int row, int col, char player);
void freeList(slist* list);


#endif /* slist_h */
