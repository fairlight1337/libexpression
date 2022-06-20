#ifndef EXPRESSION_ENTITY_HPP_
#define EXPRESSION_ENTITY_HPP_

#include <memory>

namespace expression {

class Entity {
 public:
  virtual operator std::string() const {
    return "<UNDEF ENTITY>";
  }

  virtual bool operator==(std::shared_ptr<Entity> entity) const {
    return this == entity.get();
  }

  virtual bool operator!=(std::shared_ptr<Entity> entity) const {
    return this != entity.get();
  }

  virtual size_t size() const = 0;
};

}  // namespace expression

#endif  // EXPRESSION_ENTITY_HPP_
