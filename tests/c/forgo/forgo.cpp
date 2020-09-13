#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <gos/forgo.h>

#define GOS_EX_FOR_GO_BUFFER_SIZE 1024

namespace gos {
namespace examples {
namespace forgo {

TEST(GosForGoTest, Greet) {
  int result;
  char buffer[GOS_EX_FOR_GO_BUFFER_SIZE];

  result = gos_for_go_greet(buffer, GOS_EX_FOR_GO_BUFFER_SIZE, "Orri", 1971);
  EXPECT_EQ(46, result);
  EXPECT_STREQ("Greetings, Orri from 1971! We come in peace :)", buffer);
}

TEST(GosForGoTest, GreetWithStructure) {
  int result;
  char buffer[GOS_EX_FOR_GO_BUFFER_SIZE];
  GosForGoGreetee greetee;
  greetee.buffer = buffer;
  greetee.size = GOS_EX_FOR_GO_BUFFER_SIZE;
  greetee.name = "Orri";
  greetee.year = 1971;

  result = gos_for_go_greet_st(&greetee);
  EXPECT_EQ(46, result);
  EXPECT_STREQ("Greetings, Orri from 1971! We come in peace :)", buffer);
}

} // namespace forgo
} // namespace examples
} // namespace gos
