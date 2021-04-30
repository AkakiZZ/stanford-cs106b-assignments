/*************************************************************
 * File: pqueue-vector.cpp
 *
 * Implementation file for the VectorPriorityQueue
 * class.
 */
 
#include "pqueue-vector.h"
#include "error.h"

VectorPriorityQueue::VectorPriorityQueue() {

}

VectorPriorityQueue::~VectorPriorityQueue() {
	// TODO: Fill this in!
}

int VectorPriorityQueue::size() {
	return v.size();
}

bool VectorPriorityQueue::isEmpty() {
	return size() == 0;
}

void VectorPriorityQueue::enqueue(string value) {
	v.add(value);
}

string VectorPriorityQueue::peek() {
	if (size() == 0) {
		error("No ellements");
	}
	string min = v[0];
	for (int i = 0; i < v.size(); i++) {
		if (v[i] < min) min = v[i];
	}
	return min;
}

string VectorPriorityQueue::dequeueMin() {
	if (size() == 0) {
		error("No ellements");
	}
	string min = v[0];
	int index = 0;
	for (int i = 0; i < v.size(); i++) {
		if (v[i] < min) {
			min = v[i];
			index = i;
		}
	}
	v.remove(index);
	return min;
}

