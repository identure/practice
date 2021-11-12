#include <iostream>
#include "BucketList.h"
using std::cout;
using std::endl;

Node::Node() {
	// IMPLEMENT ME
	//  next_ = nullptr;
}

Node::~Node() {
	// IMPLEMENT ME

}

BucketList::BucketList() {
	// IMPLEMENT ME
	Node** tmp = buckets_;
	cout << buckets_;
	for (size_t i = 0; i < INITIAL_CAP; i++){
		//tmp[i] = nullptr;
		cout << tmp;
	}
}

BucketList::~BucketList() {
	// IMPLEMENT ME
	Node** tmp = buckets_;
	for (size_t i = 0; i < INITIAL_CAP; i++){
		//while (tmp[i]!=nullptr){
			//Node* tmpa = tmp[i];
			//tmp[i] = tmp[i]->next_;
			//delete tmpa;
		//}
	}
}

BucketList::BucketList(const BucketList& other) {
	// IMPLEMENT ME
	BucketList* newBuckets_ = new BucketList[INITIAL_CAP];
}

BucketList& BucketList::operator=(const BucketList& other) {
	// IMPLEMENT ME
	for (size_t i = 0; i < INITIAL_CAP; i++){
		
	}
	return *this;
}

bool BucketList::contains(const string& s) const {

	// THIS IS DONE FOR YOU AS AN EXAMPLE
	// but you need to change something...

	int hc = h(s) % INITIAL_CAP; // ...here.
	Node* temp = buckets_[hc];
	while (temp != nullptr) {
		if (temp->s_ == s) return true;
		temp = temp->next_;
	}
	return false;
}

void BucketList::insert(const string& s) {
	// IMPLEMENT ME
	// Node* tmp = ;

}

void BucketList::remove(const string& s) {
	// IMPLEMENT ME
}

string BucketList::toString() const {
	// IMPLEMENT ME
	return ""; // dummy
}

int BucketList::h(const string& s) const {
	// IMPLEMENT ME
	int sum = 0;
	for(int i=0; i<s.size(); i++){
		cout << s[i];
	}
	return -1; // dummy
}

int BucketList::getSize() const {
	// IMPLEMENT ME
	return -1; // dummy
}

int BucketList::getCap() const {
	// IMPLEMENT ME
	return -1; // dummy
}
