#pragma once

#include <memory>
#include <string>

#include "Sets.h"

class Parser
{
public:
	virtual Set Evaluate() const = 0;
	virtual ~Parser() = default;
};

class Value : public Parser
{
public:
	Value(const Set& val);
	
	Set Evaluate() const override;
	
private:
	const Set _value;
};


class Op : public Parser
{
public:
	Op(const std::string& str, bool br = false);
	
	Set Evaluate() const override;
	
	void SetLeft(std::shared_ptr<Parser> node) {_left = node; }
	void SetRight(std::shared_ptr<Parser> node) {_right = node; }
	
	const bool brakets;
private:
	const std::string _op;
	std::shared_ptr<const Parser> _left, _right;
};

std::shared_ptr<Parser> Parse(std::istringstream& is, const Sets& dt);
