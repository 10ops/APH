#ifndef SHARED_PTR
#define SHARED_PTR


template <typename T> T* make_shared(const T &value);

template <typename T> 
class SharedPtr{
private:
    T* _p;
    int* _count;

public:
    SharedPtr() : _p(nullptr), _count(nullptr) { }
    SharedPtr(T *ptr) : _p(ptr), _count(new int{1}) { }

    T *get() { return _p;}

    friend T* make_shared <>(const T &value);

    int use_count() {
        return (_count == nullptr ? 0 : *_count);
    }

    ~SharedPtr();
    SharedPtr(const SharedPtr<T> &ptr);

    SharedPtr<T> &operator=(const SharedPtr<T> &ptr);
    T *operator->();

    void reset() {
        _p = nullptr;
        (*_count) --;
        _count = nullptr;
    }

    void reset(T *ptr){
        this->reset();
        this->_p = ptr;
        this->_count = new int{1};
    }

    operator T*() const {return _p;}
};



template <typename T> 
SharedPtr<T>::SharedPtr(const SharedPtr<T> &ptr) {
    _p = ptr._p;
    _count = ptr._count;
    (*_count)++;
}

template <typename T> 
SharedPtr<T> &SharedPtr<T>::operator=(const SharedPtr<T> &ptr) {
		if (ptr._p == this->_p) { return *this;}
    this->_p = ptr._p;
    this->_count = ptr._count;
    (*_count)++;
    return *this;
}

template <typename T>
SharedPtr<T>::~SharedPtr() {
    if (_count != nullptr && *_count > 1) {
        (*_count)--;
        _p = nullptr;
        _count = nullptr;
    }
    else {
        delete _p;
        delete _count;
        _p = nullptr;
        _count = nullptr;
    }
}

template <typename T> 
T *make_shared(const T &value) {
    T *ptr = new T(value);
    return ptr;
}

template <typename T>
T *SharedPtr<T>::operator->() {
    return _p;
}


#endif //SHARED_PTR
