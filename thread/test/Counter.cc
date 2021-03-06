#include "../Mutex.h"
using muduo::MutexLock;
using muduo::MutexLockGuard;
#include <iostream>
// A thread-safe counter
class Counter : boost::noncopyable
{
  // copy-ctor and assignment should be private by default for a class.
 public:
  Counter() : value_(0) {}
  Counter& operator=(const Counter& rhs);

  int64_t value() const;
  int64_t getAndIncrease();

  friend void swap(Counter& a, Counter& b);

 private:
  /* 定义互斥量 */
  mutable MutexLock mutex_;
  int64_t value_;
};

int64_t Counter::value() const
{
  MutexLockGuard lock(mutex_);
  return value_;
}

int64_t Counter::getAndIncrease()
{
  MutexLockGuard lock(mutex_);
  int64_t ret = value_++;
  std::cout << "Counter::getAndIncrease" <<std::endl;
  return ret;
}

void swap(Counter& a, Counter& b)
{
  MutexLockGuard aLock(a.mutex_);  // potential dead lock
  MutexLockGuard bLock(b.mutex_);
  int64_t value = a.value_;
  a.value_ = b.value_;
  b.value_ = value;
}

Counter& Counter::operator=(const Counter& rhs)
{
  if (this == &rhs)
    return *this;

  MutexLockGuard myLock(mutex_);  // potential dead lock
  MutexLockGuard itsLock(rhs.mutex_);
  value_ = rhs.value_;
  return *this;
}

int main()
{
  Counter c;
  c.getAndIncrease();
//  #ifdef test_pr
  std::cout << "hellowo343rld" <<std::endl;


 // #endif
}
