#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <windows.h>
#include <iostream> //Только дебаг
using namespace sf;

//Пути к файлам
#define ICON_ "C:/Users/developer/source/repos/alah akbar/icon.png" 
#define TEXTURE_ "C:/Users/developer/source/repos/alah akbar/texture.png"

const int x = 7, y = 7; //Размер игровой площадки
const int line = 3; //Размер диагонали / прямой для победы
const int size = 160; //Размер текстуры (Одного куба)
int moveCount; //Количество ходов
bool gamePause = false;
RenderWindow window(VideoMode(size* x, size* y), L"Крестики нолики"); //Окно отрисовки
Image texture_image;
Texture texture_;

std::vector<sf::Sprite>texture_sprite(x* y, sf::Sprite(texture_));

void createPool(int x, int y, int i); //Функция создания Одного куба
int checkwinner(int id, int x, int y); //Функция проверки победы
int field[x][y]; //Значение кубов

void createAllPool() //Создание всех кубов и их отображение/cброс
{
	window.pushGLStates();
	window.clear();
	for (int i = 0; i < x; i++)
	{
		for (int j = 0; j < y; j++) createPool(i, j, i + j);
	}
	window.popGLStates();
	window.display();
}

int main()
{
	//Подключаем русский язык
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	setlocale(LC_ALL, "RU");
	//Подключаем Иконку
	Image image;
	image.loadFromFile(ICON_);
	window.setIcon(604, 604, image.getPixelsPtr());
	window.setFramerateLimit(60);

	//Текстуры
	texture_image.loadFromFile(TEXTURE_); //Загрука файла текстуры
	texture_image.createMaskFromColor(Color(255, 255, 255)); //Маска (белая)
	texture_.loadFromImage(texture_image); //Подгрузка текстуры

	//Создание поля
	createAllPool();
	while (window.isOpen())  //Пока окно открыто:
	{
		Vector2i vector = Mouse::getPosition(window); //Позиция мыши X.px, Y.px
		int x = vector.x / size; // index клетки X
		int y = vector.y / size; // index клетки Y
		Event event;
		while (window.pollEvent(event)) {
			if (event.type == Event::MouseButtonPressed) { //Нажатие мыши
				if (!field[x][y] && !gamePause)
				{
					if (event.key.code == Mouse::Left) field[x][y] = 1;
					if (event.key.code == Mouse::Right) field[x][y] = 2;
					moveCount++;
					std::cout << "[Debug] Кликаю:" << x << ":" << y << std::endl;
					/*gamePause = true;
					switch (checkwinner(field[x][y], x, y))
					{
						case 1: std::cout << "Победил Нолик" << std::endl; break;
						case 2: std::cout << "Победил Крестик" << std::endl; break;
						case 3: std::cout << "Ничья" << std::endl; break;
						default: gamePause = false;
					}*/
				}
				createAllPool(); //Перерисовка поля

			}
			if ((event.type == Event::KeyPressed) && (event.key.code == Keyboard::Escape)) window.close();
			if (event.type == Event::Closed) window.close(); //Закрытие окна
		}
	}
}

int checkwinner(int id, int x, int y)
{
	//Проверка строк
	for (int i = 0; i < line; i++) {
		if (field[x][i] != id) break;
		if (i == line - 1) return id;
	}

	//Проверка столбов
	for (int i = 0; i < line; i++) {
		if (field[i][y] != id) break;
		if (i == line - 1) return id;
	}

	//Проверка диагонали
	if (x == y) {
		for (int i = 0; i < line; i++) {
			if (field[i][i] != id) break;
			if (i == line - 1) return id;
		}
	}

	//Проверка анти-диагонали
	if (x + y == line - 1) {
		for (int i = 0; i < line; i++) {
			if (field[i][(line - 1) - i] != id) break;
			if (i == line - 1) return id;
		}
	}

	//Проверка ничьей
	if (moveCount == (pow(line, 2) - 1)) return 3;
	return false;
}

void createPool(int x, int y, int i)
{
	//std::cout << "[Debug] Создаю:" << x << ":" << y << "[Значение: " << field[x][y] << "]" << std::endl;
	switch (field[x][y]) //Зависимость значения
	{
	case 0: texture_sprite[i].setTextureRect(IntRect(0, 0, size, size)); break; //Пустой квадрат
	case 1: texture_sprite[i].setTextureRect(IntRect(size, size - size, size * 2, size)); break; //квадрат Нолик
	case 2: texture_sprite[i].setTextureRect(IntRect(size * 2, size - size, size * 3, size)); break; //квадрат Крестик
	}
	texture_sprite[i].setPosition(float(x * size), float(y * size)); //Позиция куба
	window.draw(texture_sprite[i]); //Отрисовка куба
}
