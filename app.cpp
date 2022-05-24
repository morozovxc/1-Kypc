#include <iostream>
#include <fstream>
#include <sstream>
#include <windows.h>
#include <conio.h>
#include <string>
#include <iomanip>
#include <array>
#include <vector>
#include <algorithm>
#include <iterator>

#define ESC 27
#define UP 72
#define DOWN 80
#define ENTER 13
#define MAX_PLAYERS 512

using namespace std;
bool active = true;
int active_menu = 0;
bool inMenu = true;
string Menu[] = { "Вывод задания","Просмотреть результаты участниц", "Вывести список по результатам", "Вывести список по факультету", "Добавить", "Удалить","Выход"};

int menu();
int print_all();

HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);

void GoToXY(short x, short y) { SetConsoleCursorPosition(hStdOut, { x, y }); }

void ConsoleCursorVisible(bool show, short size)
{
	CONSOLE_CURSOR_INFO structCursorInfo;
	GetConsoleCursorInfo(hStdOut, &structCursorInfo);
	structCursorInfo.bVisible = show;
	structCursorInfo.dwSize = size;
	SetConsoleCursorInfo(hStdOut, &structCursorInfo);
}

bool remove_line(const char* filename, size_t index);
bool remove_line(const char* filename, size_t index)
{
	std::vector<std::string> vec;
	std::ifstream file(filename);
	if (file.is_open())
	{
		std::string str;
		while (std::getline(file, str))
			vec.push_back(str);
		file.close();
		if (vec.size() < index)
			return false;
		vec.erase(vec.begin() + index);
		std::ofstream outfile(filename);
		if (outfile.is_open())
		{
			std::copy(vec.begin(), vec.end(),
				std::ostream_iterator<std::string>(outfile, "\n"));
			outfile.close();
			return true;
		}
		return false;
	}
	return false;
}

void del_db()
{
	ifstream f("C:/Users/developer/source/repos/apop/db/db.txt");
	//
	if (f.peek() == EOF)
	{
		cout << "\n  Таблица пустая";
		cout << "\n\n  Для выхода нажмите - ESC";
		f.close();
	}
	else {
		f.close();
		fstream f("C:/Users/developer/source/repos/apop/db/db.txt", ios::app);
		print_all();
		cout << "\n\nВведите ID строки для удаления: ";
		size_t index;
		const char* file = "C:/Users/developer/source/repos/apop/db/db.txt";
		cin >> index;
		if (!remove_line(file, index - 1))
		{
			cout << "\n  Студентки под таким ID нет!";
		}
		else {
			inMenu = true;
			menu();
		}
	}
}

void add_bd()
{
	fstream f("C:/Users/developer/source/repos/apop/db/db.txt", ios::app);
	char name[30];
	char group[10];
	char fakts[50];
	char fakts2[50];
	char time[30];
	if (f.is_open())
	{
		cout << "Впишите фамилию: ";
		cin >> name;
		cout << "Впишите группу: ";
		cin >> group;
		cout << "Впишите факультет: ";

		cin >> fakts;
		cin.getline(fakts2, sizeof(fakts2));

		cout << "Впишите результат: ";
		cin >> time;

		f.close();
		ifstream f("C:/Users/developer/source/repos/apop/db/db.txt");
		if (f.peek() == EOF)
		{
			f.close();
			fstream f("C:/Users/developer/source/repos/apop/db/db.txt", ios::app);
			f << name << " " << group << " " << time << " " << fakts << fakts2;
		}
		else
		{
			string line;
			getline(f, line);
			if (strlen(line.c_str()) < 4)
			{
				f.close();
				fstream f("C:/Users/developer/source/repos/apop/db/db.txt", ios::app);
				f << "" << name << " " << group << " " << time << " " << fakts << fakts2;
			}
			else {
				f.close();
				fstream f("C:/Users/developer/source/repos/apop/db/db.txt", ios::app);
				f << "\n" << name << " " << group << " " << time << " " << fakts << fakts2;
			}
		}
		f.close();
	}
	inMenu = true;
	menu();
}

void print_top_fakt()
{

	ifstream f("C:/Users/developer/source/repos/apop/db/db.txt");
	if (f.peek() == EOF)
	{
		cout << "\n  Таблица пустая";
		cout << "\n\n  Для выхода нажмите - ESC";
		f.close();
	}
	else {
		int i = 0;
		char faktscheck[50];
		char faktscheck2[50];
		string check;

		cout << "Впишите факультет: ";
		cin >> faktscheck;
		cin.getline(faktscheck2, sizeof(faktscheck2));
		check = string(faktscheck) + string(faktscheck2);

		array<string, MAX_PLAYERS> arr;
		array<int32_t, MAX_PLAYERS> times;
		array<string, MAX_PLAYERS> names;
		array<string, MAX_PLAYERS> groups;
		array<string, MAX_PLAYERS> fakts;

		string line;
		printf("________________________________________________________________________________________________________________________\n");
		cout << setw(4) << left << "ID " << setw(30) << left << "Фамилия"
			<< setw(10) << left << "Группа"
			<< setw(17) << left << "Результат (c)"
			<< setw(50) << left << " Факультет"
			<< endl;
		while (!f.eof())
		{
			getline(f, line);
			if (strlen(line.c_str()) < 2) break;
			++i;
			char name[30];
			char group[10];
			char fakt[50];
			int time;
			const char* str = line.c_str();
			sscanf(str, "%30s%10s%d%255[^\n\r]", name, group, &time, fakt);

			string checkgroup = fakt;
			int pos = checkgroup.find(check);

			if (pos != -1)
			{
				names[i] += name;
				groups[i] += group;
				fakts[i] += fakt;
				times[i] = time;
			}
			else
			{
				if(i != 0) i--;
				continue;
			}
		}

		for (int j = 1; j < MAX_PLAYERS; j++)
		{
			for (int g = 0; g < MAX_PLAYERS - j - 1; g++)
			{
				if (times[g] > times[g + 1] && times[g + 1] > 0 && times[g] > 0)
				{
					swap(times[g], times[g + 1]);
					swap(names[g], names[g + 1]);
					swap(groups[g], groups[g + 1]);
					swap(fakts[g], fakts[g + 1]);
				}
			}
		}
		for (int j = 0; j < 512; j++)
		{
			if (times[j] > 0) cout << setw(4) << left << j << setw(30) << left << string(names[j])
				<< setw(10) << left << groups[j]
				<< setw(17) << left << times[j]
				<< setw(50) << left << fakts[j]
				<< endl;
		}

		printf("________________________________________________________________________________________________________________________\n");
		cout << "\n  Для выхода нажмите - ESC";
		f.close();
	}
}

void print_top()
{
	ifstream f("C:/Users/developer/source/repos/apop/db/db.txt");
	if (f.peek() == EOF)
	{
		cout << "\n  Таблица пустая";
		cout << "\n\n  Для выхода нажмите - ESC";
		f.close();
	}
	else {
		int i = 0;
		array<string, MAX_PLAYERS> arr;
		array<int32_t, MAX_PLAYERS> times;
		array<string, MAX_PLAYERS> names;
		array<string, MAX_PLAYERS> groups;
		array<string, MAX_PLAYERS> fakts;

		string line;
		printf("________________________________________________________________________________________________________________________\n");
		cout << setw(4) << left << "ID " << setw(30) << left << "Фамилия"
			<< setw(10) << left << "Группа"
			<< setw(17) << left << "Результат (c)"
			<< setw(50) << left << " Факультет"
			<< endl;
		while (!f.eof())
		{
			getline(f, line);
			++i;
			char name[30];
			char group[10];
			char fakt[50];
			const char* str = line.c_str();
			sscanf(str, "%30s%10s%d%255[^\n\r]", name, group, &times[i], fakt);
			names[i] += name;
			groups[i] += group;
			fakts[i] += fakt;
		}
		for (int j = 1; j < MAX_PLAYERS; j++)
		{
			for (int g = 0; g < MAX_PLAYERS - j - 1; g++)
			{
				if (times[g] > times[g + 1] && times[g + 1] > 0 && times[g] > 0)
				{
					swap(times[g], times[g + 1]);
					swap(names[g], names[g + 1]);
					swap(groups[g], groups[g + 1]);
					swap(fakts[g], fakts[g + 1]);
				}
			}
		}
		for (int j = 0; j < 512; j++)
		{
			if (times[j] > 0) cout << setw(4) << left << j << setw(30) << left << string(names[j])
				<< setw(10) << left << groups[j]
				<< setw(17) << left << times[j]
				<< setw(50) << left << fakts[j]
				<< endl;
		}

		printf("________________________________________________________________________________________________________________________\n");
		cout << "\n  Для выхода нажмите - ESC";
		f.close();
	}
}

int print_all()
{
	ifstream f("C:/Users/developer/source/repos/apop/db/db.txt");
	if (f.peek() == EOF)
	{
		cout << "\n  Таблица пустая";
		cout << "\n\n  Для выхода нажмите - ESC";
		f.close();
	}else{
		int i = 0;
		string line;
		printf("________________________________________________________________________________________________________________________\n");
		cout << setw(4) << left << "ID " << setw(30) << left << "Фамилия"
			<< setw(10) << left << "Группа"
			<< setw(17) << left << "Результат (c)"
			<< setw(50) << left << " Факультет"
			<< endl;
		while (!f.eof())
		{
			getline(f, line);
			if (strlen(line.c_str()) < 2) break;
			++i;
			const char* str = line.c_str();
			char name[50];
			char fakt[50];
			char group[10];
			int time;

			sscanf(str, "%50s%10s%d%255[^\n\r]", name, group, &time, fakt);

			cout << setw(4) << left << i << setw(30) << left << name
				<< setw(10) << left << group
				<< setw(17) << left << time
				<< setw(50) << left << fakt
				<< endl;


		}
		printf("________________________________________________________________________________________________________________________\n");
		cout << "\n  Для выхода нажмите - ESC";
		f.close();
	}
	return 0;
}

void print_dz()
{
	GoToXY(5, 2);
	cout << "Задание:\n  Составить программу для обработки результатов кросса на 500м для женщин. \n  В кроссе участвуют не более 45 студенток.\n  Для каждой участницы ввести фамилию, факультет, номер группы и результат.\
	\n  [1] Вывести список студенток, упорядоченный по результатам\n  [2] Вывести список студенток по укзанному факультету";
	cout << "\n\n  Для выхода нажмите - ESC";
}

int DrawMenu();
int DrawMenu()
{
	int x = 5, y = 2;
	GoToXY(5, 2);
	for (int i = 0; i < size(Menu); i++)
	{
		if (i == active_menu) 	SetConsoleTextAttribute(hStdOut, FOREGROUND_RED | FOREGROUND_INTENSITY);
		else 	SetConsoleTextAttribute(hStdOut, FOREGROUND_GREEN);
		GoToXY(x, y++);
		cout << Menu[i] << endl;
	}
	return 0;
}

int menu()
{
	system("CLS");
	ConsoleCursorVisible(false, 100);
	char ch;
	active = true;
	while (true)
	{
		if(active && inMenu) DrawMenu();
		active = false;
		ch = _getch();
		if (ch == -32) ch = _getch(); // Отлавливаем стрелочки
		switch (ch)
		{
			case ESC:
				inMenu = true;
				system("CLS");
				menu();
			case UP:
				if (inMenu)
				{
					if (active_menu > 0)
						--active_menu;
					else active_menu = size(Menu) - 1;
					DrawMenu();
					break;
				}
			case DOWN:
				if (inMenu)
				{
					if (active_menu < size(Menu) - 1)
						++active_menu;
					else active_menu = 0;
					DrawMenu();
					break;
				}
			case ENTER:
				switch (active_menu)
				{
					case 0:
					{
						inMenu = false;
						system("CLS");
						print_dz();
						break;
					}
					case 1:
					{
						inMenu = false;
						system("CLS");
						print_all();
						break;
					}
					case 2:
					{
						inMenu = false;
						system("CLS");
						print_top();
						break;
					}
					case 3:
					{
						inMenu = false;
						system("CLS");
						print_top_fakt();
						break;
					}
					case 4:
					{
						inMenu = false;
						system("CLS");
						add_bd();
						break;
					}
					case 5:
					{
						inMenu = false;
						system("CLS");
						del_db();
						break;
					}
					case 6:
					{
						system("CLS");
						exit(0);
						break;
					}
				}
		}
	}
	return 0;
}

int main()
{
	system("CLS");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	menu();
	system("color 22");
}

