#pragma once

// Std-Includes

// Other Includes

// Internal Includes
#include "_global.h"
#include "entity.h"
#include "keyevent.h"
#include "charevent.h"
#include "mouseevent.h"
#include "controllable.h"
#include "localcontroller.h"

ENGINE_NAMESPACE_BEGIN

class PlayerController : public LocalController
{
public:
        PlayerController( Entity );

            void    set_entity( Entity );
    virtual void    update( std::vector<KeyEvent>&, std::vector<CharEvent>&, std::vector<MouseEvent>& ) override;

private:

            void handleWASD( CControllable&, KeyEvent& );

    Entity entity;

};

ENGINE_NAMESPACE_END
