#ifndef __KEPRI_TEXT__
#define __KEPRI_TEXT__

#include "CanvasObject.h"
#include "GameObjectFactory.h"

static std::string FONTS_PATH = "../../bin/assets/fonts/";

struct SDL_Texture;
struct _TTF_Font;

/* GameObject usado para renderizar texto */
class Text : public CanvasObject
{
public: 
	/* Constructora por defecto */
	Text() : CanvasObject(), m_pFont(nullptr), m_fontSize(0), m_color(0), m_texture(nullptr) {}


	// Heredados de GameObject
	void Load(const LoaderParams* pParams) override;

	void Draw() override;
	void Update() override;
	void Clean() override;

	// Obligado
	virtual std::string Type() const override{ return "Text"; }

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

class TextCreator : public BaseCreator
{
	GameObject* CreateGameObject() const override
	{
		return new Text();
	}
};

#endif /* defined(__Text__) */