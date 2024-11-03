#include "Utiles.h"

namespace Utiles
{
	void ImprimeArray(const int v[], const int tama�o)
	{
		for (int i = 0; i < tama�o; i++)
			std::cout << v[i] << " ";
	}


	void ImprimeHex(int i)
	{
		//M�scara para mostrar medio byte = 15 = (1111)2
		const unsigned char mascaraMedioByte = 0x0F; // Tambi�n podr�a poner 15 (1111)

		int tama�o = sizeof(i);

		std::cout << "0x";
		for(int k = (tama�o * 2 - 1); k >= 0; k--)
		{
			unsigned int resultadoMascara = (mascaraMedioByte << (k * 4)) & i;
			resultadoMascara >>= k * 4;
			if (resultadoMascara < 10) // 1- 9
				std::cout << resultadoMascara;
			else // A (ascii 65) - F
				std::cout << (char)(65 + resultadoMascara - 10);
		}
	}

	bool HayBit(const int num, unsigned const char pos)
	{
		return (num >> pos) % 2;
	}

	// Se pueden usar anotaciones SAL (Source-Code Annotation Language) como _In_, pero no s� exactamente para
	// qu� sirven, porque el usuario no las ve al escribir la funci�n, y no te dan error si las usas mal
	int Suma_Valor(int num, int cant)
	{
		num += cant; // Puede hacerse porque num entra por valor
		return num;
	}

	void Suma_Salida(int num, int cant, int&res)
	{
		num += cant;
		res = num;
	}

	void Suma_Referencia(int& num, int cant)
	{
		num += cant;
		// Es equivalente a pasar un int* num y luego operar con (*num)+=cant;
		// En C asecas, se hace de esa forma
	}

	int Suma_RefConstante(const int& num, int cant)
	{
		//num += cant; // No puede hacerse porque num entra por referencia constante
		return num + cant;
	}
}