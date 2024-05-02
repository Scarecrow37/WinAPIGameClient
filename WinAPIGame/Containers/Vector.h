#pragma once
#include <cassert>
#include <stdexcept>
#include <vector>

#include "IContain.h"
#include "Features/Modify/IBackendModify.h"
#include "Features/Access/ITwoWayAccess.h"
#include "Features/Access/IRandomAccess.h"

namespace Dosuha
{
    template <typename T>
    class Vector final : public IContain, public IRandomAccess<T>, public ITwoWayAccess<T>, public IBackendModify<T>
    {
        using Iterator = T*;
        using ConstIterator = const T*;

    public:
        Vector() : _size(0)
        {
            _capacity = 1;
            _values = new T[_capacity];
        }

        ~Vector() override
        {
            delete[] _values;
        }

        // Element access
        T& At(size_t position) override
        {
            if (!InRange(position)) throw std::out_of_range("Index out of range");
            return _values[position];
        }

        const T& At(size_t position) const override
        {
            if (!InRange(position)) throw std::out_of_range("Index out of range");
            return _values[position];
        }

        T& operator[](size_t position) override
        {
            assert(InRange(position));
            return _values[position];
        }

        const T& operator[](size_t position) const override
        {
            assert(InRange(position));
            return _values[position];
        }

        T& Front() override
        {
            assert(!Empty());
            return _values[0];
        }

        const T& Front() const override
        {
            assert(!Empty());
            return _values[0];
        }

        T& Back() override
        {
            assert(!Empty());
            return _values[_size - 1];
        }

        const T& Back() const override
        {
            assert(!Empty());
            return _values[_size - 1];
        }

        T* Data() noexcept override
        {
            return _values;
        }

        const T* Data() const override
        {
            return _values;
        }

        // Iterators
        Iterator begin()
        {
            return _values;
        }

        ConstIterator begin() const
        {
            return _values;
        }

        ConstIterator cbegin() const noexcept
        {
            return _values;
        }

        Iterator end() noexcept
        {
            return _values + _size;
        }

        ConstIterator end() const noexcept
        {
            return _values + _size;
        }

        ConstIterator cend() const noexcept
        {
            return _values + _size;
        }

        // rbegin
        // crbegin
        // rend
        // crend

        // Capacity
        bool Empty() const noexcept override
        {
            return _size == 0;
        }

        size_t Size() const noexcept override
        {
            return _size;
        }

        // max_size

        void Reserve(const size_t newCapacity)
        {
            if (_capacity > newCapacity) return;
            _capacity = newCapacity;
            T* temp = _values;
            _values = new T[_capacity];
            for (size_t i = 0; i < _size; ++i)
            {
                _values[i] = temp[i];
            }
            delete[] temp;
        }

        size_t Capacity() const noexcept
        {
            return _capacity;
        }

        // Modifiers
        void Clear() noexcept
        {
            delete[] _values;
            _values = new T[_capacity];
            _size = 0;
        }

        // Insert

        // Erase

        void PushBack(const T& value) override
        {
            if (_size == _capacity)
            {
                Reserve(_capacity * 2);
            }
            _values[_size++] = value;
        }

        void PopBack() override
        {
            assert(!Empty());
            _size--;
        }

    private:
        bool InRange(const size_t position) const
        {
            return position < _size;
        }

        T* _values;
        size_t _size;
        size_t _capacity;
    };
}
