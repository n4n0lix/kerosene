#pragma once

// Std-Includes
#include <functional>

// Other Includes

// Internal Includes
#include "_global.h"
#include "owner.h"

ENGINE_NAMESPACE_BEGIN

#define CONSUMER private
#define EMITTER public

template<typename... Args>
using Consumer = std::function<void( Args... )>;

template<typename... Args>
struct Emitter
{

    typedef Consumer<Args...> __Consumer;

    void operator()( Args... args ) 
    { 
        for ( auto it = begin( _funcs ); it != end( _funcs ); ) {
            if ( it->is_ptr_usable() ) {
                auto& func = *(it->get());
                func(args...);
                ++it;
            }
            else {
                _funcs.erase( it );
            }
        }            
    }

    Emitter& operator+=( weak<__Consumer> o )
    {
        _funcs.push_back( o );
        return *this;
    };

private:
    vector<weak<__Consumer>> _funcs;
};


ENGINE_NAMESPACE_END
