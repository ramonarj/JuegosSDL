#include "Text.h"

#include "SDL.h"
#include "SDL_ttf.h"
#include "Game.h"
#include "InputHandler.h"
#include "Camera.h"


void Text::Load(const LoaderParams* pParams)
{
	/* Crea un texto con la fuente y el tamaño de fuente dados.
	La fuente deberá estar dentro de la carpeta 'fonts\'
	El color debe darse en hexadecimal, con 1 byte para cada canal (r,g,b,a) */
	GameObject::Load(pParams);

	// Cogemos de LoaderParams
	m_text = pParams->getText();
	m_fontSize = pParams->getFontSize();
	std::string fontName = pParams->getFont();
	m_color = pParams->getTextColor();


	// Creamos la fuente que vamos a usar para el texto
	m_pFont = TTF_OpenFont((FONTS_PATH + fontName).c_str(), m_fontSize);

	// Función privada para crear la textura que contendrá nuestro texto
	ChangeText(m_text.c_str());
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
	if(InputHandler::Instance()->GetMouseButtonDown(RIGHT))
	{
		m_color = ((float)std::rand() / RAND_MAX) * 0xffffffff;
		m_color ^= 0x000000ff; //para cargarnos el alfa
		SetColor(m_color);
	}
	
	// Con la barra espaciadora pulsada, variamos la intensidad del canal alfa
	if (InputHandler::Instance()->GetKey(SDL_SCANCODE_SPACE))
	{
		m_alpha = (std::sin(Game::Instance()->GetTicks() / 300.0f) + 1) / 2 * 255;
		m_color = m_color - (m_color << 24 >> 24) + m_alpha; //un poco cutre

		SDL_SetTextureAlphaMod(m_texture, Uint8(m_color));
	}

	// Con la tecla '0', el texto cambia aleatoriamente a uno de estas palabras
	std::vector<const char*> frutas {"Kepri2D", "plátano", "manzana", "ananas", "pera", "guayaba", "melocoton", "ñoqui"};
	if(InputHandler::Instance()->GetKeyDown(SDL_SCANCODE_0))
	{
		int fruta = ((float)std::rand() / RAND_MAX) * frutas.size();
		SetText(frutas[fruta]);
	}

	// Con las flechas de dirección, aumenta/disminuye el tamaño de la fuente
	// (también hay que volver a cambiar la textura)
	if (InputHandler::Instance()->GetKey(SDL_SCANCODE_UP))
	{
		Camera::Instance()->SetPosition(Camera::Instance()->GetPosition() + Vector2D(0, -1));
	}
	if (InputHandler::Instance()->GetKey(SDL_SCANCODE_DOWN))
	{
		Camera::Instance()->SetPosition(Camera::Instance()->GetPosition() + Vector2D(0, 1));
	}
	if (InputHandler::Instance()->GetKey(SDL_SCANCODE_LEFT))
	{
		Camera::Instance()->SetPosition(Camera::Instance()->GetPosition() + Vector2D(-1, 0));
	}
	if (InputHandler::Instance()->GetKey(SDL_SCANCODE_RIGHT))
	{
		Camera::Instance()->SetPosition(Camera::Instance()->GetPosition() + Vector2D(1, 0));
	}
	//if (InputHandler::Instance()->GetKeyUp(SDL_SCANCODE_UP))
	//{
	//	SetFontsize(50);
	//}
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