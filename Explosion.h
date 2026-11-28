#pragma once
using namespace System;
using namespace System::Drawing;

ref class Explosion
{
private:
	int x, y;
	int cuadro;
	int contador;
	int duracion;
public:
	Explosion(int x, int y);

	void animar();
	bool terminada();
	void dibujar(Graphics^ graphics, Bitmap^ sprite);
};

Explosion::Explosion(int x, int y)
{
	this->x = x;
	this->y = y;
	contador = 0;
	duracion = 4;
}

void Explosion::animar()
{
	contador = contador + 1;

	if (contador >= duracion)
	{
		contador = 0;
		cuadro = cuadro + 1;
	}
}

bool Explosion::terminada()
{
	return cuadro >= 4;
}

void Explosion::dibujar(Graphics^ graphics, Bitmap^ sprite)
{
	if (terminada())
	{
		return;
	}

	int ancho = sprite->Width / 4;
	int alto = sprite->Height;

	graphics->InterpolationMode = System::Drawing::Drawing2D::InterpolationMode::NearestNeighbor;
	graphics->PixelOffsetMode = System::Drawing::Drawing2D::PixelOffsetMode::Half;

	Rectangle origen = Rectangle(cuadro * ancho, 0, ancho, alto);
	Rectangle destino = Rectangle(x - ancho, y - 52, ancho * 2, alto * 2);
	graphics->DrawImage(sprite, destino, origen, GraphicsUnit::Pixel);
}