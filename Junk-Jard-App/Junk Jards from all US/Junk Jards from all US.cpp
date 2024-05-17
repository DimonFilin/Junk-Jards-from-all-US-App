
// Junk Jards from all US.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

/*
не вавтает Входа админ, пользователь*/

//исправил вход в аккаунт, доделываю регистрацию


//Различные библиотеки
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <conio.h>
#include <Windows.h>
#include <iomanip>
#include <tuple>
#include <algorithm>
#include <cstdlib>
using namespace std;


//Последнее id для юзеров
int LastId = 0;



//Основные настройки
void MainSettings() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	HWND console = GetConsoleWindow();
	ShowWindow(console, SW_SHOWMAXIMIZED);//залочить полный экран

	//	wcout.imbue(locale("Russian_Russia.UTF-8"));
}


HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE); // Получаем дескриптор консоли
// Текстовый курсор в точку x,y
void GoToXY(short x, short y)
{
	SetConsoleCursorPosition(hStdOut, { x, y });
}
COORD CalculateTextPosition(const string& text)
{
	CONSOLE_FONT_INFO fontInfo;
	GetCurrentConsoleFont(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &fontInfo);
	int fontWidth = fontInfo.dwFontSize.X;
	int fontHeight = fontInfo.dwFontSize.Y;

	int screenWidth = GetSystemMetrics(SM_CXSCREEN); // Получение ширины экрана
	int screenHeight = GetSystemMetrics(SM_CYSCREEN); // Получение высоты экрана
	int consoleWidth = screenWidth / fontWidth; // Ширина консоли в символах
	int consoleHeight = screenHeight / fontHeight; // Высота конисоли в строках

	// Рассчитываем центр консоли
	int centerX = consoleWidth / 2;
	int centerY = consoleHeight / 2;

	int textWidth = static_cast<int>(text.length()); // Ширина текста
	int textHeight = 3; // Высота текста

	int startX = centerX - textWidth / 2; // Начальная позиция x для вывода текста
	int startY = centerY - textHeight / 2; // Начальная позиция y для вывода текста

	return COORD{ static_cast<short>(startX), static_cast<short>(startY) };
}





//Класс для хранения данных об локации
class Location {
	// Инкапсуляция данных для безопасности
private:
	string State;
	string Name;
	string City;
	string ZipCode;
public:

	// Конструктор класса для удобного создания и инициализации объектов
	Location(const  string state, const  string  name, const  string  city, const  string zipcode)
		: State(state), Name(name), City(city), ZipCode(zipcode) {}
	// метод для вывода данных авто 
	vector<string> GetAllInfoAboutLocation()
	{
		return { State, Name, City, ZipCode };
	}
	string FormStringToAddToFile()
	{
		string stroke;

		stroke = State + ";" + Name + ";" + City + ";" + ZipCode;

		return stroke;
	}
	string GetZipCode() {
		return ZipCode;
	}
	string GetName() {
		return Name;
	}
	string GetState() {
		return State;
	}
};
//Метод для вывода локаций из файла в вектор
vector<Location> readLocationsFromFile(const  string filename) {
	ifstream file(filename); // Открываем файл с данными
	vector<Location> Locations;

	//Получилось открыть файл?
	if (file.is_open()) {
		string line;
		while (getline(file, line)) {
			stringstream ss(line);//Обернем строку Line в ss для работы как с потоком
			vector<string> LocationInfo;//Создаем вектор в который запишем всю информацию об автомобиле
			string info;//временная переменная, которая будет хранить часть ss

			//Разделим нашу строку по символу ;
			while (getline(ss, info, ';')) {
				LocationInfo.push_back(info);
			}
			// Проверяем корректное количество полей
			Location location(LocationInfo[0], LocationInfo[1], LocationInfo[2], LocationInfo[3]);
			Locations.push_back(location);

		}
		file.close();
	}
	else {//Не получилось
		system("cls");
		COORD cords = CalculateTextPosition("Ошибка открытия файла.\n Нажмите любую клавишу чтобы продолжить\n");
		GoToXY(cords.X, cords.Y);
		cout << "Ошибка открытия файла." << endl;
		GoToXY(cords.X - 4, cords.Y + 2);
		cout << "Нажмите любую клавишу чтобы продолжить\n";  char t = _getch();
		system("cls");
	}

	return Locations;
}
//Метод для добавления поля в список локаций
Location UpdateLocationField() {

	//Очистим консоль
	system("cls");

	//Массив для ввода значений
	string* InfoOfLocation = new string[4];

	//Заполним массив
	cout << "Введите название";
	cin >> InfoOfLocation[0];
	cout << "Введите адрес";
	cin >> InfoOfLocation[1];
	cout << "Введите город";
	cin >> InfoOfLocation[2];
	cout << "Введите код локации";
	cin >> InfoOfLocation[3];

	//Вернем готовый объект для добавления в вектор
	return Location(InfoOfLocation[0], InfoOfLocation[1], InfoOfLocation[2], InfoOfLocation[3]);
}
//Ввод информации из вектора в файл
void InsertLocationsToFile(vector<Location> locationsToFile) {

	string s = "";//строка в которую добавим текст для будущего добавления в файл
	for (int i = 0; i < locationsToFile.size(); i++)//Введем все данные в строку
	{
		s += locationsToFile[i].FormStringToAddToFile();
		s += "\n";//Добавим Enter
	}
	//cout << s;//Выведем для проверки действия

	ofstream OutputToFile("List_Of_Jards.txt"); // Открываем файл с данными
	if (OutputToFile.is_open()) {//Проверим, можно ли открыть файл
		OutputToFile << s; //Вводим в файл
		OutputToFile.close();//Закроем файл
		system("cls");
		COORD cords = CalculateTextPosition("Строка успешно записана в файл.\n Нажмите любую клавишу чтобы продолжить\n");
		GoToXY(cords.X, cords.Y);
		cout << "Строка успешно записана в файл." << endl;
		GoToXY(cords.X - 4, cords.Y + 2);
		cout << "Нажмите любую клавишу чтобы продолжить\n";  char t = _getch();
		system("cls");// Запись в файл произошла
	}
	else {
		system("cls");
		COORD cords = CalculateTextPosition("Ошибка открытия файла для записи.\n Нажмите любую клавишу чтобы продолжить\n");
		GoToXY(cords.X, cords.Y);
		cout << "Ошибка открытия файла для записи." << endl;
		GoToXY(cords.X - 4, cords.Y + 2);
		cout << "Нажмите любую клавишу чтобы продолжить\n";  char t = _getch();
		system("cls");//Возникла ошибка при открытии файла

	}
}
//Вывод списка локаций
COORD OutputLocationsInfo(vector <Location> locations) {
	COORD cords = CalculateTextPosition("Florida  Central Florida Pick & Pay 10694 Cosmonaut Blvd  Orlando FL 32824");
	int i = size(locations) / 2 * (-1);
	int iteration = 1;
	cords.Y += i;
	for (Location location : locations) {
		GoToXY(cords.X, cords.Y++);
		vector<string> locationsInfo = location.GetAllInfoAboutLocation();
		cout << iteration++ << " ";
		for (string info : locationsInfo) {
			cout << info << " ";
		}
		cout << endl;

	}
	return(cords);

}

COORD OutputInfoOf1Location(Location location) {
	COORD cords = CalculateTextPosition("Florida  Central Florida Pick & Pay 10694 Cosmonaut Blvd  Orlando FL 32824");
	int i = 6 / 2 * (-1);
	int iteration = 1;
	cords.Y += i;

	GoToXY(cords.X, cords.Y++);
	vector<string> locationsInfo = location.GetAllInfoAboutLocation();
	cout << iteration++ << " ";
	for (string info : locationsInfo) {
		cout << info << " ";
	}
	cout << endl;


	return(cords);

}


//Класс для хранения данных об автомобиле
class Car {
	// Инкапсуляция данных для безопасности
private:
	string Name;
	string PrimaryDamage;
	string SaleDate;
	string AuctionStartTime;
	string Vin;
	string Lot;
	string BuyNowCost;
	string Link;
public:
	Car() {}
	// Конструктор класса для удобного создания и инициализации объектов
	Car(const  string  name, const  string  primaryDamage, const  string  saleDate, const  string  auctionStartTime, const  string  vin, const  string  lot, const  string  buyNowCost, const  string  link)
		: Name(name), PrimaryDamage(primaryDamage), SaleDate(saleDate), AuctionStartTime(auctionStartTime), Vin(vin), Lot(lot), BuyNowCost(buyNowCost), Link(link) {}

	// метод для вывода данных авто 
	vector<string> GetAllInfoAboutCar()
	{
		return { Name, PrimaryDamage, SaleDate, AuctionStartTime, Vin, Lot, BuyNowCost, Link };
	}
	//Метод для формирования строки из данных об автомобиле
	string FormStringToAddToFile()
	{
		string stroke;

		stroke = Name + ";" + PrimaryDamage + ";" + SaleDate + ";" + AuctionStartTime + ";" + Vin + ";" + Lot + ";" + BuyNowCost + ";" + Link + ";";

		return stroke;
	}
	//Вывод информации об авто в виде списка удобного
	void CoutAllInfo()
	{

		printf("Name: %-10s, Primary Damage: %-10s, Sale Date: %-10s, Auction Time: %-10s, VIN: %-10s, Lot: %-10s, Cost: %-10s, Link: %.10s%s\n", Name.c_str(), PrimaryDamage.c_str(), SaleDate.c_str(), AuctionStartTime.c_str(), Vin.c_str(), Lot.c_str(), BuyNowCost.c_str(), Link.c_str(), (Link.length() > 10) ? "..." : "");
	}

	//вывод инфы в продвинутом виде
	void CoutAdvancedeInfo(int i)
	{
		COORD cords = CalculateTextPosition(" Link: https://abetter.bid/en/1042349153-2014-land_rover-range_rove");
		GoToXY(cords.X, cords.Y + i++);
		printf("Name: %s\n", Name.c_str());		GoToXY(cords.X, cords.Y + i++);
		printf("Primary Damage: %s\n", PrimaryDamage.c_str());		GoToXY(cords.X, cords.Y + i++);
		printf("Sale Date: %s\n", SaleDate.c_str());		GoToXY(cords.X, cords.Y + (i++));
		printf("Auction Start Time: %s\n", AuctionStartTime.c_str());		GoToXY(cords.X, cords.Y + i++);
		printf("Vin: %s\n", Vin.c_str());		GoToXY(cords.X, cords.Y + i++);
		printf("Lot: %s\n", Lot.c_str());		GoToXY(cords.X, cords.Y + i++);
		printf("Buy Now Cost: %s\n", BuyNowCost.c_str());		GoToXY(cords.X, cords.Y + i++);
		printf("Link: %s\n", Link.c_str());		GoToXY(cords.X, cords.Y + i++);

	}

	string GetName() {
		return Name;
	}
	string GetPrimaryDate() {
		return PrimaryDamage;
	}
	//Возврат даты 
	string GetSaleDate() const {
		return SaleDate;
	}
	string GetVin() const {
		return Vin;
	}
	string GetLot() const {
		return Lot;
	}
	string GetBuyNowCost() const {
		return BuyNowCost;
	}
};
//Метод для вывода списка об автомобилях из файла
vector <Car> readCarsFromFile(const  string filename) {
	ifstream file(filename); // Открываем файл с данными
	vector<Car> cars;

	//Получилось открыть файл?
	if (file.is_open()) {
		string line;
		int i = 0;
		while (getline(file, line)) {
			stringstream ss(line);//Обернем строку Line в ss для работы как с потоком
			vector< string> carInfo;//Создаем вектор в который запишем всю информацию об автомобиле
			string info;//временная переменная, которая будет хранить часть ss

			//Разделим нашу строку по символу ;
			while (getline(ss, info, ';')) {
				carInfo.push_back(info);
			}

			if (carInfo.size() == 8) {  // Проверяем корректное количество полей
				Car car(carInfo[0], carInfo[1], carInfo[2], carInfo[3], carInfo[4], carInfo[5], carInfo[6], carInfo[7]);
				cars.push_back(car);
			}
			else {
				cout << "Некорректное количество полей в строке: " << line << endl;
			}
		}
		file.close();
	}
	else {//Не получилось
		system("cls");
		COORD cords = CalculateTextPosition("Ошибка открытия файла.\n Нажмите любую клавишу чтобы продолжить\n");
		GoToXY(cords.X, cords.Y);
		cout << "Ошибка открытия файла." << endl;
		GoToXY(cords.X - 4, cords.Y + 2);
		cout << "Нажмите любую клавишу чтобы продолжить\n";  char t = _getch();
		system("cls");
	}

	return cars;
}
//Метод для добавления поля в список локаций
Car UpdateCarsField() {

	//Очистим консоль
	system("cls");

	//Массив для ввода значений
	vector <string> InfoOfCar(8);
	//Заполним вектор
	cout << "Введите название";
	cin >> InfoOfCar[0];
	cout << "Введите вид ущерба";
	cin >> InfoOfCar[1];
	cout << "Введите дату аукциона";
	cin >> InfoOfCar[2];
	cout << "Введите время начала аукциона";
	cin >> InfoOfCar[3];
	cout << "Введите вин номер автомобиля";
	cin >> InfoOfCar[4];
	cout << "Введите номер лота авто";
	cin >> InfoOfCar[5];
	cout << "Введите цену покупки автомобиля (Buy now) без знака $";
	cin >> InfoOfCar[6];
	cout << "Введите ссылку на аукцион";
	cin >> InfoOfCar[7];

	//Вернем готовый объект для добавления в вектор
	return Car(InfoOfCar[0], InfoOfCar[1], InfoOfCar[2], InfoOfCar[3], InfoOfCar[4], InfoOfCar[5], InfoOfCar[6], InfoOfCar[7]);
}
//Ввод списка авто из вектора в файл
void InsertCarsToFile(vector<Car> carsToFile, const string filename) {

	string s = "";//строка в которую добавим текст для будущего добавления в файл
	for (int i = 0; i < carsToFile.size(); i++)//Введем все данные в строку
	{
		s += carsToFile[i].FormStringToAddToFile();
		s += "\n";//Добавим Enter
	}
	//cout << s;//Выведем для проверки действия

	ofstream OutputToFile; // Открываем файл с данными
	OutputToFile.open(filename);
	if (OutputToFile.is_open()) {//Проверим, можно ли открыть файл
		OutputToFile << s; //Вводим в файл
		OutputToFile.close();//Закроем файл
		system("cls");
		COORD cords = CalculateTextPosition("Строка успешно записана в файл.\n Нажмите любую клавишу чтобы продолжить\n");
		GoToXY(cords.X, cords.Y);
		cout << "Строка успешно записана в файл." << endl;
		GoToXY(cords.X - 4, cords.Y + 2);
		cout << "Нажмите любую клавишу чтобы продолжить\n";  char t = _getch();
		system("cls");// Запись в файл произошла

	}
	else {
		system("cls");
		COORD cords = CalculateTextPosition("Ошибка открытия файла для записи.\n Нажмите любую клавишу чтобы продолжить\n");
		GoToXY(cords.X, cords.Y);
		cout << "Ошибка открытия файла для записи." << endl;
		GoToXY(cords.X - 4, cords.Y + 2);
		cout << "Нажмите любую клавишу чтобы продолжить\n";  char t = _getch();
		system("cls");//Возникла ошибка при открытии файла


	}
}
//Вывод списка авто
COORD OutputCarsInfo(vector <Car> Cars, COORD& coords) {
	system("cls");
	int i;

	if (size(Cars) > 2)
	{
		i = -20;
	}
	else i = -4;
	COORD cords = CalculateTextPosition(" Link:4-land_rover-range_rove");
	if (coords.X > 0)
	{
		cords = coords;
	}
	else
	{

		//int iteration = 1;
		cords.Y += i;
	}


	for (Car car : Cars) {
		vector<string> carInfo = car.GetAllInfoAboutCar();
		//car.CoutAllInfo(i);
		car.CoutAdvancedeInfo(i); i += 9;
		GoToXY(cords.X, cords.Y); cords.Y += 9;
	}
	return cords;
}

// Метод для получения значения из списка
template <size_t N>
int getValueFromList(COORD cords, const string(&options)[N]) {

	for (size_t i = 0; i < N; i++) {
		GoToXY(cords.X, cords.Y++);
		cout << i + 1 << ". " << options[i] << endl;
	}
	GoToXY(cords.X, cords.Y++);
AnotherStart:
	int choice;
	cout << "Введите номер: ";
	cin >> choice;

	// Проверка на правильность ввода
	if (choice < 1 || choice > N) {
		GoToXY(cords.X, cords.Y++);
		cout << "Некорректный выбор. Пожалуйста, выберите значение из списка." << endl;
		GoToXY(cords.X, cords.Y++);
		goto AnotherStart;
	}

	return choice;
}
// Примеры списков возможных вариантов
const string carTypes[] = { "Седан", "Хэтчбек", "Купе", "Кабриолет", "Кроссовер", "Пикап", "Внедорожник", "Минивэн", "Грузовик", "Кей-кар", "Мотоцикл", "Квадроцикл", "Багги", "Гидроцикл" };
const string engineTypes[] = { "Электро", "Гибрид", "Бензин", "Дизель" };
const string productionYears[] = { "менее года", "до 3 лет", "от 3 до 5 лет", "от 5 до 30 лет", "более 30 лет (раритет)" };
const string customsTypes[] = { "полная", "льготная" };
// Метод для рассчета стоимости привоза автомобиля
void calculateShippingCost() {



	// Получение информации о типе автомобиля, типе двигателя, годе производства и других параметрах
	double engineVolume, carCost;
	COORD cords = CalculateTextPosition("Нажмите любую клавишу для продолжения");

	GoToXY(cords.X, cords.Y - 1);
	// Ввод данных пользователь
	cout << "Выберите тип автомобиля:" << endl;
	int carTypeIndex = getValueFromList(cords, carTypes);
	system("cls");

	GoToXY(cords.X, cords.Y - 1);
	cout << "Выберите тип двигателя:" << endl;
	int engineTypeIndex = getValueFromList(cords, engineTypes);
	system("cls");

	GoToXY(cords.X, cords.Y - 1);
	cout << "Выберите год производства автомобиля:" << endl;
	int productionYearIndex = getValueFromList(cords, productionYears);
	system("cls");

	GoToXY(cords.X, cords.Y - 1);
	cout << "Введите объем двигателя автомобиля (в см3): ";
	cin >> engineVolume;
	system("cls");

	GoToXY(cords.X, cords.Y - 1);
	cout << "Введите стоимость автомобиля (в США) в долларах: ";
	cin >> carCost;
	system("cls");


	// Расчет стоимости привоза
	double totalCost = 1.1;
	//В зависимости от места в контейрнере
	switch (carTypeIndex)
	{
	case 1:
	case 2:
	case 3:
	case 4://простые авто
		totalCost *= 2;
		break;
	case 5:
	case 6:
	case 7:
	case 8:
		totalCost *= 4;
		break;//кроссоверы
	case 9://грузовик
		totalCost *= 5;
		break;
	case 10://кей кар
		totalCost *= 1;
		break;
	case 11:
	case 12:
	case 13:
	case 14://водный мото транспорт
		totalCost *= 0.5;
		break;
	}
	//От типа двигателя
	switch (engineTypeIndex)
	{
	case'1':
		totalCost *= 1.1;
		break;
	case'2':
		totalCost *= 1.2;
		break;
	case'3':
		totalCost *= 1.6;
		break;
	case'4':
		totalCost *= 1.7;
		break;

	}
	//От года производства
	switch (productionYearIndex)
	{
	case'1':
		totalCost *= 1;
		break;
	case'2':
		totalCost *= 1.5;
		break;
	case'3':
		totalCost *= 1.9;
		break;
	case'4':
		totalCost *= 2;
		break;
	case'5':
		totalCost *= 1;
		break;
	}

	if (engineVolume > 1)
	{
		if (engineVolume < 1500)
			totalCost *= engineVolume / 10;
		else
			totalCost *= engineVolume / 50;
	}

	GoToXY(cords.X, cords.Y++);

	cout << "Cтоимость авто: " << carCost << "$" << endl; GoToXY(cords.X, cords.Y++);
	cout << "Аукционный сбор: " << fixed << setprecision(2) << carCost / 110 << "$" << endl; GoToXY(cords.X, cords.Y++);
	cout << "Цена доставки : " << totalCost << "$" << endl; GoToXY(cords.X, cords.Y++);
	cout << "Итоговая цена : " << totalCost + carCost + carCost / 110 << "$" << endl;
}



//Класс для пользователей
class User {
	// Инкапсуляция данных для безопасности
private:
	int Id;
	string Name;
	string Password;
	string Email;
	string PhoneNumber;
public:
	int GetId() {
		return Id;
	}
	string GetName() {
		return Name;
	}
	string GetPassword() {
		return Password;
	}
	string GetEmail() {
		return Email;
	}
	string GetPhoneNumer() {
		return PhoneNumber;
	}
	// Конструктор класса для удобного создания и инициализации объектов
	User(const int id, const  string name, const string password, const  string  email, const  string  phonenumber)
		: Id(id), Name(name), Password(password), Email(email), PhoneNumber(phonenumber) {}
	// метод для вывода данных  
	tuple<int, string, string, string, string> GetAllInfoAboutUser()
	{
		return { make_tuple(Id, Name, Password, Email, PhoneNumber) };
	}
	string FormStringToAddToFile()
	{
		string stroke = "";

		stroke = to_string(Id) + ";" + Name + ";" + Password + ";" + Email + ";" + PhoneNumber;

		return stroke;
	}
	void OutPutUserInfo()
	{
		system("cls");
		COORD cords = CalculateTextPosition("1 Aretk artek2001 artek@gmail.com +375303333333");
		GoToXY(cords.X, cords.Y++);
		cout << "ID: " << Id;		GoToXY(cords.X, cords.Y++);
		cout << "Имя: " << Name;		GoToXY(cords.X, cords.Y++);
		cout << "Пароль: " << Password;		GoToXY(cords.X, cords.Y++);
		cout << "Email: " << Email;		GoToXY(cords.X, cords.Y++);
		cout << "Номер телефона: " << PhoneNumber;
		GoToXY(cords.X, cords.Y++);
		cout << "Нажмите любую клавишу для продолжения "; char t = _getch();
		GoToXY(cords.X, cords.Y);
	}
	~User() {}
};
//Метод для вывода пользователей из файла в вектор
vector<User> readUsersFromFile(const  string filename) {
	ifstream file(filename); // Открываем файл с данными
	vector<User> Users;

	//Получилось открыть файл?
	if (file.is_open()) {
		string line;
		while (getline(file, line)) {
			stringstream ss(line);//Обернем строку Line в ss для работы как с потоком
			vector<string> UsersInfo;//Создаем вектор в который запишем всю информацию об автомобиле
			string info;//временная переменная, которая будет хранить часть ss
			int i = 0, id;
			//Разделим нашу строку по символу ;
			while (getline(ss, info, ';')) {
				if (i == 0)
				{
					id = stoi(info);
					LastId = id;
				}
				else {
					UsersInfo.push_back(info);
				}
				i++;
			}
			// Проверяем корректное количество полей
			User user(id, UsersInfo[0], UsersInfo[1], UsersInfo[2], UsersInfo[3]);
			Users.push_back(user);

		}
		file.close();
	}
	else {//Не получилось
		system("cls");
		COORD cords = CalculateTextPosition("Ошибка открытия файла.\n Нажмите любую клавишу чтобы продолжить\n");
		GoToXY(cords.X, cords.Y);
		cout << "Ошибка открытия файла." << endl;
		GoToXY(cords.X - 4, cords.Y + 2);
		cout << "Нажмите любую клавишу чтобы продолжить\n";  char t = _getch();
		system("cls");

	}

	return Users;
}
//Метод для добавления поля в список пользователей
User UpdateUserField() {

	//Очистим консоль
	system("cls");

	//Массив для ввода значений
	string* InfoOfReport = new string[4]; int Id;

	//Заполним массив
	Id = ++LastId;
	//Валидация имени
	COORD cords = CalculateTextPosition("Введите пароль   ");
	GoToXY(cords.X, ++cords.Y);
	cout << "Введите логин: ";
	char ch;
	while (true) {
		ch = _getch(); // Считывание клавиши без ожидания нажатия Enter
		if (ch == 27) {// Проверка на Esc
			cout << endl << "Выход из входа." << endl;
			system("cls");
			InfoOfReport[0] = "";

			return User(1, "", "", "", "");
		}
		else if (ch == 8) {// Проверка на BackSpace

			if (!InfoOfReport[0].empty()) {//проверка на пустой пароль
				cout << "\b \b"; // Удаление последнего символа из консоли
				InfoOfReport[0].pop_back(); // Удаление последнего символа из login
			}
		}
		else if (ch == 13) {// Проверка на Enter
			cout << ch;
			cout << endl;
			goto Password;  // Завершение ввода при нажатии клавиши Enter
		}
		else {
			if (size(InfoOfReport[0]) < 16)
			{
				InfoOfReport[0] += ch;  // Добавление символа к переменной password
				cout << ch;  // Вывод * вместо введенных символов
			}
		}
	}
Password:
	GoToXY(cords.X, ++cords.Y);
	cout << "Введите пароль (минимум 5 символов): ";
	while (true) {
		ch = _getch(); // Считывание клавиши без ожидания нажатия Enter
		if (ch == 27) {// Проверка на Esc
			system("cls");
			InfoOfReport[1] = "";

			return User(1, "", "", "", "");
		}
		else if (ch == 8) {// Проверка на BackSpace

			if (!InfoOfReport[1].empty()) {//проверка на пустой пароль
				cout << "\b \b"; // Удаление последнего символа из консоли
				InfoOfReport[1].pop_back(); // Удаление последнего символа из login
			}
		}
		else if (ch == 13) {// Проверка на Enter
			if (size(InfoOfReport[1]) > 4)
			{
				cout << ch;
				cout << endl;
				goto Mail;
			}  // Завершение ввода при нажатии клавиши Enter
		}
		else {
			if (size(InfoOfReport[1]) < 30)
			{
				InfoOfReport[1] += ch;  // Добавление символа к переменной password
				cout << ch;  // Вывод * вместо введенных символов
			}
		}
	}
Mail:
	GoToXY(cords.X, ++cords.Y);
	cout << "Введите адрес почты: ";
	while (true) {
		ch = _getch(); // Считывание клавиши без ожидания нажатия Enter
		if (ch == 27) {// Проверка на Esc
			cout << endl << "Выход из входа." << endl;
			system("cls");
			InfoOfReport[2] = "";

			return User(1, "", "", "", "");
		}
		else if (ch == 8) {// Проверка на BackSpace

			if (!InfoOfReport[0].empty()) {//проверка на пустой пароль
				cout << "\b \b"; // Удаление последнего символа из консоли
				InfoOfReport[2].pop_back(); // Удаление последнего символа из login
			}
		}
		else if (ch == 13) {// Проверка на Enter
			cout << ch;
			cout << endl;
			goto Telephone;  // Завершение ввода при нажатии клавиши Enter
		}
		else {
			if (size(InfoOfReport[2]) < 30)
			{
				InfoOfReport[2] += ch;  // Добавление символа к переменной password
				cout << ch;  // Вывод * вместо введенных символов
			}
		}
	}
Telephone:
	GoToXY(cords.X, ++cords.Y);
	cout << "Введите номер телефона: +375";
	while (true) {
		ch = _getch(); // Считывание клавиши без ожидания нажатия Enter
		if (ch == 27) {// Проверка на Esc
			cout << endl << "Выход из входа." << endl;
			system("cls");
			InfoOfReport[3] = "";

			return User(1, "", "", "", "");
		}
		else if (ch == 8) {// Проверка на BackSpace

			if (!InfoOfReport[3].empty()) {//проверка на пустой пароль
				cout << "\b \b"; // Удаление последнего символа из консоли
				InfoOfReport[3].pop_back(); // Удаление последнего символа из login
			}
		}
		else if (ch == 13) {// Проверка на Enter
			cout << ch;
			cout << endl;
			goto End;  // Завершение ввода при нажатии клавиши Enter
		}
		else {
			if (size(InfoOfReport[3]) < 9)
			{
				InfoOfReport[3] += ch;  // Добавление символа к переменной password
				cout << ch;  // Вывод * вместо введенных символов
			}
		}
	}
End:
	GoToXY(cords.X, ++cords.Y);
	InfoOfReport[3] = "+ 375" + InfoOfReport[3];
	//Вернем готовый объект для добавления в вектор
	return User(Id, InfoOfReport[0], InfoOfReport[1], InfoOfReport[2], InfoOfReport[3]);
}
//Ввод информации из вектора в файл пользователей
void InsertUserToFile(vector<User> reportsToFile) {

	string s = "";//строка в которую добавим текст для будущего добавления в файл
	for (int i = 0; i < reportsToFile.size(); i++)//Введем все данные в строку
	{
		s += reportsToFile[i].FormStringToAddToFile();
		s += "\n";//Добавим Enter
	}
	//cout << s;//Выведем для проверки действия

	ofstream OutputToFile("Users.txt"); // Открываем файл с данными
	if (OutputToFile.is_open()) {//Проверим, можно ли открыть файл
		OutputToFile << s; //Вводим в файл
		OutputToFile.close();//Закроем файл
		system("cls");
		COORD cords = CalculateTextPosition("Вы успешно зарегистрировались");
		GoToXY(cords.X, cords.Y);
		cout << "Вы успешно зарегистрировались" << endl;
		GoToXY(cords.X - 4, cords.Y + 2);
		cout << "Нажмите любую клавишу чтобы продолжить\n";  char t = _getch();
		system("cls");// Запись в файл произошла
	}
	else {
		system("cls");
		COORD cords = CalculateTextPosition("Ошибка открытия файла для записи.\n Нажмите любую клавишу чтобы продолжить\n");
		GoToXY(cords.X, cords.Y);
		cout << "Ошибка открытия файла для записи." << endl;
		GoToXY(cords.X - 4, cords.Y + 2);
		cout << "Нажмите любую клавишу чтобы продолжить\n";  char t = _getch();
		system("cls");//Возникла ошибка при открытии файла


	}
}
//Вывод списка пользователей
void OutputUsersAll(vector <User> reports) {
	system("cls");
	COORD cords = CalculateTextPosition("1 Aretk artek2001 artek@gmail.com +375303333333");
	int i = size(reports) / 2 * (-1);
	for (User report : reports) {
		tuple<int, string, string, string, string> reportsInfo = report.GetAllInfoAboutUser();
		GoToXY(cords.X, cords.Y + i); i++;
		cout << get<0>(reportsInfo) << " ";
		cout << get<1>(reportsInfo) << " ";
		cout << get<2>(reportsInfo) << " ";
		cout << get<3>(reportsInfo) << " ";
		cout << get<4>(reportsInfo) << " ";
		cout << endl;
	}
	GoToXY(cords.X, cords.Y + i); i++;
	cout << "Нажмите любую клавишу для продолжения "; char t = _getch();
	GoToXY(cords.X, cords.Y + i);

}




//Класс для платных запросов
class PaidReport {
	// Инкапсуляция данных для безопасности
private:
	int Id;
	string SolvedOrNot;
	Car Title;
	string Answer;
public:
	//Получить имя
	string GetSolvedOrNot() {
		return SolvedOrNot;
	}
	// Получить айди 
	int GetId() {
		return Id;
	}
	// Конструктор класса для удобного создания и инициализации объектов
	PaidReport(const int id, const string solved, const Car car, const string answer)
		: Id(id), SolvedOrNot(solved), Title(car), Answer(answer) {}
	// метод для вывода данных авто 
	tuple<int, string, vector<string>, string> GetAllInfoAboutReport()
	{
		return { make_tuple(Id,SolvedOrNot, Title.GetAllInfoAboutCar(), Answer) };
	}
	string FormStringToAddToFile()
	{
		string stroke;

		stroke = Id + ";" + SolvedOrNot + ";" + Title.FormStringToAddToFile() + ";" + Answer;

		return stroke;
	}
	~PaidReport() {}
};
//Метод для вывода запросов из файла в вектор
vector<PaidReport> readPaidReportsFromFile(const  string filename) {
	ifstream file(filename); // Открываем файл с данными
	vector<PaidReport> PaidReports;

	//Получилось открыть файл?
	if (file.is_open()) {
		string line;
		while (getline(file, line)) {
			stringstream ss(line);//Обернем строку Line в ss для работы как с потоком
			vector<string> PaidReportsInfo;//Создаем вектор в который запишем всю информацию об автомобиле
			string info;//временная переменная, которая будет хранить часть ss
			int i = 0, id;
			//Разделим нашу строку по символу ;
			while (getline(ss, info, ';')) {
				if (i == 0)
				{
					id = stoi(info);
					LastId = id;
				}
				else {
					PaidReportsInfo.push_back(info);
				}
				i++;
			}
			// Проверяем корректное количество полей
			PaidReport paidReport(id, PaidReportsInfo[0], Car(PaidReportsInfo[1], PaidReportsInfo[2], PaidReportsInfo[3], PaidReportsInfo[4], PaidReportsInfo[5], PaidReportsInfo[6], PaidReportsInfo[7], PaidReportsInfo[8]), PaidReportsInfo[9]);
			PaidReports.push_back(paidReport);

		}
		file.close();
	}
	else {//Не получилось
		system("cls");
		COORD cords = CalculateTextPosition("Ошибка открытия файла.\n Нажмите любую клавишу чтобы продолжить\n");
		GoToXY(cords.X, cords.Y);
		cout << "Ошибка открытия файла." << endl;
		GoToXY(cords.X - 4, cords.Y + 2);
		cout << "Нажмите любую клавишу чтобы продолжить\n";  char t = _getch();
		system("cls");
	}

	return PaidReports;
}
//Метод для добавления поля в список запросов
PaidReport UpdatePaidReportField() {

	//Очистим консоль
	system("cls");

	//Массив для ввода значений
	string* PaidReportsInfo = new string[10]; int Id;

	//Заполним массив
	cout << "Введите id человека, который прислал запрос";
	cin >> Id;
	cout << "Введите тип (solved/un solved/problem)";
	cin >> PaidReportsInfo[0];
	cout << "Введите название автомобиля";
	cin >> PaidReportsInfo[1];
	cout << "Введите вид ущерба автомобиля";
	cin >> PaidReportsInfo[2];
	cout << "Введите дату аукциона автомобиля";
	cin >> PaidReportsInfo[3];
	cout << "Введите время начала аукциона автомобиля";
	cin >> PaidReportsInfo[4];
	cout << "Введите вин номер автомобиля";
	cin >> PaidReportsInfo[5];
	cout << "Введите номер лота авто";
	cin >> PaidReportsInfo[6];
	cout << "Введите цену покупки автомобиля (Buy now) без знака $";
	cin >> PaidReportsInfo[7];
	cout << "Введите ссылку на аукцион авто";
	cin >> PaidReportsInfo[8];
	cout << "Введите ответ от администратора";
	cin >> PaidReportsInfo[9];

	//Вернем готовый объект для добавления в вектор
	return PaidReport(Id, PaidReportsInfo[0], Car(PaidReportsInfo[1], PaidReportsInfo[2], PaidReportsInfo[3], PaidReportsInfo[4], PaidReportsInfo[5], PaidReportsInfo[6], PaidReportsInfo[7], PaidReportsInfo[8]), PaidReportsInfo[9]);
}
//Ввод информации из вектора в файл запросов
void InsertPaidReportsToFile(vector<PaidReport> reportsToFile) {

	string s = "";//строка в которую добавим текст для будущего добавления в файл
	for (int i = 0; i < reportsToFile.size(); i++)//Введем все данные в строку
	{
		s += reportsToFile[i].FormStringToAddToFile();
		s += "\n";//Добавим Enter
	}
	//cout << s;//Выведем для проверки действия

	ofstream OutputToFile("List_Of_Jards.txt"); // Открываем файл с данными
	if (OutputToFile.is_open()) {//Проверим, можно ли открыть файл
		OutputToFile << s; //Вводим в файл
		OutputToFile.close();//Закроем файл
		system("cls");
		COORD cords = CalculateTextPosition("Строка успешно записана в файл.\n Нажмите любую клавишу чтобы продолжить\n");
		GoToXY(cords.X, cords.Y);
		cout << "Строка успешно записана в файл." << endl;
		GoToXY(cords.X - 4, cords.Y + 2);
		cout << "Нажмите любую клавишу чтобы продолжить\n";  char t = _getch();
		system("cls");// Запись в файл произошла
	}
	else {
		system("cls");
		COORD cords = CalculateTextPosition("Ошибка открытия файла для записи.\n Нажмите любую клавишу чтобы продолжить\n");
		GoToXY(cords.X, cords.Y);
		cout << "Ошибка открытия файла для записи." << endl;
		GoToXY(cords.X - 4, cords.Y + 2);
		cout << "Нажмите любую клавишу чтобы продолжить\n";  char t = _getch();
		system("cls");//Возникла ошибка при открытии файла


	}
}
//Вывод списка запросов
void OutputPaidReportsAll(vector <PaidReport> reports, int mode) {


	for (PaidReport report : reports) {
		tuple<int, string, vector<string>, string> reportsInfo = report.GetAllInfoAboutReport();

		cout << get<0>(reportsInfo) << " ";
		cout << get<1>(reportsInfo) << " ";
		for (int i = 0; i < 8; i++)
		{
			cout << get<2>(reportsInfo)[i] << " ";
		}
		cout << get<3>(reportsInfo) << " ";
		cout << endl;
	}

	/*for (PaidReport report : reports) {
		tuple<int, string, vector<string>, string> reportsInfo = report.GetAllInfoAboutReport();

		cout << get<0>(reportsInfo) << " ";
		for (int i = 0; i < sizeof(get<2>(reportsInfo)); i++)
		{
			cout << get<2>(reportsInfo)[1] << " ";
		}
		cout << get<3>(reportsInfo) << " ";
		cout << endl;*/

}




// Метод сравнения для сортировки по id   РЕПОРТОВ
void SortPaidReportsById(vector<PaidReport>& reports) {
	sort(reports.begin(), reports.end(), [](PaidReport& a, PaidReport& b) {
		return a.GetId() < b.GetId();
		});
}
// Метод сравнения для сортировки по решенности
void SortPaidReportsBySolvedOrNot(vector<PaidReport>& reports) {
	sort(reports.begin(), reports.end(), [](PaidReport& a, PaidReport& b) {
		return a.GetSolvedOrNot() < b.GetSolvedOrNot();
		});
}
// Методы для запроса по критерию
vector<PaidReport> PaidReportRequestBySolvMode(vector<PaidReport>& reports, string solvMode) {
	vector<PaidReport> reportsafter;
	for (PaidReport report : reports)
	{
		if (report.GetSolvedOrNot() == solvMode)
		{
			reportsafter.push_back(report);
		}
	}
	return reportsafter;
}
vector<PaidReport> PaidReportRequestById(vector<PaidReport>& reports, int Id) {
	vector<PaidReport> reportsafter;
	for (PaidReport report : reports)
	{
		if (report.GetId() == Id)
		{
			reportsafter.push_back(report);
		}
	}
	return reportsafter;
}




// Метод для сортировки по имени  ЛОКАЦИЙ И АВТО
template <typename T>
void SortByName(vector<T>& items) {
	sort(items.begin(), items.end(), [](T& a, T& b) {
		return a.GetName() < b.GetName();
		});
}
// Метод для сортировки по штату
void SortByState(vector<Location>& reports) {
	sort(reports.begin(), reports.end(), [](Location& a, Location& b) {
		return a.GetState() < b.GetState();
		});
}
// Метод для сортировки по коду локации
void SortByCode(vector<Location>& reports) {
	sort(reports.begin(), reports.end(), [](Location& a, Location& b) {
		return a.GetZipCode() < b.GetZipCode();
		});
}



// Метод для сортировки вектора Car по дате продажи
// Лямбда-функция для преобразования строки даты в структуру tm и сравнения дат
auto compareDates = [](const Car& a, const Car& b) {//auto - для понимания того, что вернуть
	tm tm1 = {};
	tm tm2 = {};
	stringstream ss1(a.GetSaleDate());
	stringstream ss2(b.GetSaleDate());
	ss1 >> get_time(&tm1, "%a. %b %d, %Y");
	ss2 >> get_time(&tm2, "%a. %b %d, %Y");
	return mktime(&tm1) < mktime(&tm2);
};//надо протестирвать
void SortCarsBySaleDate(vector<Car>& cars) {
	// Сортировка вектора Car с использованием лямбда-функции
	sort(cars.begin(), cars.end(), compareDates);
}
//Метод для сортировки по дамагу
void SortByDamage(vector<Car>& reports) {
	sort(reports.begin(), reports.end(), [](Car& a, Car& b) {
		return a.GetPrimaryDate() < b.GetPrimaryDate();
		});
}
// Методы для запроса по критерию
vector<Car> CarByVin(vector<Car>& Cars, string vin) {
	vector<Car> Carsafter;
	for (Car Car : Cars)
	{
		if (Car.GetVin() == vin)
		{
			Carsafter.push_back(Car);
		}
	}
	return Carsafter;
}
// Запрос по лоту
vector<Car> CarByLot(vector<Car>& Cars, string lot) {
	vector<Car> Carsafter;
	for (Car Car : Cars)
	{
		if (Car.GetLot() == lot)
		{
			Carsafter.push_back(Car);
		}
	}
	return Carsafter;
}
// Запрос по buy now
vector<Car> CarByBuyNow(vector<Car>& Cars, string BuyNow) {
	vector<Car> Carsafter;
	for (Car Car : Cars)
	{
		if (Car.GetBuyNowCost() == BuyNow)
		{
			Carsafter.push_back(Car);
		}
	}
	return Carsafter;
}


string NameValidation() {
	string Name;

	return Name;
}//Доделать



int getConsoleWidth() {
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	int columns, rows;

	if (GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi)) {
		columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;
		rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
	}
	else {
		columns = 80; // Значение по умолчанию, если не удается определить ширину консоли
		rows = 25;
	}

	return columns;
}

vector<string> splitString(const string& str, int maxLength) {
	vector<string> result;
	stringstream ss(str);
	string line;
	string word;

	while (getline(ss, word, ' ')) {
		if (line.length() + word.length() > maxLength) {
			result.push_back(line);
			line.clear();
		}
		if (!line.empty()) {
			line += ' ';
		}
		line += word;
	}

	if (!line.empty()) {
		result.push_back(line);
	}

	return result;
}





enum class States {
	Login,
	Registration,
	Locations,
	LocationInfo,
	Cars,
	CarInfo,
	Meny1,
	Meny2,
	Meny3,
	Meny4,
	Meny5,
	ChangeAlignmentCars,
	ChangeAlignmentLocations,
	LocationsChoose,
	CarsChoose,
	PersonData,
	CalcaulateCostShipping,
	CarFind,

};

#define Login States::Login
#define Registration States::Registration
#define Locations States::Locations
#define LocationInfo States::LocationInfo
#define Cars States::Cars
#define CarInfo States::CarInfo
#define Meny1 States::Meny1
#define Meny2 States::Meny2
#define Meny3 States::Meny3
#define Meny4 States::Meny4
#define Meny5 States::Meny5
#define PersonData States::PersonData
#define ChangeAlignmentCars States::ChangeAlignmentCars
#define ChangeAlignmentLocations States::ChangeAlignmentLocations
#define LocationsChoose States::LocationsChoose
#define CarsChoose States::CarsChoose
#define CalcaulateCostShipping States::CalcaulateCostShipping
#define CarFind States::CarFind

//Переменные для работы кода
vector<Car> cars;
vector<Location> locations;
vector<PaidReport> reports;
vector<User> users;
vector <Car> FindCars;
Car ChoosenCar;
COORD cordsempty;

void UserTest() {


	States State;

	//cars = readCarsFromFile("FL 32771.txt");//Вектор для хранения автомобилей
	////Сохраним данные об локации в отделюную переменную
	//string infoAboutLocation = cars[0].GetName();
	////И удалим ее из основного вектора
	//cars.erase(cars.begin());


	users = readUsersFromFile("Users.txt");
	//OutputUsersAll(users);
	char ch; string login = "", password = "";
	User persondata = User(1, "", "", "", "");
	locations = readLocationsFromFile("List_Of_Jards.txt");


	State = Meny1;

	while (true) {
	Start:
		system("cls");
		if (State == Meny1) {
			system("cls");
			COORD cords = CalculateTextPosition("Выберите, как войти");
			GoToXY(cords.X, cords.Y);
			cout << "Выберите, как войти" << endl;
			GoToXY(cords.X, ++cords.Y);
			cout << "1.Вход" << endl;
			GoToXY(cords.X, ++cords.Y);
			cout << "2.Регистрация" << endl;
			int t = _getch() - 48; cout << t;
			switch (t)
			{
			case 1:
				State = Login;
				goto Start;
				break;
			case 2:
				State = Registration;
				goto Start;
				break;
			default:
				GoToXY(cords.X, ++cords.Y);
				cout << "Такой клавиши нет";
				GoToXY(cords.X - 8, ++cords.Y);
				cout << "Нажмите любую клавишу чтобы продолжить\n";  char t = _getch();
				system("cls");
				break;
			}

		}
		if (State == Login)
		{
		Identifications:
			COORD cords = CalculateTextPosition("Введите логин");
			GoToXY(cords.X, cords.Y++);

			cout << "Введите логин: ";

			//Ввод логина
			while (true) {
				ch = _getch(); // Считывание клавиши без ожидания нажатия Enter
				if (ch == 27) {// Проверка на Esc
					system("cls");

					GoToXY(cords.X, cords.Y++);
					cout << "Выход.";
					GoToXY(cords.X - 15, cords.Y + 2);
					cout << "Нажмите любую клавишу чтобы продолжить\n";  char t = _getch();
					State = Meny1;
					goto Start;

				}
				else if (ch == 8) {// Проверка на BackSpace
					if (!login.empty()) {//проверка на пустой пароль
						cout << "\b \b"; // Удаление последнего символа из консоли
						login.pop_back(); // Удаление последнего символа из login

					}
				}
				else if (ch == 13) {// Проверка на Enter
					break;  // Завершение ввода при нажатии клавиши Enter
				}
				else {
					if (size(login) < 16)
					{
						login += ch;  // Добавление символа 
						cout << ch;  // Вывод символа
					}


				}
			}

			// Cверка с существующими логинами(идентификация)
			for (User user : users)
			{
				if (login == user.GetName())
				{
					persondata = user;
					break;
				}
			}
			if (persondata.GetName() == "")
			{
				system("cls");
				GoToXY(cords.X, cords.Y);
				cout << "Вы ввели неправильный логин\n";
				login = ""; password = "";

				goto Identifications;
			}




			// Ввод пароля

			GoToXY(cords.X, cords.Y);
			cout << "                                               ";
			GoToXY(cords.X, ++cords.Y);
			cout << "Введите пароль: ";
			GoToXY(cords.X, ++cords.Y);
			while (true) {
				ch = _getch(); // Считывание клавиши без ожидания нажатия Enter
				if (ch == 27) {// Проверка на Esc
					cout << endl << "Выход из входа." << endl;
					system("cls");
					persondata = User(1, "", "", "", "");
					login = ""; password = "";

					goto Identifications;
				}
				else if (ch == 8) {// Проверка на BackSpace

					if (!password.empty()) {//проверка на пустой пароль
						cout << "\b \b"; // Удаление последнего символа из консоли
						password.pop_back(); // Удаление последнего символа из login
					}
				}
				else if (ch == 13) {// Проверка на Enter
					cout << "\b \b" << "*";
					cout << endl;
					break;  // Завершение ввода при нажатии клавиши Enter
				}
				else {
					if (password.empty())
					{
						password += ch;  // Добавление символа к переменной password
						cout << ch;  // Вывод символа
					}
					else
					{
						if (size(password) < 30)
						{
							cout << "\b \b" << "*";
							password += ch;  // Добавление символа к переменной password
							cout << ch;  // Вывод символа
						}
					}
				}
			}

			// Cверка с паролем (аутентификации)
			if (password != persondata.GetPassword())
			{
				system("cls");
				GoToXY(cords.X, cords.Y - 2);

				cout << "Вы ввели неправильный пароль, войдите еще раз\n";
				persondata = User(1, "", "", "", "");
				login = ""; password = "";
				goto Identifications;
			}
			login = password = "";

			State = Meny2;

		}
		if (State == Registration)
		{
			persondata = UpdateUserField();
			if (persondata.GetName() != "")
			{
				users.push_back(persondata);
				InsertUserToFile(users); cout << "yes";
			}
			persondata = User(1, "", "", "", "");
			State = Meny1;
			cout << "no";
		}
		if (State == Meny2) {
			system("cls");
			COORD cords = CalculateTextPosition("Нажмите любую клавишу для продолжения");
			GoToXY(cords.X, cords.Y);
			cout << "Вы вошли как " << persondata.GetName();
			GoToXY(cords.X - 8, ++cords.Y);
			cout << "Нажмите любую клавишу чтобы продолжить\n";  char t = _getch();
			system("cls");
			while (true) {
			Start2:
				system("cls");
				if (State == Meny2)
				{
					COORD cords = CalculateTextPosition("1.Посмотреть контактные данные");
					GoToXY(cords.X, cords.Y);
					cout << "Выберите пункт меню:";
					GoToXY(cords.X, ++cords.Y);
					cout << "1.Посмотреть контактные данные";
					GoToXY(cords.X, ++cords.Y);
					cout << "2.Вывети список локаций";
					GoToXY(cords.X, ++cords.Y);
					cout << "3.Рассчитать стоимость привоза авто в РБ";
					GoToXY(cords.X, ++cords.Y);
					cout << "4.Выйти в меню входа";
					GoToXY(cords.X, ++cords.Y);

					char t = _getch(); cout << t;
					switch (t)
					{
					case '1':
						State = PersonData;
						goto Start2;
						break;
					case '2':
						State = Locations;
						goto Start2;
						break;
					case '3':
						State = CalcaulateCostShipping;
						goto Start2;
						break;
					case '4':
						State = Meny1;
						persondata = User(1, "", "", "", "");
						goto Start;
						break;
					default:
						GoToXY(cords.X, ++cords.Y);
						cout << "Такой клавиши нет";
						GoToXY(cords.X - 8, ++cords.Y);
						cout << "Нажмите любую клавишу чтобы продолжить\n";  char t = _getch();
						system("cls");
						goto Start2;
					}
				}
				if (State == PersonData) {
					persondata.OutPutUserInfo();
					State = Meny2;
				}
				if (State == Locations) {
					cords = OutputLocationsInfo(locations);
					GoToXY(cords.X, cords.Y);
					cout << "1.Выбрать локацию";
					GoToXY(cords.X, ++cords.Y);
					cout << "2.Изменить сортировку";
					GoToXY(cords.X, ++cords.Y);
					cout << "3.Выйти в меню аккаунта";
					GoToXY(cords.X, ++cords.Y);
					char t = _getch(); cout << t;
					switch (t)
					{
					case '1':
						State = LocationsChoose;
						goto Start2;
						break;
					case '2':
						State = ChangeAlignmentLocations;
						goto Start2;
						break;
					case '3':
						State = Meny2;
						goto Start2;
						break;
					default:
						GoToXY(cords.X, ++cords.Y);
						cout << "Такой клавиши нет";
						GoToXY(cords.X - 8, ++cords.Y);
						cout << "Нажмите любую клавишу чтобы продолжить\n";  char t = _getch();
						system("cls");
						goto Start2;
					}


					State = Meny3;
					goto Start2;
				}
				if (State == CalcaulateCostShipping)
				{
					//COORD cords = OutputInfoOf1Location(locations[LocationChoose]);
					COORD cords = CalculateTextPosition("Нажмите любую клавишу для продолжения");

					calculateShippingCost();
					GoToXY(cords.X - 6, cords.Y + 5);
					cout << "Нажмите любую клавишу чтобы продолжить\n";  char t = _getch();
					State = Meny2;
					goto Start2;
				}

				//Сортировка
				if (State == ChangeAlignmentLocations) {
					cords = OutputLocationsInfo(locations);
					GoToXY(cords.X, cords.Y);
					cout << "1.Отсортировать по имени";
					GoToXY(cords.X, ++cords.Y);
					cout << "2.по штату";
					GoToXY(cords.X, ++cords.Y);
					cout << "3.по коду локации";
					GoToXY(cords.X, ++cords.Y);
					cout << "4.Выйти в выбора локации без изменения сортировки";
					GoToXY(cords.X, ++cords.Y);

					char t = _getch(); cout << t;
					switch (t)
					{
					case '1':
						SortByName(locations);
						State = Locations;
						break;
					case '2':
						SortByState(locations);
						State = Locations;
						break;
					case '3':
						SortByCode(locations);
						State = Locations;
						break;
					case '4':

						system("cls");
						State = Locations;
						break;
					default:
						GoToXY(cords.X, ++cords.Y);
						cout << "Такой клавиши нет";
						GoToXY(cords.X - 8, ++cords.Y);
						cout << "Нажмите любую клавишу чтобы продолжить\n";  char t = _getch();
						system("cls");
						State = Locations;
					}
					goto Start2;
				}
				if (State == LocationsChoose) {
					cords = OutputLocationsInfo(locations);
					GoToXY(cords.X, cords.Y++);
					cout << "Выберите локацию (напишите номер) ";
					int LocationChoose;
					cin >> LocationChoose;
					string s = "locations\\" + locations[LocationChoose - 1].GetZipCode() + ".txt"; cout << s;
					State = Meny4;
					cars = readCarsFromFile(s);
					string Info = cars[0].GetName();
					cars.erase(cars.begin());
					while (true) {
					Start3:
						system("cls");

						if (State == Meny4)
						{
							COORD cords = CalculateTextPosition("1.Вывести информацию об локации");
							GoToXY(cords.X, cords.Y);
							cout << "Выберите пункт меню:";
							GoToXY(cords.X, ++cords.Y);
							cout << "1.Вывести информацию об локации";
							GoToXY(cords.X, ++cords.Y);
							cout << "2.Вывети список автомобилей";
							GoToXY(cords.X, ++cords.Y);
							cout << "3.Выйти в меню выбора локации";
							GoToXY(cords.X, ++cords.Y);

							char t = _getch(); cout << t;
							switch (t)
							{
							case '1':
								State = LocationInfo;
								goto Start3;
								break;
							case '2':
								State = Cars;
								goto Start3;
								break;
							case '3':
								State = Meny2;
								//persondata = User(1, "", "", "", "");
								goto Start2;
								break;
							default:
								GoToXY(cords.X, ++cords.Y);
								cout << "Такой клавиши нет";
								GoToXY(cords.X - 8, ++cords.Y);
								cout << "Нажмите любую клавишу чтобы продолжить\n";  char t = _getch();
								system("cls");
								goto Start3;
							}
						}
						if (State == LocationInfo)
						{
							COORD cords = OutputInfoOf1Location(locations[LocationChoose - 1]);
							GoToXY(cords.X, cords.Y);
							COORD position = CalculateTextPosition("Below are the cities that the US Postal Service accepts for the ZIP code 32824. This code is specific toarea, be sure to use this ZIP code to ensure that you");

							int consoleWidth = getConsoleWidth();
							int maxLineLength = consoleWidth / 2;

							vector<string> shortStrings = splitString(Info, maxLineLength);

							for (const auto& line : shortStrings) {
								GoToXY(cords.X, cords.Y++);
								cout << line;
							}


							/*GoToXY(position.X, position.Y);
							cout << Info;
							GoToXY(cords.X, cords.Y++);*/
							cout << "Нажмите любую клавишу чтобы продолжить\n";  char t = _getch();
							State = Meny4;
							goto Start3;
						}
						if (State == Cars)
						{
							system("cls");

							COORD cords = OutputCarsInfo(cars, cordsempty);
							GoToXY(cords.X, cords.Y);
							cout << "1.Выбрать автомобиль";
							GoToXY(cords.X, ++cords.Y);
							cout << "2.Изменить сортировку";
							GoToXY(cords.X, ++cords.Y);
							cout << "3.Поиск автомобиля по критерию";
							GoToXY(cords.X, ++cords.Y);
							cout << "4.Выйти в меню локации";
							GoToXY(cords.X, ++cords.Y);
							char t = _getch(); cout << t;
							switch (t)
							{
							case '1':
								State = CarsChoose;
								goto Start4;
								break;
							case '2':
								State = ChangeAlignmentCars;
								goto Start4;
								break;
							case '3':
								State = CarFind;
								goto Start4;
								break;
							case '4':
								State = Meny2;
								goto Start3;
								break;
							default:
								GoToXY(cords.X, ++cords.Y);
								cout << "Такой клавиши нет";
								GoToXY(cords.X - 8, ++cords.Y);
								cout << "Нажмите любую клавишу чтобы продолжить\n";  char t = _getch();
								system("cls");
								goto Start3;
							}
							не хватает входа в автомобиль, выбора авто, в поиске авто вход в авто если 1,

								while (true) {
								Start4:
									system("cls");

									if (State == CarsChoose)
									{
										COORD cords = OutputCarsInfo(cars, cordsempty);
										GoToXY(cords.X, cords.Y);
										cout << "Выберите локацию (напишите номер) ";
										int CarNumber;
										cin >> CarNumber;
										ChoosenCar = cars[CarNumber];

									}
									//Поиск
									if (State == CarFind) {
										cords = OutputCarsInfo(cars, cordsempty);
										GoToXY(cords.X, cords.Y);
										cout << "1.Поиск по норему лота ";
										GoToXY(cords.X, ++cords.Y);
										cout << "2.По вин коду";
										GoToXY(cords.X, ++cords.Y);
										cout << "3.По цене (buy now";
										GoToXY(cords.X, ++cords.Y);
										cout << "4.Выйти в выбора автомобиля без изменения сортировки";
										GoToXY(cords.X, ++cords.Y);
										string str;
										char t = _getch(); cout << t;
										switch (t)
										{
										case '1':
											GoToXY(cords.X, ++cords.Y);
											cout << "Введите лот";
											GoToXY(cords.X, ++cords.Y);
											cin >> str;
											FindCars = CarByLot(cars, str);
											break;
										case '2':
											GoToXY(cords.X, ++cords.Y);
											cout << "Введите лот";
											GoToXY(cords.X, ++cords.Y);
											cin >> str;
											FindCars = CarByVin(cars, str);
											break;
										case '3':
											GoToXY(cords.X, ++cords.Y);
											cout << "Введите лот";
											GoToXY(cords.X, ++cords.Y);
											cin >> str;
											FindCars = CarByBuyNow(cars, str);
											break;
										case '4':
											system("cls");
											break;
										default:
											GoToXY(cords.X, ++cords.Y);
											cout << "Такой клавиши нет";
											GoToXY(cords.X - 8, ++cords.Y);
											cout << "Нажмите любую клавишу чтобы продолжить\n";  char t = _getch();
											system("cls");
										}
										if (size(FindCars) == 1)
										{
											ChoosenCar = FindCars[0];
											system("cls");
											//загрузка
											COORD cords = CalculateTextPosition("По вашему запросу был найден 1 автомобиль");
											GoToXY(cords.X, cords.Y);
											cout << "По вашему запросу был найден 1 автомобиль";
											GoToXY(cords.X - 8, ++cords.Y);
											cout << "Нажмите любую клавишу чтобы продолжить\n";  char t = _getch();
											system("cls");
											State = Meny5;
											goto Start4;

										}
										else if (size(FindCars) > 1)
										{
											system("cls");
											//загрузка
											COORD cords = CalculateTextPosition("По вашему запросу было найдено 4 автомобиля ");
											cords.Y = cords.Y - 15;
											GoToXY(cords.X, cords.Y);
											cout << "По вашему запросу было найдено " << size(FindCars) << " автомобилей";
											cords = OutputCarsInfo(FindCars, cords);
											GoToXY(cords.X - 8, ++cords.Y);
											cout << "Нажмите любую клавишу чтобы продолжить\n";  char t = _getch();
											//system("cls");
										}

										FindCars.clear();
										State = Cars;
										goto Start3;
									}

									//Сортировка
									if (State == ChangeAlignmentCars) {
										cords = OutputCarsInfo(cars, cordsempty);
										GoToXY(cords.X, cords.Y);
										cout << "1.Отсортировать по имени";
										GoToXY(cords.X, ++cords.Y);
										cout << "2.по дате продажи";
										GoToXY(cords.X, ++cords.Y);
										cout << "3.по виду урона";
										GoToXY(cords.X, ++cords.Y);
										cout << "4.Выйти в выбора автомобиля без изменения сортировки";
										GoToXY(cords.X, ++cords.Y);

										char t = _getch(); cout << t;
										switch (t)
										{
										case '1':
											SortByName(cars);
											break;
										case '2':
											SortCarsBySaleDate(cars);
											break;
										case '3':
											SortByDamage(cars);
											break;
										case '4':
											system("cls");
											break;
										default:
											GoToXY(cords.X, ++cords.Y);
											cout << "Такой клавиши нет";
											GoToXY(cords.X - 8, ++cords.Y);
											cout << "Нажмите любую клавишу чтобы продолжить\n";  char t = _getch();
											system("cls");
										}
										State = Cars;
										goto Start3;
									}
								}




						}

						GoToXY(cords.X, cords.Y++);
						cout << "Нажмите любую клавишу чтобы продолжить\n";  char t = _getch();
						system("cls");
						goto Start2;
					}


				}
				locations = readLocationsFromFile("List_Of_Jards.txt");

				OutputLocationsInfo(locations);


				/*COORD cords = CalculateTextPosition("Вы вошли как влаолвоалв");
				GoToXY(cords.X, cords.Y);
				cout << "Вы вошли как " <<persondata.GetName();
				GoToXY(cords.X, ++cords.Y);
				cout << "Вход" << endl;
				GoToXY(cords.X, ++cords.Y);
				cout << "Регистрация" << endl;
				int t = _getch() - 48;
				switch (t)
				{
				case 1:
					State = Login;
					goto Start;
					break;
				case 2:
					State = Registration;
					goto Start;
					break;
				default:
					State =Meny1;
					goto Start;
					break;
				}*/

			}

		}
	}
	/*while (true) {
			ch = _getch(); // Считывание клавиши без ожидания нажатия Enter
			if (ch == 27) {// Проверка на Esc
				cout << endl << "Выход из ввода логина." << endl;
				system("cls");
				goto Start;
			}
			else if (ch == 8) {// Проверка на BackSpace
				if (!login.empty()) {
					cout << "\b \b"; // Удаление последнего символа из консоли
					login.pop_back(); // Удаление последнего символа из login
				}
			}
			else if (ch == 13) {// Проверка на Enter
				cout << endl;
				break;  // Завершение ввода при нажатии клавиши Enter
			}
			else {
				login += ch;  // Добавление символа к переменной login
				cout << ch;  // Вывод * вместо введенных символов
			}
		}*/



		//State = static_cast<States>((int)_getch() - 49);

		/*методя для репортов
		reports = readPaidReportsFromFile("PaidReports.txt");
		vector<PaidReport> reportsAfterReqest = PaidReportRequestBySolvMode(reports,"problem");
		OutputPaidReportsAll(reportsAfterReqest, 0);*/
		/*
		работа с юзерами
		users = readUsersFromFile("Users.txt");
		OutputUsersAll(users);
		*/



		//string t;
		//cin >> t;



		/*locations = readLocationsFromFile("List_Of_Jards.txt");

		// Выводим информацию о каждом автомобиле после считывания
		OutputLocationsInfo(locations);



		cout << "Выберите из списка:\n";


		string s = locations[_getch() - 48].GetZipCode() + ".txt";

		string s = locations[t].GetZipCode() + ".txt";

		OutputCarsInfo(carsFromLocation);

		SortCarsBySaleDate(carsFromLocation);
		OutputCarsInfo(carsFromLocation);*/
}



int main() {
	MainSettings();
	try {
		UserTest();
	}
	catch (const exception& e) {
		cerr << "Исключение: " << e.what() << endl;
	}
}



//#include <iostream>
//
//using namespace std;
//int main()
//{
//     cout << "Hello World!\n";
//
//}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.








