#ifndef __LOADERPARAMS__
#define __LOADERPARAMS__

#include <string>

/* Parámetros necesarios para la construcción de un GameObject */
class LoaderParams
{
public:
	/* Constructora */
	LoaderParams(int x, int y, int width, int height, int frameWidth, int frameHeight,
		std::string textureID, int numFrames = 1, int callbackID = 0, int animSpeed = 0, 
		std::string text = "", std::string font = "", int fontSize = 0, uint32_t textColor = 0) :
		m_x(x), m_y(y), m_width(width), m_height(height), m_frameWidth(frameWidth), m_frameHeight(frameHeight),
		m_textureID(textureID), m_numFrames(numFrames), m_callbackID(callbackID), m_animSpeed(animSpeed), 
		m_text(text), m_font(font), m_fontSize(fontSize), m_textColor(textColor)
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

	// Para textos
	std::string getText() const { return m_text; }
	std::string getFont() const { return m_font; }
	int getFontSize() const { return m_fontSize; }
	uint32_t getTextColor() const { return m_textColor; }
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

	// Texto (para clase Text)
	std::string m_text;
	std::string m_font;
	int m_fontSize;
	int m_textColor;
};

#endif /* defined(__LoaderParams__) */