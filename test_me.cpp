#include "overload.h"
#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include <catch.hpp>
#include <eggs/variant.hpp>
#include <string>
#include <type_traits>

using std::string;
using eggs::variant;
using eggs::variants::apply;

using namespace std::string_literals;

template<typename T>
concept bool Numeric = (std::is_same<int,T>::value || std::is_same<double,T>::value);

template <typename T> concept bool Appendable() {
  return requires(T & t, const T &u) {
    { t.append(u) }
    ->T &;
  };
}

TEST_CASE("concept-based dispatch works") 
{
  using v_t = variant<int,double,string>;

  auto o = overload([](Numeric n) { return n + n; },
                    [](Appendable s) { return s.append(s); });

  SECTION("int") {
    auto rv = apply<variant<int, double, string>>(o, v_t(10));
    REQUIRE(rv == 20);
  }

  SECTION("double") {
    auto rv = apply<variant<int, double, string>>(o, v_t(0.25));
    REQUIRE(rv == 0.5);
  }
  
  SECTION("string") {
    auto rv = apply<variant<int, double, string>>(o, v_t("foo"));
    REQUIRE(rv == "foofoo"s);
  }
}
