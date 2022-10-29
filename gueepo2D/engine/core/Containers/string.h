#pragma once

namespace gueepo {
	class string {
	public:
		string() { m_buffer = emptyBuffer; m_length = m_capacity = 0; }
		string(const char* start, const char* end = nullptr) : string() { set(start, end); }
		string(const string& str) : string() { set(str); }
		~string() { if (m_buffer != nullptr && m_buffer != emptyBuffer) { delete[] m_buffer; } }

		// Operators
		char& operator[](int index) { return data()[index]; }
		const char& operator[](int index) const { return data()[index]; }
		bool operator==(const string& rhs) const;
		bool operator!=(const string& rhs) const;
		bool operator==(const char* rhs) const;
		bool operator!=(const char* rhs) const;
		string& operator=(const string& rhs) { set(rhs.c_str(), rhs.c_str() + rhs.m_length); return *this; }
		string& operator=(const char* rhs) { set(rhs, nullptr); return *this; }

		// Appending
		string& operator+=(const char& rhs) { return append(rhs); }
		string& operator+=(const char* rhs) { return append(rhs); }
		string& operator+=(const string& rhs) { return append(rhs); }
		string operator+(const char& rhs) { string str; str.append(*this).append(rhs); return str; }
		string operator+(const char* rhs) { string str; str.append(*this).append(rhs); return str; }
		string operator+(const string& rhs) { string str; str.append(*this).append(rhs); return str; }
		string& append(char c);
		string& append(uint32_t c);
		string& append(const char* start, const char* end = nullptr);
		string& append(const string& str, int start = 0, int end = -1);

		// Implicit casting
		operator char*() { return c_str(); }
		operator const char* () const { return c_str(); }

		// UTF-8 and UTF-16 shenanigans
		uint32_t utf8_at(int index) const;
		int utf8_length(int index) const;
		string& append_utf16(const uint16_t* start, const uint16_t* end = nullptr, bool swapEndian = false);

		// #TODO: search and manipulation functions (starts with, contains, ends with, first index of, last index of, etc...)
		string substring(int start, int end) const;

		void reserve(int capacity);
		void clear();

		char* c_str() { return data(); }
		const char* c_str() const { return data(); }
		const char* begin() const { return data(); }
		const char* end() const { return data() + m_length; }

		inline bool empty() const { return m_length <= 0; }
		inline int length() const { return m_length; }
		inline int capacity() const { return m_capacity; }
	protected:

		// Returns a pointer to the heap buffer
		char* data() { return m_buffer; }
		const char* data() const { return m_buffer; }

		// Set the content of the string
		void set(const string& str) { set(str.c_str(), str.c_str() + str.m_length); }
		void set(const char* start, const char* end = nullptr);
		
		char* m_buffer;
	private:
		static char emptyBuffer[1];
		int m_length;
		int m_capacity;
	};
}