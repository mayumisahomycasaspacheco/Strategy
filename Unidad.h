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
public:
	Unidad(int fila, int columa, Bando bando, int tamano, Bitmap^ sprite);
	~Unidad();
};

Unidad::Unidad(int fila, int columna, Bando bando, int tamano, Bitmap^ sprite)
{

}

Unidad::~Unidad()
{
	//Destructor vacio
}