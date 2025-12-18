#include <iostream>
#include <algorithm>
#include <string>
using namespace std;

class Item {
private:
    string name_;
    int price_;
public:
    Item(): name_(""),price_(0){} //기본 생성자
    Item(string name, int price) :name_(name), price_(price) {}
    ~Item(){}

    void PrintInfo() const {
        cout << "name: " << name_ << ", price: " << price_ << endl;
    }
    int GetPrice() const {
        return price_;
    }
};
template <typename T>
bool compareItemsByPrice(const T& a, const T& b) {
    return a.GetPrice() < b.GetPrice();
}

template <typename T>
class Inventory {
private:
    T* pItems_;
    int capacity_;
    int size_;

public:
    Inventory(int capacity = 10):size_(0) {
        if (capacity < 1)
            capacity_ = 1;
        else
            capacity_ = capacity;
        pItems_ = new T[capacity_];
    }
    Inventory(const Inventory<T>& other) {  //복사 생성자
        capacity_ = other.capacity_;
        size_ = other.size_;
        pItems_ = new T[capacity_];
        for (int i = 0; i < other.size_; i++) {
            pItems_[i] = other.pItems_[i];
        }
        cout << "*Inventory Copy!"<<endl;
    }
    ~Inventory() {
        delete[] pItems_;
        pItems_ = nullptr;
    }
    void AddItem(const T& item) {
        if (size_ >= capacity_) {
            //cout << "*Inventory is full..." << endl;
            cout << "*Inventory Size Up" << endl;
            T* temp = new T[capacity_ * 2];
            copy(pItems_, pItems_ + size_, temp);
            delete[] pItems_;
            capacity_ *= 2;
            pItems_ = temp;
        }
        pItems_[size_] = item; //아이템 넣기
        size_++;
    }
    void RemoveLastItem() {
        if (size_ == 0) {
            cout << "*Inventory is empty..." << endl;
        }
        else {
            size_--;
        }
    }
    int GetSize() const {
        return size_;
    }
    int GetCapacity() const {
        return capacity_;
    }
    void printAllItems() const {
        if (size_ == 0) {
            cout << "*Empty..." << endl;
        }
        else {
            for (int i = 0; i < size_;i++) {
                pItems_[i].PrintInfo(); //각 아이템 멤버 함수 출력
            }
        }
    }
    void Assign(const Inventory<T>& other) {
        size_ = other.size_;
        capacity_ = other.capacity_;
        delete[] pItems_;
        pItems_ = new T[size_];
        for (int i = 0; i < size_; i++) {
            pItems_[i] = other.pItems_[i];
        }
        cout << "*Inventory Overwrite!" << endl;
    }
    void Resize(int newCapacity) {
        T* temp = new T[newCapacity];
        copy(pItems_, pItems_ + size_, temp);
        delete[] pItems_;
        pItems_ = temp;
    }
    void SortItems() {
        sort(pItems_, pItems_ + size_,compareItemsByPrice<T>);
    }
};

int main() {
    Item cap = Item("cap", 500);
    Item shoes = Item("shoes", 700);
    Item banana = Item("banana", 100);
    Item apple = Item("apple", 150);

    Inventory<Item> box;
    cout << "상자크기: " << box.GetCapacity() << endl;
    box.AddItem(cap);
    box.AddItem(shoes);
    box.AddItem(banana);
    box.printAllItems();
    box.RemoveLastItem();
    box.printAllItems();
    box.AddItem(apple);
    box.printAllItems();
    box.SortItems();
    box.printAllItems();


    return 0;
}