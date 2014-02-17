#include "Mocks.hpp"

TEST(Attribute, CanMakeCustomAttribute) {
    auto attr = attribute::make<std::int32_t>("custom", 42);
    EXPECT_EQ("custom", attr.first);
    EXPECT_EQ(42, boost::get<std::int32_t>(attr.second.value));
}

TEST(Attribute, TimestampIsEventAttribute) {
    log::attribute_pair_t pair = (keyword::timestamp() = timeval{ 0, 0 });
    EXPECT_EQ(log::attribute::scope::event, pair.second.scope);
}

namespace testing {

enum class level { debug };

} // namespace testing

TEST(Attribute, SeverityIsEventAttribute) {
    log::attribute_pair_t pair = (keyword::severity<testing::level>() = testing::level::debug);
    EXPECT_EQ(log::attribute::scope::event, pair.second.scope);
}

TEST(Attribute, MessageIsEventAttribute) {
    log::attribute_pair_t pair = (keyword::message() = "le message");
    EXPECT_EQ(log::attribute::scope::event, pair.second.scope);
}
