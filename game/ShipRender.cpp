#include "ShipRender.h"
#include "sfwdraw.h"
#include "shapedraw.h"
#include "Collider.h"

using namespace sfw;

ShipRender::ShipRender(unsigned inColor, float inSize)
{
	color = inColor;
	size = inSize;
}


ShipRender::~ShipRender()
{
}

void ShipRender::draw(const Transform & t, const mat3 & camera)
{
	mat3 glob = t.getGlobalTransform();

	mat3 l = camera * glob;

	
	vec2 pos = l.c[2].xy;

	vec3 point1 = (l *  (vec3 {  0,  7 ,1} * size));
	vec3 point2 = (l *  (vec3 {  4, -7 ,1} * size));
	vec3 point3 = (l *  (vec3 { -4, -7 ,1} * size));
	vec3 point4 = (l *  (vec3 {  0, -5, 1} * size));

	drawLine(point1.x, point1.y, point2.x, point2.y, color);
	drawLine(point1.x, point1.y, point3.x, point3.y, color);
	drawLine(point2.x, point2.y, point4.x, point4.y, color);
	drawLine(point3.x, point3.y, point4.x, point4.y, color);

	vec3 F1 = l * vec3{ -4,-7,  1} *size;
	vec3 L1 = l * vec3{ -4, 7,  1 }*size;
	vec3 R1 = l * vec3{ 4, -7,  1 }*size;
	vec3 B1 = l * vec3{ 4, 7,  1 }*size;

	

	vec2 stuff[4] = { F1.xy, L1.xy, R1.xy, B1.xy };

	
	Collider playerCollider(stuff, size);
	playerCollider.DebugDraw(camera, t);


}
