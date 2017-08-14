#ifndef __HAZ_GAMEOBJECT
#define __HAZ_GAMEOBJECT

#include <frameworkHaz/GameObject/Component/Component.hpp>
#include <frameworkHaz/Tools/Macro.hpp>
#include <frameworkHaz/Tools/Utility.hpp>
#include <map>
#include <vector>
#include <algorithm>
#include <frameworkHaz/Tools/EnumFlag.hpp>

ENUM_FLAG_NESTED(BEG_NAMESPACE_HAZ, END_NAMESPACE_HAZ, 
Layers, {
    Default         = 1 << 0,
    Light           = 1 << 1,
    RayCast         = 1 << 2,
    UI              = 1 << 3,

    Custom_1        = 1 << 10,
    Custom_2        = 1 << 11,
    Custom_3        = 1 << 12,
    Custom_4        = 1 << 13,
    Custom_5        = 1 << 14,
    Custom_6        = 1 << 15,
    Custom_7        = 1 << 16,
    Custom_8        = 1 << 17,
    Custom_9        = 1 << 18,

    All             = ~0
});

BEG_NAMESPACE_HAZ

#define TEMPLATE_T template<typename T, typename = typename std::enable_if<std::is_base_of<Component, T>::value>::type>
#define TEMPLATE_T_As_Args template<typename T, typename As = T, typename ...Args, typename = typename std::enable_if<std::is_base_of<Component, As>::value>::type, typename = typename std::enable_if<std::is_base_of<As, T>::value>::type>
#define TEMPLATE_T_As template<typename T, typename As = T, typename = typename std::enable_if<std::is_base_of<Component, As>::value>::type, typename = typename std::enable_if<std::is_base_of<As, T>::value>::type>

class GameObject {
public:
    GameObject(std::string const& name);

    virtual ~GameObject();

    GameObject(GameObject const& go);

    GameObject& operator=(GameObject go);

    static void swap(GameObject& a, GameObject& b);

    /* Component */
    TEMPLATE_T_As_Args T* addComponent(Args... args);
    TEMPLATE_T_As T* addComponent();

    TEMPLATE_T void removeComponent();

    TEMPLATE_T T* getComponent();
    TEMPLATE_T const T* getComponent() const;

    std::vector<Component*> getComponents();
    std::vector<const Component*> getComponents() const;

    TEMPLATE_T std::vector<T*> getComponentsInChilds();
    TEMPLATE_T std::vector<const T*> getComponentsInChilds() const;

    TEMPLATE_T T* getComponentInChilds();
    TEMPLATE_T const T* getComponentInChilds() const;

    TEMPLATE_T T* getComponentInParent();
    TEMPLATE_T const T* getComponentInParent() const;

    void setParent(GameObject* go);
    void addChild(GameObject* go);

    std::string to_string() const;
    void setName(std::string const& n);
    bool compareName(std::string const& n);

    std::string getTag() const;
    void setTag(std::string const& t);
    bool compareTag(std::string const& t);

    bool isActive() const;
    void setActive(bool b);

    bool isOnAnyLayer(Layers l) const;
    bool isOnAllLayers(Layers l) const;
    void AddLayer(Layers l);
    void setLayers(Layers l);
    void removeLayers(Layers l);
    Layers getLayers() const;

protected:

private:
    std::map<std::size_t, Component*> components;

    GameObject* parent = nullptr;
    std::vector<GameObject*> childs = {};

    std::string name;
    std::string tag = "";

    bool is_active = true;
    Layers layers = Layers::Default | Layers::RayCast;
};

#undef TEMPLATE_T
#undef TEMPLATE_T_As
#undef TEMPLATE_T_As_Args

#define TEMPLATE_T template<typename T, typename>
#define TEMPLATE_T_As template<typename T, typename As, typename , typename>
#define TEMPLATE_T_As_Args template<typename T, typename As, typename ...Args, typename , typename>

#include <frameworkHaz/GameObject/GameObject.tcc>

#undef TEMPLATE_T
#undef TEMPLATE_T_As
#undef TEMPLATE_T_As_Args

END_NAMESPACE_HAZ

#endif