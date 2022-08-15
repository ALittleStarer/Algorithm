#pragma once
#include<iostream>
#include<unordered_map>
using namespace std;

/*双端链表*/
struct DeNode
{
	DeNode* next;
	DeNode* pre;
	int val;
	DeNode(): val(0),next(NULL),pre(NULL){}
	DeNode(int value):val(value),next(NULL),pre(NULL){}
	DeNode(int value,DeNode* precent):val(value),next(NULL),pre(precent){}
};

/*
*  LRU算法：最近最少用
* 实现方式：双端链表 + 哈希
*/
class LRU
{
private:
	unordered_map<int, DeNode*> findMap;
	DeNode* head = NULL;
	DeNode* tail = NULL;
public:
	LRU() {
		head = NULL;
		tail = NULL;
	}
	~LRU() {
		while(head){
			DeNode* cur = head;
			head = head->next;
			delete cur;
		}
	}

	void put(int val) {
		if (findMap.find(val) != findMap.end()) {
			return;
		}
		DeNode* newnode = new DeNode(val, tail);
		findMap[val] = newnode;
		if (!tail) {
			head = newnode;
			tail = newnode;
		}
		else {
			tail->next = newnode;
			tail = newnode;
		}
	}

	void call(int val) {
		if (findMap.find(val) == findMap.end()) {
			put(val);
			return;
		}
		else {
			DeNode* node = findMap[val];
			if (node->pre&&node->next) {
				node->pre->next = node->next;
				node->next->pre = node->pre;
				node->pre = tail;
				tail->next = node;
				node->next = NULL;
				tail = tail->next;
			}
			else if (node->next) {
				displace();
			}
			else {
				return;
			}
		}
	}

	void displace() {
		tail->next = head;
		head = head->next;
		tail->next->next = NULL;
		tail = tail->next;
	}

	void show() {
		DeNode* cur = head;
		while (cur) {
			cout << cur->val << " ";
			cur = cur->next;
		}
		cout << endl;
	}
};

