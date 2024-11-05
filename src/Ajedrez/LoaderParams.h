#ifndef __LOADERPARAMS__
#define __LOADERPARAMS__

#include <string>

/* Parámetros necesarios para la construcción de un GameObject */
class LoaderParams
{
public:
	/* Constructora */
	LoaderParams(int x, int y, int width, int height, std::string textureID) : 
		m_x(x), m_y(y), m_width(width), m_height(height), m_textureID(textureID)
	{
	}

	/* Getters y setters */
	int getX() const { return m_x; }
	int getY() const { return m_y; }

	int getWidth() const { return m_width; }
	int getHeight() const { return m_height; }

	std::string getTextureID() const { return m_textureID; }
private:
	// Posición
	int m_x;
	int m_y;

	// Tamaño
	int m_width;
	int m_height;

	// Nombre de la textura
	std::string m_textureID;
};

#endif /* defined(__TextureManager__) */