#ifndef FRUSTUM_H
#define FRUSTUM_H

#include <glew.h>
#include <gl/GL.h>
#include <gl/GLU.h>

enum PlaneData
{
	A = 0,		// The X value of the plane's normal
	B = 1,		// The Y value of the plane's normal
	C = 2,		// The Z value of the plane's normal
	D = 3		// The distance the plane is from the origin
};

enum FrustumSide
{
	RIGHT = 0,		// The RIGHT side of the frustum
	LEFT = 1,		// The LEFT	 side of the frustum
	BOTTOM = 2,		// The BOTTOM side of the frustum
	TOP = 3,		// The TOP side of the frustum
	BACK = 4,		// The BACK	side of the frustum
	FRONT = 5		// The FRONT side of the frustum
};

class Frustum
{
public:
	Frustum();
	~Frustum();


};

#endif // !FRUSTUM_H
