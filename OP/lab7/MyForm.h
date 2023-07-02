#pragma once

#include <string>
#include "FileRepresent.h"
#include "Performer.h"
#include <msclr\marshal_cppstd.h>

using namespace std;

namespace lab72 {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	IntArr OperatedFile, ResFile;

	/// <summary>
	/// Summary for MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^ Button_add;
	protected:
	private: System::Windows::Forms::Button^ Button_clear;
	private: System::Windows::Forms::TextBox^ TextBox_append;
	private: System::Windows::Forms::Label^ Label_Error;
	private: System::Windows::Forms::Label^ From_To_label;
	private: System::Windows::Forms::TextBox^ TextBox_save;
	private: System::Windows::Forms::Button^ Button_load;
	private: System::Windows::Forms::Label^ File_out_text;
	private: System::Windows::Forms::Label^ File_in_text;
	private: System::Windows::Forms::TextBox^ TextBox_load;
	private: System::Windows::Forms::Label^ File_out_label;
	private: System::Windows::Forms::Label^ File_in_label;
	private: System::Windows::Forms::TextBox^ TextBox_NumIncreace;
	private: System::Windows::Forms::TextBox^ TextBox_NumTo;
	private: System::Windows::Forms::TextBox^ TextBox_NumFrom;

	private: System::Windows::Forms::Button^ Button_calculate;
	private: System::Windows::Forms::Button^ Button_Save_In;
	private: System::Windows::Forms::Button^ Button_save_out;
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::Button^ Gen_random_but;
	private: System::Windows::Forms::TextBox^ Gen_Random;





	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->Button_add = (gcnew System::Windows::Forms::Button());
			this->Button_clear = (gcnew System::Windows::Forms::Button());
			this->TextBox_append = (gcnew System::Windows::Forms::TextBox());
			this->Label_Error = (gcnew System::Windows::Forms::Label());
			this->From_To_label = (gcnew System::Windows::Forms::Label());
			this->TextBox_save = (gcnew System::Windows::Forms::TextBox());
			this->Button_load = (gcnew System::Windows::Forms::Button());
			this->File_out_text = (gcnew System::Windows::Forms::Label());
			this->File_in_text = (gcnew System::Windows::Forms::Label());
			this->TextBox_load = (gcnew System::Windows::Forms::TextBox());
			this->File_out_label = (gcnew System::Windows::Forms::Label());
			this->File_in_label = (gcnew System::Windows::Forms::Label());
			this->TextBox_NumIncreace = (gcnew System::Windows::Forms::TextBox());
			this->TextBox_NumTo = (gcnew System::Windows::Forms::TextBox());
			this->TextBox_NumFrom = (gcnew System::Windows::Forms::TextBox());
			this->Button_calculate = (gcnew System::Windows::Forms::Button());
			this->Button_Save_In = (gcnew System::Windows::Forms::Button());
			this->Button_save_out = (gcnew System::Windows::Forms::Button());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->Gen_random_but = (gcnew System::Windows::Forms::Button());
			this->Gen_Random = (gcnew System::Windows::Forms::TextBox());
			this->SuspendLayout();
			// 
			// Button_add
			// 
			this->Button_add->Location = System::Drawing::Point(107, 365);
			this->Button_add->Name = L"Button_add";
			this->Button_add->Size = System::Drawing::Size(75, 23);
			this->Button_add->TabIndex = 32;
			this->Button_add->Text = L"add";
			this->Button_add->UseVisualStyleBackColor = true;
			this->Button_add->Click += gcnew System::EventHandler(this, &MyForm::Button_add_Click);
			// 
			// Button_clear
			// 
			this->Button_clear->Location = System::Drawing::Point(183, 365);
			this->Button_clear->Name = L"Button_clear";
			this->Button_clear->Size = System::Drawing::Size(75, 23);
			this->Button_clear->TabIndex = 31;
			this->Button_clear->Text = L"clear";
			this->Button_clear->UseVisualStyleBackColor = true;
			this->Button_clear->Click += gcnew System::EventHandler(this, &MyForm::Button_clear_Click);
			// 
			// TextBox_append
			// 
			this->TextBox_append->Location = System::Drawing::Point(11, 367);
			this->TextBox_append->Name = L"TextBox_append";
			this->TextBox_append->Size = System::Drawing::Size(93, 20);
			this->TextBox_append->TabIndex = 30;
			// 
			// Label_Error
			// 
			this->Label_Error->AutoSize = true;
			this->Label_Error->Location = System::Drawing::Point(8, 517);
			this->Label_Error->Name = L"Label_Error";
			this->Label_Error->Size = System::Drawing::Size(0, 13);
			this->Label_Error->TabIndex = 29;
			// 
			// From_To_label
			// 
			this->From_To_label->Anchor = System::Windows::Forms::AnchorStyles::Bottom;
			this->From_To_label->AutoSize = true;
			this->From_To_label->Location = System::Drawing::Point(273, 447);
			this->From_To_label->Name = L"From_To_label";
			this->From_To_label->Size = System::Drawing::Size(10, 13);
			this->From_To_label->TabIndex = 28;
			this->From_To_label->Text = L":";
			// 
			// TextBox_save
			// 
			this->TextBox_save->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->TextBox_save->Location = System::Drawing::Point(297, 7);
			this->TextBox_save->Name = L"TextBox_save";
			this->TextBox_save->Size = System::Drawing::Size(241, 20);
			this->TextBox_save->TabIndex = 27;
			// 
			// Button_load
			// 
			this->Button_load->Location = System::Drawing::Point(53, 30);
			this->Button_load->Name = L"Button_load";
			this->Button_load->Size = System::Drawing::Size(75, 23);
			this->Button_load->TabIndex = 26;
			this->Button_load->Text = L"load";
			this->Button_load->UseVisualStyleBackColor = true;
			this->Button_load->Click += gcnew System::EventHandler(this, &MyForm::Button_load_Click);
			// 
			// File_out_text
			// 
			this->File_out_text->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->File_out_text->BackColor = System::Drawing::SystemColors::ControlLight;
			this->File_out_text->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->File_out_text->Location = System::Drawing::Point(298, 73);
			this->File_out_text->Name = L"File_out_text";
			this->File_out_text->Size = System::Drawing::Size(241, 289);
			this->File_out_text->TabIndex = 25;
			this->File_out_text->Text = L"-";
			// 
			// File_in_text
			// 
			this->File_in_text->BackColor = System::Drawing::SystemColors::ControlLight;
			this->File_in_text->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->File_in_text->Location = System::Drawing::Point(12, 75);
			this->File_in_text->Name = L"File_in_text";
			this->File_in_text->Size = System::Drawing::Size(246, 289);
			this->File_in_text->TabIndex = 24;
			this->File_in_text->Text = L"-";
			// 
			// TextBox_load
			// 
			this->TextBox_load->Location = System::Drawing::Point(11, 7);
			this->TextBox_load->Name = L"TextBox_load";
			this->TextBox_load->Size = System::Drawing::Size(247, 20);
			this->TextBox_load->TabIndex = 23;
			// 
			// File_out_label
			// 
			this->File_out_label->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->File_out_label->BackColor = System::Drawing::SystemColors::ControlLight;
			this->File_out_label->Location = System::Drawing::Point(297, 56);
			this->File_out_label->Name = L"File_out_label";
			this->File_out_label->Size = System::Drawing::Size(241, 15);
			this->File_out_label->TabIndex = 22;
			this->File_out_label->Text = L"File out";
			// 
			// File_in_label
			// 
			this->File_in_label->BackColor = System::Drawing::SystemColors::ControlLight;
			this->File_in_label->Location = System::Drawing::Point(12, 56);
			this->File_in_label->Name = L"File_in_label";
			this->File_in_label->Size = System::Drawing::Size(246, 15);
			this->File_in_label->TabIndex = 21;
			this->File_in_label->Text = L"File in";
			// 
			// TextBox_NumIncreace
			// 
			this->TextBox_NumIncreace->Anchor = System::Windows::Forms::AnchorStyles::Bottom;
			this->TextBox_NumIncreace->Location = System::Drawing::Point(196, 470);
			this->TextBox_NumIncreace->Name = L"TextBox_NumIncreace";
			this->TextBox_NumIncreace->Size = System::Drawing::Size(159, 20);
			this->TextBox_NumIncreace->TabIndex = 20;
			// 
			// TextBox_NumTo
			// 
			this->TextBox_NumTo->Anchor = System::Windows::Forms::AnchorStyles::Bottom;
			this->TextBox_NumTo->Location = System::Drawing::Point(288, 444);
			this->TextBox_NumTo->Name = L"TextBox_NumTo";
			this->TextBox_NumTo->Size = System::Drawing::Size(159, 20);
			this->TextBox_NumTo->TabIndex = 19;
			// 
			// TextBox_NumFrom
			// 
			this->TextBox_NumFrom->Anchor = System::Windows::Forms::AnchorStyles::Bottom;
			this->TextBox_NumFrom->Location = System::Drawing::Point(108, 444);
			this->TextBox_NumFrom->Name = L"TextBox_NumFrom";
			this->TextBox_NumFrom->Size = System::Drawing::Size(159, 20);
			this->TextBox_NumFrom->TabIndex = 18;
			// 
			// Button_calculate
			// 
			this->Button_calculate->Anchor = System::Windows::Forms::AnchorStyles::Bottom;
			this->Button_calculate->Location = System::Drawing::Point(239, 496);
			this->Button_calculate->Name = L"Button_calculate";
			this->Button_calculate->Size = System::Drawing::Size(75, 23);
			this->Button_calculate->TabIndex = 17;
			this->Button_calculate->Text = L"perform";
			this->Button_calculate->UseVisualStyleBackColor = true;
			this->Button_calculate->Click += gcnew System::EventHandler(this, &MyForm::Button_calculate_Click);
			// 
			// Button_Save_In
			// 
			this->Button_Save_In->Location = System::Drawing::Point(134, 30);
			this->Button_Save_In->Name = L"Button_Save_In";
			this->Button_Save_In->Size = System::Drawing::Size(75, 23);
			this->Button_Save_In->TabIndex = 33;
			this->Button_Save_In->Text = L"save";
			this->Button_Save_In->UseVisualStyleBackColor = true;
			this->Button_Save_In->Click += gcnew System::EventHandler(this, &MyForm::Button_Save_In_Click);
			// 
			// Button_save_out
			// 
			this->Button_save_out->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->Button_save_out->Location = System::Drawing::Point(381, 30);
			this->Button_save_out->Name = L"Button_save_out";
			this->Button_save_out->Size = System::Drawing::Size(75, 23);
			this->Button_save_out->TabIndex = 35;
			this->Button_save_out->Text = L"save";
			this->Button_save_out->UseVisualStyleBackColor = true;
			this->Button_save_out->Click += gcnew System::EventHandler(this, &MyForm::Button_save_out_Click);
			// 
			// label1
			// 
			this->label1->Anchor = System::Windows::Forms::AnchorStyles::Bottom;
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(63, 447);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(42, 13);
			this->label1->TabIndex = 36;
			this->label1->Text = L"Range:";
			// 
			// label2
			// 
			this->label2->Anchor = System::Windows::Forms::AnchorStyles::Bottom;
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(116, 473);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(74, 13);
			this->label2->TabIndex = 37;
			this->label2->Text = L"Increase num:";
			// 
			// Gen_random_but
			// 
			this->Gen_random_but->Location = System::Drawing::Point(134, 394);
			this->Gen_random_but->Name = L"Gen_random_but";
			this->Gen_random_but->Size = System::Drawing::Size(124, 23);
			this->Gen_random_but->TabIndex = 39;
			this->Gen_random_but->Text = L"add random";
			this->Gen_random_but->UseVisualStyleBackColor = true;
			this->Gen_random_but->Click += gcnew System::EventHandler(this, &MyForm::Gen_random_but_Click);
			// 
			// Gen_Random
			// 
			this->Gen_Random->Location = System::Drawing::Point(11, 396);
			this->Gen_Random->Name = L"Gen_Random";
			this->Gen_Random->Size = System::Drawing::Size(117, 20);
			this->Gen_Random->TabIndex = 38;
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->AutoScroll = true;
			this->AutoSize = true;
			this->ClientSize = System::Drawing::Size(554, 536);
			this->Controls->Add(this->File_in_text);
			this->Controls->Add(this->Gen_random_but);
			this->Controls->Add(this->Gen_Random);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->Button_save_out);
			this->Controls->Add(this->Button_Save_In);
			this->Controls->Add(this->Button_add);
			this->Controls->Add(this->Button_clear);
			this->Controls->Add(this->TextBox_append);
			this->Controls->Add(this->Label_Error);
			this->Controls->Add(this->From_To_label);
			this->Controls->Add(this->TextBox_save);
			this->Controls->Add(this->Button_load);
			this->Controls->Add(this->File_out_text);
			this->Controls->Add(this->TextBox_load);
			this->Controls->Add(this->File_out_label);
			this->Controls->Add(this->File_in_label);
			this->Controls->Add(this->TextBox_NumIncreace);
			this->Controls->Add(this->TextBox_NumTo);
			this->Controls->Add(this->TextBox_NumFrom);
			this->Controls->Add(this->Button_calculate);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
			this->Name = L"MyForm";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"MyForm";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
private:

	void show_error(const char* er) {
		MessageBox::Show(gcnew String(("Error: " + string(er)).c_str()), "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
	}
	void show_info(const char* info) {
		MessageBox::Show(gcnew String(("Info: " + string(info)).c_str()), "Info", MessageBoxButtons::OK, MessageBoxIcon::Information);
	}

	void show_file(IntArr& f, System::Windows::Forms::Label^ label) {
		label->Text = gcnew String(f.to_str().c_str());
	}

	bool check_file_name(string f_name) {
		if (f_name.empty()) {
			show_error("Textbox should be filled");
			return false;
		}

		if (f_name.substr(max(f_name.size() - 4, 0)).compare(".bin")) {
			show_error("Unsuported extension");
			return false;
		}

		return true;
	}

	void save_file(IntArr& f, string name) {
		try {
			f.save_to_bin(name);
		}
		catch (exception& e) {
			show_error(e.what());
			return;
		}
		
		catch (...) {
			show_error("Unexpected error");
			return;
		}

		show_info("File saved successfully");
	}

	System::Void Button_load_Click(System::Object^ sender, System::EventArgs^ e) {

		string from_name = msclr::interop::marshal_as<std::string>(TextBox_load->Text->ToString());

		if (!check_file_name(from_name)) return;

		try {
			OperatedFile.load_from_bin(from_name);
		}
		catch (exception& e){
			show_error(e.what());
			return;
		}
		catch (...) {
			show_error("Unexpected error");
			return;
		}

		File_in_text->Text = gcnew String(OperatedFile.to_str().c_str());
	}


	System::Void Button_Save_In_Click(System::Object^ sender, System::EventArgs^ e) {
		string from_name = msclr::interop::marshal_as<std::string>(TextBox_load->Text->ToString());

		if (!check_file_name(from_name)) return;

		save_file(OperatedFile, from_name);
	}


	System::Void Button_save_out_Click(System::Object^ sender, System::EventArgs^ e) {
		string to_name = msclr::interop::marshal_as<std::string>(TextBox_save->Text->ToString());

		if (!check_file_name(to_name)) return;

		save_file(ResFile, to_name);
	}

	System::Void Button_calculate_Click(System::Object^ sender, System::EventArgs^ e) {

		unsigned int from_int, to_int, increase;

		string from_str = msclr::interop::marshal_as<std::string>(TextBox_NumFrom->Text);
		string to_str = msclr::interop::marshal_as<std::string>(TextBox_NumTo->Text);
		string increase_str = msclr::interop::marshal_as<std::string>(TextBox_NumIncreace->Text);

		if (OperatedFile.empty()) {
			show_error("Main arr is empty");
			return;
		}

		if (from_str.empty() || to_str.empty() || increase_str.empty()) {
			show_error("Fill in all the data");
			return;
		}

		try {
			from_int = get_unsigned_int(from_str);
			to_int = get_unsigned_int(to_str);
			increase = get_unsigned_int(increase_str);
		}
		catch (exception& e) {
			show_error(e.what());
			return;
		}
		catch (...) {
			show_error("Unexpected error");
			return;
		}

		try {
			ResFile = OperatedFile.get_performed(from_int, to_int, increase);
		}
		catch (exception& e) {
			show_error(e.what());
			return;
		}
		catch (...) {
			show_error("Unexpected error");
			return;
		}

		if (ResFile.empty()) {
			show_error("No int in given range found");
			return;
		}

		show_file(ResFile, File_out_text);
	}

	System::Void Button_add_Click(System::Object^ sender, System::EventArgs^ e) {

		string temp_s = msclr::interop::marshal_as<std::string>(TextBox_append->Text);

		try {
			OperatedFile.append(get_unsigned_int(temp_s));
		}
		catch (exception& e) {
			show_error(e.what());
			return;
		}
		catch (...) {
			show_error("Unexpected error");
			return;
		}

		show_file(OperatedFile, File_in_text);
	}

	System::Void Button_clear_Click(System::Object^ sender, System::EventArgs^ e) {
		OperatedFile.clear();
		show_file(OperatedFile, File_in_text);
	}

	System::Void Gen_random_but_Click(System::Object^ sender, System::EventArgs^ e) {
		unsigned int amount;

		try {
			amount = get_unsigned_int(msclr::interop::marshal_as<std::string>(Gen_Random->Text));
		}
		catch (exception& e) {
			show_error(e.what());
			return;
		}
		catch (...) {
			show_error("Unexpected error");
			return;
		}

		for (unsigned int i = 0; i < amount; i++) OperatedFile.append(rand() % 10000);

		show_file(OperatedFile, File_in_text);

		show_info(("Added " + to_string(amount) + " random elements").c_str());
	}
};
}
