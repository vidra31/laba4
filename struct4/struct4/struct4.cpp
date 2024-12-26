﻿
#include <stdlib.h>
#include <stdio.h>
#include <locale.h>
#include <iostream>

void bubbleSort(int arr[], int size) {
    for (int i = 0; i < size - 1; ++i) {
        for (int j = 0; j < size - i - 1; ++j) {
            if (arr[j] > arr[j + 1]) {
                std::swap(arr[j], arr[j + 1]);
            }
        }
    }
}

void shakerSort(int arr[], int size) {
    bool swapped = true;
    int start = 0, end = size - 1;

    while (swapped) {
        swapped = false;
        for (int i = start; i < end; ++i) {
            if (arr[i] > arr[i + 1]) {
                std::swap(arr[i], arr[i + 1]);
                swapped = true;
            }
        }
        if (!swapped) break;

        swapped = false;
        --end;

        for (int i = end - 1; i >= start; --i) {
            if (arr[i] > arr[i + 1]) {
                std::swap(arr[i], arr[i + 1]);
                swapped = true;
            }
        }
        ++start;
    }
}

void combSort(int arr[], int size) {
    int gap = size;
    const double shrink = 1.3;
    bool swapped = true;

    while (gap > 1 || swapped) {
        gap = std::max(1, int(gap / shrink));
        swapped = false;

        for (int i = 0; i + gap < size; ++i) {
            if (arr[i] > arr[i + gap]) {
                std::swap(arr[i], arr[i + gap]);
                swapped = true;
            }
        }
    }
}

void insertionSort(int arr[], int size) {
    for (int i = 1; i < size; ++i) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            --j;
        }
        arr[j + 1] = key;
    }
}

void merge(int arr[], int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    int* leftArr = new int[n1];
    int* rightArr = new int[n2];

    for (int i = 0; i < n1; ++i) leftArr[i] = arr[left + i];
    for (int i = 0; i < n2; ++i) rightArr[i] = arr[mid + 1 + i];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (leftArr[i] <= rightArr[j]) arr[k++] = leftArr[i++];
        else arr[k++] = rightArr[j++];
    }

    while (i < n1) arr[k++] = leftArr[i++];
    while (j < n2) arr[k++] = rightArr[j++];

    delete[] leftArr;
    delete[] rightArr;
}

void mergeSort(int arr[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

void selectionSort(int arr[], int size) {
    for (int i = 0; i < size - 1; ++i) {
        int minIdx = i;
        for (int j = i + 1; j < size; ++j) {
            if (arr[j] < arr[minIdx]) minIdx = j;
        }
        std::swap(arr[i], arr[minIdx]);
    }
}

void countingSort(int arr[], int size) {

    int minElem = arr[0];
    int maxElem = arr[0];
    for (int i = 1; i < size; ++i) {
        if (arr[i] < minElem) minElem = arr[i];
        if (arr[i] > maxElem) maxElem = arr[i];
    }

    int range = maxElem - minElem + 1;

    int* count = (int*)calloc(range, sizeof(int));

    if (!count) {
        std::cerr << "Memory allocation failed!" << std::endl;
        return;
    }

    for (int i = 0; i < size; ++i) {
        count[arr[i] - minElem]++;
    }

    int index = 0;
    for (int i = 0; i < range; ++i) {
        while (count[i] > 0) {
            arr[index++] = i + minElem;
            count[i]--;
        }
    }

    free(count);
}

void quickSort(int arr[], int left, int right) {
    if (left >= right) return;

    int pivot = arr[right];
    int i = left - 1;

    for (int j = left; j < right; ++j) {
        if (arr[j] <= pivot) {
            std::swap(arr[++i], arr[j]);
        }
    }
    std::swap(arr[i + 1], arr[right]);

    quickSort(arr, left, i);
    quickSort(arr, i + 2, right);
}

void heapify(int arr[], int size, int root) {
    int largest = root;
    int left = 2 * root + 1;
    int right = 2 * root + 2;

    if (left < size && arr[left] > arr[largest]) largest = left;
    if (right < size && arr[right] > arr[largest]) largest = right;

    if (largest != root) {
        std::swap(arr[root], arr[largest]);
        heapify(arr, size, largest);
    }
}

void heapSort(int arr[], int size) {
    for (int i = size / 2 - 1; i >= 0; --i) heapify(arr, size, i);
    for (int i = size - 1; i > 0; --i) {
        std::swap(arr[0], arr[i]);
        heapify(arr, i, 0);
    }
}

int binarySearch(int arr[], int size, int target) {
    int left = 0, right = size - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;

        if (arr[mid] == target) return mid;
        if (arr[mid] < target) left = mid + 1;
        else right = mid - 1;
    }
    return -1;
}

#define MAX_NODES 100
void bfs(int graph[MAX_NODES][MAX_NODES], int numNodes, int start) {
    int* visited = (int*)calloc(numNodes, sizeof(int));
    int* queue = (int*)malloc(numNodes * sizeof(int));
    int front = 0, rear = 0;

    queue[rear++] = start;
    visited[start] = 1;

    while (front < rear) {
        int node = queue[front++];
        std::cout << node << " ";

        for (int i = 0; i < numNodes; ++i) {
            if (graph[node][i] && !visited[i]) {
                queue[rear++] = i;
                visited[i] = 1;
            }
        }
    }

    free(queue);
    free(visited);
}


void dfsRecursive(int graph[MAX_NODES][MAX_NODES], int numNodes, int node, int* visited) {
    visited[node] = 1;
    std::cout << node << " ";

    for (int i = 0; i < numNodes; ++i) {
        if (graph[node][i] && !visited[i]) {
            dfsRecursive(graph, numNodes, i, visited);
        }
    }
}

void dfs(int graph[MAX_NODES][MAX_NODES], int numNodes, int start) {
    int* visited = (int*)calloc(numNodes, sizeof(int));
    dfsRecursive(graph, numNodes, start, visited);

    free(visited);
}

int main() {

    setlocale(LC_ALL, "Rus");
    int arr[100], size, target, index, numb, ctrl;
    bool flag = false;
    std::cout << "Введите кол-во элементов в массиве: ";
    std::cin >> size;
    std::cout << "Введите массив: ";
    for (int i = 0; i < size; i++)
    {
        std::cin >> numb;
        arr[i] = numb;
    }
    std::cout << "Выберите метод сортировки:\n1.Сортировка пузырьком\n2.Шейкерная сортировка\n3.Сортировка расчёской\n4.Сортировка вставками\n5.Сортировка слиянием\n6.Сортировка выбором\n7.Сортировка подсчётом.\n8.Быстрая сортировка\n9.Пирамидальная сортировка.\n10.Бинарный поиск.\n11.Выход.\n";
    std::cin >> ctrl;
    while (!(ctrl > 0 && ctrl < 12))
    {
        std::cout << "Введено неверное значение.";
        std::cin >> ctrl;
    }
    switch (ctrl)
    {
    case 1:
    {
        bubbleSort(arr, size);
        break;
    }
    case 2:
    {
        shakerSort(arr, size);
        break;
    }
    case 3:
    {
        combSort(arr, size);
        break;
    }
    case 4:
    {
        insertionSort(arr, size);
        break;
    }
    case 5:
    {
        mergeSort(arr, 0, size - 1);
        break;
    }
    case 6:
    {
        selectionSort(arr, size);
        break;
    }
    case 7:
    {
        countingSort(arr, size);
        break;
    }
    case 8:
    {
        quickSort(arr, 0, size - 1);
        break;
    }
    case 9:
    {
        heapSort(arr, size);
        break;
    }
    case 10:
    {
        std::cout << "Введите поисковой элемент: ";
        std::cin >> target;
        index = binarySearch(arr, size, target);
        if (index != -1)
        {
            std::cout << "Элемент " << target << " найден под индексом " << index << "\n";
        }
        else
        {
            std::cout << "Элемент не найден.";
        }
        flag = true;
        break;
    }
    case 11:
    {
        return 0;
    }
    }
    if (!flag)
    {
        std::cout << "Отсортированный массив: ";
        for (int i = 0; i < size; ++i) {
            std::cout << arr[i] << " ";
        }
        std::cout << std::endl;
    }

    int graph[MAX_NODES][MAX_NODES] = { 0 };
    int numnodes = 6;

    graph[0][1] = 1;
    graph[0][2] = 1;
    graph[1][3] = 1;
    graph[2][3] = 1;
    graph[3][4] = 1;

    std::cout << "BFS: ";
    bfs(graph, numnodes, 0);

    std::cout << "\nDFS: ";
    dfs(graph, numnodes, 0);
}