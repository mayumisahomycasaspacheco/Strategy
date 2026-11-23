#pragma once
using namespace System;
using namespace System::Drawing;

enum class Bando { Aleman, Sovietico};

ref class Unidad
{
private:
	int fila, columna;
	int x, y;
	int vida;
	int vida_maxima;
	Bando bando;
	int tamano;
	Bitmap^ sprite;
	int direccion;
	int cuadro;
	int escala;
	int velocidad;
	int contador;
	int movimiento;
	int desplazamiento_y;
	bool ya_actuo;
public:
	Unidad(int fila, int columa, Bando bando, int tamano, Bitmap^ sprite);
	~Unidad();

	void dibujar(Graphics^ graphics);
	int obtener_fila();
	int obtener_columna();
	Bando obtener_bando();
	int obtener_movimiento();
	void mover_a(int nueva_fila, int nueva_columna);
	void animar();
	bool en_movimiento();
	void recibir_danio(int danio);
	bool esta_viva();
	bool obtener_ya_actuo();
	void marcar_actuo();
	void nuevo_turno();
	void establecer_vida(int nueva_vida);
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
	vida_maxima = 10;
	direccion = 0;
	cuadro = 1;
	escala = 2;
	velocidad = 4;
	contador = 0;
	movimiento = 3;
	desplazamiento_y = -12;
	ya_actuo = false;
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

	if (ya_actuo)
	{
		color_bando = Color::FromArgb(160, 120, 120, 120);
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

	if (vida < vida_maxima)
	{
		int ancho_barra = (tamano - 6) * vida / vida_maxima;
		SolidBrush^ fondo = gcnew SolidBrush(Color::Black);
		SolidBrush^ barra = gcnew SolidBrush(Color::LimeGreen);
		graphics->FillRectangle(fondo, x + 3, y + tamano - 5, tamano - 6, 4);
		graphics->FillRectangle(barra, x + 3, y + tamano - 5, ancho_barra, 4);
		delete fondo;
		delete barra;
	}
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

void Unidad::mover_a(int nueva_fila, int nueva_columna)
{
	int dif_fila = nueva_fila - fila;
	int dif_columna = nueva_columna - columna;

	if (Math::Abs(dif_columna) >= Math::Abs(dif_fila))
	{
		if (dif_columna > 0)
		{
			direccion = 3;
		}

		else
		{
			direccion = 2;
		}
	}

	else
	{
		if (dif_fila > 0)
		{
			direccion = 0;
		}

		else
		{
			direccion = 1;
		}
	}

	fila = nueva_fila;
	columna = nueva_columna;
}

bool Unidad::en_movimiento()
{
	return x != columna * tamano || y != fila * tamano;
}

void Unidad::animar()
{
	int destino_x = columna * tamano;
	int destino_y = fila * tamano;

	if (x < destino_x)
	{
		x = x + velocidad;
		
		if (x > destino_x)
		{
			x = destino_x;
		}
	}

	else if (x > destino_x)
	{
		x = x - velocidad;
		
		if (x < destino_x)
		{
			x = destino_x;
		}
	}

	if (y < destino_y)
	{
		y = y + velocidad;

		if (y > destino_y)
		{
			y = destino_y;
		}
	}

	else if (y > destino_y)
	{
		y = y - velocidad;

		if (y < destino_y)
		{
			y = destino_y;
		}
	}

	if (en_movimiento())
	{
		contador = contador + 1;
		int fase = (contador / 5) % 4;

		if (fase == 3)
		{
			cuadro = 1;
		}

		else
		{
			cuadro = fase;
		}
	}

	else
	{
		contador = 0;
		cuadro = 1;
	}
}

void Unidad::recibir_danio(int danio)
{
	vida = vida - danio;

	if (vida < 0)
	{
		vida = 0;
	}
}

bool Unidad::esta_viva()
{
	return vida > 0;
}

bool Unidad::obtener_ya_actuo()
{
	return ya_actuo;
}

void Unidad::marcar_actuo()
{
	ya_actuo = true;
}

void Unidad::nuevo_turno()
{
	ya_actuo = false;
}

void Unidad::establecer_vida(int nueva_vida)
{
	vida = nueva_vida;
	vida_maxima = nueva_vida;
}