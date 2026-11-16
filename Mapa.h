#pragma once
using namespace System;
using namespace System::Drawing;

ref class Mapa
{
private:
	array<int, 2>^ casillas;
	int filas;
	int columnas;
	int tamano;
public:
	Mapa();
	~Mapa();

	void dibujar_mapa(Graphics^ graphics);
	bool es_transitable(int fila, int columna);
};

Mapa::Mapa()
{
	filas = 16;
	columnas = 32;
	tamano = 32;
}

Mapa::~Mapa()
{
	//destructor vacio
}

void Mapa::dibujar_mapa(Graphics^ graphics)
{
	SolidBrush^ pasto = gcnew SolidBrush(Color::DarkOliveGreen);
	SolidBrush^ rio = gcnew SolidBrush(Color::SteelBlue);
	Pen^ lapiz = gcnew Pen(Color::FromArgb(60, 0, 0, 0));

	for (int f = 0; f < filas; f++)
	{
		for (int c = 0; c < columnas; c++)
		{
			if (casillas[f, c] == 1)
			{
				graphics->FillRectangle(rio, c * tamano, f * tamano, tamano, tamano);
			}

			else
			{
				graphics->FillRectangle(pasto, c * tamano, f * tamano, tamano, tamano);
			}

			graphics->DrawRectangle(lapiz, c * tamano, f * tamano, tamano, tamano);
		}

		delete pasto;
		delete rio;
		delete lapiz;
	}
}