#ifndef __KEPRI_TEXT__
#define __KEPRI_TEXT__

#include "GameObject.h"

static std::string FONTS_PATH = "../../bin/assets/fonts/";

struct SDL_Texture;
struct _TTF_Font;

/* GameObject usado para renderizar texto */
class Text : public GameObject
{
public: 
	/* Crea un texto con la fuente y el tamaño de fuente dados.
	La fuente deberá estar dentro de la carpeta 'fonts\'
	El color debe darse en hexadecimal, con 1 byte para cada canal (r,g,b,a) */
	Text(std::string message, std::string fontName, int size, uint32_t color = 0);

	// Heredados de GameObject
	void Draw();
	void Update();
	void Clean();

	// Setters
	/* Cambia el color del texto al color dado, 1 byte por canal (0xrrggbbaa) */
	void SetColor(uint32_t color);

	/* Cambia el contenido del texto */
	void SetText(std::string newText);

	/* Cambia el contenido del texto */
	void SetFontsize(int fontSize);

private:
	/* Cadena de caracteres que se está pintando */
	std::string m_text;

	/* Textura que muestra la cadena de texto */
	SDL_Texture* m_texture;

	/* Fuente que se está utilizando */
	_TTF_Font* m_pFont;

	/* Tamaño de la fuente usada */
	int m_fontSize;

	/* Color del texto, profundidad de 1 byte/canal */
	uint32_t m_color;

	// Métodod auxiliar para crear una nueva textura cuando el texto se actualiza
	void ChangeText(const char* newText);
};

#endif 