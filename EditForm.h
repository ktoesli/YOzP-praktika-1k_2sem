#pragma once
#include "CarList.h"
#include <msclr/marshal_cppstd.h>

namespace CarShop {

    using namespace System;
    using namespace System::Windows::Forms;
    using namespace System::Drawing;

    public ref class EditForm : public Form
    {
    public:
        EditForm(BrandList* brands, CarList* cars, bool editBrand)
        {
            this->brandList = brands;
            this->carList = cars;
            this->isEditBrand = editBrand;
            InitializeComponent();
        }

    private:
        BrandList* brandList;
        CarList* carList;
        bool isEditBrand;
        int selectedIndex;

        // Контролы выбора
        Label^ lblSelect;
        ComboBox^ comboSelect;

        // Контролы для марки
        Label^ lblBrandCode;
        NumericUpDown^ numBrandCode;
        Label^ lblBrandName;
        TextBox^ txtBrandName;
        Label^ lblCountry;
        TextBox^ txtCountry;

        // Контролы для автомобиля
        Label^ lblCarBrandCode;
        ComboBox^ comboBrandCode;
        Label^ lblModel;
        TextBox^ txtModel;
        Label^ lblEngine;
        ComboBox^ comboEngine;
        Label^ lblPrice;
        NumericUpDown^ numPrice;
        Label^ lblFuel;
        NumericUpDown^ numFuel;
        Label^ lblReliability;
        NumericUpDown^ numReliability;
        Label^ lblComfort;
        NumericUpDown^ numComfort;

        Button^ btnSave;
        Button^ btnCancel;

        void InitializeComponent()
        {
            this->SuspendLayout();

            // Выбор элемента
            this->lblSelect = (gcnew Label());
            this->lblSelect->Location = System::Drawing::Point(20, 20);
            this->lblSelect->Size = System::Drawing::Size(100, 20);
            this->lblSelect->Text = L"Выберите:";
            this->Controls->Add(this->lblSelect);

            this->comboSelect = (gcnew ComboBox());
            this->comboSelect->Location = System::Drawing::Point(150, 20);
            this->comboSelect->Size = System::Drawing::Size(280, 20);
            this->comboSelect->DropDownStyle = ComboBoxStyle::DropDownList;
            this->comboSelect->SelectedIndexChanged += gcnew EventHandler(this, &EditForm::comboSelect_SelectedIndexChanged);
            this->Controls->Add(this->comboSelect);

            if (isEditBrand) {
                InitializeBrandControls();
                LoadBrandsToCombo();
            }
            else {
                InitializeCarControls();
                LoadCarsToCombo();
            }

            // Кнопки
            this->btnSave = (gcnew Button());
            this->btnSave->Location = System::Drawing::Point(120, isEditBrand ? 200 : 400);
            this->btnSave->Name = L"btnSave";
            this->btnSave->Size = System::Drawing::Size(100, 30);
            this->btnSave->Text = L"Сохранить";
            this->btnSave->Click += gcnew EventHandler(this, &EditForm::btnSave_Click);
            this->Controls->Add(this->btnSave);

            this->btnCancel = (gcnew Button());
            this->btnCancel->Location = System::Drawing::Point(240, isEditBrand ? 200 : 400);
            this->btnCancel->Name = L"btnCancel";
            this->btnCancel->Size = System::Drawing::Size(100, 30);
            this->btnCancel->Text = L"Отмена";
            this->btnCancel->Click += gcnew EventHandler(this, &EditForm::btnCancel_Click);
            this->Controls->Add(this->btnCancel);

            // Form
            this->ClientSize = System::Drawing::Size(460, isEditBrand ? 250 : 450);
            this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
            this->MaximizeBox = false;
            this->MinimizeBox = false;
            this->Name = L"EditForm";
            this->StartPosition = FormStartPosition::CenterParent;
            this->Text = isEditBrand ? L"Редактирование марки" : L"Редактирование автомобиля";
            this->ResumeLayout(false);
        }

        void InitializeBrandControls()
        {
            int y = 70;

            this->lblBrandCode = (gcnew Label());
            this->lblBrandCode->Location = System::Drawing::Point(20, y);
            this->lblBrandCode->Size = System::Drawing::Size(100, 20);
            this->lblBrandCode->Text = L"Код марки:";
            this->Controls->Add(this->lblBrandCode);

            this->numBrandCode = (gcnew NumericUpDown());
            this->numBrandCode->Location = System::Drawing::Point(150, y);
            this->numBrandCode->Size = System::Drawing::Size(280, 20);
            this->numBrandCode->Minimum = 1;
            this->numBrandCode->Maximum = 10000;
            this->numBrandCode->Enabled = false; // Код нельзя менять
            this->Controls->Add(this->numBrandCode);

            y += 40;
            this->lblBrandName = (gcnew Label());
            this->lblBrandName->Location = System::Drawing::Point(20, y);
            this->lblBrandName->Size = System::Drawing::Size(100, 20);
            this->lblBrandName->Text = L"Название марки:";
            this->Controls->Add(this->lblBrandName);

            this->txtBrandName = (gcnew TextBox());
            this->txtBrandName->Location = System::Drawing::Point(150, y);
            this->txtBrandName->Size = System::Drawing::Size(280, 20);
            this->Controls->Add(this->txtBrandName);

            y += 40;
            this->lblCountry = (gcnew Label());
            this->lblCountry->Location = System::Drawing::Point(20, y);
            this->lblCountry->Size = System::Drawing::Size(100, 20);
            this->lblCountry->Text = L"Страна:";
            this->Controls->Add(this->lblCountry);

            this->txtCountry = (gcnew TextBox());
            this->txtCountry->Location = System::Drawing::Point(150, y);
            this->txtCountry->Size = System::Drawing::Size(280, 20);
            this->Controls->Add(this->txtCountry);
        }

        void InitializeCarControls()
        {
            int y = 70;

            this->lblCarBrandCode = (gcnew Label());
            this->lblCarBrandCode->Location = System::Drawing::Point(20, y);
            this->lblCarBrandCode->Size = System::Drawing::Size(100, 20);
            this->lblCarBrandCode->Text = L"Марка:";
            this->Controls->Add(this->lblCarBrandCode);

            this->comboBrandCode = (gcnew ComboBox());
            this->comboBrandCode->Location = System::Drawing::Point(150, y);
            this->comboBrandCode->Size = System::Drawing::Size(280, 20);
            this->comboBrandCode->DropDownStyle = ComboBoxStyle::DropDownList;
            LoadBrandsToCarCombo();
            this->Controls->Add(this->comboBrandCode);

            y += 40;
            this->lblModel = (gcnew Label());
            this->lblModel->Location = System::Drawing::Point(20, y);
            this->lblModel->Size = System::Drawing::Size(100, 20);
            this->lblModel->Text = L"Модель:";
            this->Controls->Add(this->lblModel);

            this->txtModel = (gcnew TextBox());
            this->txtModel->Location = System::Drawing::Point(150, y);
            this->txtModel->Size = System::Drawing::Size(280, 20);
            this->Controls->Add(this->txtModel);

            y += 40;
            this->lblEngine = (gcnew Label());
            this->lblEngine->Location = System::Drawing::Point(20, y);
            this->lblEngine->Size = System::Drawing::Size(100, 20);
            this->lblEngine->Text = L"Тип двигателя:";
            this->Controls->Add(this->lblEngine);

            this->comboEngine = (gcnew ComboBox());
            this->comboEngine->Location = System::Drawing::Point(150, y);
            this->comboEngine->Size = System::Drawing::Size(280, 20);
            this->comboEngine->Items->AddRange(gcnew cli::array<String^> { "Бензин", "Дизель", "Электро", "Гибрид" });
            this->Controls->Add(this->comboEngine);

            y += 40;
            this->lblPrice = (gcnew Label());
            this->lblPrice->Location = System::Drawing::Point(20, y);
            this->lblPrice->Size = System::Drawing::Size(120, 20);
            this->lblPrice->Text = L"Цена (тыс. $):";
            this->Controls->Add(this->lblPrice);

            this->numPrice = (gcnew NumericUpDown());
            this->numPrice->Location = System::Drawing::Point(150, y);
            this->numPrice->Size = System::Drawing::Size(280, 20);
            this->numPrice->DecimalPlaces = 1;
            this->numPrice->Minimum = 0;
            this->numPrice->Maximum = 1000;
            this->Controls->Add(this->numPrice);

            y += 40;
            this->lblFuel = (gcnew Label());
            this->lblFuel->Location = System::Drawing::Point(20, y);
            this->lblFuel->Size = System::Drawing::Size(120, 20);
            this->lblFuel->Text = L"Расход (л/100км):";
            this->Controls->Add(this->lblFuel);

            this->numFuel = (gcnew NumericUpDown());
            this->numFuel->Location = System::Drawing::Point(150, y);
            this->numFuel->Size = System::Drawing::Size(280, 20);
            this->numFuel->DecimalPlaces = 1;
            this->numFuel->Minimum = 0;
            this->numFuel->Maximum = 50;
            this->Controls->Add(this->numFuel);

            y += 40;
            this->lblReliability = (gcnew Label());
            this->lblReliability->Location = System::Drawing::Point(20, y);
            this->lblReliability->Size = System::Drawing::Size(120, 20);
            this->lblReliability->Text = L"Надежность (лет):";
            this->Controls->Add(this->lblReliability);

            this->numReliability = (gcnew NumericUpDown());
            this->numReliability->Location = System::Drawing::Point(150, y);
            this->numReliability->Size = System::Drawing::Size(280, 20);
            this->numReliability->Minimum = 0;
            this->numReliability->Maximum = 50;
            this->Controls->Add(this->numReliability);

            y += 40;
            this->lblComfort = (gcnew Label());
            this->lblComfort->Location = System::Drawing::Point(20, y);
            this->lblComfort->Size = System::Drawing::Size(120, 20);
            this->lblComfort->Text = L"Комфорт (баллы):";
            this->Controls->Add(this->lblComfort);

            this->numComfort = (gcnew NumericUpDown());
            this->numComfort->Location = System::Drawing::Point(150, y);
            this->numComfort->Size = System::Drawing::Size(280, 20);
            this->numComfort->Minimum = 0;
            this->numComfort->Maximum = 10;
            this->Controls->Add(this->numComfort);
        }

        void LoadBrandsToCombo()
        {
            comboSelect->Items->Clear();
            BrandNode* current = brandList->GetHead();
            while (current != nullptr) {
                String^ item = String::Format("{0} - {1}",
                    current->data.brandCode,
                    gcnew String(current->data.brandName));
                comboSelect->Items->Add(item);
                current = current->next;
            }
            if (comboSelect->Items->Count > 0) {
                comboSelect->SelectedIndex = 0;
            }
        }

        void LoadCarsToCombo()
        {
            comboSelect->Items->Clear();
            CarNode* current = carList->GetHead();
            int index = 0;
            while (current != nullptr) {
                CarBrand* brand = brandList->Find(current->data.brandCode);
                String^ brandName = brand ? gcnew String(brand->brandName) : "???";
                String^ item = String::Format("{0}. {1} {2}",
                    index,
                    brandName,
                    gcnew String(current->data.model));
                comboSelect->Items->Add(item);
                current = current->next;
                index++;
            }
            if (comboSelect->Items->Count > 0) {
                comboSelect->SelectedIndex = 0;
            }
        }

        void LoadBrandsToCarCombo()
        {
            comboBrandCode->Items->Clear();
            BrandNode* current = brandList->GetHead();
            while (current != nullptr) {
                String^ item = String::Format("{0} - {1}",
                    current->data.brandCode,
                    gcnew String(current->data.brandName));
                comboBrandCode->Items->Add(item);
                current = current->next;
            }
        }

        void comboSelect_SelectedIndexChanged(Object^ sender, EventArgs^ e)
        {
            if (comboSelect->SelectedIndex < 0) return;

            selectedIndex = comboSelect->SelectedIndex;

            if (isEditBrand) {
                LoadBrandData();
            }
            else {
                LoadCarData();
            }
        }

        void LoadBrandData()
        {
            CarBrand* brand = brandList->GetByIndex(selectedIndex);
            if (brand != nullptr) {
                numBrandCode->Value = brand->brandCode;
                txtBrandName->Text = gcnew String(brand->brandName);
                txtCountry->Text = gcnew String(brand->country);
            }
        }

        void LoadCarData()
        {
            Car* car = carList->GetByIndex(selectedIndex);
            if (car != nullptr) {
                // Устанавливаем марку
                BrandNode* current = brandList->GetHead();
                int brandIndex = 0;
                while (current != nullptr) {
                    if (current->data.brandCode == car->brandCode) {
                        comboBrandCode->SelectedIndex = brandIndex;
                        break;
                    }
                    current = current->next;
                    brandIndex++;
                }

                txtModel->Text = gcnew String(car->model);
                comboEngine->Text = gcnew String(car->engineType);
                numPrice->Value = (Decimal)car->price;
                numFuel->Value = (Decimal)car->fuelConsumption;
                numReliability->Value = car->reliability;
                numComfort->Value = car->comfort;
            }
        }

        void btnSave_Click(Object^ sender, EventArgs^ e)
        {
            try {
                if (isEditBrand) {
                    SaveBrand();
                }
                else {
                    SaveCar();
                }
            }
            catch (Exception^ ex) {
                MessageBox::Show("Ошибка: " + ex->Message, "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
            }
        }

        void SaveBrand()
        {
            if (String::IsNullOrWhiteSpace(txtBrandName->Text)) {
                MessageBox::Show("Введите название марки!", "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Warning);
                return;
            }

            if (String::IsNullOrWhiteSpace(txtCountry->Text)) {
                MessageBox::Show("Введите страну!", "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Warning);
                return;
            }

            msclr::interop::marshal_context context;
            const char* name = context.marshal_as<const char*>(txtBrandName->Text);
            const char* country = context.marshal_as<const char*>(txtCountry->Text);

            int code = (int)numBrandCode->Value;
            CarBrand brand(code, name, country);

            if (brandList->Update(code, brand)) {
                MessageBox::Show("Марка успешно обновлена!", "Успех", MessageBoxButtons::OK, MessageBoxIcon::Information);
                this->DialogResult = System::Windows::Forms::DialogResult::OK;
                this->Close();
            }
            else {
                MessageBox::Show("Ошибка обновления марки!", "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
            }
        }

        void SaveCar()
        {
            if (comboBrandCode->SelectedIndex < 0) {
                MessageBox::Show("Выберите марку!", "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Warning);
                return;
            }

            if (String::IsNullOrWhiteSpace(txtModel->Text)) {
                MessageBox::Show("Введите модель!", "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Warning);
                return;
            }

            String^ selected = comboBrandCode->SelectedItem->ToString();
            int brandCode = Int32::Parse(selected->Substring(0, selected->IndexOf(" -")));

            msclr::interop::marshal_context context;
            const char* model = context.marshal_as<const char*>(txtModel->Text);
            const char* engine = context.marshal_as<const char*>(comboEngine->Text);

            Car car(brandCode, model, engine,
                (double)numPrice->Value,
                (double)numFuel->Value,
                (int)numReliability->Value,
                (int)numComfort->Value);

            if (carList->Update(selectedIndex, car)) {
                MessageBox::Show("Автомобиль успешно обновлен!", "Успех", MessageBoxButtons::OK, MessageBoxIcon::Information);
                this->DialogResult = System::Windows::Forms::DialogResult::OK;
                this->Close();
            }
            else {
                MessageBox::Show("Ошибка обновления автомобиля!", "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
            }
        }

        void btnCancel_Click(Object^ sender, EventArgs^ e)
        {
            this->Close();
        }
    };
}
