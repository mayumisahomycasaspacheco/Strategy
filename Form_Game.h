#pragma once
#include "Controladora.h"

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

			juego = gcnew Controladora();
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
		   Controladora^ juego;
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
			this->timer1->Tick += gcnew System::EventHandler(this, &Form_Game::timer1_Tick);
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
			this->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &Form_Game::Form_Game_KeyDown);
			this->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form_Game::Form_Game_MouseClick);
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void Form_Game_Paint(System::Object^ sender, System::Windows::Forms::PaintEventArgs^ e) 
	{
		juego->dibujar(e->Graphics);
	}
	private: System::Void Form_Game_MouseClick(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e) 
	{
		if (juego->hay_derrota())
		{
			Sesion::jugar_de_nuevo = true;
			this->Close();
			return;
		}

		juego->clic(e->X, e->Y);
		this->Invalidate();
	}
	private: System::Void timer1_Tick(System::Object^ sender, System::EventArgs^ e) 
	{
		juego->mover();
		this->Invalidate();
	}
	private: System::Void Form_Game_KeyDown(System::Object^ sender, System::Windows::Forms::KeyEventArgs^ e) 
	{
		if (e->KeyCode == Keys::Space)
		{
			juego->terminar_turno();
			this->Invalidate();
		}

		if (e->KeyCode == Keys::K)
		{
			juego->trampa_matar();
			this->Invalidate();
		}

		if (e->KeyCode == Keys::B)
		{
			juego->trampa_bombardeo();
			this->Invalidate();
		}
	}
	};
}
