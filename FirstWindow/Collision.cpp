#include "Collision.h"
#include "ColliderComponent.h"

bool Collision::AABB(const SDL_Rect & A, const SDL_Rect & B)
{
	return (A.x + A.w >= B.x &&
		B.x + B.w >= A.x &&
		A.y + A.h >= B.y &&
		B.y + B.h >= A.y);
}

bool Collision::AABB(const ColliderComponent& A, const ColliderComponent& B)
{
	if (&A == &B) return false;
	if (AABB(A.collider, B.collider))
	{
		std::cout << A._tag << " hit " << B._tag << std::endl;
		return true;
	}
	else
	{
		return false;
	}

}

