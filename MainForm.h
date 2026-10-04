#pragma once
#include "CarList.h"
#include "FileManager.h"

namespace CarShop {

    using namespace System;
    using namespace System::ComponentModel;
    using namespace System::Collections;
    using namespace System::Windows::Forms;
    using namespace System::Data;
    using namespace System::Drawing;

    public ref class MainForm : public System::Windows::Forms::Form
    {
    public:
        MainForm(void)
        {
            InitializeComponent();
            brandList = new BrandList();
            carList = new CarList();
            dataLoaded = false;
            forceExit = false;   // ИЗМЕНЕНО: добавлено
        }

    protected:
        ~MainForm()
        {
            if (components)
            {
                delete components;
            }
            // Освобождаем динамическую память
            if (brandList != nullptr) {
                delete brandList;
            }
            if (carList != nullptr) {
                delete carList;
            }
        }

    private:


        // Динамические списки на C++
        BrandList* brandList;
        CarList* carList;
        bool dataLoaded;
        bool forceExit;   // ИЗМЕНЕНО: добавлено. true = закрываем без повторных вопросов

        // Компоненты формы
        System::Windows::Forms::MenuStrip^ menuStrip;
        System::Windows::Forms::ToolStripMenuItem^ menu1_LoadData;
        System::Windows::Forms::ToolStripMenuItem^ menu2_ViewData;
        System::Windows::Forms::ToolStripMenuItem^ menu2_ViewBrands;
        System::Windows::Forms::ToolStripMenuItem^ menu2_ViewCars;
        System::Windows::Forms::ToolStripMenuItem^ menu3_Sort;
        System::Windows::Forms::ToolStripMenuItem^ menu4_Search;
        System::Windows::Forms::ToolStripMenuItem^ menu5_Add;
        System::Windows::Forms::ToolStripMenuItem^ menu5_AddBrand;
        System::Windows::Forms::ToolStripMenuItem^ menu5_AddCar;
        System::Windows::Forms::ToolStripMenuItem^ menu6_Delete;
        System::Windows::Forms::ToolStripMenuItem^ menu6_DeleteBrand;
        System::Windows::Forms::ToolStripMenuItem^ menu6_DeleteCar;
        System::Windows::Forms::ToolStripMenuItem^ menu7_Edit;
        System::Windows::Forms::ToolStripMenuItem^ menu7_EditBrand;
        System::Windows::Forms::ToolStripMenuItem^ menu7_EditCar;
        System::Windows::Forms::ToolStripMenuItem^ menu8_SpecialFunction;
        System::Windows::Forms::ToolStripMenuItem^ menu9_ExitNoSave;
        System::Windows::Forms::ToolStripMenuItem^ menu10_ExitWithSave;
        System::Windows::Forms::Label^ labelInfo;
        System::Windows::Forms::PictureBox^ pictureBoxLogo;
        System::ComponentModel::Container^ components;

        System::Windows::Forms::Button^ oneButton;
        System::Windows::Forms::Button^ viewButton;
        System::Windows::Forms::Button^ viewBrandButton;
        System::Windows::Forms::Button^ SpecialFunctionButoon;

#pragma region 
        void InitializeComponent(void)
        {
            this->menuStrip = (gcnew System::Windows::Forms::MenuStrip());
            this->menu1_LoadData = (gcnew System::Windows::Forms::ToolStripMenuItem());
            this->menu2_ViewData = (gcnew System::Windows::Forms::ToolStripMenuItem());
            this->menu2_ViewBrands = (gcnew System::Windows::Forms::ToolStripMenuItem());
            this->menu2_ViewCars = (gcnew System::Windows::Forms::ToolStripMenuItem());
            this->menu3_Sort = (gcnew System::Windows::Forms::ToolStripMenuItem());
            this->menu4_Search = (gcnew System::Windows::Forms::ToolStripMenuItem());
            this->menu5_Add = (gcnew System::Windows::Forms::ToolStripMenuItem());
            this->menu5_AddBrand = (gcnew System::Windows::Forms::ToolStripMenuItem());
            this->menu5_AddCar = (gcnew System::Windows::Forms::ToolStripMenuItem());
            this->menu6_Delete = (gcnew System::Windows::Forms::ToolStripMenuItem());
            this->menu6_DeleteBrand = (gcnew System::Windows::Forms::ToolStripMenuItem());
            this->menu6_DeleteCar = (gcnew System::Windows::Forms::ToolStripMenuItem());
            this->menu7_Edit = (gcnew System::Windows::Forms::ToolStripMenuItem());
            this->menu7_EditBrand = (gcnew System::Windows::Forms::ToolStripMenuItem());
            this->menu7_EditCar = (gcnew System::Windows::Forms::ToolStripMenuItem());
            this->menu8_SpecialFunction = (gcnew System::Windows::Forms::ToolStripMenuItem());
            this->menu9_ExitNoSave = (gcnew System::Windows::Forms::ToolStripMenuItem());
            this->menu10_ExitWithSave = (gcnew System::Windows::Forms::ToolStripMenuItem());
            this->labelInfo = (gcnew System::Windows::Forms::Label());
            this->pictureBoxLogo = (gcnew System::Windows::Forms::PictureBox());

            this->oneButton = (gcnew System::Windows::Forms::Button);
            this->viewButton = (gcnew System::Windows::Forms::Button);
            this->viewBrandButton = (gcnew System::Windows::Forms::Button);
            this->SpecialFunctionButoon = (gcnew System::Windows::Forms::Button);

            this->FormClosing += gcnew System::Windows::Forms::FormClosingEventHandler(this, &MainForm::MyForm_FormClosing);

            this->menuStrip->SuspendLayout();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBoxLogo))->BeginInit();
            this->SuspendLayout();
            //
            // menuStrip
            //                                                                          (количество элементов вверху)
            this->menuStrip->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(5) {
                
                    this->menu3_Sort, this->menu4_Search, this->menu5_Add, this->menu6_Delete, this->menu7_Edit,
                    //this->menu8_SpecialFunction, //this->menu9_ExitNoSave, this->menu10_ExitWithSave
            });
            this->menuStrip->Location = System::Drawing::Point(0, 0);
            this->menuStrip->Name = L"menuStrip";
            this->menuStrip->Size = System::Drawing::Size(884, 24);
            this->menuStrip->TabIndex = 0;
            //
            // menu1_LoadData
            //
            this->menu1_LoadData->Name = L"menu1_LoadData";
            this->menu1_LoadData->Size = System::Drawing::Size(135, 20);
            this->menu1_LoadData->Text = L"Загрузить данные";
            this->menu1_LoadData->Click += gcnew System::EventHandler(this, &MainForm::menu1_LoadData_Click);
            //
            // menu2_ViewData
            //
            this->menu2_ViewData->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
                this->menu2_ViewBrands,
                    this->menu2_ViewCars
            });
            this->menu2_ViewData->Name = L"menu2_ViewData";
            this->menu2_ViewData->Size = System::Drawing::Size(89, 20);
            this->menu2_ViewData->Text = L"2. Просмотр";
            //
            // menu2_ViewBrands
            //
            this->menu2_ViewBrands->Name = L"menu2_ViewBrands";
            this->menu2_ViewBrands->Size = System::Drawing::Size(152, 22);
            this->menu2_ViewBrands->Text = L"Марки";
            this->menu2_ViewBrands->Click += gcnew System::EventHandler(this, &MainForm::menu2_ViewBrands_Click);
            //
            // menu2_ViewCars
            //
            this->menu2_ViewCars->Name = L"menu2_ViewCars";
            this->menu2_ViewCars->Size = System::Drawing::Size(152, 22);
            this->menu2_ViewCars->Text = L"Автомобили";
            this->menu2_ViewCars->Click += gcnew System::EventHandler(this, &MainForm::menu2_ViewCars_Click);
            //
            // menu3_Sort
            //
            this->menu3_Sort->Name = L"menu3_Sort";
            this->menu3_Sort->Size = System::Drawing::Size(105, 20);
            this->menu3_Sort->Text = L"Сортировка";
            this->menu3_Sort->Click += gcnew System::EventHandler(this, &MainForm::menu3_Sort_Click);
            //
            // menu4_Search
            //
            this->menu4_Search->Name = L"menu4_Search";
            this->menu4_Search->Size = System::Drawing::Size(69, 20);
            this->menu4_Search->Text = L"Поиск";
            this->menu4_Search->Click += gcnew System::EventHandler(this, &MainForm::menu4_Search_Click);
            //
            // menu5_Add
            //
            this->menu5_Add->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
                this->menu5_AddBrand,
                    this->menu5_AddCar
            });
            this->menu5_Add->Name = L"menu5_Add";
            this->menu5_Add->Size = System::Drawing::Size(93, 20);
            this->menu5_Add->Text = L"Добавить";
            //
            // menu5_AddBrand
            //
            this->menu5_AddBrand->Name = L"menu5_AddBrand";
            this->menu5_AddBrand->Size = System::Drawing::Size(152, 22);
            this->menu5_AddBrand->Text = L"Марку";
            this->menu5_AddBrand->Click += gcnew System::EventHandler(this, &MainForm::menu5_AddBrand_Click);
            //
            // menu5_AddCar
            //
            this->menu5_AddCar->Name = L"menu5_AddCar";
            this->menu5_AddCar->Size = System::Drawing::Size(152, 22);
            this->menu5_AddCar->Text = L"Автомобиль";
            this->menu5_AddCar->Click += gcnew System::EventHandler(this, &MainForm::menu5_AddCar_Click);
            //
            // menu6_Delete
            //
            this->menu6_Delete->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
                this->menu6_DeleteBrand,
                    this->menu6_DeleteCar
            });
            this->menu6_Delete->Name = L"menu6_Delete";
            this->menu6_Delete->Size = System::Drawing::Size(82, 20);
            this->menu6_Delete->Text = L"Удалить";
            //
            // menu6_DeleteBrand
            //
            this->menu6_DeleteBrand->Name = L"menu6_DeleteBrand";
            this->menu6_DeleteBrand->Size = System::Drawing::Size(152, 22);
            this->menu6_DeleteBrand->Text = L"Марку";
            this->menu6_DeleteBrand->Click += gcnew System::EventHandler(this, &MainForm::menu6_DeleteBrand_Click);
            //
            // menu6_DeleteCar
            //
            this->menu6_DeleteCar->Name = L"menu6_DeleteCar";
            this->menu6_DeleteCar->Size = System::Drawing::Size(152, 22);
            this->menu6_DeleteCar->Text = L"Автомобиль";
            this->menu6_DeleteCar->Click += gcnew System::EventHandler(this, &MainForm::menu6_DeleteCar_Click);
            //
            // menu7_Edit
            //
            this->menu7_Edit->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
                this->menu7_EditBrand,
                    this->menu7_EditCar
            });
            this->menu7_Edit->Name = L"menu7_Edit";
            this->menu7_Edit->Size = System::Drawing::Size(129, 20);
            this->menu7_Edit->Text = L"Редактирование";
            //
            // menu7_EditBrand
            //
            this->menu7_EditBrand->Name = L"menu7_EditBrand";
            this->menu7_EditBrand->Size = System::Drawing::Size(152, 22);
            this->menu7_EditBrand->Text = L"Марку";
            this->menu7_EditBrand->Click += gcnew System::EventHandler(this, &MainForm::menu7_EditBrand_Click);
            //
            // menu7_EditCar
            //
            this->menu7_EditCar->Name = L"menu7_EditCar";
            this->menu7_EditCar->Size = System::Drawing::Size(152, 22);
            this->menu7_EditCar->Text = L"Автомобиль";
            this->menu7_EditCar->Click += gcnew System::EventHandler(this, &MainForm::menu7_EditCar_Click);
            //
            // menu8_SpecialFunction
            //
            this->menu8_SpecialFunction->Name = L"menu8_SpecialFunction";
            this->menu8_SpecialFunction->Size = System::Drawing::Size(188, 20);
            this->menu8_SpecialFunction->Text = L"Поиск по требованиям покупателя";
            this->menu8_SpecialFunction->Click += gcnew System::EventHandler(this, &MainForm::menu8_SpecialFunction_Click);
            ////
            //// menu9_ExitNoSave
            ////
            //this->menu9_ExitNoSave->Name = L"menu9_ExitNoSave";
            //this->menu9_ExitNoSave->Size = System::Drawing::Size(143, 20);
            //this->menu9_ExitNoSave->Text = L"Выход без сохранения";
            //this->menu9_ExitNoSave->Click += gcnew System::EventHandler(this, &MainForm::menu9_ExitNoSave_Click);
            ////
            // menu10_ExitWithSave
            ////
            //this->menu10_ExitWithSave->Name = L"menu10_ExitWithSave";
            //this->menu10_ExitWithSave->Size = System::Drawing::Size(146, 20);
            //this->menu10_ExitWithSave->Text = L"Выход с сохранением";
            //this->menu10_ExitWithSave->Click += gcnew System::EventHandler(this, &MainForm::menu10_ExitWithSave_Click);
            ////
            // button_test
            //
            this->oneButton->Name = L"test_but";
            this->oneButton->Text = L"Загрузить / обновить данные";
            this->oneButton->Size = Drawing::Size(200, 80);
            //this->oneButton->Location = Point(this->ClientSize.Width , this->ClientSize.Height / 2 - 50);
            this->oneButton->Location = Point(70, 100);
            this->oneButton->Click += gcnew System::EventHandler(this, &MainForm::menu1_LoadData_Click);
            // 
            // view_button
            // 
            this->viewButton->Name = L"view_button";
            this->viewButton->Text = L"Просмотреть модели машин";
            this->viewButton->Size = Drawing::Size(200, 80);
            //this->viewButton->Location = Point(this->ClientSize.Width , this->ClientSize.Height / 2 - 50);
            this->viewButton->Location = Point(350, 100);
            this->viewButton->Click += gcnew System::EventHandler(this, &MainForm::menu2_ViewCars_Click);
            //
            // view_brand_button
            // 
            this->viewBrandButton->Name = L"view_button";
            this->viewBrandButton->Text = L"Просмотреть марки машин";
            this->viewBrandButton->Size = Drawing::Size(200, 80);
            //this->viewButton->Location = Point(this->ClientSize.Width , this->ClientSize.Height / 2 - 50);
            this->viewBrandButton->Location = Point(350, 200);
            this->viewBrandButton->Click += gcnew System::EventHandler(this, &MainForm::menu2_ViewBrands_Click);
            //
			// poisk_po_trebovaniyam_button
            //
            this->SpecialFunctionButoon->Name = L"SpecialFunctionButton";
            this->SpecialFunctionButoon->Text = L"Поиск по требованиям покупателя";
            this->SpecialFunctionButoon->Size = Drawing::Size(200, 80);
            this->SpecialFunctionButoon->Location = Point(70, 200);
            this->SpecialFunctionButoon->Click += gcnew System::EventHandler(this, &MainForm::menu8_SpecialFunction_Click);
            //
            // labelInfo
            //
            this->labelInfo->Anchor = System::Windows::Forms::AnchorStyles::None;
            this->labelInfo->Font = (gcnew System::Drawing::Font(L"Segoe UI", 14.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(204)));
            this->labelInfo->Location = System::Drawing::Point(12, 100);
            this->labelInfo->Name = L"labelInfo";
            this->labelInfo->Size = System::Drawing::Size(860, 350);
            this->labelInfo->TabIndex = 1;
            this->labelInfo->Text = L"Добро пожаловать в систему управления автомагазином!\r\n\r\nВыберите \"1. Загрузить да"
                L"нные\" для начала работы.\r\n\r\nЕсли файлы с данными отсутствуют,\r\nони будут созданы а"
                L"втоматически с тестовыми данными.";
            this->labelInfo->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
            //
            // pictureBoxLogo
            //
            //this->pictureBoxLogo->Location = System::Drawing::Point(342, 250);
            //this->pictureBoxLogo->Name = L"pictureBoxLogo";
            //this->pictureBoxLogo->Size = System::Drawing::Size(200, 200);
            //this->pictureBoxLogo->TabIndex = 2;
            //this->pictureBoxLogo->TabStop = false;
            //
            // MainForm
            //
            this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
            this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
            this->ClientSize = System::Drawing::Size(600, 400);
            this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
            this->MaximizeBox = false;
            //this->Controls->Add(this->pictureBoxLogo);
            //this->Controls->Add(this->labelInfo);
            this->Controls->Add(this->menuStrip);
            this->Controls->Add(this->oneButton);
            this->Controls->Add(this->viewButton);
            this->Controls->Add(this->viewBrandButton);
            this->Controls->Add(this->SpecialFunctionButoon);

            this->MainMenuStrip = this->menuStrip;
            this->Name = L"MainForm";
            this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
            this->Text = L"Car4u";
            this->menuStrip->ResumeLayout(false);
            this->menuStrip->PerformLayout();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBoxLogo))->EndInit();
            this->ResumeLayout(false);
            this->PerformLayout();

        }
#pragma endregion

    private:
        // ИЗМЕНЕНО: обработчик закрытия формы (крестик, Alt+F4, пункт меню 10)
        System::Void MyForm_FormClosing(System::Object^ sender, System::Windows::Forms::FormClosingEventArgs^ e)
        {
            // Уже подтвердили выход или данные не загружены - просто закрываемся
            if (forceExit || !dataLoaded) return;

            auto result = MessageBox::Show(
                "Сохранить изменения перед выходом?",
                "Подтверждение выхода",
                MessageBoxButtons::YesNoCancel,
                MessageBoxIcon::Question
            );

            if (result == System::Windows::Forms::DialogResult::Cancel) {
                e->Cancel = true;      // остаёмся в программе
                return;
            }

            if (result == System::Windows::Forms::DialogResult::Yes) {
                if (!SaveAllData()) {  // ошибка сохранения - не закрываем
                    e->Cancel = true;
                    return;
                }
            }

            forceExit = true;          // форма закроется сама, вопросов больше не будет
        }

        // Обработчики меню
        System::Void menu1_LoadData_Click(System::Object^ sender, System::EventArgs^ e);
        System::Void menu2_ViewBrands_Click(System::Object^ sender, System::EventArgs^ e);
        System::Void menu2_ViewCars_Click(System::Object^ sender, System::EventArgs^ e);
        System::Void menu3_Sort_Click(System::Object^ sender, System::EventArgs^ e);
        System::Void menu4_Search_Click(System::Object^ sender, System::EventArgs^ e);
        System::Void menu5_AddBrand_Click(System::Object^ sender, System::EventArgs^ e);
        System::Void menu5_AddCar_Click(System::Object^ sender, System::EventArgs^ e);
        System::Void menu6_DeleteBrand_Click(System::Object^ sender, System::EventArgs^ e);
        System::Void menu6_DeleteCar_Click(System::Object^ sender, System::EventArgs^ e);
        System::Void menu7_EditBrand_Click(System::Object^ sender, System::EventArgs^ e);
        System::Void menu7_EditCar_Click(System::Object^ sender, System::EventArgs^ e);
        System::Void menu8_SpecialFunction_Click(System::Object^ sender, System::EventArgs^ e);
        System::Void menu9_ExitNoSave_Click(System::Object^ sender, System::EventArgs^ e);
        System::Void menu10_ExitWithSave_Click(System::Object^ sender, System::EventArgs^ e);

        // Вспомогательные методы
        void CheckDataLoaded();
        bool SaveAllData();   // ИЗМЕНЕНО: добавлено
        String^ GetBrandNameByCode(int brandCode);
    };
}
