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

	int tamano = mapa->obtener_tamano();
	unidades->Add(gcnew Unidad(12, 5, Bando::Aleman, tamano, sprite_soldado));
}

Controladora::~Controladora()
{
	delete sprite_soldado;
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