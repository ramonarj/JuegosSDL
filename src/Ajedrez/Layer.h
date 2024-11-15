#ifndef __LAYER__
#define __LAYER__

/* Clase abstracta para las capas del juego */
class Layer
{
public:
	// Destructora virtual
	virtual ~Layer(){}

	// Métodos básicos
	virtual void Render() = 0;
	virtual void Update() = 0;
};

#endif /* defined(__Layer__) */