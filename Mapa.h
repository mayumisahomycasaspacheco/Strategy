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
	Bitmap^ imagen;
public:
	Mapa();
	~Mapa();

	void dibujar(Graphics^ graphics);
	bool es_transitable(int fila, int columna);
	void clic(int x, int y);
	int obtener_tamano();
	int obtener_filas();
	int obtener_columnas();
};

Mapa::Mapa()
{
	imagen = gcnew Bitmap("sprites/Sprite-0001.png");

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
		casillas[f, 23] = 0;
	}
}

Mapa::~Mapa()
{
	delete imagen;
}

void Mapa::dibujar(Graphics^ graphics)
{
	graphics->InterpolationMode = System::Drawing::Drawing2D::InterpolationMode::NearestNeighbor;
	graphics->PixelOffsetMode = System::Drawing::Drawing2D::PixelOffsetMode::Half;
	graphics->DrawImage(imagen, 0, 0, columnas * tamano, filas * tamano);

	SolidBrush^ rojo = gcnew SolidBrush(Color::FromArgb(90, 255, 0, 0));
	
	for (int f = 0; f < filas; f++)
	{
		for (int c = 0; c < columnas; c++)
		{
			if (casillas[f, c] == 1)
			{
				graphics->FillRectangle(rojo, c * tamano, f * tamano, tamano, tamano);
			}
		}
	}

	delete rojo;

	if (fila_clic != -1)
	{
		Color color_luz;

		if (es_transitable(fila_clic, columna_clic))
		{
			color_luz = Color::FromArgb(120, 0, 120, 255);
		}

		else
		{
			color_luz = Color::FromArgb(120, 255, 0, 0);
		}

		SolidBrush^ luz = gcnew SolidBrush(color_luz);
		graphics->FillRectangle(luz, columna_clic * tamano, fila_clic * tamano, tamano, tamano);
		delete luz;
	}
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

int Mapa::obtener_tamano()
{
	return tamano;
}

int Mapa::obtener_filas()
{
	return filas;
}

int Mapa::obtener_columnas()
{
	return columnas;
}