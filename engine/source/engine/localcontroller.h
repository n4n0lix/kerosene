#pragma once

// Std-Includes

// Other Includes

// Internal Includes
#include "_global.h"
#include "entity.h"

ENGINE_NAMESPACE_BEGIN


class LocalController
{
public:
                    LocalController();
    virtual         ~LocalController();

            void    set_entity( weak<Entity> );

};

ENGINE_NAMESPACE_END