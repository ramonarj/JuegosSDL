#include "CollisionManager.h"

#include "Collision.h"

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
	auto it2 = it1;
	it2++;
	// Iteramos todas las posibles combinaciones de GameObjects, 
	// sin repetir casos
	while(it1 != m_collidableObjects.end())
	{
		/// Empezamos desde el anterior
		while(it2 != m_collidableObjects.end())
		{
			if (it1 != it2)
			{
				SDL_Rect r1 = { (*it1)->GetPosition().GetX(), (*it1)->GetPosition().GetY(), (*it1)->GetWidth(), (*it1)->GetHeight() };
				SDL_Rect r2 = { (*it2)->GetPosition().GetX(), (*it2)->GetPosition().GetY(), (*it2)->GetWidth(), (*it2)->GetHeight() };
				if (RectRect(&r1, &r2))
				{
					std::cout << "Colisión entre GameObjects\n";
				}
			}
			it2++;
		}
		it1++;
		it2 = it1;
		it2++;
	}
}