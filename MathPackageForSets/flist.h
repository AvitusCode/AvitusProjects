#pragma once
#include <string>

struct Node
{
	std::string data;
	Node* next_node;
};

class fList
{
public:
	fList();
	//��������� �������
	bool push(const std::string&);
	//������� �������
	bool erase(const std::string&);
	// ���� �� �������
	bool iselem(const std::string& str) const;
	// ������
	void printAll() const;
	// ������
	size_t getSize() const;
	// �������
	void clearNodes();
	//~fList();
	
	// �������� ���������
	static bool inList(const fList&, const fList&);
	// �����������
	static fList unionList(const fList&, const fList&);
	// �����������
	static fList intersectList(const fList&, const fList&);
	// ��������
	static fList divList(const fList&, const fList&);
	
	//fList& operator=(const fList&);
	fList(const fList&);
private:
	Node* first;
	Node* end;
	size_t size;
	static const size_t MAX_SIZE = 80;
	void append(const std::string&); // ��������� � ����� � �� ���������� �������� �� ����������/��������������� ���������
};
