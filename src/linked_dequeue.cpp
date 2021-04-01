#include "linked_dequeue.hpp"

#include <stdexcept>  // logic_error

namespace itis {

void LinkedDequeue::Enqueue(Element e) {
  if (size_ == 0) {
    auto node = new DoublyNode(e, nullptr, nullptr);
    front_ = node;
    back_ = node;
    size_ = 1;
  } else {
    auto node = new DoublyNode(e, back_, nullptr);
    back_->next = node;
    back_ = node;
    size_++;
  }
}

void LinkedDequeue::EnqueueFront(Element e) {
  if (size_ == 0) {
    auto node = new DoublyNode(e, nullptr, nullptr);
    front_ = node;
    back_ = node;
    size_ = 1;
  } else {
    auto node = new DoublyNode(e, nullptr, front_);
    front_->previous = node;
    front_ = node;
    size_++;
  }
}

void LinkedDequeue::Dequeue() {
  if (size_ == 0) {
    throw std::logic_error("cannot not dequeue from empty queue");
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
    front_->previous = nullptr;
    size_--;
  }
}

void LinkedDequeue::DequeueBack() {
  if (size_ == 0) {
    throw std::logic_error("cannot not dequeue from empty queue");
  }

  if (size_ == 1) {
    delete front_;
    front_ = nullptr;
    back_ = nullptr;
    size_ = 0;
  } else {
    auto temp = back_->previous;
    delete back_;
    back_ = temp;
    back_->next = nullptr;
    size_--;
  }
}

void LinkedDequeue::Clear() {
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

LinkedDequeue::~LinkedDequeue() {
  Clear();
}

std::optional<Element> LinkedDequeue::front() const {
  return front_ == nullptr ? std::nullopt : std::make_optional(front_->data);
}

std::optional<Element> LinkedDequeue::back() const {
  return back_ == nullptr ? std::nullopt : std::make_optional(back_->data);
}

bool LinkedDequeue::IsEmpty() const {
  return size_ == 0;
}

int LinkedDequeue::size() const {
  return size_;
}

// === НЕОБХОДИМО ДЛЯ ТЕСТИРОВАНИЯ ===

std::ostream &operator<<(std::ostream &os, const LinkedDequeue &queue) {
  os << "size: " << queue.size_ << '\n';
  for (auto current_node = queue.front_; current_node != nullptr; current_node = current_node->previous) {
    if (current_node == queue.front_) os << "[FRONT] ";
    if (current_node == queue.back_) os << "[BACK] ";
    os << enum2str(current_node->data) << '\n';
  }
  return os;
}

}  // namespace itis
