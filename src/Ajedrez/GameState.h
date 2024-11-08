#ifndef __GAMESTATE__
#define __GAMESTATE__

#include <string>
#include <vector>

/* Clase abstracta, igual que GameObject, para un estado de juego */
class GameState
{
public:
	virtual void Update() = 0;
	virtual void Render() = 0;

	virtual bool OnEnter() = 0;
	virtual bool OnExit() = 0;

	virtual std::string GetStateID() const = 0;

protected:
	/* Lista de IDs de texturas */
	std::vector<std::string> m_textureIDList;
};


#endif /* defined(__GameState__) */