/*************************************************************
 * File: pqueue-linkedlist.cpp
 *
 * Implementation file for the LinkedListPriorityQueue
 * class.
 */
 
#include "pqueue-linkedlist.h"
#include "error.h"

LinkedListPriorityQueue::LinkedListPriorityQueue() {
	head = NULL;
	length = 0;
}

LinkedListPriorityQueue::~LinkedListPriorityQueue() {
	while (head != NULL) {
		Cell* next = head->next;
		delete head;
		head = next;
	}
}

int LinkedListPriorityQueue::size() {
	return length;
}

bool LinkedListPriorityQueue::isEmpty() {
	return size() == 0;
}

void LinkedListPriorityQueue::enqueue(string value) {
	length++;
	Cell* newCell = new Cell;
	newCell->value = value;
	if (head == NULL || head->value >= value) {
		newCell->next = head;
		head = newCell;
	} else {
		Cell* current = head;
		while (current->next != NULL && current->next->value < value){
			current = current->next;
		}
		newCell->next = current->next;
		current->next = newCell;
	}
}

string LinkedListPriorityQueue::peek() {
	if (isEmpty()) {
		error("No Elements");
	} 
	return head->value;
}

string LinkedListPriorityQueue::dequeueMin() {
	if (isEmpty()) {
		error("No Elements");
	} 
	length--;
	string s = head->value;
	Cell* newHead = head->next;
	head = newHead;
	return s;
}

