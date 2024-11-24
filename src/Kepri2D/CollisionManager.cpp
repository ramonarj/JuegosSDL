#include "CollisionManager.h"

#include "Collision.h"
#include "Game.h"
#include "TileLayer.h"
#include "Camera.h"

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

void CollisionManager::SetCollidableLayer(TileLayer* layer, bool collidable)
{
	auto it = std::find(m_collidableLayers.begin(), m_collidableLayers.end(), layer);
	// El elemento ya estaba en la lista
	if (it != m_collidableLayers.end())
	{
		// Lo quitamos
		if (!collidable)
		{
			m_collidableLayers.erase(it);
		}
	}
	//No estaba en la lista
	else if (collidable)
		m_collidableLayers.push_back(layer);
}

void CollisionManager::Update()
{
	// Colisiones entre GameObjects
	ObjectObjectCollisions();

	// Colisiones de una GameObject con una capa de tiles colisionable
	ObjectLayerCollisions();
}

void CollisionManager::Render()
{
	if (!m_visibleColliders)
		return;

	// Guardar el antiguo color y ponerlo a verde
	SDL_Color defColor;
	SDL_GetRenderDrawColor(Game::Instance()->GetRenderer(), &defColor.r, &defColor.g, &defColor.b, &defColor.a);

	SDL_SetRenderDrawColor(Game::Instance()->GetRenderer(), 0, 255, 0, 255);

	// Pintar los colliders de los objetos
	for (GameObject* go : m_collidableObjects)
	{
		//int posX = (int)go->GetPosition().GetX();
		//int posY = (int)go->GetPosition().GetY();
		Vector2D screenPos = Camera::Instance()->WorldToScreen(go->GetPosition());
		int posX = screenPos.GetX();
		int posY = screenPos.GetY();

		// Se podría hacer llamando 4 veces a SDL_RenderDrawLine; esta otra opción usa 5 puntos y los une
		// (el primer y último punto son iguales)
		const SDL_Point points[5] = { {posX, posY}, {posX + go->GetWidth(), posY},
			{posX + go->GetWidth(), posY + go->GetHeight()}, {posX, posY + go->GetHeight()}, {posX, posY} };
		SDL_RenderDrawLines(Game::Instance()->GetRenderer(), points, 5);
	}

	// Pintar los colliders de las capas de tiles con colisiones
	for (TileLayer* layer : m_collidableLayers)
	{
		// Datos de la capa y tamaño de los tiles
		std::vector<std::vector<int>> data = layer->GetTileIDs();
		int tileSize = layer->GetTileSize();
		for (int i = 0; i < data.size(); i++)
		{
			for (int j = 0; j < data.at(0).size(); j++)
			{
				// Si hay tile, dibujamos una cajita a su alrededor
				if (data[i][j] != 0)
				{
					Vector2D screenPos = Camera::Instance()->WorldToScreen(Vector2D(j * tileSize, i * tileSize));
					SDL_Rect rect = { screenPos.GetX(), screenPos.GetY(), tileSize, tileSize};
					SDL_RenderDrawRect(Game::Instance()->GetRenderer(), &rect);
				}
			}
		}
	}

	// Volver a su color original
	SDL_SetRenderDrawColor(Game::Instance()->GetRenderer(), defColor.r, defColor.g, defColor.b, defColor.a);
}

void CollisionManager::ObjectObjectCollisions()
{
	auto it1 = m_collidableObjects.begin();
	// Iteramos todas las posibles combinaciones de GameObjects, 
	// sin repetir casos
	while (it1 != m_collidableObjects.end())
	{
		auto it2 = it1;
		it2++;
		/// Empezamos desde el siguiente
		while (it2 != m_collidableObjects.end())
		{
			if (it1 != it2)
			{
				SDL_Rect r1 = { (int)(*it1)->GetPosition().GetX(), (int)(*it1)->GetPosition().GetY(),
					(int)(*it1)->GetWidth(), (int)(*it1)->GetHeight() };
				SDL_Rect r2 = { (int)(*it2)->GetPosition().GetX(), (int)(*it2)->GetPosition().GetY(),
					(*it2)->GetWidth(), (*it2)->GetHeight() };
				if (RectRect(&r1, &r2)) //hay colisión
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

void CollisionManager::ObjectLayerCollisions()
{
	Vector2D cameraPos = Camera::Instance()->GetPosition();
	int windowWidth = Game::Instance()->GetGameWidth();
	int windowHeight = Game::Instance()->GetGameHeight();

	auto objIt = m_collidableObjects.begin();
	while (objIt != m_collidableObjects.end())
	{
		auto layIt = m_collidableLayers.begin();
		while (layIt != m_collidableLayers.end())
		{
			// Solo comprobamos las colisiones de los tiles que están siendo 'enfocados'
			// por la cámara
			std::vector<std::vector<int>> data = (*layIt)->GetTileIDs();
			int tileSize = (*layIt)->GetTileSize();

			int firstTileX = int(cameraPos.GetX() - windowWidth / 2) / tileSize;
			int firstTileY = int(cameraPos.GetY() - windowHeight / 2) / tileSize;
			// Recorremos cada tile visible y vemos si choca con el GameObject dado
			for (int i = firstTileX; i < firstTileX + 20; i++)
			{
				if (i < 0 || i >= 60)
					continue;
				for (int j = firstTileY; j < firstTileY + 15; j++)
				{
					if (j < 0 || j >= 15)
						continue;
					// Comprobamos que haya tile
					if (data[j][i] != 0)
					{
						SDL_Rect rObj = { (int)(*objIt)->GetPosition().GetX(), (int)(*objIt)->GetPosition().GetY(),
							(*objIt)->GetWidth(), (*objIt)->GetHeight() };
						SDL_Rect rTile = { i * tileSize, j * tileSize, tileSize, tileSize };
						if (RectRect(&rObj, &rTile)) // hay colisión
							std::cout << "Colisión de " << (*objIt)->Type() << " con capa de tiles\n";
					}
				}
			}

			layIt++;
		}
		objIt++;
	}
}