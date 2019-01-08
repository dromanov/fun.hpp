/*******************************************************************************
 * This file is part of the "https://github.com/blackmatov/fun.hpp"
 * For conditions of distribution and use, see copyright notice in LICENSE.md
 * Copyright (C) 2019, by Matvey Cherevko (blackmatov@gmail.com)
 ******************************************************************************/

#pragma once
#include "_instances.hpp"

#include "../types/all.hpp"
#include "../types/any.hpp"
#include "../types/sum.hpp"
#include "../types/product.hpp"

#include "../types/box.hpp"
#include "../types/maybe.hpp"

#include "../classes/ord.hpp"

namespace fun
{
    //
    // arithmetic types
    //

    template < typename A >
    struct ord_inst_t<A,
        std::enable_if_t<
            std::is_arithmetic<A>::value, A>
        > : ord_inst_t<A>
    {
        static constexpr bool instance = true;
        static bool less(A l, A r) {
            return l < r;
        }
    };

    //
    // all_t
    //

    template <>
    struct ord_inst_t<all_t, all_t> : ord_inst_t<all_t> {
        static constexpr bool instance = true;
        static bool less(const all_t& l, const all_t& r) {
            return l.get_all() < r.get_all();
        }
    };

    //
    // any_t
    //

    template <>
    struct ord_inst_t<any_t, any_t> : ord_inst_t<any_t> {
        static constexpr bool instance = true;
        static bool less(const any_t& l, const any_t& r) {
            return l.get_any() < r.get_any();
        }
    };

    //
    // sum_t
    //

    template < typename A >
    struct ord_inst_t<sum_t<A>,
        std::enable_if_t<
            ord_t::instance<A>, sum_t<A>>
        > : ord_inst_t<sum_t<A>>
    {
        static constexpr bool instance = true;
        static bool less(const sum_t<A>& l, const sum_t<A>& r) {
            return ord_f::less(l.get_sum(), r.get_sum());
        }
    };

    //
    // product_t
    //

    template < typename A >
    struct ord_inst_t<product_t<A>,
        std::enable_if_t<
            ord_t::instance<A>, product_t<A>>
        > : ord_inst_t<product_t<A>>
    {
        static constexpr bool instance = true;
        static bool less(const product_t<A>& l, const product_t<A>& r) {
            return ord_f::less(l.get_product(), r.get_product());
        }
    };

    //
    // box_t
    //

    template < typename A >
    struct ord_inst_t<box_t<A>,
        std::enable_if_t<
            ord_t::instance<A>, box_t<A>>
        > : ord_inst_t<box_t<A>>
    {
        static constexpr bool instance = true;
        static bool less(const box_t<A>& l, const box_t<A>& r) {
            return ord_f::less(*l, *r);
        }
    };

    //
    // maybe_t
    //

    template < typename A >
    struct ord_inst_t<maybe_t<A>,
        std::enable_if_t<
            ord_t::instance<A>, maybe_t<A>>
        > : ord_inst_t<maybe_t<A>>
    {
        static constexpr bool instance = true;
        static bool less(const maybe_t<A>& l, const maybe_t<A>& r) {
            return
                (l.is_just() < r.is_just()) ||
                (l.is_just() && r.is_just() && ord_f::less(*l, *r));
        }
    };
}
