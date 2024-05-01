#ifndef UNIQUE_PTR
#define UNIQUE_PTR

template <typename T> T* make_unique(const T &value);

template <typename T> 
class UniquePtr {
private:
    T* _p;
public:
    UniquePtr() : _p(nullptr) { }
    UniquePtr(T* ptr) : _p(ptr) { }
    
    // destructor 
    ~UniquePtr() { 
        delete _p;
        _p = nullptr;
    }

    // can't Copy constructor
    UniquePtr(const UniquePtr<T> &uniquep) = delete;

    // Operator=
    void operator=(UniquePtr<T> &uniquep) = delete;

    // get
    T *get() { return _p;}

    // Operator*
    T operator*();

    // Operator->
    T *operator->() { return _p;};

    // reset
    void reset();
    void reset(T *ptr);
    
    // release
    T *release();

    friend T *make_unique <>(const T &value);
    
    operator T*() const { return _p;}
};

template <typename T>
T *make_unique(const T &value) {
    T *Tptr = new T(value);
    return Tptr;
}

template <typename T> 
void UniquePtr<T>::reset() {
    delete _p;
    _p = nullptr;
}

template <typename T>
void UniquePtr<T>::reset(T *ptr) {
    reset();
    _p = ptr;
}

template <typename T>
T UniquePtr<T>::operator*() {
    return *get();
}

template <typename T>
T *UniquePtr<T>::release() {
    T *res = _p;
    _p = nullptr;
    return res;
}

#endif //UNIQUE_PTR
