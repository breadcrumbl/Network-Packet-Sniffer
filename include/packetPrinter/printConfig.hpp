#pragma once

// Space between columns of info displayed
// constexpr -> value known at runtime
// inline   -> variables which are allowed to be defined in multiple files without breaking the ODR, so long as those definitions are identical
//          -> work by telling compiler to replace ever instance of print_space with 4 
//          -> historically connected to being exemot from ODR due to inline function rules
//          -> external linkage by definition (linker can see them so can check definitions match)
namespace PrintConfig {
    inline constexpr int print_space { 4 };


}

namespace ColumnWidth {
    inline constexpr int time { 19 };
}
