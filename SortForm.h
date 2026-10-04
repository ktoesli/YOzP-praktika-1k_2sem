#pragma once
#include "CarList.h"

namespace CarShop {

    using namespace System;
    using namespace System::Windows::Forms;
    using namespace System::Drawing;

    public ref class SortForm : public Form
    {
    public:
        SortForm(CarList* cars, BrandList* brands)
        {
            this->carList = cars;
            this->brandList = brands;
            InitializeComponent();
        }

    private:
        CarList* carList;
        BrandList* brandList;

        Label^ lblInfo;
        Label^ lblSortBy;
        ComboBox^ comboSortBy;
        Button^ btnSort;
        Button^ btnCancel;
        DataGridView^ dataGridView;

        void InitializeComponent()
        {
            this->lblInfo = (gcnew Label());
            this->lblSortBy = (gcnew Label());
            this->comboSortBy = (gcnew ComboBox());
            this->btnSort = (gcnew Button());
            this->btnCancel = (gcnew Button());
            this->dataGridView = (gcnew DataGridView());
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView))->BeginInit();
            this->SuspendLayout();

            // lblInfo
            this->lblInfo->Location = System::Drawing::Point(20, 20);
            this->lblInfo->Size = System::Drawing::Size(740, 40);
            this->lblInfo->Text = L"Сортировка производится сначала по маркам,\nа внутри каждой марки - по выбранному параметру.";

            // lblSortBy
            this->lblSortBy->Location = System::Drawing::Point(20, 70);
            this->lblSortBy->Size = System::Drawing::Size(150, 20);
            this->lblSortBy->Text = L"Сортировать внутри марки по:";

            // comboSortBy
            this->comboSortBy->Location = System::Drawing::Point(200, 70);
            this->comboSortBy->Size = System::Drawing::Size(250, 20);
            this->comboSortBy->DropDownStyle = ComboBoxStyle::DropDownList;
            this->comboSortBy->Items->AddRange(gcnew cli::array<String^> {
                "Модели (алфавит)",
                "Цене (возрастание)",
                "Расходу топлива (возрастание)",
                "Надежности (убывание)",
                "Комфорту (убывание)"
            });
            this->comboSortBy->SelectedIndex = 0;

            // btnSort
            this->btnSort->Location = System::Drawing::Point(500, 65);
            this->btnSort->Size = System::Drawing::Size(120, 30);
            this->btnSort->Text = L"Сортировать";
            this->btnSort->Click += gcnew EventHandler(this, &SortForm::btnSort_Click);

            // btnCancel
            this->btnCancel->Location = System::Drawing::Point(640, 65);
            this->btnCancel->Size = System::Drawing::Size(120, 30);
            this->btnCancel->Text = L"Закрыть";
            this->btnCancel->Click += gcnew EventHandler(this, &SortForm::btnCancel_Click);

            // dataGridView
            this->dataGridView->AllowUserToAddRows = false;
            this->dataGridView->AllowUserToDeleteRows = false;
            this->dataGridView->Anchor = static_cast<AnchorStyles>((((AnchorStyles::Top | AnchorStyles::Bottom)
                | AnchorStyles::Left) | AnchorStyles::Right));
            this->dataGridView->AutoSizeColumnsMode = DataGridViewAutoSizeColumnsMode::Fill;
            this->dataGridView->ColumnHeadersHeightSizeMode = DataGridViewColumnHeadersHeightSizeMode::AutoSize;
            this->dataGridView->Location = System::Drawing::Point(20, 110);
            this->dataGridView->Name = L"dataGridView";
            this->dataGridView->ReadOnly = true;
            this->dataGridView->SelectionMode = DataGridViewSelectionMode::FullRowSelect;
            this->dataGridView->Size = System::Drawing::Size(740, 330);
            this->dataGridView->TabIndex = 0;

            // SortForm
            this->ClientSize = System::Drawing::Size(784, 461);
            this->Controls->Add(this->dataGridView);
            this->Controls->Add(this->btnCancel);
            this->Controls->Add(this->btnSort);
            this->Controls->Add(this->comboSortBy);
            this->Controls->Add(this->lblSortBy);
            this->Controls->Add(this->lblInfo);
            this->Name = L"SortForm";
            this->StartPosition = FormStartPosition::CenterParent;
            this->Text = L"Сортировка автомобилей";
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView))->EndInit();
            this->ResumeLayout(false);

            LoadData();
        }

        void btnSort_Click(Object^ sender, EventArgs^ e)
        {
            if (comboSortBy->SelectedIndex < 0) {
                MessageBox::Show("Выберите параметр сортировки!", "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Warning);
                return;
            }

            // Выполняем сортировку
            carList->SortByBrandAndParameter(comboSortBy->SelectedIndex);

            // Обновляем отображение
            LoadData();

            MessageBox::Show("Сортировка выполнена успешно!", "Успех", MessageBoxButtons::OK, MessageBoxIcon::Information);
        }

        void LoadData()
        {
            dataGridView->Columns->Clear();
            dataGridView->Rows->Clear();

            dataGridView->Columns->Add("BrandCode", "Код марки");
            dataGridView->Columns->Add("BrandName", "Марка");
            dataGridView->Columns->Add("Model", "Модель");
            dataGridView->Columns->Add("Engine", "Двигатель");
            dataGridView->Columns->Add("Price", "Цена (тыс.$)");
            dataGridView->Columns->Add("Fuel", "Расход (л/100км)");
            dataGridView->Columns->Add("Reliability", "Надежность (лет)");
            dataGridView->Columns->Add("Comfort", "Комфорт (баллы)");

            CarNode* current = carList->GetHead();
            while (current != nullptr) {
                CarBrand* brand = brandList->Find(current->data.brandCode);
                String^ brandName = brand ? gcnew String(brand->brandName) : "Неизвестно";

                dataGridView->Rows->Add(
                    current->data.brandCode,
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
        }

        void btnCancel_Click(Object^ sender, EventArgs^ e)
        {
            this->Close();
        }
    };
}
