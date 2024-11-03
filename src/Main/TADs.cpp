#include <iostream>
#include <vector>
#include "../RamonLib/Utiles.h"
#include "../RamonLib/ListaEnlazada.h"

using string = std::string;

void PruebaListaEnlazada();
void PruebaVector();

void PruebaTADs()
{
    //PruebaListaEnlazada();
    PruebaVector();
}

void PruebaListaEnlazada()
{
    // LISTA ENLAZADA
    
    // Constructora normal
    //RamonLib::ListaEnlazada<string> listaFrutas; // Más lento, tendríamos que llamar a "Añade" 4 veces
    //listaFrutas.Aniade("limon"); 
    //string fruta2 = "platano";
    //listaFrutas.Aniade("platano"); // etc.

    // Constructora con lista de inicialización (usando llaves)
    RamonLib::ListaEnlazada<string> listaFrutas = { "limon", "platano", "pera", "manzana" };
    listaFrutas.ImprimeDebug("Lista 1");

    // Constructora por copia
    std::cout << "\n\n";
    RamonLib::ListaEnlazada<string>lista2 = listaFrutas;
    lista2.ImprimeDebug("Lista 2");

    // Apuntan a distintos nodos gracias al constructor por copia
    std::cout << "\n\n\tCambio de fruta" << "\n";
    listaFrutas[0] = "albaricoque";
    listaFrutas.ImprimeDebug("Lista 1");
    std::cout << "\n\n";
    lista2.ImprimeDebug("Lista 2");
    std::cout << "\n\n";

    // Añadir e insertar elementos
    string frutaAux = "freson";
    string frutaIns = "ananas";
    lista2.Aniade(frutaAux);
    lista2.Inserta(frutaIns, 0);
    lista2.ImprimeDebug("Lista 2");
    std::cout << std::endl;

    // Operador de acceso (get y set)
    lista2[1] = "donquixote";
    NOMBRE_VALOR_MEMORIA(lista2[1]);
    lista2.ImprimeDebug("Lista 2");
    std::cout << std::endl;

    // Eliminar elementos
    while (lista2.Tamanio() > 0)
        lista2.Elimina(0);
    lista2.ImprimeDebug("Lista 2 tras eliminar");

    // Otras funciones
    std::cout << std::endl;
    NOMBRE_VALOR(lista2.Tamanio());

    // CONSTRUCTOR POR COPIA / OPERADOR DE ASIGNACIÓN
    std::cout << std::endl;
    // Aquí se llama a la constructora
    RamonLib::ListaEnlazada<bool> a;
    a.Aniade(false); a.Aniade(true);
    // Aquí se llama al constructor por copia, porque 'b' todavía no está creado 
    // ((el código se ejecuta de derecha a izquierda))
    RamonLib::ListaEnlazada<bool> b = a;
    // Aquí se llama al operador de asignación, porque 'c' está creado antes de ser asignado a 'a'
    RamonLib::ListaEnlazada<bool> c; //llamada al constructor
    c = a; 
    // equivalente a escribir c.operator=(a), llamando explícitamente al operador  de asignación
    //c.operator=(a); //<- justo esto

    // Esta línea daría problemas si no evitáramos la auto-asignación en el operador
    //c = c.operator=(a);
    // c.operator=(c.operator=(a)) // equivalente

    // Resultados (no hay referencias cruzadas de nodos)
    b[0] = true;
    c[1] = false;
    a.ImprimeDebug("Lista a"); std::cout << std::endl;
    b.ImprimeDebug("Lista b"); std::cout << std::endl;
    c.ImprimeDebug("Lista c");

    // Si "ListaEnlazada" no tuviera definido un operador de asignación, el programa petaría al terminar esta 
    // función (porque la destructora de 'a' intentaría borrar los nodos que ya ha borrado 'c' en la suya
    // Las destructoras de variables locales se llaman en orden inverso a su declaración (c -> b -> a)

} // Aquí se llama a las 3 destructoras

void PruebaVector()
{
    // ITERADORES

    // begin
    std::vector<int> vector{ 1, 2, 3 };
    std::vector<int>::iterator it = vector.begin();
    it++;
    NOMBRE_VALOR(*it);

    // rbegin, rend
    // Para recorrer el contenedor empezando por el final
    auto it2 = vector.rbegin();
    while (it2 != vector.rend())
    {
        std::cout << (*it2) << ", ";
        it2++; // Es "++" porque el recorrido de la iteración es  a la inversa
    }

    // Tamaño del iterador (12 bytes)
    std::cout << std::endl;
    NOMBRE_VALOR(sizeof(it));

    // El atributo '_Ptr' contiene el puntero al elemento en cuestión
    it = vector.end() - 1;
    NOMBRE_VALOR(*(it._Ptr));
}