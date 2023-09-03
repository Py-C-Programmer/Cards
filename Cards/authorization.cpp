#include <iostream> // Стандартна бібліотека вводу-виводу в консоль
#include <windows.h> // Стандартна біліотека з фукнціями взаємодії з Windows
#include <string>
#include <fstream>
#include <conio.h>

#define path "C:\\Users\\User\\Desktop\\USERS.txt"

using namespace std;

enum Keys {
	Q = 113, W = 119, E = 101, R = 114, T = 116, Y = 121, U = 117, I = 105, O = 111, P = 112,
	ZERO = 48, ONE = 49, TWO = 50, THREE = 51, FOUR = 52, FIVE = 53, SIX = 54, SEVEN = 55, EIGHT = 56, NINE = 57,
	UP_ARROW = 72, DOWN_ARROW = 80, RIGHT_ARROW = 77, LEFT_ARROW = 75,
	ENTER = 13, ESC = 27
};

void SetCursPos(short x, short y) //#include <Windows.h>
{
	COORD coord = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

bool findUser(ifstream& file, string username) {
	string user;
	while (!file.eof()) {
		getline(file, user);
		if (user != "") {
			int space = user.find("|");

			string name = "";
			for (int i = 0; i < space; i++) {
				name += user[i];
			}
			if (username == name) {
				return true;
			}
		}
	}
	return false;
}

string getPassword(ifstream& file, string username) {
	string user;
	while (!file.eof()) {
		getline(file, user);
		int space = user.find("|");

		string name = "";
		for (int i = 0; i < space; i++) {
			name += user[i];
		}

		if (name == username) {
			string pass = "";
			for (int i = space + 1; i < user.size(); i++) {
				pass += user[i];
			}
			return pass;
		}
	}
}

bool passwordCheck(string password) {
	if (password.size() >= 6) {
		int letters = 0;
		int numbers = 0;

		for (int i = 0; i < password.size(); i++) {
			if (isalpha(password[i]) != 0) {
				letters++;
			}
			else if (isdigit(password[i]) != 0) {
				numbers++;
			}
			else if (password[i] == '|') {
				return false;
			}
		}

		if (letters == 0 || numbers == 0) {
			return false;
		}
		else {
			return true;
		}
	}

	return false;
}

void SignUp() {
	bool STOP = false;

	ifstream file;
	file.open(path);

	cout << "Реєстрація:" << endl;

	string username;

	if (file.fail()) {
		cout << "Введіть логін >> ";
		getline(cin, username);
		file.close();
	}
	else {
		file.close();
		bool user_exists;
		do {
			ifstream file;
			file.open(path);

			cout << "Введіть логін >> ";
			getline(cin, username);

			user_exists = findUser(file, username);
			if (user_exists == true) {
				cout << "Назва аккаунту вже використовується! Натисніть ENTER, щоб повторити спробу реєстрації, або ESC, щоб вийти";
				int key = _getch();
				switch (key)
				{
				case ENTER:
					system("cls");
					break;
				case ESC:
					STOP = true;
					system("cls");
					break;
				default:
					break;
				}
			}

			if (STOP == true) {
				break;
			}

			file.close();
		} while (user_exists == true);
	}

	file.close();

	if (STOP == false) {
		string password;

		do {
			cout << "Введіть пароль >> ";
			getline(cin, password);

			if (passwordCheck(password) == false) {
				cout << "Пароль повинен складатися принаймні з 6 символів, містити хоча б 1 букву й 1 цифру та не мати в собі знак '|' чи літер кирилиці !  Натисніть ENTER, щоб ввести пароль ще раз, або ESC, щоб вийти";
				int key = _getch();
				switch (key)
				{
				case ENTER:
					system("cls");
					break;
				case ESC:
					STOP = true;
					break;
				default:
					break;
				}
			}

			if (STOP == true) {
				break;
			}
		} while (passwordCheck(password) == false);

		ofstream file;
		file.open(path, ios::app);

		file << username << "|" << password << "\n";

		file.close();

		cout << "Реєстрація користувача " << username << " проведена успішно!";
		int key = _getch();
		system("cls");
	}
}

void LogIn() {
	bool STOP = false;

	ifstream file;
	file.open(path);

	cout << "Вхід в аккаунт:" << endl;

	cout << "Введіть ЛОГІН >> ";
	string login;
	getline(cin, login);

	if (findUser(file, login) == true) {
		file.close();

		string password;
		string true_pass;
		do {
			ifstream file;
			file.open(path);

			cout << "Введіть пароль >> ";
			getline(cin, password);

			true_pass = getPassword(file, login);
			if (password != true_pass) {
				cout << "Пароль не правильний! Натисніть ENTER, щоб ввести пароль ще раз, або ESC, щоб вийти";

				int key = _getch();
				switch (key)
				{
				case ENTER:
					system("cls");
					break;
				case ESC:
					STOP = true;
					system("cls");
					break;
				default:
					break;
				}

				file.close();

				if (STOP == true) {
					break;
				}
			}
			else {
				cout << "Добрий день, " << login << "!";
				int key = _getch();
				system("cls");
			}

		} while (password != true_pass);
	}
	else {
		cout << "Користувача з логіном " << login << " не існує! Натисніть будь-яку клавішу, щоб повернутися до меню";
		int key = _getch();
		system("cls");
	}
}

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	setlocale(LC_ALL, "Ukrainian");

	srand(time(NULL));

	short todo;

	do {
		cout << "Меню:" << endl;
		cout << "1. Увійти в аккаунт" << endl;
		cout << "2. Зареєструватися" << endl;
		cout << "3. Вийти";

		int x = 0;
		int y = 0;
		SetCursPos(x, y);

		bool choosing = true;
		while (choosing == true) {
			int key = _getch();
			switch (key)
			{
			case UP_ARROW:
				if (y > 0) {
					y--;
					SetCursPos(x, y);
				}
				break;
			case DOWN_ARROW:
				y++;
				SetCursPos(x, y);
				break;
			case ENTER:
				if (y < 4 && y > 0) {
					todo = y;
				}
				else {
					todo = 0;
				}
				system("cls");
				choosing = false;
				break;
			default:
				break;
			}
		}


		switch (todo) {
		case 1:
			LogIn();
			break;
		case 2:
			SignUp();
			break;
		default:
			break;
		}

	} while (todo != 3);
}