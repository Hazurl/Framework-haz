#ifndef __HAZ_2D_BOXCOLLIDER
#define __HAZ_2D_BOXCOLLIDER

#include <GameObject//Component/2D/Collider.hpp>
#include <Tools/Macro.hpp>

BEG_NAMESPACE_HAZ_2D

class BoxCollider : public Collider {
public:
	BoxCollider(GameObject* go);
	BoxCollider(GameObject* go, float x, float y, float width, float height);
	BoxCollider(GameObject* go, Vectorf const& position, float width, float height);
	BoxCollider(GameObject* go, Vectorf const& position, Vectorf const& size);

	~BoxCollider();

	Component* clone(GameObject* go) const;

	inline Vectorf position() const { return {x, y}; }
	inline Vectorf center() const { return {x + width / 2, y + height / 2}; }
	inline Vectorf size() const { return {width, height}; }

	inline float top() const { return y; }
	inline float bottom() const { return y + height; }
	inline float left() const { return x; }
	inline float right() const { return x + width; }

	float x, y, width, height;
};

END_NAMESPACE_HAZ_2D

#endif