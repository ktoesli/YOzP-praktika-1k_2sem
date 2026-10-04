#pragma once
#include <cstring>

// Структура данных для марки автомобиля
struct CarBrand {
    int brandCode;              // Код марки
    char brandName[50];         // Название марки
    char country[50];           // Страна

    CarBrand() : brandCode(0) {
        brandName[0] = '\0';
        country[0] = '\0';
    }

    CarBrand(int code, const char* name, const char* ctry) : brandCode(code) {
        strncpy_s(brandName, name, 49);
        brandName[49] = '\0';
        strncpy_s(country, ctry, 49);
        country[49] = '\0';
    }
};

// Структура данных для автомобиля
struct Car {
    int brandCode;              // Код марки (связь с CarBrand)
    char model[50];             // Модель автомобиля
    char engineType[30];        // Тип двигателя (бензин, дизель, электро, гибрид)
    double price;               // Стоимость (тыс. $)
    double fuelConsumption;     // Расход бензина на 100 км (л)
    int reliability;            // Надежность (лет безотказной работы)
    int comfort;                // Комфортность (баллы 0-10)

    Car() : brandCode(0), price(0.0), fuelConsumption(0.0), reliability(0), comfort(0) {
        model[0] = '\0';
        engineType[0] = '\0';
    }

    Car(int code, const char* mdl, const char* engine, double pr, double fuel, int rel, int comf)
        : brandCode(code), price(pr), fuelConsumption(fuel), reliability(rel), comfort(comf) {
        strncpy_s(model, mdl, 49);
        model[49] = '\0';
        strncpy_s(engineType, engine, 29);
        engineType[29] = '\0';
    }
};
