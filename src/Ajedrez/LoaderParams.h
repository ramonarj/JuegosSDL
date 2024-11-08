#ifndef __LOADERPARAMS__
#define __LOADERPARAMS__

#include <string>

/* Par�metros necesarios para la construcci�n de un GameObject */
class LoaderParams
{
public:
	/* Constructora */
	LoaderParams(int x, int y, int width, int height, std::string textureID, int numFrames = 1) : 
		m_x(x), m_y(y), m_width(width), m_height(height), m_textureID(textureID), m_numFrames(numFrames)
	{
	}

	/* Getters y setters */
	int getX() const { return m_x; }
	int getY() const { return m_y; }

	int getWidth() const { return m_width; }
	int getHeight() const { return m_height; }

	int getNumFrames() const { return m_numFrames; }

	std::string getTextureID() const { return m_textureID; }
private:
	// Posici�n
	int m_x;
	int m_y;

	// Tama�o
	int m_width;
	int m_height;

	// N�mero de frames
	int m_numFrames;

	// Nombre de la textura
	std::string m_textureID;
};

#endif /* defined(__LoaderParams__) */