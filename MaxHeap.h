#pragma once

template <class T>
class MaxHeap {
private:
	int heapSize, maxSize;
	T* heap;
	void swap(int, int);
public:
	class EmptyHeapException {};
	class FullHeapException {};
	MaxHeap(int);
	~MaxHeap();
	void add(T);
	T extractMax();
	bool isEmpty() const;
};

///////////////////////////////
// Implementation of MaxHeap //
///////////////////////////////

template <class T>
MaxHeap<T>::MaxHeap(int size) {
	heapSize = 0;
	maxSize = size;
	// Allocate memory for an array of given size
	heap = new T[size];
}

template <class T>
MaxHeap<T>::~MaxHeap() {
	// Free memory
	delete heap;
}

template <class T>
void MaxHeap<T>::add(T item) {
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
		// Swap node with parent if needed
		if (int(heap[parentIdx]) < currValue) {
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
T MaxHeap<T>::extractMax() {
	// Throw exception if trying to extract from empty heap
	if (heapSize == 0) {
		throw EmptyHeapException();
	}

	// Swap root with last leaf then decrement 
	// heapSize variable, essentially deleting 
	// the node. Root node is now out of place
	// (heap is no longer a heap)
	T maxItem = heap[0];
	heap[0] = heap[heapSize - 1];
	int currValue = int(heap[0]);
	--heapSize;

	// indecies of left and right children of root
	int leftIdx = 1;
	int rightIdx = 2;
	int currIdx = 0;

	// "sink" node so that we have a valid heap again
	while (true) {
		// This is a max heap, so we want to sink the
		// node if it is less than the children. Chooses
		// the direction of the greater node.
		if (rightIdx < heapSize && int(heap[rightIdx]) > currValue && int(heap[rightIdx]) >= int(heap[leftIdx])) {
			swap(currIdx, rightIdx);
			currIdx = rightIdx;
			leftIdx = currIdx * 2 + 1;
			rightIdx = currIdx * 2 + 2;
		}
		else if (leftIdx < heapSize && int(heap[leftIdx]) > currValue) {
			swap(currIdx, leftIdx);
			currIdx = leftIdx;
			leftIdx = currIdx * 2 + 1;
			rightIdx = currIdx * 2 + 2;
		}
		// Break if node is in the correct position or
		// if it is a leaf (sunk to the bottom)
		else
			break;
	}

	return maxItem;
}

// helper function for swapping nodes in heap array
template <class T>
void MaxHeap<T>::swap(int a, int b) {
	T temp = heap[a];
	heap[a] = heap[b];
	heap[b] = temp;
}

template <class T>
bool MaxHeap<T>::isEmpty() const {
	return heapSize == 0;
}