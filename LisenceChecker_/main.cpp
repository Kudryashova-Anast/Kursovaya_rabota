/** 
* @file main.cpp
* @brief Главный модуль программы LicenseChecker
*/
#include <LicenseChecker.h>
using namespace std;

int main (int argc, char **argv)
{
	string num, key;
	int reload = 1;
	
	do{
		cout << "Введите серийный номер" << endl;
		cin >> num;
		cout << "Введите лицензионный ключ" << endl;
		cin >> key;
		
		LicenseChecker product(num, key);
		if(product.check()){
			cout << "Продукт активирован!" << endl;
			break;
		}else{
			cout << "Не верный ключ активации!" << endl;
			cout << "Чтобы ввести ключ повтороно введите 1, выйти 0" << endl;
			cin >> reload;
		}
		
	}while(reload == 1);
	
	return 0;
}
