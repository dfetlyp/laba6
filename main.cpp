#include <iostream>
#include <vector>
#include <algorithm>

class SortingStrategy {
public:
    virtual void sort(std::vector<int>& values) = 0;
    virtual ~SortingStrategy() = default;
};

// Сортировка пузырьком
class BubbleSortStrategy : public SortingStrategy {
public:
    void sort(std::vector<int>& values) override {
        for (size_t i = 0; i < values.size(); ++i)
            for (size_t j = 0; j < values.size() - 1; ++j)
                if (values[j] > values[j + 1])
                    std::swap(values[j], values[j + 1]);
    }
};

// Быстрая сортировка
class QuickSortStrategy : public SortingStrategy {
public:
    void sort(std::vector<int>& values) override {
        quicksort(values, 0, values.size() - 1);
    }
private:
    void quicksort(std::vector<int>& a, int left, int right) {
        int i = left, j = right;
        int pivot = a[(left + right) / 2];
        while (i <= j) {
            while (a[i] < pivot) ++i;
            while (a[j] > pivot) --j;
            if (i <= j) std::swap(a[i++], a[j--]);
        }
        if (left < j) quicksort(a, left, j);
        if (i < right) quicksort(a, i, right);
    }
};

// Вставками
class InsertSortStrategy : public SortingStrategy {
public:
    void sort(std::vector<int>& values) override {
        for (size_t i = 1; i < values.size(); ++i) {
            int temp = values[i];
            int j = i - 1;
            while (j >= 0 && values[j] > temp) {
                values[j + 1] = values[j];
                --j;
            }
            values[j + 1] = temp;
        }
    }
};

class Sorter {
private:
    SortingStrategy* strategy;
public:
    explicit Sorter(SortingStrategy* algo) : strategy(algo) {}
    void sortData(std::vector<int>& data) {
        strategy->sort(data);
    }
};

// Вывод
void printArray(const std::vector<int>& arr, const std::string& label) {
    std::cout << label << ": ";
    for (int x : arr) std::cout << x << " ";
    std::cout << "\n";
}

int main() {
    std::vector<int> base = { 4, 3, 9, 1, 4, 7 };

    BubbleSortStrategy bubble;
    QuickSortStrategy quick;
    InsertSortStrategy insert;

    std::vector<int> set1 = base;
    std::vector<int> set2 = base;
    std::vector<int> set3 = base;

    Sorter bubbleSort(&bubble);
    Sorter quickSort(&quick);
    Sorter insertionSort(&insert);

    bubbleSort.sortData(set1);
    quickSort.sortData(set2);
    insertionSort.sortData(set3);

    printArray(base, "Base");
    printArray(set1, "Bubble");
    printArray(set2, "Quick");
    printArray(set3, "Insert");

    return 0;
}
