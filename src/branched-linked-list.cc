#include "branched-linked-list.hpp"

BLL::BLL(const BLL& to_copy) {
  if (to_copy.head_ == nullptr) {
    return;
  }
  unsigned int counter = 0;
  Node* current = to_copy.head_;
  while (current != nullptr) {
    PushBack(current->data_);
    if (current->next_bll_ != nullptr) {
      BLL* branch = new BLL(*current->next_bll_);
      Join(counter, branch);
    }
    counter++;
    current = current->next_node_;
  }
}
/* void BLL::DeleteBranch(BLL* temp) {
  while (temp->head_ != nullptr) {
    Node* next = temp->head_->next_node_;
    delete temp->head_;
    temp->head_ = next;
  }
} */
BLL::~BLL() {
  if (head_ == nullptr) {
    return;
  }
  Node* current = head_;
  while (current != nullptr) {
    // if (current->next_bll_ != nullptr) {
    delete current->next_bll_;
    //}
    current = current->next_node_;
  }
  while (head_ != nullptr) {
    Node* next = head_->next_node_;
    delete head_;
    head_ = next;
  }
  head_ = nullptr;
}

BLL& BLL::operator=(const BLL& rhs) {
  if (this == &rhs) {
    return *this;
  }
  if ((head_ != nullptr)) {
    Node* current = head_;
    while (current != nullptr) {
      // if (current->next_bll_ != nullptr) {
      delete current->next_bll_;
      //}
      current = current->next_node_;
    }
    while (head_ != nullptr) {
      Node* next = head_->next_node_;
      delete head_;
      head_ = next;
    }
    head_ = nullptr;
  }
  if (!(rhs.head_ == nullptr)) {
    Node* current = rhs.head_;
    unsigned int counter = 0;
    while (current != nullptr) {
      PushBack(current->data_);
      if (current->next_bll_ != nullptr) {
        // std::cout << current->next_bll_->ToString() << std::endl;
        BLL* branch = new BLL(*current->next_bll_);
        // std::cout << branch->ToString() << std::endl;
        Join(counter, branch);
      }
      counter++;
      current = current->next_node_;
    }
  }
  return *this;
}

Node* BLL::PushBack(char dat) {
  if (head_ == nullptr) {
    head_ = new Node(dat);
    return head_;
  }
  Node* current = head_;
  while (current != nullptr) {
    if (current->next_node_ == nullptr) {
      current->next_node_ = new Node(dat);
      break;
    }
    current = current->next_node_;
  }
  return current->next_node_;
}

char BLL::GetAt(size_t idx) const {
  if (head_ == nullptr) {
    throw std::invalid_argument("head_ is nullptr GetAt");
  }
  if (idx < 0 || idx >= Size()) {
    throw std::invalid_argument("idx out of bounds GetAt");
  }
  Node* current = head_;
  char toreturn = 'a';
  unsigned int stepper = 0;
  while (current != nullptr) {
    if (stepper == idx) {
      toreturn = current->data_;
      break;
    }
    stepper++;
    if (current->next_bll_ != nullptr) {
      toreturn = current->next_bll_->GetAt((idx - stepper));
    }
    current = current->next_node_;
  }
  return toreturn;
}
void BLL::SetAt(size_t idx, char dat) {
  if (head_ == nullptr) {
    throw std::invalid_argument("head_ is nullptr SetAt");
  }
  if (idx < 0 || idx >= Size()) {
    throw std::invalid_argument("idx out of bounds SetAt");
  }
  Node* current = head_;
  unsigned int stepper = 0;
  while (current != nullptr) {
    if (stepper == idx) {
      current->data_ = dat;
      break;
    }
    stepper++;
    if (current->next_bll_ != nullptr) {
      current->next_bll_->SetAt((idx - stepper), dat);
    }
    current = current->next_node_;
  }
}
void BLL::Join(size_t idx, BLL* list) {
  if (head_ == nullptr) {
    throw std::invalid_argument("a");
  }
  if (idx < 0 || idx > Size()) {
    throw std::invalid_argument("idx out of bounds JOIN");
  }
  if (!(IsBLLAcyclic())) {
    throw std::invalid_argument("cyclic list");
  }
  Node* current = head_;
  unsigned int stepper = 0;
  while (current != nullptr) {
    if (stepper == idx) {
      if (current->next_bll_ != nullptr) {
        throw std::invalid_argument("BLL at idx");
      }
      current->next_bll_ = list;
      break;
    }
    stepper++;
    if (current->next_bll_ != nullptr) {
      current->next_bll_->Join((idx - stepper), list);
    }
    current = current->next_node_;
  }
}
std::string BLL::ToString() const {
  if (head_ == nullptr) {
    return "";
  }
  std::string toreturn;
  Node* current = head_;
  while (current != nullptr) {
    toreturn += current->data_;
    if (current->next_bll_ != nullptr) {
      toreturn += current->next_bll_->ToString();
    }
    current = current->next_node_;
  }
  return toreturn;
}
size_t BLL::Size() const {
  if (head_ == nullptr) {
    return 0;
  }
  size_t toreturn = 0;
  Node* current = head_;
  while (current != nullptr) {
    toreturn++;
    if (current->next_bll_ != nullptr) {
      toreturn += current->next_bll_->Size();
    }
    current = current->next_node_;
  }
  return toreturn;
}
Node* BLL::Helper(Node* tortoise) const {
  if (tortoise->next_bll_ != nullptr) {
    return tortoise->next_bll_->head_;
  }
  return tortoise->next_node_;
}
bool BLL::IsBLLAcyclic() const {
  if (head_ == nullptr) {
    return true;
  }
  Node* tortoise = head_;
  Node* hare = head_->next_node_;
  while (tortoise != nullptr && hare != nullptr &&
         (hare->next_node_ != nullptr || hare->next_bll_ != nullptr)) {
    if (tortoise == hare) {
      return false;
    }
    tortoise = Helper(tortoise);
    hare = Helper(hare);
    if (hare != nullptr) {
      hare = Helper(hare);
    }
  }
  return true;
}
