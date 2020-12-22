#pragma once
#include <iostream>
#include <fstream>
#include <exception>

#include <unistd.h> //close()
#include <arpa/inet.h> //inet_aton()
#include <string.h>

using namespace std;

class DataBase
{
private:
	string idpass;
	string database_path;//адрес Базы Данных
public:
	DataBase(string DATABASE_PATH, const string IDPASS);
	bool check() const;
};


//Анализ ошибок
class checker_error: public std::invalid_argument
{
public:
	explicit checker_error (const std::string& what_arg):
		std::invalid_argument(what_arg) {}
	explicit checker_error (const char* what_arg):
		std::invalid_argument(what_arg) {}
};