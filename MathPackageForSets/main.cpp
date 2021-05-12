#include <iostream>
#include <sstream>

#include "Sets.h"
#include "parser.h"

using namespace std;

int main(void) 
{
	Sets data;
	
	for (string line; getline(cin, line); )
	{
		istringstream is(line);
		
		string com;
		is >> com;
		
		if (com == "ADD")
		{
			string name, elems;
			is >> name;
			
			while (is >> elems)
			{
				try{
			      data.insert(name, elems);
				}
				catch (invalid_argument& e)
				{
					std::cerr << e.what() << std::endl;
				}
				catch(bad_alloc& e) // Ошибки при выделении памяти сообщают, что лучше бы программу выключить
				{
					std::cerr << e.what() << std::endl;
					exit(-1);
				}
			}
			
		}
		else if (com == "DEL")
		{
			string name;
			info inf = info::SUCCESS;
			is >> name;
			
			if (is.eof() && name != "")
			{
				inf = data.del(name);
			}
			else if (name != "")
			{
				string elems;
				while (is >> elems)
				{
					inf = data.del(name, elems);
				}
			}
			else // Удаляем все!
			{
				data.clear();
			}
			
			if (inf != info::SUCCESS){
				std::cerr << "There was a problem with delition" << std::endl;
			}
		}
		else if (com == "RANK")
		{
			string name;
			is >> name;
			
			try 
			{
				Set selm = data.getSetByName(name);
				std::cout << data.getRank(selm) << std::endl;
			}
			catch (exception& e)
			{
				std::cout << "There is no such entity";
				continue;
			}
			
		}
		else if (com == "PRINT")
		{
			string name;
			is >> name;

			if (name == "")
			{
				data.Print();
				continue;
			}
			
			try
			{
			    Set selm = data.getSetByName(name);
			    std::cout << selm.name << ": ";
				selm.s.printAll();
			}
			catch(exception& e)
			{
				std::cout << "There is no such entity" << std::endl;
				continue;
			}
			
		}
		else if (com == "EVALUATE")
		{
			is >> ws;

			try
			{
				auto node = Parse(is, data);
				Set nelem = node->Evaluate();
				data.addEntity(nelem);
			}
			catch (exception& e)
			{
				std::cout << e.what() << std::endl;
				continue;
			}
		}
		else if (com == "EIN")
		{
			string elm, name;
			is >> elm >> name;
			
			if (data.count(name, elm))
				std::cout << "Yes" << std::endl;
			else
				std::cout << "No" << std::endl;
		}
		else if (com == "IN")
		{
			string name1, name2;
			is >> name1 >> name2;
			
			try
			{
			    Set one = data.getSetByName(name1);
			    Set two = data.getSetByName(name2);
			    
			    if (data.isinside(one, two))
			    	std::cout << "Yes" << std::endl;
			    else
			    	std::cout << "No" << std::endl;
			}
			catch(exception& e)
			{
				std::cerr << "There is no such entity " << e.what() << std::endl; 
		        continue;
			}
		}
		else
		{
			std::cout << com << " undefined token, try again" << std::endl;
		}
	}
	
	return 0;
}
