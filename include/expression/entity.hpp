#ifndef EXPRESSION_ENTITY_HPP_
#define EXPRESSION_ENTITY_HPP_

#include <memory>

namespace expression {

class Entity {
 public:
  explicit virtual operator std::string() const {
    return "<UNDEF ENTITY>";
  }

  virtual bool operator==(const std::shared_ptr<Entity>& entity) const {
    return this == entity.get();
  }

  virtual bool operator!=(const std::shared_ptr<Entity>& entity) const {
    return this != entity.get();
  }

  [[nodiscard]] virtual size_t size() const = 0;
};

}  // namespace expression

#endif  // EXPRESSION_ENTITY_HPP_
