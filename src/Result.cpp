#include "Result.hpp"
#include <utility>

namespace lab_6
{

Result<void>::Result() noexcept : exp_() {}
Result<void>::Result(IndexError error) noexcept : exp_(std::unexpected(std::move(error))) {}

bool Result<void>::has_value() const noexcept
{
    return exp_.has_value();
}

void Result<void>::value() const
{
    exp_.value();
}
const IndexError& Result<void>::error() const&
{
    return exp_.error();
}

} // namespace lab6
