#ifndef RTYPE_LAMBDA_TRAITS_H_
#define RTYPE_LAMBDA_TRAITS_H_

#include <tuple>

// Thanks to https://stackoverflow.com/questions/7943525/
// is-it-possible-to-figure-out-the-parameter-type-and-return-type-of-a-lambda?rq=1

template <typename>
struct function_traits;

template <typename T>
struct function_traits : public function_traits<decltype(&T::operator())> {
};

// Specialization for pointers to member function or lambdas
template <typename ClassType, typename ReturnType, typename... Args>
struct function_traits<ReturnType (ClassType::*)(Args...) const>
{
    enum { arity = sizeof...(Args) };
    // arity is the number of arguments.

    typedef ReturnType result_type;

    template <size_t i>
    struct arg {
        typedef typename std::tuple_element<i, std::tuple<Args...>>::type type;
        // the i-th argument is equivalent to the i-th tuple element of a tuple
        // composed of those arguments.
    };
};

// Specialization for function pointers
template <typename ReturnType, typename... Args>
struct function_traits<ReturnType (*)(Args...)>
{
    enum { arity = sizeof...(Args) };

    typedef ReturnType result_type;

    template <size_t i>
    struct arg {
        typedef typename std::tuple_element<i, std::tuple<Args...>>::type type;
    };
};

#endif // RTYPE_LAMBDA_TRAITS_H_
