#ifndef __LOADERPARAMS__
#define __LOADERPARAMS__

#include <string>

/* Parámetros necesarios para la construcción de un GameObject */
class LoaderParams
{
public:
	/* Constructora */
	LoaderParams(int x, int y, int width, int height, int frameWidth, int frameHeight,
		std::string textureID, int numFrames = 1, int callbackID = 0, int animSpeed = 0) :
		m_x(x), m_y(y), m_width(width), m_height(height), m_frameWidth(frameWidth), m_frameHeight(frameHeight),
		m_textureID(textureID), m_numFrames(numFrames), m_callbackID(callbackID), m_animSpeed(animSpeed)
	{
	}

	/* Getters */
	int getX() const { return m_x; }
	int getY() const { return m_y; }

	int getWidth() const { return m_width; }
	int getHeight() const { return m_height; }

	int getFrameWidth() const { return m_frameWidth; }
	int getFrameHeight() const { return m_frameHeight; }

	int getNumFrames() const { return m_numFrames; }
	int getCallbackID() const { return m_callbackID; }
	int getAnimSpeed() const { return m_animSpeed; }

	std::string getTextureID() const { return m_textureID; }
private:
	// Nombre de la textura
	std::string m_textureID;

	// Posición
	int m_x;
	int m_y;

	// Tamaño
	int m_width;
	int m_height;

	// Tamaño, en píxeles, de cada frame de la textura
	int m_frameWidth;
	int m_frameHeight;

	// Número de frames y velocidad de la animación
	int m_numFrames;
	int m_animSpeed;

	// Callbacks (para botones)
	int m_callbackID;
};

#endif /* defined(__LoaderParams__) */