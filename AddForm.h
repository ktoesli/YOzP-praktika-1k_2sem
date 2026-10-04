#pragma once
#include "CarList.h"
#include <msclr/marshal_cppstd.h>

namespace CarShop {

    using namespace System;
    using namespace System::Windows::Forms;
    using namespace System::Drawing;

    public ref class AddForm : public Form
    {
    public:
        AddForm(BrandList* brands, CarList* cars, bool addBrand)
        {
            this->brandList = brands;
            this->carList = cars;
            this->isAddBrand = addBrand;
            InitializeComponent();
        }

    private:
        BrandList* brandList;
        CarList* carList;
        bool isAddBrand;

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

            if (isAddBrand) {
                InitializeBrandControls();
            }
            else {
                InitializeCarControls();
            }

            // Кнопки
            this->btnSave = (gcnew Button());
            this->btnSave->Location = System::Drawing::Point(120, isAddBrand ? 150 : 350);
            this->btnSave->Name = L"btnSave";
            this->btnSave->Size = System::Drawing::Size(100, 30);
            this->btnSave->Text = L"Сохранить";
            this->btnSave->Click += gcnew EventHandler(this, &AddForm::btnSave_Click);
            this->Controls->Add(this->btnSave);

            this->btnCancel = (gcnew Button());
            this->btnCancel->Location = System::Drawing::Point(240, isAddBrand ? 150 : 350);
            this->btnCancel->Name = L"btnCancel";
            this->btnCancel->Size = System::Drawing::Size(100, 30);
            this->btnCancel->Text = L"Отмена";
            this->btnCancel->Click += gcnew EventHandler(this, &AddForm::btnCancel_Click);
            this->Controls->Add(this->btnCancel);

            // Form
            this->ClientSize = System::Drawing::Size(460, isAddBrand ? 200 : 400);
            this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
            this->MaximizeBox = false;
            this->MinimizeBox = false;
            this->Name = L"AddForm";
            this->StartPosition = FormStartPosition::CenterParent;
            this->Text = isAddBrand ? L"Добавление марки" : L"Добавление автомобиля";
            this->ResumeLayout(false);
        }

        void InitializeBrandControls()
        {
            this->lblBrandCode = (gcnew Label());
            this->lblBrandCode->Location = System::Drawing::Point(20, 20);
            this->lblBrandCode->Size = System::Drawing::Size(100, 20);
            this->lblBrandCode->Text = L"Код марки:";
            this->Controls->Add(this->lblBrandCode);

            this->numBrandCode = (gcnew NumericUpDown());
            this->numBrandCode->Location = System::Drawing::Point(150, 20);
            this->numBrandCode->Size = System::Drawing::Size(280, 20);
            this->numBrandCode->Minimum = 1;
            this->numBrandCode->Maximum = 10000;
            this->numBrandCode->Value = 1;
            this->Controls->Add(this->numBrandCode);

            this->lblBrandName = (gcnew Label());
            this->lblBrandName->Location = System::Drawing::Point(20, 60);
            this->lblBrandName->Size = System::Drawing::Size(100, 20);
            this->lblBrandName->Text = L"Название марки:";
            this->Controls->Add(this->lblBrandName);

            this->txtBrandName = (gcnew TextBox());
            this->txtBrandName->Location = System::Drawing::Point(150, 60);
            this->txtBrandName->Size = System::Drawing::Size(280, 20);
            this->Controls->Add(this->txtBrandName);

            this->lblCountry = (gcnew Label());
            this->lblCountry->Location = System::Drawing::Point(20, 100);
            this->lblCountry->Size = System::Drawing::Size(100, 20);
            this->lblCountry->Text = L"Страна:";
            this->Controls->Add(this->lblCountry);

            this->txtCountry = (gcnew TextBox());
            this->txtCountry->Location = System::Drawing::Point(150, 100);
            this->txtCountry->Size = System::Drawing::Size(280, 20);
            this->Controls->Add(this->txtCountry);
        }

        void InitializeCarControls()
        {
            int y = 20;

            this->lblCarBrandCode = (gcnew Label());
            this->lblCarBrandCode->Location = System::Drawing::Point(20, y);
            this->lblCarBrandCode->Size = System::Drawing::Size(100, 20);
            this->lblCarBrandCode->Text = L"Марка:";
            this->Controls->Add(this->lblCarBrandCode);

            this->comboBrandCode = (gcnew ComboBox());
            this->comboBrandCode->Location = System::Drawing::Point(150, y);
            this->comboBrandCode->Size = System::Drawing::Size(280, 20);
            this->comboBrandCode->DropDownStyle = ComboBoxStyle::DropDownList;
            LoadBrandsToCombo();
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
            this->comboEngine->SelectedIndex = 0;
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
            this->numPrice->Value = 20;
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
            this->numFuel->Value = 7;
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
            this->numReliability->Value = 5;
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
            this->numComfort->Value = 5;
            this->Controls->Add(this->numComfort);
        }

        void LoadBrandsToCombo()
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
            if (comboBrandCode->Items->Count > 0) {
                comboBrandCode->SelectedIndex = 0;
            }
        }

        void btnSave_Click(Object^ sender, EventArgs^ e)
        {
            try {
                if (isAddBrand) {
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

            int code = (int)numBrandCode->Value;

            // Проверка на существование кода
            if (brandList->Find(code) != nullptr) {
                MessageBox::Show("Марка с таким кодом уже существует!", "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Warning);
                return;
            }

            msclr::interop::marshal_context context;
            const char* name = context.marshal_as<const char*>(txtBrandName->Text);
            const char* country = context.marshal_as<const char*>(txtCountry->Text);

            CarBrand brand(code, name, country);
            brandList->Add(brand);

            MessageBox::Show("Марка успешно добавлена!", "Успех", MessageBoxButtons::OK, MessageBoxIcon::Information);
            this->DialogResult = System::Windows::Forms::DialogResult::OK;
            this->Close();
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

            // Извлекаем код марки из выбранного элемента
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

            carList->Add(car);

            MessageBox::Show("Автомобиль успешно добавлен!", "Успех", MessageBoxButtons::OK, MessageBoxIcon::Information);
            this->DialogResult = System::Windows::Forms::DialogResult::OK;
            this->Close();
        }

        void btnCancel_Click(Object^ sender, EventArgs^ e)
        {
            this->Close();
        }
    };
}
