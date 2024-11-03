// Main.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.

#include <iostream>
#include <fstream>
//#include <cstring>
#include <vector>
#include <bitset>
#include <cassert>
#include "../RamonLib/Utiles.h"
#include "../RamonLib/ListaEnlazada.h"
#include "../RamonLib/checkML.h"

using string = std::string;


// Declaración de funciones (para que compile; si no habría que poner el main al final)
void PruebaTipos();
void PruebaEnums();
void PruebaOperadores();
void PruebaArrays();
void PruebaPunteros();
void PruebaPasoParametros();
void PruebaStructs();
void PruebaStrings();
void PruebaFlujos();
void PruebaArchivos();
void PruebaMacros();
void PruebaTryCatch();
void PruebaBits();
void PruebasVarias();


// Esto está definido en Ensamblador.cpp, pero no vamos a hacer el include porque es un .cpp
// (solo lo declaramos, dejamos que lo resuelva el vinculador)
// Realmente es lo mismo que que crear un .h con la declaración de la función (que se define en el .cpp)
void PruebaEnsamblador();
void PruebaTADs();


#define TRES 3;


int main()
{
    // Para detectar memoria dinámica que falte por borrar (Memory Leaks)
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);


    //PruebaTipos();
    //PruebaOperadores();
    //PruebaEnums();
    //PruebaArrays();
    //PruebaPunteros();
    //PruebaPasoParametros();
    //PruebaStructs();
    //PruebaStrings();
    //PruebaFlujos();
    //PruebaArchivos();
    //PruebaMacros();
    //PruebaTryCatch();
    //PruebaEnsamblador();
    //PruebaBits();
    PruebasVarias();
    //PruebaTADs();

    // Para que no se cierre
    int e;
    std::cin >> e;

    // Prueba de memoria dinámica sin borrar
    RamonLib::ListaEnlazada<double>* listaDoubles = new RamonLib::ListaEnlazada<double>();
    listaDoubles->~ListaEnlazada(); // Llamada explícita al destructor (sigue dando memory leak)
    delete listaDoubles;// operador delete (libera la memoria dinámica)
    //listaDoubles->Aniade(2.3); //ERROR: infracción de memoria

    return 0;
}

// Definición de las funciones declaradas
void PruebaTipos()
{
    uint32_t lel;
    unsigned int ol;
    
    long long largo;
    using EnteroLargo = int64_t;
    EnteroLargo tLargo;
    int harray[4] = { 1, 2, 3, 4 };
    int matriz[3][3];

    unsigned int sinSigno = -3;
    //switch(sinSigno)
    //{
    //case -3:
    //    std::cout << "Vale -3\n"; 
    //    break;
    //case 4294967293: // Esto es pa cagarse de la risa jajajajaja
    //    break;
    //}

    bool si = true;
    int a, b, c;

    std::cout << "Hola mundo\n";
    std::cout << sinSigno;
    std::cout << "Tamaño de int64_t:" << sizeof(largo) << "\n";
    std::cout << "Tamaño de unsigned int:" << sizeof(ol) << "\n";


    // Caracteres. Realmente se pueden usar como tipos enteros de 1 byte (0-255)
    std::cout << std::endl;
    char i1 = 4;
    char i2 = 6;
    char i3 = 65;
    std::cout << sizeof(i1) << std::endl;
    std::cout << "i1: " << i1 << " | i2: " << i2 << " | i3: " << i3 << std::endl; 
    std::cout << "i1 + i2 = " << i1 + i2 << std::endl;


    char c1 = '4';
    char c2 = '6';
    std::cout << "c1: " << c1 << " | c2: " << c2 << std::endl;
    std::cout << "c1 + c2 = " << c1 + c2 << std::endl; //52 + 54 = 106
    std::cout << "(char)(c1 + c2) = " << (char)(c1 + c2) << std::endl; // 'j' es el caracter 106


    // Pruebas de type_info y typeid
    // Esto hay que declararlo EXACTAMENTE así o da error (con el const y el '&')
    string sPrueba = "cadena prueba";
    int f = 3;
    const type_info &tipoVar = typeid(std::vector<short>); 
    std::cout << tipoVar.name();
}

void PruebaOperadores()
{
    // Operador de desplazamiento
    int a = 8;
    std::cout << (a << 1) << std::endl;
    std::cout << (a >>= 1) << std::endl;
    std::cout << a << std::endl;

    // Operadores de puertas lógicas (bit-a-bit)
    int b = 5;
    std::cout << "\n" << b << " & 1: " << (b & 1) << std::endl;
    std::cout << b << " | 1: " << (b | 1) << std::endl;
    std::cout << b << " ^ 1: " << (b ^ 1) << std::endl;
    int noB = ~b;
    std::cout << "~" << b << ": " << (~b) << std::endl;

    /*
    * Los operadores bit-a-bit tienen palabras alternativas con las que se pueden usar
    * & = bitand
    * | = bitor
    * ~ = compl 
    * ^ = xor
    * Y también otros operadores como &&, ||, ! ... se pueden poner de distinta forma
    */

    // Conseguir un -5 a partir del 5 con operaciones bit a bit
    int menosB = noB + 1;
    std::cout << "Menos " << b << ": " << menosB << std::endl << std::endl;


    // Pruebas del complemento a 2 y la representación en hexadecimal
    int minimo = INT_MIN; //0x8000...0
    int maximo = INT_MAX; //0x7fff...f
    int cero = 0; 
    int menosUno = -1; //0xfff...f

    //for(int i = 0; i <= INT_MAX; i++)
    //{
    //    Utiles::ImprimeHex(i);
    //    std::cout << std::endl;
    //}

    // Pruebas del operador de desplazamiento para codificar en binario/hexadecimal, usando plantillas
    int diez = 10;
    char diezChar = diez;
    Utiles::ImprimeBinario<int>(10);
    std::cout << std::endl;
    Utiles::ImprimeBinario(diez);
    std::cout << std::endl;
    Utiles::ImprimeBinario(diezChar);
    std::cout << std::endl;
    Utiles::ImprimeHex(diez);
    std::cout << std::endl;
}

void PruebaEnums()
{
    // Enums
    // A efectos prácticos son una colección de variables enteras. De normal empiezan en 0, si se
    // le pone un valor explícito a un componente, los siguientes continúan desde ese valor.
    enum Nombres { Ramon = 'e', Juan, Pepe };
    Nombres n = Ramon;
    std::cout << "\nPepe: " << Nombres::Pepe << std::endl;
    int ramoncito = (Ramon - 1) / 2; //'e' = 101
    std::cout << "Ramoncito: " << ramoncito << std::endl;
    //std::cout << "Juan: " << Nombres::Juan << std::endl;

    enum class Colores { Rojo = 2, Verde, Violeta };
    Colores col1 = Colores::Violeta;
    // Esto no compila; 'enum class' no deja convertir los elementos implícitamente a int
    //int purpura = Colores::Violeta + 1; 
    int purpura = (int)Colores::Violeta + 1; // Esto sí
    std::cout << "Purpura: " << purpura << std::endl;
    if (col1 != Colores::Rojo)
        std::cout << "No es rojo, es " << (int)col1 << std::endl; //no se como sacar el nombre 

    enum class Sexo : char { V, H } sexo;
    sexo = Sexo::V;
    enum class Mae : short { V, H } OJO;

    std::cout << sizeof(sexo) << std::endl;
    std::cout << sizeof(Mae) << std::endl;

    // Todo lo que no esté en la posición 0 se convierte a true
    enum Verdadero : bool{Falso = true, Verda, Nose, asd, aseee, otpto, pqqo, dajjejje, Aver = false};
    Verdadero nidea = Aver;
    std::cout << nidea << std::endl;
}

// PARA LA PRUEBA DE STRUCTS
//Podemos definir una/varias variables al final del struct 
struct Mueble
{
    string madera;
    bool barnizado;
    int precio;
} silla, mesa, estanteria;

// Podemos sobrecargar los operadores de inserción (<<) y extracción (>>) para 
// usar tipos no básicos (structs, clases propias) dentro de flujos de E/S
std::ostream& operator<<(std::ostream& os, const Mueble& m)
{
    string barnizadoStr = m.barnizado ? "Si" : "No";
    return os << "MUEBLE\n{ Tipo de madera: " << m.madera << std::endl
        << "  Barnizado: " << barnizadoStr << std::endl
        << "  Precio: " << m.precio << "$ }\n";
}


void PruebaArrays()
{
    int tamMueble = sizeof(string) + sizeof(int) + sizeof(bool);
    NOMBRE_VALOR(tamMueble);
    int v1[3] = {10, 11, 12};
    //int v2[3] = v1; //Los arrays no pueden asignarse entre sí
    int* pV1 = v1;

    std::cout << v1 << std::endl;
    std::cout << pV1 << std::endl;
    std::cout << *pV1 << std::endl;
    std::cout << pV1[1] << std::endl << std::endl;

    pV1[1] = -1;
    std::cout << sizeof(v1) << std::endl;
    Utiles::ImprimeArray(v1, 3);
    std::cout << std::endl;
    pV1 = nullptr;
    Utiles::ImprimeArray(v1, 3);
    std::cout << "\n\n";

    // INICIALIZACIÓN AGREGADA
    // Podemos usar listas de inicialización para tipos agregados (como arrays, structs, clases),
    // escribiendo los elementos entre LLAVES.
    int arrayInts[4] = { 1, 2, 3, 4 }; // lo normal
    //int arrayInts[4] = { 1, 2, 3, 4, 5 }; //ERROR: demasiados valores de inicializador
    // Esta es una forma rápida de inicializar arrays a 0 sin tener que usar bucles.
    int arraySiete[4] = { 7 }; // los elementos a los que no se les da valor se rellenan con 0 ({7, 0, 0, 0})
    int arraySorpresa[4];

    Utiles::ImprimeArray(arraySiete, 4);
    std::cout << std::endl;
    // Al no estar inicializado, no podemos saber qué valores contendrá
    Utiles::ImprimeArray(arraySorpresa, 4);
    std::cout << std::endl;

    // Otra forma de inicializarlos (sin especificar tamaño)
    int arrayNegs[] = {-1, -2, -3};

    // TAMAÑO DEL ARRAY
    // Con esta expresión (tamaño total / tam. 1º elemento) obtenemos el nº de elementos del array
    int tamArray = sizeof(arrayNegs) / sizeof(*arrayNegs); // 3
    NOMBRE_VALOR(tamArray); 

    // ARRAY DE DATOS DINÁMICOS
    // Se va reservando espacio en el heap para cada uno de los elementos según se vaya necesitando
    // Por tanto, los elementos del array no están en memoria contigua. El array de punteros está en la pila.
    Mueble* arrMuebles[3];
    arrMuebles[0] = new Mueble; // equivalente a new Mueble() con paréntesis

    // Como el array contiene punteros, se puede incluso tener unos elementos en el heap
    // y otros en la pila (como curiosidad, no creo que sea muy útil)
    Mueble mueblePila = { "sauco", true, 5 };
    arrMuebles[1] = &mueblePila; //pila

    arrMuebles[2] = new Mueble; //heap
    delete arrMuebles[0];
    delete arrMuebles[2];

    // Para borrarlos, hay que usar un "for" y hacer un "delete" por cada "new"
    //for (int i = 0; i < 3; i++)
    //    delete arrMuebles[i];


    // ARRAY DINÁMICO
    // Se reserva todo el espacio de golpe, por lo que los elementos del array están en 
    // memoria contigua, como un array normal (pero en el heap). Solamente el puntero a la 1º posición está en la pila.
    Mueble* arrDinamico = new Mueble[5]; // corchetes para especificar el tamaño
    arrDinamico[0] = { "olivo", true, 50 };
    arrDinamico[1] = { "castanio", false, 60 };

    // Para borrarlo, basta con usar el operador especial "delete []"
    delete[] arrDinamico;
}

void PruebaPunteros()
{
    int* pInt = new int(3);
    bool* pBool = nullptr;
    void* pVoid = nullptr;
    auto p2 = pInt;

    std::cout << "Tamaño de puntero:" << sizeof(pInt) << "\n";
    std::cout << pInt << "\n";
    std::cout << p2 << "\n";
    std::cout << *p2 << "\n";
    *pInt = 4;
    std::cout << *p2 << "\n";
    delete pInt;
    std::cout << *p2 << "\n";
    pInt = nullptr;
    std::cout << *p2 << "\n";

    // Punteros a constantes y punteros constantes
    std::cout << std::endl;
    short cortoStack = 9;
    const short cortoStackConst = 140;
    const short cortoHeapConst = *(new const short(23));
    short* pS;
    const short* pShortConst;
    //short* const pConstShort; // Error -> obliga a dar un valor al puntero al declararlo
    short* const pConstShort = &cortoStack; 

    pShortConst = &cortoStack; // Deja hacerlo (aunque cortoStack no es const)
    //*pShortConst = 23; // Error (el contenido del puntero no es modificable)

    *pConstShort = 44;
    //pConstShort = &cortoStackConst; // Error (la dirección del puntero no es modificable)

    std::cout << "Dirección de memoria: " << pShortConst << " | Valor: " << *pShortConst << std::endl;
    std::cout << "Dirección de memoria: " << pConstShort << " | Valor: " << *pConstShort << std::endl;
}

void PruebaPasoParametros()
{
    int num1 = 10;
    int res;
    std::cout << "- - Valores iniciales - -" << std::endl;
    NOMBRE_VALOR_MEMORIA(num1);
    NOMBRE_VALOR_MEMORIA(res);

    //1. Por valor (es el paso por defecto)
    std::cout << "\nSuma_Valor" << std::endl;
    res = Utiles::Suma_Valor(num1, 5);
    NOMBRE_VALOR_MEMORIA(num1);
    NOMBRE_VALOR_MEMORIA(res);

    //2. Por salida (la variable 'res' es devuelta por la función)
    // Es equivalente a hacer "int res = Suma(num1, 5)" pero con funciones tipo void o que 
    // devuelvan no solo uno, sino varios valores (Ej: division(int D, int d, int&c, int&r))
    std::cout << "\nSuma_Salida" << std::endl;
    Utiles::Suma_Salida(num1, 5, res);
    NOMBRE_VALOR_MEMORIA(num1);
    NOMBRE_VALOR_MEMORIA(res);

    //3. Por referencia (se envía a la función como dirección de memoria para que esta opere con sus
    // contenidos sin tener que hacer una copia). Por tanto, la función puede modificarla.
    // A diferencia de las variables de salida, las que pasan por referencia se usan en los cálculos
    // que haga la función, no solo como resultado
    std::cout << "\nSuma_Referencia" << std::endl;
    Utiles::Suma_Referencia(num1, 5);
    NOMBRE_VALOR_MEMORIA(num1);
    NOMBRE_VALOR_MEMORIA(res);

    // 4. Por referencia constante (igual que la 3) pero evitando que se altere su contenido, i.e., 
    // la variable se comporta como solo lectura. Útil para pasar clases grandes y así evitar la copia, 
    // en este ejemplo concreto no tiene demasiado sentido usarlo.
    std::cout << "\nSuma_RefConstante" << std::endl;
    res = Utiles::Suma_RefConstante(num1, 5);
    NOMBRE_VALOR_MEMORIA(num1);
    NOMBRE_VALOR_MEMORIA(res);
    std::cout << "\n";


    // DEVOLUCIÓN DE VALORES
    NOMBRE_VALOR_MEMORIA(Utiles::varPrueba);
    std::cout << std::endl;
    // 1. Normal (sin puntero ni referencia, se crea una copia)
    int var = Utiles::DevuelveNormal();
    var = 47;
    NOMBRE_VALOR_MEMORIA(Utiles::varPrueba); // el valor no ha cambiado
    NOMBRE_VALOR_MEMORIA(var); // el valor no ha cambiado
    std::cout << std::endl;

    // 2. Referencia (a efectos prácticos, es un puntero camuflado para que sea más estético)
    //int varRef = Utiles::DevuelveReferencia(); //Esto no funciona de la forma esperada (pero compila)
    int& varRef = Utiles::DevuelveReferencia();
    varRef = -3; // Esto sí (equivalente a hacer Utiles::DevuelveReferencia() = 47;)
    NOMBRE_VALOR_MEMORIA(Utiles::varPrueba);
    NOMBRE_VALOR_MEMORIA(varRef);
    std::cout << std::endl;

    // 3. Puntero 
    int* varPunt = Utiles::DevuelvePuntero();
    *varPunt = 11;
    NOMBRE_VALOR_MEMORIA(Utiles::varPrueba);
    NOMBRE_VALOR_MEMORIA(varPunt);
    std::cout << std::endl;

    // 4. Referencia constante (podemos leerla pero no escribir)
    //int& varRefConst = Utiles::DevuelveRefConst(); //ERROR: falta el const
    const int& varRefConst = Utiles::DevuelveRefConst();
    //varRefConst = 100; // ERROR: "la expresión debe ser un valor L modificable"
    int otraVar = varRefConst;
    otraVar++;
    NOMBRE_VALOR_MEMORIA(otraVar);
}

void PruebaStructs()
{
    // DECLARACION DE STRUCTS
    // 2 formas distintas de declarar structs
    // 1) Igual que en C#
    struct Persona
    {
        int edad;
        bool hombre;
        string nombre;
        //Persona pareja; // ERROR: tipo incompleto (estamos definiéndolo todavía)
        Persona* pareja; // ok
    };

    // 2) Con typedef, y el nombre del struct al final
    typedef struct
    {
        string especie;
        bool macho;
    } Animal;

    Persona p; 
    Animal a;
    a.macho = false;


    // Variables declaradas junto a la definición de "Mueble"
    silla.madera = mesa.madera = "roble";
    estanteria.madera = "caoba";

    // Comoo tipo agregado que son, los structs pueden crearse con listas de inicialización
    Mueble armario = { "eucalipto", false, 75 };
    //Mueble armario = { -21.5, "baobab", 75 }; // ERROR: el compilador sabe de qué tipo es cada parámetro
    std::cout << armario; // prueba de operator<<


    // UNION TYPES
    // Ocupa lo mismo que su miembro más grande (en este caso int = 4 bytes)
    // El resto de miembros comparten esta memoria
    union Color 
    {
        unsigned char r; //1 byte
        unsigned char g; //1 byte
        unsigned char b; //1 byte
        unsigned int rgb; //4 bytes
    };

    Color morado; //Morado
    morado.r = 0xff;
    morado.g = 0x00;
    morado.b = 0xff;
    morado.rgb = 0xff00ff;

    Utiles::ImprimeHex(morado.rgb);
    std::cout << std::endl;
    Utiles::ImprimeHex(morado.r);
    std::cout << std::endl;

    std::cout.setf(std::ios::showbase);
    std::cout << std::hex << morado.rgb << std::endl;
}

// Para que el compilador no se queje por usar "strcpy"
#pragma warning(disable : 4996)
void PruebaStrings()
{
    // C-STRINGS
    char num[] = "numero"; // equivalente a = {"numero}; o = {'n', 'u', 'm', 'e', 'r', 'o'};
    NOMBRE_VALOR_MEMORIA(num);
    NOMBRE_VALOR(sizeof(num)); //7 (6+1)

    //num += "s primos"; //ERROR: solo con std::strings

    // Funciones con C-strings (librería <cstring> o <string>)
    // 1) strcpy: Copia una cadena en otra, borrando el contenido que tuviera
    //char num2[6] = ""; //ERROR en ejecución: valor corrupto  (no cabe el '\0')
    char num2[7] = "asdasd";
    strcpy(num2, num); // del derecho al izquierdo
    NOMBRE_VALOR_MEMORIA(num2);

    // 2) strcat: Añade una cadena a otra (la concatena)
    char primos[] = "s primos";
    char numPrimos[15];
    strcpy(numPrimos, num);
    strcat(numPrimos, primos);
    NOMBRE_VALOR(numPrimos);

    // 3) strlen: Devuelve la longitud de la cadena sin contar el carácter nulo
    // (Visto en el ejemplo anterior)
    NOMBRE_VALOR(strlen(numPrimos));

    // 4) strcmp: Compara dos cadenas, caracter por caracter, devolviendo:
    // ~ 0: si los caracteres son iguales
    // ~ -1: si el primer caracter es menor que el segundo (en ASCII)
    // ~ 1 : si el primer caracter es mayor que el segundo (en ASCII)
    NOMBRE_VALOR(strcmp(num, "numero")); //0
    NOMBRE_VALOR(strcmp(num, "numera")); //1
    NOMBRE_VALOR(strcmp(num, "numeru")); //-1
}


void PruebaFlujos()
{
    // Ya que casi todos los métodos que usamos aquí son de la std, podríamos hacer uso de su espacio
    // de nombres (al poner el "using" dentro de una función, el ámbito se limita a esta)
    //using namespace std;

    int morado = 0xff00ff00;

    // La STD permite cambiar la base del flujo que estamos leyendo/escribiendo
    // a decimal (dec), hexadecimal (hex) y octal (oct). 
    // SE QUEDA CON ESA BASE PUESTA PARA CIN/COUT, IMPORTANTE ACORDARSE
    std::cout.setf(std::ios::showbase); // Para mostrar la base ("0x" en hex)
    std::cout << std::hex << morado << std::endl;


    //Ej: leer un número en hexadecimal y mostrarlo en decimal
    int num;
    std::cout << "Escribe un numero en hexadecimal: ";
    std::cin >> std::hex >> num;
    std::cout << "Tu numero en decimal: " << std::dec << num; //el std::dec es necesario porque el flujo se había quedado en hexadecimal

    // Forma alternativa: cambiando los flags de los flujos 'cin' y 'cout' de antemano (son independientes)
    std::cin.setf(std::ios::hex, std::ios::basefield);
    //...recoger input en hex.
    std::cout.setf(std::ios::dec, std::ios::basefield);
    //...mostrar output en dec.

    // CARACTERES ESPECIALES
    std::cout << "\b"; // backspace
    //std::cout << "\"; // -> error
    std::cout << "\\"; //backslash (para poder escribirlo sin escapar)
    std::cout << "\t"; //tabular
    // Hay más

    // GETLINE: lee caracteres de un flujo y los coloca en un string.
    std::cout << std::endl;
    string lecturaLinea;
    std::cin.ignore(1, '\n'); // Para limpiar lo que había en "cin" (un salto de linea)
    //std::cin.ignore(); // Esta línea funcionaría exactamente igual porque 1 y '\n' son los valores por defecto
    std::getline(std::cin, lecturaLinea);
    std::cout << "Me estas diciendo que " << lecturaLinea << "?";

    // GET: tiene varios usos
    std::cout << "\n¿Su nombre?: ";
    char inicial = std::cin.get(); // sin argumentos, lee solo 1 caracter (aunque sea un espacio)
    std::cin.ignore(30, ' ');
    string apellido;
    std::cin >> apellido;
    std::cout << "Hola " << inicial << ". " << apellido;
}

void PruebaArchivos()
{
    // Por defecto se crean en la carpeta del proyecto, no del ejecutable
    const string RUTA_ARCHIVOS = "../../bin/";

    // Hay que incluir <fstream> (<iostream> es solo para consola)
    // ARCHIVO DE SALIDA
    std::ofstream archivo;
    archivo.open(RUTA_ARCHIVOS + "output.txt"); // si el archivo ya existe, sobreescribe todo lo que hubiera en él
    if(archivo.is_open())
    {
        // Hacer cosas
        archivo << "Esta es una prueba de salida\nY esta es la segunda linea";
    }
    archivo.close(); // importante

    // ARCHIVO DE ENTRADA
    std::ifstream archivoEntrada(RUTA_ARCHIVOS + "output.txt");
    string texto;
    if(archivoEntrada.is_open())
    {
        // Leemos una línea (descarta el salto de línea del final)
        std::getline(archivoEntrada, texto);
    }
    archivoEntrada.close();

    std::cout << texto;
}

void PruebaMacros()
{
    // Prueba de la macro NOMBRE_VALOR
    int Entero = 7;
    NOMBRE_VALOR(Entero);

    int* pEntero = &Entero;
    Entero += TRES;
    NOMBRE_VALOR(pEntero);

    string cadenaCien = "100";
    NOMBRE_VALOR(cadenaCien);
    NOMBRE_VALOR(INT_MAX);

    double numeroDoble = 6.03958595;
    NOMBRE_VALOR(numeroDoble);
    

    // Compilación condicional; según el tipo de build y la plataforma destino, añadimos/omitimos instrucciones
#ifdef _DEBUG
    std::cout << "\nEstamos en Debug";
#else
    std::cout << "\nEstamos en Release";
#endif

#ifdef _WIN64
    std::cout << " para Windows x64" << std::endl;
#else
    std::cout << " para Windows x86" << std::endl;
#endif

    // Prueba de la macro CONCATENA
    string utensilio = CONCATENA("saca", "corchos");
    //string utensilio2 = "saca" + "puntas"; // Esto daría error C2110; "no se pueden sumar dos punteros"
    NOMBRE_VALOR(utensilio);

    int veintitres = CONCATENA(2, 3);
    NOMBRE_VALOR(veintitres);


    // La macro "__LINE__" devuelve la línea de código en la que estamos
    std::cout << "\nLinea " << __LINE__ << std::endl;
    // Lo mismo pasa con "__FILE__"
    std::cout << "Archivo: " << __FILE__ << std::endl;
    // Y con la macro "__func__" o "__FUNCTION__"
    std::cout << "Funcion: " << __func__ << std::endl;
    std::cout << "Funcion: " << __FUNCTION__ << std::endl;
    std::cout << "Funcion detallada: " << __FUNCSIG__ << std::endl;

    // También hay para el día y la hora <EN LA QUE SE COMPILÓ EL PROYECTO>
    // (no sirve para saber el día o la hora sobre la marcha)
    NOMBRE_VALOR(__DATE__);
    int esc = 1;
    do
    {
        NOMBRE_VALOR(__TIME__); // Podemos ver que no se actualiza en pantalla
        std::cin >> esc;
    } while (esc != 0);


    // También se puede "indefinir" ? una macro, para no volver a usarla
    int l = TRES;
#undef TRES
    //int h = TRES; //ERROR: el identificador "TRES" no está definido



    // Aserciones estáticas -> dan fallo en compilación si el valor evaluado es falso
    //static_assert(3 == 4); // ERROR
    static_assert(16 == (32 / 2));
    static_assert(16 == 16.0000001f); // Con un cero menos, da error (precisión de millonésima)

    static_assert(INFINITY > 3);

    // Aserciones normales: se comprueban y provocan excepciones en tiempo de ejecución, no 
    // de compilación (Archivo <cassert>)
    assert(3 == 4); //En consola salta un Debug Error "Assertion failed: 3 == 4, file:.... line:..." 

}

void PruebaTryCatch()
{
    try
    {
        int miArr[5];
        miArr[0] = 3;
        miArr[5] = -1; // Sorprendentemente, esto no lanza excepciones (en C# si)
    }
    // Los 3 puntos significan que atrapa cualquier excepción que le venga
    catch(...)
    {
        std::cout << "Excepción interceptada";
    }
}


void PruebaBits()
{
    bool hayBit = false;

    // El bittest lo podemos hacer también en C++ (pero solo con tipos long). Es específico de Microsoft
    const long siete = 7;
    hayBit = _bittest(&siete, 3); // false
    NOMBRE_VALOR(hayBit);

    // También hay un tipo "bitset" para hacer cosas parecidas, con el tamaño que queramos
    std::cout << "\nBITSET:" << std::endl;
    std::bitset<5> bs{ 0x10 }; // 5 bits, equivalente a {1 0000} = 16
    hayBit = bs.test(4); // true
    //hayBit = bs.test(5); // ERROR-> el test tiene que ser con un número menor o igual al nº bits
    NOMBRE_VALOR(hayBit);

    bs.set(3, 1); //Lo hemos convertido en 24
    hayBit = bs.test(3); // true
    NOMBRE_VALOR(hayBit);
    
    bs.reset(); // pone todos a 0
    bool hayAlgunBit = bs.any(); // false
    NOMBRE_VALOR(hayAlgunBit);

    std::bitset<5> bs2{ 0x1f };
    bool todosBitsActivos = bs2.all(); // true
    NOMBRE_VALOR(todosBitsActivos);


    // También lo podemos implementar nosotros de alguna forma original
    std::cout << std::endl;
    hayBit = Utiles::HayBit(siete, 2); // true
    NOMBRE_VALOR(hayBit);
}


void PruebasVarias()
{
    // Podemos conseguir la dirección de memoria de una función con el operador '&' igual que con otros tipos
    NOMBRE_VALOR_MEMORIA(PruebaBits);
    NOMBRE_VALOR_MEMORIA(PruebaTADs);
    std::cout << &PruebaTADs;
    // Para probarlo en una máquina virtual cuando pueda
#ifdef __linux__
    std::cout << "Estamos en Linux" << std::endl;
#endif
    // intrucción goto (rompe el flujo). Se puede usar si hay muchos bucles anidados,
    // para salir de todos a la vez
    goto pan;

pan:
    std::cout << "Pan" << "\n\n";


    // PRUEBA ENDIANS (https://es.wikipedia.org/wiki/Endianness)
    int16_t i = 1;
    int8_t* p = (int8_t*)&i;

    if (p[0] == 1) // equivalente a (*p == 1)
        printf("Little endian\n");
    else 
        printf("Big endian\n");

    int n = 1;
    // little endian if true
    if (*(char*)&n == 1)

        std::cout << "Little Endian de nuevo";


    // COSILLAS
    //Se puede declarar más de una variable en un bucle 'for' poniendo comas. Tienen que ser del mismo tipo.
    for (int i = 0, j = 3; i < 5; i++)
        std::cout << "algo ";
    std::cout << std::endl;

    // Sirve para reiniciar variables en bucles anidados por ejemplo
    float k = 0.0f;
    for(int i = 0; i<5; i++)
    {
        for (int j = 0, k = 0.0; j < 2; j++) // Se pone k a 0 en cada iteración de 'i' (5 veces)
        {
            k += 1; 
            // Hacer algo con k
            std::cout << k << " ";
        }
    }
}