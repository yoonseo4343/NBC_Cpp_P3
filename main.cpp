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
};

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
    ~Inventory() {
        delete[] pItems_;
        pItems_ = nullptr;
    }
    void AddItem(const T& item) {
        if (size_ < capacity_) {
            pItems_[size_] = item; //아이템 넣기
            size_++;
        }
        else {
            cout << "*Inventory is full..." << endl;
        }
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

    return 0;
}