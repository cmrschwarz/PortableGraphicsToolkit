#pragma once
#include <vector>
#include <string>
#include <assert.h>
namespace dt {
    enum class DataType { DOUBLE, STRING, EMPTY };
    class Content {
      private:
        DataType data_type;
        union {
            std::string _str;
            double _dbl;
        };

      public:
        Content(double d)
        {
            setValue(d);
        }
        Content(const std::string& s)
        {
            setValue(s);
        }
        Content()
        {
            data_type = DataType::EMPTY;
        }
        Content(const Content& rhs)
        {
            setValue(rhs);
        }
        void operator=(const Content& rhs)
        {
            setValue(rhs);
        }
        ~Content()
        {
        }

      public:
        void setValue(double d)
        {
            data_type = DataType::DOUBLE;
            new (&_dbl) double(d);
        }
        void setValue(const std::string& val)
        {
            data_type = DataType::STRING;
            new (&_str) std::string(val);
        }
        void setValue(const Content& c)
        {
            switch (c.data_type) {
            case dt::DataType::DOUBLE:
                setValue(c._dbl);
                break;
            case dt::DataType::STRING:
                setValue(c._str);
                break;
            case dt::DataType::EMPTY:
                removeValue();
                break;
            default:
                assert(false, "Invalid Content Type");
                break;
            }
        }
        void removeValue()
        {
            data_type = DataType::EMPTY;
        }
        const std::string& getString() const
        {
            return _str;
        }
        double getDouble() const
        {
            return _dbl;
        }
        bool isString() const
        {
            return (data_type == DataType::STRING) ? true : false;
        }
        bool isDouble() const
        {
            return (data_type == DataType::DOUBLE) ? true : false;
        }
        bool isEmpty() const
        {
            return (data_type == DataType::EMPTY) ? true : false;
        }
    };
}