#pragma once
#include <iostream>
#include <stdexcept>
#include <functional>
#include <string>
#include "LinkedList.h"

using namespace std;


template <class Key, class Content>
class HashElement {
protected:
	Content content;
	Key key;

public:
	HashElement(Key _key, Content _content) {
		content = Content(_content);
		key = Key(_key);
	}
	HashElement(Key _key) {
		key = Key(_key);
	}

	Content& get_content() { return content; }
	Key get_key() { return key; }

	void set_content(Content _content) { content = _content; }

	bool operator==(HashElement<Key, Content> other) { return key == other.key; }
	bool operator==(Key other) { return key == other; }

	friend ostream& operator<<(ostream& os, const HashElement<Key, Content>& elem) {
		os << elem.key << " : " << elem.content;
		return os;
	}
};

template <class Key, class Content>
class HashList {
protected:
	unsigned int size;

	LinkedList<HashElement<Key, Content>>* arr;

public:
	HashList(unsigned int _size) {
		size = _size;
		arr = new LinkedList<HashElement<Key, Content>>[size];
	}
	~HashList() {
		delete[] arr;
	}

	bool is_empty() {
		for (LinkedList<HashElement<Key, Content>> i : *this) {
			if (i.get_size() > 0) return false;
		}
		return true;
	}

	unsigned int hash(Key key) {
		return std::hash<Key>{}(key) % size;
	}

	void put(Key key, Content content) {
		int hash_i = hash(key);
		int index = arr[hash_i].index<Key>(key);

		if (index < 0) {
			arr[hash_i].add(HashElement<Key, Content>(key, content));
		}
		else{
			arr[hash_i][index]->set_content(content);
		}
	}

	Content& get(Key key) {
		int hash_i = hash(key);
		int index = arr[hash_i].index<Key>(key);

		if (index < 0) {
			throw std::invalid_argument("Key is absent in dictionary");
		}
		else {
			return arr[hash_i][index]->get_content();
		}
	}

	bool contains(Key key) {
		int hash_i = hash(key);
		return arr[hash_i].contains<Key>(key);
	}

	Content& operator[](Key key) {
		return get(key);
	}

	Content pop(Key key) {
		int hash_i = hash(key);
		int index = arr[hash_i].index<Key>(key);

		if (index < 0) {
			throw std::invalid_argument("Key is absent in dictionary");
		}
		else {
			return arr[hash_i].pop(index).get_content();
		}
	}

	friend ostream& operator<<(ostream& os, HashList<Key, Content>& l) {
		os << "{";
		for (LinkedList<HashElement<Key, Content>> i : l) {
			for (ListNode<HashElement<Key, Content>> j : i) {
				os << j << ", ";
			}
		}
		os << "}";
		return os;
	}

	struct Iterator
	{
		using iterator_category = std::forward_iterator_tag;
		using difference_type = std::ptrdiff_t;

		using value_type = LinkedList<HashElement<Key, Content>>;
		using pointer = LinkedList<HashElement<Key, Content>>*;
		using reference = LinkedList<HashElement<Key, Content>>&;

		Iterator(pointer ptr) : m_ptr(ptr) {}

		reference operator*() const { return *m_ptr; }
		pointer operator->() { return m_ptr; }
		Iterator& operator++() { m_ptr++; return *this; }
		Iterator operator++(int) { Iterator tmp = *this; ++(*this); return tmp; }
		friend bool operator== (const Iterator& a, const Iterator& b) { return a.m_ptr == b.m_ptr; };
		friend bool operator!= (const Iterator& a, const Iterator& b) { return a.m_ptr != b.m_ptr; };

	private:
		pointer m_ptr;
	};

	Iterator begin() { return Iterator(&arr[0]); }
	Iterator end() { return Iterator(&arr[size]); }
};