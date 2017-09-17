#pragma once

#define OWNER_VECTOR_EXT

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                        Includes                        */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

// Std-Includes
#include <utility>

#ifdef  OWNER_VECTOR_EXT
    #include <vector>
#endif

// MEMORY LEAK DETECTION
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#ifdef _DEBUG
#define DEBUG_NEW new(_NORMAL_BLOCK, __FILE__, __LINE__)
#define new DEBUG_NEW
#endif

// Other Includes

ENGINE_NAMESPACE_BEGIN

template<typename T> class owner;

//
//   weak
////////////////////////////////////////////////////////////////

template<typename T>
class weak
{
    template<typename T>             friend class owner;
    template<typename T, typename U> friend weak<T> static_weak_cast(weak<U> u);

public:
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    /*                        Public                          */
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

    // Constructor
    weak() : weak(nullptr) {}

    // Constructor
    weak(std::nullptr_t null) {
        // Create state
        _ptr = nullptr;
        _ptrValid = nullptr;
        _ptrRefCounter = nullptr;
        _isNullPtr = true;
    }

    // Copy-Constructor
    weak(const weak<T>& orig) {
        // Copy state
        _ptr            = orig._ptr;
        _ptrValid       = orig._ptrValid;
        _ptrRefCounter  = orig._ptrRefCounter;
        _isNullPtr      = _ptr == nullptr;

        // Increase ref counter
        ref_count_inc();
    }

    // Move-Constructor
    weak(weak<T>&& orig) {
        // Move state
        _ptr            = orig._ptr;
        _ptrValid       = orig._ptrValid;
        _ptrRefCounter  = orig._ptrRefCounter;
        _isNullPtr      = _ptr == nullptr;

        // Initialize orig to nullptr
        orig._ptr = nullptr;
        orig._ptr = nullptr;
        orig._ptrRefCounter = nullptr;
        orig._isNullPtr = true;
    }

    // Destructor
    ~weak() {
        ref_count_dec();
    }

    // Copy assignment
    weak<T>&       operator=(const weak<T>& orig)  {
        // Copy state
        _ptr            = orig._ptr;
        _ptrValid       = orig._ptrValid;
        _ptrRefCounter  = orig._ptrRefCounter;
        _isNullPtr      = _ptr == nullptr;

        // Increase ref counter
        ref_count_inc();

        return *this;
    }

    // Move assignment
    template<typename U> // needed for move assign inherent types
    weak<T>&       operator=(weak<U>&& orig) {
        // Move state
        _ptr            = orig._ptr;
        _ptrValid       = orig._ptrValid;
        _ptrRefCounter  = orig._ptrRefCounter;
        _isNullPtr      = _ptr == nullptr;

        // Initialize orig to nullptr
        orig._ptr = nullptr;
        orig._ptr = nullptr;
        orig._ptrRefCounter = nullptr;
        orig._isNullPtr = true;

        return *this;
    }

    inline T*      operator->() const { return _ptr; }
    inline T*      get()        const { return _ptr; }

    bool operator== (const weak &y) const { return _ptr == y._ptr; }
    bool operator!= (const weak &y) const { return !(_ptr == y._ptr); }

    template<typename U>
    bool operator== (const owner<U> &y) const { return _ptr == y.get(); }

    template<typename U>
    bool operator!= (const owner<U> &y) const { return !(_ptr == y.get()); }

    // Determines if it's safe to use the ptr retrieved from get(). Does not ensure that the ptr is not null!
    inline bool ptr_is_valid() const
    { 
        return _isNullPtr ? true : (*_ptrValid);
    }

private:
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    /*                        Private                         */
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

            // Constructor
            weak(T* ptr, bool* ptrValid, uint32_t* ptrInsCounter) {
                _ptr = ptr;
                _ptrValid = ptrValid;
                _ptrRefCounter = ptrInsCounter;
                _isNullPtr = false;

                // Increase ref counter
                ref_count_inc();
            }

            void make_null() {
                // Decrease ref counter
                ref_count_dec();

                // Delete state
                _ptr = nullptr;
                _ptrValid = nullptr;
                _ptrRefCounter = nullptr;
                _isNullPtr = true;
            }

    inline uint32_t ref_count()
    {
        return _isNullPtr ? 1 : *_ptrRefCounter;
    }

    inline void ref_count_inc() {
        if (_isNullPtr) return;

        (*_ptrRefCounter)++;
    }

    inline void ref_count_dec() {
        if (_isNullPtr) return;

        (*_ptrRefCounter)--;
        if ((*_ptrRefCounter) == 0) {
            delete _ptrValid;
            delete _ptrRefCounter;
        }
    }

    T*          _ptr;
    bool*       _ptrValid;
    uint32_t*   _ptrRefCounter;

    bool _isNullPtr;
};

//
//   owner
////////////////////////////////////////////////////////////////

template<typename T>
class owner
{
    template<typename T> friend owner<T> make_owner(T* ptr);

public:

    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    /*                        Public                          */
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

    // Constructor
    owner() : owner(nullptr) {} // TODO: Investigate if owner(T*) or owner(nullptr_t) is called

    // Constructor
    explicit owner(T* ptr) {
        // Create new State
        _ptr = ptr;
        _ptrValid = new bool(true);
        _ptrRefCounter = new uint32_t(0);
        
        // Increase ref counter
        ref_count_inc();
    }

    // Constructor
    owner(nullptr_t null) {
        // Nullpointer State
        _ptr = nullptr;
        _ptrValid = nullptr;
        _ptrRefCounter = nullptr;
    }

    // Copy-Constructor
    owner(const owner<T>&  orig) = delete;

    // Move-Constructor
    template<typename U> // needed for move assign inherent types
    owner(owner<U>&& orig) {
        // Move state
        _ptr           = orig._ptr;
        _ptrValid      = orig._ptrValid;
        _ptrRefCounter = orig._ptrRefCounter;

        // Initialize orig to nullptr
        orig._ptr           = nullptr;
        orig._ptrValid      = nullptr;
        orig._ptrRefCounter = nullptr;
    }

    // Destructor
    ~owner() { 
        if (_ptr != nullptr) {
            invalidate_pointer();
            ref_count_dec();
            delete _ptr;
        }
    }

    inline T* operator->() const { return _ptr; }
    inline T* get() const { return _ptr; }
    T* release() {
        T* oldPtr = _ptr;
        
        if (_ptr != nullptr) {
            invalidate_pointer();
            ref_count_dec();
        }

        _ptr            = nullptr;
        _ptrValid       = nullptr;
        _ptrRefCounter  = nullptr;

        return oldPtr;
    }

    void destroy() {
        if (_ptr != nullptr) {
            invalidate_pointer();
            ref_count_dec();
            delete _ptr;

            _ptr = nullptr;
            _ptrValid = nullptr;
            _ptrRefCounter = nullptr;
        }
    }

    // Copy Assignment
    owner<T>&       operator=(const owner<T>& orig) = delete;

    // Move assignment
    template<typename U> // needed for move assign inherent types
    owner<T>&       operator=(owner<U>&& orig) {
        // Move state
        _ptr            = orig._ptr;
        _ptrValid       = orig._ptrValid;
        _ptrRefCounter  = orig._ptrRefCounter;

        // Initialize orig to nullptr
        orig._ptr           = nullptr;
        orig._ptrValid      = nullptr;
        orig._ptrRefCounter = nullptr;

        return *this;
    }

    template<typename U>
    bool            operator== (const weak<U> &y) const { return _ptr == y.get(); }

    template<typename U>
    bool            operator!= (const weak<U> &y) const { return !(_ptr == y.get()); }

    bool            operator== (const owner &other) const { return (_ptr == other._ptr); }
    bool            operator!= (const owner &other) const { return !(this == other); }

    bool            operator== (const nullptr_t &other) const { return (_ptr == other); }
    bool            operator!= (const nullptr_t &other) const { return !(this == other); }

    inline weak<T>  get_non_owner() {
        if (_ptr == nullptr)
            return weak<T>();
        else
            return weak<T>(_ptr, _ptrValid, _ptrRefCounter); 
    }

    inline uint32_t ref_count() { return *_ptrRefCounter; }

private:
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    /*                        Private                         */
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    template <typename U>  friend class owner; // needed for move assign inherent types

    inline void invalidate_pointer() {
        (*_ptrValid) = false;
    }

    inline void ref_count_dec() {
        (*_ptrRefCounter)--;

        if ((*_ptrRefCounter) == 0) {
            delete _ptrValid;
            delete _ptrRefCounter;
        }
    }

    inline void ref_count_inc() {
        (*_ptrRefCounter)++;
    }


    T*          _ptr;
    bool*       _ptrValid;
    uint32_t*   _ptrRefCounter;

};

//
// utility
/////////////////////////////////////////////////////////////////

template<typename T, typename... Args>
owner<T> make_owner(Args&&... args) {
    return owner<T>(new T(std::forward<Args>(args)...));
}

template<typename T, typename U>
weak<T> static_weak_cast(weak<U> u) {
    if (u.get() == nullptr)
        return weak<T>(nullptr);
    else
        return weak<T>((T*)u._ptr, u._ptrValid, u._ptrRefCounter);
}

template<typename T>
owner<T> extract_owner(std::vector<owner<T>>& vec, weak<T> ptr) {
    auto it = vec.begin();
    for (; it != vec.end(); ++it) {
        if (it->get() == ptr.get()) break;
    }

    if (it != vec.end()) {
        auto retval = std::move( *it );
        vec.erase(it);
        return std::move( retval );
    }

    return nullptr;
}

template<typename T>
bool contains_owner(const std::vector<owner<T>>& vec, weak<T> ptr) {
    auto it = vec.begin();
    for (; it != vec.end(); ++it) {
        if (it->get() == ptr.get()) break;
    }

    return it != vec.end();
}

template<typename T>
struct weak_less {
    bool operator() (const weak<T>& x, const weak<T>& y) const {
        return x.get() < y.get();
    }
};

ENGINE_NAMESPACE_END