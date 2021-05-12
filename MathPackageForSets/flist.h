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
	//Добавляем элемент
	bool push(const std::string&);
	//Удаляем элемент
	bool erase(const std::string&);
	// Есть ли элемент
	bool iselem(const std::string& str) const;
	// Печать
	void printAll() const;
	// размер
	size_t getSize() const;
	// очистка
	void clearNodes();
	//~fList();
	
	// проверка вхождения
	static bool inList(const fList&, const fList&);
	// объединение
	static fList unionList(const fList&, const fList&);
	// пересечение
	static fList intersectList(const fList&, const fList&);
	// разность
	static fList divList(const fList&, const fList&);
	
	//fList& operator=(const fList&);
	fList(const fList&);
private:
	Node* first;
	Node* end;
	size_t size;
	static const size_t MAX_SIZE = 80;
	void append(const std::string&); // Добавляет в конец и не производит проверку на повторение/упорядоченность элементов
};
