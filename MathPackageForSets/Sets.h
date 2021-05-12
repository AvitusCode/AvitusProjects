#pragma once
#include <string>
#include <map>
#include "fList.h"

enum class info
{
	SUCCESS,
	NO_ENTITY,
	WARNING
};

struct Set
{
	std::string name;
	fList s;
	
	Set() = default;
	Set(const Set&);
};


class Sets
{
public:
	Sets() = default;
	~Sets();
	
	// Общие операции
	size_t getRank(const Set& name) const; // Мощность конкретного множества
	void addEntity(const Set& ent); // добавить целое множество
	bool insert(const std::string& name, const std::string& elem); // добавить элемент в множество
	info del(const std::string& name, const std::string& elem = ""); // Удалить из множества или все множество
	void clear();
	bool count(const std::string& name, const std::string& elem) const; // Есть ли элемент в множестве
	Set getSetByName(const std::string& name) const;
	
	//Операции над множествами
	Set unionSets(const Set& left, const Set& right) const;
	Set intersectSets(const Set& left, const Set& right) const;
	Set divSets(const Set& left, const Set& right) const;
	Set simdivSets(const Set& left, const Set& right) const;
	bool isinside(const Set& left, const Set& right) const;
	
	void Print() const;
	Sets(Sets&&) = delete;
	Sets(const Sets&) = delete;
	Sets& operator=(const Sets&) = delete;
	
private:
	std::map<std::string, fList> sets;
};
