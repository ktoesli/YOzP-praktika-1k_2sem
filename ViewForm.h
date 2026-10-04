#pragma once
#include "CarList.h"

namespace CarShop {

    using namespace System;
    using namespace System::Windows::Forms;
    using namespace System::Drawing;

    public ref class ViewForm : public Form
    {
    public:
        ViewForm(BrandList* brands, CarList* cars, bool showBrands)
        {
            this->brandList = brands;
            this->carList = cars;
            this->isBrandView = showBrands;
            InitializeComponent();
            LoadData();
        }

    private:
        BrandList* brandList;
        CarList* carList;
        bool isBrandView;

        DataGridView^ dataGridView;
        Button^ btnClose;

        void InitializeComponent()
        {
            this->dataGridView = (gcnew DataGridView());
            this->btnClose = (gcnew Button());
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView))->BeginInit();
            this->SuspendLayout();

            // dataGridView
            this->dataGridView->AllowUserToAddRows = false;
            this->dataGridView->AllowUserToDeleteRows = false;
            this->dataGridView->Anchor = static_cast<AnchorStyles>((((AnchorStyles::Top | AnchorStyles::Bottom)
                | AnchorStyles::Left) | AnchorStyles::Right));
            this->dataGridView->AutoSizeColumnsMode = DataGridViewAutoSizeColumnsMode::Fill;
            this->dataGridView->ColumnHeadersHeightSizeMode = DataGridViewColumnHeadersHeightSizeMode::AutoSize;
            this->dataGridView->Location = System::Drawing::Point(12, 12);
            this->dataGridView->Name = L"dataGridView";
            this->dataGridView->ReadOnly = true;
            this->dataGridView->SelectionMode = DataGridViewSelectionMode::FullRowSelect;
            this->dataGridView->Size = System::Drawing::Size(760, 388);
            this->dataGridView->TabIndex = 0;

            // btnClose
            this->btnClose->Anchor = static_cast<AnchorStyles>((AnchorStyles::Bottom | AnchorStyles::Right));
            this->btnClose->Location = System::Drawing::Point(672, 415);
            this->btnClose->Name = L"btnClose";
            this->btnClose->Size = System::Drawing::Size(100, 30);
            this->btnClose->TabIndex = 1;
            this->btnClose->Text = L"Закрыть";
            this->btnClose->UseVisualStyleBackColor = true;
            this->btnClose->Click += gcnew EventHandler(this, &ViewForm::btnClose_Click);

            // ViewForm
            this->ClientSize = System::Drawing::Size(784, 461);
            this->Controls->Add(this->btnClose);
            this->Controls->Add(this->dataGridView);
            this->Name = L"ViewForm";
            this->StartPosition = FormStartPosition::CenterParent;
            this->Text = isBrandView ? L"Просмотр марок" : L"Просмотр автомобилей";
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView))->EndInit();
            this->ResumeLayout(false);
        }

        void LoadData()
        {
            if (isBrandView) {
                LoadBrands();
            }
            else {
                LoadCars();
            }
        }

        void LoadBrands()
        {
            dataGridView->Columns->Clear();
            dataGridView->Rows->Clear();

            dataGridView->Columns->Add("Code", "Код марки");
            dataGridView->Columns->Add("Name", "Название марки");
            dataGridView->Columns->Add("Country", "Страна");

            BrandNode* current = brandList->GetHead();
            while (current != nullptr) {
                dataGridView->Rows->Add(
                    current->data.brandCode,
                    gcnew String(current->data.brandName),
                    gcnew String(current->data.country)
                );
                current = current->next;
            }
        }

        void LoadCars()
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
                // Находим название марки по коду
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

        void btnClose_Click(Object^ sender, EventArgs^ e)
        {
            this->Close();
        }
    };
}
