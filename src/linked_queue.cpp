#include "linked_queue.hpp"

#include <stdexcept>  // logic_error

namespace itis {

void LinkedQueue::Enqueue(Element e) {
  if (size_ == 0) {
    auto node = new SinglyNode(e, nullptr);
    front_ = node;
    back_ = node;
    size_ = 1;
  } else {
    auto node = new SinglyNode(e, nullptr);
    back_->next = node;
    back_ = node;
    size_++;
  }
}

void LinkedQueue::Dequeue() {
  if (size_ == 0) {
    throw std::logic_error("could not dequeue from empty queue");
  }

  if (size_ == 1) {
    delete front_;
    front_ = nullptr;
    back_ = nullptr;
    size_ = 0;
  } else {
    auto temp = front_->next;
    delete front_;
    front_ = temp;
    size_--;
  }
}

void LinkedQueue::Clear() {
  auto curr = front_;
  for (int i = 0; i < size_; ++i) {
    auto temp = curr -> next;
    delete curr;
    curr = temp;
  }
  delete curr;
  size_ = 0;
  front_ = nullptr;
  back_ = nullptr;
}

// === РЕАЛИЗОВАНО ===

LinkedQueue::~LinkedQueue() {
  Clear();
}

std::optional<Element> LinkedQueue::front() const {
  return front_ == nullptr ? std::nullopt : std::make_optional(front_->data);
}

std::optional<Element> LinkedQueue::back() const {
  return back_ == nullptr ? std::nullopt : std::make_optional(back_->data);
}

bool LinkedQueue::IsEmpty() const {
  return size_ == 0;
}
int LinkedQueue::size() const {
  return size_;
}

// === НЕОБХОДИМО ДЛЯ ТЕСТИРОВАНИЯ ===

std::ostream &operator<<(std::ostream &os, const LinkedQueue &queue) {
  os << "size: " << queue.size_ << '\n';
  for (auto current_node = queue.front_; current_node != nullptr; current_node = current_node->next) {
    if (current_node == queue.front_) os << "[FRONT] ";
    if (current_node == queue.back_) os << "[BACK] ";
    os << enum2str(current_node->data) << '\n';
  }
  return os;
}

}  // namespace itis