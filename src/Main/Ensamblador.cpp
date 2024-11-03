#include <iostream>
#include "../RamonLib/Utiles.h"

void SaltoASM()
{
    std::cout << "Vengo del branch and link" << std::endl;
}


void PruebaEnsamblador()
{
#ifndef _WIN64
    // Se puede insertar código ENSAMBLADOR directamente con "asm" 
    // (solo en arquitecturas de 32 bits, por eso el uso de la macro)

    short a = 3; // si lo declaro int, da fallo en la multiplicación
    short b = 32;

    bool iguales = 0;
    // Prueba de desplazamientos, multiplicacion y salto condicional
    __asm
    {
        // Da igual minúsculas que mayúsculas
        MOV a, 10
        SUB a, 1 // 9
        SHR a, 1 // (shift right) 4
        SHL a, 1 // (shift left) 8 porque me he cargado el bit

        mov ax, 4
        mul a // 32. 'mul' multiplica lo que haya en eax por el operando especificado
        mov a, ax


        mov bx, b
        cmp ax, bx // ax y bx, por lo que se ve, son registros de propósito general de 16 bits
        je IGUALES // (JE = Jump if Equal = BEQ en arm), (JNE = Jump if Not Equal == BNE en arm)

        mov iguales, 0
        jmp FIN // Jump

        IGUALES :
        mov iguales, 1

            FIN :
    }

    //NOMBRE_VALOR(ax); // Error; el código ensamblador puede acceder a las variables de C++ pero no viceversa
    NOMBRE_VALOR(a);
    NOMBRE_VALOR(iguales);

    int c = 9;
    int d;
    int resto;
    // Ej: eleva 'c' al cuadrado y lo divide por 38
    __asm
    {
        // ERROR: el ensamblado insertado en C++ no permite declarar variables (tipo DB, DW, DD) ni la etiqueta .DATA
        // Las variables que haya que usar se cogen de fuera (del propio código en C++)
        //.DATA
        //divisor dd 38

        mov eax, c // eax y ebx también son de propósito general, pero de 32 bits
        mov ebx, d

        mul eax // 81 (9 al cuadrado)
        mov c, eax

        mov ebx, 38
        //'idiv' hace división entera de eax/operando especificado. El cociente lo guarda en eax y el resto en edx
        idiv ebx // 27 (81/3).  
        mov c, eax
        mov resto, edx

        cmp eax, ebx
        // Podemos hacer alusión a etiquetas escritas en un bloque "__asm" distinto
        //jmp FIN // En este caso crearíamos un bucle infinito y no saldríamos nunca de esta función
    }
    NOMBRE_VALOR(c);
    //Utiles::ImprimeHex(c);
    NOMBRE_VALOR(resto);
    std::cout << std::endl;


    // Prueba de rotaciones, loads y stores (MOV)
    int entero = 7;
    int* punteroInt = &entero;
    unsigned char byteNum = 1;
    __asm
    {
        rol byteNum, 1 // 2
        ror byteNum, 2 // 128 (2^7)

        // Hacer el inverso de 128 
        not byteNum // 127
        // Otra forma de hacer el inverso (con una XOR). 
        // Se puede poner en decimal (255) o en hexadecimal (0xff)
        xor byteNum, 0xff

        // En x86 no hay ni 'ldr' ni 'str', solo mov
        // Cuando usamos los corchetes [], estamos tratando los contenidos del registro como una dirección
        // de memoria en lugar de una variable común.
        // Ej1: (BR -> BR) sin corchetes, copia el valor de 'entero' y lo pega en el registro 'ebx'
        mov ebx, entero
        mov entero, ebx
        and ebx, 0 //Limpiamos

        // Ej2: (MEM -> BR) con corchete en la derecha, copia el valor contenido en la dirección de memoria 
        //'punteroInt' y lo pega en el registro 'ebx'
        mov eax, punteroInt
        mov ebx, [eax]
        mov entero, ebx //creo que hay una forma mejor de hacerlo
        //mov entero, 3

        //Ej3: (BR -> MEM) con corchete en la izquierda, copia el valor de 'INT_MAX' y lo guarda en la dirección 
        // contenida en 'ebx = punteroInt'
        mov eax, entero
        mov ebx, punteroInt
        mov dword ptr[ebx], INT_MAX // Para mover más de 1 byte, hay que usar los modificadores:
        // byte ptr (1 byte), word ptr (2 bytes), dword ptr (4 bytes)

        //"Ej4": (MEM -> MEM) no existe, x86 no permite mover directamente valores en memoria
        // Hay que pasarlo primero por el BR
    }
    NOMBRE_VALOR((int)byteNum);
    Utiles::ImprimeBinario(byteNum);
    std::cout << std::endl;
    NOMBRE_VALOR(entero);
    NOMBRE_VALOR(*punteroInt);



    // Prueba de llamada a funciones, LEA, BT 
    std::cout << "\n";

    // Otro entero de prueba, esta vez en el 'heap'
    entero = 14;
    int* punteroInt2 = new int(-2);
    int entero2 = *punteroInt2;
    bool hayBit = false;
    __asm
    {
        // En x86, los registros se guardan/sacan de la pila con 'PUSH' y 'POP', para llamadas a funciones,
        // en vez de usar LDR y STR jugando con el Stack Pointer (ESP) como en ARM (SP)
        // Los branch-and-link se hacen con la instrucción 'CALL'

        //jmp SaltoASM // Si hago esto, da infracción de acceso en el main (el programa no sabe por donde seguir)
        call SaltoASM

        // lea = Load Effective Address; carga en el registro la dirección dada (para tener un puntero)
        // Intercambiamos los punteros (sería como hacer punteroInt2 = &entero; punteroInt = &entero2;)
        lea edx, entero
        mov punteroInt2, edx
        lea edx, entero2
        mov punteroInt, edx

        mov al, 7
        bt al, 0 //Bit-test; compara si hay un 1 en la posición dada y almacena el resultado en el flag de CARRY (CF)
        jc hay // Jump-if-Carry (salta si el flag de carry está a 1)
        jmp FINAL
        HAY :
        mov hayBit, 1
            FINAL :
    }
    std::cout << "Sigo en pruebaASM\n";
    NOMBRE_VALOR_MEMORIA(entero);
    NOMBRE_VALOR(*punteroInt);
    NOMBRE_VALOR(entero2);
    NOMBRE_VALOR_MEMORIA(punteroInt2);

    std::cout << std::endl;
    NOMBRE_VALOR(hayBit); // true

#endif
}