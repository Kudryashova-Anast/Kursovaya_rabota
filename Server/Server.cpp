#include <Server.h>

DataBase::DataBase(string DATABASE_PATH, const string IDPASS){
	database_path = DATABASE_PATH;
	idpass = IDPASS;
}
bool DataBase::check() const
{
	ifstream file;
	
	file.open(database_path);//открыли файл и извлекли адресо БД функцией класса ServerConfig 
	if (!file.good()) {
		cerr << "Ошибка открытия файла Data" << endl;
		return false;
	}
	
	string ch;
	while (true) {
		file >> ch; //Читать строку из БД
		if (ch == idpass) { //Сравнивать пароль и логин с этой строкой
			return true;
		}
		if ( file.eof()) {
			return false;
		}
	}
}
