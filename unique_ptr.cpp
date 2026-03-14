#include <iostream>

template <typename T>
class UniquePtr {
private:
	T* ptr_;

public:
	explicit UniquePtr(T* ptr) 
		: ptr_{ptr} {}

	~UniquePtr() {
		delete ptr_;
	}

	UniquePtr(const UniquePtr&) = delete;
	UniquePtr& operator=(const UniquePtr&) = delete;

	UniquePtr(UniquePtr&& other) 
		: ptr_{other.ptr_}
	{
		other.ptr_ = nullptr;
	}
	
	UniquePtr& operator=(UniquePtr&& other) {
		if (this == &other) {
			return *this;
		}

		// doesn't handle pointers to arrays
		delete ptr_;

		ptr_ = other.ptr_;
		other.ptr_ = nullptr;

		return *this;
	}

	T& operator*() {
		return *ptr_;
	}

	T* operator->() {
		return ptr_;
	}

};

int main() {
	std::cout << "unique pointer\n";
	return 0;
}