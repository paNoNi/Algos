#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <new>

class LinkedList {
public:
    class LinkedListNode {
    public:
        std::string key = "";

        LinkedListNode* p_prev = nullptr;
        LinkedListNode* p_next = nullptr;

        LinkedListNode* p_prev_enter = nullptr;
        LinkedListNode* p_next_enter = nullptr;
    };

    bool add(const std::string &key, LinkedListNode* &last_enter_ptr);

    bool remove(const std::string &key, LinkedListNode* &last_enter_ptr);

    long size();

    ~LinkedList();

private:
    LinkedListNode* p_begin = nullptr;
    LinkedListNode* p_end = nullptr;
    long list_size = 0;

    LinkedListNode* findKey(const std::string &key);
};

class LinkedHashTable {
public:
    LinkedHashTable() = default;

    explicit LinkedHashTable(long size);

    ~LinkedHashTable();

    bool setSize(long size);

    void add(const std::string &key);

    bool remove(const std::string &key);

    const LinkedList::LinkedListNode* getLastEnterPtr();

    const long getElementsCount();

private:
    LinkedList* table = nullptr;
    long table_size = 0;
    const double A = (sqrt(5) - 1) / 2;

    LinkedList::LinkedListNode* prev_enter_ptr = nullptr;
    long elements_count = 0;

    long hash(const std::string &key) {
        int keyVal = 0;
        for (int i = 0; i < key.length(); ++i) {
            keyVal += key[i] * (i + 1);
        }
        keyVal *= key.length() + 1;

        double int_part;
        return (long)(table_size * modf(keyVal * A, &int_part));
    }
};

class List {
public:
    explicit List(long _element_map_size);

    ~List();

    void add(const std::string &key, const std::string &value);

    void removeAll(const std::string &key);

    void removePair(const std::string &key, const std::string &value);

    const LinkedList::LinkedListNode* getLastEnterPtr(const std::string &key);

    const long getElementsCount(const std::string &key);

    long size();

private:
    class Node {
    public:
        std::string key = "";
        LinkedHashTable linked_map;
        Node* p_prev = nullptr;
        Node* p_next = nullptr;

        explicit Node(long map_size) {
            linked_map.setSize(map_size);
        }
    };

    Node* p_begin = nullptr;
    Node* p_end = nullptr;
    long list_size = 0;
    long element_map_size = 0;

    Node* findKey(const std::string &_key);
};

class HashMultiMap {
public:
    explicit HashMultiMap(long _level_first_size, long _level_second_size);

    ~HashMultiMap();

    void addPair(const std::string &key, const std::string &value);

    void removeAll(const std::string &key);

    void removePair(const std::string &key, const std::string &value);


    const LinkedList::LinkedListNode* getLastEnterPtr(const std::string &key);

    const long getElementsCount(const std::string &key);

private:
    List* table = nullptr;
    long level_first_size = 0;
    long level_second_size = 0;

    const double A = (sqrt(5) - 1) / 2;

    long hash(const std::string &_key);
};

// LinkedList class methods
LinkedList::~LinkedList() {
    LinkedListNode* p_look = p_begin;
    while (p_look != nullptr) {
        LinkedListNode* temp = p_look;
        p_look = p_look->p_next;
        delete(temp);
    }

    p_begin = nullptr;
    p_end = nullptr;
}

LinkedList::LinkedListNode *LinkedList::findKey(const std::string &key) {
    if (!list_size)
        return nullptr;

    LinkedListNode *p_look = p_begin;
    while (p_look != nullptr && p_look->key != key)
        p_look = p_look->p_next;
    return p_look;
}

bool LinkedList::add(const std::string &key, LinkedList::LinkedListNode *&last_enter_ptr) {
    LinkedListNode* ptr_temp = findKey(key);
    if (ptr_temp != nullptr)
        return false;

    list_size++;
    auto* temp = new LinkedListNode;
    temp->key = key;

    temp->p_prev_enter = last_enter_ptr;
    if (last_enter_ptr != nullptr)
        last_enter_ptr->p_next_enter = temp;

    if (p_end == nullptr) {
        p_begin = temp;
        p_end = temp;
        last_enter_ptr=  p_end;
        return true;
    }

    temp->p_prev = p_end;
    p_end->p_next = temp;
    p_end = temp;
    last_enter_ptr = p_end;
    return true;

}

bool LinkedList::remove(const std::string &key, LinkedList::LinkedListNode *&last_enter_ptr) {
    LinkedListNode* ptr_temp = findKey(key);
    if (ptr_temp == nullptr)
        return false;

    if (ptr_temp == last_enter_ptr)
        last_enter_ptr = ptr_temp->p_prev_enter;

    if (ptr_temp == p_begin)
        p_begin = ptr_temp->p_next;
    if (ptr_temp == p_end)
        p_end = ptr_temp->p_prev;

    if (ptr_temp->p_prev != nullptr)
        ptr_temp->p_prev->p_next = ptr_temp->p_next;
    if (ptr_temp->p_next != nullptr)
        ptr_temp->p_next->p_prev = ptr_temp->p_prev;

    if (ptr_temp->p_prev_enter != nullptr)
        ptr_temp->p_prev_enter->p_next_enter = ptr_temp->p_next_enter;
    if (ptr_temp->p_next_enter != nullptr)
        ptr_temp->p_next_enter->p_prev_enter = ptr_temp->p_prev_enter;

    delete(ptr_temp);
    --list_size;

    return true;
}

long LinkedList::size() {
    return list_size;
}

// LinkedHashTableClassMethods
LinkedHashTable::LinkedHashTable(long size) {
    table = new LinkedList[size];
    table_size = size;
}

LinkedHashTable::~LinkedHashTable() {
    delete[](table);
    table = nullptr;
}

bool LinkedHashTable::setSize(long size) {
    // You can call this function only one time, no support for resize()
    if (!table_size) {
        table_size = size;
        table = new LinkedList[size];
        return true;
    }
    return false;
}

void LinkedHashTable::add(const std::string &key) {
    if (table[hash(key)].add(key, prev_enter_ptr))
        ++elements_count;
}

bool LinkedHashTable::remove(const std::string &key) {
    if (table[hash(key)].remove(key, prev_enter_ptr))
        --elements_count;
    return elements_count == 0;
}

const LinkedList::LinkedListNode *LinkedHashTable::getLastEnterPtr() {
    return prev_enter_ptr;
}

const long LinkedHashTable::getElementsCount() {
    return elements_count;
}

// List class methods
List::List(long _element_map_size) {
    element_map_size = _element_map_size;
}

List::~List() {
    Node* p_look = p_begin;
    while (p_look != nullptr) {
        Node* temp = p_look;
        p_look = p_look->p_next;
        delete(temp);
    }

    p_begin = nullptr;
    p_end = nullptr;
}

void List::add(const std::string &key, const std::string &value) {
    Node* ptr_temp = findKey(key);
    if (ptr_temp == nullptr) {
        list_size++;
        auto* temp = new Node(element_map_size);
        temp->key = key;
        temp->linked_map.add(value);

        if (p_end == nullptr) {
            p_begin = temp;
            p_end = temp;
            return;
        }

        temp->p_prev = p_end;
        p_end->p_next = temp;
        p_end = temp;
        return;
    }

    ptr_temp->linked_map.add(value);
}

void List::removeAll(const std::string &key) {
    Node* ptr_temp = findKey(key);
    if (ptr_temp == nullptr)
        return;

    if (ptr_temp == p_begin)
        p_begin = ptr_temp->p_next;
    if (ptr_temp == p_end)
        p_end = ptr_temp->p_prev;

    if (ptr_temp->p_prev != nullptr)
        ptr_temp->p_prev->p_next = ptr_temp->p_next;
    if (ptr_temp->p_next != nullptr)
        ptr_temp->p_next->p_prev = ptr_temp->p_prev;

    delete(ptr_temp);
    --list_size;
}

void List::removePair(const std::string &key, const std::string &value) {
    Node* ptr_temp = findKey(key);
    if (ptr_temp == nullptr)
        return;
    if (ptr_temp->linked_map.remove(value))
        removeAll(key);
}

const LinkedList::LinkedListNode *List::getLastEnterPtr(const std::string &key) {
    Node* ptr_temp = findKey(key);
    if (ptr_temp == nullptr)
        return nullptr;
    return ptr_temp->linked_map.getLastEnterPtr();
}

const long List::getElementsCount(const std::string &key) {
    Node* ptr_temp = findKey(key);
    if (ptr_temp == nullptr)
        return 0;
    return ptr_temp->linked_map.getElementsCount();
}

long List::size() {
    return list_size;
}

List::Node *List::findKey(const std::string &_key) {
    if (!list_size)
        return nullptr;

    Node *p_look = p_begin;
    while (p_look != nullptr && p_look->key != _key)
        p_look = p_look->p_next;
    return p_look;
}

// HashMultiMap class methods
HashMultiMap::HashMultiMap(long _level_first_size, long _level_second_size) {
    level_first_size = _level_first_size;
    level_second_size = _level_second_size;

    table = static_cast<List*>(operator new[] (level_first_size * sizeof(List)));
    for (long i = 0; i < level_first_size; i++) {
        new (table + i) List(level_second_size);
    }
}

HashMultiMap::~HashMultiMap() {
    for (long i = 0; i < level_first_size; i++)
        table[i].~List();

    operator delete[] (table);
    table = nullptr;
}

void HashMultiMap::addPair(const std::string &key, const std::string &value) {
    long hash_value = hash(key);
    table[hash_value].add(key, value);
}

void HashMultiMap::removeAll(const std::string &key) {
    table[hash(key)].removeAll(key);
}

const LinkedList::LinkedListNode *HashMultiMap::getLastEnterPtr(const std::string &key) {
    return table[hash(key)].getLastEnterPtr(key);
}

void HashMultiMap::removePair(const std::string &key, const std::string &value) {
    table[hash(key)].removePair(key, value);
}

const long HashMultiMap::getElementsCount(const std::string &key) {
    return table[hash(key)].getElementsCount(key);
}

long HashMultiMap::hash(const std::string &_key) {
    int keyVal = 0;
    for (int i = 0; i < _key.length(); ++i) {
        keyVal += _key[i] * (i + 1);
    }
    keyVal *= _key.length() + 1;

    double int_part;
    return (long)(level_first_size * modf(keyVal * A, &int_part));
}

#define IN_FILE_NAME "multimap.in"
#define OUT_FILE_NAME "multimap.out"

using std::ifstream;
using std::ofstream;
using std::string;

int main() {
    ifstream fin(IN_FILE_NAME);
    if (!fin.is_open())
        return 2;
    ofstream fout(OUT_FILE_NAME);
    if (!fout.is_open())
        return 2;

    HashMultiMap multi_map(1000, 200);
    while (true) {
        string command;
        fin >> command;
        if (command.empty())
            break;

        string key;
        fin >> key;
        if (command == "put") {
            string value;
            fin >> value;
            multi_map.addPair(key, value);
        }
        else if (command == "delete") {
            string value;
            fin >> value;
            multi_map.removePair(key, value);
        }
        else if (command == "deleteall") {
            multi_map.removeAll(key);
        }
        else if (command == "get") {
            fout << multi_map.getElementsCount(key) << ' ';

            auto* element_ptr = (LinkedList::LinkedListNode*)multi_map.getLastEnterPtr(key);
            while (element_ptr != nullptr) {
                fout << element_ptr->key << ' ';
                element_ptr = element_ptr->p_prev_enter;
            }
            fout << '\n';
        }
    }

    return 0;
}