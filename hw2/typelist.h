#pragma once
#include <iostream>

struct NullType{};

template <class ...Args>
struct Typelist;

template <class T, class ...Args>
struct Typelist<T,Args...> {
    typedef T head;
    typedef Typelist<Args...> tail;
};

template <>
struct Typelist<> {};

// LENGTH
template <class TList>
struct Length;

template <>
struct Length <Typelist<>> : std::integral_constant<unsigned int, 0> {};

template <class T, class ...Args>
struct Length<Typelist<T, Args...>>:
    std::integral_constant<unsigned int,
        1 + Length<Typelist<Args...>>::value >
{};

// PUSH_FRONT
template <class TList, class T>
struct PushFront;

template <class T>
struct PushFront<Typelist<>, T>
{
    typedef Typelist<T> result;
};

template <class Tlist>
struct PushFront<Tlist, NullType>{
    typedef Tlist result;
};

template <class T, class ...Args>
struct PushFront<Typelist<Args...>, T>
{
    typedef Typelist<T, Args...> result;
};

// TERNARY_OPERATOR(не нужен)
template <bool B, class T, class U>
struct Ternary;

template <class T, class U>
struct Ternary<true,T,U> {
    typedef T result;
};

template <class T, class U>
struct Ternary<false,T,U> {
    typedef U result;
};

// POP_FRONT
template <class TList>
struct PopFront;

template<>
struct PopFront< Typelist<> > {
    typedef NullType result;
};

template <class T, class ...Args>
struct PopFront< Typelist<T, Args...> > {
    typedef T result;
};

//GET_FIRST_N_TYPES если не хватает возвращает что есть
template <class TList, unsigned int N>
struct GetFirstN;

template <unsigned int N, class ...Args>
struct GetFirstN<Typelist<Args...>,N> {
    typedef
        typename PushFront<
        typename GetFirstN< typename Typelist<Args...>::tail, N-1 >::result,
        typename Typelist<Args...>::head
    >::result
    result;
};

template <class ...Args>
struct GetFirstN<Typelist<Args...>, 0> {
    typedef Typelist<> result;
};

template<unsigned int N>
struct GetFirstN<Typelist<>, N> {
    typedef Typelist<> result;
};

template <>
struct GetFirstN<Typelist<>,0> {
    typedef Typelist<> result;
};

//PRINT
template <typename TList>
void print() {
    std::cout << typeid(typename TList::head).name() << " ";
    print<typename TList::tail>();
};

template <>
void print<Typelist<>>() {
    std::cout << "end\n";
    return;
}

// REMOVE_FIRST_N_TYPES
template <class TList, unsigned int N>
struct RemoveFirstN;

template <unsigned int N, class ...Args>
struct RemoveFirstN<Typelist<Args...>,N> {
    typedef typename RemoveFirstN<typename Typelist<Args...>::tail, N-1>::result result;
};

template <class ...Args>
struct RemoveFirstN<Typelist<Args...>, 0> {
    typedef Typelist<Args...> result;
};

template <unsigned int N>
struct RemoveFirstN<Typelist<>,N> {
    typedef Typelist<> result;
};

template <>
struct RemoveFirstN<Typelist<>,0> {
    typedef Typelist<> result;
};
