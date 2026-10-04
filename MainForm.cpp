#include "MainForm.h"
#include "ViewForm.h"
#include "EditForm.h"
#include "AddForm.h"
#include "SearchForm.h"
#include "SortForm.h"
#include "DeleteForm.h"
#include <msclr/marshal_cppstd.h>

using namespace System;
using namespace System::Windows::Forms;

namespace CarShop {

    System::Void MainForm::menu1_LoadData_Click(System::Object^ sender, System::EventArgs^ e) {
        try {
            // Преобразуем пути к файлам
            System::String^ brandsFile = "brands.dat";
            System::String^ carsFile = "cars.dat";

            msclr::interop::marshal_context context;
            const char* brandsPath = context.marshal_as<const char*>(brandsFile);
            const char* carsPath = context.marshal_as<const char*>(carsFile);

            // Проверяем существование файлов
            if (!System::IO::File::Exists(brandsFile) || !System::IO::File::Exists(carsFile)) {
                auto result = MessageBox::Show(
                    "Файлы с данными не найдены.\nСоздать тестовые файлы?",
                    "Создание файлов",
                    MessageBoxButtons::YesNo,
                    MessageBoxIcon::Question
                );

                if (result == System::Windows::Forms::DialogResult::Yes) {
                    FileManager::CreateTestFiles(brandsPath, carsPath);
                    MessageBox::Show("Тестовые файлы созданы успешно!", "Успех", MessageBoxButtons::OK, MessageBoxIcon::Information);
                }
                else {
                    return;
                }
            }

            // Загружаем данные
            bool brandsLoaded = FileManager::LoadBrands(brandsPath, *brandList);
            bool carsLoaded = FileManager::LoadCars(carsPath, *carList);

            if (brandsLoaded && carsLoaded) {
                dataLoaded = true;
                MessageBox::Show(
                    String::Format("Данные загружены успешно!\n\nМарок: {0}\nАвтомобилей: {1}",
                        brandList->GetCount(), carList->GetCount()),
                    "Загрузка завершена",
                    MessageBoxButtons::OK,
                    MessageBoxIcon::Information
                );

                labelInfo->Text = String::Format(
                    "Данные загружены в память.\n\n" +
                    "Марок автомобилей: {0}\n" +
                    "Автомобилей в продаже: {1}\n\n" +
                    "Используйте меню для работы с данными.",
                    brandList->GetCount(), carList->GetCount()
                );
            }
            else {
                MessageBox::Show("Ошибка загрузки данных из файлов!", "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
            }
        }
        catch (Exception^ ex) {
            MessageBox::Show("Ошибка: " + ex->Message, "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
        }
    }

    System::Void MainForm::menu2_ViewBrands_Click(System::Object^ sender, System::EventArgs^ e) {
        CheckDataLoaded();
        if (!dataLoaded) return;

        ViewForm^ form = gcnew ViewForm(brandList, carList, true);
        form->ShowDialog();
    }

    System::Void MainForm::menu2_ViewCars_Click(System::Object^ sender, System::EventArgs^ e) {
        CheckDataLoaded();
        if (!dataLoaded) return;

        ViewForm^ form = gcnew ViewForm(brandList, carList, false);
        form->ShowDialog();
    }

    System::Void MainForm::menu3_Sort_Click(System::Object^ sender, System::EventArgs^ e) {
        CheckDataLoaded();
        if (!dataLoaded) return;

        SortForm^ form = gcnew SortForm(carList, brandList);
        form->ShowDialog();
    }

    System::Void MainForm::menu4_Search_Click(System::Object^ sender, System::EventArgs^ e) {
        CheckDataLoaded();
        if (!dataLoaded) return;

        SearchForm^ form = gcnew SearchForm(carList, brandList, false);
        form->ShowDialog();
    }

    System::Void MainForm::menu5_AddBrand_Click(System::Object^ sender, System::EventArgs^ e) {
        CheckDataLoaded();
        if (!dataLoaded) return;

        AddForm^ form = gcnew AddForm(brandList, carList, true);
        form->ShowDialog();
    }

    System::Void MainForm::menu5_AddCar_Click(System::Object^ sender, System::EventArgs^ e) {
        CheckDataLoaded();
        if (!dataLoaded) return;

        AddForm^ form = gcnew AddForm(brandList, carList, false);
        form->ShowDialog();
    }

    System::Void MainForm::menu6_DeleteBrand_Click(System::Object^ sender, System::EventArgs^ e) {
        CheckDataLoaded();
        if (!dataLoaded) return;

        DeleteForm^ form = gcnew DeleteForm(brandList, carList, true);
        form->ShowDialog();
    }

    System::Void MainForm::menu6_DeleteCar_Click(System::Object^ sender, System::EventArgs^ e) {
        CheckDataLoaded();
        if (!dataLoaded) return;

        DeleteForm^ form = gcnew DeleteForm(brandList, carList, false);
        form->ShowDialog();
    }

    System::Void MainForm::menu7_EditBrand_Click(System::Object^ sender, System::EventArgs^ e) {
        CheckDataLoaded();
        if (!dataLoaded) return;

        EditForm^ form = gcnew EditForm(brandList, carList, true);
        form->ShowDialog();
    }

    System::Void MainForm::menu7_EditCar_Click(System::Object^ sender, System::EventArgs^ e) {
        CheckDataLoaded();
        if (!dataLoaded) return;

        EditForm^ form = gcnew EditForm(brandList, carList, false);
        form->ShowDialog();
    }

    System::Void MainForm::menu8_SpecialFunction_Click(System::Object^ sender, System::EventArgs^ e) {
        CheckDataLoaded();
        if (!dataLoaded) return;

        SearchForm^ form = gcnew SearchForm(carList, brandList, true);
        form->ShowDialog();
    }

    // ИЗМЕНЕНО: выход без сохранения
    System::Void MainForm::menu9_ExitNoSave_Click(System::Object^ sender, System::EventArgs^ e) {
        auto result = MessageBox::Show(
            "Выйти без сохранения изменений?\nВсе несохраненные данные будут потеряны!",
            "Подтверждение выхода",
            MessageBoxButtons::YesNo,
            MessageBoxIcon::Warning
        );

        if (result == System::Windows::Forms::DialogResult::Yes) {
            forceExit = true;   // FormClosing больше ничего не спросит
            this->Close();
        }
    }

    // ИЗМЕНЕНО: выход с сохранением - вся логика (вопрос + сохранение) в FormClosing
    System::Void MainForm::menu10_ExitWithSave_Click(System::Object^ sender, System::EventArgs^ e) {
        this->Close();
    }

    // ИЗМЕНЕНО: новый метод, общий для сохранения данных
    bool MainForm::SaveAllData() {
        try {
            System::String^ brandsFile = "brands.dat";
            System::String^ carsFile = "cars.dat";

            msclr::interop::marshal_context context;
            const char* brandsPath = context.marshal_as<const char*>(brandsFile);
            const char* carsPath = context.marshal_as<const char*>(carsFile);

            bool saved = FileManager::SaveBrands(brandsPath, *brandList) &&
                FileManager::SaveCars(carsPath, *carList);

            if (!saved) {
                MessageBox::Show("Ошибка сохранения данных!", "Ошибка",
                    MessageBoxButtons::OK, MessageBoxIcon::Error);
            }
            return saved;
        }
        catch (Exception^ ex) {
            MessageBox::Show("Ошибка при сохранении: " + ex->Message, "Ошибка",
                MessageBoxButtons::OK, MessageBoxIcon::Error);
            return false;
        }
    }

    void MainForm::CheckDataLoaded() {
        if (!dataLoaded) {
            MessageBox::Show(
                "Сначала необходимо загрузить данные!\nНажмите на кнопку \"Загрузить данные\"",
                "Данные не загружены",
                MessageBoxButtons::OK,
                MessageBoxIcon::Warning
            );
        }
    }

    String^ MainForm::GetBrandNameByCode(int brandCode) {
        CarBrand* brand = brandList->Find(brandCode);
        if (brand != nullptr) {
            return gcnew String(brand->brandName);
        }
        return "Неизвестно";
    }
}
