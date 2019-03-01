#ifndef Chess_Position_h
#define Chess_Position_h

#include <iostream>
#include <string>
#include <ostream>
#include <sstream>
#include <utility>
#include <stdexcept>

#include <SFML/System/Vector2.hpp>

#include "../Util/UniqueNumericID.h"


constexpr unsigned lowerCaseA {97} ;

template <typename NumericType>
using simd_vector_2 = NumericType __attribute__((ext_vector_type(2))) ;


template <typename NumericType>

struct vec2 {

	simd_vector_2<NumericType> value ;

    inline constexpr vec2(NumericType n) : value(simd_vector_2<NumericType> {n, n}) {}

    inline constexpr vec2(NumericType x, NumericType y) : value(simd_vector_2<NumericType> {x, y}) {}

    template <typename OtherNumericType>
    inline constexpr vec2(OtherNumericType x, OtherNumericType y) : value {static_cast<NumericType>(x), static_cast<NumericType>(y)} {}

	inline constexpr vec2(const vec2 & other) : value(other.value) {}

	inline constexpr vec2(const simd_vector_2<NumericType> val) : value(val) {}

    template <typename OtherNumericType>
    inline constexpr vec2(const vec2<OtherNumericType> val) : value {static_cast<NumericType>(val.x()), static_cast<NumericType>(val.y())} {}

	template <typename OtherNumericType>
	inline constexpr vec2(const simd_vector_2<OtherNumericType> val) : value {static_cast<NumericType>(val.x), static_cast<NumericType>(val.y)} {}

    template<typename OtherVectorType>
    inline constexpr vec2(const OtherVectorType & val) : vec2 (val.position) {}

    template<typename OtherNumericType, template<typename> typename OtherVectorType>
    inline constexpr vec2(const OtherVectorType<OtherNumericType> & val) : value {static_cast<NumericType>(val.x), static_cast<NumericType>(val.y)} {}

    inline constexpr vec2(std::initializer_list<NumericType> & init) : value(init) {}

	inline constexpr operator simd_vector_2<NumericType>() const { return this->value ; }

	template <typename OtherNumericType>
	inline constexpr operator simd_vector_2<OtherNumericType>() const {
		return simd_vector_2<OtherNumericType> {
            static_cast<OtherNumericType>(value.x),
            static_cast<OtherNumericType>(value.y)
        } ;
	}

    template<typename OtherNumericType, template<typename> typename OtherVectorType>
    inline operator OtherVectorType<OtherNumericType>() const {
        return OtherVectorType<OtherNumericType> {
            static_cast<OtherNumericType>(value.x),
            static_cast<OtherNumericType>(value.y)
        } ;
    }

	inline constexpr NumericType operator [] (size_t i) const { return value[i] ; }

	inline constexpr bool operator == (vec2 other) const { return ((this->value.x == other.value.x) && (this->value.y == other.value.y)) ; }
	inline constexpr bool operator != (vec2 other) const { return (!(*this == other)) ; }

	inline constexpr vec2 & operator += (vec2 other) { this->value += other.value ; return * this ;}

	inline constexpr vec2 & operator -= (vec2 other) {this->value -= other.value ; return * this ;}

	inline constexpr vec2 & operator *= (vec2 other) {this->value *= other.value ; return * this ;}

	inline constexpr vec2 & operator /= (vec2 other) {this->value /= other.value ; return * this ;}

	inline constexpr vec2 & operator += (NumericType n) {this->value += n ; return * this ;}

	inline constexpr vec2 & operator -= (NumericType n) {this->value -= n ; return * this ;}

	template <typename NumericType0>
	inline constexpr vec2<NumericType> & operator *= (NumericType0 n) {this->value *= n ; return * this ;}

	template <typename NumericType0>
	inline constexpr vec2<NumericType> & operator /= (NumericType0 n) {this->value /= n ; return * this ;}

    inline constexpr NumericType x() const { return value.x; };
    inline constexpr NumericType y() const { return value.y; };


	/*
	 * Compiler seems to provide these operator overloads implicitly, retaining for reference and/or the possibility
	 * we run into problem later
	 *
	inline friend constexpr vec2 operator + (const vec2 v0, const vec2 v1) { return vec2<NumericType> { (v0.value + v1.value) } ; }
	inline friend constexpr vec2 operator - (const vec2 v0, const vec2 v1) { return vec2<NumericType> { (v0.value - v1.value) } ; }
	inline friend constexpr vec2 operator * (const vec2 v0, const vec2 v1) { return vec2<NumericType> { (v0.value * v1.value) } ; }
	inline friend constexpr vec2 operator / (const vec2 v0, const vec2 v1) { return vec2<NumericType> { (v0.value / v1.value) } ; }
	 */

	inline friend constexpr vec2 operator + (const vec2 v, const NumericType n) { return vec2 {(v.value.x + n), (v.value.y + n)} ; }
	inline friend constexpr vec2 operator - (const vec2 v, const NumericType n) { return vec2 {(v.value.x - n), (v.value.y - n)} ; }
	inline friend constexpr vec2 operator * (const vec2 v, const NumericType n) { return vec2 {(v.value.x * n), (v.value.y * n)} ; }
	inline friend constexpr vec2 operator / (const vec2 v, const NumericType n) { return vec2 {(v.value.x / n), (v.value.y / n)} ; }

} ;



struct Direction {

protected:

	const simd_vector_2<int> value ;

public:

	constexpr Direction(const simd_vector_2<int> val) : value(val) {}

	constexpr Direction(const int h, const int v) : value(simd_vector_2<int> {h, v}) {}

	constexpr operator simd_vector_2<int>() const { return this->value ; }

	template <typename NumericType>
	friend simd_vector_2<NumericType> operator * (const Direction &, const NumericType) ;

	template <typename NumericType>
	friend simd_vector_2<NumericType> operator + (const Direction &, const simd_vector_2<NumericType>) ;

} ;

namespace Directions {

	static constexpr Direction up  		 { simd_vector_2<int>{ 0, -1} } ;
	static constexpr Direction down 	 { simd_vector_2<int>{ 0,  1} } ;
	static constexpr Direction left 	 { simd_vector_2<int>{-1,  0} } ;
	static constexpr Direction right 	 { simd_vector_2<int>{ 1,  0} } ;

	static constexpr Direction upLeft    { simd_vector_2<int>{-1, -1} } ;
	static constexpr Direction upRight   { simd_vector_2<int>{ 1, -1} } ;
	static constexpr Direction downLeft  { simd_vector_2<int>{-1,  1} } ;
	static constexpr Direction downRight { simd_vector_2<int>{ 1,  1} } ;

}


template <typename NumericType>
simd_vector_2<NumericType> operator * (const Direction & direction, const NumericType n) {

	simd_vector_2<NumericType> ret ;

	ret.x = direction.value.x * n ;
	ret.y = direction.value.y * n ;

	return ret ;
}

template <typename NumericType>
simd_vector_2<NumericType> operator + (const Direction & direction, const simd_vector_2<NumericType> vec) {

	simd_vector_2<NumericType> ret ;

	ret.x = direction.value.x + vec.x ;
	ret.y = direction.value.y + vec.y ;

	return ret ;
}

template <typename Character, typename NumericType>
std::basic_ostream<Character> & operator << (std::basic_ostream<Character> & out, const simd_vector_2<NumericType> & vect) {
	out << "x = " << vect[0] << " y = " << vect[1] ;
	return out ;
}

/**
 * Code partial credit StackOverflow:
 * @link http://stackoverflow.com/questions/20511347/a-good-hash-function-for-a-vector
 */
template <typename VectorType>
inline UniqueNumericIdentifier hashVector(const VectorType & vect, size_t vectorSize) {
	unsigned long seed = 0;

	for (auto i = 0 ; i < vectorSize ; i++) {
		seed ^= vect[i] + 0x9e3779b9 + (seed << 6) + (seed >> 2);
	}

	return seed;
}


template <typename VectorType>
inline UniqueNumericIdentifier hashTwoVector(const VectorType twoVect) {
	auto hash = hashVector(twoVect, 2) ;
	return hash ;
}

/**
 * Allows creating a unique identifying value for simd_vector_2, which isn't
 * a class and can't store a UniqueNumericIdentifier as a member variable
 */
template <typename NumericType>
inline UniqueNumericIdentifier generateID(simd_vector_2<NumericType> vect) {
	return hashTwoVector<simd_vector_2<NumericType>>(vect) ;
}



template <typename NumericType>
NumericType calculateDistance(const simd_vector_2<int> startingPosition) {
	return NumericType() ;
}



#endif
