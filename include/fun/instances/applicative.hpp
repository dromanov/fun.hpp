/*******************************************************************************
 * This file is part of the "https://github.com/blackmatov/fun.hpp"
 * For conditions of distribution and use, see copyright notice in LICENSE.md
 * Copyright (C) 2019, by Matvey Cherevko (blackmatov@gmail.com)
 ******************************************************************************/

#pragma once
#include "_instances.hpp"

#include <functional>
#include <type_traits>

#include "../types/box.hpp"
#include "../types/maybe.hpp"

#include "../instances/functor.hpp"
#include "../classes/applicative.hpp"

namespace fun
{
    template <>
    struct applicative_inst_t<box_t, box_t> : applicative_inst_t<box_t> {
        static constexpr bool instance = true;

        template < typename A >
        static box_t<A> pure(const A& a) {
            return make_box(a);
        }

        template < typename A, typename F, typename B = std::invoke_result_t<F,A> >
        static box_t<B> apply(const box_t<F>& f, const box_t<A>& v) {
            static_assert(
                std::is_convertible<F, std::function<B(A)>>::value,
                "apply requires a function type (A -> B)");
            return make_box((*f)(*v));
        }
    };

    template <>
    struct applicative_inst_t<maybe_t, maybe_t> : applicative_inst_t<maybe_t> {
        static constexpr bool instance = true;

        template < typename A >
        static maybe_t<A> pure(const A& a) {
            return make_just(a);
        }

        template < typename A, typename F, typename B = std::invoke_result_t<F,A> >
        static maybe_t<B> apply(const maybe_t<F>& f, const maybe_t<A>& v) {
            static_assert(
                std::is_convertible<F, std::function<B(A)>>::value,
                "apply requires a function type (A -> B)");
            return (f.is_just() && v.is_just())
                ? make_just((*f)(*v))
                : make_nothing<B>();
        }
    };
}