#include "CarList.h"
#include <cstring>

// ============ BrandList Implementation ============

BrandList::BrandList() : head(nullptr), count(0) {}

BrandList::~BrandList() {
    Clear();
}

void BrandList::Add(const CarBrand& brand) {
    BrandNode* newNode = new BrandNode(brand);

    if (head == nullptr) {
        head = newNode;
    } else {
        BrandNode* current = head;
        while (current->next != nullptr) {
            current = current->next;
        }
        current->next = newNode;
    }
    count++;
}

bool BrandList::Remove(int brandCode) {
    if (head == nullptr) return false;

    // Если удаляем первый элемент
    if (head->data.brandCode == brandCode) {
        BrandNode* temp = head;
        head = head->next;
        delete temp;
        count--;
        return true;
    }

    // Ищем элемент для удаления
    BrandNode* current = head;
    while (current->next != nullptr) {
        if (current->next->data.brandCode == brandCode) {
            BrandNode* temp = current->next;
            current->next = temp->next;
            delete temp;
            count--;
            return true;
        }
        current = current->next;
    }

    return false;
}

bool BrandList::Update(int brandCode, const CarBrand& newData) {
    BrandNode* current = head;
    while (current != nullptr) {
        if (current->data.brandCode == brandCode) {
            current->data = newData;
            return true;
        }
        current = current->next;
    }
    return false;
}

CarBrand* BrandList::Find(int brandCode) {
    BrandNode* current = head;
    while (current != nullptr) {
        if (current->data.brandCode == brandCode) {
            return &(current->data);
        }
        current = current->next;
    }
    return nullptr;
}

void BrandList::Clear() {
    while (head != nullptr) {
        BrandNode* temp = head;
        head = head->next;
        delete temp;
    }
    count = 0;
}

CarBrand* BrandList::GetByIndex(int index) {
    if (index < 0 || index >= count) return nullptr;

    BrandNode* current = head;
    for (int i = 0; i < index; i++) {
        current = current->next;
    }
    return &(current->data);
}

// ============ CarList Implementation ============

CarList::CarList() : head(nullptr), count(0) {}

CarList::~CarList() {
    Clear();
}

void CarList::Add(const Car& car) {
    CarNode* newNode = new CarNode(car);

    if (head == nullptr) {
        head = newNode;
    } else {
        CarNode* current = head;
        while (current->next != nullptr) {
            current = current->next;
        }
        current->next = newNode;
    }
    count++;
}

bool CarList::Remove(int index) {
    if (index < 0 || index >= count || head == nullptr) return false;

    // Если удаляем первый элемент
    if (index == 0) {
        CarNode* temp = head;
        head = head->next;
        delete temp;
        count--;
        return true;
    }

    // Ищем элемент перед удаляемым
    CarNode* current = head;
    for (int i = 0; i < index - 1; i++) {
        current = current->next;
    }

    CarNode* temp = current->next;
    current->next = temp->next;
    delete temp;
    count--;
    return true;
}

bool CarList::Update(int index, const Car& newData) {
    Car* car = GetByIndex(index);
    if (car != nullptr) {
        *car = newData;
        return true;
    }
    return false;
}

Car* CarList::GetByIndex(int index) {
    if (index < 0 || index >= count) return nullptr;

    CarNode* current = head;
    for (int i = 0; i < index; i++) {
        current = current->next;
    }
    return &(current->data);
}

void CarList::Clear() {
    while (head != nullptr) {
        CarNode* temp = head;
        head = head->next;
        delete temp;
    }
    count = 0;
}

// Сортировка пузырьком 
void CarList::SortByBrandAndParameter(int sortParam) {
    if (count < 2) return;

    bool swapped;
    do {
        swapped = false;
        CarNode* current = head;
        CarNode* prev = nullptr;
        CarNode* next = head->next;

        while (next != nullptr) {
            bool needSwap = false;

            // Сначала сравниваем по brandCode
            if (current->data.brandCode > next->data.brandCode) {
                needSwap = true;
            } else if (current->data.brandCode == next->data.brandCode) {
                // Внутри одной марки сортируем по выбранному параметру
                switch (sortParam) {
                    case 0: // model
                        needSwap = (strcmp(current->data.model, next->data.model) > 0);
                        break;
                    case 1: // price
                        needSwap = (current->data.price > next->data.price);
                        break;
                    case 2: // fuel consumption
                        needSwap = (current->data.fuelConsumption > next->data.fuelConsumption);
                        break;
                    case 3: // reliability
                        needSwap = (current->data.reliability < next->data.reliability); // больше = лучше
                        break;
                    case 4: // comfort
                        needSwap = (current->data.comfort < next->data.comfort); // больше = лучше
                        break;
                }
            }

            if (needSwap) {
                swapped = true;

                if (prev != nullptr) {
                    CarNode* tmp = next->next;
                    prev->next = next;
                    next->next = current;
                    current->next = tmp;
                } else {
                    CarNode* tmp = next->next;
                    head = next;
                    next->next = current;
                    current->next = tmp;
                }

                prev = next;
                next = current->next;
            } else {
                prev = current;
                current = next;
                next = next->next;
            }
        }
    } while (swapped);
}

// Поиск по критериям покупателя
CarList* CarList::SearchByCriteria(
    int brandCode,
    const char* engineType,
    double priceMin, double priceMax,
    double fuelMin, double fuelMax,
    int reliabilityMin, int reliabilityMax,
    int comfortMin, int comfortMax
) {
    CarList* result = new CarList();

    CarNode* current = head;
    while (current != nullptr) {
        bool match = true;

        // Проверка по коду марки
        if (brandCode != -1 && current->data.brandCode != brandCode) {
            match = false;
        }

        // Проверка по типу двигателя
        if (match && engineType != nullptr && strlen(engineType) > 0) {
            if (strcmp(current->data.engineType, engineType) != 0) {
                match = false;
            }
        }

        // Проверка по цене
        if (match && (current->data.price < priceMin || current->data.price > priceMax)) {
            match = false;
        }

        // Проверка по расходу топлива
        if (match && (current->data.fuelConsumption < fuelMin || current->data.fuelConsumption > fuelMax)) {
            match = false;
        }

        // Проверка по надежности
        if (match && (current->data.reliability < reliabilityMin || current->data.reliability > reliabilityMax)) {
            match = false;
        }

        // Проверка по комфортности
        if (match && (current->data.comfort < comfortMin || current->data.comfort > comfortMax)) {
            match = false;
        }

        if (match) {
            result->Add(current->data);
        }

        current = current->next;
    }

    return result;
}
