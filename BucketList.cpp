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
	// IMPLEMENT ME
	c = INITIAL_CAP;
	number = 0;
	newbn = 0;
	buckets_ = new Node*[INITIAL_CAP];
	for (int i = 0; i < INITIAL_CAP; i++){
		buckets_[i] = nullptr;
	}
}

BucketList::~BucketList() {
	// IMPLEMENT ME
	Node** tmp = buckets_;
	for (int i = 0; i < INITIAL_CAP; i++){
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
	// IMPLEMENT ME
	c = other.c;
	newbn = other.newbn;
	newbn++;
	number = getSize()/(2*newbn);
	buckets_ = new Node* [c];
	for (int i = 0; i < c;i++) {
		buckets_[i] = nullptr;
	}
	for (int i = 0; i < c; i++) {
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
	// IMPLEMENT ME
	c = other.c;
	newbn = other.newbn;
	newbn++;
	number = getSize() / (2 * newbn);
	Node** tmp = buckets_;
	for (int i = 0; i < INITIAL_CAP; i++) { //清空初始值
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
	buckets_ = new Node * [c]; //重新创建，跟上面一样，把other复制过来
	for (int i = 0; i < c; i++) {
		buckets_[i] = nullptr;
	}
	for (int i = 0; i < c; i++) {
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
}

bool BucketList::contains(const string& s) const {
	// THIS IS DONE FOR YOU AS AN EXAMPLE
	// but you need to change something...
	cout << "contains start: aaa value" << getSize() << "c" << c << endl;
	int hc = h(s) % getCap(); // ...here.
	cout << hc << "hs" << endl;
	if (buckets_ != nullptr) {
		Node* temp = buckets_[hc];
		while (temp != nullptr) {
			if (temp->s_ == s) {
				cout << "true has this value" << endl;
				return true;
			}
			temp = temp->next_;
		}
		cout << "false000 has not this value" << endl;
		return false;
	}
	cout << "false001 has not this value" << endl;
	return false;
}

void BucketList::insert(const string& s) {
	// IMPLEMENT ME
	cout << "insert start" << endl;
	bool boolV = contains(s);
	cout << boolV << ":1exist" << endl;
	if (!boolV) {
		cout << "begin insert" << endl;
		cout << getSize() << "number value" << endl;
		if (getSize() >= MAX_LOAD_FACTOR * c) {
			c = 2 * c;
		}
		cout << c << "current size value" << endl;
		int hc = h(s) % c;
		cout << hc << "hc address" << endl;
		//桶的尺寸变了需要清空数据重新插入
		//getSArr();
		if (buckets_[hc]!=nullptr) { //如果buckets_[hc]分配了内存
			cout << "2" << endl;
			Node* first = buckets_[hc]->next_;
			if (first != nullptr) { //如果buckets_[hc]->next_值不为空
				cout << "22" << endl;
				if (s.compare(first->s_) < 0) { //如果比第一个值小，则插入在第一个
					cout << "221" << endl;
					Node* tmpe = new Node;
					tmpe->s_ = s;
					tmpe->next_ = first;
					buckets_[hc]->next_ = tmpe;
				}else{
					cout << "222" << endl;
					if (first->next_!=nullptr) {
						cout << "2221" << endl;
						bool success = false;
						while (first->next_!=nullptr) { //如果buckets_[hc]->next_->next_值不为空
							cout << "22211" << endl; 
							Node* second = first->next_;
							if (s.compare(first->s_) >= 0 && s.compare(second->s_) < 0) {
								Node* tmpb = new Node;
								tmpb->s_ = s;
								tmpb->next_ = second;
								first->next_ = tmpb;
								cout << "插入最中间" << endl;
								success = true;
								break;
							}
							first = first->next_;
						}
						if (first->next_ == nullptr && !success) { //如果buckets_[hc]->next_->next_值为空
							cout << "22212" << endl;
							Node* tmph = new Node;
							tmph->s_ = s;
							tmph->next_ =nullptr;
							first->next_ = tmph;
							cout << "插入最后面" << endl;
						}
					}else { //如果buckets_[hc]->next_->next_值为空,代表只有一个值
						cout << "2221" << endl;
						Node* tmpd = new Node;
						tmpd->s_ = s;
						tmpd->next_ = nullptr;
						first->next_ = tmpd;
						cout << "插入最后面" << endl;
					}
				}
			}else { //如果buckets_[hc]->next_值为空,就代表一个都没有
				cout << "21" << endl;
				Node* tmpa = new Node;
				tmpa->s_ = s;
				first = tmpa;
				first->next_ = nullptr;
			}
		}
		if(buckets_[hc]==nullptr){ //如果buckets_[hc]没有分配内存
			cout << "1" << endl;
			buckets_[hc] = new Node;
			Node* tmp = new Node;
			tmp->s_ = s;
			tmp->next_ = nullptr;
			buckets_[hc]->next_ = tmp;
		}
		number++;
	}
}

void BucketList::remove(const string& s) {
	// IMPLEMENT ME
	cout << "remove start" << endl;
	bool boolV = contains(s);
	cout << boolV << "开始删除是存在吗exist" << endl;
	if (boolV) {
		cout << "begin remove" << endl;
		int hc = h(s) % c;
		Node* temp = buckets_[hc];
		Node* tmp = temp->next_;
		if (tmp->s_ == s) { // 如果第一个值就是该值
			cout << "delete1" << endl;
			cout << "find this value" << endl;
			if (tmp->next_ != nullptr) { //如果后面还有其他指针
				cout << "delete11" << endl;
				Node* tmpf = tmp;
				buckets_[hc]->next_ = tmp->next_;
				delete tmpf;
			}else { //如果只有该指针
				cout << "delete12" << endl;
				delete tmp;
				//delete buckets_[hc];
				buckets_[hc] = nullptr;
			}
		}else{ // 如果第一个值不是该值
			cout << "delete2" << endl;
			Node* tmpPrev = temp;
			if (tmpPrev == nullptr) return;
			Node* tmpNext = tmpPrev->next_;
			while (tmpNext != nullptr) { //当前指针不为空指针时
				if (tmpNext->s_ == s) {
					cout << "delete21" << endl;
					cout << "find this value" << endl;
					tmpPrev->next_ = tmpNext->next_;
					delete tmpNext;
					break;
				}
				tmpPrev = tmpNext;
				tmpNext = tmpNext->next_;
			}
		}
		number--;
		cout << "remove success" << endl;
	}
}

string BucketList::toString() const {
	// IMPLEMENT ME
	cout << "toString start" << getCap() << endl;
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
	return res; // dummy
}

int BucketList::h(const string& s) const {
	// IMPLEMENT ME
	int sum = 0;
	/*for (char c : s) {
		sum += (int)c;
	}*/
	int num = s.size();
	for (int i = 0; i < num; i++) {
		sum += (int)pow(2,i)*s[i];
	}
	//cout << "字符串ASCII值的和为" << sum << endl;
	return sum; // dummy
}

int BucketList::getSize() const {
	// IMPLEMENT ME
	//cout << "getSize start" << endl;
	return number; // dummy
	int aaa = 0;
	for (int i = 0; i < getCap(); i++) {
		Node* tmp = buckets_[i];
		if (tmp != nullptr) {
			while (tmp != nullptr) {
				if (tmp == buckets_[i]) {
				}
				else {
					aaa++;
				}
				tmp = tmp->next_;
			}
		}
	}
	return aaa; // dummy
}

int BucketList::getCap() const {
	// IMPLEMENT ME
	//cout << "getCap start" << endl;
	return c; // dummy
}

string BucketList::getSArr() const{
	cout << getSize() << getCap() << "字符串数量和桶的数量";
	int arrSize = getSize();
	string arr;
	if (arrSize == 0) {
		return arr;
	}else if(arrSize>0){
		for (int i = 0; i < getCap(); i++) {
			Node* tmp = buckets_[i];
			if (tmp != nullptr) {
				while (tmp->next_ != nullptr) {
					arr += tmp->next_->s_ + "";
					tmp->next_ = tmp->next_->next_;
				}
			}
		}
		cout << arr;
		return arr;
	}
}
