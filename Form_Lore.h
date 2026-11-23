#pragma once
#include "Form_Lore2.h"

namespace Strategy {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Resumen de Form_Lore
	/// </summary>
	public ref class Form_Lore : public System::Windows::Forms::Form
	{
	public:
		Form_Lore(void)
		{
			InitializeComponent();
			
			using namespace System::Drawing;

			label1->Font = gcnew System::Drawing::Font("Consolas", 60, FontStyle::Regular, GraphicsUnit::Pixel);
			label2->Font = gcnew System::Drawing::Font("Consolas", 37, FontStyle::Regular, GraphicsUnit::Pixel);
			label3->Font = gcnew System::Drawing::Font("Consolas", 30, FontStyle::Regular, GraphicsUnit::Pixel);
			label4->Font = gcnew System::Drawing::Font("Consolas", 27, FontStyle::Regular, GraphicsUnit::Pixel);
		}

	protected:
		/// <summary>
		/// Limpiar los recursos que se estén usando.
		/// </summary>
		~Form_Lore()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::Label^ label3;
	private: System::Windows::Forms::Label^ label4;
	private: System::Windows::Forms::Label^ label_flecha;

	protected:

	private:
		/// <summary>
		/// Variable del diseñador necesaria.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Método necesario para admitir el Diseñador. No se puede modificar
		/// el contenido de este método con el editor de código.
		/// </summary>
		void InitializeComponent(void)
		{
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(Form_Lore::typeid));
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->label_flecha = (gcnew System::Windows::Forms::Label());
			this->SuspendLayout();
			// 
			// label1
			// 
			this->label1->BackColor = System::Drawing::Color::Transparent;
			this->label1->Font = (gcnew System::Drawing::Font(L"Consolas", 36, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label1->ForeColor = System::Drawing::Color::Gold;
			this->label1->Location = System::Drawing::Point(151, 146);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(723, 70);
			this->label1->TabIndex = 0;
			this->label1->Text = L"CREPÚSCULO DEL ÁGUILA";
			// 
			// label2
			// 
			this->label2->BackColor = System::Drawing::Color::Transparent;
			this->label2->Font = (gcnew System::Drawing::Font(L"Consolas", 22.2F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label2->ForeColor = System::Drawing::SystemColors::ControlLightLight;
			this->label2->Location = System::Drawing::Point(328, 229);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(359, 43);
			this->label2->TabIndex = 1;
			this->label2->Text = L"Batalla de Berlín";
			// 
			// label3
			// 
			this->label3->BackColor = System::Drawing::Color::Transparent;
			this->label3->Font = (gcnew System::Drawing::Font(L"Consolas", 18, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label3->ForeColor = System::Drawing::SystemColors::ControlLightLight;
			this->label3->Location = System::Drawing::Point(40, 459);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(351, 36);
			this->label3->TabIndex = 2;
			this->label3->Text = L"BERLÍN, ABRIL DE 1945";
			// 
			// label4
			// 
			this->label4->BackColor = System::Drawing::Color::Transparent;
			this->label4->Font = (gcnew System::Drawing::Font(L"Consolas", 16.2F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label4->ForeColor = System::Drawing::SystemColors::ControlLightLight;
			this->label4->Location = System::Drawing::Point(40, 524);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(870, 66);
			this->label4->TabIndex = 3;
			this->label4->Text = L"El ejercito rojo está en las puertas de la ciudad. Lo que\r\nqueda del ejército ale"
				L"mán resiste entre las ruinas.";
			// 
			// label_flecha
			// 
			this->label_flecha->BackColor = System::Drawing::Color::Transparent;
			this->label_flecha->Cursor = System::Windows::Forms::Cursors::Hand;
			this->label_flecha->Location = System::Drawing::Point(980, 593);
			this->label_flecha->Name = L"label_flecha";
			this->label_flecha->Size = System::Drawing::Size(32, 23);
			this->label_flecha->TabIndex = 4;
			this->label_flecha->Click += gcnew System::EventHandler(this, &Form_Lore::label_flecha_Click);
			// 
			// Form_Lore
			// 
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::None;
			this->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"$this.BackgroundImage")));
			this->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->ClientSize = System::Drawing::Size(1024, 640);
			this->Controls->Add(this->label_flecha);
			this->Controls->Add(this->label4);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->label1);
			this->DoubleBuffered = true;
			this->MaximizeBox = false;
			this->Name = L"Form_Lore";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"Form_Lore";
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void label_flecha_Click(System::Object^ sender, System::EventArgs^ e) 
	{
		this->Hide();
		Form_Lore2^ lore2 = gcnew Form_Lore2();
		lore2->ShowDialog();
		this->Close();
	}
};
}
