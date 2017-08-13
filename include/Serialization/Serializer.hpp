/*#ifndef __HAZ_SERIALIZER
#define __HAZ_SERIALIZER

#include <Tools/Macro.hpp>

#include <string>

BEG_NAMESPACE_HAZ_SERIALIZATION

template <bool is_input>
class Archive;

template<typename T>
void load(Archive<false>& a, T & t);

template<typename T>
void save(Archive<true>& a, T & t);

template<>
class Archive<true> {
public:
	Archive(std::string & s) : content(s) {}

	template<typename T>
	Archive& operator & (T & t) {
		save(*this, t);
		return *this;
	}

	#define OPERATOR_TYPE(T) Archive& operator & (T & i) { content += std::to_string(i); return *this;}

	OPERATOR_TYPE(char)
	OPERATOR_TYPE(wchar_t)
	OPERATOR_TYPE(unsigned char)

	OPERATOR_TYPE(int)
	OPERATOR_TYPE(unsigned int)

	OPERATOR_TYPE(short)
	OPERATOR_TYPE(unsigned short)

	OPERATOR_TYPE(long)
	OPERATOR_TYPE(unsigned long)
	OPERATOR_TYPE(long long)

	OPERATOR_TYPE(double)
	OPERATOR_TYPE(long double)

	OPERATOR_TYPE(float)
	
	std::string& content;
};

template<>
class Archive<false> {
public:
	Archive(std::string & s) : content(s) {}

	template<typename T>
	Archive& operator & (T & t) {
		load(*this, t);
		return *this;
	}

	std::string& content;
};

#include <Serialization/Load.tcc>
#include <Serialization/Save.tcc>

class Serializable {
	template <typename T>
	void serialize(T & a);
};

class Serializer {
public:
	Serializer();
	virtual ~Serializer();

	template<typename T>
	Serializer& operator << (T & t) {
		Archive<true>(res) & t;

		return *this;
	}

	template<typename T>
	Serializer& operator >> (T & t) {
		Archive<false>(res) & t;
		
		return *this;
	}

	std::string& get() {
		return res;
	}

private:
	std::string res = "";
};

END_NAMESPACE_HAZ_SERIALIZATION

#endif*/