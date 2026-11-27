#pragma once
#include "Mapa.h"
#include "Unidad.h"
#include "Bomba.h"

using namespace System;
using namespace System::Drawing;
using namespace System::Collections::Generic;

enum class Turno { Aleman, Sovietico };

ref class Sesion
{
public:
	static bool jugar_de_nuevo;
};

ref class Controladora
{
private:
	Mapa^ mapa;
	List<Unidad^>^ unidades;
	Bitmap^ sprite_soldado;
	Bitmap^ sprite_soldado1;
	Bitmap^ sprite_abuela;
	Bitmap^ sprite_mujer;
	Bitmap^ sprite_nino;
	Bitmap^ sprite_bomba;
	List<Bomba^>^ bombas;
	bool bombardeando;
	void terminar_bombardeo();
	void lanzar_bombas(int cantidad);
	Unidad^ seleccionada;

	Unidad^ buscar_unidad(int fila, int columna);
	bool puede_ir_a(Unidad^ unidad, int fila, int columna);
	void dibujar_alcance(Graphics^ graphics);
	bool hay_alguien_moviendose();

	int bajas_sovieticas;
	int sovieticos_iniciales;
	int sovieticos_oleada;
	int bajas_oleada;
	int bombardeos;
	int calcular_puntaje();
	int contar_sovieticos();
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
	void aparecer_unidad(int fila, int columna, Bando bando, Bitmap^ sprite, int vida);

	bool evento_zhukov;
	void revisar_eventos();
	void bombardeo();
	void perder_tropas_alemanas();
	void agregar_linea(String^ nombre, String^ texto);
	void iniciar_dialogo();
	void dibujar_dialogo(Graphics^ graphics);
	void dibujar_derrota(Graphics^ graphics);
	void aparecer_sovieticos(int cantidad);

	bool dialogo_activo;
	bool derrota;
	int contar_alemanes();
	String^ dialogo_nombre;
	String^ dialogo_texto;
	List<String^>^ dialogo_nombres;
	List<String^>^ dialogo_textos;
	int dialogo_indice;
public:
	Controladora();
	~Controladora();

	void dibujar(Graphics^ graphics);
	void clic(int x, int y);
	void mover();

	void terminar_turno();
	bool hay_derrota();
	void trampa_matar();
	void trampa_bombardeo();
};

Controladora::Controladora()
{
	mapa = gcnew Mapa();
	unidades = gcnew List<Unidad^>();
	sprite_soldado = gcnew Bitmap("sprites/Sprite-0002.png");
	sprite_soldado1 = gcnew Bitmap("sprites/Sprite-0003.png");
	sprite_abuela = gcnew Bitmap("sprites/Sprite-0006.png");
	sprite_mujer = gcnew Bitmap("sprites/Sprite-0007.png");
	sprite_nino = gcnew Bitmap("sprites/Sprite-0008.png");
	sprite_bomba = gcnew Bitmap("sprites/Sprite-0009.png");
	sprite_bomba->RotateFlip(RotateFlipType::RotateNoneFlipY);
	bombas = gcnew List<Bomba^>();
	bombardeando = false;
	seleccionada = nullptr;
	bajas_sovieticas = 0;
	evento_zhukov = false;
	sovieticos_oleada = 0;
	bajas_oleada = 0;
	bombardeos = 0;

	dialogo_activo = false;
	derrota = false;
	dialogo_nombre = "";
	dialogo_texto = "";

	dialogo_nombres = gcnew List<String^>();
	dialogo_textos = gcnew List<String^>();
	dialogo_indice = 0;

	numero_turno = 1;

	int tamano = mapa->obtener_tamano();
	unidades->Add(gcnew Unidad(12, 5, Bando::Aleman, tamano, sprite_soldado));
	unidades->Add(gcnew Unidad(12, 7, Bando::Aleman, tamano, sprite_soldado));
	unidades->Add(gcnew Unidad(11, 9, Bando::Sovietico, tamano, sprite_soldado1));

	unidades->Add(gcnew Unidad(10, 14, Bando::Sovietico, tamano, sprite_soldado1));
	unidades->Add(gcnew Unidad(9, 16, Bando::Sovietico, tamano, sprite_soldado1));
	unidades->Add(gcnew Unidad(11, 18, Bando::Sovietico, tamano, sprite_soldado1));
	aparecer_unidad(10, 21, Bando::Sovietico, sprite_soldado1, 10);
	aparecer_unidad(11, 25, Bando::Sovietico, sprite_soldado1, 10);
	
	sovieticos_iniciales = 0;

	for (int i = 0; i < unidades->Count; i++)
	{
		if (unidades[i]->obtener_bando() == Bando::Sovietico)
		{
			sovieticos_iniciales = sovieticos_iniciales + 1;
		}
	}
	
	turno = Turno::Aleman;
	cola_enemiga = gcnew List<Unidad^>();
	indice_enemigo = 0;
	espera = 0;

	aparecer_unidad(13, 4, Bando::Aleman, sprite_abuela, 5);
	aparecer_unidad(13, 5, Bando::Aleman, sprite_mujer, 5);
	aparecer_unidad(13, 6, Bando::Aleman, sprite_nino, 5);
	aparecer_unidad(13, 7, Bando::Aleman, sprite_abuela, 5);
	aparecer_unidad(13, 8, Bando::Aleman, sprite_mujer, 5);
	aparecer_unidad(13, 9, Bando::Aleman, sprite_nino, 5);
}

Controladora::~Controladora()
{
	delete sprite_soldado;
	delete sprite_soldado1;
	delete sprite_abuela;
	delete sprite_mujer;
	delete sprite_nino;
	delete sprite_bomba;
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

	for (int i = 0; i < bombas->Count; i++)
	{
		bombas[i]->dibujar(graphics, sprite_bomba);
	}

	dibujar_panel(graphics);

	if (dialogo_activo)
	{
		dibujar_dialogo(graphics);
	}

	if (derrota)
	{
		dibujar_derrota(graphics);
	}
}

void Controladora::clic(int x, int y)
{
	if (dialogo_activo)
	{
		dialogo_indice = dialogo_indice + 1;

		if (dialogo_indice < dialogo_nombres->Count)
		{
			dialogo_nombre = dialogo_nombres[dialogo_indice];
			dialogo_texto = dialogo_textos[dialogo_indice];
		}

		else
		{
			dialogo_activo = false;
			dialogo_nombres->Clear();
			dialogo_textos->Clear();
		}

		return;
	}

	if (bombardeando)
	{
		return;
	}

	if (derrota)
	{
		return;
	}

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
		Unidad^ atacante = seleccionada;
		atacar(atacante, unidad);
		atacante->marcar_actuo();
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
	for (int i = bombas->Count - 1; i >= 0; i--)
	{
		bombas[i]->caer();

		if (bombas[i]->llego())
		{
			bombas->RemoveAt(i);
		}
	}

	if (bombardeando)
	{
		if (bombas->Count == 0)
		{
			bombardeando = false;
			terminar_bombardeo();
		}

		return;
	}

	if (dialogo_activo)
	{
		return;
	}

	if (derrota)
	{
		return;
	}

	if (contar_alemanes() == 0)
	{
		derrota = true;
		return;
	}

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
			bajas_oleada = bajas_oleada + 1;
			revisar_eventos();
		}
	}
}

void Controladora::terminar_turno()
{
	if (dialogo_activo)
	{
		return;
	}

	if (derrota)
	{
		return;
	}

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
		de_quien = "Germans";
	}

	else
	{
		de_quien = "Soviets";
	}

	graphics->DrawString(String::Format("Shift {0} - {1}", numero_turno, de_quien), letra, Brushes::White, 15, 525);

	graphics->DrawString(String::Format("Germans: {0} / Soviets: {1} / Soviet casualties: {2}", alemanes, sovieticos, bajas_sovieticas), letra, Brushes::White, 15, 555);
	graphics->DrawString("Clic: choose / move / attack Space: End shift", letra, Brushes::Gray, 15, 595);
	
	if (evento_zhukov)
	{
		graphics->DrawString("Zhukov event", letra, Brushes::Yellow, 700, 525);
	}

	graphics->DrawString(String::Format("Wave kills: {0} / {1}", bajas_oleada, sovieticos_oleada), letra, Brushes::Yellow, 700, 555);

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

void Controladora::aparecer_unidad(int fila, int columna, Bando bando, Bitmap^ sprite, int vida)
{
	if (!mapa->es_transitable(fila, columna) || buscar_unidad(fila, columna) != nullptr)
	{
		return;
	}

	Unidad^ nueva = gcnew Unidad(fila, columna, bando, mapa->obtener_tamano(), sprite);
	nueva->establecer_vida(vida);
	unidades->Add(nueva);
}

void Controladora::aparecer_sovieticos(int cantidad)
{
	int puestos = 0;

	for (int c = 31; c >= 0 && puestos < cantidad; c--)
	{
		for (int f = 9; f <= 13 && puestos < cantidad; f++)
		{
			if (mapa->es_transitable(f, c) && buscar_unidad(f, c) == nullptr)
			{
				aparecer_unidad(f, c, Bando::Sovietico, sprite_soldado1, 10);
				puestos = puestos + 1;
			}
		}
	}
}

void Controladora::revisar_eventos()
{
	if (!evento_zhukov && bajas_sovieticas * 4 >= sovieticos_iniciales)
	{
		evento_zhukov = true;
		aparecer_sovieticos(sovieticos_iniciales * 2);
		sovieticos_oleada = contar_sovieticos();
		bajas_oleada = 0;

		agregar_linea("MARSHAL ZHUKOV", "Fresh divisions have reached the city. Berlin will fall");
		agregar_linea("GENERAL HELMUTH WEIDLING", "Hold the line. Defend to the last man.");
		iniciar_dialogo();
	}

	if (evento_zhukov && sovieticos_oleada > 0 && bajas_oleada * 10 >= sovieticos_oleada * 9)
	{
		bombardeo();
	}
}

void Controladora::agregar_linea(String^ nombre, String^ texto)
{
	dialogo_nombres->Add(nombre);
	dialogo_textos->Add(texto);
}

void Controladora::iniciar_dialogo()
{
	if (dialogo_nombres->Count == 0)
	{
		return;
	}

	dialogo_indice = 0;
	dialogo_nombre = dialogo_nombres[0];
	dialogo_texto = dialogo_textos[0];
	dialogo_activo = true;
	seleccionada = nullptr;
}

void Controladora::dibujar_dialogo(Graphics^ graphics)
{
	graphics->FillRectangle(Brushes::Black, 0, 512, 1024, 128);

	SolidBrush^ dorado = gcnew SolidBrush(Color::FromArgb(216, 176, 64));
	graphics->FillRectangle(dorado, 15, 525, 6, 24);
	delete dorado;

	Font^ letra_nombre = gcnew Font("Consolas", 16.0f, FontStyle::Bold);
	Font^ letra = gcnew Font("Consolas", 14.0f);

	graphics->DrawString(dialogo_nombre, letra_nombre, Brushes::White, 30, 525);
	graphics->DrawString(dialogo_texto, letra, Brushes::White, RectangleF(30, 560, 960, 70));

	delete letra_nombre;
	delete letra;
}

int Controladora::contar_sovieticos()
{
	int total = 0;

	for (int i = 0; i < unidades->Count; i++)
	{
		if (unidades[i]->obtener_bando() == Bando::Sovietico)
		{
			total = total + 1;
		}
	}

	return total;
}

int Controladora::contar_alemanes()
{
	int total = 0;

	for (int i = 0; i < unidades->Count; i++)
	{
		if (unidades[i]->obtener_bando() == Bando::Aleman)
		{
			total = total + 1;
		}
	}

	return total;
}

void Controladora::perder_tropas_alemanas()
{
	List<Unidad^>^ alemanes = gcnew List<Unidad^>();

	for (int i = 0; i < unidades->Count; i++)
	{
		if (unidades[i]->obtener_bando() == Bando::Aleman)
		{
			alemanes->Add(unidades[i]);
		}
	}

	int perdidas = (alemanes->Count + 1) / 2;
	Random^ azar = gcnew Random();

	for (int i = 0; i < perdidas; i++)
	{
		int elegido = azar->Next(alemanes->Count);
		unidades->Remove(alemanes[elegido]);
		alemanes->RemoveAt(elegido);
	}
}

void Controladora::bombardeo()
{
	bombardeando = true;
	sovieticos_oleada = 0;
	bajas_oleada = 0;
	seleccionada = nullptr;

	lanzar_bombas(14);
}

void Controladora::terminar_bombardeo()
{
	bombardeos = bombardeos + 1;
	perder_tropas_alemanas();
	aparecer_sovieticos(sovieticos_iniciales);

	sovieticos_oleada = contar_sovieticos();
	bajas_oleada = 0;

	agregar_linea("GENERAL HELMUTH WEIDLING", "Artillery! Take cover!");
	iniciar_dialogo();
}

int Controladora::calcular_puntaje()
{
	return bajas_sovieticas * 100 + bombardeos * 500 + numero_turno * 10;
}

void Controladora::dibujar_derrota(Graphics^ graphics)
{
	graphics->FillRectangle(Brushes::Black, 0, 0, 1024, 640);

	SolidBrush^ dorado = gcnew SolidBrush(Color::FromArgb(216, 176, 64));
	Font^ letra_titulo = gcnew Font("Consolas", 48.0f, FontStyle::Bold);
	Font^ letra = gcnew Font("Consolas", 20.0f);

	graphics->DrawString("BERLIN HAS FALLEN", letra_titulo, dorado, 190, 50);

	graphics->DrawString(String::Format("Soviet casualties: {0}", bajas_sovieticas), letra, Brushes::White, 330, 190);
	graphics->DrawString(String::Format("Waves survived: {0}", bombardeos), letra, Brushes::White, 330, 230);
	graphics->DrawString(String::Format("Shifts survived: {0}", numero_turno), letra, Brushes::White, 330, 270);
	graphics->DrawString(String::Format("SCORE: {0}", calcular_puntaje()), letra, dorado, 330, 330);

	graphics->DrawString("Epilogue text goes here.", letra, Brushes::Gray, RectangleF(100, 430, 824, 150));
	graphics->DrawString("Click to play again", letra, dorado, 370, 590);

	delete dorado;
	delete letra_titulo;
	delete letra;
}

bool Controladora::hay_derrota()
{
	return derrota;
}

void Controladora::trampa_matar()
{
	if (dialogo_activo || derrota)
	{
		return;
	}

	for (int i = 0; i < unidades->Count; i++)
	{
		if (unidades[i]->obtener_bando() == Bando::Sovietico)
		{
			unidades->RemoveAt(i);
			bajas_sovieticas = bajas_sovieticas + 1;
			bajas_oleada = bajas_oleada + 1;
			revisar_eventos();
			return;
		}
	}
}

void Controladora::trampa_bombardeo()
{
	if (dialogo_activo || derrota || bombardeando)
	{
		return;
	}

	bombardeo();
}

void Controladora::lanzar_bombas(int cantidad)
{
	Random^ azar = gcnew Random();

	for (int i = 0; i < cantidad; i++)
	{
		int x = azar->Next(0, 1008);
		int destino = azar->Next(150, 500);
		int retraso = i * 20 + azar->Next(0, 20);

		bombas->Add(gcnew Bomba(x, destino, retraso));
	}
}