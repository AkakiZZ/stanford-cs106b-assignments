/*************************************************************
 * File: pqueue-doublylinkedlist.cpp
 *
 * Implementation file for the DoublyLinkedListPriorityQueue
 * class.
 */
 
#include "pqueue-doublylinkedlist.h"
#include "error.h"

DoublyLinkedListPriorityQueue::DoublyLinkedListPriorityQueue() {
	length = 0;
	head = NULL;
}

DoublyLinkedListPriorityQueue::~DoublyLinkedListPriorityQueue() {
	while (head != NULL) {
		Cell* next = head->next;
		delete head;
		head = next;
	}
}

int DoublyLinkedListPriorityQueue::size() {
	return length;
}

bool DoublyLinkedListPriorityQueue::isEmpty() {
	return size() == 0;
}

void DoublyLinkedListPriorityQueue::enqueue(string value) {
	length++;
	Cell* newCell = new Cell;
	newCell->value = value;
	newCell->next = NULL;
	newCell->previous = NULL;
	if (head == NULL) {
		head = newCell;
	} else {
		Cell* current = head;
		while (current->next != NULL) {
			current = current->next;
		}
		current->next = newCell;
		newCell->previous = current;
	}
}

string DoublyLinkedListPriorityQueue::peek() {
	if (isEmpty()) 
		error("No elements");
	string min = head->value;
	Cell* current = head;
	while(current->next != NULL) {
		current = current->next;
		if (current->value < min) {
			min = current->value;
		}
	}
	
	return min;
}

string DoublyLinkedListPriorityQueue::dequeueMin() {
	if (isEmpty()) 
		error("No elements");
	length--;
	string min = head->value;
	Cell* minCell = head;
	Cell* current = head;
	while(current->next != NULL) {
		current = current->next;
		if (current->value < min) {
			min = current->value;
			minCell = current;
		}
	}
	if (minCell->previous == NULL && minCell->next == NULL) {
		head = NULL;
		delete minCell;
	} else if (minCell->previous == NULL) {
		minCell->next->previous = NULL;
		head = minCell->next;
		delete minCell;
	} else if (minCell->next == NULL) {
		minCell->previous->next = NULL;
		delete minCell;
	} else {
		minCell->previous->next = minCell->next;
		minCell->next->previous = minCell->previous;
	}
	return min;
}

