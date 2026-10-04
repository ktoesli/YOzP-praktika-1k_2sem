#pragma once
#include "CarData.h"

// Узел списка марок автомобилей
struct BrandNode {
    CarBrand data;
    BrandNode* next;

    BrandNode() : next(nullptr) {}
    BrandNode(const CarBrand& brand) : data(brand), next(nullptr) {}
};

// Узел списка автомобилей
struct CarNode {
    Car data;
    CarNode* next;

    CarNode() : next(nullptr) {}
    CarNode(const Car& car) : data(car), next(nullptr) {}
};

// Класс для управления списком марок (односвязный список на указателях)
class BrandList {
private:
    BrandNode* head;
    int count;

public:
    BrandList();
    ~BrandList();

    // Основные операции
    void Add(const CarBrand& brand);
    bool Remove(int brandCode);
    bool Update(int brandCode, const CarBrand& newData);
    CarBrand* Find(int brandCode);
    void Clear();

    // Доступ к данным
    BrandNode* GetHead() const { return head; }
    int GetCount() const { return count; }

    // Получение марки по индексу (для отображения)
    CarBrand* GetByIndex(int index);
};

// Класс для управления списком автомобилей (односвязный список на указателях)
class CarList {
private:
    CarNode* head;
    int count;

public:
    CarList();
    ~CarList();

    // Основные операции
    void Add(const Car& car);
    bool Remove(int index);
    bool Update(int index, const Car& newData);
    Car* GetByIndex(int index);
    void Clear();

    // Доступ к данным
    CarNode* GetHead() const { return head; }
    int GetCount() const { return count; }

    // Сортировка (по маркам, потом по параметру)
    void SortByBrandAndParameter(int sortParam); // 0=model, 1=price, 2=fuel, 3=reliability, 4=comfort

    // Поиск по фильтрам
    CarList* SearchByCriteria(
        int brandCode,           // -1 = любой
        const char* engineType,  // nullptr или "" = любой
        double priceMin, double priceMax,
        double fuelMin, double fuelMax,
        int reliabilityMin, int reliabilityMax,
        int comfortMin, int comfortMax
    );
};
