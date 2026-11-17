#pragma once
#include "Mapa.h"

namespace Strategy {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Resumen de Form_Game
	/// </summary>
	public ref class Form_Game : public System::Windows::Forms::Form
	{
	public:
		Form_Game(void)
		{
			InitializeComponent();
			//
			//TODO: agregar código de constructor aquí
			//

			mapa = gcnew Mapa();
		}

	protected:
		/// <summary>
		/// Limpiar los recursos que se estén usando.
		/// </summary>
		~Form_Game()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Timer^ timer1;
		   Mapa^ mapa;
	protected:
	private: System::ComponentModel::IContainer^ components;

	private:
		/// <summary>
		/// Variable del diseñador necesaria.
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Método necesario para admitir el Diseñador. No se puede modificar
		/// el contenido de este método con el editor de código.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			this->timer1 = (gcnew System::Windows::Forms::Timer(this->components));
			this->SuspendLayout();
			// 
			// timer1
			// 
			this->timer1->Enabled = true;
			this->timer1->Interval = 30;
			// 
			// Form_Game
			// 
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::None;
			this->ClientSize = System::Drawing::Size(1024, 640);
			this->DoubleBuffered = true;
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
			this->KeyPreview = true;
			this->MaximizeBox = false;
			this->Name = L"Form_Game";
			this->RightToLeftLayout = true;
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"Eagle\'s Twilight";
			this->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &Form_Game::Form_Game_Paint);
			this->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form_Game::Form_Game_MouseClick);
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void Form_Game_Paint(System::Object^ sender, System::Windows::Forms::PaintEventArgs^ e) 
	{
		mapa->dibujar(e->Graphics);
	}
	private: System::Void Form_Game_MouseClick(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e) 
	{
		mapa->clic(e->X, e->Y);
		this->Invalidate();
	}
	};
}
