#include <Server.h>

int main (int argc, char **argv)
{
	string dbPath = "db.txt";
	int sPort = 44214;
	struct sockaddr_in addr;

	int err, ls;

	// создаем дескриптор сокета
	if(-1 == (ls = socket( AF_INET, SOCK_STREAM, IPPROTO_TCP))) //создание сокета
		throw checker_error("create socket failed");

	int rc;
	setsockopt(ls, SOL_SOCKET, SO_REUSEADDR, &rc, sizeof(rc)); //функция манипуляци флагами
	memset( &addr , 0, sizeof(addr) );

	addr.sin_family = AF_INET; //семейство
	addr.sin_port = htons (sPort); //порт переведен из компьютерного в сетевой
	addr.sin_addr.s_addr = INADDR_ANY;

	// Привязать адрес к сокету
	if (err = bind(ls, (struct sockaddr*) &addr, sizeof(addr)) < 0) {
		close(ls);//закрыть сокет
		throw checker_error("bind failed");
	}
	
	// Ожидание запросов
	if (listen(ls, 25)<0) {
		close(ls);
		throw checker_error("listen failed");
	}

	while (true) {
		rc = accept(ls, NULL, NULL);// блокирует все остальные запросы 
		int pid = fork();
		if (pid < 0) 
			cerr << "fork abort" << endl;
		if (pid == 0) {
			close( ls );
			char *remote_bufer = new char[256]; //буфер для записи серийного номера и ключа, отправленного сервером
			
			//принять Id, пароль
			int rv = recv(rc,remote_bufer,256,0);
			if (rv < 0)
				cerr << "recv failed" << endl;
				
			string str = string(remote_bufer); //перевести отправленные номер и ключ в строку 
			DataBase x(dbPath, str); //параметры: адрес БД и строка с введённым номером и ключом
			bool result = x.check(); //проверка лицензии
			
			unsigned char res_buf = result ? 1 : 0;
			rv = send(rc,&res_buf,sizeof(res_buf),0); //отправить клиенту результат проверки
			if (rv < 0)
				cerr << "send failed" << endl;
				
			close(rc);
			return -1;
		} else {
			close(rc);
		}
	}

	return 0;
}
