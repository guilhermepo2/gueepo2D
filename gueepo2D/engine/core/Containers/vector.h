// ******************************************************************
// vector.h
// 
// 
// https://github.com/NoelFB/blah/blob/master/include/blah/containers/vector.h
// https://github.com/brianbatista93/windmill-engine/blob/main/modules/core/include/containers/dyn_array.h
// ******************************************************************
#pragma once
#include "core/Log.h"

namespace gueepo {
	template<class T>
	class vector {
	public:
		vector();
		vector(int capacity);
		// Vector(const InitializerList<T>& list);
		vector(const vector& src);
		// Vector(Vector&& src) noexcept;
		~vector();

		void clear();
		void dispose();

		int size() const;
		int capacity() const;

		// operator
		vector& operator=(const vector& src);
		vector& operator=(vector&& src) noexcept;
		T& operator[](int index);
		const T& operator[](int index) const;

		// managing vector size
		void reserve(int newCapacity);
		void resize(int newCount);
		T* expand(int amount = 1);

		// data manipulation
		void add(const T& item);
		void add(T&& item);

		// it seems like this gets the constructor and allocates/creates a new item for you?
		// looks good, but...maybe later
		// template<class ...Args>
		// void emplace_back(Args&&...args);

		void erase(int index, int elements = 1);
		T pop();

		T* data();
		const T* data() const;
		T* begin();
		const T* begin() const;
		T* end();
		const T* end() const;

		T& front();
		const T& front() const;
		T& back();
		const T& back() const;

	private:
		T* m_data;
		int m_count;
		int m_capacity;
	};

	template<class T>
	vector<T>::vector() {
		m_data = nullptr;
		m_count = 0;
		m_capacity = 0;
	}

	template<class T>
	vector<T>::vector(int capacity) {
		m_data = nullptr;
		m_count = 0;
		m_capacity = 0;
		reserve(capacity);
	}
	
	template<class T>
	vector<T>::vector(const vector& src) {
		m_data = nullptr;
		m_count = 0;
		m_capacity = 0;
		reserve(src.m_capacity);

		for (int i = 0; i < src.m_count; i++) {
			new(m_data + i) T(src.m_data[i]);
		}

		m_count = src.m_count;
	}
	
	template<class T>
	vector<T>::~vector() {
		dispose();
	}

	// (1) destroy all elements in the vector
	// (2) reset count
	// Important to note that it doesn't free the m_data memory.
	template<class T>
	void vector<T>::clear() {
		for (int i = 0; i < m_count; i++) {
			m_data[i].~T();
		}

		m_count = 0;
	}

	// Clear and THEN frees the buffer memory
	template<class T>
	void vector<T>::dispose() {
		clear();
		::operator delete (m_data, sizeof(T) * m_capacity);

		m_capacity = 0;
		m_data = nullptr;
	}

	template<class T>
	int vector<T>::size() const {
		return m_count;
	}

	template<class T>
	int vector<T>::capacity() const {
		return m_capacity;
	}

	// ---------------------------------------------------------------
	// Managing Vector Size
	// ---------------------------------------------------------------
	template<class T>
	vector<T>& vector<T>::operator=(const vector& src) {
		clear();
		reserve(src.m_capacity);
		for (int i = 0; i < src.m_count; i++) {
			new(m_data + i) T(src.m_data[i]);
		}

		m_count = src.m_count;
		return *this;
	}

	template<class T>
	vector<T>& vector<T>::operator=(vector&& src) noexcept {
		dispose();
		m_data = src.m_data;
		m_capacity = src.m_capacity;
		m_count = src.m_count;

		src.m_data = nullptr;
		src.m_capacity = 0;
		src.m_count = 0;

		return *this;
	}

	template<class T>
	T& vector<T>::operator[](int index) {
		g2dassert(index >= 0 && index <= m_count, "index out of range!");
		return m_data[index];
	}

	template<class T>
	const T& vector<T>::operator[](int index) const {
		g2dassert(index >= 0 && index <= m_count, "index out of range!");
		return m_data[index];
	}

	// ---------------------------------------------------------------
	// Managing Vector Size
	// ---------------------------------------------------------------
	template<class T>
	void vector<T>::reserve(int newCapacity) {
		if (newCapacity > m_capacity) {
			// Calculating the actual capacity the vector will reserve.
			int updatedCapacity = m_capacity;
			if (updatedCapacity <= 0) {
				updatedCapacity = 8;
			}
			while (updatedCapacity < newCapacity) {
				updatedCapacity = updatedCapacity * 2;
			}

			T* newBuffer = (T*)::operator new (sizeof(T) * updatedCapacity);

			/*
			* https://en.cppreference.com/w/cpp/types/is_trivially_copyable
			* Objects of trivially-copyable types that are not potentially-overlapping subobjects are the only C++ objects that may be safely copied with std::memcpy or serialized to/from binary files with std::ofstream::write()/std::ifstream::read().
			*/
			// Copying the old vector to the new buffer
			if (std::is_trivially_copyable<T>()) {
				memcpy(newBuffer, m_data, m_count * sizeof(T));
			}
			else {
				for (int i = 0; i < m_count; i++) {
					if (i < updatedCapacity) {
						new(newBuffer + i) T(std::move(m_data[i]));
					}
					m_data[i].~T();
				}
			}

			::operator delete (m_data, sizeof(T) * m_capacity);

			m_data = newBuffer;
			m_capacity = updatedCapacity;
		}


	}
	
	template<class T>
	void vector<T>::resize(int newCount) {
		if (newCount < m_count) {
			erase(newCount, m_count - newCount);
		}
		else {
			expand(newCount - m_count);
		}
	}

	template<class T>
	T* vector<T>::expand(int amount /* = 1 */) {
		if (amount > 0) {
			int count = m_count;
			reserve(count + amount);
			
			for (int i = 0; i < amount; i++) {
				new(m_data + count + i) T();
			}

			m_count += amount;
			return &m_data[count]; // return the first position of the expanded area of the vector
		}

		return m_data; // returns the buffer if we don't expand
	}

	// ---------------------------------------------------------------
	// ---------------------------------------------------------------
	// Data Manipulation
	// ---------------------------------------------------------------
	// ---------------------------------------------------------------
	template<class T>
	void vector<T>::add(const T& item) {
		reserve(m_count + 1);
		new(m_data + m_count) T(item);
		m_count++;
	}

	template<class T>
	void vector<T>::add(T&& item) {
		reserve(m_count + 1);
		new(m_data + m_count) T(std::move(item));
		m_count++;
	}

	template<class T>
	void vector<T>::erase(int index, int elements /* = 1 */) {
		g2dassert(index >= 0 && index + elements <= m_count, "index out of range");

		if (elements >= 1) {
			for (int i = index; i < (m_count - elements); i++) {
				m_data[i] = std::move(m_data[i + elements]);
			}

			for (int i = m_count - elements; i < m_count; i++) {
				m_data[i].~T();
			}

			m_count -= elements;
		}
	}

	template<class T>
	T vector<T>::pop() {
		g2dassert(m_count > 0, "index out of range!");

		T returnValue = std::move(m_data[m_count - 1]);
		m_data[m_count - 1].~T();
		m_count--;
		return returnValue;
	}

	// ---------------------------------------------------------------
	// ---------------------------------------------------------------
	// Accessing
	// ---------------------------------------------------------------
	// ---------------------------------------------------------------
	template<class T>
	T* vector<T>::data() {
		return m_data;
	}

	template<class T>
	const T* vector<T>::data() const {
		return m_data;
	}

	template<class T>
	T* vector<T>::begin() {
		return m_data;
	}

	template<class T>
	const T* vector<T>::begin() const {
		return m_data;
	}

	template<class T>
	T* vector<T>::end() {
		return m_data + m_count;
	}

	template<class T>
	const T* vector<T>::end() const {
		return m_data + m_count;
	}

	template<class T>
	T& vector<T>::front() {
		g2dassert(m_count > 0, "index out of range!");
		return m_data[0];
	}
	
	template<class T>
	const T& vector<T>::front() const {
		g2dassert(m_count > 0, "index out of range!");
		return m_data[0];
	}
	
	template<class T>
	T& vector<T>::back() {
		g2dassert(m_count > 0, "index out of range!");
		return m_data[m_count - 1];
	}
	
	template<class T>
	const T& vector<T>::back() const {
		g2dassert(m_count > 0, "index out of range!");
		return m_data[m_count - 1];
	}
}
