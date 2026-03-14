#include <iostream>

template <typename T>
class SharedPtr {
private:
	T* ptr_;
	int* refcount_;

	void release() {
		if (refcount_ == nullptr) {
			return;
		}

		(*refcount_)--;

		// shared pointer refcount hit 0 -> destroy everything
		if (*refcount_ == 0) {
			delete ptr_;
			delete refcount_;
		}
	}

public:
	explicit SharedPtr(T* ptr) {
		ptr_ = ptr;
		refcount_ = new int{ 1 };
	}
	
	SharedPtr() : ptr_{nullptr}, refcount_{nullptr} {}

	~SharedPtr() {
		release();
	}
	
	SharedPtr(const SharedPtr& other) 
		: ptr_{other.ptr_}, refcount_{other.refcount_}
	{
		// increase refcount since a new pointer has been added to this object
		(*refcount_)++;
	}

	SharedPtr& operator=(const SharedPtr& other) {
		// decrement refcount on current object and destroy if it hits 0
		release();

		// copy all members 
		ptr_ = other.ptr_;
		refcount_ = other.refcount_;
		(*refcount_)++;
		return *this;
	}

	SharedPtr(SharedPtr&& other)
		: ptr_{other.ptr_}, refcount_{other.refcount_}
	{
		// setting other members to null because moved
		other.ptr_ = nullptr;
		other.refcount_ = nullptr;
	}
	
	SharedPtr& operator=(SharedPtr&& other) {
		if (this == &other) {
			return *this;
		}

		// decrement current refcount and let destructor delete it if its 0
		release();

		// copy all the values into this object
		ptr_ = other.ptr_;
		refcount_ = other.refcount_;

		// set the other object members to null
		other.ptr_ = nullptr;
		other.refcount_ = nullptr;

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
	return 0;
}