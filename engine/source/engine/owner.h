#pragma once

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                        Includes                        */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

// Std-Includes
#include <utility>
#include <exception>

// Other Includes

// Internal Includes

ENGINE_NAMESPACE_BEGIN

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                         Class                          */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

template<class T> class ownerP;

template<class T, typename... Args>
ownerP<T> make_owner(Args&&... args) {
    return ownerP<T>(new T( std::forward(args) ));
}

template<class T>
class weak
{
    template<class T> friend class ownerP;

public:
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    /*                        Public                          */
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

    const T*    operator->() { return _ptr; }
    bool        is_valid()   { return _ptrValid; }

private:
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    /*                        Private                         */
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

            weak(T* ptr, bool* ptrValid, int* ptrInsCounter) { 
                _ptr            = ptr;
                _ptrValid       = ptrValid;
                _ptrInsCounter  = ptrInsCounter;
                _ptrInsCounter++;
            }

            ownerP(const ownerP<T>&  orig) = default;
            ownerP(ownerP<T>&& orig)       = default;

            ~weak() {
                _ptrInsCounter--;
                if (_ptrInsCounter == 0) {
                    delete _ptrValid;
                    delete _ptrInsCounter;
                }
            }

    T*          _ptr;
    bool*       _ptrValid;
    int*        _ptrInsCounter;
};

template<class T>
class ownerP
{
    template<class T> friend ownerP<T> make_owner(T* ptr);

public:
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    /*                        Public                          */
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
            ownerP()        : ownerP(nullptr) {}

            ownerP(T* ptr) { 
                _ptr           = ptr;
                _ptrValid      = new bool(true);
                _ptrInsCounter = new int(1);
            }

            ownerP(const ownerP<T>&  orig) = delete;
            ownerP(ownerP<T>&& orig)       = default;

            ~ownerP() {
                _ptrValid = false;
                delete _ptr;

                _ptrInsCounter--;
                if (_ptrInsCounter == 0) {
                    delete _ptrValid;
                    delete _ptrInsCounter;
                } 
            }


    T*          operator->()    { return _ptr; }
    weak<T>     get_non_owner   { return std::move( weak<T>(_ptr, _ptrValid) ); }

private:
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    /*                        Private                         */
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

    T*          _ptr;
    bool*       _ptrValid;
    int*        _ptrInsCounter;
};

ENGINE_NAMESPACE_END