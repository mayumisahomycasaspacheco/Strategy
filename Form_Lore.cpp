#include "Form_Lore.h"

using namespace System;
using namespace System::Windows::Forms;

[STAThreadAttribute]
int main(array<String^>^ args)
{
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	
	do
	{
		Sesion::jugar_de_nuevo = false;
		Application::Run(gcnew Strategy::Form_Lore());
	}

	while (Sesion::jugar_de_nuevo);
}
