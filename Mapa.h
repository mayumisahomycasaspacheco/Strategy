#pragma once
using namespace System;
using namespace System::Drawing;

ref class Mapa
{
private:
	array<int, 2>^ casillas;
	int filas, columnas;
	int tamano;

	int fila_clic, columna_clic;
public:
	Mapa();
	~Mapa();

	void dibujar(Graphics^ graphics);
	bool es_transitable(int fila, int columna);
	void clic(int x, int y);
};

Mapa::Mapa()
{
	filas = 16;
	columnas = 32;
	tamano = 32;
	fila_clic = -1;
	columna_clic = -1;
	
	casillas = gcnew array<int, 2>(filas, columnas);

	for (int f = 6; f <= 8; f++)
	{
		for (int c = 0; c < columnas; c++)
		{
			casillas[f, c] = 1;
		}
	}

	for (int f = 6; f <= 8; f++)
	{
		casillas[f, 7] = 0;
		casillas[f, 8] = 0;
		casillas[f, 23] = 0;
		casillas[f, 24] = 0;
	}
}

Mapa::~Mapa()
{
	//Destructor vacio
}

void Mapa::dibujar(Graphics^ graphics)
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
	}

	delete pasto;
	delete rio;
	delete lapiz;
}

bool Mapa::es_transitable(int fila, int columna)
{
	if (fila < 0 || fila >= filas || columna < 0 || columna >= columnas)
	{
		return false;
	}
	return casillas[fila, columna] == 0;
}

void Mapa::clic(int x, int y)
{
	columna_clic = x / tamano;
	fila_clic = y / tamano;

	if (fila_clic >= filas)
	{
		fila_clic = -1;
		columna_clic = -1;
	}
}