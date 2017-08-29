#ifndef __HAZ_ENVIRONEMENT
#define __HAZ_ENVIRONEMENT

#include <frameworkHaz/Tools/Macro.hpp>
#include <frameworkHaz/GameObject/GameObject.hpp>
#include <frameworkHaz/Geometry/2D/Vector.hpp>
#include <frameworkHaz/GameObject/Component/2D/Collider.hpp>

#include <vector>
#include <map>
#include <string>

BEG_NAMESPACE_HAZ

class Environement {
public:
	/* Ctor Dtor */
	Environement();
	~Environement();

	/* GameObjects Modifier */
#define TEMP_ARGS template<typename ...Args>
	TEMP_ARGS GameObject* instantiate(Args... args);
#undef TEMP_ARGS

private:
	std::vector<GameObject*> gos;

public:	
	/* Components Query */
		/* By Name */
	GameObject* find_GO_of_name(std::string const& name);
	const GameObject* find_GO_of_name(std::string const& name) const;
	std::vector<GameObject*> find_GOs_of_name(std::string const& name);
	std::vector<const GameObject*> find_GOs_of_name(std::string const& name) const;
		/* By Tag */
	GameObject* find_GO_of_tag(std::string const& tag);
	const GameObject* find_GO_of_tag(std::string const& tag) const;
	std::vector<GameObject*> find_GOs_of_tag(std::string const& tag);
	std::vector<const GameObject*> find_GOs_of_tag(std::string const& tag) const;
		/* By Type */
#define TEMP_COMP template<typename T, typename = typename std::enable_if<std::is_base_of<Component, T>::value>::type>
	TEMP_COMP T* getComponent();
	TEMP_COMP const T* getComponent() const;
	TEMP_COMP std::vector<T*> getComponents();
	TEMP_COMP std::vector<const T*> getComponents() const;
#undef TEMP_COMP
		/* All */
    std::vector<Component*> getAllComponents();
	std::vector<const Component*> getAllComponents() const;
	
	/* Debug */
	void print_to_tree ();
private:
	void print_to_tree_helper (GameObject* cur, std::string indent, bool is_last);
	
};

#define TEMP_ARGS template<typename ...Args>

TEMP_ARGS
GameObject* Environement::instantiate(Args... args) {
	GameObject* go = new GameObject(args...);
	gos.push_back(go);
	return go;
}

#undef TEMP_ARGS

#define TEMP_COMP template<typename T, typename>
TEMP_COMP std::vector<T*> Environement::getComponents() {
    std::vector<T*> v = {};
    for (auto* go : gos)
        for (auto* c : go->getComponentsInChilds<T>())
            v.push_back(c);

    return v;
}
TEMP_COMP std::vector<const T*> Environement::getComponents() const {
    std::vector<const T*> v = {};
    for (auto* go : gos)
        for (auto* c : go->getComponentsInChilds<T>())
            v.push_back(c);

    return v;
}
TEMP_COMP T* Environement::getComponent() {
    for (auto* go : gos)
        for (auto* c : go->getComponentsInChilds<T>())
            return c;

    return nullptr;
}
TEMP_COMP const T* Environement::getComponent() const {
    for (auto* go : gos)
        for (auto* c : go->getComponentsInChilds<T>())
            return c;
    
    return nullptr;
}
#undef TEMP_COMP

END_NAMESPACE_HAZ

#endif