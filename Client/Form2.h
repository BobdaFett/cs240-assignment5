#pragma once

namespace cs240assignment2 {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for Form2
	/// </summary>
	public ref class Form2 : public System::Windows::Forms::Form
	{
	public:
		Form2(void)
		{
			InitializeComponent();
		}

		System::Windows::Forms::Label^ getLabel() {
			return textLabel;
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~Form2()
		{
			if (components)
			{
				delete components;
			}
		}

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container^ components;
		System::Windows::Forms::Label^ textLabel;
		System::Windows::Forms::Button^ buttonOK;

		System::Void buttonOK_Click(System::Object^ sender, System::EventArgs^ e) {
			this->Close();
		}

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->buttonOK = (gcnew System::Windows::Forms::Button());
			this->textLabel = (gcnew System::Windows::Forms::Label());
			this->SuspendLayout();
			// 
			// buttonOK
			// 
			this->buttonOK->Location = System::Drawing::Point(207, 149);
			this->buttonOK->Name = L"buttonOK";
			this->buttonOK->Size = System::Drawing::Size(100, 50);
			this->buttonOK->TabIndex = 0;
			this->buttonOK->Text = L"OK";
			this->buttonOK->UseVisualStyleBackColor = true;
			this->buttonOK->Click += gcnew System::EventHandler(this, &Form2::buttonOK_Click);
			// 
			// textLabel
			// 
			this->textLabel->Location = System::Drawing::Point(12, 41);
			this->textLabel->Name = L"textLabel";
			this->textLabel->Size = System::Drawing::Size(500, 61);
			this->textLabel->TabIndex = 1;
			this->textLabel->Text = L"label";
			this->textLabel->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// errorWindow
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(12, 25);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(524, 229);
			this->Controls->Add(this->textLabel);
			this->Controls->Add(this->buttonOK);
			this->Name = L"errorWindow";
			this->Text = L"errorWindow";
			this->ResumeLayout(false);
		}
#pragma endregion
	};
}
