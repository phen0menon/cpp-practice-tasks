/**
 * Simple LRUCache implementation
 */

#include <iostream>
#include <map>
#include <string>
using namespace std;

struct Node {
	Node* next;
	Node* prev;
	int value;
	int key;
	Node(Node* p, Node* n, int k, int val) :prev(p), next(n), key(k), value(val) {};
	Node(int k, int val) :prev(NULL), next(NULL), key(k), value(val) {};
};

class Cache {
protected:
	// Map the key to the node in the linked list
	map<int, Node*> mp;
	// Capacity
	int cp;
	// Double linked list tail pointer
	Node* tail;
	// Double linked list head pointer
	Node* head;
	virtual void set(int, int) = 0;
	virtual int get(int) = 0;
};

class LRUCache : public Cache {
private:
	int capacity;

public:
	LRUCache(int capacity) {
		this->capacity = capacity;
	}

	void set(int key, int value) override {
		Node *N;

		// No nodes
		if (mp.empty()) {
			N = new Node(key, value);
			tail = head = N;
			mp[key] = N;

			return;
		}

		map<int, Node*>::iterator  it = mp.find(key);

		// In hashtable
		if (it != mp.end()) {
			it->second->value = value;

			// Head?
			if (head == it->second)
				return;

			it->second->prev->next = it->second->next;

			// Tail?
			if (tail == it->second)
				tail = tail->prev;
			else
				it->second->next->prev = it->second->prev;

			it->second->next = head;
			it->second->prev = NULL;
			head->prev = it->second;
			head = it->second;
		}
		else {
			N = new Node(head->prev, head, key, value);
			head->prev = N;
			head = N;
			mp[key] = N;

			if (mp.size() > cp) {
				tail = tail->prev;
				mp.erase(tail->next->key);
				delete tail->next;
				tail->next = NULL;
			}
		}
	}
	int get(int key) override {
		map<int, Node*>::iterator it = mp.find(key);

		if (it != mp.end())
			return it->second->value;

		return -1;
	}
};

int main() {
	int n, capacity, i;
	cin >> n >> capacity;

	LRUCache l(capacity);

	for (i = 0; i < n; i++) {
		string command;
		cin >> command;

		if (command == "get") {
			int key;
			cin >> key;
			cout << l.get(key) << endl;
		}
		else if (command == "set") {
			int key, value;

			cin >> key >> value;
			l.set(key, value);
		}
	}

	return 0;
}