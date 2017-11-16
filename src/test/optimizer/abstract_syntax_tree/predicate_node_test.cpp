#include <memory>

#include "gtest/gtest.h"

#include "base_test.hpp"

#include "optimizer/abstract_syntax_tree/predicate_node.hpp"
#include "optimizer/abstract_syntax_tree/stored_table_node.hpp"

namespace opossum {

class PredicateNodeTest : public BaseTest {
 protected:
  void SetUp() override {
    StorageManager::get().add_table("table_a", load_table("src/test/tables/int_float_double_string.tbl", 2));

    _table_node = std::make_shared<StoredTableNode>("table_a");
  }

  std::shared_ptr<StoredTableNode> _table_node;
};

TEST_F(PredicateNodeTest, Descriptions) {
  auto predicate_a = std::make_shared<PredicateNode>(ColumnID{0}, ScanType::OpEquals, 5);
  predicate_a->set_left_child(_table_node);
  EXPECT_EQ(predicate_a->description(), "[Predicate] table_a.i = 5");

  auto predicate_b = std::make_shared<PredicateNode>(ColumnID{1}, ScanType::OpNotEquals, 2.5);
  predicate_b->set_left_child(_table_node);
  EXPECT_EQ(predicate_b->description(), "[Predicate] table_a.f != 2.5");

  auto predicate_c = std::make_shared<PredicateNode>(ColumnID{2}, ScanType::OpBetween, 2.5, 10.0);
  predicate_c->set_left_child(_table_node);
  EXPECT_EQ(predicate_c->description(), "[Predicate] table_a.d BETWEEN 2.5 AND 10");

  auto predicate_d = std::make_shared<PredicateNode>(ColumnID{3}, ScanType::OpEquals, "test");
  predicate_d->set_left_child(_table_node);
  EXPECT_EQ(predicate_d->description(), "[Predicate] table_a.s = test");
}

}  // namespace opossum