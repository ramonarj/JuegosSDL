#ifndef __MENUBUTTON__
#define __MENUBUTTON__

#include "CanvasObject.h"
#include "GameObjectFactory.h"

class MenuButton : public CanvasObject
{
public:
	/* Constructora por defecto */
	MenuButton() : m_callback(nullptr), m_bReleased(false), m_callbackID(0){}
	void Load(const LoaderParams* pParams);

	// Heredadas
	virtual void Update();

	// Obligado
	virtual std::string Type() const { return "MenuButton"; }

	/* Getter */
	int GetCallbackID() { return m_callbackID; }

	/* Establece la funci�n a la que llamar */
	void SetCallback(void(*callback)()) { m_callback = callback; }

private:
	enum button_state
	{
		MOUSE_OUT = 0,
		MOUSE_OVER = 1,
		CLICKED = 2
	};

	/* Puntero a la funci�n que se llamar� al clicarlo */
	void (*m_callback)();
	/* Identificador que le llega de archivo */
	int m_callbackID;

	/* Para el clic del rat�n */
	bool m_bReleased;
};

class MenuButtonCreator : public BaseCreator
{
	GameObject* CreateGameObject() const
	{
		return new MenuButton();
	}
};

#endif /* defined(__MenuButton__) */