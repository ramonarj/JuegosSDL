#include "CollisionManager.h"

#include "Collision.h"
#include "Game.h"

void CollisionManager::SetCollidableObject(GameObject* g, bool collidable)
{
	auto it = std::find(m_collidableObjects.begin(), m_collidableObjects.end(), g);
	// El elemento ya estaba en la lista
	if (it != m_collidableObjects.end())
	{
		// Lo quitamos
		if (!collidable)
		{
			m_collidableObjects.erase(it);
		}
	}
	//No estaba en la lista
	else if (collidable)
		m_collidableObjects.push_back(g);
}

void CollisionManager::Update()
{
	auto it1 = m_collidableObjects.begin();
	// Iteramos todas las posibles combinaciones de GameObjects, 
	// sin repetir casos
	while(it1 != m_collidableObjects.end())
	{
		auto it2 = it1;
		it2++;
		/// Empezamos desde el anterior
		while(it2 != m_collidableObjects.end())
		{
			if (it1 != it2)
			{
				SDL_Rect r1 = { (*it1)->GetPosition().GetX(), (*it1)->GetPosition().GetY(), (*it1)->GetWidth(), (*it1)->GetHeight() };
				SDL_Rect r2 = { (*it2)->GetPosition().GetX(), (*it2)->GetPosition().GetY(), (*it2)->GetWidth(), (*it2)->GetHeight() };
				if (RectRect(&r1, &r2))
				{
					(*it1)->OnCollision((*it2));
					(*it2)->OnCollision((*it1));
				}
			}
			it2++;
		}
		it1++;
	}
}

void CollisionManager::Render()
{
	if (!m_visibleColliders)
		return;

	// Guardar el antiguo color y ponerlo a verde
	SDL_Color defColor;
	SDL_GetRenderDrawColor(Game::Instance()->GetRenderer(), &defColor.r, &defColor.g, &defColor.b, &defColor.a);

	SDL_SetRenderDrawColor(Game::Instance()->GetRenderer(), 0, 255, 0, 255);

	// Pintar los colliders
	for(GameObject* go : m_collidableObjects)
	{
		int posX = go->GetPosition().GetX();
		int posY = go->GetPosition().GetY();

		// Son 4 líneas
		//SDL_RenderDrawLine(Game::Instance()->GetRenderer(), 
		//	posX, posY, posX, posY + go->GetHeight());
		//SDL_RenderDrawLine(Game::Instance()->GetRenderer(), 
		//	posX, posY, posX + go->GetWidth(), posY);
		//SDL_RenderDrawLine(Game::Instance()->GetRenderer(), 
		//	posX, posY + go->GetHeight(), posX + go->GetWidth(), posY + go->GetHeight());
		//SDL_RenderDrawLine(Game::Instance()->GetRenderer(), 
		//	posX + go->GetWidth(), posY, posX + go->GetWidth(), posY + go->GetHeight());
		
		// Se podría hacer llamando 4 veces a SDL_RenderDrawLine; esta otra opción usa 5 puntos y los une
		const SDL_Point points[5] = { {posX, posY}, {posX + go->GetWidth(), posY}, 
			{posX + go->GetWidth(), posY + go->GetHeight()}, {posX, posY + go->GetHeight()}, {posX, posY} };
		SDL_RenderDrawLines(Game::Instance()->GetRenderer(), points, 5);
	}

	// Volver a su color original
	SDL_SetRenderDrawColor(Game::Instance()->GetRenderer(), defColor.r, defColor.g, defColor.a, 255);
}