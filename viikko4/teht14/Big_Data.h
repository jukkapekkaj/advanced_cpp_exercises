#include <cstdlib>
#include <cstring>
#include <exception>


class Big_Data {
public:
	Big_Data(size_t n) : size(n) {
		ptr = std::malloc(n);
		if (ptr == 0) {
			throw std::bad_alloc();
		}
	}

	Big_Data(const Big_Data& other) {
		ptr = std::malloc(other.size);
		if (ptr == nullptr) {
			throw std::bad_alloc();
		}
		std::memcpy(ptr, other.ptr, other.size);
		size = other.size;
	
	}

	Big_Data& operator=(const Big_Data& other) {
		if (this == &other) {
			return *this;
		}
		void* new_ptr = std::malloc(other.size);
		if (new_ptr == nullptr) {
			throw std::bad_alloc();
		}
		
		std::memcpy(new_ptr, other.ptr, other.size);
		std::free(ptr);
		ptr = new_ptr;
		size = other.size;
	
		return *this;
	}

	~Big_Data() {
		std::free(ptr);
	}

private:
	void* ptr;
	size_t size;
};