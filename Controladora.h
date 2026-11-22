#pragma once
#include "Mapa.h"
#include "Unidad.h"

using namespace System;
using namespace System::Drawing;
using namespace System::Collections::Generic;

enum class Turno { Aleman, Sovietico };

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
	bool hay_alguien_moviendose();

	int bajas_sovieticas;
	int distancia(Unidad^ a, Unidad^ b);
	void atacar(Unidad^ atacante, Unidad^ objetivo);

	int numero_turno;
	void dibujar_panel(Graphics^ graphics);

	Turno turno;
	List<Unidad^>^ cola_enemiga;
	int indice_enemigo;
	int espera;

	Unidad^ buscar_aleman_mas_cercano(Unidad^ desde);
	void actuar_enemigo(Unidad^ enemigo);
	void turno_enemigo();

	bool todos_los_alemanes_actuaron();
public:
	Controladora();
	~Controladora();

	void dibujar(Graphics^ graphics);
	void clic(int x, int y);
	void mover();

	void terminar_turno();
};

Controladora::Controladora()
{
	mapa = gcnew Mapa();
	unidades = gcnew List<Unidad^>();
	sprite_soldado = gcnew Bitmap("sprites/Sprite-0002.png");
	sprite_soldado1 = gcnew Bitmap("sprites/Sprite-0003.png");
	seleccionada = nullptr;
	bajas_sovieticas = 0;

	numero_turno = 1;

	int tamano = mapa->obtener_tamano();
	unidades->Add(gcnew Unidad(12, 5, Bando::Aleman, tamano, sprite_soldado));
	unidades->Add(gcnew Unidad(12, 7, Bando::Aleman, tamano, sprite_soldado));
	unidades->Add(gcnew Unidad(11, 9, Bando::Sovietico, tamano, sprite_soldado1));

	unidades->Add(gcnew Unidad(10, 14, Bando::Sovietico, tamano, sprite_soldado1));
	unidades->Add(gcnew Unidad(9, 16, Bando::Sovietico, tamano, sprite_soldado1));
	unidades->Add(gcnew Unidad(11, 18, Bando::Sovietico, tamano, sprite_soldado1));
	
	turno = Turno::Aleman;
	cola_enemiga = gcnew List<Unidad^>();
	indice_enemigo = 0;
	espera = 0;
}

Controladora::~Controladora()
{
	delete sprite_soldado;
	delete sprite_soldado1;
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
	int pasos = Math::Abs(unidad->obtener_fila() - fila) + Math::Abs(unidad->obtener_columna() - columna);

	if (pasos > unidad->obtener_movimiento())
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

	SolidBrush^ rojo = gcnew SolidBrush(Color::FromArgb(140, 255, 0, 0));

	for (int i = 0; i < unidades->Count; i++)
	{
		Unidad^ otra = unidades[i];

		if (otra->obtener_bando() != seleccionada->obtener_bando() && distancia(seleccionada, otra) == 1)
		{
			graphics->FillRectangle(rojo, otra->obtener_columna() * tamano, otra->obtener_fila() * tamano, tamano, tamano);
		}
	}

	delete rojo;
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

	dibujar_panel(graphics);
}

void Controladora::clic(int x, int y)
{
	if (turno != Turno::Aleman)
	{
		return;
	}

	if (hay_alguien_moviendose())
	{
		return;
	}

	int tamano = mapa->obtener_tamano();
	int columna = x / tamano;
	int fila = y / tamano;

	Unidad^ unidad = buscar_unidad(fila, columna);

	if (unidad != nullptr && unidad->obtener_bando() == Bando::Aleman && !unidad->obtener_ya_actuo())
	{
		seleccionada = unidad;
	}

	else if (unidad != nullptr && unidad->obtener_bando() == Bando::Sovietico && seleccionada != nullptr && distancia(seleccionada, unidad) == 1)
	{
		atacar(seleccionada, unidad);
		seleccionada->marcar_actuo();
		seleccionada = nullptr;
	}

	else if (seleccionada != nullptr && puede_ir_a(seleccionada, fila, columna))
	{
		seleccionada->mover_a(fila, columna);
		seleccionada->marcar_actuo();
		seleccionada = nullptr;
	}

	else
	{
		seleccionada = nullptr;
	}

	if (todos_los_alemanes_actuaron())
	{
		terminar_turno();
	}
}

bool Controladora::hay_alguien_moviendose()
{
	for (int i = 0; i < unidades->Count; i++)
	{
		if (unidades[i]->en_movimiento())
		{
			return true;
		}
	}

	return false;
}

void Controladora::mover()
{
	for (int i = 0; i < unidades->Count; i++)
	{
		unidades[i]->animar();
	}

	if (turno == Turno::Sovietico && !hay_alguien_moviendose())
	{
		espera = espera + 1;

		if (espera >= 15)
		{
			espera = 0;
			turno_enemigo();
		}
	}
}

int Controladora::distancia(Unidad^ a, Unidad^ b)
{
	return Math::Abs(a->obtener_fila() - b->obtener_fila()) + Math::Abs(a->obtener_columna() - b->obtener_columna());
}

void Controladora::atacar(Unidad^ atacante, Unidad^ objetivo)
{
	objetivo->recibir_danio(3);

	if (!objetivo->esta_viva())
	{
		unidades->Remove(objetivo);

		if (objetivo->obtener_bando() == Bando::Sovietico)
		{
			bajas_sovieticas = bajas_sovieticas + 1;
		}
	}
}

void Controladora::terminar_turno()
{
	if (turno != Turno::Aleman)
	{
		return;
	}

	seleccionada = nullptr;
	turno = Turno::Sovietico;

	cola_enemiga->Clear();

	for (int i = 0; i < unidades->Count; i++)
	{
		if (unidades[i]->obtener_bando() == Bando::Sovietico)
		{
			cola_enemiga->Add(unidades[i]);
		}
	}

	indice_enemigo = 0;
	espera = 0;
}

void Controladora::dibujar_panel(Graphics^ graphics)
{
	int alemanes = 0;
	int sovieticos = 0;

	for (int i = 0; i < unidades->Count; i++)
	{
		if (unidades[i]->obtener_bando() == Bando::Aleman)
		{
			alemanes = alemanes + 1;
		}

		else
		{
			sovieticos = sovieticos + 1;
		}
	}

	graphics->FillRectangle(Brushes::Black, 0, 512, 1024, 128);
	Font^ letra = gcnew Font("Consolas", 14.0f);

	String^ de_quien;

	if (turno == Turno::Aleman)
	{
		de_quien = "Alemanes";
	}

	else
	{
		de_quien = "Sovieticos";
	}

	graphics->DrawString(String::Format("Turno {0} - {1}", numero_turno, de_quien), letra, Brushes::White, 15, 525);

	graphics->DrawString(String::Format("Alemanes: {0} Sovieticos: {1} Bajas sovieticas: {2}", alemanes, sovieticos, bajas_sovieticas), letra, Brushes::White, 15, 555);
	graphics->DrawString("Clic: elegir / mover / atacar Espacio: Terminar turno", letra, Brushes::Gray, 15, 595);
	delete letra;
}

Unidad^ Controladora::buscar_aleman_mas_cercano(Unidad^ desde)
{
	Unidad^ cercano = nullptr;
	int menor = 1000;

	for (int i = 0; i < unidades->Count; i++)
	{
		if (unidades[i]->obtener_bando() == Bando::Aleman)
		{
			int d = distancia(desde, unidades[i]);

			if (d < menor)
			{
				menor = d;
				cercano = unidades[i];
			}
		}
	}

	return cercano;
}

void Controladora::actuar_enemigo(Unidad^ enemigo)
{
	Unidad^ objetivo = buscar_aleman_mas_cercano(enemigo);

	if (objetivo == nullptr)
	{
		return;
	}

	if (distancia(enemigo, objetivo) == 1)
	{
		atacar(enemigo, objetivo);
		return;
	}

	int mov = enemigo->obtener_movimiento();
	int mejor_fila = -1;
	int mejor_columna = -1;
	int mejor_distancia = distancia(enemigo, objetivo);

	for (int f = enemigo->obtener_fila() - mov; f <= enemigo->obtener_fila() + mov; f++)
	{
		for (int c = enemigo->obtener_columna() - mov; c <= enemigo->obtener_columna() + mov; c++)
		{
			if (puede_ir_a(enemigo, f, c))
			{
				int d = Math::Abs(f - objetivo->obtener_fila()) + Math::Abs(c - objetivo->obtener_columna());

				if (d < mejor_distancia)
				{
					mejor_distancia = d;
					mejor_fila = f;
					mejor_columna = c;
				}
			}
		}
	}

	if (mejor_fila != -1)
	{
		enemigo->mover_a(mejor_fila, mejor_columna);
	}
}

void Controladora::turno_enemigo()
{
	if (indice_enemigo < cola_enemiga->Count)
	{
		Unidad^ enemigo = cola_enemiga[indice_enemigo];
		indice_enemigo = indice_enemigo + 1;
		actuar_enemigo(enemigo);
	}

	else
	{
		for (int i = 0; i < unidades->Count; i++)
		{
			unidades[i]->nuevo_turno();
		}

		turno = Turno::Aleman;
		numero_turno = numero_turno + 1;
	}
}

bool Controladora::todos_los_alemanes_actuaron()
{
	for (int i = 0; i < unidades->Count; i++)
	{
		if (unidades[i]->obtener_bando() == Bando::Aleman && !unidades[i]->obtener_ya_actuo())
		{
			return false;
		}
	}

	return true;
}