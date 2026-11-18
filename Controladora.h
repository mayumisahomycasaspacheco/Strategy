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

bool Controladora::puede_ir_a(Unidad^ unidad, int fila, int columna)
{
	int distancia = Math::Abs(unidad->obtener_fila() - fila) + Math::Abs(unidad->obtener_columna() - columna);

	if (distancia > unidad->obtener_movimiento())
	{
		return false;
	}

	if (!mapa->es_transitable(fila, columna))
	{
		return false;
	}

	if (buscar_unidad(fila, columna) != nullptr)
	{
		return false;
	}

	return true;
}

void Controladora::dibujar_alcance(Graphics^ graphics)
{
	if (seleccionada == nullptr)
	{
		return;
	}

	int tamano = mapa->obtener_tamano();
	int movimiento = seleccionada->obtener_movimiento();
	int fila = seleccionada->obtener_fila();
	int columna = seleccionada->obtener_columna();

	SolidBrush^ azul = gcnew SolidBrush(Color::FromArgb(120, 0, 120, 255));
	SolidBrush^ amarillo = gcnew SolidBrush(Color::FromArgb(120, 255, 220, 0));

	graphics->FillRectangle(amarillo, columna * tamano, fila * tamano, tamano, tamano);

	for (int f = fila - movimiento; f <= fila + movimiento; f++)
	{
		for (int c = columna - movimiento; c <= columna + movimiento; c++)
		{
			if (puede_ir_a(seleccionada, f, c))
			{
				graphics->FillRectangle(azul, c * tamano, f * tamano, tamano, tamano);
			}
		}
	}

	delete azul;
	delete amarillo;
}

void Controladora::dibujar(Graphics^ graphics)
{
	mapa->dibujar(graphics);
	dibujar_alcance(graphics);

	for (int i = 0; i < unidades->Count; i++)
	{
		unidades[i]->dibujar(graphics);
	}
}

void Controladora::clic(int x, int y)
{
	int tamano = mapa->obtener_tamano();
	int columna = x / tamano;
	int fila = y / tamano;

	Unidad^ unidad = buscar_unidad(fila, columna);

	if (unidad != nullptr && unidad->obtener_bando() == Bando::Aleman)
	{
		seleccionada = unidad;
	}

	else
	{
		seleccionada = nullptr;
	}
}