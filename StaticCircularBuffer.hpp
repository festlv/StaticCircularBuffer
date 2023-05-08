//
// Created by reinis on 5/8/23.
//

#ifndef STATIC_CIRCULAR_BUFFER_HPP
#define STATIC_CIRCULAR_BUFFER_HPP

#include <array>
#include <unistd.h>
#include <cassert>

/**
 * Buffer that stores last TElemCount items and allows accessing them in last-added first.
 *
 * Usage example:
 * StaticCircularBuffer<char, 3> b; // allocates static storage for up to 3 chars
 * b.add('A');
 * b.add('B');
 * b.add('C'); // now the statically allocated array is full
 * b.at(0) -> 'C'
 * b.at(1) -> 'B'
 * b.at(2) -> 'A'
 *
 * b.add('D') // now the array overflows and the oldest item is overwritten by 'D'
 * b.at(0) -> 'D'
 * b.at(1) -> 'C'
 * b.at(1) -> 'B'
 *
 *
 * @tparam T
 * @tparam TElemCount
 */
template<class T, size_t TElemCount>
class StaticCircularBuffer {
public:
    explicit StaticCircularBuffer() = default;

    /**
     * Returns the number of valid elements stored in buffer.
     * @return
     */
    size_t size() const {
        return _size;
    }

    /**
     * Returns the maximum number of elements that can be stored in buffer
     * @return
     */
    size_t capacity() const {
        return TElemCount;
    }

    /**
     * Adds an element to buffer, overwriting the oldest element if buffer is full
     * @param elem
     */
    void add(const T& elem) {
        _buf[_last] = elem;
        _last = (_last + 1) % TElemCount;
        if (_size < TElemCount) {
            _size++;
        }
    }

    /**
     * Returns true if buffer has reached it's max capacity (all elements are valid)
     * @return
     */
    bool full() const {
        return _size == TElemCount;
    }

    /**
     * Returns elements starting from last added
     * @param pos
     * @return
     */
    inline T& at(size_t pos) {
        assert(pos < TElemCount);
        ssize_t i = (ssize_t)_last - pos - 1;
        if (i < 0)
            i = TElemCount + i;
        return _buf.at(i);
    }
    void fill(const T& elem) {
        for (auto& a: _buf)
            a = elem;
    }

    /**
     *  Iterator that allows to use range-based for loops to iterate over the valid elements of the buffer
     */
    class iterator {
    public:
        explicit iterator(size_t at, StaticCircularBuffer<T, TElemCount>* parent ): _at(at), _parent(parent) {}
        iterator operator++() { ++_at; return *this; }
        bool operator!=(const iterator & other) const { return _at != other._at;  }
        const T& operator*() { return _parent->at(_at); }
    private:
        size_t _at;
        StaticCircularBuffer<T, TElemCount>* _parent;
    };

    iterator begin() { return iterator(0, this); }
    iterator end() { return iterator(_size, this); }

private:
    mutable std::array<T, TElemCount> _buf;
    mutable size_t _last = 0;
    mutable size_t _size = 0;
};

#endif
