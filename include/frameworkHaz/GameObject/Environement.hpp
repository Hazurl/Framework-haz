#ifndef __HAZ_ENVIRONEMENT
#define __HAZ_ENVIRONEMENT

#include <frameworkHaz/Tools/Macro.hpp>
#include <frameworkHaz/GameObject/GameObject.hpp>
#include <vector>
#include <frameworkHaz/Geometry/2D/Vector.hpp>
#include <frameworkHaz/GameObject/Component/2D/Collider.hpp>

BEG_NAMESPACE_HAZ

#define TEMPLATE_T template<typename T, typename = typename std::enable_if<std::is_base_of<Component, T>::value>::type>

class Environement {
public:
	Environement();
	virtual ~Environement();

	GameObject* addGameObject(GameObject* go);

	/* Find */

	GameObject* find_GO_of_name(std::string const& name);
	GameObject* find_GO_of_tag(std::string const& tag);

	std::vector<GameObject*> find_GOs_of_name(std::string const& name);
	std::vector<GameObject*> find_GOs_of_tag(std::string const& tag);

	const GameObject* find_GO_of_name(std::string const& name) const;
	const GameObject* find_GO_of_tag(std::string const& tag) const;

	std::vector<const GameObject*> find_GOs_of_name(std::string const& name) const;
	std::vector<const GameObject*> find_GOs_of_tag(std::string const& tag) const;

    TEMPLATE_T std::vector<T*> getComponents();
    TEMPLATE_T std::vector<const T*> getComponents() const;

    TEMPLATE_T T* getComponent();
    TEMPLATE_T const T* getComponent() const;

    std::vector<Component*> getAllComponents();
    std::vector<const Component*> getAllComponents() const;

	std::vector<GameObject*> gos;
};

#undef TEMPLATE_T
#define TEMPLATE_T template<typename T, typename>

#include <frameworkHaz/GameObject/Environement.tcc>

#undef TEMPLATE_T

END_NAMESPACE_HAZ

#endif