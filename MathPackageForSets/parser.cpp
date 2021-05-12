#include "parser.h"
#include <stack>
#include <stdexcept>
#include <sstream>

// Доработать парсер для скобочек
Value::Value(const Set& val) :_value(val) {};
	
Set Value::Evaluate() const{
	return _value;
}

Op::Op(const std::string& str, bool br) : brakets(br), _op(str) {};
	
Set Op::Evaluate() const
{
	if (_op == "UNION")
	{
		Set res;
		res.name = _left->Evaluate().name + _right->Evaluate().name;
		res.s = fList::unionList(_left->Evaluate().s, _right->Evaluate().s);

		return res;
	} 
	else if (_op == "INTERSECTION")
	{
		Set res;
		res.name = _left->Evaluate().name + _right->Evaluate().name;
		res.s = fList::intersectList(_left->Evaluate().s, _right->Evaluate().s);

		return res;
	} 
	else if (_op == "DIV")
	{
		Set res;
		res.name = _left->Evaluate().name + _right->Evaluate().name;
		res.s = fList::divList(_left->Evaluate().s, _right->Evaluate().s);

		return res;
	} 
	else if (_op == "XDIV")
	{
		fList a = fList::unionList(_left->Evaluate().s, _right->Evaluate().s);
		fList b = fList::intersectList(_left->Evaluate().s, _right->Evaluate().s);
		Set res;
		res.name = _left->Evaluate().name + _right->Evaluate().name;
		res.s = fList::divList(a, b);

		return res;
	}
}


std::shared_ptr<Parser> Parse(std::istringstream& is, const Sets& dt)
{
	//Случай пустоты
	if (is.peek() == ' ' || is.peek() == '\n' || is.peek() == '\r')
		throw std::invalid_argument("ERROR: empty line");

	// Что-то вроде простой реализации алгоритма Сортировочной станции
	std::stack<std::shared_ptr<Parser>> values;
	std::stack<std::shared_ptr<Op>> ops;
	bool brakets = false;
	
	auto PopOps = [&](){
		while (!ops.empty())
		{
			auto value1 = values.top();
			values.pop();
			auto value2 = values.top();
			values.pop();
			auto op = ops.top();
			ops.pop();

			op->SetRight(value1);
			op->SetLeft(value2);

			values.push(op);
			if (op->brakets)
				break;
			
		}
	};
	
	std::string value;
	int cbrakets = 0;
	while (is.peek() != '\0' && is.peek() != '\r' && is.peek() != '\n' && !is.eof())
	{
		is >> std::ws;
		if (is.peek() == '(')
		{
			cbrakets++;
			brakets = true;
			is.ignore(1);
			continue;
		}
		else if (is.peek() == ')')
		{

			is.ignore(1);
			cbrakets--;
			if (cbrakets != 0)
				brakets = true;

			PopOps();
			continue;
		}

		is >> value;

		if (value == "UNION" || value == "INTERSECTION" || value == "DIV" || value == "XDIV")
		{
			if (!brakets)
			 PopOps();
			ops.push(std::make_shared<Op>(value, brakets));
			brakets = false;
		}
		else if (value == "(")
		{
			cbrakets++;
			brakets = true;
		}
		else if (value == ")")
		{
			cbrakets--;
			if (cbrakets != 0)
				brakets = true;
			PopOps();
		}
		else{
			values.push(std::make_shared<Value>(dt.getSetByName(value)));
		}

		if (cbrakets < 0)
			throw std::invalid_argument("Brakets error!");
		
	}

	if (cbrakets < 0)
		throw std::invalid_argument("Brakets error!");

	while (!ops.empty())
		PopOps();
	
	return values.top();
}

