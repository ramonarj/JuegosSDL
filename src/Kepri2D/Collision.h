#ifndef __COLLISION__
#define __COLLISION__

#include "SDL.h"

// Modificador para que los colliders sean m�s peque�os
// Cuanto m�s alto este n�mero, m�s realista la colisi�n (menos "justa")
const static int s_buffer = 50;

/* Colisi�n tipo AABB, de cajas */
static bool RectRect(SDL_Rect* A, SDL_Rect* B)
{
	// Hacemos los rect�ngulos un poco m�s peque�os, de acuerdo al buffer
	int aHBuf = A->h / s_buffer;
	int aWBuf = A->w / s_buffer;
	int bHBuf = B->h / s_buffer;
	int bWBuf = B->w / s_buffer;

	// if the bottom of A is less than the top of B - no collision
	if ((A->y + A->h) - aHBuf <= B->y + bHBuf) { return false; }
	// if the top of A is more than the bottom of B = no collision
	if (A->y + aHBuf >= (B->y + B->h) - bHBuf) { return false; }
	// if the right of A is less than the left of B - no collision
	if ((A->x + A->w) - aWBuf <= B->x + bWBuf) { return false; }
	// if the left of A is more than the right of B - no collision
	if (A->x + aWBuf >= (B->x + B->w) - bWBuf) { return false; }

	// otherwise there has been a collision
	return true;
}

#endif /* defined(__Collision__) */