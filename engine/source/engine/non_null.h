#pragma once

//
// not_null
//
// Restricts a pointer or smart pointer to only hold non-null values.
// 
// Has zero size overhead over T.
//
// If T is a pointer (i.e. T == U*) then 
// - allow construction from U* or U& 
// - disallow construction from nullptr_t
// - disallow default construction
// - ensure construction from U* fails with nullptr
// - allow implicit conversion to U*
//
template<class T>
class not_null
{
    static_assert(std::is_assignable<T&, std::nullptr_t>::value, "T cannot be assigned nullptr.");
public:
    not_null(T t) : ptr_(t) { ensure_invariant(); }
    not_null& operator=(const T& t) { ptr_ = t; ensure_invariant(); return *this; }

    not_null(const not_null &other) = default;
    not_null& operator=(const not_null &other) = default;

    template <typename U, typename Dummy = std::enable_if_t<std::is_convertible<U, T>::value>>
    not_null(const not_null<U> &other)
    {
        *this = other;
    }

    template <typename U, typename Dummy = std::enable_if_t<std::is_convertible<U, T>::value>>
    not_null& operator=(const not_null<U> &other)
    {
        ptr_ = other.get();
        return *this;
    }

    // prevents compilation when someone attempts to assign a nullptr 
    not_null(std::nullptr_t) = delete;
    not_null(int) = delete;
    not_null<T>& operator=(std::nullptr_t) = delete;
    not_null<T>& operator=(int) = delete;

    T get() const {
#ifdef _MSC_VER
        __assume(ptr_ != nullptr);
#endif
        return ptr_;
    } // the assume() should help the optimizer

    operator T() const { return get(); }
    T operator->() const { return get(); }

    bool operator==(const T& rhs) const { return ptr_ == rhs; }
    bool operator!=(const T& rhs) const { return !(*this == rhs); }
private:
    T ptr_;

    // we assume that the compiler can hoist/prove away most of the checks inlined from this function
    // if not, we could make them optional via conditional compilation
    void ensure_invariant() const { Requires(ptr_ != nullptr); }

    // unwanted operators...pointers only point to single objects!
    // TODO ensure all arithmetic ops on this type are unavailable
    not_null<T>& operator++() = delete;
    not_null<T>& operator--() = delete;
    not_null<T> operator++(int) = delete;
    not_null<T> operator--(int) = delete;
    not_null<T>& operator+(size_t) = delete;
    not_null<T>& operator+=(size_t) = delete;
    not_null<T>& operator-(size_t) = delete;
    not_null<T>& operator-=(size_t) = delete;
};