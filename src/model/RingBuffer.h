//
// Created by Florian Bruggisser on 24.11.18.
//

#ifndef THREE_SCAN_MUTABLEBUFFER_H
#define THREE_SCAN_MUTABLEBUFFER_H

template<class T>
class RingBuffer {
private:
    typedef T *TPtr;

    TPtr *data;

    unsigned int maxSize = 0;

    unsigned int index = 0;

    unsigned int size = 0;

    const unsigned int getIndex(unsigned int i);

public:
    explicit RingBuffer(unsigned int maxSize);

    ~RingBuffer();

    void add(TPtr value);

    void reset();

    void clear();

    const unsigned int length();

    const unsigned int getMaxSize() const {
        return maxSize;
    }

    TPtr operator[](int i) const { return data[getIndex(i)]; }

    TPtr &operator[](int i) { return data[getIndex(i)]; }
};

template<class T>
RingBuffer<T>::RingBuffer(unsigned int maxSize) {
    this->maxSize = maxSize;
    this->data = new TPtr[maxSize];
    reset();
}

template<class T>
RingBuffer<T>::~RingBuffer() {
    clear();
    delete[] data;
}

template<class T>
void RingBuffer<T>::add(TPtr value) {
    data[getIndex(index)] = value;

    index++;
    size = min(size + 1, maxSize);
}

template<class T>
void RingBuffer<T>::reset() {
    index = 0;
    size = 0;
}

template<class T>
void RingBuffer<T>::clear() {
    for (auto i = 0; i < length(); i++) {
        delete data[i];
    }
    reset();
}

template<class T>
const unsigned int RingBuffer<T>::length() {
    return size;
}

template<class T>
const unsigned int RingBuffer<T>::getIndex(unsigned int i) {
    return (index - i + maxSize) % maxSize;
}


#endif //THREE_SCAN_MUTABLEBUFFER_H
