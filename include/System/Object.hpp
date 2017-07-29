#ifndef __SYSTEM_OBJECT
#define __SYSTEM_OBJECT

#include <string>
#include <typeinfo>
#include <type_traits>

// Demangled type name
#include <memory>
#include <cxxabi.h>

#include <SystemMacro.h>

BEG_NAMESPACE_HAZ

struct TypeInfo;

class Object {
public:
    typedef std::string TString;

    virtual ~Object();
    virtual TString to_string() const = 0;
    friend std::ostream& operator<< (std::ostream& os, Object const& o);

    TypeInfo getType() const;

    virtual int hash() const = 0;

private:
    static const TString demangle(const char* name);
};

struct TypeInfo {
    const typename Object::TString name;
};

END_NAMESPACE_HAZ

#endif