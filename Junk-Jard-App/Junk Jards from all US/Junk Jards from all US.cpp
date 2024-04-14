// Junk Jards from all US.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//


#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <conio.h>

using namespace std;
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
// Класс для хранения данных об 1 автомобиле
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
	Car(const  string  name, const  string  primaryDamage, const  string  saleDate,
		const  string  auctionStartTime, const  string  vin, const  string  lot,
		const  string  buyNowCost, const  string  link)
		: Name(name), PrimaryDamage(primaryDamage), SaleDate(saleDate), AuctionStartTime(auctionStartTime), Vin(vin), Lot(lot), BuyNowCost(buyNowCost), Link(link) {}
	// метод для вывода данных авто 
	vector<string> GetAllInfoAboutCar()
	{
		return { Name, PrimaryDamage, SaleDate, AuctionStartTime, Vin, Lot, BuyNowCost, Link };
	}
};
vector<Car> readCarsFromFile(const  string filename) {
	ifstream file(filename); // Открываем файл с данными
	vector<Car> cars;

	//Получилось открыть файл?
	if (file.is_open()) {
		string line;
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
int main() {
	setlocale(LC_ALL, "ru_RU.UTF-8");

	vector<Location> locations = readLocationsFromFile("List_Of_Jards.txt");

	// Выводим информацию о каждом автомобиле после считывания
	for (Location location : locations) {
		vector<string> locationsInfo = location.GetAllInfoAboutLocation();
		for (string info : locationsInfo) {
			cout << info << " ";
		}
		cout << endl;
	}




	cout << "Введите номер локации :";

	int i = _getch();
	cout << locations[i - 48].GetZipCode() + ".txt";

	string s = locations[i-48].GetZipCode()+".txt";
	vector<Car> carsFromLocation = readCarsFromFile("FL 32824.txt");

	// Выводим информацию о каждом автомобиле после считывания
	for (Car car : carsFromLocation) {
		vector<string> carInfo = car.GetAllInfoAboutCar();
		for (string info : carInfo) {
			cout << info << " ";
		}
		cout << endl;
	}
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
