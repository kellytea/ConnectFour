/*
 * slist.c
 *
 *  Created on: Oct 1, 2023
 *      Author: kellytran
 */

#include <stdio.h>
#include <stdlib.h>
#include "slist.h"

void insertTail(slist* list, int row, int col, char player) {
	//Create a new node.
	struct Node* newNode;
	newNode = malloc(sizeof(struct Node));

	newNode->row = row;
	newNode->col = col;
	newNode->player = player;
	newNode->next = NULL;

	//Adjust pointers based on current list.
	if (list->head == NULL) {
		list->head = newNode;
	} else {
		list->tail->next = newNode;
	}
	list->tail = newNode;
}

void freeList(slist* list) { //Frees the list once the game is over.
	struct Node* current = list->head;
	while (current != NULL) {
		struct Node* temp = current;
		current = current->next;
		free(temp);
	}
	free(list);
}

