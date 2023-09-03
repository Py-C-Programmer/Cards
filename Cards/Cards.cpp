#include <iostream> 
#include <windows.h> 
#include <iomanip> 
#include <string>
#include <fstream>
#include <conio.h>

#define path_users "C:\\Users\\User\\Desktop\\USERS.txt"

using namespace std;

enum ConsoleColor {
	// Standard text colors
	GRAY = 8, BLUE, GREEN,
	TEAL, RED, PINK,
	YELLOW, WHITE,
	// Faded text colors
	BLACK = 0, BLUE_FADE, GREEN_FADE,
	TEAL_FADE, RED_FADE, PINK_FADE,
	YELLOW_FADE, WHITE_FADE,
	NONE
};

enum Keys {
	Q = 113, W = 119, E = 101, R = 114, T = 116, Y = 121, U = 117, I = 105, O = 111, P = 112,
	ZERO = 48, ONE = 49, TWO = 50, THREE = 51, FOUR = 52, FIVE = 53, SIX = 54, SEVEN = 55, EIGHT = 56, NINE = 57,
	UP_ARROW = 72, DOWN_ARROW = 80, RIGHT_ARROW = 77, LEFT_ARROW = 75,
	ENTER = 13, ESC = 27
};

struct Card {
	short num;
	string kind;
};

// Set console colors
void SetColor(ConsoleColor text, ConsoleColor background = BLACK)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (short)text | ((short)background << 4));
}

void SetCursPos(short x, short y) //#include <Windows.h>
{
	COORD coord = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void append(Card*& arr, short& size, Card card) {
	Card* copy = new Card[size + 1];
	for (int i = 0; i < size; i++) {
		copy[i] = arr[i];
	}
	copy[size] = card;
	delete[] arr;
	size++;
	arr = copy;
}

void append(short*& arr, short& size, short card) {
	short* copy = new short[size + 1];
	for (int i = 0; i < size; i++) {
		copy[i] = arr[i];
	}
	copy[size] = card;
	delete[] arr;
	size++;
	arr = copy;
}

void append(string*& arr, int& size, string card) {
	string* copy = new string[size + 1];
	for (int i = 0; i < size; i++) {
		copy[i] = arr[i];
	}
	copy[size] = card;
	delete[] arr;
	size++;
	arr = copy;
}

void remove(Card*& arr, short& size, int ind) {
	Card* copy = new Card[size - 1];
	int index = 0;
	for (int i = 0; i < size; i++) {
		if (i != ind) {
			copy[i - index] = arr[i];
		}
		else {
			index++;
		}
	}

	delete[] arr;
	size--;
	arr = copy;
}

bool card_present(Card* CARDS, short SIZE, Card card) {
	for (int i = 0; i < SIZE; i++) {
		if (CARDS[i].num == card.num && CARDS[i].kind == card.kind) {
			return true;
		}
	}
	return false;
}

bool add_able(Card* TABLE, short TABLE_SIZE, short num) {
	for (int i = 0; i < TABLE_SIZE; i++) {
		if (TABLE[i].num == num) {
			return true;
		}
	}
	return false;
}

char first_player(Card* US_CARDS, short US_SIZE, Card* PC_CARDS, short PC_SIZE, Card cozar) {
	short cozar_count_pc = 0;
	short cozar_count_us = 0;
	short* cozars_pc = new short[cozar_count_pc];
	short* cozars_us = new short[cozar_count_us];

	for (int i = 0; i < PC_SIZE; i++) {
		if (PC_CARDS[i].kind == cozar.kind) {
			append(cozars_pc, cozar_count_pc, PC_CARDS[i].num);
		}
	}

	short min_cozar_pc;
	if (cozar_count_pc != 0) {
		min_cozar_pc = cozars_pc[0];
		for (int i = 0; i < cozar_count_pc; i++) {
			if (cozars_pc[i] < min_cozar_pc) {
				min_cozar_pc = cozars_pc[i];
			}
		}
	}
	else {
		min_cozar_pc = 0;
	}


	for (int i = 0; i < US_SIZE; i++) {
		if (US_CARDS[i].kind == cozar.kind) {
			append(cozars_us, cozar_count_us, US_CARDS[i].num);
		}
	}

	short min_cozar_us;
	if (cozar_count_us != 0) {
		min_cozar_us = cozars_us[0];
		for (int i = 0; i < cozar_count_us; i++) {
			if (cozars_us[i] < min_cozar_us) {
				min_cozar_us = cozars_us[i];
			}
		}
	}
	else {
		min_cozar_us = 0;
	}

	delete[] cozars_pc;
	delete[] cozars_us;

	if (min_cozar_pc == 0 && min_cozar_us != 0) {
		return 'u';
	}
	else if (min_cozar_pc != 0 && min_cozar_us == 0) {
		return 'p';
	}
	else if (min_cozar_pc == 0 && min_cozar_us == 0) {
		if (rand() % 2 == 1) {
			return 'u';
		}
		else {
			return 'p';
		}
	}
	else if (min_cozar_pc != 0 && min_cozar_us != 0) {
		if (min_cozar_pc < min_cozar_us) {
			return 'p';
		}
		else {
			return 'u';
		}
	}
}

void Read(ifstream& file, string username, string*& USERS, int& USERS_COUNT) {
	file.open(path_users);
	string user;

	while (!file.eof()) {
		getline(file, user);
		append(USERS, USERS_COUNT, user);
	}
}

void Renew_balance(string*& USERS, int& USERS_COUNT, string login, int profit) {
	for (int i = 0; i < USERS_COUNT; i++) {
		if (USERS[i].find(login) != string::npos) {
			int space1 = USERS[i].find("|");
			int space2 = USERS[i].find("|", space1 + 1);

			string name = "";
			for (int j = 0; j <= space2; j++) {
				name += USERS[i][j];
			}

			string money = "";
			for (int j = space2 + 1; j < USERS[i].size(); j++) {
				money += USERS[i][j];
			}
			
			money = to_string(stoi(money) + profit);

			USERS[i] = name + money;
			break;
		}
	}
}

void Rewrite(ofstream& file, string* USERS, int USERS_COUNT) {
	file.open(path_users);

	for (int i = 0; i < USERS_COUNT; i++) {
		file << USERS[i] << '\n';
	}

	file.close();
}

void ShowCard(char Kind, short SIZE, short PC_SIZE, Card cozar) {
	if (Kind == 'E') {
		SetColor(WHITE, BLACK);     //ENTIRE set of cards
		SetCursPos(0, 7);
		cout << "Колода карт:";
		SetColor(BLACK, WHITE);
		SetCursPos(0, 8);
		cout << "      ";
		SetCursPos(0, 9);
		cout << "      ";
		SetCursPos(0, 10);
		cout << "  " << SIZE;
		if (SIZE > 9) {
			cout << "  ";
		}
		else {
			cout << "   ";
		}
		SetCursPos(0, 11);
		cout << "      ";
		SetCursPos(0, 12);
		cout << "      ";
	}
	else if (Kind == 'P') {
		SetColor(WHITE, BLACK);     //PC_CARDS
		SetCursPos(65, 0);
		cout << "Карти комп'ютера:";
		SetColor(BLACK, WHITE);
		SetCursPos(70, 1);
		cout << "      ";
		SetCursPos(70, 2);
		cout << "      ";
		SetCursPos(70, 3);
		cout << "  " << PC_SIZE;
		if (PC_SIZE > 9) {
			cout << "  ";
		}
		else {
			cout << "   ";
		}
		SetCursPos(70, 4);
		cout << "      ";
		SetCursPos(70, 5);
		cout << "      ";
	}
	else if (Kind == 'C') {
		SetColor(WHITE, BLACK);		//Cozar
		SetCursPos(145, 7);
		cout << "Козир:";
		SetCursPos(145, 8);
		//
		if (cozar.kind == "Chirva" || cozar.kind == "Buba") {
			SetColor(RED, WHITE);
		}
		else if (cozar.kind == "Cross" || cozar.kind == "Pika") {
			SetColor(BLACK, WHITE);
		}
		//
		if (cozar.num == 11) {
			cout << "J";
		}
		else if (cozar.num == 12) {
			cout << "Q";
		}
		else if (cozar.num == 13) {
			cout << "K";
		}
		else if (cozar.num == 14) {
			cout << "T";
		}
		else {
			cout << cozar.num;
		}
		if (cozar.num != 10) {
			cout << "     ";
		}
		else {
			cout << "    ";
		}
		SetCursPos(145, 9);
		cout << "      ";
		SetCursPos(145, 10);
		cout << cozar.kind;
		if (cozar.kind.size() == 4) {
			cout << "  ";
		}
		else if (cozar.kind.size() == 5) {
			cout << " ";
		}
		SetCursPos(145, 11);
		cout << "      ";
		SetCursPos(145, 12);
		if (cozar.num != 10) {
			cout << "     ";
		}
		else {
			cout << "    ";
		}
		if (cozar.num == 11) {
			cout << "J";
		}
		else if (cozar.num == 12) {
			cout << "Q";
		}
		else if (cozar.num == 13) {
			cout << "K";
		}
		else if (cozar.num == 14) {
			cout << "T";
		}
		else {
			cout << cozar.num;
		}
	}
}

void ShowCards(Card* CARDS, short SIZE, int y, int delay) {
	int x = 30;
	y++;
	for (int card = 0; card < SIZE; card++) {
		if (x < 125) {
			SetCursPos(x + 2, y - 1);
			if ((card + 1) % 2 == 1) {
				SetColor(WHITE, RED);
			}
			else {
				SetColor(WHITE, BLACK);
			}
			cout << card + 1;

			SetCursPos(x, y);
			//
			if (CARDS[card].kind == "Chirva" || CARDS[card].kind == "Buba") {
				SetColor(RED, WHITE);
			}
			else if (CARDS[card].kind == "Cross" || CARDS[card].kind == "Pika") {
				SetColor(BLACK, WHITE);
			}
			//
			if (CARDS[card].num == 11) {
				cout << "J";
			}
			else if (CARDS[card].num == 12) {
				cout << "Q";
			}
			else if (CARDS[card].num == 13) {
				cout << "K";
			}
			else if (CARDS[card].num == 14) {
				cout << "T";
			}
			else {
				cout << CARDS[card].num;
			}
			if (CARDS[card].num != 10) {
				cout << "     ";
			}
			else {
				cout << "    ";
			}
			y++;
			SetCursPos(x, y);
			cout << "      ";
			y++;
			SetCursPos(x, y);
			cout << CARDS[card].kind;
			if (CARDS[card].kind.size() == 4) {
				cout << "  ";
			}
			else if (CARDS[card].kind.size() == 5) {
				cout << " ";
			}
			y++;
			SetCursPos(x, y);
			cout << "      ";
			y++;
			SetCursPos(x, y);
			if (CARDS[card].num != 10) {
				cout << "     ";
			}
			else {
				cout << "    ";
			}
			if (CARDS[card].num == 11) {
				cout << "J";
			}
			else if (CARDS[card].num == 12) {
				cout << "Q";
			}
			else if (CARDS[card].num == 13) {
				cout << "K";
			}
			else if (CARDS[card].num == 14) {
				cout << "T";
			}
			else {
				cout << CARDS[card].num;
			}
			y -= 4;
			x += 8;
			if (card == SIZE - 2) {
				Sleep(delay);
			}
		}
		else {
			x = 30;
			y += 7;

			SetCursPos(x + 2, y - 1);
			if ((card + 1) % 2 == 1) {
				SetColor(WHITE, RED);
			}
			else {
				SetColor(WHITE, BLACK);
			}
			cout << card + 1;

			SetCursPos(x, y);
			//
			if (CARDS[card].kind == "Chirva" || CARDS[card].kind == "Buba") {
				SetColor(RED, WHITE);
			}
			else if (CARDS[card].kind == "Cross" || CARDS[card].kind == "Pika") {
				SetColor(BLACK, WHITE);
			}
			//
			if (CARDS[card].num == 11) {
				cout << "J";
			}
			else if (CARDS[card].num == 12) {
				cout << "Q";
			}
			else if (CARDS[card].num == 13) {
				cout << "K";
			}
			else if (CARDS[card].num == 14) {
				cout << "T";
			}
			else {
				cout << CARDS[card].num;
			}
			if (CARDS[card].num != 10) {
				cout << "     ";
			}
			else {
				cout << "    ";
			}
			y++;
			SetCursPos(x, y);
			cout << "      ";
			y++;
			SetCursPos(x, y);
			cout << CARDS[card].kind;
			if (CARDS[card].kind.size() == 4) {
				cout << "  ";
			}
			else if (CARDS[card].kind.size() == 5) {
				cout << " ";
			}
			y++;
			SetCursPos(x, y);
			cout << "      ";
			y++;
			SetCursPos(x, y);
			if (CARDS[card].num != 10) {
				cout << "     ";
			}
			else {
				cout << "    ";
			}
			if (CARDS[card].num == 11) {
				cout << "J";
			}
			else if (CARDS[card].num == 12) {
				cout << "Q";
			}
			else if (CARDS[card].num == 13) {
				cout << "K";
			}
			else if (CARDS[card].num == 14) {
				cout << "T";
			}
			else {
				cout << CARDS[card].num;
			}
			y -= 4;
			x += 8;
			if (card == SIZE - 2) {
				Sleep(delay);
			}
		}
	}
	SetColor(WHITE, BLACK);
}

bool AttackUS(Card*& TABLE, short& TABLE_SIZE, Card*& US_CARDS, short& US_SIZE, Card* PC_CARDS, short PC_SIZE, short SIZE, Card cozar, bool COZAR_AVAILABLE) {
	Card attack;

	//cin.ignore(32767, '\n');
	while (true) {
		//Attack
		system("cls");
		SetColor(WHITE, GREEN);
		cout << "ВАШ ХІД";

		if (SIZE != 0) {
			ShowCard('E', SIZE, PC_SIZE, cozar);
		}
		if (COZAR_AVAILABLE == true) {
			ShowCard('C', SIZE, PC_SIZE, cozar);
		}
		if (PC_SIZE != 0) {
			ShowCard('P', SIZE, PC_SIZE, cozar);
		}

		if (TABLE_SIZE != 0) {
			ShowCards(TABLE, TABLE_SIZE, 9, 1000);
		}

		SetCursPos(0, 25);
		SetColor(WHITE, BLACK);
		cout << "Ваші карти:";
		ShowCards(US_CARDS, US_SIZE, 26, 0);
		cout << endl;

		cout << "\nВведіть номер обраної Вами карти (якщо бажаєте пропустити хід, введіть 0) >> ";
		short num;
		cin >> num;

		if (num == 0) {
			if (TABLE_SIZE != 0) {
				return false;
			}
		}
		else if (num > 0 && num <= US_SIZE) {
			attack.kind = US_CARDS[num - 1].kind;
			attack.num = US_CARDS[num - 1].num;

			if (TABLE_SIZE == 0) {
				if (card_present(US_CARDS, US_SIZE, attack) == true) {
					append(TABLE, TABLE_SIZE, attack);
					remove(US_CARDS, US_SIZE, num - 1);
					return true;
				}
			}
			else {
				if (card_present(US_CARDS, US_SIZE, attack) == true && add_able(TABLE, TABLE_SIZE, attack.num) == true) {
					append(TABLE, TABLE_SIZE, attack);
					remove(US_CARDS, US_SIZE, num - 1);
					return true;
				}
			}
		}

	}
}

bool DefendPC(Card*& TABLE, short& TABLE_SIZE, Card*& PC_CARDS, short& PC_SIZE, Card cozar) {
	Card attack;
	attack.kind = TABLE[TABLE_SIZE - 1].kind;
	attack.num = TABLE[TABLE_SIZE - 1].num;

	short defend_size = 0;
	Card* defends = new Card[defend_size];
	for (int i = 0; i < PC_SIZE; i++) {
		if ((PC_CARDS[i].kind == attack.kind && attack.num < PC_CARDS[i].num) || (PC_CARDS[i].kind == cozar.kind && attack.kind != cozar.kind)) {
			append(defends, defend_size, PC_CARDS[i]);
		}
	}

	if (defend_size != 0) {
		Card defend;
		defend = defends[0];
		for (int d = 0; d < defend_size; d++) {
			if (defends[d].num < defend.num) {
				defend = defends[d];
			}
		}
		append(TABLE, TABLE_SIZE, defend);
		for (int p = 0; p < PC_SIZE; p++) {
			if (PC_CARDS[p].kind == defend.kind && PC_CARDS[p].num == defend.num) {
				remove(PC_CARDS, PC_SIZE, p);
				break;
			}
		}

		delete[] defends;
		return true;
	}
	else {
		delete[] defends;
		return false;
	}
}

bool AttackPC(Card*& TABLE, short& TABLE_SIZE, Card*& PC_CARDS, short& PC_SIZE, Card cozar) {
	Card attack;

	//Attack
	short cards_count = 0;
	Card* cards_without_cozars = new Card[cards_count];

	if (TABLE_SIZE == 0) {
		for (int i = 0; i < PC_SIZE; i++) {
			if (PC_CARDS[i].kind != cozar.kind) {
				append(cards_without_cozars, cards_count, PC_CARDS[i]);
			}
		}

		if (cards_count != 0) {
			attack = cards_without_cozars[0];
			for (int j = 0; j < cards_count; j++) {
				if (cards_without_cozars[j].num < attack.num) {
					attack = cards_without_cozars[j];
				}
			}
		}
		else {
			attack = PC_CARDS[0];
			for (int j = 0; j < PC_SIZE; j++) {
				if (PC_CARDS[j].num < attack.num) {
					attack = PC_CARDS[j];
				}
			}
		}

		append(TABLE, TABLE_SIZE, attack);
		for (int i = 0; i < PC_SIZE; i++) {
			if (PC_CARDS[i].kind == attack.kind && PC_CARDS[i].num == attack.num) {
				remove(PC_CARDS, PC_SIZE, i);
				break;
			}
		}
	}
	else {
		for (int i = 0; i < PC_SIZE; i++) {
			if (PC_CARDS[i].kind != cozar.kind && add_able(TABLE, TABLE_SIZE, PC_CARDS[i].num) == true) {
				append(cards_without_cozars, cards_count, PC_CARDS[i]);
			}
		}

		if (cards_count != 0) {
			attack = cards_without_cozars[0];
			for (int j = 0; j < cards_count; j++) {
				if (cards_without_cozars[j].num < attack.num) {
					attack = cards_without_cozars[j];
				}
			}

		append(TABLE, TABLE_SIZE, attack);
		for (int i = 0; i < PC_SIZE; i++) {
			if (PC_CARDS[i].kind == attack.kind && PC_CARDS[i].num == attack.num) {
				remove(PC_CARDS, PC_SIZE, i);
				break;
			}
		}
		}
		else {
			return false;
		}
	}

	delete[] cards_without_cozars;

	return true;
}

bool DefendUS(Card*& TABLE, short& TABLE_SIZE, Card*& US_CARDS, short& US_SIZE, Card* PC_CARDS, short PC_SIZE, short SIZE, Card cozar, bool COZAR_AVAILABLE) {
	Card defend;

	while (true) {
		//Defending
		system("cls");
		SetColor(WHITE, RED_FADE);
		cout << "ЗАХИЩАЙТЕСЯ";

		if (SIZE != 0) {
			ShowCard('E', SIZE, PC_SIZE, cozar);
		}
		if (COZAR_AVAILABLE == true) {
			ShowCard('C', SIZE, PC_SIZE, cozar);
		}
		if (PC_SIZE != 0) {
			ShowCard('P', SIZE, PC_SIZE, cozar);
		}

		if (TABLE_SIZE != 0) {
			ShowCards(TABLE, TABLE_SIZE, 9, 1000);
		}

		SetCursPos(0, 25);
		SetColor(WHITE, BLACK);
		cout << "Ваші карти:";
		ShowCards(US_CARDS, US_SIZE, 26, 0);
		cout << endl;

		cout << "\nВведіть номер обраної Вами карти (якщо хочете взяти карти, введіть 0) >> ";
		short num;
		cin >> num;

		if (num == 0) {
			return false;
		}
		else if (num > 0 && num <= US_SIZE) {
			if ((US_CARDS[num - 1].kind == TABLE[TABLE_SIZE - 1].kind && TABLE[TABLE_SIZE - 1].num < US_CARDS[num - 1].num) || (TABLE[TABLE_SIZE - 1].kind != cozar.kind && US_CARDS[num - 1].kind == cozar.kind)) {
				defend.kind = US_CARDS[num - 1].kind;
				defend.num = US_CARDS[num - 1].num;

				append(TABLE, TABLE_SIZE, defend);
				remove(US_CARDS, US_SIZE, num - 1);

				return true;
			}
		}
	}
}

void initGame(short& choise) {
	//Menu
	system("cls");
	cout << "Гра 'Дурень':" << endl;
	cout << "1. Колода на 24 карти" << endl;
	cout << "2. Колода на 36 карт" << endl;
	cout << "3. Колода на 52 карти" << endl;
	cout << "4. Вийти";

	int y = 0;
	SetCursPos(0, 0);
	bool choosing = true;
	while (choosing == true) {
		int key = _getch();
		switch (key)
		{
		case UP_ARROW:
			if (y > 0) {
				y--;
				SetCursPos(0, y);
			}
			break;
		case DOWN_ARROW:
			y++;
			SetCursPos(0, y);
			break;
		case ENTER:
			if (y == 1) {
				choise = 24;
			}
			else if (y == 2) {
				choise = 36;
			}
			else if (y == 3) {
				choise = 52;
			}
			else if (y == 4) {
				exit(3);
			}
			system("cls");
			choosing = false;
			break;
		default:
			break;
		}
	}
}

void GAME(string login) {
	//Initializating...
	short choice = 0;
	initGame(choice);

	short cards_nums[] = {2,3,4,5,6,7,8,9,10,11,12,13,14};
	string cards_kinds[] = { "Pika","Buba","Cross","Chirva" };

	//The entire cadrs set
	short SIZE = choice;
	Card* CARDS = new Card[SIZE];

	//Filling the set with cards
	Card new_card;
	short ind = 0;
	short n;
	if (choice == 24) {
		n = 7;
	}
	else if (choice == 36) {
		n = 4;
	}
	else {
		n = 0;
	}
	for (int kind = 0; kind < 4; kind++) {
		for (int number = 12; number >= n; number--) {
			new_card.num = cards_nums[number];
			new_card.kind = cards_kinds[kind];
			CARDS[ind] = new_card;
			ind++;
		}
	}

	//Choosing the cozar
	int shuffled_card = rand() % SIZE;
	Card cozar = CARDS[shuffled_card];
	remove(CARDS, SIZE, shuffled_card);
	bool COZAR_AVAILABLE = true;

	//Computer's cards
	short PC_SIZE = 6;
	Card* PC_CARDS = new Card[PC_SIZE];

	for (int i = 0; i < PC_SIZE; i++) {
		int shuffled_card = rand() % SIZE;
		PC_CARDS[i] = CARDS[shuffled_card];
		remove(CARDS, SIZE, shuffled_card);
	}

	//User's cards
	short US_SIZE = 6;
	Card* US_CARDS = new Card[US_SIZE];

	for (int i = 0; i < US_SIZE; i++) {
		int shuffled_card = rand() % SIZE;
		US_CARDS[i] = CARDS[shuffled_card];
		remove(CARDS, SIZE, shuffled_card);
	}
	
	//Playing...
	short TABLE_SIZE = 0;
	Card* TABLE = new Card[TABLE_SIZE];

	bool STOP = false;
	if (first_player(US_CARDS, US_SIZE, PC_CARDS, PC_SIZE, cozar) == 'u') {
		while (STOP != true) {
			for (int i = 1; i <= 6; i++) {
				if (STOP != true && US_SIZE != 0) {
					if (AttackUS(TABLE, TABLE_SIZE, US_CARDS, US_SIZE, PC_CARDS, PC_SIZE, SIZE, cozar, COZAR_AVAILABLE) == true) {
						if (DefendPC(TABLE, TABLE_SIZE, PC_CARDS, PC_SIZE, cozar) == false) {
							SetColor(WHITE, BLUE);
							cout << "\nКомп'ютер:";
							SetColor(WHITE, BLACK);
							cout << " забираю";
							Sleep(1500);
							//
							if (PC_SIZE != 0) {
								short through_up;
								for (int t = 1; t <= 6 - i; t++) {
									cout << "\n\nВведіть 1, якщо бажаєте підкинути карту, якщо ні - будь-яке інше число >> ";
									cin >> through_up;
									if (through_up == 1) {
										if (AttackUS(TABLE, TABLE_SIZE, US_CARDS, US_SIZE, PC_CARDS, PC_SIZE, SIZE, cozar, COZAR_AVAILABLE) == false) {
											t = 7;
										}
									}
									else {
										t = 7;
									}
								}
							}
							//
							for (int j = 0; j < TABLE_SIZE; j++) {
								append(PC_CARDS, PC_SIZE, TABLE[j]);
							}
							for (int j = TABLE_SIZE - 1; j > -1; j--) {
								remove(TABLE, TABLE_SIZE, j);
							}
							//Dealing Cards
							while (US_SIZE != 6) {
								if (SIZE != 0) {
									int shuffled_card = rand() % SIZE;
									append(US_CARDS, US_SIZE, CARDS[shuffled_card]);
									remove(CARDS, SIZE, shuffled_card);
								}
								else {
									if (COZAR_AVAILABLE == true) {
										append(US_CARDS, US_SIZE, cozar);
										COZAR_AVAILABLE = false;
									}
									if (US_SIZE == 0) {
										SetCursPos(0, 0);
										SetColor(WHITE, YELLOW_FADE);
										cout << "Ви перемогли!\t+5 $";
										SetColor(WHITE, BLACK);
										ifstream file;
										int USERS_COUNT = 0;
										string* USERS = new string[USERS_COUNT];
										Read(file, login, USERS, USERS_COUNT);
										file.close();
										Renew_balance(USERS, USERS_COUNT, login, 5);
										ofstream file1;
										Rewrite(file1, USERS, USERS_COUNT);
										file1.close();
										int key = _getch();
										STOP = true;
										i = 7;
									}
									break;
								}
							}
							if (US_SIZE == 0 && SIZE == 0) {
								SetCursPos(0, 0);
								SetColor(WHITE, YELLOW_FADE);
								cout << "Ви перемогли!\t+5 $";
								SetColor(WHITE, BLACK);
								ifstream file;
								int USERS_COUNT = 0;
								string* USERS = new string[USERS_COUNT];
								Read(file, login, USERS, USERS_COUNT);
								file.close();
								Renew_balance(USERS, USERS_COUNT, login, 5);
								ofstream file1;
								Rewrite(file1, USERS, USERS_COUNT);
								file1.close();
								int key = _getch();
								STOP = true;
							}
							if (STOP != true) {
								i = 1;
							}
							else {
								i = 7;
							}
						}
						else {
							SetColor(WHITE, BLUE);
							cout << "\nКомп'ютер:";
							SetColor(WHITE, BLACK);
							cout << " відбив";
							Sleep(1500);
						}
					}
					else {
						i = 7;
					}
				}
			}

			if (STOP != true) {
				//Dealing cards
				while (US_SIZE != 6) {
					if (SIZE != 0) {
						int shuffled_card = rand() % SIZE;
						append(US_CARDS, US_SIZE, CARDS[shuffled_card]);
						remove(CARDS, SIZE, shuffled_card);
					}
					else {
						if (COZAR_AVAILABLE == true) {
							append(US_CARDS, US_SIZE, cozar);
							COZAR_AVAILABLE = false;
						}
						if (US_SIZE == 0) {
							SetCursPos(0, 0);
							SetColor(WHITE, YELLOW_FADE);
							cout << "Ви перемогли!\t+5 $";
							SetColor(WHITE, BLACK);
							ifstream file;
							int USERS_COUNT = 0;
							string* USERS = new string[USERS_COUNT];
							Read(file, login, USERS, USERS_COUNT);
							file.close();
							Renew_balance(USERS, USERS_COUNT, login, 5);
							ofstream file1;
							Rewrite(file1, USERS, USERS_COUNT);
							file1.close();
							int key = _getch();
							STOP = true;
						}
						break;
					}
				}

				while (PC_SIZE != 6) {
					if (SIZE != 0) {
						int shuffled_card = rand() % SIZE;
						append(PC_CARDS, PC_SIZE, CARDS[shuffled_card]);
						remove(CARDS, SIZE, shuffled_card);
					}
					else {
						if (COZAR_AVAILABLE == true) {
							append(PC_CARDS, PC_SIZE, cozar);
							COZAR_AVAILABLE = false;
						}
						if (PC_SIZE == 0) {
							SetCursPos(0, 0);
							SetColor(WHITE, RED);
							cout << "Комп'ютер переміг!\t-5 $";
							SetColor(WHITE, BLACK);
							ifstream file;
							int USERS_COUNT = 0;
							string* USERS = new string[USERS_COUNT];
							Read(file, login, USERS, USERS_COUNT);
							file.close();
							Renew_balance(USERS, USERS_COUNT, login, -5);
							ofstream file1;
							Rewrite(file1, USERS, USERS_COUNT);
							file1.close();
							int key = _getch();
							STOP = true;
						}
						break;
					}
				}
				//

				//Cleaning Table
				for (int j = TABLE_SIZE - 1; j > -1; j--) {
					remove(TABLE, TABLE_SIZE, j);
				}
			}

			for (int i = 1; i <= 6; i++) {
				if (STOP != true && PC_SIZE != 0) {
					if (AttackPC(TABLE, TABLE_SIZE, PC_CARDS, PC_SIZE, cozar) == true) {
						if (DefendUS(TABLE, TABLE_SIZE, US_CARDS, US_SIZE, PC_CARDS, PC_SIZE, SIZE, cozar, COZAR_AVAILABLE) == false) {
							//
							if (US_SIZE != 0) {
								for (int t = 1; t <= 6 - i; t++) {
									if (AttackPC(TABLE, TABLE_SIZE, PC_CARDS, PC_SIZE, cozar) == false) {
										t = 7;
									}
								}
							}
							//
							for (int j = 0; j < TABLE_SIZE; j++) {
								append(US_CARDS, US_SIZE, TABLE[j]);
							}
							for (int j = TABLE_SIZE - 1; j > -1; j--) {
								remove(TABLE, TABLE_SIZE, j);
							}
							//Dealing Cards
							while (PC_SIZE != 6) {
								if (SIZE != 0) {
									int shuffled_card = rand() % SIZE;
									append(PC_CARDS, PC_SIZE, CARDS[shuffled_card]);
									remove(CARDS, SIZE, shuffled_card);
								}
								else {
									if (COZAR_AVAILABLE == true) {
										append(PC_CARDS, PC_SIZE, cozar);
										COZAR_AVAILABLE = false;
									}
									if (PC_SIZE == 0) {
										SetCursPos(0, 0);
										SetColor(WHITE, RED);
										cout << "Комп'ютер переміг!\t-5 $";
										SetColor(WHITE, BLACK);
										ifstream file;
										int USERS_COUNT = 0;
										string* USERS = new string[USERS_COUNT];
										Read(file, login, USERS, USERS_COUNT);
										file.close();
										Renew_balance(USERS, USERS_COUNT, login, -5);
										ofstream file1;
										Rewrite(file1, USERS, USERS_COUNT);
										file1.close();
										int key = _getch();
										STOP = true;
										i = 7;
									}
									break;
								}
							}
							if (PC_SIZE == 0 && SIZE == 0) {
								SetCursPos(0, 0);
								SetColor(WHITE, RED);
								cout << "Комп'ютер переміг!\t-5 $";
								SetColor(WHITE, BLACK);
								ifstream file;
								int USERS_COUNT = 0;
								string* USERS = new string[USERS_COUNT];
								Read(file, login, USERS, USERS_COUNT);
								file.close();
								Renew_balance(USERS, USERS_COUNT, login, -5);
								ofstream file1;
								Rewrite(file1, USERS, USERS_COUNT);
								file1.close();
								int key = _getch();
								STOP = true;
							}
							if (STOP != true) {
								i = 1;
							}
							else {
								i = 7;
							}
							Sleep(1000);
						}
						else {
							Sleep(1000);
						}
					}
					else {
						i = 7;
					}
				}
			}

			if (STOP != true) {
				//Dealing cards
				while (PC_SIZE != 6) {
					if (SIZE != 0) {
						int shuffled_card = rand() % SIZE;
						append(PC_CARDS, PC_SIZE, CARDS[shuffled_card]);
						remove(CARDS, SIZE, shuffled_card);
					}
					else {
						if (COZAR_AVAILABLE == true) {
							append(PC_CARDS, PC_SIZE, cozar);
							COZAR_AVAILABLE = false;
						}
						if (PC_SIZE == 0) {
							SetCursPos(0, 0);
							SetColor(WHITE, RED);
							cout << "Комп'ютер переміг!\t-5 $";
							SetColor(WHITE, BLACK);
							ifstream file;
							int USERS_COUNT = 0;
							string* USERS = new string[USERS_COUNT];
							Read(file, login, USERS, USERS_COUNT);
							file.close();
							Renew_balance(USERS, USERS_COUNT, login, -5);
							ofstream file1;
							Rewrite(file1, USERS, USERS_COUNT);
							file1.close();
							int key = _getch();
							STOP = true;
						}
						break;
					}
				}

				while (US_SIZE != 6) {
					if (SIZE != 0) {
						int shuffled_card = rand() % SIZE;
						append(US_CARDS, US_SIZE, CARDS[shuffled_card]);
						remove(CARDS, SIZE, shuffled_card);
					}
					else {
						if (COZAR_AVAILABLE == true) {
							append(US_CARDS, US_SIZE, cozar);
							COZAR_AVAILABLE = false;
						}
						if (US_SIZE == 0) {
							SetCursPos(0, 0);
							SetColor(WHITE, YELLOW_FADE);
							cout << "Ви перемогли!\t+5 $";
							SetColor(WHITE, BLACK);
							ifstream file;
							int USERS_COUNT = 0;
							string* USERS = new string[USERS_COUNT];
							Read(file, login, USERS, USERS_COUNT);
							file.close();
							Renew_balance(USERS, USERS_COUNT, login, 5);
							ofstream file1;
							Rewrite(file1, USERS, USERS_COUNT);
							file1.close();
							int key = _getch();
							STOP = true;
						}
						break;
					}
				}
				//

				//Cleaning Table
				for (int j = TABLE_SIZE - 1; j > -1; j--) {
					remove(TABLE, TABLE_SIZE, j);
				}
			}
		}
	}
	else {
		while (STOP != true) {
			for (int i = 1; i <= 6; i++) {
				if (STOP != true && PC_SIZE != 0) {
					if (AttackPC(TABLE, TABLE_SIZE, PC_CARDS, PC_SIZE, cozar) == true) {
						if (DefendUS(TABLE, TABLE_SIZE, US_CARDS, US_SIZE, PC_CARDS, PC_SIZE, SIZE, cozar, COZAR_AVAILABLE) == false) {
							//
							if (US_SIZE != 0) {
								for (int t = 1; t <= 6 - i; t++) {
									if (AttackPC(TABLE, TABLE_SIZE, PC_CARDS, PC_SIZE, cozar) == false) {
										t = 7;
									}
								}
							}
							//
							for (int j = 0; j < TABLE_SIZE; j++) {
								append(US_CARDS, US_SIZE, TABLE[j]);
							}
							for (int j = TABLE_SIZE - 1; j > -1; j--) {
								remove(TABLE, TABLE_SIZE, j);
							}
							//Dealing Cards
							while (PC_SIZE != 6) {
								if (SIZE != 0) {
									int shuffled_card = rand() % SIZE;
									append(PC_CARDS, PC_SIZE, CARDS[shuffled_card]);
									remove(CARDS, SIZE, shuffled_card);
								}
								else {
									if (COZAR_AVAILABLE == true) {
										append(PC_CARDS, PC_SIZE, cozar);
										COZAR_AVAILABLE = false;
									}
									if (PC_SIZE == 0) {
										SetCursPos(0, 0);
										SetColor(WHITE, RED);
										cout << "Комп'ютер переміг!\t-5 $";
										SetColor(WHITE, BLACK);
										ifstream file;
										int USERS_COUNT = 0;
										string* USERS = new string[USERS_COUNT];
										Read(file, login, USERS, USERS_COUNT);
										file.close();
										Renew_balance(USERS, USERS_COUNT, login, -5);
										ofstream file1;
										Rewrite(file1, USERS, USERS_COUNT);
										file1.close();
										int key = _getch();
										STOP = true;
										i = 7;
									}
									break;
								}
							}
							if (PC_SIZE == 0 && SIZE == 0) {
								SetCursPos(0, 0);
								SetColor(WHITE, RED);
								cout << "Комп'ютер переміг!\t-5 $";
								SetColor(WHITE, BLACK);
								ifstream file;
								int USERS_COUNT = 0;
								string* USERS = new string[USERS_COUNT];
								Read(file, login, USERS, USERS_COUNT);
								file.close();
								Renew_balance(USERS, USERS_COUNT, login, -5);
								ofstream file1;
								Rewrite(file1, USERS, USERS_COUNT);
								file1.close();
								int key = _getch();
								STOP = true;
							}
							if (STOP != true) {
								i = 1;
							}
							else {
								i = 7;
							}
							Sleep(1000);
						}
						else {
							Sleep(1000);
						}
					}
					else {
						i = 7;
					}
				}
			}

			if (STOP != true) {
				//Dealing cards
				while (PC_SIZE != 6) {
					if (SIZE != 0) {
						int shuffled_card = rand() % SIZE;
						append(PC_CARDS, PC_SIZE, CARDS[shuffled_card]);
						remove(CARDS, SIZE, shuffled_card);
					}
					else {
						if (COZAR_AVAILABLE == true) {
							append(PC_CARDS, PC_SIZE, cozar);
							COZAR_AVAILABLE = false;
						}
						if (PC_SIZE == 0) {
							SetCursPos(0, 0);
							SetColor(WHITE, RED);
							cout << "Комп'ютер переміг!\t-5 $";
							SetColor(WHITE, BLACK);
							ifstream file;
							int USERS_COUNT = 0;
							string* USERS = new string[USERS_COUNT];
							Read(file, login, USERS, USERS_COUNT);
							file.close();
							Renew_balance(USERS, USERS_COUNT, login, -5);
							ofstream file1;
							Rewrite(file1, USERS, USERS_COUNT);
							file1.close();
							int key = _getch();
							STOP = true;
						}
						break;
					}
				}

				while (US_SIZE != 6) {
					if (SIZE != 0) {
						int shuffled_card = rand() % SIZE;
						append(US_CARDS, US_SIZE, CARDS[shuffled_card]);
						remove(CARDS, SIZE, shuffled_card);
					}
					else {
						if (COZAR_AVAILABLE == true) {
							append(US_CARDS, US_SIZE, cozar);
							COZAR_AVAILABLE = false;
						}
						if (US_SIZE == 0) {
							SetCursPos(0, 0);
							SetColor(WHITE, YELLOW_FADE);
							cout << "Ви перемогли!\t+5 $";
							SetColor(WHITE, BLACK);
							ifstream file;
							int USERS_COUNT = 0;
							string* USERS = new string[USERS_COUNT];
							Read(file, login, USERS, USERS_COUNT);
							file.close();
							Renew_balance(USERS, USERS_COUNT, login, 5);
							ofstream file1;
							Rewrite(file1, USERS, USERS_COUNT);
							file1.close();
							int key = _getch();
							STOP = true;
						}
						break;
					}
				}
				//

				//Cleaning Table
				for (int j = TABLE_SIZE - 1; j > -1; j--) {
					remove(TABLE, TABLE_SIZE, j);
				}
			}

			for (int i = 1; i <= 6; i++) {
				if (STOP != true && US_SIZE != 0) {
					if (AttackUS(TABLE, TABLE_SIZE, US_CARDS, US_SIZE, PC_CARDS, PC_SIZE, SIZE, cozar, COZAR_AVAILABLE) == true) {
						if (DefendPC(TABLE, TABLE_SIZE, PC_CARDS, PC_SIZE, cozar) == false) {
							SetColor(WHITE, BLUE);
							cout << "\nКомп'ютер:";
							SetColor(WHITE, BLACK);
							cout << " забираю";
							Sleep(1500);
							//
							if (PC_SIZE != 0) {
								short through_up;
								for (int t = 1; t <= 6 - i; t++) {
									cout << "\n\nВведіть 1, якщо бажаєте підкинути карту, якщо ні - будь-яке інше число >> ";
									cin >> through_up;
									if (through_up == 1) {
										if (AttackUS(TABLE, TABLE_SIZE, US_CARDS, US_SIZE, PC_CARDS, PC_SIZE, SIZE, cozar, COZAR_AVAILABLE) == false) {
											t = 7;
										}
									}
									else {
										t = 7;
									}
								}
							}
							//
							for (int j = 0; j < TABLE_SIZE; j++) {
								append(PC_CARDS, PC_SIZE, TABLE[j]);
							}
							for (int j = TABLE_SIZE - 1; j > -1; j--) {
								remove(TABLE, TABLE_SIZE, j);
							}
							//Dealing Cards
							while (US_SIZE != 6) {
								if (SIZE != 0) {
									int shuffled_card = rand() % SIZE;
									append(US_CARDS, US_SIZE, CARDS[shuffled_card]);
									remove(CARDS, SIZE, shuffled_card);
								}
								else {
									if (COZAR_AVAILABLE == true) {
										append(US_CARDS, US_SIZE, cozar);
										COZAR_AVAILABLE = false;
									}
									if (US_SIZE == 0) {
										SetCursPos(0, 0);
										SetColor(WHITE, YELLOW_FADE);
										cout << "Ви перемогли!\t+5 $";
										SetColor(WHITE, BLACK);
										ifstream file;
										int USERS_COUNT = 0;
										string* USERS = new string[USERS_COUNT];
										Read(file, login, USERS, USERS_COUNT);
										file.close();
										Renew_balance(USERS, USERS_COUNT, login, 5);
										ofstream file1;
										Rewrite(file1, USERS, USERS_COUNT);
										file1.close();
										int key = _getch();
										STOP = true;
										i = 7;
									}
									break;
								}
							}
							if (US_SIZE == 0 && SIZE == 0) {
								SetCursPos(0, 0);
								SetColor(WHITE, YELLOW_FADE);
								cout << "Ви перемогли!\t+5 $";
								SetColor(WHITE, BLACK);
								ifstream file;
								int USERS_COUNT = 0;
								string* USERS = new string[USERS_COUNT];
								Read(file, login, USERS, USERS_COUNT);
								file.close();
								Renew_balance(USERS, USERS_COUNT, login, 5);
								ofstream file1;
								Rewrite(file1, USERS, USERS_COUNT);
								file1.close();
								int key = _getch();
								STOP = true;
							}
							if (STOP != true) {
								i = 1;
							}
							else {
								i = 7;
							}
						}
						else {
							SetColor(WHITE, BLUE);
							cout << "\nКомп'ютер:";
							SetColor(WHITE, BLACK);
							cout << " відбив";
							Sleep(1500);
						}
					}
					else {
						i = 7;
					}
				}
			}

			if (STOP != true) {
				//Dealing cards
				while (US_SIZE != 6) {
					if (SIZE != 0) {
						int shuffled_card = rand() % SIZE;
						append(US_CARDS, US_SIZE, CARDS[shuffled_card]);
						remove(CARDS, SIZE, shuffled_card);
					}
					else {
						if (COZAR_AVAILABLE == true) {
							append(US_CARDS, US_SIZE, cozar);
							COZAR_AVAILABLE = false;
						}
						if (US_SIZE == 0) {
							SetCursPos(0, 0);
							SetColor(WHITE, YELLOW_FADE);
							cout << "Ви перемогли!\t+5 $";
							SetColor(WHITE, BLACK);
							ifstream file;
							int USERS_COUNT = 0;
							string* USERS = new string[USERS_COUNT];
							Read(file, login, USERS, USERS_COUNT);
							file.close();
							Renew_balance(USERS, USERS_COUNT, login, 5);
							ofstream file1;
							Rewrite(file1, USERS, USERS_COUNT);
							file1.close();
							int key = _getch();
							STOP = true;
						}
						break;
					}
				}

				while (PC_SIZE != 6) {
					if (SIZE != 0) {
						int shuffled_card = rand() % SIZE;
						append(PC_CARDS, PC_SIZE, CARDS[shuffled_card]);
						remove(CARDS, SIZE, shuffled_card);
					}
					else {
						if (COZAR_AVAILABLE == true) {
							append(PC_CARDS, PC_SIZE, cozar);
							COZAR_AVAILABLE = false;
						}
						if (PC_SIZE == 0) {
							SetCursPos(0, 0);
							SetColor(WHITE, RED);
							cout << "Комп'ютер переміг!\t-5 $";
							SetColor(WHITE, BLACK);
							ifstream file;
							int USERS_COUNT = 0;
							string* USERS = new string[USERS_COUNT];
							Read(file, login, USERS, USERS_COUNT);
							file.close();
							Renew_balance(USERS, USERS_COUNT, login, -5);
							ofstream file1;
							Rewrite(file1, USERS, USERS_COUNT);
							file1.close();
							int key = _getch();
							STOP = true;
						}
						break;
					}
				}
				//

				//Cleaning Table
				for (int j = TABLE_SIZE - 1; j > -1; j--) {
					remove(TABLE, TABLE_SIZE, j);
				}
			}
		}
	}
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
		int space1 = user.find("|");
		int space2 = user.find("|", space1 + 1);

		string name = "";
		for (int i = 0; i < space1; i++) {
			name += user[i];
		}

		if (name == username) {
			string pass = "";
			for (int i = space1 + 1; i < space2; i++) {
				pass += user[i];
			}
			return pass;
		}
	}
}

string getCoins(ifstream& file, string username) {
	string user;
	while (!file.eof()) {
		getline(file, user);
		int space1 = user.find("|");
		int space2 = user.find("|", space1 + 1);

		string name = "";
		for (int i = 0; i < space1; i++) {
			name += user[i];
		}

		if (name == username) {
			string coins = "";
			for (int i = space2 + 1; i < user.size(); i++) {
				coins += user[i];
			}
			return coins;
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
	file.open(path_users);

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
			file.open(path_users);

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
		file.open(path_users, ios::app);

		file << username << "|" << password << "|" << 100 << "\n";

		file.close();

		cout << "Реєстрація користувача " << username << " проведена успішно!";
		cout << "\nНа Ваш баланс нараховано 100 $";
		int key = _getch();
		system("cls");
	}
}

string LogIn() {
	bool STOP = false;

	ifstream file;
	file.open(path_users);

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
			file.open(path_users);

			cout << "Введіть пароль >> ";
			getline(cin, password);

			true_pass = getPassword(file, login);
			file.close();
			if (password != true_pass) {
				ifstream file;
				file.open(path_users);

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
				ifstream file;
				file.open(path_users);

				cout << "Добрий день, " << login << "!";
				cout << "\nНа Вашому балансі зараз " << getCoins(file, login) << " $";

				file.close();

				int key = _getch();
				system("cls");
				return login;
			}

		} while (password != true_pass);
	}
	else {
		cout << "Користувача з логіном " << login << " не існує! Натисніть будь-яку клавішу, щоб повернутися до меню";
		int key = _getch();
		system("cls");
		return "";
	}
}

void AUTHORIZATION(string& LOGIN) {
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
			LOGIN = LogIn();
			if (LOGIN != "") {
				todo = 4;
			}
			break;
		case 2:
			SignUp();
			break;
		case 3:
			exit(3);
		default:
			break;
		}

	} while (todo != 4);
}


int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	setlocale(LC_ALL, "Russian");

	srand(time(NULL));

	string LOGIN = "";
	AUTHORIZATION(LOGIN);

	while (true) {
		GAME(LOGIN);
	}
}
