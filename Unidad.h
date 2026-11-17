#pragma once
using namespace System;
using namespace System::Drawing;

enum class Bando { Aleman };

ref class Unidad
{
private:
	int fila, columna;
	int x, y;
	int vida;
	Bando bando;
	int tamano;
	Bitmap^ sprite;
	int direccion;
	int cuadro;
	int escala;
	int movimiento;
	int desplazamiento_y;
public:
	Unidad(int fila, int columa, Bando bando, int tamano, Bitmap^ sprite);
	~Unidad();

	void dibujar(Graphics^ graphics);
	int obtener_fila();
	int obtener_columna();
	Bando obtener_bando();
	int obtener_movimiento();
};

Unidad::Unidad(int fila, int columna, Bando bando, int tamano, Bitmap^ sprite)
{
	this->fila = fila;
	this->columna = columna;
	this->bando = bando;
	this->tamano = tamano;
	this->sprite = sprite;
	x = columna * tamano;
	y = fila * tamano;
	vida = 10;
	direccion = 0;
	cuadro = 1;
	escala = 2;
	movimiento = 3;
	desplazamiento_y = -12;
}

Unidad::~Unidad()
{
	//Destructor vacio
}

void Unidad::dibujar(Graphics^ graphics)
{
	Color color_bando;

	if (bando == Bando::Aleman)
	{
		color_bando = Color::FromArgb(160, 65, 105, 225);
	}

	else
	{
		color_bando = Color::FromArgb(160, 178, 34, 34);
	}

	SolidBrush^ aro = gcnew SolidBrush(color_bando);
	graphics->FillEllipse(aro, x + 3, y + tamano - 12 + desplazamiento_y, tamano - 6, 10);
	delete aro;

	int ancho = sprite->Width / 3;
	int alto = sprite->Height / 4;

	Rectangle origen = Rectangle(cuadro * ancho, direccion * alto, ancho, alto);
	Rectangle destino = Rectangle(x, y + tamano - alto * escala + desplazamiento_y, ancho * escala, alto * escala);

	graphics->InterpolationMode = System::Drawing::Drawing2D::InterpolationMode::NearestNeighbor;
	graphics->PixelOffsetMode = System::Drawing::Drawing2D::PixelOffsetMode::Half;
	graphics->DrawImage(sprite, destino, origen, GraphicsUnit::Pixel);
}

int Unidad::obtener_fila()
{
	return fila;
}

int Unidad::obtener_columna()
{
	return columna;
}

Bando Unidad::obtener_bando()
{
	return bando;
}

int Unidad::obtener_movimiento()
{
	return movimiento;
}