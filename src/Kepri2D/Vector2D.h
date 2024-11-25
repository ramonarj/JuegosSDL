#ifndef __VECTOR2D__
#define __VECTOR2D__

#include <cmath>
#include <string>
#include <iostream>

class Vector2D
{
public:
	/* Constructoras */
	Vector2D() : m_x(0), m_y(0){}
	Vector2D(float x, float y) : m_x(x), m_y(y) {}

	/* Módulo del vector */
	inline float Length() { return sqrt(m_x * m_x + m_y * m_y); }

	/* Getters y setters */
	inline float GetX() const{ return m_x; }
	inline float GetY() const{ return m_y; }

	inline void SetX(float x) { m_x = x; }
	inline void SetY(float y) { m_y = y; }

	/* Normalizar un vector */
	void Normalize()
	{
		float l = Length();
		if (l > 0) // we never want to attempt to divide by 0
		{
			(*this) *= 1 / l;
		}
	}


	/* OPERADORES */
	/* Suma de vectores*/
	inline Vector2D operator+(const Vector2D& v2) const
	{
		return Vector2D(m_x + v2.m_x, m_y + v2.m_y);
	}

	inline friend Vector2D& operator+=(Vector2D& v1, const Vector2D& v2)
	{
		v1.m_x += v2.m_x;
		v1.m_y += v2.m_y;
		return v1;
	}

	/* Resta de vectores */
	inline Vector2D operator-(const Vector2D& v2)
	{
		return Vector2D(m_x - v2.m_x, m_y - v2.m_y);
	}

	inline friend Vector2D& operator-=(Vector2D& v1, const Vector2D& v2)
	{
		v1.m_x -= v2.m_x;
		v1.m_y -= v2.m_y;
		return v1;
	}

	/* Producto por un escalar */
	inline Vector2D operator*(float scalar)
	{
		return Vector2D(m_x * scalar, m_y * scalar);
	}

	inline Vector2D& operator*=(float scalar)
	{
		m_x *= scalar;
		m_y *= scalar;
		return *this;
	}

	/* División por un escalar */
	inline Vector2D operator/(float scalar)
	{
		return Vector2D(m_x / scalar, m_y / scalar);
	}

	inline Vector2D& operator/=(float scalar)
	{
		m_x /= scalar;
		m_y /= scalar;
		return *this;
	}

	/* Multiplicación elemento por elemento */
	inline Vector2D operator*(const Vector2D& v2) const
	{
		return Vector2D(m_x * v2.m_x, m_y * v2.m_y);
	}

	inline friend Vector2D& operator*=(Vector2D& v1, const Vector2D& v2)
	{
		v1.m_x *= v2.m_x;
		v1.m_y *= v2.m_y;
		return v1;
	}

	// Sobrecarga del operador de extracción (para debug)
	friend std::ostream& operator<<(std::ostream& os, Vector2D const& v)
	{
		return os << "{" << v.m_x << ", " << v.m_y << "}";
	}

private:
	float m_x;
	float m_y;
};



#endif  /* defined(__Vector2D__) */