#pragma once

template <class T>
class MinHeap {
private:
	int heapSize, maxSize;
	T* heap;
	void swap(int, int);
public:
	class EmptyHeapException {};
	class FullHeapException {};
	MinHeap(int);
	~MinHeap();
	void add(T);
	T extractMin();
	bool isEmpty() const;
};

///////////////////////////////
// Implementation of MinHeap //
///////////////////////////////

template <class T>
MinHeap<T>::MinHeap(int size) {
	heapSize = 0;
	maxSize = size;
	// Allocate memory for an array of given size
	heap = new T[size];
}

template <class T>
MinHeap<T>::~MinHeap() {
	// Free memory
	delete heap;
}

template <class T>
void MinHeap<T>::add(T item) {
	// Throw exception if heap is full since the
	// implementation has static size
	if (heapSize == maxSize) {
		throw FullHeapException();
	}

	// Insert node into first open index of array
	// to maintain the complete tree
	heap[heapSize] = item;
	int currValue = int(item);
	int currIdx = heapSize;
	// Index of parent node of inserted node
	int parentIdx = (currIdx - 1) / 2;
	++heapSize;

	// Bubble node up so heap invariant is satisfied
	while (true) {
		// Break if node is at top
		if (currIdx == 0)
			break;

		// Swap node with parent if needed, performing
		// the "bubble up"
		if (int(heap[parentIdx]) > currValue) {
			swap(parentIdx, currIdx);
			currIdx = parentIdx;
			parentIdx = (currIdx - 1) / 2;
		}
		// Break if current orientation is a heap
		else
			break;
	}
}

template <class T>
T MinHeap<T>::extractMin() {
	// Throw exception if trying to extract from empty heap
	if (heapSize == 0) {
		throw EmptyHeapException();
	}

	// Swap root with last leaf then decrement 
	// heapSize variable, essentially deleting 
	// the node. Root node is now out of place
	// (heap is no longer a heap)
	T minItem = heap[0];
	heap[0] = heap[heapSize - 1];
	int currValue = int(heap[0]);
	--heapSize;

	// indecies of left and right children of root
	int leftIdx = 1;
	int rightIdx = 2;
	int currIdx = 0;

	// "sink" node so that we have a valid heap again
	while (true) {
		// This is a min heap, so we want to sink the
		// node if it is greater than the children.
		// Chooses the direction of the lesser node.
		if (leftIdx < heapSize && int(heap[leftIdx]) < currValue && int(heap[leftIdx]) <= int(heap[rightIdx])) {
			swap(currIdx, leftIdx);
			currIdx = leftIdx;
			leftIdx = currIdx * 2 + 1;
			rightIdx = currIdx * 2 + 2;
		}
		else if (rightIdx < heapSize && int(heap[rightIdx]) < currValue) {
			swap(currIdx, rightIdx);
			currIdx = rightIdx;
			leftIdx = currIdx * 2 + 1;
			rightIdx = currIdx * 2 + 2;
		}
		// Break if node is in the correct position or
		// if it is a leaf (sunk to the bottom)
		else
			break;
	}

	return minItem;
}

// helper function for swapping nodes in heap array
template <class T>
void MinHeap<T>::swap(int a, int b) {
	T temp = heap[a];
	heap[a] = heap[b];
	heap[b] = temp;
}

template <class T>
bool MinHeap<T>::isEmpty() const {
	return heapSize == 0;
}