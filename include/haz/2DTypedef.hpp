#ifndef __HAZ_2DTYPEDEF
#define __HAZ_2DTYPEDEF

#include <haz/Tools/Macro.hpp>

#include <haz/Geometry/2D/Vector.hpp>

#include <haz/GameObject/2D/Physic.hpp>
#include <haz/GameObject/Component/2D/Transform.hpp>
#include <haz/GameObject/Component/2D/BoxCollider.hpp>
#include <haz/GameObject/Component/2D/CircleCollider.hpp>
#include <haz/GameObject/Component/2D/EdgeCollider.hpp>
#include <haz/GameObject/Component/2D/PolygonCollider.hpp>

BEG_NAMESPACE_HAZ

typedef _2D::Vectorf Vector2f;
typedef _2D::Vectord Vector2d;
typedef _2D::Vectori Vector2i;
typedef _2D::Vectorui Vector2ui;

typedef _2D::Physic Physic2D;

typedef _2D::Transform Transform2D;

typedef _2D::BoxCollider BoxCollider;
typedef _2D::CircleCollider CircleCollider;
typedef _2D::EdgeCollider EdgeCollider;
typedef _2D::PolygonCollider PolygonCollider;

END_NAMESPACE_HAZ

#endif
