#pragma once
//STD Headers

//Library Headers

//Void Engine Headers
#include "utils/Name.h"

//Used for base classes in a RTTI tree only
#define TYPE_INFO_BASE_DECL(CLAZZ) \
public:\
    virtual utils::Name GetTypename() const; \
    static utils::Name GetStaticTypename();

#define TYPE_INFO_DECL(CLAZZ) \
public:\
    virtual utils::Name GetTypename() const override; \
    static utils::Name GetStaticTypename();

#define TYPE_INFO_IMPL(CLAZZ) \
utils::Name CLAZZ::GetTypename() const { return utils::Name(#CLAZZ); } \
utils::Name CLAZZ::GetStaticTypename() { return utils::Name(#CLAZZ); } 