// Junk Jards from all US.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

/*
не вавтает Входа админ, пользователь
сортировки
заказа платного осмортра
*/


Не хватает паролья в User


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
using namespace std;


//Последнее id для юзеров
int LastId = 0;


//Основные настройки
void MainSettings() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	//	wcout.imbue(std::locale("Russian_Russia.UTF-8"));
}

//Класс для хранения данных об локации
class Location {
	// Инкапсуляция данных для безопасности
private:
	string Name;
	string Address;
	string City;
	string ZipCode;
public:
	// Конструктор класса для удобного создания и инициализации объектов
	Location(const  string name, const  string  address, const  string  city, const  string zipcode)
		: Name(name), Address(address), City(city), ZipCode(zipcode) {}
	// метод для вывода данных авто 
	vector<string> GetAllInfoAboutLocation()
	{
		return { Name, Address, City, ZipCode };
	}
	string FormStringToAddToFile()
	{
		string stroke;

		stroke = Name + ";" + Address + ";" + City + ";" + ZipCode;

		return stroke;
	}
	string GetZipCode() {
		return ZipCode;
	}
};
//Функция для вывода локаций из файла в вектор
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

		cout << "Ошибка открытия файла.\n";
	}

	return Locations;
}
//Фукнция для добавления поля в список локаций
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
		cout << "Строка успешно записана в файл." << std::endl;//Ура, запись произошла
	}
	else {
		cout << "Ошибка открытия файла для записи." << std::endl;//Возникла ошибка при открытии файла

	}
}
//Вывод списка локаций
void OutputLocationsInfo(vector <Location> locations) {
	for (Location location : locations) {
		vector<string> locationsInfo = location.GetAllInfoAboutLocation();
		for (string info : locationsInfo) {
			cout << info << " ";
		}
		cout << endl;
	}
}




//Класс для хранения данных об автомобиле
class Car {
	// Инкапсуляция данных для безопасности
private:
	string  Name;
	string PrimaryDamage;
	string SaleDate;
	string AuctionStartTime;
	string Vin;
	string Lot;
	string BuyNowCost;
	string Link;
public:
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
	void CoutAdvancedeInfo()
	{
		printf("Name: %s\n", Name.c_str());
		printf("Primary Damage: %s\n", PrimaryDamage.c_str());
		printf("Sale Date: %s\n", SaleDate.c_str());
		printf("Auction Start Time: %s\n", AuctionStartTime.c_str());
		printf("Vin: %s\n", Vin.c_str());
		printf("Lot: %s\n", Lot.c_str());
		printf("Buy Now Cost: %s\n", BuyNowCost.c_str());
		printf("Link: %s\n", Link.c_str());

	}

	string GetName() {
		return Name;
	}

	void OrderAPaidReport() {

	}

};
//Функция для вывода списка об автомобилях из файла
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

		cout << "Ошибка открытия файла.\n";
	}

	return cars;
}
//Фукнция для добавления поля в список локаций
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
		cout << "Строка успешно записана в файл." << std::endl;//Ура, запись произошла
	}
	else {
		cout << "Ошибка открытия файла для записи." << std::endl;//Возникла ошибка при открытии файла

	}
}
//Вывод списка авто
void OutputCarsInfo(vector <Car> Cars) {
	for (Car car : Cars) {
		vector<string> carInfo = car.GetAllInfoAboutCar();
		//car.CoutAllInfo();
		car.CoutAdvancedeInfo();
		cout << endl;
	}
}
// Функция для получения значения из списка
template <size_t N>
int getValueFromList(const string(&options)[N]) {
	for (size_t i = 0; i < N; i++) {
		cout << i + 1 << ". " << options[i] << endl;
	}

	int choice;
	cout << "Введите номер: ";
	cin >> choice;

	// Проверка на правильность ввода
	if (choice < 1 || choice > N) {
		cout << "Некорректный выбор. Пожалуйста, выберите значение из списка." << endl;
		return getValueFromList(options);
	}

	return choice;
}
// Примеры списков возможных вариантов
const string carTypes[] = { "Седан", "Хэтчбек", "Купе", "Кабриолет", "Кроссовер", "Пикап", "Внедорожник", "Минивэн", "Грузовик", "Кей-кар", "Мотоцикл", "Квадроцикл", "Багги", "Гидроцикл" };
const string engineTypes[] = { "Электро", "Гибрид", "Бензин", "Дизель" };
const string productionYears[] = { "менее года", "до 3 лет", "от 3 до 5 лет", "от 5 до 30 лет", "более 30 лет (раритет)" };
const string customsTypes[] = { "полная", "льготная" };
// Функция для рассчета стоимости привоза автомобиля
void calculateShippingCost() {

	// Получение информации о типе автомобиля, типе двигателя, годе производства и других параметрах
	double engineVolume, carCost;

	// Ввод данных пользователь
	cout << "Выберите тип автомобиля:" << endl;
	int carTypeIndex = getValueFromList(carTypes);

	cout << "Выберите тип двигателя:" << endl;
	int engineTypeIndex = getValueFromList(engineTypes);

	cout << "Выберите год производства автомобиля:" << endl;
	int productionYearIndex = getValueFromList(productionYears);

	cout << "Введите объем двигателя автомобиля: ";
	cin >> engineVolume;

	cout << "Введите стоимость автомобиля в долларах: ";
	cin >> carCost;

	system("cls");

		// Расчет стоимости привоза
	double totalCost = 1.1; cout << carTypeIndex << " byltrc";
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


	cout << "Cтоимость авто: " << carCost << "$" << endl;
	cout << "Аукционный сбор: " << fixed << setprecision(2) << carCost / 110 << "$" << endl;
	cout << "Цена доставки : " << totalCost << "$" << endl;
	cout <<	"Итоговая цена : " << totalCost+carCost << "$" << endl;
}



//Класс для пользователей
class User {
	// Инкапсуляция данных для безопасности
private:
	int Id;
	string Name;
	string Email;
	string PhoneNumber;
public:
	// Конструктор класса для удобного создания и инициализации объектов
	User(const int id, const  string name, const  string  email, const  string  phonenumber)
		: Id(id), Name(name), Email(email), PhoneNumber(phonenumber) {}
	// метод для вывода данных авто 
	tuple<int,string,string,string> GetAllInfoAboutReport()
	{
		return { make_tuple(Id,Name, Email, PhoneNumber)};
	}
	string FormStringToAddToFile()
	{
		string stroke;

		stroke = Id+";" + Name + ";" + Email + ";" + PhoneNumber;

		return stroke;
	}
	~User() {}
};
//Функция для вывода пользователей из файла в вектор
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
			User user(id, UsersInfo[0], UsersInfo[1], UsersInfo[2]);
			Users.push_back(user);

		}
		file.close();
	}
	else {//Не получилось

		cout << "Ошибка открытия файла.\n";
	}

	return Users;
}
//Фукнция для добавления поля в список пользователей
User UpdateUserField() {

	//Очистим консоль
	system("cls");

	//Массив для ввода значений
	string* InfoOfReport = new string[3]; int Id;

	//Заполним массив
	Id = ++LastId;
	cout << "Введите название";
	cin >> InfoOfReport[0];
	cout << "Введите адрес почты";
	cin >> InfoOfReport[1];
	cout << "Введите номер телефона +375";
	cin >> InfoOfReport[2];

	//Вернем готовый объект для добавления в вектор
	return User(Id, InfoOfReport[0], InfoOfReport[1], InfoOfReport[2]);
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

	ofstream OutputToFile("List_Of_Jards.txt"); // Открываем файл с данными
	if (OutputToFile.is_open()) {//Проверим, можно ли открыть файл
		OutputToFile << s; //Вводим в файл
		OutputToFile.close();//Закроем файл
		cout << "Строка успешно записана в файл." << std::endl;//Ура, запись произошла
	}
	else {
		cout << "Ошибка открытия файла для записи." << std::endl;//Возникла ошибка при открытии файла

	}
}
//Вывод списка пользователей
void OutputUsersAll(vector <User> reports) {
	
		for (User report : reports) {
			tuple<int, string, string, string> reportsInfo = report.GetAllInfoAboutReport();

			cout << get<0>(reportsInfo) << " ";
			cout << get<2>(reportsInfo) << " ";
			cout << get<3>(reportsInfo) << " ";
			cout << endl;
		}
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
	// Конструктор класса для удобного создания и инициализации объектов
	PaidReport(const int id, const string solved, const Car car, const std::string answer)
		: Id(id), SolvedOrNot(solved), Title(car), Answer(answer) {}
	// метод для вывода данных авто 
	tuple<int, string, vector<string>, string> GetAllInfoAboutReport()
	{
		return { make_tuple(Id,SolvedOrNot, Title.GetAllInfoAboutCar(), Answer) };
	}
	string FormStringToAddToFile()
	{
		string stroke;

		stroke = Id + ";" + SolvedOrNot + ";" + Title.FormStringToAddToFile()+ ";" + Answer;

		return stroke;
	}
	~PaidReport() {}
};
//Функция для вывода запросов из файла в вектор
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

		cout << "Ошибка открытия файла.\n";
	}

	return PaidReports;
}
//Фукнция для добавления поля в список запросов
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
		cout << "Строка успешно записана в файл." << std::endl;//Ура, запись произошла
	}
	else {
		cout << "Ошибка открытия файла для записи." << std::endl;//Возникла ошибка при открытии файла

	}
}
//Вывод списка запросов
void OutputPaidReportsAll(vector <PaidReport> reports, int mode) {

	if (mode = 0)
	{
		for (PaidReport report : reports) {
			tuple<int, string, vector<string>, string> reportsInfo = report.GetAllInfoAboutReport();

			cout << get<0>(reportsInfo) << " ";
			for (int i = 0; i < sizeof(get<2>(reportsInfo)); i++)
			{
				cout << get<2>(reportsInfo)[1] << " ";
			}
			cout << get<3>(reportsInfo) << " ";
			cout << endl;
		}
	}
	for (PaidReport report : reports) {
		tuple<int, string, vector<string>, string> reportsInfo = report.GetAllInfoAboutReport();

		cout << get<0>(reportsInfo) << " ";
		for (int i = 0; i < sizeof(get<2>(reportsInfo)); i++)
		{
			cout << get<2>(reportsInfo)[1] << " ";
		}
		cout << get<3>(reportsInfo) << " ";
		cout << endl;
	}
}


//Переменные для работы кода
vector<Car> carsFromLocation;
vector<Location> locations;
vector<PaidReport> reports;
vector<User> users;

void test() {

	users = readUsersFromFile("Users.txt");
	OutputUsersAll(users);
	

	/*string t;
	cin >> t;



	locations = readLocationsFromFile("List_Of_Jards.txt");

	// Выводим информацию о каждом автомобиле после считывания
	OutputLocationsInfo(locations);



	cout << "Выберите из списка:\n";


	string s = locations[_getch() - 48].GetZipCode() + ".txt";







	//Вектор для хранения автомобилей
	carsFromLocation = readCarsFromFile(s);
	//Сохраним данные об локации в отделюную переменную
	string infoAboutLocation = carsFromLocation[0].GetName();
	//И удалим ее из основного вектора
	carsFromLocation.erase(carsFromLocation.begin());




	OutputCarsInfo(carsFromLocation);*/
}



int main() {
	MainSettings();
	test();

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


