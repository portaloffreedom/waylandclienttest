#ifndef WL_EXCEPTION_H
#define WL_EXCEPTION_H
#include <exception>
#include <string>

namespace wl {

/**
 * @todo write docs
 */
class exception : public std::exception
{
private:
    std::string message;

public:
    exception() : message() {}
    exception(const char* message) : message(message) {}
    exception(std::string message) : message(std::move(message)) {}

    exception& operator<<(const char* message) { this->message += message; return *this;}
    exception& operator<<(const char c) { this->message += c; return *this;}

    virtual const char* what() const noexcept
    { return message.c_str(); }
};

template<typename T>
T* expect_not_null(T* value, const char* message)
{
    if (value == nullptr) {
        throw wl::exception(message);
    }
    return value;
}

template<typename T>
T expect_not_zero(T value, const char* message)
{
    if (value == 0) {
        throw wl::exception(message);
    }
    return value;
}

}

#endif // WL_EXCEPTION_H
