#ifndef UNIQUE_PTR
#define UNIQUE_PTR


template <typename T> T* make_unique( T value);

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
    UniquePtr(UniquePtr<T> &uniquep) = delete;

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

    friend T *make_unique <>(T value);
};



#endif //UNIQUE_PTR
