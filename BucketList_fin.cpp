#include <iostream>
#include "BucketList.h"
using std::cout;
using std::endl;

Node::Node() {
	// IMPLEMENT ME
	//next_ = nullptr;
}

Node::~Node() {
	// IMPLEMENT ME
	//Node* tmp = next_;
	//while (tmp!=nullptr) {
		//Node* tmpa = tmp;
		//tmp = tmp->next_;
		//delete tmpa;
	//}
}

BucketList::BucketList() {
	c_ = INITIAL_CAP;
	number_ = 0;
	newbn_ = 0;
	buckets_ = new Node*[INITIAL_CAP];
	for (int i = 0; i < INITIAL_CAP; i++){
		buckets_[i] = nullptr;
	}
}

BucketList::~BucketList() {
	Node** tmp = buckets_;
	for (int i = 0; i < c_; i++){
		if (tmp[i]!=nullptr) {
			while (tmp[i]->next_ != nullptr) {
				Node* tmpa = tmp[i]->next_;
				tmp[i]->next_ = tmp[i]->next_->next_;
				delete tmpa;
			}
			tmp[i] = tmp[i]->next_;
		}
	}
	delete[] buckets_;
}

BucketList::BucketList(const BucketList& other) {
	c_ = other.c_;
	number_ = other.number_;
	newbn_ = other.newbn_;
	newbn_++;
	number_ = (int)(getSize()/(2*newbn_));
	buckets_ = new Node* [c_];
	for (int i = 0; i < c_;i++) {
		buckets_[i] = nullptr;
	}
	for (int i = 0; i < c_; i++) {
		Node* tmpa = other.buckets_[i];
		if (tmpa!=nullptr) {
			while (tmpa != nullptr) {
				if (tmpa!=other.buckets_[i]) {
					insert(tmpa->s_);
				}
				tmpa = tmpa->next_;
			}
		}
	}
}

BucketList& BucketList::operator=(const BucketList& other) {
	c_ = other.c_;
	newbn_ = other.newbn_;
	newbn_++;
	number_ = getSize() / (2 * newbn_);
	Node** tmp = buckets_;
	for (int i = 0; i < c_; i++) { 
		if (tmp[i] != nullptr) {
			while (tmp[i]->next_ != nullptr) {
				Node* tmpa = tmp[i]->next_;
				tmp[i]->next_ = tmp[i]->next_->next_;
				delete tmpa;
			}
			tmp[i] = tmp[i]->next_;
		}
	}
	delete[] buckets_;
	buckets_ = new Node * [c_]; 
	for (int i = 0; i < c_; i++) {
		buckets_[i] = nullptr;
	}
	for (int i = 0; i < c_; i++) {
		Node* tmpa = other.buckets_[i];
		if (tmpa != nullptr) {
			while (tmpa != nullptr) {
				if (tmpa != other.buckets_[i]) {
					insert(tmpa->s_);
				}
				tmpa = tmpa->next_;
			}
		}
	}
	return *this;
}


bool BucketList::contains(const string& s) const {
	int hc = h(s) % getCap();
	if (buckets_ != nullptr) {
		Node* temp = buckets_[hc];
		while (temp != nullptr) {
			if (temp->s_ == s) {
				return true;
			}
			temp = temp->next_;
		}
		return false;
	}
	return false;
}

void BucketList::insert(const string& s) {
	bool boolV = contains(s);
	if (!boolV) {
		//if (getSize() >= MAX_LOAD_FACTOR * c_) {
			//c_ = 2 * c_;
		//}
		int hc = h(s) % c_;
		//桶的尺寸变了需要清空数据重新插入
		//getSArr();
		if (buckets_[hc]!=nullptr) { //如果buckets_[hc]分配了内存
			Node* first = buckets_[hc]->next_;
			if (first != nullptr) { //如果buckets_[hc]->next_值不为空
				if (s.compare(first->s_) < 0) { //如果比第一个值小，则插入在第一个
					Node* tmpe = new Node;
					tmpe->s_ = s;
					tmpe->next_ = first;
					buckets_[hc]->next_ = tmpe;
				}else{
					if (first->next_!=nullptr) {
						bool success = false;
						while (first->next_!=nullptr) { //如果buckets_[hc]->next_->next_值不为空
							Node* second = first->next_;
							if (s.compare(first->s_) >= 0 && s.compare(second->s_) < 0) {
								Node* tmpb = new Node;
								tmpb->s_ = s;
								tmpb->next_ = second;
								first->next_ = tmpb;
								success = true;
								break;
							}
							first = first->next_;
						}
						if (first->next_ == nullptr && !success) { //如果buckets_[hc]->next_->next_值为空
							Node* tmph = new Node;
							tmph->s_ = s;
							tmph->next_ =nullptr;
							first->next_ = tmph;
						}
					}else { //如果buckets_[hc]->next_->next_值为空,代表只有一个值
						Node* tmpd = new Node;
						tmpd->s_ = s;
						tmpd->next_ = nullptr;
						first->next_ = tmpd;
					}
				}
			}else { //如果buckets_[hc]->next_值为空,就代表一个都没有
				Node* tmpa = new Node;
				tmpa->s_ = s;
				first = tmpa;
				first->next_ = nullptr;
			}
		}
		if(buckets_[hc]==nullptr){ //如果buckets_[hc]没有分配内存
			buckets_[hc] = new Node;
			Node* tmp = new Node;
			tmp->s_ = s;
			tmp->next_ = nullptr;
			buckets_[hc]->next_ = tmp;
		}
		number_++;
	}
}

void BucketList::remove(const string& s) {
	bool boolV = contains(s);
	if (boolV) {
		int hc = h(s) % c_;
		Node* temp = buckets_[hc];
		Node* tmp = temp->next_;
		if (tmp->s_ == s) { // 如果第一个值就是该值
			if (tmp->next_ != nullptr) { //如果后面还有其他指针
				Node* tmpf = tmp;
				buckets_[hc]->next_ = tmp->next_;
				delete tmpf;
			}else { //如果只有该指针
				delete tmp;
				buckets_[hc] = nullptr;
			}
		}else{ // 如果第一个值不是该值
			Node* tmpPrev = temp;
			if (tmpPrev == nullptr) return;
			Node* tmpNext = tmpPrev->next_;
			while (tmpNext != nullptr) { //当前指针不为空指针时
				if (tmpNext->s_ == s) {
					tmpPrev->next_ = tmpNext->next_;
					delete tmpNext;
					break;
				}
				tmpPrev = tmpNext;
				tmpNext = tmpNext->next_;
			}
		}
		number_--;
	}
}

string BucketList::toString() const {
	string res = "";
	for (int i = 0; i < getCap(); i++) {
		Node* tmp = buckets_[i];
		res += to_string(i);
		if (tmp!=nullptr) {
			while (tmp!=nullptr) {
				if (tmp == buckets_[i]) {
				}else {
					res += " " + tmp->s_;
				}
				tmp = tmp->next_;
			}
		}
		if (i!=getCap()-1) {
			res += "\n";
		}
	}
	return res; 
}

int BucketList::h(const string& s) const {
	int sum = 0;
	/*for (char c : s) {
		sum += (int)c;
	}*/
	int num = s.size();
	for (int i = 0; i < num; i++) {
		sum += (int)pow(2,i)*s[i];
	}
	return sum;
}

int BucketList::getSize() const {
	return number_; // dummy
}

int BucketList::getCap() const {
	return c_; // dummy
}



