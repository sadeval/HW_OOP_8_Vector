#include <iostream>
#include <cstdlib> 
#include <ctime>   

using namespace std;

class ArrayList
{
    unsigned int size = 0;       // количество действительно присутствующих элементов в контейнере
    unsigned int capacity = 10;  // ёмкость (вместительность, запас памяти)
    int* data = nullptr;         // указатель на динамический массив целых чисел

    void EnsureCapacity(unsigned int newCapacity)
    {
        if (newCapacity <= capacity) return;

        int* newData = new int[newCapacity];
        for (unsigned int i = 0; i < size; i++) {
            newData[i] = data[i];
        }

        delete[] data;
        data = newData;
        capacity = newCapacity;
    }

public:
    ArrayList() : ArrayList(10) {}

    ArrayList(unsigned int capacity)
    {
        if (capacity < 10) {
            capacity = 10;
        }
        this->capacity = capacity;
        data = new int[capacity];
    }

    ~ArrayList()
    {
        if (data != nullptr) {
            delete[] data;
            data = nullptr;
        }
    }

    unsigned int GetSize() const
    {
        return size;
    }

    unsigned int GetCapacity() const
    {
        return capacity;
    }

    void PushBack(int value)
    {
        EnsureCapacity(size + 1);
        data[size++] = value;
    }

    void PushFront(int value)
    {
        EnsureCapacity(size + 1);
        for (int i = size; i > 0; i--) {
            data[i] = data[i - 1];
        }
        data[0] = value;
        size++;
    }

    void Clear()
    {
        size = 0;
    }

    bool IsEmpty() const
    {
        return size == 0;
    }

    void Print() const
    {
        if (IsEmpty()) {
            cout << "Vector is empty.\n";
            return;
        }

        for (int i = 0; i < size; i++) {
            cout << data[i] << " ";
        }
        cout << "\n";
    }

    void Remove(int value)
    {
        unsigned int writeIndex = 0;
        for (unsigned int readIndex = 0; readIndex < size; readIndex++) {
            if (data[readIndex] != value) {
                data[writeIndex++] = data[readIndex];
            }
        }
        size = writeIndex;
    }

    void Reverse()
    {
        for (unsigned int i = 0; i < size / 2; i++) {
            int temp = data[i];
            data[i] = data[size - i - 1];
            data[size - i - 1] = temp;
        }
    }

    void SortDesc()
    {
        for (unsigned int i = 0; i < size - 1; i++) {
            for (unsigned int j = 0; j < size - i - 1; j++) {
                if (data[j] < data[j + 1]) {
                    int temp = data[j];
                    data[j] = data[j + 1];
                    data[j + 1] = temp;
                }
            }
        }
    }

    void RandomFill(unsigned int count, int minVal, int maxVal)
    {
        srand(time(nullptr));
        EnsureCapacity(size + count);
        for (unsigned int i = 0; i < count; i++) {
            data[size++] = minVal + rand() % (maxVal - minVal + 1);
        }
    }

    void RandomlyUserInput()
    {
        unsigned int count;
        int minVal, maxVal;
        cout << "Enter the number of elements: ";
        cin >> count;
        cout << "Enter the minimum value: ";
        cin >> minVal;
        cout << "Enter the maximum value: ";
        cin >> maxVal;
        RandomFill(count, minVal, maxVal);
    }

    int LastIndexOf(int value) const {
        for (int i = size - 1; i >= 0; i--) {
            if (data[i] == value) {
                return i;
            }
        }
        return -1; 
    }
};

int main()
{
    ArrayList ar;
    ar.Print();

    ar.PushBack(1);
    ar.Print();

    ar.PushBack(2);
    ar.Print();

    ar.PushBack(3);
    ar.Print();

    ar.PushFront(4);
    ar.Print();

    ar.Clear();
    ar.Print();

    ar.RandomlyUserInput();
    cout << "\nRandomly filled array: " << "\n";
    ar.Print();
    cout << "\nSize: " << ar.GetSize() << ", Capacity: " << ar.GetCapacity() << "\n";

    ar.Reverse();
    cout << "\nReverse: " << "\n";
    ar.Print();

    ar.SortDesc();
    cout << "\nSort: " << "\n";
    ar.Print();

    ar.Remove(14);
    cout << "\nRemove value: " << 14 << "\n";
    ar.Print();

    int lastIndex = ar.LastIndexOf(16);
    cout << "\nLast index of 16 is: " << lastIndex << "\n";

}
