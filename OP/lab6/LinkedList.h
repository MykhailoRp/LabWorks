#pragma once
#include <iostream>
#include <stdexcept>

using namespace std;

template <class ContentClass>
class ListNode {
protected:
	ContentClass* content = nullptr;
	ListNode<ContentClass>* child = nullptr;

public:
	ListNode(ContentClass _content, ListNode<ContentClass>* _child = nullptr) {
		set_content(_content);
		child = _child;
	}

	ListNode() {};

	ListNode(ListNode &other) {
		if (other.content != nullptr) {
			delete content;
			content = new ContentClass(*other.content);
		}
		child = other.child;
	};

	ListNode(ListNode<ContentClass>&& other)  {
		content = other.content;
		child = other.child;

		other.content = nullptr;
		other.child = nullptr;
	}

	~ListNode() { 
		delete content; 
	}

	ContentClass* get_content() { return content; }

	void set_content(ContentClass _content){ 
		delete content;
		content = new ContentClass(_content); 
	}

	ListNode<ContentClass>* get_child() { 
		return child; 
	}
	void set_child(ListNode<ContentClass>* _child) { child = _child; }

	friend ostream& operator<<(ostream& os, const ListNode<ContentClass>& node) {
		os << *node.content;
		return os;
	}

	ListNode<ContentClass>& operator=(ListNode<ContentClass>&& other)  {

		if (this != &other)
		{
			delete content;

			content = other.content;
			child = other.child;

			other.content = nullptr;
			other.child = nullptr;
		}
		return *this;
	}
};

template <class ContentClass>
class LinkedList {
protected:
	unsigned int size = 0;
	ListNode<ContentClass>* head = nullptr;

	ListNode<ContentClass>* get(unsigned int index) {
		ListNode<ContentClass>* element = head;

		while (index > 0) {
			element = element->get_child();

			if (element == nullptr) throw std::out_of_range("Index out of range");

			index--;
		}

		return element;
	}

	void clear_head() {
		while (size > 0) {
			pop(size - 1);
		}
	}

public:
	LinkedList(){}

	LinkedList(LinkedList<ContentClass>&& other)  {
		head = other.head;
		size = other.size;

		other.head = nullptr;
		other.size = 0;
	}
	LinkedList(LinkedList<ContentClass>& other)  {
		for (ListNode<ContentClass> i : other) {
			append(*i.get_content());
		}
	}

	~LinkedList() {
		clear_head();
	}

	unsigned int get_size() { return size; }

	void add(ContentClass element) {

		ListNode<ContentClass>* temp = nullptr;

		if (head == nullptr) {
			head = new ListNode<ContentClass>(element);
		}
		else {
			temp = new ListNode<ContentClass>(element, head);
			head = temp;
		}

		size++;
	}
	void append(ContentClass element) {

		if (head == nullptr) {
			head = new ListNode<ContentClass>(element);
		}
		else {
			get(size - 1)->set_child(new ListNode<ContentClass>(element));
		}

		size++;
	}
	
	ContentClass pop_first() {
		ListNode<ContentClass>* temp = nullptr;

		if (head != nullptr) {
			temp = head->get_child();
			ContentClass return_val = *(head->get_content());
			delete head;
			head = temp;


			size--;

			return return_val;
		}
		else {
			throw std::out_of_range("Cant pop empty list");
		}
	}
	ContentClass pop(unsigned int index) {

		if (index == 0) return pop_first();

		ListNode<ContentClass>* element = head;
		ListNode<ContentClass>* prev_element = head;

		while (index > 0) {
			prev_element = element;
			element = element->get_child();

			if (element == nullptr) throw std::out_of_range("Index out of range");

			index--;
		}

		prev_element->set_child(element->get_child());

		ContentClass return_val = *(element->get_content());

		delete element;

		size--;

		return return_val;
	}

	template<class iContentClass>
	int index(iContentClass to_find) {

		ListNode<ContentClass>* element = head;

		int index = 0;

		while (element != nullptr) {

			if (*(element->get_content()) == to_find) return index;

			index++;

			element = element->get_child();
		}

		return -1;
	}

	template<class iContentClass>
	bool contains(iContentClass to_find) {
		return index<iContentClass>(to_find) >= 0;
	}

	ContentClass* operator[](unsigned int index) {

		ListNode<ContentClass>* element = head;

		while (index > 0) {
			element = element->get_child();

			if (element == nullptr) throw std::out_of_range("Index out of range");

			index--;
		}

		return element->get_content();
	}

	void operator=(LinkedList<ContentClass>& other)	{
		clear_head();

		for (ListNode<ContentClass> i : other) {
			append(*i.get_content());
		}
	}

	LinkedList<ContentClass>& operator=(LinkedList<ContentClass>&& other) noexcept	{
		if (this != &other)
		{
			clear_head();

			head = other.head;
			size = other.size;

			other.head = nullptr;
			other.size = 0;
		}
		return *this;
	}

	struct Iterator
	{
		using iterator_category = std::forward_iterator_tag;
		using difference_type = std::ptrdiff_t;
		using value_type = ListNode<ContentClass>;
		using pointer = ListNode<ContentClass>*;
		using reference = ListNode<ContentClass>&;

		Iterator(pointer ptr) : m_ptr(ptr) {}

		reference operator*() const { return *m_ptr; }
		pointer operator->() { return m_ptr; }
		Iterator& operator++() { 
			m_ptr = m_ptr->get_child();
			return *this; 
		}
		Iterator operator++(int) { 
			Iterator tmp = *this; 
			++(*this); 
			return tmp; 
		}
		friend bool operator== (const Iterator& a, const Iterator& b) { return a.m_ptr == b.m_ptr; };
		friend bool operator!= (const Iterator& a, const Iterator& b) { return a.m_ptr != b.m_ptr; };

	private:
		pointer m_ptr;
	};

	friend ostream& operator<<(ostream& os, LinkedList<ContentClass>& l) {
		os << "[";
		for (ListNode<ContentClass> i : l) {
			os << i << ", ";
		}
		os << "]";
		return os;
	}

	Iterator begin() { return Iterator(head); }
	Iterator end() { return Iterator(nullptr); }
};