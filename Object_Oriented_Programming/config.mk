# Directory containing test files
TEST_PATH     := test
# Space-separated list of header files (e.g., algebra.hpp)
HEADERS       := emergency.hpp
# Space-separated list of implementation files (e.g., algebra.cpp)
IMPLEMS       := emergency.cpp
# File containing main
DRIVER        := tuffyaid.cpp
# Expected name of executable file
EXECFILE      := tuffyaid
CLANGTDY_CHKS := *,-google-build-using-namespace,-fuchsia-default-arguments,-llvm-header-guard,-google-runtime-int,-cppcoreguidelines-pro-type-member-init,-hicpp-member-init,-cppcoreguidelines-pro-bounds-pointer-arithmetic,-cppcoreguidelines-pro-bounds-constant-array-index,-cppcoreguidelines-pro-bounds-array-to-pointer-decay,-hicpp-no-array-decay,-google-runtime-references,-cppcoreguidelines-avoid-magic-numbers,-cppcoreguidelines-avoid-c-arrays,-modernize-avoid-c-arrays,-readability-magic-numbers,-hicpp-avoid-c-arrays,-bugprone-too-small-loop-variable,-modernize-pass-by-value,-modernize-use-default-member-init,-modernize-use-nodiscard,-cppcoreguidelines-owning-memory,-hicpp-use-auto,-modernize-use-auto
