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
        PlayerController( weak<Entity> );

            void    set_entity( weak<Entity> );
    virtual void    update( vector<KeyEvent>&, vector<CharEvent>&, vector<MouseEvent>& ) override;

private:

            void handleWASD( Controllable&, KeyEvent& );

    weak<Entity> entity;

};

ENGINE_NAMESPACE_END
