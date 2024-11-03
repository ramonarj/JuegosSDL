#pragma once
#include <iostream>

// Declaraci�n de macros. El '\' es para indicar que la macro sigue en la siguiente l�nea

// Imprime el nombre y contenido de una variable por pantalla
#define NOMBRE_VALOR(VAR) \
std::cout << #VAR << " = " << VAR << std::endl;

// Imprime el nombre, contenido y direcci�n de memoria de una variable
#define NOMBRE_VALOR_MEMORIA(VAR) \
std::cout << #VAR << " = " << VAR << " (0x" << &VAR << ")" << std::endl;

// Concatena los dos tokens
#define CONCATENA(VAR1, VAR2) \
VAR1##VAR2;

namespace Utiles
{
	static int varPrueba = 0;


	void ImprimeArray(const int vector[], int tama�o);

	// Las plantillas solo pueden implementarse en los archivos de cabecera en C++, no en el cpp
	template<typename T>
	void ImprimeBinario(T i)
	{
		unsigned const char tamBits = sizeof(T) * 8;
		for (int k = tamBits - 1; k >= 0; k--)
		{
			T res = (1 << k) & i;
			if (res)
				std::cout << 1;
			else
				std::cout << 0;
		}
	}

	// Muestra un entero en su representaci�n hexadecimal
	void ImprimeHex(int i);

	// Nos dice si hay bit en la posici�n dada, empezando por la derecha y con el 0
	bool HayBit(const int num, unsigned const char pos);

	// Ejemplos de una misma funcionalidad con distintos tipos de par�metros:
	// ((Funci�n ilustrativa)) Suma una cantidad al n�mero recibido.
	int Suma_Valor(int num, int cant);
	// ((Funci�n ilustrativa)) Suma una cantidad al n�mero recibido y lo devuelve en 'res'
	void Suma_Salida(int num, int cant, int& res);
	// ((Funci�n ilustrativa)) Igual que la primera, pero con el resultado esperado
	void Suma_Referencia(int& num, int cant);
	// ((Funci�n ilustrativa)) Igual que la primera, pero con el resultado esperado
	int Suma_RefConstante(const int& num, int cant);


	// Valor devuelto de forma normal
	static int DevuelveNormal() { return varPrueba; }
	// Valor devuelto por referencia
	static int& DevuelveReferencia() { return varPrueba; }
	// Valor devuelto por referencia constante
	static const int& DevuelveRefConst() { return varPrueba; }
	// Valor devuelto en un puntero
	static int* DevuelvePuntero() { return &varPrueba; }
}