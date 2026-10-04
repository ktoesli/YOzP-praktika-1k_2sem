#pragma once
#include "CarList.h"

namespace CarShop {

    using namespace System;
    using namespace System::Windows::Forms;
    using namespace System::Drawing;

    public ref class DeleteForm : public Form
    {
    public:
        DeleteForm(BrandList* brands, CarList* cars, bool deleteBrand)
        {
            this->brandList = brands;
            this->carList = cars;
            this->isDeleteBrand = deleteBrand;
            InitializeComponent();
        }

    private:
        BrandList* brandList;
        CarList* carList;
        bool isDeleteBrand;

        Label^ lblSelect;
        ComboBox^ comboSelect;
        Button^ btnDelete;
        Button^ btnCancel;

        void InitializeComponent()
        {
            this->lblSelect = (gcnew Label());
            this->comboSelect = (gcnew ComboBox());
            this->btnDelete = (gcnew Button());
            this->btnCancel = (gcnew Button());
            this->SuspendLayout();

            // lblSelect
            this->lblSelect->Location = System::Drawing::Point(20, 20);
            this->lblSelect->Size = System::Drawing::Size(100, 20);
            this->lblSelect->Text = L"Выберите:";

            // comboSelect
            this->comboSelect->Location = System::Drawing::Point(150, 20);
            this->comboSelect->Size = System::Drawing::Size(280, 20);
            this->comboSelect->DropDownStyle = ComboBoxStyle::DropDownList;

            if (isDeleteBrand) {
                LoadBrandsToCombo();
            }
            else {
                LoadCarsToCombo();
            }

            // btnDelete
            this->btnDelete->Location = System::Drawing::Point(120, 70);
            this->btnDelete->Size = System::Drawing::Size(100, 30);
            this->btnDelete->Text = L"Удалить";
            this->btnDelete->Click += gcnew EventHandler(this, &DeleteForm::btnDelete_Click);

            // btnCancel
            this->btnCancel->Location = System::Drawing::Point(240, 70);
            this->btnCancel->Size = System::Drawing::Size(100, 30);
            this->btnCancel->Text = L"Отмена";
            this->btnCancel->Click += gcnew EventHandler(this, &DeleteForm::btnCancel_Click);

            // DeleteForm
            this->ClientSize = System::Drawing::Size(460, 120);
            this->Controls->Add(this->lblSelect);
            this->Controls->Add(this->comboSelect);
            this->Controls->Add(this->btnDelete);
            this->Controls->Add(this->btnCancel);
            this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
            this->MaximizeBox = false;
            this->MinimizeBox = false;
            this->Name = L"DeleteForm";
            this->StartPosition = FormStartPosition::CenterParent;
            this->Text = isDeleteBrand ? L"Удаление марки" : L"Удаление автомобиля";
            this->ResumeLayout(false);
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

        void btnDelete_Click(Object^ sender, EventArgs^ e)
        {
            if (comboSelect->SelectedIndex < 0) {
                MessageBox::Show("Выберите элемент для удаления!", "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Warning);
                return;
            }

            auto result = MessageBox::Show(
                "Вы уверены, что хотите удалить выбранный элемент?",
                "Подтверждение удаления",
                MessageBoxButtons::YesNo,
                MessageBoxIcon::Question
            );

            if (result == System::Windows::Forms::DialogResult::Yes) {
                try {
                    if (isDeleteBrand) {
                        DeleteBrand();
                    }
                    else {
                        DeleteCar();
                    }
                }
                catch (Exception^ ex) {
                    MessageBox::Show("Ошибка: " + ex->Message, "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
                }
            }
        }

        void DeleteBrand()
        {
            int selectedIndex = comboSelect->SelectedIndex;
            CarBrand* brand = brandList->GetByIndex(selectedIndex);

            if (brand != nullptr) {
                int brandCode = brand->brandCode;

                // Проверяем, есть ли автомобили этой марки
                CarNode* current = carList->GetHead();
                bool hasRelatedCars = false;
                while (current != nullptr) {
                    if (current->data.brandCode == brandCode) {
                        hasRelatedCars = true;
                        break;
                    }
                    current = current->next;
                }

                if (hasRelatedCars) {
                    auto result = MessageBox::Show(
                        "У этой марки есть автомобили в списке!\nУдалить марку и все связанные автомобили?",
                        "Предупреждение",
                        MessageBoxButtons::YesNo,
                        MessageBoxIcon::Warning
                    );

                    if (result == System::Windows::Forms::DialogResult::No) {
                        return;
                    }

                    // Удаляем все автомобили этой марки
                    int i = 0;
                    current = carList->GetHead();
                    while (i < carList->GetCount()) {
                        Car* car = carList->GetByIndex(i);
                        if (car != nullptr && car->brandCode == brandCode) {
                            carList->Remove(i);
                            // Не увеличиваем i, так как список сдвинулся
                        }
                        else {
                            i++;
                        }
                    }
                }

                if (brandList->Remove(brandCode)) {
                    MessageBox::Show("Марка успешно удалена!", "Успех", MessageBoxButtons::OK, MessageBoxIcon::Information);
                    this->DialogResult = System::Windows::Forms::DialogResult::OK;
                    this->Close();
                }
                else {
                    MessageBox::Show("Ошибка удаления марки!", "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
                }
            }
        }

        void DeleteCar()
        {
            int selectedIndex = comboSelect->SelectedIndex;

            if (carList->Remove(selectedIndex)) {
                MessageBox::Show("Автомобиль успешно удален!", "Успех", MessageBoxButtons::OK, MessageBoxIcon::Information);
                this->DialogResult = System::Windows::Forms::DialogResult::OK;
                this->Close();
            }
            else {
                MessageBox::Show("Ошибка удаления автомобиля!", "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
            }
        }

        void btnCancel_Click(Object^ sender, EventArgs^ e)
        {
            this->Close();
        }
    };
}
