#pragma once

#include "test.h"

#include "_global.h"
#include "gameobject.h"
    using kerosene::GameObject;

BEHAVIOUR(GameObject, if_child_is_added_it_becomes_a_child)
    GameObject parent;
    s_ptr<GameObject> uChild = make_shared<GameObject>();
    GameObject*       rChild = uChild.get();

    parent.add_child( rChild );

    IS_TRUE( parent.is_child( rChild ) );
END

BEHAVIOUR(GameObject, if_child_is_removed_its_no_longer_a_child)
    GameObject parent;
    u_ptr<GameObject> uChild = make_unique<GameObject>();
    GameObject*       rChild = uChild.get();

    parent.add_child( move(uChild) );
    uChild = parent.remove_child( rChild );

    IS_FALSE( parent.is_child(uChild.get()) );
END