#pragma once

#include "fibonacci.h"
#include "typelist.h"


//GEN_LINEAR_HIERARCHY
template <
    class TList,
    template <class AtomicType,class Base> class Unit,
    class Root = NullType
>
class GenLinearHierarchy;

template <
    class Head,
    template <class,class> class Unit,
    class Root,
    class ...Tail
>
class GenLinearHierarchy<Typelist<Head,Tail...>,Unit,Root>
    : public Unit<Head, GenLinearHierarchy<Typelist<Tail...>, Unit, Root>>
{};

template <
    class T,
    template <class,class> class Unit,
    class Root
>
class GenLinearHierarchy<Typelist<T>,Unit,Root>
    : public Unit<T,Root>
{};

//unit
template <class T, class Base>
struct BaseHolder: Base {
    T value;
};

//GEN_SCATTER_HIERARCHY (не нужна)
template <class TList, template <class> class Unit>
class GenScatterHierarchy;

template <class Head, template <class> class Unit, class ...Tail>
class GenScatterHierarchy<Typelist<Head, Tail...>, Unit>
    : public GenScatterHierarchy<Head, Unit>
    , public GenScatterHierarchy<Typelist<Tail...>, Unit>
{};

template <class AtomicType, template <class> class Unit>
class GenScatterHierarchy: Unit<AtomicType>
{};

template <template <class> class Unit>
class GenScatterHierarchy<Typelist<>, Unit> {};

//unit из учебника
template <class T>
struct Holder {
    T value;
};

//GEN_FIB_HIERARCHY

template <class TList, unsigned int N, template <class,class> class Unit>
class GenMixedHierarchy
    : public GenLinearHierarchy< typename GetFirstN<TList, Fibonacci<N>::value + 1>::result, Unit>
    , public GenMixedHierarchy< typename RemoveFirstN<TList, Fibonacci<N>::value + 1>::result, N+1, Unit>
{};

template <unsigned int N, template <class,class> class Unit>
class GenMixedHierarchy<Typelist<>, N, Unit> {};

template <class TList, template <class,class> class Unit>
using GenFibHierarchy = GenMixedHierarchy<TList, 0, Unit>;
