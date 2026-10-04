#pragma once
#include "CarList.h"
#include <msclr/marshal_cppstd.h>
#include <fstream>
#include <ctime>

namespace CarShop {

    using namespace System;
    using namespace System::Windows::Forms;
    using namespace System::Drawing;
    using namespace System::IO;

    public ref class SearchForm : public Form
    {
    public:
        SearchForm(CarList* cars, BrandList* brands, bool isSpecialFunction)
        {
            this->carList = cars;
            this->brandList = brands;
            this->isSpecial = isSpecialFunction;
            InitializeComponent();
        }

    private:
        CarList* carList;
        BrandList* brandList;
        bool isSpecial;

        // Контролы фильтров
        Label^ lblBrand;
        ComboBox^ comboBrand;
        CheckBox^ chkAnyBrand;

        Label^ lblEngine;
        ComboBox^ comboEngine;
        CheckBox^ chkAnyEngine;

        Label^ lblPriceRange;
        NumericUpDown^ numPriceMin;
        Label^ lblPriceTo;
        NumericUpDown^ numPriceMax;

        Label^ lblFuelRange;
        NumericUpDown^ numFuelMin;
        Label^ lblFuelTo;
        NumericUpDown^ numFuelMax;

        Label^ lblReliabilityRange;
        NumericUpDown^ numReliabilityMin;
        Label^ lblReliabilityTo;
        NumericUpDown^ numReliabilityMax;

        Label^ lblComfortRange;
        NumericUpDown^ numComfortMin;
        Label^ lblComfortTo;
        NumericUpDown^ numComfortMax;

        Button^ btnSearch;
        Button^ btnClear;
        Button^ btnClose;

        DataGridView^ dataGridView;
        Label^ lblResults;

        void InitializeComponent()
        {
            this->SuspendLayout();

            int y = 20;

            // Марка
            this->lblBrand = (gcnew Label());
            this->lblBrand->Location = System::Drawing::Point(20, y);
            this->lblBrand->Size = System::Drawing::Size(100, 20);
            this->lblBrand->Text = L"Марка:";
            this->Controls->Add(this->lblBrand);

            this->comboBrand = (gcnew ComboBox());
            this->comboBrand->Location = System::Drawing::Point(130, y);
            this->comboBrand->Size = System::Drawing::Size(200, 20);
            this->comboBrand->DropDownStyle = ComboBoxStyle::DropDownList;
            LoadBrandsToCombo();
            this->Controls->Add(this->comboBrand);

            this->chkAnyBrand = (gcnew CheckBox());
            this->chkAnyBrand->Location = System::Drawing::Point(340, y);
            this->chkAnyBrand->Size = System::Drawing::Size(100, 20);
            this->chkAnyBrand->Text = L"Любая";
            this->chkAnyBrand->Checked = true;
            this->chkAnyBrand->CheckedChanged += gcnew EventHandler(this, &SearchForm::chkAnyBrand_CheckedChanged);
            this->Controls->Add(this->chkAnyBrand);

            y += 35;

            // Тип двигателя
            this->lblEngine = (gcnew Label());
            this->lblEngine->Location = System::Drawing::Point(20, y);
            this->lblEngine->Size = System::Drawing::Size(100, 20);
            this->lblEngine->Text = L"Тип двигателя:";
            this->Controls->Add(this->lblEngine);

            this->comboEngine = (gcnew ComboBox());
            this->comboEngine->Location = System::Drawing::Point(130, y);
            this->comboEngine->Size = System::Drawing::Size(200, 20);
            this->comboEngine->DropDownStyle = ComboBoxStyle::DropDownList;
            this->comboEngine->Items->AddRange(gcnew cli::array<String^> { "Бензин", "Дизель", "Электро", "Гибрид" });
            this->comboEngine->SelectedIndex = 0;
            this->Controls->Add(this->comboEngine);

            this->chkAnyEngine = (gcnew CheckBox());
            this->chkAnyEngine->Location = System::Drawing::Point(340, y);
            this->chkAnyEngine->Size = System::Drawing::Size(100, 20);
            this->chkAnyEngine->Text = L"Любой";
            this->chkAnyEngine->Checked = true;
            this->chkAnyEngine->CheckedChanged += gcnew EventHandler(this, &SearchForm::chkAnyEngine_CheckedChanged);
            this->Controls->Add(this->chkAnyEngine);

            y += 35;

            // Цена
            this->lblPriceRange = (gcnew Label());
            this->lblPriceRange->Location = System::Drawing::Point(20, y);
            this->lblPriceRange->Size = System::Drawing::Size(100, 20);
            this->lblPriceRange->Text = L"Цена (тыс.$):";
            this->Controls->Add(this->lblPriceRange);

            this->numPriceMin = (gcnew NumericUpDown());
            this->numPriceMin->Location = System::Drawing::Point(130, y);
            this->numPriceMin->Size = System::Drawing::Size(80, 20);
            this->numPriceMin->DecimalPlaces = 1;
            this->numPriceMin->Minimum = 0;
            this->numPriceMin->Maximum = 1000;
            this->numPriceMin->Value = 0;
            this->Controls->Add(this->numPriceMin);

            this->lblPriceTo = (gcnew Label());
            this->lblPriceTo->Location = System::Drawing::Point(215, y);
            this->lblPriceTo->Size = System::Drawing::Size(20, 20);
            this->lblPriceTo->Text = L"-";
            this->lblPriceTo->TextAlign = ContentAlignment::MiddleCenter;
            this->Controls->Add(this->lblPriceTo);

            this->numPriceMax = (gcnew NumericUpDown());
            this->numPriceMax->Location = System::Drawing::Point(240, y);
            this->numPriceMax->Size = System::Drawing::Size(80, 20);
            this->numPriceMax->DecimalPlaces = 1;
            this->numPriceMax->Minimum = 0;
            this->numPriceMax->Maximum = 1000;
            this->numPriceMax->Value = 1000;
            this->Controls->Add(this->numPriceMax);

            y += 35;

            // Расход топлива
            this->lblFuelRange = (gcnew Label());
            this->lblFuelRange->Location = System::Drawing::Point(20, y);
            this->lblFuelRange->Size = System::Drawing::Size(100, 20);
            this->lblFuelRange->Text = L"Расход (л/100):";
            this->Controls->Add(this->lblFuelRange);

            this->numFuelMin = (gcnew NumericUpDown());
            this->numFuelMin->Location = System::Drawing::Point(130, y);
            this->numFuelMin->Size = System::Drawing::Size(80, 20);
            this->numFuelMin->DecimalPlaces = 1;
            this->numFuelMin->Minimum = 0;
            this->numFuelMin->Maximum = 50;
            this->numFuelMin->Value = 0;
            this->Controls->Add(this->numFuelMin);

            this->lblFuelTo = (gcnew Label());
            this->lblFuelTo->Location = System::Drawing::Point(215, y);
            this->lblFuelTo->Size = System::Drawing::Size(20, 20);
            this->lblFuelTo->Text = L"-";
            this->lblFuelTo->TextAlign = ContentAlignment::MiddleCenter;
            this->Controls->Add(this->lblFuelTo);

            this->numFuelMax = (gcnew NumericUpDown());
            this->numFuelMax->Location = System::Drawing::Point(240, y);
            this->numFuelMax->Size = System::Drawing::Size(80, 20);
            this->numFuelMax->DecimalPlaces = 1;
            this->numFuelMax->Minimum = 0;
            this->numFuelMax->Maximum = 50;
            this->numFuelMax->Value = 50;
            this->Controls->Add(this->numFuelMax);

            y += 35;

            // Надежность
            this->lblReliabilityRange = (gcnew Label());
            this->lblReliabilityRange->Location = System::Drawing::Point(20, y);
            this->lblReliabilityRange->Size = System::Drawing::Size(100, 20);
            this->lblReliabilityRange->Text = L"Надежность (лет):";
            this->Controls->Add(this->lblReliabilityRange);

            this->numReliabilityMin = (gcnew NumericUpDown());
            this->numReliabilityMin->Location = System::Drawing::Point(130, y);
            this->numReliabilityMin->Size = System::Drawing::Size(80, 20);
            this->numReliabilityMin->Minimum = 0;
            this->numReliabilityMin->Maximum = 50;
            this->numReliabilityMin->Value = 0;
            this->Controls->Add(this->numReliabilityMin);

            this->lblReliabilityTo = (gcnew Label());
            this->lblReliabilityTo->Location = System::Drawing::Point(215, y);
            this->lblReliabilityTo->Size = System::Drawing::Size(20, 20);
            this->lblReliabilityTo->Text = L"-";
            this->lblReliabilityTo->TextAlign = ContentAlignment::MiddleCenter;
            this->Controls->Add(this->lblReliabilityTo);

            this->numReliabilityMax = (gcnew NumericUpDown());
            this->numReliabilityMax->Location = System::Drawing::Point(240, y);
            this->numReliabilityMax->Size = System::Drawing::Size(80, 20);
            this->numReliabilityMax->Minimum = 0;
            this->numReliabilityMax->Maximum = 50;
            this->numReliabilityMax->Value = 50;
            this->Controls->Add(this->numReliabilityMax);

            y += 35;

            // Комфорт
            this->lblComfortRange = (gcnew Label());
            this->lblComfortRange->Location = System::Drawing::Point(20, y);
            this->lblComfortRange->Size = System::Drawing::Size(100, 20);
            this->lblComfortRange->Text = L"Комфорт (баллы):";
            this->Controls->Add(this->lblComfortRange);

            this->numComfortMin = (gcnew NumericUpDown());
            this->numComfortMin->Location = System::Drawing::Point(130, y);
            this->numComfortMin->Size = System::Drawing::Size(80, 20);
            this->numComfortMin->Minimum = 0;
            this->numComfortMin->Maximum = 10;
            this->numComfortMin->Value = 0;
            this->Controls->Add(this->numComfortMin);

            this->lblComfortTo = (gcnew Label());
            this->lblComfortTo->Location = System::Drawing::Point(215, y);
            this->lblComfortTo->Size = System::Drawing::Size(20, 20);
            this->lblComfortTo->Text = L"-";
            this->lblComfortTo->TextAlign = ContentAlignment::MiddleCenter;
            this->Controls->Add(this->lblComfortTo);

            this->numComfortMax = (gcnew NumericUpDown());
            this->numComfortMax->Location = System::Drawing::Point(240, y);
            this->numComfortMax->Size = System::Drawing::Size(80, 20);
            this->numComfortMax->Minimum = 0;
            this->numComfortMax->Maximum = 10;
            this->numComfortMax->Value = 10;
            this->Controls->Add(this->numComfortMax);

            y += 40;

            // Кнопки
            this->btnSearch = (gcnew Button());
            this->btnSearch->Location = System::Drawing::Point(20, y);
            this->btnSearch->Size = System::Drawing::Size(100, 30);
            this->btnSearch->Text = L"Найти";
            this->btnSearch->Click += gcnew EventHandler(this, &SearchForm::btnSearch_Click);
            this->Controls->Add(this->btnSearch);

            this->btnClear = (gcnew Button());
            this->btnClear->Location = System::Drawing::Point(130, y);
            this->btnClear->Size = System::Drawing::Size(100, 30);
            this->btnClear->Text = L"Сбросить";
            this->btnClear->Click += gcnew EventHandler(this, &SearchForm::btnClear_Click);
            this->Controls->Add(this->btnClear);

            this->btnClose = (gcnew Button());
            this->btnClose->Location = System::Drawing::Point(240, y);
            this->btnClose->Size = System::Drawing::Size(100, 30);
            this->btnClose->Text = L"Закрыть";
            this->btnClose->Click += gcnew EventHandler(this, &SearchForm::btnClose_Click);
            this->Controls->Add(this->btnClose);

            y += 45;

            // Результаты
            this->lblResults = (gcnew Label());
            this->lblResults->Location = System::Drawing::Point(20, y);
            this->lblResults->Size = System::Drawing::Size(740, 20);
            this->lblResults->Text = L"Результаты поиска:";
            this->Controls->Add(this->lblResults);

            y += 25;

            this->dataGridView = (gcnew DataGridView());
            this->dataGridView->AllowUserToAddRows = false;
            this->dataGridView->AllowUserToDeleteRows = false;
            this->dataGridView->AutoSizeColumnsMode = DataGridViewAutoSizeColumnsMode::Fill;
            this->dataGridView->ColumnHeadersHeightSizeMode = DataGridViewColumnHeadersHeightSizeMode::AutoSize;
            this->dataGridView->Location = System::Drawing::Point(20, y);
            this->dataGridView->ReadOnly = true;
            this->dataGridView->SelectionMode = DataGridViewSelectionMode::FullRowSelect;
            this->dataGridView->Size = System::Drawing::Size(740, 200);
            this->Controls->Add(this->dataGridView);

            // Form
            this->ClientSize = System::Drawing::Size(784, y + 210);
            this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
            this->MaximizeBox = false;
            this->Name = L"SearchForm";
            this->StartPosition = FormStartPosition::CenterParent;
            this->Text = isSpecial ? L"Поиск по требованиям покупателя" : L"Поиск автомобилей";
            this->ResumeLayout(false);

            InitializeDataGrid();
        }

        void LoadBrandsToCombo()
        {
            comboBrand->Items->Clear();
            BrandNode* current = brandList->GetHead();
            while (current != nullptr) {
                String^ item = String::Format("{0} - {1}",
                    current->data.brandCode,
                    gcnew String(current->data.brandName));
                comboBrand->Items->Add(item);
                current = current->next;
            }
            if (comboBrand->Items->Count > 0) {
                comboBrand->SelectedIndex = 0;
            }
            comboBrand->Enabled = false;
        }

        void InitializeDataGrid()
        {
            dataGridView->Columns->Clear();
            dataGridView->Columns->Add("BrandName", "Марка");
            dataGridView->Columns->Add("Model", "Модель");
            dataGridView->Columns->Add("Engine", "Двигатель");
            dataGridView->Columns->Add("Price", "Цена (тыс.$)");
            dataGridView->Columns->Add("Fuel", "Расход (л/100км)");
            dataGridView->Columns->Add("Reliability", "Надежность (лет)");
            dataGridView->Columns->Add("Comfort", "Комфорт (баллы)");
        }

        void chkAnyBrand_CheckedChanged(Object^ sender, EventArgs^ e)
        {
            comboBrand->Enabled = !chkAnyBrand->Checked;
        }

        void chkAnyEngine_CheckedChanged(Object^ sender, EventArgs^ e)
        {
            comboEngine->Enabled = !chkAnyEngine->Checked;
        }

        void btnSearch_Click(Object^ sender, EventArgs^ e)
        {
            // Получаем параметры поиска
            int brandCode = -1;
            if (!chkAnyBrand->Checked && comboBrand->SelectedIndex >= 0) {
                String^ selected = comboBrand->SelectedItem->ToString();
                brandCode = Int32::Parse(selected->Substring(0, selected->IndexOf(" -")));
            }

            const char* engineType = nullptr;
            String^ engineStr = nullptr;
            if (!chkAnyEngine->Checked) {
                engineStr = comboEngine->Text;
            }

            msclr::interop::marshal_context context;
            if (engineStr != nullptr) {
                engineType = context.marshal_as<const char*>(engineStr);
            }

            // Выполняем поиск
            CarList* results = carList->SearchByCriteria(
                brandCode,
                engineType,
                (double)numPriceMin->Value, (double)numPriceMax->Value,
                (double)numFuelMin->Value, (double)numFuelMax->Value,
                (int)numReliabilityMin->Value, (int)numReliabilityMax->Value,
                (int)numComfortMin->Value, (int)numComfortMax->Value
            );

            // Отображаем результаты
            DisplayResults(results);

            // Если это специальная функция, сохраняем в файл
            if (isSpecial) {
                SaveResultsToFile(results);
            }

            // Освобождаем память результатов
            delete results;
        }

        void DisplayResults(CarList* results)
        {
            dataGridView->Rows->Clear();

            int count = results->GetCount();
            lblResults->Text = String::Format("Результаты поиска: найдено {0} автомобилей", count);

            CarNode* current = results->GetHead();
            while (current != nullptr) {
                CarBrand* brand = brandList->Find(current->data.brandCode);
                String^ brandName = brand ? gcnew String(brand->brandName) : "Неизвестно";

                dataGridView->Rows->Add(
                    brandName,
                    gcnew String(current->data.model),
                    gcnew String(current->data.engineType),
                    current->data.price,
                    current->data.fuelConsumption,
                    current->data.reliability,
                    current->data.comfort
                );
                current = current->next;
            }

            if (count == 0) {
                MessageBox::Show("По заданным критериям автомобили не найдены.", "Результат поиска",
                    MessageBoxButtons::OK, MessageBoxIcon::Information);
            }
        }

        void SaveResultsToFile(CarList* results)
        {
            try {
                // Генерируем имя файла с датой и временем
                DateTime now = DateTime::Now;
                String^ filename = String::Format("search_results_{0:yyyyMMdd_HHmmss}.txt", now);

                msclr::interop::marshal_context context;
                const char* filepath = context.marshal_as<const char*>(filename);

                std::ofstream file(filepath);
                if (!file.is_open()) {
                    MessageBox::Show("Ошибка создания файла результатов!", "Ошибка",
                        MessageBoxButtons::OK, MessageBoxIcon::Error);
                    return;
                }

                // Записываем заголовок
                file << "=================================================================\n";
                file << "   РЕЗУЛЬТАТЫ ПОИСКА АВТОМОБИЛЕЙ ПО ТРЕБОВАНИЯМ ПОКУПАТЕЛЯ\n";
                file << "=================================================================\n\n";

                // Записываем дату и время
                std::time_t t = std::time(nullptr);
                std::tm timeInfo;
                localtime_s(&timeInfo, &t);
                char timeStr[100];
                std::strftime(timeStr, sizeof(timeStr), "%d.%m.%Y %H:%M:%S", &timeInfo);
                file << "Дата и время поиска: " << timeStr << "\n\n";

                // Записываем критерии поиска
                file << "КРИТЕРИИ ПОИСКА:\n";
                file << "-----------------------------------------------------------------\n";

                if (!chkAnyBrand->Checked && comboBrand->SelectedIndex >= 0) {
                    String^ brandText = comboBrand->Text;
                    file << "Марка: " << context.marshal_as<const char*>(brandText) << "\n";
                } else {
                    file << "Марка: Любая\n";
                }

                if (!chkAnyEngine->Checked) {
                    file << "Тип двигателя: " << context.marshal_as<const char*>(comboEngine->Text) << "\n";
                } else {
                    file << "Тип двигателя: Любой\n";
                }

                file << "Цена: от " << (double)numPriceMin->Value << " до " << (double)numPriceMax->Value << " тыс.$\n";
                file << "Расход топлива: от " << (double)numFuelMin->Value << " до " << (double)numFuelMax->Value << " л/100км\n";
                file << "Надежность: от " << (int)numReliabilityMin->Value << " до " << (int)numReliabilityMax->Value << " лет\n";
                file << "Комфорт: от " << (int)numComfortMin->Value << " до " << (int)numComfortMax->Value << " баллов\n\n";

                // Записываем результаты
                int count = results->GetCount();
                file << "НАЙДЕНО АВТОМОБИЛЕЙ: " << count << "\n";
                file << "=================================================================\n\n";

                if (count > 0) {
                    int index = 1;
                    CarNode* current = results->GetHead();
                    while (current != nullptr) {
                        CarBrand* brand = brandList->Find(current->data.brandCode);
                        const char* brandName = brand ? brand->brandName : "Неизвестно";

                        file << index << ". " << brandName << " " << current->data.model << "\n";
                        file << "   Тип двигателя: " << current->data.engineType << "\n";
                        file << "   Цена: " << current->data.price << " тыс.$\n";
                        file << "   Расход топлива: " << current->data.fuelConsumption << " л/100км\n";
                        file << "   Надежность: " << current->data.reliability << " лет\n";
                        file << "   Комфорт: " << current->data.comfort << " баллов\n";
                        file << "-----------------------------------------------------------------\n";

                        current = current->next;
                        index++;
                    }
                } else {
                    file << "По заданным критериям автомобили не найдены.\n";
                }

                file << "\n=================================================================\n";
                file << "                     КОНЕЦ ОТЧЕТА\n";
                file << "=================================================================\n";

                file.close();

                MessageBox::Show(String::Format("Результаты сохранены в файл:\n{0}", filename),
                    "Сохранение результатов", MessageBoxButtons::OK, MessageBoxIcon::Information);

            }
            catch (Exception^ ex) {
                MessageBox::Show("Ошибка при сохранении результатов: " + ex->Message,
                    "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
            }
        }

        void btnClear_Click(Object^ sender, EventArgs^ e)
        {
            // Сброс всех фильтров
            chkAnyBrand->Checked = true;
            chkAnyEngine->Checked = true;
            numPriceMin->Value = 0;
            numPriceMax->Value = 1000;
            numFuelMin->Value = 0;
            numFuelMax->Value = 50;
            numReliabilityMin->Value = 0;
            numReliabilityMax->Value = 50;
            numComfortMin->Value = 0;
            numComfortMax->Value = 10;

            dataGridView->Rows->Clear();
            lblResults->Text = "Результаты поиска:";
        }

        void btnClose_Click(Object^ sender, EventArgs^ e)
        {
            this->Close();
        }
    };
}
