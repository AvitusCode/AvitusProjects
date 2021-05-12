#include "fList.h"
#include <iostream>
#include <stdexcept>

const size_t fList::MAX_SIZE;

inline void checkNull(const Node* ptr)
{
	if (ptr == nullptr)
		throw std::bad_alloc();
}

fList::fList(){
	first = nullptr;
	end = nullptr;
	size = 0;
}

fList::fList(const fList& fl)
{
	first = fl.first;
	end = fl.end;
	size = fl.size;
}

// Вставка в упорядоченный список
bool fList::push(const std::string& str)
{
	if (str.size() > MAX_SIZE)
		throw std::invalid_argument("ERROR: string is too big!");

	if (first == nullptr)
	{
		first = new Node{ str, nullptr };
		end = first;
		checkNull(first);
		return true;
	}
	else if (first->next_node == nullptr)
	{
		if (str == first->data)
			return false;
		if (str < first->data)
		{
			first->next_node = new Node{first->data, nullptr};
			checkNull(first->next_node);
			first->data = str;
		}
		else
		{
			first->next_node = new Node{ str, nullptr };
			checkNull(first->next_node);
		}

		end = first->next_node;
		return true;
	}

	Node* current = first, *prev = first;

	while (current->next_node != nullptr && str >= current->data)
	{
		if (str == current->data)
			return false;

		prev = current;
		current = current->next_node;
	}

	if (str == current->data)
		return false;

	Node* nxt = new Node{ str, nullptr };
	checkNull(nxt);

	if (current->next_node == nullptr)
	{
		if (str >= current->data)
		{
			current->next_node = nxt;
			end = nxt;
		}
		else
		{
			nxt->next_node = current;
			prev->next_node = nxt;
		}
	}
	else
	{
		if (current == first)
		{
			nxt->next_node = current->next_node;
			first = nxt;
		}
		else
		{
			prev->next_node = nxt;
			nxt->next_node = current;
		}
	}

	return true;
}

bool fList::erase(const std::string& str)
{
	if (first == nullptr)
		return false;
	
	Node *prev = first, *current = first->next_node;
	if (current == nullptr)
	{
		if (prev->data == str)
		{
			delete prev;
			end = first = nullptr;
			size--;
			return true;
		}
		else
			return false;
	}
	
	
	while (current != nullptr)
	{
		if (current->data == str)
		{
			prev->next_node = current->next_node;
			
			if (prev->next_node == nullptr)
				end = prev;
			
			delete current;
			size--;
			return true;
		}
		
		prev = current;
		current = current->next_node;
	}
	
	return false;
}

void fList::append(const std::string& str)
{
	if (first == nullptr)
	{
		push(str);
		return;
	}
	
	end->next_node = new Node{str, nullptr};
	checkNull(end->next_node);
	end = end->next_node;
	size++;
}

bool fList::iselem(const std::string& str) const
{
	Node *temp = first;
	
	while (temp != nullptr)
	{
		if (temp->data == str)
			return true;
		else
			return false;
	}
	
	return false;
}

bool fList::inList(const fList& left, const fList& right)
{
	Node *pa = left.first, *pb = right.first;
	
	while (pa != nullptr && pb != nullptr)
	{
		if (pa->data < pb->data)
			return false;
		else if (pa->data > pb->data)
			pb = pb->next_node;
		else
		{
			pa = pa->next_node;
			pb = pb->next_node;
		}
	}
	
	return pa == nullptr;
}

fList fList::unionList(const fList& left, const fList& right)
{
	fList c;
	std::string d;
	
	Node *pa = left.first, *pb = right.first;
	
	while (pa != nullptr && pb != nullptr)
	{
		if (pa->data < pb->data)
		{
			d = pa->data;
			pa = pa->next_node;
		}
		else if (pa->data > pb->data)
		{
			d = pb->data;
			pb = pb->next_node;
		}
		else
		{
			d = pa->data;
			pa = pa->next_node;
			pb = pb->next_node;
		}
		
		c.append(d);
	}
	
	Node *p = c.end;
	if (pa != nullptr)
		p = pa;
	if (pb != nullptr)
		p = pb;
	while (p != nullptr)
	{
		c.append(p->data);
		p = p->next_node;
	}
	
	return c;
}

fList fList::intersectList(const fList& left, const fList& right)
{
	fList c;
	Node *pa = left.first, *pb = right.first;
	
	while (pa != nullptr && pb != nullptr)
	{
		if (pa->data < pb->data)
			pa = pa->next_node;
		else if (pa->data > pb->data)
			pb = pb->next_node;
		else
		{
			c.append(pa->data);
			pa = pa->next_node;
			pb = pb->next_node;
		}
	}
	
	return c;
}

fList fList::divList(const fList& left, const fList& right)
{
	fList c;
	Node *pa = left.first, *pb = right.first;
		
	while (pa != nullptr && pb != nullptr)
	{
		if (pa->data < pb->data)
		{
			c.append(pa->data);
			pa = pa->next_node;
		}
		else if (pa->data > pb->data)
		{
			pb = pb->next_node;
		}
		else
		{
			pa = pa->next_node;
			pb = pb->next_node;
		}
	}
	
	while (pb == nullptr && pa != nullptr)
	{
		c.append(pa->data);
		pa = pa->next_node;
	}
	
	return c;
}

void fList::printAll() const
{
	Node* temp = first;
	bool fr = true;
	
	std::cout << "{ ";
	while (temp != nullptr)
	{
		if (!fr)
		{
			std::cout << ", ";
		}

		std::cout << temp->data;
		temp = temp->next_node;
		fr = false;
	}
	std::cout << "}";
	std::cout << std::endl;
}

size_t fList::getSize() const{
	return size;
}

void fList::clearNodes()
{
	Node *temp = first;
		
	while (temp != nullptr)
	{
		Node *prev = temp;
		temp = temp->next_node;
		size = 0;
		delete prev;
	}
}

//fList::~fList(){
//	clearNodes();
//}




