#include "Sets.h"
#include <iostream>

Set::Set(const Set& sl)
{
	name = sl.name;
	s = sl.s;
}

Sets::~Sets(){
	clear();
}

size_t Sets::getRank(const Set& name) const{
	return name.s.getSize();
}

void Sets::addEntity(const Set& ent){
	sets[ent.name] = ent.s;
}

bool Sets::insert(const std::string& name, const std::string& elem)
{
	if (sets.count(name) == 0){
		sets[name].push(elem);
		return true;
	}
	
	fList& fl = sets[name];
	
	return fl.push(elem);
}


info Sets::del(const std::string& name, const std::string& elem)
{
	if (sets.count(name) == 0)
		return info::NO_ENTITY;
	
	if (elem == "")
	{
		sets[name].clearNodes();
		sets.erase(name);
		return info::SUCCESS;
	}
	
	fList& fl = sets[name];
	
	return fl.erase(elem) ? info::SUCCESS : info::WARNING;
}

void Sets::clear()
{
	for (auto& [key, value] : sets)
	{
		value.clearNodes();
	}
	sets.clear();
}


bool Sets::count(const std::string& name, const std::string& elem) const
{
	if (sets.count(name) == 0)
		return false;
	
	const fList& fl = sets.at(name);
	
	return fl.iselem(elem);
}


// throws exception
Set Sets::getSetByName(const std::string& name) const
{
	Set result;
	
	result.name = name;
	result.s = sets.at(name);
	
	return result;
}
	

Set Sets::unionSets(const Set& left, const Set& right) const
{
	Set result;
	
	result.name = left.name + right.name;
    result.s = fList::unionList(left.s, right.s);
    
    return result;
}


Set Sets::intersectSets(const Set& left, const Set& right) const
{
	Set result;
	
	result.name = left.name + right.name;
	result.s = fList::intersectList(left.s, right.s);
	
	return result;
}

Set Sets::divSets(const Set& left, const Set& right) const
{
	Set result;
		
	result.name = left.name + right.name;
	result.s = fList::divList(left.s, right.s);
	
	return std::move(result);
}

Set Sets::simdivSets(const Set& left, const Set& right) const
{
	Set result;
			
	result.name = left.name + right.name;
	fList a = fList::unionList(left.s, right.s);
	fList b = fList::intersectList(left.s, right.s);
	result.s = fList::divList(a, b);	
	return result;
}


bool Sets::isinside(const Set& left, const Set& right) const{
	return fList::inList(left.s, right.s);
}

void Sets::Print() const
{
	for (const auto& [key, value] : sets)
	{
		std::cout << key << ": ";
		value.printAll();
	}
}




