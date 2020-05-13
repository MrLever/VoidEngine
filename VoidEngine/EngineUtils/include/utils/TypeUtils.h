#pragma once
//STD Headers

//Library Headers

//Void Engine Headers
#include "utils/EngineUtilities.h"
#include "utils/Name.h"

#define ENABLE_RTTI(CLAZZ) \
public:\
    virtual utils::Name GetTypename() const { return utils::Name(#CLAZZ); } \
    static utils::Name GetStaticTypename() { return utils::Name(#CLAZZ); } \
    template<class T> bool Is() { VE_ASSERT(false, "Not yet implemented") return false; }
