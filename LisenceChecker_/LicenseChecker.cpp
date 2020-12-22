/**
 * @file LicenseChecker.cpp
 */
#include <../LicenseChecker/LicenseChecker.h>
/**
* @brief Конструктор
* @param num - серийный номер, должен быть натуральным числом.
* key - лицензионный ключ, длинна 9 символов, содержит прописные латинские символы и цифры
* @throw checker_error, если произошла ошибка.
* @return Строка вида "num/key"
*/
LicenseChecker::LicenseChecker(string num, string key){
	// Валидация номера
	if(num.empty() || num[0] == '0')
		throw checker_error("Invalid serial number");
	for(int i = 0; i < num.length(); i++){
		if(num[i] < 48 || num[i] > 57)
			throw checker_error("Invalid serial number");
	}
	
	// Валидация ключа
	if(key.length() != 9)
		throw checker_error("Invalid license key");
	for(int i = 0; i < key.length(); i++){
		if(key[i] < 48 || (key[i] > 57 && key[i] < 65) || key[i] > 90)
			throw checker_error("Invalid license key");
	}
	
	idpass = num + "/" + key;
}
/**
* @brief Проверка лицензии
* @details Подключается к серверу 127.0.0.1:44214 по протоколу UDP
* отправляет ему строку idpass
* @throw checker_error, если произошла ошибка.
* @return true если номер и ключ найдены в БД, false если нет
*/
bool LicenseChecker::check(){
	size_t size = idpass.size();
	
	//запись пароля,логина в буфер для отправки серверу
	char self_bufer[256] = {0};
	for(size_t i=0; i < size; i++){
		self_bufer[i] = idpass[i];
	}

	int sock = 0;
	struct sockaddr_in serv_addr;
	if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
		throw checker_error("Socket creation error");

	serv_addr.sin_family = AF_INET; //семейство
	serv_addr.sin_port = htons(sPort); //перевести порт в сетевую форму

	// Преобразование адресов IPv4  из текста в двоичную форму
	if (inet_pton(AF_INET, sAddr.c_str(), &serv_addr.sin_addr) <= 0)
		throw checker_error("Invalid address/ Address not supported");

	// Подключение
	if (connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0)
		throw checker_error("Connection Failed");
	
	// Отправка на сервер сообщения с серийным номером и ключом
	send(sock, self_bufer, sizeof(self_bufer), 0);
	
	//Клиент принимает сообщение
	unsigned char answer;
	int valread = read(sock , &answer, sizeof(answer));
	
	if (answer)
		return true;
	else
		return false;
}
