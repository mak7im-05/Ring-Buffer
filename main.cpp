#include <iostream>
#include "iterator"
#include <algorithm>

using namespace std;

template<typename T>
class RingBuffer {
private:
    int capacity;
    T *Buffer;
    int size = 0;
    int endIndex = 0;
public:
    class Iterator  {
    private:
    public:
        T *iterPointer;

        Iterator() : iterPointer{nullptr} {}

        Iterator(T *p) : iterPointer{p} {}

        Iterator(const Iterator &iterator) : iterPointer{iterator.iterPointer} {}

        Iterator operator+(int n) {
            return Iterator(iterPointer + n);
        }

        Iterator operator-(int n) {
            return Iterator(iterPointer - n);
        }

        Iterator &operator+=(T n) {
            iterPointer += n;
            return *this;
        }

        Iterator &operator-=(T n) {
            iterPointer -= n;
            return *this;
        }

        Iterator &operator++() {
            iterPointer++;
            return *this;
        }

        Iterator &operator--() {
            iterPointer--;
            return *this;
        }

        Iterator operator++(T) {
            Iterator iterator{*this};
            ++iterPointer;
            return iterator;
        }

        Iterator operator--(T) {
            Iterator iterator{*this};
            --iterPointer;
            return iterator;
        }

        auto operator-(const Iterator &iterator) {
            return (iterPointer - iterator.iterPointer);
        }

        T &operator*() const {
            return *iterPointer;
        }

        T *operator->() const {
            return iterPointer;
        }

        T &operator[](const int n) {
            return iterPointer[n];
        }

        bool operator==(const Iterator &iterator) const {
            return iterator.iterPointer == this->iterPointer;
        }

        bool operator!=(const Iterator &iterator) const {
            return iterator.iterPointer != this->iterPointer;
        }

        bool operator<(const Iterator &iterator) const {
            return iterator.iterPointer < this->iterPointer;
        }

        bool operator>(const Iterator &iterator) const {
            return iterator.iterPointer > this->iterPointer;
        }

        bool operator>=(const Iterator &iterator) const {
            return iterator.iterPointer >= this->iterPointer;
        }

        bool operator<=(const Iterator &iterator) const {
            return iterator.iterPointer <= this->iterPointer;
        }

        T *getLink() {
            return iterPointer;
        }
    };

    RingBuffer(int capacity) {
        this->capacity = capacity;
        Buffer = new T[capacity];
        for (int i = 0; i < capacity; ++i) {
            Buffer[i] = 0;
        }
    }

    ~RingBuffer() {
        delete[] Buffer;
    }

    void push_front(T data) {
        for (int i = capacity-1; i > 0; --i) {
            swap(Buffer[i], Buffer[i-1]);
        }
        Buffer[0] = data;
        if (size != capacity) {
            size++;
        }
    }

    void push_back(T data) {
        Buffer[endIndex] = data;
        endIndex = (endIndex + 1) % capacity;
        if (size != capacity) {
            size++;
        }
    }

    void pop_front() {
        if (size == 0) {
            cout << "is_empty";
            return;
        }
        for (int i = 0; i < capacity - 1; ++i) {
            swap(Buffer[i], Buffer[i + 1]);
        }
        size--;
    }

    void pop_back() {
        if (size == 0) {
            cout << "Buf is empty" << endl;
            return;
        }
        size--;
    }

    const T &front() {
        return Buffer[0];
    }

    const T &back() {
        return Buffer[size-1];
    }

    bool is_empty() {
        return size == 0;
    }

    void set_capacity(int newCapacity) {
        T *newBuf = new T[newCapacity];
        endIndex = 0;
        for (int i = 0; i < newCapacity; ++i) {
            if (i < capacity) {
                newBuf[i] = Buffer[i];
                endIndex++;
            } else
                newBuf[i] = 0;
        }
        delete[] Buffer;
        Buffer = newBuf;
        capacity = newCapacity;
    }

    int getSize() {
        return size;
    }

    Iterator begin() {
        return Iterator(Buffer);
    }

    Iterator end() {
        return Iterator(Buffer + size);
    }

    T &operator[](int index) {
        return Buffer[index % capacity];
    }
};

int main() {
    int n;
    cout << "Enter size buffer" << endl;
    cin >> n;
    RingBuffer<int> buf(n);

    while (true) {
        cout << "0 - write data" << endl;
        cout << "1 - push_front" << endl;
        cout << "2 - push_back" << endl;
        cout << "3 - pop_back" << endl;
        cout << "4 - pop_front" << endl;
        cout << "5 - front" << endl;
        cout << "6 - back" << endl;
        cout << "7 - print" << endl;
        cout << "8 - is_empty" << endl;
        cout << "9 - new_capacity" << endl;
        cout << "10 - Finish" << endl << endl;
        int x;
        int y;
        cin >> x;
        switch (x) {
            case 0:
                cout << "enter count data";
                cin >> y;
                for (int i = 0; i < y; ++i) {
                    int a;
                    cin >> a;
                    buf.push_back(a);
                }
                break;
            case 1:
                cout << "enter data for push_front";
                cin >> y;
                buf.push_front(y);
                cout << endl;
                break;
            case 2:
                cout << "enter data for push_back";
                cin >> y;
                buf.push_back(y);
                cout << endl;
                break;
            case 3:
                cout << "POP BACKA";
                buf.pop_back();
                break;
            case 4:
                cout << "POP FRONTA";
                buf.pop_front();
                break;
            case 5:
                cout << "front - " << buf.front() << endl;
                break;
            case 6:
                cout << "back - " << buf.back() << endl;
                break;
            case 7:
                for (auto it = buf.begin(); it != buf.end(); ++it) {
                    cout << *it << ' ';
                }
                cout << endl;
                break;
            case 8:
                cout << "is empty" << buf.is_empty() << endl;
                break;
            case 9:
                int new_capacity;
                cout << "enter new_capacity:";
                cin >> new_capacity;
                buf.set_capacity(new_capacity);
                break;
            case 10: {
                return 0;
            }
            default:
                cout << "the command isnt exist";
        }
    }
}