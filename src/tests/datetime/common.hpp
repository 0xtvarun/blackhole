#pragma once

#include <string>

#include <blackhole/detail/datetime.hpp>

#include "../global.hpp"

class generator_test_case_t : public Test {
protected:
    std::tm tm;
    suseconds_t usec;

    void SetUp() {
        tm = std::tm();
        usec = 0;
    }

    std::string generate(const std::string& pattern) const {
        std::string str;
        blackhole::aux::attachable_basic_ostringstream<char> stream(str);
        blackhole::aux::datetime::generator_t generator =
                blackhole::aux::datetime::generator_factory_t::make(pattern);
        generator(stream, tm, usec);
        return stream.str();
    }
};

namespace common {

template<std::size_t N>
inline std::string using_strftime(const char(&format)[N], const std::tm& tm) {
    char buffer[128];
    std::size_t ret = std::strftime(buffer, sizeof(buffer), format, &tm);
    BOOST_ASSERT(ret > 0);

    return buffer;
}

} // namespace common
