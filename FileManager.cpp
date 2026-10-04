#include "FileManager.h"
#include <fstream>

bool FileManager::LoadBrands(const char* filename, BrandList& brandList) {
    std::ifstream file(filename, std::ios::binary);
    if (!file.is_open()) {
        return false;
    }

    brandList.Clear();

    // Читаем количество записей
    int count = 0;
    file.read(reinterpret_cast<char*>(&count), sizeof(int));

    // Читаем записи
    for (int i = 0; i < count; i++) {
        CarBrand brand;
        file.read(reinterpret_cast<char*>(&brand), sizeof(CarBrand));
        brandList.Add(brand);
    }

    file.close();
    return true;
}

bool FileManager::LoadCars(const char* filename, CarList& carList) {
    std::ifstream file(filename, std::ios::binary);
    if (!file.is_open()) {
        return false;
    }

    carList.Clear();

    // Читаем количество записей
    int count = 0;
    file.read(reinterpret_cast<char*>(&count), sizeof(int));

    // Читаем записи
    for (int i = 0; i < count; i++) {
        Car car;
        file.read(reinterpret_cast<char*>(&car), sizeof(Car));
        carList.Add(car);
    }

    file.close();
    return true;
}

bool FileManager::SaveBrands(const char* filename, BrandList& brandList) {
    std::ofstream file(filename, std::ios::binary);
    if (!file.is_open()) {
        return false;
    }

    // Записываем количество элементов
    int count = brandList.GetCount();
    file.write(reinterpret_cast<const char*>(&count), sizeof(int));

    // Записываем все элементы
    BrandNode* current = brandList.GetHead();
    while (current != nullptr) {
        file.write(reinterpret_cast<const char*>(&current->data), sizeof(CarBrand));
        current = current->next;
    }

    file.close();
    return true;
}

bool FileManager::SaveCars(const char* filename, CarList& carList) {
    std::ofstream file(filename, std::ios::binary);
    if (!file.is_open()) {
        return false;
    }

    // Записываем количество элементов
    int count = carList.GetCount();
    file.write(reinterpret_cast<const char*>(&count), sizeof(int));

    // Записываем все элементы
    CarNode* current = carList.GetHead();
    while (current != nullptr) {
        file.write(reinterpret_cast<const char*>(&current->data), sizeof(Car));
        current = current->next;
    }

    file.close();
    return true;
}

void FileManager::CreateTestFiles(const char* brandsFile, const char* carsFile) {
    // Создаем тестовые марки
    BrandList brands;
    brands.Add(CarBrand(1, "Toyota", "Япония"));
    brands.Add(CarBrand(2, "BMW", "Германия"));
    brands.Add(CarBrand(3, "Ford", "США"));
    brands.Add(CarBrand(4, "Lada", "Россия"));
    brands.Add(CarBrand(5, "Mercedes-Benz", "Германия"));

    SaveBrands(brandsFile, brands);

    // Создаем тестовые автомобили
    CarList cars;

    // Toyota
    cars.Add(Car(1, "Camry", "Бензин", 25.5, 7.8, 10, 9));
    cars.Add(Car(1, "Corolla", "Бензин", 18.2, 6.5, 12, 8));
    cars.Add(Car(1, "RAV4", "Гибрид", 32.0, 5.9, 8, 9));

    // BMW
    cars.Add(Car(2, "X5", "Дизель", 65.0, 8.5, 7, 10));
    cars.Add(Car(2, "3 Series", "Бензин", 45.0, 7.2, 6, 9));
    cars.Add(Car(2, "i4", "Электро", 55.0, 0.0, 5, 10));

    // Ford
    cars.Add(Car(3, "Focus", "Бензин", 20.0, 7.0, 8, 7));
    cars.Add(Car(3, "Mustang", "Бензин", 48.0, 12.5, 5, 8));
    cars.Add(Car(3, "Explorer", "Бензин", 42.0, 11.0, 7, 8));

    // Lada
    cars.Add(Car(4, "Vesta", "Бензин", 10.5, 7.5, 5, 6));
    cars.Add(Car(4, "Granta", "Бензин", 8.0, 7.8, 4, 5));

    // Mercedes-Benz
    cars.Add(Car(5, "E-Class", "Дизель", 72.0, 6.5, 8, 10));
    cars.Add(Car(5, "GLE", "Бензин", 85.0, 10.2, 7, 10));
    cars.Add(Car(5, "EQS", "Электро", 95.0, 0.0, 6, 10));

    SaveCars(carsFile, cars);
}
