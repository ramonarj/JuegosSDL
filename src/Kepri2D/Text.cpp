#include "Text.h"

#include "SDL.h"
#include "SDL_ttf.h"
#include "Game.h"
#include "InputHandler.h"

Text::Text(std::string message, std::string fontName, int size, uint32_t color) :
	m_text(message), m_fontSize(size), m_color(color), m_texture(nullptr)
{
	// Creamos la fuente que vamos a usar para el texto
	m_pFont = TTF_OpenFont((FONTS_PATH + fontName).c_str(), size);

	// Función privada para crear la textura que contendrá nuestro texto
	ChangeText(message.c_str());
}

void Text::Draw()
{
	// Posición en la que se pinta
	SDL_Rect destRect = { (int)m_position.GetX(), (int)m_position.GetY(), m_width, m_height };
	SDL_RenderCopy(Game::Instance()->GetRenderer(), m_texture, NULL, &destRect); 
	//NULL porque se coge toda la textura
}

void Text::Update()
{
	// Con el clic derecho, asignamos un color aleatorio al texto (con alfa=max)
	if(InputHandler::Instance()->GetMouseButtonState(RIGHT))
	{
		m_color = ((float)std::rand() / RAND_MAX) * 0xffffffff;
		m_color ^= 0x000000ff; //para cargarnos el alfa
		std::cout << m_color << std::endl;
		SetColor(m_color);
	}
	
	// Con la barra espaciadora pulsada, variamos la intensidad del canal alfa
	if (InputHandler::Instance()->IsKeyDown(SDL_SCANCODE_SPACE))
	{
		m_alpha = (std::sin(Game::Instance()->GetTicks() / 300.0f) + 1) / 2 * 255;
		m_color = m_color - (m_color << 24 >> 24) + m_alpha; //un poco cutre

		SDL_SetTextureAlphaMod(m_texture, Uint8(m_color));
	}

	// Con la tecla '0', el texto cambia aleatoriamente a uno de estas palabras
	std::vector<const char*> frutas {"Kepri2D", "plátano", "manzana", "ananas", "pera", "guayaba", "melocoton", "ñoqui"};
	if(InputHandler::Instance()->IsKeyDown(SDL_SCANCODE_0))
	{
		int fruta = ((float)std::rand() / RAND_MAX) * frutas.size();
		SetText(frutas[fruta]);
	}

	// Con las flechas de dirección, aumenta/disminuye el tamaño de la fuente
	// (también hay que volver a cambiar la textura)
	if (InputHandler::Instance()->IsKeyDown(SDL_SCANCODE_UP))
	{
		SetFontsize(m_fontSize + 1);
	}
	if (InputHandler::Instance()->IsKeyDown(SDL_SCANCODE_DOWN))
	{
		SetFontsize(m_fontSize - 1);
	}
}

void Text::Clean()
{
	TTF_CloseFont(m_pFont);
}

void Text::SetColor(uint32_t color)
{
	m_color = color;
	SDL_SetTextureColorMod(m_texture, Uint8(color >> 24), Uint8(color >> 16), Uint8(color >> 8));
}

void Text::SetText(std::string text)
{
	// Cada vez que se cambia el texto hay que crear una nueva superficie y textura
	m_text = text;
	ChangeText(text.c_str());
}

void Text::SetFontsize(int fontSize)
{
	// Igual que en "SetText"
	m_fontSize = fontSize;
	TTF_SetFontSize(m_pFont, fontSize);
	ChangeText(m_text.c_str());
}

void Text::ChangeText(const char* newText)
{
	/* El color con el que vamos a crear la textura va a ser siempre blanco,
	 para que luego si queremos cambiar el color del texto, nos valga con llamar a
	 SDL_...colorMod */
	SDL_Color sdlColor = { 0xff, 0xff, 0xff, SDL_ALPHA_OPAQUE };

	// Surface temporal. Las dimensiones del GameObject se ajustan a lo que ocupe la 'surface' en píxeles
	SDL_Surface* pTempSurface = TTF_RenderText_Solid(m_pFont, newText, sdlColor);
	m_width = pTempSurface->w;
	m_height = pTempSurface->h;

	// Textura que se pintará (y su color), liberamos la surface
	m_texture = SDL_CreateTextureFromSurface(Game::Instance()->GetRenderer(), pTempSurface);
	SDL_SetTextureColorMod(m_texture, Uint8(m_color >> 24), Uint8(m_color >> 16), Uint8(m_color >> 8));
	SDL_SetTextureAlphaMod(m_texture, Uint8(m_color));

	SDL_FreeSurface(pTempSurface);
}