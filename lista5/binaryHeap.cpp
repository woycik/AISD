#include <iostream>
#include <vector>

using namespace std;

class BinaryHeap {
private:
    vector<int> heap;

    int getParentIndex(int childIndex) {
        return (childIndex - 1) / 2;
    }

    int getLeftChildIndex(int parentIndex) {
        return 2 * parentIndex + 1;
    }

    int getRightChildIndex(int parentIndex) {
        return 2 * parentIndex + 2;
    }

    void heapifyUp(int index) {
        if (index == 0) {
            return;
        }

        int parentIndex = getParentIndex(index);
        if (heap[index] < heap[parentIndex]) {
            swap(heap[index], heap[parentIndex]);
            heapifyUp(parentIndex);
        }
    }

    void heapifyDown(int index) {
        int leftChildIndex = getLeftChildIndex(index);
        int rightChildIndex = getRightChildIndex(index);
        int smallestIndex = index;

        if (leftChildIndex < heap.size() && heap[leftChildIndex] < heap[smallestIndex]) {
            smallestIndex = leftChildIndex;
        }

        if (rightChildIndex < heap.size() && heap[rightChildIndex] < heap[smallestIndex]) {
            smallestIndex = rightChildIndex;
        }

        if (smallestIndex != index) {
            swap(heap[index], heap[smallestIndex]);
            heapifyDown(smallestIndex);
        }
    }

public:
    bool isEmpty() {
        return heap.empty();
    }

    void insert(int value) {
        heap.push_back(value);
        heapifyUp(heap.size() - 1);
    }

    int getMin() {
        if (isEmpty()) {
            throw out_of_range("Heap is empty");
        }
        return heap[0];
    }

    void deleteMin() {
        if (isEmpty()) {
            throw out_of_range("Heap is empty");
        }

        heap[0] = heap.back();
        heap.pop_back();
        heapifyDown(0);
    }

    void merge(BinaryHeap& otherHeap) {
        heap.insert(heap.end(), otherHeap.heap.begin(), otherHeap.heap.end());
        int startIndex = (heap.size() - 2) / 2;  
        for (int i = startIndex; i >= 0; i--) {
            heapifyDown(i);
        }
    }
};

int main() {
    BinaryHeap heap;

    heap.insert(5);
    heap.insert(7);
    heap.insert(3);
    heap.insert(10);
    heap.insert(2);

    cout << "Minimum value: " << heap.getMin() << endl;

    heap.deleteMin();

    cout << "Minimum value after deletion: " << heap.getMin() << endl;

    return 0;
}
