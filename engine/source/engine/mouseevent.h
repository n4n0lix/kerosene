#pragma once

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                        Includes                        */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

// Std-Includes

// Other Includes

// Internal Includes
#include "_global.h"

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                         Class                          */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
ENGINE_NAMESPACE_BEGIN

class MouseEvent {};

class MoveEvent : public MouseEvent {
public:
    MoveEvent( double x, double y ) : _x( x ), _y( y ) {}

    double x() { return _x; }
    double y() { return _y; }

private:
    double _x;
    double _y;
};

class ClickEvent : public MouseEvent {
public:
    ClickEvent( double x, double y, int button, int action, int mods )
        : _x( x ), _y( y ), _button( button ), _action( action ), _mods( mods ) {}

    double x() { return _x; }
    double y() { return _y; }
    int32  button() { return _button; }
    int32  action() { return _action; }
    int32  mods() { return _mods; }

private:
    double _x;
    double _y;
    int32  _button;
    int32  _action;
    int32  _mods;
};

class LeaveEvent : public MouseEvent {
public:
    LeaveEvent() {}

};

class EnterEvent : public MouseEvent {
public:
    EnterEvent() {}
};

class ScrollEvent : public MouseEvent {
public:
    ScrollEvent( double x, double y ) : _x( x ), _y( y ) {}

    double x_offset() { return _x; }
    double y_offset() { return _y; }

private:
    double _x;
    double _y;
};

ENGINE_NAMESPACE_END
