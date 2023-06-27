#pragma once
#ifndef FORWARD_LIST_HPP
#define FORWARD_LIST_HPP

#include <algorithm>

template <typename T>
class Forward_list
{

public:
    class Node
    {
    public:
        // A node will hold data of type T
        T data{};
        // next will point to the next node in the list
        // we initialise next to nullptr
        Node* next = nullptr;

        // Because we have already intialised the variables
        // the default constructor doesn't need to do anything
        Node() {}

        // To make life easier we also provide a constructor
        // that takes the T data to be copied into the data member variable 
        // There is an optional second argument which is
        // used to update the next pointer.  This defaults to nullptr 
        // if the constructor is called with just one argument.
        Node(T input_data, Node* next_node = nullptr)
        {
            data = input_data;
            next = next_node;
        }

        // Destructor
        ~Node() {}
    };

    private:
        // private member variables for Forward_list
        // the trailing underscore is a stylistic choice to 
        // distinguish these as private member variables
        unsigned size_ = 0;
        Node* head_ = nullptr;

    public:
        // public member functions of the Forward_list class
        // We have generally used the same names as for the
        // corresponding functions of std::forward_list

        // Default constructor does not need to do anything 
        Forward_list();

        // The destructor 
        ~Forward_list();

        // Copy constructor

        Forward_list(const Forward_list<T>& other);

        // Constructor from initializer list
        Forward_list(std::initializer_list<T> input);

        // Add an element to the front of the list
        void push_front(const T& data);

        // Remove the first element of the list
        void pop_front();

        // Return the data held in the first item of the list
        // This function should not change the list, which is 
        // why it is declared const
        T front() const;

        // Print out all the data in the list in sequence
        void display() const;

        // Outputs if the list is empty or not
        bool empty() const;

        // outputs the size of the list
        unsigned size() const;


        // methods related to sorting     

        // merge two sorted lists, *this and other
        void merge(Forward_list& other);

        // split *this into its first half, which becomes the new *this,
        // and its second half which is returned
        Forward_list split();

        // The sort function uses the helper functions 
        // merge and split
        void sort();

        void add_Node(const T& data);

        void remove_last_Node();

    private:

        // sort is implemented via a recursive merge sort
        void merge_sort(Forward_list&);
};

// Default Constructor
template <typename T>
Forward_list<T>::Forward_list()
{
}

// Destructor
template <typename T>
Forward_list<T>::~Forward_list() {

    while (head_ != nullptr) {
        Node* tmp = head_;
        head_ = head_->next;
        delete tmp;
        --size_;
    }
}

// Copy constructor

// The copy constructor takes as argument a const reference to a 
// another Forward_list "other" 
// The const means that the function should not modify other
// The function should make a "deep copy" of the other list,
// that is create a new node for every node in other and copy 
// the data of other into these new nodes.  
template <typename T>
Forward_list<T>::Forward_list(const Forward_list& other) {

    if (other.head_ == nullptr) { // if there is no head node in other, then head_ will be null
        head_ = nullptr;
    }
    else {
        head_ = new Node(other.head_->data); // In head_, store the first node of the "other" list
        size_ = 1; // size i sbeing incremented by 1 becuase head_ private variable has a node in it
        Node* thislistNode = head_; // first node of new list being created is initliased here
        Node* nextnodePointer = other.head_; // nodePointer will point to the next node after "other"'s head

        //thislistNode and nextnodePointer are used so that head_ and other.head_ dont
        //change in values. This is easier to cycle through the values in a while loop

        //this loop cycles until the last node of the "other" list
        while (nextnodePointer->next != nullptr) {
            thislistNode->next = new Node(nextnodePointer->next->data); //nodes are being copied from other list to "this" list
            if (thislistNode->next != nullptr) { //thislistNode is incremented so node can be copied in next iteration
                thislistNode = thislistNode->next;
            }

            if (nextnodePointer->next != nullptr) { //Same as thislistNode, nextnodePointer is incremented
                nextnodePointer = nextnodePointer->next;
            }// add an if clause for it 
            size_ = size_ + 1; //since a node is added to the thislistNode chain, size_variable increases by 1
        }
    }
}

// Constructor from initializer list

// This implements the functionality you see with, for example, 
// std::forward_list<int> my_list = {1,2,3}
// which creates a new linked list where the first node holds 1, second 2, and 
// third 3.
// The {1,2,3} here is of type std::initializer_list<int> and you 
// see this is the argument to this constructor (with data of type T
// rather than just int). 

// You can access the elements of a std::initializer_list via an iterator
// for example you can cycle through all the elements with
// for(auto it = input.begin(); it!= input.end(); ++it){Do something with *it} 
template <typename T>
Forward_list<T>::Forward_list(std::initializer_list<T> input)
{
    // make a function that adds creates a node and adds it to the forward list
    // loop through the list using head_->next != nullptr and add elements lol
    bool checker = true; //this boolean is used to add the data from input into the head node
    size_ = 0; //size_ iprivate variable is initialised here 

    //this iterator is used to loop through the input list data
    for (auto it = input.begin(); it != input.end(); ++it) {

        if (checker) { //this if case adds the head node from the 1st data value from input list 
            head_ = new Node(*it);
            size_ = size_ + 1;
            checker = false;
        }
        else {
            add_Node(*it); //this function adds a node to "this" list using the data from the input list
        }
    }
}


// Add element to front of list
template <typename T>
void Forward_list<T>::push_front(const T& data) {

    Node* element = new Node(data); // a new node with the input data is created
    element->next = head_; // This points the new node to the head node to make it the starting node
    head_ = element; //the head_ node becomes the new node added
    ++size_; //the size is incremented by 1 becasue a new node is added
}

// Remove the front element of the list 
// If the list is empty don't do anything
template <typename T>
void Forward_list<T>::pop_front() {

    if (head_ != nullptr) {
        Node* temp = head_; // temp is going hold the node that will be deleted
        head_ = head_->next; // changing the head node to the node next to the original head_ node
        delete temp; //deleting the temp node which holds the original head_ node
        --size_; // size is decremented by 1 because a node is deleted
    }
}

// Return the data in the front element of the list
// If the list is empty the behaviour is undefined:
// you can return an arbitrary value, but don't segfault 
// ***For you to implement
template <typename T>
T Forward_list<T>::front() const {

    if (head_ != nullptr) {
        return head_->data; // if the head_ node is not empty, the data from head_ is returned
    }
    else {
        return 0; // this is for the case when the heads_ node is empty
    }

}

// Print out the list
template <typename T>
void Forward_list<T>::display() const
{
    Node* temp_node = head_;
    while (temp_node != nullptr) {
        std::cout << temp_node->data << " ,";
        temp_node = temp_node->next;
    }
}


// Outputs if the list is empty or not
template <typename T>
bool Forward_list<T>::empty() const
{
    return (head_ == nullptr);
}

// Returns the size of the list
// It is implemented for you but you need to correctly 
// update the size_ variable in your code as needed

// Note that std::forward_list actually does not have a size function
template <typename T>
unsigned Forward_list<T>::size() const
{
    return size_;
}

// the split function splits *this into its first half, which becomes 
// the new *this, and its second half which is returned
// if the the size of *this is n, then after split the size of *this 
// should be ceiling(n/2), and the size of the returned list should be
// floor(n/2)

// As an example, if *this is of the form
// head_ -> a -> b -> c -> d -> nullptr
// then after split *this should be
// head_ -> a -> b -> nullptr
// and you should a return a Forward_list other where
// other.head_ = c -> d -> nullptr

// Don't forget to update the size_ variable of *this and other
// You do not need to create any new nodes for this function,
// just change pointers.
template <typename T>

// So split splits the functions into two halves where my_list retains the first half 
// and "second" retains the second half of the list 
// top two lines are the implementation in merge sort
//So split function will return the second half of the *this list



Forward_list<T> Forward_list<T>::split()
{
    //split *this into two halves
    //no need to create any new nodes for this function
    //might have to create a new list though 

    //Normally in java a full instance of a class object can be created
    //In C++ we can create a pointer to the class Forward_list using *


    Forward_list<T>* second_half = new Forward_list<T>; // This list is for holding the second half of the list

    Node* first_temp = head_; // first_temp is used to hold the node at the middle element using the for loop
    Node* second_temp;
    int middle_element = (size_ + 1) / 2; //this is to get the position of the middle position
    int second_half_size = size_ - middle_element; // size of the second_half list is determined here
    int i = 1;

    for (i = 1; i < middle_element; i++) { // at the end of for loop, first_temp will point to the middle element

        first_temp = first_temp->next;
    }

    if (i == middle_element) { //when middle point is reached you have to change *this list too 

        second_temp = first_temp->next; // this is to hold the nodes after the middle element in the second_half list

        first_temp->next = nullptr; //this creates the first half of the list in "this" list
        size_ = middle_element; // the size_ of "this" is determined as the list is halved

        second_half->head_ = second_temp; // the head node of the second_half list is assigned
        second_half->size_ = second_half_size;   // the size of the second_half list is assigned
    }

    return *second_half;
}

// Merging two sorted lists
// For this function it is assumed that both *this and the 
// input Forward_list other are already sorted
// The function merges the two lists into sorted order, and the merger becomes 
// the new *this

// You do not need to create any new nodes in this function,
// just update pointers.  
// Set other to be an empty list at the end of the function
template <typename T>
void Forward_list<T>::merge(Forward_list& other) {

    if (other.head_ == nullptr) { // this is for the case when the "other" list is empty
        return; // the function is called back because the "this" list is already sorted
    }

    if (head_ == nullptr) { // this is for the case when the "this" list is empty
        head_ = other.head_; //assign the private variable head_ to the head of the second orted list "other"
        size_ = other.size_; //assign the size_ private variable as the size of the list "other" 
        other.head_ = nullptr; //setting the "other" list to be empty
        return; // function is called back because list is sorted
    }

    Node* this_temp = head_; // this pointer is to loop through the "this" list
    Node* other_temp = other.head_; // this pointer is to loop through the "other" list
    Node* tail_temp; // this pointer is to hold the node that is to be added to the merged list

    //this if else clause determines the head of the merged list

    if (head_->data <= other.head_->data) { //if head_ is the smallest node, head_ is assigned as the head node
        head_ = this_temp;
        this_temp = this_temp->next; // this pointer is incremented to cycle through the nodes in the "this" list
    }
    else { //if other.head_ is the smallest node, other.head_ is assigned as the head node
        head_ = other_temp;
        other_temp = other_temp->next; // this pointer is incremented to cycle through the nodes in the "other" list
    }

    head_->next = nullptr; // This establishes the head node of the merged list. The head_ private variable of "this" is also assigned

    // the rest of the nodes from the original "this" list can be accessed by incrementing this_temp as it points to the second node in the original "this" list (line 385)

    Node* tail = head_; // this pointer is used to loop through the new "this" list with head_ as head node and add new nodes 
    size_ = size_ + other.size_; // the size_ private variable of the new "this" list is assigned

    while (this_temp != nullptr && other_temp != nullptr) { // this loop runs until one of the sorted list is sorted into the new "this" list

        if (this_temp->data <= other_temp->data) { // in this case, node from the original "this" list is added to the new merged "this" list
            tail_temp = this_temp; // this holds the node to be added to the merged list as this_temp will be incremented 
            tail->next = tail_temp; //As line 397 holds the head_ node of the new merged list in "tail", tail_temp is added as the next node 
            tail = tail_temp; //tail pointer is incremented to accomodate for the next iteration of the loop
            this_temp = this_temp->next; //this-temp is incremented to compare it in the next iteration of the loop
        }
        else { // in this case, node from the other list is added to the new merged "this" list
            tail_temp = other_temp; // 406 - 409 work similarly to the if clause but elements from "other" list are addded to the new merged list 
            tail->next = tail_temp;
            tail = tail_temp;
            other_temp = other_temp->next;
        }
    }

    if (other_temp != nullptr) { //in case the loop ends with more elements in the "other" list, they are added to the merged list
        tail->next = other_temp;
    }

    if (this_temp != nullptr) { //in case the loop ends with more elements in the original "this" list, they are addded to the merged list
        tail->next = this_temp;
    }

    other.head_ = nullptr; // the "other" list is set to be empty by assigned the head node to be a null pointer
}

// recursive implementation of merge_sort
template <typename T>
void Forward_list<T>::merge_sort(Forward_list& my_list) {
    if (my_list.size() == 0 || my_list.size() == 1)
    {
        return;
    }

    // So split splits the functions into two halves where my_list retains the first half 
    // and "second" retains the second half of the list 
    Forward_list<T> second = my_list.split();
    merge_sort(my_list); //This is the first half being merge sorted
    merge_sort(second); //This is the second half being merge sorted
    my_list.merge(second);
}

// sorts the list by calling merge_sort
// once your merge and split functions are working
// sort should automatically work
template <typename T>
void Forward_list<T>::sort() {
    merge_sort(*this);
}

template <typename T>
void Forward_list<T>::remove_last_Node() { // this function is used for the initialiser list constructor

    Node* temp = head_; // this pointer is used to iterate through the "this" list
    while (temp->next != nullptr) { // This is gonna go to the end of the loop and store the last node 
        temp = temp->next;
    }

    delete temp; // the last node of the "this" list os deleted

}

template <typename T>
void Forward_list<T>::add_Node(const T& data) { // this function is used for the initialiser list constructor

    Node* temp = head_; // this pointer is used to iterate through the "this" list
    Node* current_Node; // this is to hold the data in a new node called current_Node

    while (temp->next != nullptr) { // This is gonna go to the end of the loop and store the last node 
        temp = temp->next;
    }

    current_Node = new Node(data);
    temp->next = current_Node; //This is going to add the node to the end of the list
    size_ = size_ + 1; //As node is added to the list, the size is incremented to 1

}



#endif