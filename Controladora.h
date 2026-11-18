#pragma once
#include "Mapa.h"
#include "Unidad.h"

using namespace System;
using namespace System::Drawing;
using namespace System::Collections::Generic;

ref class Controladora
{
private:
	Mapa^ mapa;
	List<Unidad^>^ unidades;
	Bitmap^ sprite_soldado;
	Bitmap^ sprite_soldado1;
	Unidad^ seleccionada;

	Unidad^ buscar_unidad(int fila, int columna);
	bool puede_ir_a(Unidad^ unidad, int fila, int columna);
	void dibujar_alcance(Graphics^ graphics);
public:
	Controladora();
	~Controladora();

	void dibujar(Graphics^ graphics);
	void clic(int x, int y);
};

Controladora::Controladora()
{
	mapa = gcnew Mapa();
	unidades = gcnew List<Unidad^>();
	sprite_soldado = gcnew Bitmap("sprites/Sprite-0002.png");
	sprite_soldado1 = gcnew Bitmap("sprites/Sprite-0003.png");
	seleccionada = nullptr;

	int tamano = mapa->obtener_tamano();
	unidades->Add(gcnew Unidad(12, 5, Bando::Aleman, tamano, sprite_soldado));
	unidades->Add(gcnew Unidad(2, 20, Bando::Sovietico, tamano, sprite_soldado1));
}

Controladora::~Controladora()
{
	delete sprite_soldado;
}

Unidad^ Controladora::buscar_unidad(int fila, int columna)
{
	for (int i = 0; i < unidades->Count; i++)
	{
		if (unidades[i]->obtener_fila() == fila && unidades[i]->obtener_columna() == columna)
		{
			return unidades[i];
		}
	}

	return nullptr;
}

void Controladora::dibujar(Graphics^ graphics)
{
	mapa->dibujar(graphics);

	for (int i = 0; i < unidades->Count; i++)
	{
		unidades[i]->dibujar(graphics);
	}
}

void Controladora::clic(int x, int y)
{
	mapa->clic(x, y);
}