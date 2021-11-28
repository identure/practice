/*
 * LinkedList.h
 */

#ifndef LINKEDLIST_H_
#define LINKEDLIST_H_

#include <iostream>
using std::cout;
using std::endl;


template <class T>
struct LNode {
	T data_;
	LNode<T>* next_;
	LNode<T>* prev_;
};

/*
 * Create a container using a doubly linked list
 */
template <class T>
class LinkedList {
public:
	// Constructor, Initialize the linkedlist to empty
	LinkedList() {
		head_ = nullptr;
	}

	// Destructor - make sure to clean after yourself
	~LinkedList() {
		// just repeatedly call delete
		while (head_ != nullptr) remove(head_);
	}

	// print all entries in the list, in order
	void print() const {
		LNode<T>* tmp = head_;
		while (tmp != nullptr) {
			cout << tmp->data_ << " ";
			tmp = tmp->next_;
		}
		cout << endl;
	}

	LinkedList& operator<<(const LinkedList& other){
		LNode<T>* tmp = head_;
		while (tmp != nullptr) {
			cout << tmp->data_ << " ";
			tmp = tmp->next_;
		}
		cout << endl;
	}

	// find t from the list, returning a pointer to that node.
	// if not found, return nullptr
	LNode<T>* find(T t) const {
		LNode<T>* tmp = head_;
		while (tmp != nullptr) {
			if (tmp->data_ == t) return tmp;
			tmp = tmp->next_;
		}
		return tmp;
	}
	LinkedList& operator==(const LinkedList& other) {
		LNode<T>* tmp = head_;
		while (tmp != nullptr) {
			if (tmp->data_ == t) return tmp;
			tmp = tmp->next_;
		}
		return tmp;
	}

	// insert t to the list as the new head
	void insert_head(T t) {
		LNode<T>* tmp = new LNode<T>;
		tmp->data_ = t;
		tmp->next_ = head_;
		tmp->prev_ = nullptr;
		if (head_ != nullptr) head_->prev_ = tmp;
		head_ = tmp;
	}

	// insert t as a new node after "location"
	// location is assumed to point to a valid position in the list
	void insert_after(LNode<T>* location, T t) {
		LNode<T>* tmp = new LNode<T>;
		tmp->data_ = t;
		tmp->next_ = location->next_;
		tmp->prev_ = location;
		if (location->next_ != nullptr) location->next_->prev_ = tmp;
		location->next_ = tmp;
	}

	// remove the entry pointed to by "location"
	// location is assumed to point to a valid position in the list
	void remove(LNode<T>* location) {
		if (location == nullptr) return;
		if (location == head_) head_ = head_->next_;
		if (location->next_ != nullptr)
			location->next_->prev_ = location->prev_;
		if (location->prev_ != nullptr)
			location->prev_->next_ = location->next_;
		delete location;
	}

private:
	LNode<T>* head_;
};

#endif /* LINKEDLIST_H_ */
