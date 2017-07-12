#pragma once
#include <type_traits>
#include <cstdlib>
#include <pgt/io/logger/logger.h>
namespace pgt {
// A dynamically resizing Queue of a templated type.
// It does NOT support const types.
// It does NOT have ACCESS_VIOLATION protection on pop operations for
// performance reason. Use with caution (as always :)) The number of elements it
// grows once the current capacity is reached can be customized by changing
// GROW_STEPS. when not changed, the array size will be doubled positive grow
// steps will cause linear growth, negative values are reserved for constants
// suggested use style: push_back, pop_front

#define PGT_CARRAY_GROWTH_MULT_2 -1
#define PGT_CARRAY_GROWTH_MULT_1_5 -2
    template <typename TYPE, int GROW_STEPS = PGT_CARRAY_GROWTH_MULT_2>
    class Queue {
      protected:
        TYPE* _start;
        TYPE* _end;
        TYPE* _first;
        TYPE* _last;

      private:
        static const int START_CAPACITY = 4;
        void bring_back_to_front()
        {
            memmove(_start, _first, size() * sizeof(TYPE));
            _last -= (_first - _start);
            _first = _start;
        }
        void resize(int size_new)
        {
            TYPE* new_array = (TYPE*)malloc(size_new * sizeof(TYPE));
            PGT_DEBUG_ASSERT(new_array != NULL, "MEMORY REALLOCATION FAILED");
            memcpy(new_array, _first, size() * sizeof(TYPE));
            _last = new_array + (_last - _first);
            _first = new_array;
            _end = new_array + size_new - 1;
            free(_start);
            _start = new_array;
        }
        void grow()
        {
            switch (GROW_STEPS) {
            case PGT_CARRAY_GROWTH_MULT_2:
                resize(capacity() << 1);
                break;
            case PGT_CARRAY_GROWTH_MULT_1_5:
                resize((int)(capacity() * 1.5));
                break;
            default:
                resize(capacity() + GROW_STEPS);
                break;
            }
        }

      public:
        Queue(int capacity = START_CAPACITY)
        {
            _start = (TYPE*)malloc(sizeof(TYPE) * capacity);
            _end = _start + (capacity - 1);
            _last = _start - 1;
            _first = _start;
        }
        ~Queue()
        {
            free(_start);
        }

      public:
        void reserve(int space_min)
        {
            if (capacity() < space_min) resize(space_min);
        }
        void push_back(const TYPE& element)
        {
            if (_last == _end) {
                if (_first > _start)
                    bring_back_to_front();
                else
                    grow();
            }
            _last++;
            *_last = element;
        }
        void push_front(const TYPE& element)
        {
            if (_first > _start) {
                _first--;
                *_first = element;
                return;
            }
            if (_last == _end) {
                grow();
            }
            memmove(_start, _start + 1, size() * sizeof(TYPE));
            _last++;
            *_start = element;
        }
        void set_capacity(int capacity)
        {
            if (_first > _start) bring_back_to_front();
            if (size() > capacity) {
                _last = _start + capacity - 1;
            }
            resize(capacity);
        }
        void shrink_to_fit()
        {
            if (_first > _start) bring_back_to_front();
            resize(size());
        }
        //!! this changes the order of the elements by simply inserting the last
        //! element into the
        //! free slot.
        void remove_fast_at(int index, int count = 1)
        {
            memcpy(_first + index, _last - count, sizeof(TYPE) * count);
            _last -= count;
        }
        void remove_at(int index, int count = 1)
        {
            memmove(_first + index, _first + index + count,
                    sizeof(TYPE) * (size() - index - count));
            _last -= count;
        }
        void swap(int i_left, int i_right)
        {
            TYPE& vl = get(i_left);
            TYPE& vr = get(i_right);
            TYPE temp = vl;
            vl = vr;
            vr = temp;
        }
        inline void clear()
        {
            _first = _start;
            _last = _start - 1;
        }
        inline void pop_back(int count = 1)
        {
            _last -= count;
            if (_last < _first) clear();
        }
        inline void pop_front(int count = 1)
        {
            _first += count;
            if (_last < _first) clear();
        }
        inline TYPE& get(int index) const
        {
            return *(_first + index);
        }
        inline TYPE& operator[](int index) const
        {
            return get(index);
        }
        inline TYPE& back() const
        {
            return *_last;
        }
        inline TYPE& front() const
        {
            return *_first;
        }
        inline TYPE* begin() const
        {
            return _first;
        }
        inline TYPE* end() const
        {
            return _last + 1;
        }
        inline const int capacity() const
        {
            return _end - _start + 1;
        };
        inline const int size() const
        {
            return _last - _first + 1;
        };
    };
}
