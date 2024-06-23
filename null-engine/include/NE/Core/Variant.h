#pragma once

namespace null
{
    template <typename... Ts>
    struct VariantVisitor : Ts...
    {
        using Ts::operator() ...;
    };
    template <class... Ts>
    VariantVisitor(Ts...) -> VariantVisitor<Ts...>;
}
