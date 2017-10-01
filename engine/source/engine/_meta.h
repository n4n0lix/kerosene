#pragma once

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                        Includes                        */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

// Std-Includes


// Other Includes

// Internal Includes
#include "_global.h"
#include "owner.h"

ENGINE_NAMESPACE_BEGIN

#define META_CLASS private:         \
    static bool __meta_reg;         \
public:                             \
    virtual string __meta_name();   \
private:            

#define META_CLASS_REGISTER(p_id, p_classname)                          \
bool __##p_classname##_Register() {                                     \
    MetaObject mobj = MetaObject();                                     \
    mobj.id = 0;                                                        \
    mobj.name = #p_classname;                                           \
    function<void*(void)> _new = []() { return new p_classname##(); };  \
    mobj.newInstance = _new;                                            \
    Meta::instance().register_meta( mobj );                             \
    return true;                                                        \
}                                                                       \
bool  p_classname##::__meta_reg = __##p_classname##_Register();         \
string p_classname##::__meta_name() { return #p_classname; }            \

struct MetaObject {
    uint16                 id;
    string                 name;
    function<void*(void)>  newInstance;
};

class Meta {
public:
    static Meta& instance() {
        static Meta INSTANCE;
        return INSTANCE;
    }

    void register_meta( MetaObject obj ) {
        classTableByString[obj.name] = obj;
        classTableByID[obj.id] = obj;
    }

    MetaObject& get_meta( string name );

    MetaObject& get_meta( uint16 id );

private:
    Meta() = default;
    map<string, MetaObject> classTableByString;
    map<uint16, MetaObject> classTableByID;
};



ENGINE_NAMESPACE_END