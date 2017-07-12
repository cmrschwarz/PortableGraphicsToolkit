#pragma once
#include <pgt/io/logger/logger.h>
namespace pgt {
// A dynamically resizing Array of a templated type.
// It does NOT support const types.
// It does NOT have ACCESS_VIOLATION protection on pop operations for
// performance reason. Use with caution (as always :)) The number of elements it
// grows once the current capacity is reached can be customized by changing
// GROW_STEPS. when not changed, the array size will be doubled (pretty
// aggressive i know)

#define PGT_CARRAY_GROWTH_MULT_2 -1
#define PGT_CARRAY_GROWTH_MULT_1_5 -2
    template <typename TYPE, int GROW_STEPS = PGT_CARRAY_GROWTH_MULT_2>
    class DArray {
      protected:
        TYPE* _start;
        TYPE* _last;
        TYPE* _end;

      private:
        static const int START_CAPACITY = 4;
        void resize(int size_new)
        {
            TYPE* new_array = (TYPE*)realloc(_start, size_new * sizeof(TYPE));
            PGT_ASSERT(new_array != NULL, "MEMORY REALLOCATION FAILED");
            _end = new_array + size_new - 1;
            _last = _last - _start + new_array;
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
        DArray(int capacity = START_CAPACITY)
        {
            _start = (TYPE*)malloc(sizeof(TYPE) * capacity);
            PGT_ASSERT(_start != NULL, "MEMORY ALLOCATION FAILED");
            _end = _start + (capacity - 1);
            _last = _start - 1;
        }
        ~DArray()
        {
            free(_start);
        }

      public:
        void reserve(int space_min)
        {
            if (capacity() < space_min) resize(space_min);
        }
        void push_back_unsafe(const TYPE& element)
        {
            _last++;
            *_last = element;
        }
        void push_back(const TYPE& element)
        {
            if (_last == _end) grow();
            _last++;
            *_last = element;
        }
        void set_capacity(int capacity)
        {
            if (size() > capacity) {
                _last = _start + capacity - 1;
            }
            resize(capacity);
        }
        // shrinks array to required capacity (min 1)
        void shrink_to_fit()
        {
            int s_req = size();
            if (s_req < 1) s_req = 1;
            resize(s_req);
        }
        //!! this changes the order of the elements by simply inserting the last
        //! element into the
        //! free slot.
        void remove_fast_at(int index, int count = 1)
        {
            memcpy(_start + index, _last - count, sizeof(TYPE) * count);
            _last -= count;
        }
        void remove_at(int index, int count = 1)
        {
            memmove(_start + index, _start + index + count,
                    sizeof(TYPE) * (size() - index - count));
            _last -= count;
        }
        void emplace_at(int index, TYPE element)
        {
            if (_last == _end) grow();
            memmove(_start + index + 1, _start + index,
                    sizeof(TYPE) * (size() - index));
            *(_start + index) = element;
            _last++;
        }
        void emplace_at(int index, TYPE* element, int count)
        {
            if (size() + count > capacity()) resize(capacity() + count);
            memmove(_start + index + count, _start + index,
                    sizeof(TYPE) * (size() - index));
            memcpy(_start + index, element, count * sizeof(TYPE));
            _last += count;
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
            _last = _start - 1;
        }
        inline void pop_back()
        {
            _last--;
        }
        inline void pop_back(int count)
        {
            _last -= count;
        }
        inline TYPE& get(int index) const
        {
            return *(_start + index);
        }
        inline TYPE& operator[](int index) const
        {
            return get(index);
        }
        inline TYPE& back() const
        {
            return *_last;
        }
        inline TYPE* begin() const
        {
            return _start;
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
            return _last - _start + 1;
        };
    };
}
