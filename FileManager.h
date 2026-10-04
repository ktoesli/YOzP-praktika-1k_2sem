#pragma once
#include "CarList.h"
#include <string>

// Класс для работы с типизированными (бинарными) файлами
class FileManager {
public:
    // Чтение данных из файлов в динамические списки
    static bool LoadBrands(const char* filename, BrandList& brandList);
    static bool LoadCars(const char* filename, CarList& carList);

    // Сохранение данных из динамических списков в файлы
    static bool SaveBrands(const char* filename, BrandList& brandList);
    static bool SaveCars(const char* filename, CarList& carList);

    // Создание тестовых файлов с примерными данными
    static void CreateTestFiles(const char* brandsFile, const char* carsFile);
};
