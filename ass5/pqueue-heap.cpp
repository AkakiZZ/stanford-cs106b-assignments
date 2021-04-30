/*************************************************************
 * File: pqueue-heap.cpp
 *
 * Implementation file for the HeapPriorityQueue
 * class.
 */
 
#include "pqueue-heap.h"
#include "error.h"

HeapPriorityQueue::HeapPriorityQueue() {
	length = 0;
	allocLen = 10;
	heap = new string[allocLen];
}

HeapPriorityQueue::~HeapPriorityQueue() {
	delete[] heap;
}

int HeapPriorityQueue::size() {
	return length;
}

bool HeapPriorityQueue::isEmpty() {
	return size() == 0;
}

void HeapPriorityQueue::enqueue(string value) {
	if (allocLen == length) grow();
	heap[length] = value;
	bubbleUp(length);
	length++;
}

string HeapPriorityQueue::peek() {
	if (isEmpty()) error("No elements");
	return heap[0];
}

string HeapPriorityQueue::dequeueMin() {
	if (isEmpty()) error("No elements");
	string res = heap[0];
	swap(0, length - 1);
	length--;
	bubbleDown();
	return res;
}

void HeapPriorityQueue::grow() {
	allocLen *= 2;
	string* newHeap = new string[allocLen * 2];
	for (int i = 0; i < length; i++) {
		newHeap[i] = heap[i];
	}
	delete[] heap;
	heap = newHeap;
}

void HeapPriorityQueue::bubbleUp(int index) {
	while(heap[index] < heap[index / 2]) {
		swap(index, index / 2);
		index = index / 2;
	}
}

void HeapPriorityQueue::bubbleDown() {
	int index = 0;
	while ((2 * index < length)) {
		string first = heap[2 * index];
		string second;
		if (2 * index + 1 < length) {
			second = heap[2 * index + 1];
			if (first < second && heap[index] > first) {
				swap(index, 2 * index);
				index *= 2;
			} else if (first >= second && heap[index] > second) {
				swap(index, 2 * index + 1);
				index = 2 * index + 1;
			} else {
				break;
			}
		} else {
			if (heap[index] > first) {
				swap(index, 2 * index);
				index *= 2;
			} else {
				break;
			}
		}
	}
}

void HeapPriorityQueue::swap(int i, int j) {
	string tmp = heap[i];
	heap[i] = heap[j];
	heap[j] = tmp;
}

