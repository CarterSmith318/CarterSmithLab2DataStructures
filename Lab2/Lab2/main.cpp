#include <iostream>

// Enumeration type for item comparison
enum RelationType { LESS, GREATER, EQUAL };

// Node structure for the linked list
template <class ItemType>
struct NodeType {
    ItemType info;
    NodeType* next;
};

// UnsortedType class representing an unsorted linked list
template <class ItemType>
class UnsortedType {
private:
    static const int MaxItems = 100; // Replace with your desired value
    NodeType<ItemType>* front;       // Pointer to the first item in the list
    NodeType<ItemType>* position;    // Pointer to the current position in the list

public:
    // Constructor
    UnsortedType();

    // Destructor
    ~UnsortedType();

    // Method to initialize the list to an empty state
    void MakeEmpty();

    // Method to check if the list is full
    bool IsFull() const;

    // Method to get the length of the list
    int GetLength() const;

    // Method to insert an item into the list
    void InsertItem(ItemType item);

    // Method to delete an item from the list
    void DeleteItem(ItemType item);

    // Method to reset the current position to the front of the list
    void ResetList();

    // Method to get the next item in the list
    ItemType GetNextItem();

    // Method to search for a given item in the list
    NodeType<ItemType>* Search(ItemType item);

    // Method to compare two ItemType objects based on their keys
    RelationType ComparedTo(ItemType item1, ItemType item2);

    // Method to perform the union of two lists and create a new list with unique elements
    void Union(UnsortedType<ItemType>& list1, UnsortedType<ItemType>& list2);
};

// Implementation of UnsortedType methods

template <class ItemType>
UnsortedType<ItemType>::UnsortedType() {
    front = nullptr;
    position = nullptr;
}

template <class ItemType>
UnsortedType<ItemType>::~UnsortedType() {
    MakeEmpty();
}

template <class ItemType>
void UnsortedType<ItemType>::MakeEmpty() {
    NodeType<ItemType>* tempPtr;

    while (front != nullptr) {
        tempPtr = front;
        front = front->next;
        delete tempPtr;
    }
    position = nullptr;
}

template <class ItemType>
bool UnsortedType<ItemType>::IsFull() const {
    NodeType<ItemType>* location;
    try {
        location = new NodeType<ItemType>;
        delete location;
        return false;
    }
    catch (std::bad_alloc exception) {
        return true;
    }
}

template <class ItemType>
int UnsortedType<ItemType>::GetLength() const {
    int count = 0;
    NodeType<ItemType>* tempPtr = front;

    while (tempPtr != nullptr) {
        count++;
        tempPtr = tempPtr->next;
    }

    return count;
}

template <class ItemType>
void UnsortedType<ItemType>::InsertItem(ItemType item) {
    if (IsFull()) {
        std::cerr << "List is full. Cannot insert more items." << std::endl;
        return;
    }

    if (GetLength() >= MaxItems) {
        std::cerr << "List is at maximum capacity. Cannot insert more items." << std::endl;
        return;
    }

    NodeType<ItemType>* newNode = new NodeType<ItemType>;
    newNode->info = item;
    newNode->next = front;
    front = newNode;
}

template <class ItemType>
void UnsortedType<ItemType>::DeleteItem(ItemType item) {
    NodeType<ItemType>* tempPtr = front;
    NodeType<ItemType>* predPtr = nullptr;

    while (tempPtr != nullptr && tempPtr->info != item) {
        predPtr = tempPtr;
        tempPtr = tempPtr->next;
    }

    if (tempPtr != nullptr) {
        if (predPtr == nullptr) {
            front = tempPtr->next;
        }
        else {
            predPtr->next = tempPtr->next;
        }
        delete tempPtr;
    }
}

template <class ItemType>
void UnsortedType<ItemType>::ResetList() {
    position = nullptr;
}

template <class ItemType>
ItemType UnsortedType<ItemType>::GetNextItem() {
    if (position == nullptr) {
        position = front;
    }
    else {
        position = position->next;
    }

    return (position != nullptr) ? position->info : ItemType{};
}

template <class ItemType>
NodeType<ItemType>* UnsortedType<ItemType>::Search(ItemType item) {
    NodeType<ItemType>* tempPtr = front;

    while (tempPtr != nullptr && tempPtr->info != item) {
        tempPtr = tempPtr->next;
    }

    return tempPtr;
}

template <class ItemType>
RelationType UnsortedType<ItemType>::ComparedTo(ItemType item1, ItemType item2) {
    if (item1 < item2) {
        return LESS;
    }
    else if (item1 > item2) {
        return GREATER;
    }
    else {
        return EQUAL;
    }
}

template <class ItemType>
void UnsortedType<ItemType>::Union(UnsortedType<ItemType>& list1, UnsortedType<ItemType>& list2) {
    list1.ResetList();
    ItemType item;

    while ((item = list1.GetNextItem()) != ItemType{}) {
        if (Search(item) == nullptr) {
            InsertItem(item);
        }
    }

    list2.ResetList();

    while ((item = list2.GetNextItem()) != ItemType{}) {
        if (Search(item) == nullptr) {
            InsertItem(item);
        }
    }
}

// Example client code
int main() {
    // Test case 1: Basic Union Operation
    UnsortedType<int> list1;
    list1.InsertItem(1);
    list1.InsertItem(2);
    list1.InsertItem(3);

    UnsortedType<int> list2;
    list2.InsertItem(3);
    list2.InsertItem(4);
    list2.InsertItem(5);

    UnsortedType<int> resultList;
    resultList.Union(list1, list2);

    std::cout << "Resulting List after Union Operation: ";

    int item;
    resultList.ResetList();
    while ((item = resultList.GetNextItem()) != 0) {
        std::cout << item << " ";
    }
    std::cout << std::endl;

    // Test case 2: Union Operation with Empty Lists
    UnsortedType<int> emptyList1;
    UnsortedType<int> emptyList2;
    UnsortedType<int> resultEmptyList;
    resultEmptyList.Union(emptyList1, emptyList2);
    std::cout << "Resulting List after Union Operation on Empty Lists: ";
    resultEmptyList.ResetList();
    while ((item = resultEmptyList.GetNextItem()) != 0) {
        std::cout << item << " ";
    }
    std::cout << std::endl;

    // Test case 3: Union Operation with Duplicates
    UnsortedType<int> listWithDuplicates;
    listWithDuplicates.InsertItem(1);
    listWithDuplicates.InsertItem(2);
    listWithDuplicates.InsertItem(2);
    listWithDuplicates.InsertItem(3);
    listWithDuplicates.InsertItem(3);
    UnsortedType<int> resultListWithDuplicates;
    resultListWithDuplicates.Union(listWithDuplicates, listWithDuplicates);
    std::cout << "Resulting List after Union Operation with Duplicates: ";
    resultListWithDuplicates.ResetList();
    while ((item = resultListWithDuplicates.GetNextItem()) != 0) {
        std::cout << item << " ";
    }
    std::cout << std::endl;

    // Test case 4: Union Operation exceeding MaxItems
    const int MaxItems = 5;
    UnsortedType<int> myList;
    for (int i = 1; i <= MaxItems; ++i) {
        myList.InsertItem(i);
    }

    // Try to insert one more item, which should exceed the MaxItems limit
    myList.InsertItem(MaxItems + 1);

    return 0;
}
