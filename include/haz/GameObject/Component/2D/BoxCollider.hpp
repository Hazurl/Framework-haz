#ifndef __HAZ_2D_BOXCOLLIDER
#define __HAZ_2D_BOXCOLLIDER

#include <haz/GameObject//Component/2D/Collider.hpp>
#include <haz/Tools/Macro.hpp>

BEG_NAMESPACE_HAZ_2D

class BoxCollider : public Collider {
public:
	BoxCollider(GameObject* go);
	BoxCollider(GameObject* go, float x, float y, float width, float height);
	BoxCollider(GameObject* go, Vectorf const& position, float width, float height);
	BoxCollider(GameObject* go, Vectorf const& position, Vectorf const& size);

	~BoxCollider();

	std::string to_string() const;
    std::vector<std::string> pretty_strings() const;
	
	Component* clone(GameObject* go) const;

	HAZ_FORCE_INLINE Vectorf position() const { return {x, y}; }
	HAZ_FORCE_INLINE Vectorf center() const { return {x + width / 2, y + height / 2}; }
	HAZ_FORCE_INLINE Vectorf size() const { return {width, height}; }

	HAZ_FORCE_INLINE float top() const { return y; }
	HAZ_FORCE_INLINE float bottom() const { return y + height; }
	HAZ_FORCE_INLINE float left() const { return x; }
	HAZ_FORCE_INLINE float right() const { return x + width; }

	float x, y, width, height;
};

END_NAMESPACE_HAZ_2D

#endif