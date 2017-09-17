#ifndef __HAZ_TYPE_HELPER
#define __HAZ_TYPE_HELPER

#include <haz/Tools/Macro.hpp>

/*
    TypeDisplayer<...>
        Show at compile time types
            ex: TypeDisplayer<...> t;

    TypeList<...>
        Represent a list of type
        ::size size of the list
            ex: using myList = TypeList<int, double>;

    TypeListRepeat<unsigned int N, ...>
        TypeList<..., ..., ...> // n times

    TypeListConcat<TypeList<...>, TypeList<...>>
        TypeList<..., ...>
        Concat the 2 list
            ex: using concat_list = TypeListConcat<TypeList<int, double>, TypeList<long>>; // <=> TypeList<int, double, long>

    TypeListFlatten<...>
        concat all type into a TypeList, if there is any TypeList<...>, it's flatten
            ex: TypeListFlattent<int, TypeList<double>, long> // <=> TypeList<int, double, long>

    TypeListAdd<TypeList<...>, ...>
        TypeList<..., ...>
        Same as TypeListFlatten<TypeList<...>, ...>

    TypeListRemove<TypeList<...>, ...>
        all type in the second parameter pack is remove from the TypeList
            ex: TypeListRemove<TypeList<int, double, long, int>, double, int> // <=> TypeList<long>

    TypeListRemoveAt<unsigned int P, TypeList<...>>
        Remove the Pnth element of the list
            ex: TypeListRemoveAt<1, TypeList<int, double, long>> // <=> TypeList<int, long>

    TypeListAddAt<unsigned int P, T, TypeList<...>>
        Add T at the Pnth element of the list
            ex: TypeListAddAt<1, int, TypeList<double, long, short>> // <=> TypeList<double, int, long, short>

    TypeListCut<unsigned int LB, unsigned int HB, TypeList<...>>
        TypeList with all type of the TypeList<...> in the index range [LB, HB[
        TypeListCut<0, TypeList<...>::size, TypeList<...>> is equivalent to TypeList<...>
            ex: TypeListCut<1, 3, TypeList<int, double, long, short, char>> // <=> TypeList<double, long>

    TypeAt<unsigned int P, TypeList<...>>
        Alias of type at the position P in the list
            ex: using my_int = TypeAt<1, TypeList<double, int, long>>

    Rank<P, N>
        Represent a rank, can be use to keep track ot the position in a list of N element
        Rank<P, N> is child of Rank<P+1, N>, it means that every Rank before the position P can be replace bu that position P 
        Error is throw if P >= N
        ::rank alias of P
            ex: using myRank = Rank<0, TypeList<int, double>::size>;

    TypeIn<T, TypeList<...>>
        check if a type is in the list
            ex: bool has_int = TypeIn<int, TypeList<int, double, long>>;

    TypeE<T>
        ::type alias of T
            ex: using self_type = Type<decltype(*this)>;
*/

BEG_NAMESPACE_HAZ
BEG_NAMESPACE_NESTED_HIDDEN
template<typename ListA, typename ListB>                    struct TypeListConcatHelper;
template<unsigned int N, typename...Args>                   struct TypeListRepeatHelper;
template<typename...Args>                                   struct TypeListFlattenHelper;
template<unsigned int P, typename A, typename ...Args>      struct TypeAtHelper;
template<unsigned int P, typename List>                     struct TypeAtHelper_;
template<typename T, typename...Args>                       struct TypeInHelper;
template<typename T, typename List>                         struct TypeInHelper_;
END_NAMESPACE_NESTED_HIDDEN

/* ==================== TypeDisplayer */
template<typename... Args>
struct TypeDisplayer;

/* ==================== TypeList */
template<typename... Args>
struct TypeList { static constexpr unsigned int size = sizeof...(Args); };

/* ==================== TypeIn */
template<typename T, typename TypeL>
constexpr bool TypeIn = NS_HAZ_HIDDEN::TypeInHelper_<T, TypeL>::value;

/* ==================== TypeListConcat */
template<typename ListA, typename ListB>
using TypeListConcat = typename NS_HAZ_HIDDEN::TypeListConcatHelper<ListA, ListB>::type;

/* ==================== TypeListRepeat */
template<unsigned int N, typename...Args>
using TypeListRepeat = typename NS_HAZ_HIDDEN::TypeListRepeatHelper<N, Args...>::type;

/* ==================== TypeListFlatten */
template<typename...Args>
using TypeListFlatten = typename NS_HAZ_HIDDEN::TypeListFlattenHelper<Args...>::type;

/* ==================== TypeAT */
template<unsigned int P, typename TypeL>
using TypeAt = typename NS_HAZ_HIDDEN::TypeAtHelper_<P, TypeL>::type;

/* ==================== TypeE */
template<typename E>
struct TypeE { using type = E; };

/* ==================== Rank */
template<unsigned int P, unsigned int N>
struct Rank : public Rank<P + 1, N> { static constexpr unsigned int rank = P; };
template<unsigned int N>
struct Rank<N, N> { static constexpr unsigned int rank = N; };






BEG_NAMESPACE_NESTED_HIDDEN

template<typename... ArgsA, typename... ArgsB>
struct TypeListConcatHelper<TypeList<ArgsA...>, TypeList<ArgsB...>> {
    using type = TypeList<ArgsA..., ArgsB...>;
};





template<unsigned int N, typename...Args>
struct TypeListRepeatHelper {
    using type = TypeListConcat<TypeList<Args...>, typename TypeListRepeatHelper<N-1, Args...>::type>;
};

template<typename...Args>
struct TypeListRepeatHelper<0, Args...> {
    using type = TypeList<>;
};







template<typename A, typename...Args>
struct TypeListFlattenHelper<A, Args...> {
        using type = TypeListConcat<typename TypeListFlattenHelper<A>::type, typename TypeListFlattenHelper<Args...>::type>;
};

template<typename A>
struct TypeListFlattenHelper<A> {
    using type = TypeList<A>;
};

template<typename... Args>
struct TypeListFlattenHelper<TypeList<Args...>> {
    using type = TypeList<Args...>;
};






template<unsigned int P, typename A, typename ...Args>
struct TypeAtHelper {
    static_assert(P < TypeList<A, Args...>::size, "Position is not in list range");
    using type = typename TypeAtHelper<P - 1, Args...>::type;
};

template<typename A, typename...Args>
struct TypeAtHelper<0, A, Args...> {
    using type = A;
};

template<unsigned int P, typename...Args>
struct TypeAtHelper_<P, TypeList<Args...>> {
    static_assert(P < TypeList<Args...>::size, "Position is not in list range");
    using type = typename TypeAtHelper<P, Args...>::type;
};






template<typename T, typename A, typename...Args>
struct TypeInHelper<T, A, Args...> {
    static constexpr bool value = std::is_same<T, A>::value || TypeInHelper<T, Args...>::value;
};

template<typename T, typename A>
struct TypeInHelper<T, A> {
    static constexpr bool value = std::is_same<T, A>::value;
};

template<typename T>
struct TypeInHelper<T> {
    static constexpr bool value = false;
};

template<typename T, typename...Args>
struct TypeInHelper_<T, TypeList<Args...>> {
    static constexpr bool value = TypeInHelper<T, Args...>::value;
};





END_NAMESPACE_NESTED_HIDDEN
END_NAMESPACE_HAZ

#endif