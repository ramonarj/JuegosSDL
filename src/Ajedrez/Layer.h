#ifndef __LAYER__
#define __LAYER__

/* Clase abstracta para las capas del juego */
class Layer
{
public:
	// M�todos b�sicos
	virtual void Render() = 0;
	virtual void Update() = 0;
protected:
	virtual ~Layer() {}
};

#endif /* defined(__Layer__) */