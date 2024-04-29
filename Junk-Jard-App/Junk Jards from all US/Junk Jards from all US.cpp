// Junk Jards from all US.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//




//Проблема — ввод русский не воспринимает, надо ли это решать
//Добавить - ввод сохранение в файл (метод подготовлен)


//Различные библиотеки
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <conio.h>
#include <Windows.h>
using namespace std;

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


Location UpdateLocationField() {

	//Очистим консоль
	system("cls");

	//Масси для ввода значений
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
	};
	vector<Car> readCarsFromFile(const  string filename) {
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

	vector<Car> carsFromLocation;
	vector<Location> locations;

	int main() {

		SetConsoleCP(1251);
		SetConsoleOutputCP(1251);
		//	wcout.imbue(std::locale("Russian_Russia.UTF-8"));

		locations = readLocationsFromFile("List_Of_Jards.txt");

		// Выводим информацию о каждом автомобиле после считывания
		for (Location location : locations) {
			vector<string> locationsInfo = location.GetAllInfoAboutLocation();
			for (string info : locationsInfo) {
				cout << info << " ";
			}
			cout << endl;
		}

		cout << "Выберите из списка:\n";


		string s = locations[_getch() - 48].GetZipCode() + ".txt";






		//Добавим поле в вектор
		locations.push_back(UpdateLocationField());

		//Перенесем текст в файл
		InsertLocationsToFile(locations);



		/*




		// Выводим информацию о каждом автомобиле после считывания
		for (Location location : locations) {
			vector<string> locationsInfo = location.GetAllInfoAboutLocation();
			for (string info : locationsInfo) {
				cout << info << " ";
			}
			cout << endl;
		}


		//Вектор для хранения автомобилей
		carsFromLocation = readCarsFromFile(s);
		//Сохраним данные об локации в отделюную переменную
		string infoAboutLocation = carsFromLocation[0].GetName();
		carsFromLocation.erase(carsFromLocation.begin());

		// Выводим информацию о каждом автомобиле после считывания
		for (Car car : carsFromLocation) {
			vector<string> carInfo = car.GetAllInfoAboutCar();
			car.CoutAllInfo();
			car.CoutAdvancedeInfo();
			cout << endl;
		}
		*/

		return 0;
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
