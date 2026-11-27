#pragma once
using namespace System;
using namespace System::Drawing;

ref class Bomba
{
private:
	int x, y;
	int destino_y;
	int velocidad;
public:
	Bomba(int x, int destino_y, int retraso);
	void caer();
	bool llego();
	void dibujar(Graphics^ graphics, Bitmap^ sprite);
};

Bomba::Bomba(int x, int destino_y, int retraso)
{
	this->x = x;
	this->destino_y = destino_y;
	y = -retraso;
	velocidad = 5;
}

void Bomba::caer()
{
	y = y + velocidad;

	if (y > destino_y)
	{
		y = destino_y;
	}
}

bool Bomba::llego()
{
	return y >= destino_y;
}

void Bomba::dibujar(Graphics^ graphics, Bitmap^ sprite)
{
	graphics->InterpolationMode = System::Drawing::Drawing2D::InterpolationMode::NearestNeighbor;
	graphics->PixelOffsetMode = System::Drawing::Drawing2D::PixelOffsetMode::Half;

	Rectangle destino = Rectangle(x, y - 32, 16, 32);
	Rectangle origen = Rectangle(0, 0, sprite->Width, sprite->Height);
	graphics->DrawImage(sprite, destino, origen, GraphicsUnit::Pixel);
}