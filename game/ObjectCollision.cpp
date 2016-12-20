#include "ObjectCollision.h"
#include "flops.h"

void PlayerAsteroidCollision(PlayerShip & player, Asteroid & as)
{
	CollisionData out = DynamicResolution(player.transform, player.rigidbody, player.collider,
		as.transform, as.rigidbody, as.collider);

	
}

void AsteroidCollision(Asteroid & a1, Asteroid & a2)
{
	DynamicResolution(a1.transform, a1.rigidbody, a1.collider,
					  a2.transform, a2.rigidbody, a2.collider);
}

void PlayerBallCollision(PlayerShip & player, PlayerBall & ball)
{
	DynamicResolution(player.transform, player.rigidbody, player.collider,
					  ball.transform, ball.rigidbody, ball.collider);
}

void BallCollision(PlayerBall & b1, PlayerBall & b2)
{
	
}

bool BallPointCollision(PlayerBall & ball, CaptureBall & p)
{
	CollisionData out = ColliderCollision(ball.transform, ball.collider, p.transform, p.collider);

	if (out.penDepth >= 0)
	{
		p.team = ball.team;
		return true;
	}
	return false;
}


void BoundCollision(Transform &trans, RigidBody & rigid, Collider &col, Boundary & bound, float bounciness)
{
	

	CollisionData data;


	data = boxCollision(trans.getGlobalTransform() * col.box,
		bound.collider.box);


	if (data.penDepth >= 0)
		data = HullCollision(trans.getGlobalTransform() * col.hull,
			bound.collider.hull);

	if (data.penDepth >= 0)
	{
		vec2 mtv = data.penDepth * data.colNormal;
		trans.pos -= mtv;

		rigid.velocity = reflect(rigid.velocity, data.colNormal) * bounciness;
	}
}


void BoundCollision(PlayerShip & obj, Boundary & bound, float bounciness)
{
	CollisionData data;

	
	data = boxCollision(obj.transform.getGlobalTransform() * obj.collider.box,
		bound.collider.box);

	if (data.penDepth >= 0)
		data = HullCollision(obj.transform.getGlobalTransform() * obj.collider.hull,
			bound.collider.hull);

	if (data.penDepth >= 0)
	{
		vec2 mtv = data.penDepth * data.colNormal;
		obj.transform.pos -= mtv;

		obj.rigidbody.velocity = reflect(obj.rigidbody.velocity, data.colNormal) * bounciness;
	}
}


void BoundCollision(PlayerBall & obj, Boundary & bound, float bounciness)
{
	CollisionData data;

	data = boxCollision(obj.transform.getGlobalTransform() * obj.collider.box,
		bound.collider.box);

	if (data.penDepth >= 0)
		data = HullCollision(obj.transform.getGlobalTransform() * obj.collider.hull,
			bound.collider.hull);

	if (data.penDepth >= 0)
	{
		vec2 mtv = data.penDepth * data.colNormal;
		obj.transform.pos -= mtv;

		obj.rigidbody.velocity = reflect(obj.rigidbody.velocity, data.colNormal) * bounciness;
		obj.transform.rotAngle = -obj.transform.rotAngle;
	}
}


void BoundCollision(CaptureBall & obj, Boundary & bound, float bounciness)
{
	CollisionData data;

	data = boxCollision(obj.transform.getGlobalTransform() * obj.collider.box,
		bound.collider.box);

	if (data.penDepth >= 0)
		data = HullCollision(obj.transform.getGlobalTransform() * obj.collider.hull,
			bound.collider.hull);

	if (data.penDepth >= 0)
	{
		vec2 mtv = data.penDepth * data.colNormal;
		obj.transform.pos -= mtv;

		obj.rigidbody.velocity = reflect(obj.rigidbody.velocity, data.colNormal) * bounciness;
		obj.transform.rotAngle += obj.transform.rotAngle/2;	
	}
}

void StaticBoundCollision(Boundary &col, Transform & trans, RigidBody & rigid)
{
	AABB &b = col.collider.box;	

	if ((trans.pos.x >= b.max().x && col.isPos) || (trans.pos.x <= b.min().x && !col.isPos))
	{
		rigid.velocity.x = -rigid.velocity.x;
	}

	if ((trans.pos.x >= b.max().y && col.isPos) || (trans.pos.x <= b.min().y && !col.isPos))
	{
		rigid.velocity.y = -rigid.velocity.y;
	}

}
