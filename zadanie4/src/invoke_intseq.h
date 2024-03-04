#ifndef INVOKE_INTSEQ_H
#define INVOKE_INTSEQ_H

#include <functional>
#include <utility>
#include <type_traits>
#include <array>

namespace INVOKE_INTSEQ_NAMESPACE {
    template <class T>
    using base_type = typename std::remove_cv_t<typename std::remove_reference_t<T>>;

    template <class>
    struct is_integer_sequence : std::false_type {};

    template <class T, T... Args>
    struct is_integer_sequence<std::integer_sequence<T, Args...>> : std::true_type {};

    template <class T>
    constexpr bool is_integer_sequence_t = is_integer_sequence<base_type<T>>::value;

    // 'value' określa rozmiar tablicy potrzebnej do przechowania wyników dla argumentów o danych typach.
    template <class... Args>
    struct cnt_output_size;

    template <>
    struct cnt_output_size<> {
        static constexpr size_t value = 1;
    };

    template <class T, class... Args>
    struct cnt_output_size<T, Args...> {
        static constexpr size_t value = cnt_output_size<Args...>::value;
    };

    template <class T, T... ints, class... Args>
    struct cnt_output_size<std::integer_sequence<T, ints...>, Args...> {
        static constexpr size_t value = sizeof...(ints) * cnt_output_size<Args...>::value;
    };

    // 'type' reprezentuje std::integral_constant, gdy T jest std::integer_sequence, a w przeciwnym razie jest to T.
    template <class... Args>
    struct get_first_from_intseq;

    template <class T, T first_int, T... ints>
    struct get_first_from_intseq<std::integer_sequence<T, first_int, ints...>> {
        using type = std::integral_constant<T, first_int>;
    };

    template <class T, T... ints>
    struct get_first_from_intseq<std::integer_sequence<T, ints...>> {
        using type = std::integral_constant<T, 0>;
    };

    // Ta specjalizacja dla typu T, niebędącego std::integer_sequence, nie jest używana.
    // Jest zadeklarowana dla umożliwienia użycia std::conditional_t z get_first_from_intseq.
    template <class T>
    struct get_first_from_intseq<T> {
        using type = T;
    };

    template <class T>
    using get_first_from_intseq_t = typename get_first_from_intseq<base_type<T>>::type;

    // Określa typ, na który jest konwertowany T przed wykonaniem std::invoke.
    template <class T>
    using get_type_to_invoke_t = std::conditional_t<is_integer_sequence_t<T>, get_first_from_intseq_t<T>, T>;

    // Tworzy i zwraca std::array typu T i rozmiaru size, inicjalizowany podanymi wartościami args.
    template <class T, size_t size, class... Args>
    constexpr decltype(auto) create_array(Args&&... args) {
        if constexpr (std::is_reference_v<T>) {
            return std::array<std::reference_wrapper<std::remove_reference_t<T>>, size> {args...};
        } else {
            return std::array<T, size> {args...};
        }
    }

    // Tworzy i zwraca std::array typu T, rozmiaru size, wypełniony wartościami default_val.
    // Funkcja powinna być wywoływana bez dodatkowych argumentów args.
    template <class T, size_t size, size_t i, class... Args>
    constexpr decltype(auto) create_array_with_default_val(T&& default_val, Args&&... args) {
        if constexpr (size == i) {
            return create_array<T, size>(std::forward<T>(args)...);
        } else {
            return create_array_with_default_val<T, size, i + 1>(std::forward<T>(default_val), std::forward<T>(default_val), std::forward<T>(args)...);
        }
    }

    // Zwraca pierwszą wartość z argumentu arg. Jeśli arg jest std::integer_sequence, zwraca pierwszą wartość tej sekwencji.
    // W przeciwnym razie zwraca sam argument arg.
    template <class T>
    constexpr decltype(auto) get_first_value(T&& arg) {
        if constexpr (is_integer_sequence_t<T>) {
            return get_first_from_intseq_t<T>{};
        } else {
            return std::forward<T>(arg);
        }
    }

    // Zwraca wynik pierwszego wywołania std::invoke z funkcją f i przekształconymi argumentami args.
    template <class F, class... Args>
    constexpr decltype(auto) get_first_invoke_result(F&& f, Args&&... args){
        return std::invoke(std::forward<F>(f), get_first_value<Args>(std::forward<Args>(args))...);
    }

    // Deklaracje funkcji służących do wywoływania std::invoke z różnymi kombinacjami argumentów.
    // Funkcje calculate_output i calculate_output_to_tab iterują przez wszystkie argumenty,
    // dla każdego std::integer_sequence ekstrahując i używając poszczególnych wartości std::integral_constant w wywołaniu std::invoke.

    // Jeśli funkcja f zwraca wartość (nie jest typu void), wyniki jej działania są zapisywane w tablicy wynikowej OUT, zaczynając od indeksu i.
    // Pomija pozycję 0, gdyż została ona użyta do zainicjowania tablicy.
    template <size_t lvl, size_t max_lvl, class OUT, class F, class Arg, class... Args>
    constexpr typename std::enable_if_t<!is_integer_sequence_t<Arg>, void> calculate_output_to_tab(OUT &tab, size_t &i, F&& f, Arg&& arg, Args&&... args);

    template <size_t lvl, size_t max_lvl, class OUT, class F, class T, T... ints, class... Args>
    constexpr void calculate_output_to_tab(OUT &tab, size_t &i, F&& f, const std::integer_sequence<T, ints...>&, Args&&... args);

    // Przetwarza przypadki, gdy funkcja f zwraca typ void. 
    // W tej sytuacji wywołuje std::invoke z podanymi argumentami, ale nie zapisuje wyników, ponieważ f nie zwraca żadnej wartości.
    template <size_t lvl, size_t max_lvl, class F, class Arg, class... Args>
    constexpr typename std::enable_if_t<!is_integer_sequence_t<Arg>, void> calculate_output(F&& f, Arg&& arg, Args&&... args);

    template <size_t lvl, size_t max_lvl, class F, class T, T... ints, class... Args>
    constexpr void calculate_output(F&& f, const std::integer_sequence<T, ints...>&, Args&&... args);

    // Implementacje funkcji odpowiedzialnych za wywołanie std::invoke.
    template <size_t lvl, size_t max_lvl, class OUT, class F, class Arg, class... Args>
    constexpr typename std::enable_if_t<!is_integer_sequence_t<Arg>, void> calculate_output_to_tab(OUT &tab, size_t &i, F&& f, Arg&& arg, Args&&... args) {
        if constexpr (lvl != max_lvl) {
            calculate_output_to_tab<lvl + 1, max_lvl>(tab, i, std::forward<F>(f), std::forward<Args>(args)..., std::forward<Arg>(arg));
        } else {
            if (i != 0)
                tab[i] = std::invoke(std::forward<F>(f), std::forward<Arg>(arg), std::forward<Args>(args)...);
            i++;
        }
    }

    template <size_t lvl, size_t max_lvl, class OUT, class F, class T, T... ints, class... Args>
    constexpr void calculate_output_to_tab(OUT &tab, size_t &i, F&& f, const std::integer_sequence<T, ints...>&, Args&&... args) {
        (calculate_output_to_tab<lvl, max_lvl>(tab, i, std::forward<F>(f), std::integral_constant<T, ints>{}, std::forward<Args>(args)...), ...);
    }

    template <size_t lvl, size_t max_lvl, class F, class Arg, class... Args>
    constexpr typename std::enable_if_t<!is_integer_sequence_t<Arg>, void> calculate_output(F&& f, Arg&& arg, Args&&... args) {
        if constexpr (lvl != max_lvl) {
            calculate_output<lvl + 1, max_lvl>(std::forward<F>(f), std::forward<Args>(args)..., std::forward<Arg>(arg));
        } else {
            std::invoke(std::forward<F>(f), std::forward<Arg>(arg), std::forward<Args>(args)...);
        }
    }

    template <size_t lvl, size_t max_lvl, class F, class T, T... ints, class... Args>
    constexpr void calculate_output(F&& f, const std::integer_sequence<T, ints...>&, Args&&... args) {
        (calculate_output<lvl, max_lvl>(std::forward<F>(f), std::integral_constant<T, ints>{}, std::forward<Args>(args)...), ...);
    }
}

template <class F, class... Args>
constexpr decltype(auto) invoke_intseq(F&& f, Args&&... args) {
    // Typ zwracany przez funkcję f.
    using result_type = std::invoke_result_t<F, INVOKE_INTSEQ_NAMESPACE::get_type_to_invoke_t<Args>...>;

    // Liczba argumentów ('arg_cnt') oraz liczba wymaganych wywołań funkcji invoke ('output_size').
    constexpr size_t arg_cnt = sizeof...(Args);
    constexpr size_t output_size = INVOKE_INTSEQ_NAMESPACE::cnt_output_size<INVOKE_INTSEQ_NAMESPACE::base_type<Args>...>::value;

    if constexpr ((!INVOKE_INTSEQ_NAMESPACE::is_integer_sequence_t<Args> && ...)) {
        // Obsługa przypadku, gdy wśród argumentów nie ma std::integer_sequence.
        return std::invoke(std::forward<F>(f), std::forward<Args>(args)...);
    } else if constexpr (std::is_void_v<result_type>) {
        // Obsługa przypadku, gdy funkcja f zwraca void (brak zapisu wyników).
        INVOKE_INTSEQ_NAMESPACE::calculate_output<0, arg_cnt>(std::forward<F>(f), std::forward<Args>(args)...);
    } else {
        // Obsługa przypadku, gdy funkcja f zwraca wartość i występuje std::integer_sequence w argumentach.
        if constexpr (output_size == 0) {
            // Obsługa sytuacji z pustym std::integer_sequence w argumentach.
            return INVOKE_INTSEQ_NAMESPACE::create_array<result_type, output_size>();
        } else {
            // Inicjalizacja pierwszego wyniku invoke oraz tworzenie tablicy wynikowej.
            // Tablica wynikowa jest inicjalizowana wartościami z pierwszego wywołania invoke.
            decltype(auto) first_output = INVOKE_INTSEQ_NAMESPACE::get_first_invoke_result(std::forward<F>(f), std::forward<Args>(args)...);
            decltype(auto) output = INVOKE_INTSEQ_NAMESPACE::create_array_with_default_val<result_type, output_size, 0>(std::forward<result_type>(first_output));

            size_t i = 0;
            INVOKE_INTSEQ_NAMESPACE::calculate_output_to_tab<0, arg_cnt>(output, i, std::forward<F>(f), std::forward<Args>(args)...);

            return output;
        }
    }
}

#endif /* INVOKE_INTSEQ_H */