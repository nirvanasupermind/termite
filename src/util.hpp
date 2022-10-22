// -*- util.hpp -*-
// Part of the Termite project, under the MIT License.

#ifndef UTIL_HPP
#define UTIL_HPP

#include <iostream>
#include <exception>

namespace termite
{
    // Dummy constructor label
    enum NativeInt { native_int };
    enum Sept { sept };

    // Logs a value
    #define LOG_(value) std::cout << #value << " = " << (value) << '\n';

} // namespace termite

#endif // UTIL_HPP