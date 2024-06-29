#include <bits/stdc++.h>
#include <ctime> // For time()

using namespace std;

// Assume a basic heap structure with relevant methods
struct Heap {
    vector<long long> heap;
    unordered_map<long long, long long> pointer_to_array;
    long long size;
    long long sum;

    Heap() : size(0), sum(0) {}

    void insert(long long pointer, long long value) {
        heap.push_back(value);
        sum += value;
        pointer_to_array[pointer] = heap.size() - 1;
        size++;
        push_heap(heap.begin(), heap.end());
    }

    void deleteMin() {
        pop_heap(heap.begin(), heap.end());
        sum -= heap.back();
        heap.pop_back();
        size--;
    }

    void deleteNumber(long long value, long long pointer) {
        sum -= value;
        long long index = pointer_to_array[pointer];
        swap(heap[index], heap.back());
        heap.pop_back();
        pointer_to_array.erase(pointer);
        size--;
        make_heap(heap.begin(), heap.end());
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

  
    srand(time(0));

    long long n = 1000;  
    long long k = rand() % n + 1;    

    cout << "n: " << n << ", k: " << k << endl;

    long long array[n];
    for (long long i = 0; i < n; ++i) {
        array[i] = rand() % 1000 + 1;  
    }


    Heap firstHalf;
    Heap secondHalf;
    secondHalf.insert(1, 1);

    firstHalf.insert(1, -array[0]);

    for (long long currentSize = 1; currentSize < k; currentSize++) {
        if (array[currentSize] <= -firstHalf.heap[0])
            firstHalf.insert(currentSize + 1, -array[currentSize]);
        else
            secondHalf.insert(currentSize + 1, array[currentSize]);

        if (firstHalf.size - secondHalf.size > 1) {
            secondHalf.insert(firstHalf.pointer_to_array[0], -firstHalf.heap[0]);
            firstHalf.deleteMin();
        } else if (secondHalf.size - firstHalf.size >= 1) {
            firstHalf.insert(secondHalf.pointer_to_array[0], -secondHalf.heap[0]);
            secondHalf.deleteMin();
        }
    }

    long long result = firstHalf.sum + secondHalf.sum;
    if (k % 2 == 1)
        result -= firstHalf.heap[0];
    cout << result << " ";

    for (long long i = k; i < n; ++i) {
        if (firstHalf.pointer_to_array[i - k + 1] == 0) {
            long long pointer = firstHalf.pointer_to_array[i - k + 1];
            firstHalf.deleteNumber(-array[i - k], pointer);
        } else {
            long long pointer = secondHalf.pointer_to_array[i - k + 1];
            secondHalf.deleteNumber(array[i - k], pointer);
        }

        if (array[i] <= -firstHalf.heap[0])
            firstHalf.insert(i + 1, -array[i]);
        else
            secondHalf.insert(i + 1, array[i]);

        if (-firstHalf.heap[0] > secondHalf.heap[0]) {
            long long p = firstHalf.pointer_to_array[0];
            long long v = -firstHalf.heap[0];
            firstHalf.insert(secondHalf.pointer_to_array[0], -secondHalf.heap[0]);
            secondHalf.insert(p, v);
            firstHalf.deleteMin();
            secondHalf.deleteMin();
        }

        if (firstHalf.size - secondHalf.size > 1) {
            secondHalf.insert(firstHalf.pointer_to_array[0], -firstHalf.heap[0]);
            firstHalf.deleteMin();
        } else if (secondHalf.size - firstHalf.size >= 1) {
            firstHalf.insert(secondHalf.pointer_to_array[0], -secondHalf.heap[0]);
            secondHalf.deleteMin();
        }

        result = firstHalf.sum + secondHalf.sum;
        if (k % 2 == 1)
            result -= firstHalf.heap[0];
       // cout << result << " ";
    }

    return 0;
}

