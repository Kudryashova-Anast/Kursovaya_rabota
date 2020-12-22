/** 
* @file LicenseChecker.h
* @author А.А.Кудряшова
* @version 1.0
* @date 09.12.2020
* @copyright ИБСТ ПГУ
* @brief Заголовочный файл для модуля LicenseChecker
*/
#pragma once
#include <iostream>
#include <string>
#include <fstream>

#include <cstdlib>//exit()
#include <unistd.h> //close()
#include <netinet/in.h>//sockaddr_in + <sys/socket.h>
#include <arpa/inet.h> //inet_aton()
using namespace std;

/** @brief Класс проверки лицензиии
* @details В объект класса передаётся серийный номер и лицензионный ключ
* с помощью метода check осуществляется проверка лицензии на сервере 127.0.0.1:44214
* @warning Реализация только для латинских символов
*/
class LicenseChecker
{
private:
	string idpass;
	string sAddr = "127.0.0.1";
	int sPort = 44214;
public:
	LicenseChecker(string num, string key);
	bool check();
};

/** @brief Класс обработки ошибок checker_error
* @details Выводит сообщения об ошибках и завершает программу
*/
class checker_error: public std::invalid_argument
{
public:
	explicit checker_error (const std::string& what_arg):
		std::invalid_argument(what_arg) {}
	explicit checker_error (const char* what_arg):
		std::invalid_argument(what_arg) {}
};