//
// SPDX-License-Identifier: BSD-3-Clause
// Copyright Contributors to the OpenEXR Project.
// 

#ifndef INCLUDED_IMATHVEC_H
#define INCLUDED_IMATHVEC_H

//----------------------------------------------------
//
//	2D, 3D and 4D point/vector class templates
//
//----------------------------------------------------

#include "ImathLimits.h"
#include "ImathMath.h"
#include "ImathNamespace.h"

#include <iostream>
#include <stdexcept>

#if (defined _WIN32 || defined _WIN64) && defined _MSC_VER
// suppress exception specification warnings
#    pragma warning(push)
#    pragma warning(disable : 4290)
#endif

IMATH_INTERNAL_NAMESPACE_HEADER_ENTER

template <class T> class Vec2;
template <class T> class Vec3;
template <class T> class Vec4;

enum InfException
{
    INF_EXCEPTION
};

template <class T> class Vec2
{
  public:
    //-------------------
    // Access to elements
    //-------------------

    T x, y;

    IMATH_HOSTDEVICE IMATH_CONSTEXPR14 T& operator[] (int i) noexcept;
    IMATH_HOSTDEVICE constexpr const T& operator[] (int i) const noexcept;

    //-------------
    // Constructors
    //-------------

    IMATH_HOSTDEVICE Vec2() noexcept;                                // no initialization
    IMATH_HOSTDEVICE IMATH_CONSTEXPR14 explicit Vec2 (T a) noexcept; // (a a)
    IMATH_HOSTDEVICE IMATH_CONSTEXPR14 Vec2 (T a, T b) noexcept;     // (a b)

    //---------------------------------
    // Copy constructors and assignment
    //---------------------------------

    IMATH_HOSTDEVICE IMATH_CONSTEXPR14 Vec2 (const Vec2& v) noexcept;
    template <class S> IMATH_HOSTDEVICE IMATH_CONSTEXPR14 Vec2 (const Vec2<S>& v) noexcept;

    IMATH_HOSTDEVICE IMATH_CONSTEXPR14 const Vec2& operator= (const Vec2& v) noexcept;

    //------------
    // Destructor
    //------------

    ~Vec2() noexcept = default;

    //----------------------
    // Compatibility with Sb
    //----------------------

    template <class S> IMATH_HOSTDEVICE void setValue (S a, S b) noexcept;

    template <class S> IMATH_HOSTDEVICE void setValue (const Vec2<S>& v) noexcept;

    template <class S> IMATH_HOSTDEVICE void getValue (S& a, S& b) const noexcept;

    template <class S> IMATH_HOSTDEVICE void getValue (Vec2<S>& v) const noexcept;

    IMATH_HOSTDEVICE T* getValue() noexcept;
    IMATH_HOSTDEVICE const T* getValue() const noexcept;

    //---------
    // Equality
    //---------

    template <class S> IMATH_HOSTDEVICE constexpr bool operator== (const Vec2<S>& v) const noexcept;

    template <class S> IMATH_HOSTDEVICE constexpr bool operator!= (const Vec2<S>& v) const noexcept;

    //-----------------------------------------------------------------------
    // Compare two vectors and test if they are "approximately equal":
    //
    // equalWithAbsError (v, e)
    //
    //	    Returns true if the coefficients of this and v are the same with
    //	    an absolute error of no more than e, i.e., for all i
    //
    //      abs (this[i] - v[i]) <= e
    //
    // equalWithRelError (v, e)
    //
    //	    Returns true if the coefficients of this and v are the same with
    //	    a relative error of no more than e, i.e., for all i
    //
    //      abs (this[i] - v[i]) <= e * abs (this[i])
    //-----------------------------------------------------------------------

    IMATH_HOSTDEVICE IMATH_CONSTEXPR14 bool equalWithAbsError (const Vec2<T>& v, T e) const noexcept;
    IMATH_HOSTDEVICE IMATH_CONSTEXPR14 bool equalWithRelError (const Vec2<T>& v, T e) const noexcept;

    //------------
    // Dot product
    //------------

    IMATH_HOSTDEVICE constexpr T dot (const Vec2& v) const noexcept;
    IMATH_HOSTDEVICE constexpr T operator^ (const Vec2& v) const noexcept;

    //------------------------------------------------
    // Right-handed cross product, i.e. z component of
    // Vec3 (this->x, this->y, 0) % Vec3 (v.x, v.y, 0)
    //------------------------------------------------

    IMATH_HOSTDEVICE constexpr T cross (const Vec2& v) const noexcept;
    IMATH_HOSTDEVICE constexpr T operator% (const Vec2& v) const noexcept;

    //------------------------
    // Component-wise addition
    //------------------------

    IMATH_HOSTDEVICE IMATH_CONSTEXPR14 const Vec2& operator+= (const Vec2& v) noexcept;
    IMATH_HOSTDEVICE constexpr Vec2 operator+ (const Vec2& v) const noexcept;

    //---------------------------
    // Component-wise subtraction
    //---------------------------

    IMATH_HOSTDEVICE IMATH_CONSTEXPR14 const Vec2& operator-= (const Vec2& v) noexcept;
    IMATH_HOSTDEVICE constexpr Vec2 operator- (const Vec2& v) const noexcept;

    //------------------------------------
    // Component-wise multiplication by -1
    //------------------------------------

    IMATH_HOSTDEVICE constexpr Vec2 operator-() const noexcept;
    IMATH_HOSTDEVICE IMATH_CONSTEXPR14 const Vec2& negate() noexcept;

    //------------------------------
    // Component-wise multiplication
    //------------------------------

    IMATH_HOSTDEVICE IMATH_CONSTEXPR14 const Vec2& operator*= (const Vec2& v) noexcept;
    IMATH_HOSTDEVICE IMATH_CONSTEXPR14 const Vec2& operator*= (T a) noexcept;
    IMATH_HOSTDEVICE constexpr Vec2 operator* (const Vec2& v) const noexcept;
    IMATH_HOSTDEVICE constexpr Vec2 operator* (T a) const noexcept;

    //------------------------
    // Component-wise division
    //------------------------

    IMATH_HOSTDEVICE IMATH_CONSTEXPR14 const Vec2& operator/= (const Vec2& v) noexcept;
    IMATH_HOSTDEVICE IMATH_CONSTEXPR14 const Vec2& operator/= (T a) noexcept;
    IMATH_HOSTDEVICE constexpr Vec2 operator/ (const Vec2& v) const noexcept;
    IMATH_HOSTDEVICE constexpr Vec2 operator/ (T a) const noexcept;

    //----------------------------------------------------------------
    // Length and normalization:  If v.length() is 0.0, v.normalize()
    // and v.normalized() produce a null vector; v.normalizeExc() and
    // v.normalizedExc() throw a std::domain_error.
    // v.normalizeNonNull() and v.normalizedNonNull() are slightly
    // faster than the other normalization routines, but if v.length()
    // is 0.0, the result is undefined.
    //----------------------------------------------------------------

    IMATH_HOSTDEVICE T length() const noexcept;
    IMATH_HOSTDEVICE constexpr T length2() const noexcept;

    IMATH_HOSTDEVICE const Vec2& normalize() noexcept; // modifies *this
    const Vec2& normalizeExc();
    IMATH_HOSTDEVICE const Vec2& normalizeNonNull() noexcept;

    IMATH_HOSTDEVICE Vec2<T> normalized() const noexcept; // does not modify *this
    Vec2<T> normalizedExc() const;
    IMATH_HOSTDEVICE Vec2<T> normalizedNonNull() const noexcept;

    //--------------------------------------------------------
    // Number of dimensions, i.e. number of elements in a Vec2
    //--------------------------------------------------------

    IMATH_HOSTDEVICE constexpr static unsigned int dimensions() noexcept { return 2; }

    //-------------------------------------------------
    // Limitations of type T (see also class limits<T>)
    //-------------------------------------------------

    IMATH_HOSTDEVICE constexpr static T baseTypeMin() noexcept { return limits<T>::min(); }
    IMATH_HOSTDEVICE constexpr static T baseTypeMax() noexcept { return limits<T>::max(); }
    IMATH_HOSTDEVICE constexpr static T baseTypeSmallest() noexcept { return limits<T>::smallest(); }
    IMATH_HOSTDEVICE constexpr static T baseTypeEpsilon() noexcept { return limits<T>::epsilon(); }

    //--------------------------------------------------------------
    // Base type -- in templates, which accept a parameter, V, which
    // could be either a Vec2<T>, a Vec3<T>, or a Vec4<T> you can
    // refer to T as V::BaseType
    //--------------------------------------------------------------

    typedef T BaseType;

  private:
    IMATH_HOSTDEVICE IMATH_CONSTEXPR14 T lengthTiny() const noexcept;
};

template <class T> class Vec3
{
  public:
    //-------------------
    // Access to elements
    //-------------------

    T x, y, z;

    IMATH_HOSTDEVICE IMATH_CONSTEXPR14 T& operator[] (int i) noexcept;
    IMATH_HOSTDEVICE constexpr const T& operator[] (int i) const noexcept;

    //-------------
    // Constructors
    //-------------

    IMATH_HOSTDEVICE constexpr Vec3() noexcept;                       // no initialization
    IMATH_HOSTDEVICE IMATH_CONSTEXPR14 explicit Vec3 (T a) noexcept;  // (a a a)
    IMATH_HOSTDEVICE IMATH_CONSTEXPR14 Vec3 (T a, T b, T c) noexcept; // (a b c)

    //---------------------------------
    // Copy constructors and assignment
    //---------------------------------

    IMATH_HOSTDEVICE IMATH_CONSTEXPR14 Vec3 (const Vec3& v) noexcept;
    template <class S> IMATH_HOSTDEVICE IMATH_CONSTEXPR14 Vec3 (const Vec3<S>& v) noexcept;

    IMATH_HOSTDEVICE IMATH_CONSTEXPR14 const Vec3& operator= (const Vec3& v) noexcept;

    //-----------
    // Destructor
    //-----------

    ~Vec3() noexcept = default;

    //---------------------------------------------------------
    // Vec4 to Vec3 conversion, divides x, y and z by w:
    //
    // The one-argument conversion function divides by w even
    // if w is zero.  The result depends on how the environment
    // handles floating-point exceptions.
    //
    // The two-argument version throws an InfPointExc exception
    // if w is zero or if division by w would overflow.
    //---------------------------------------------------------

    template <class S> IMATH_HOSTDEVICE explicit IMATH_CONSTEXPR14 Vec3 (const Vec4<S>& v) noexcept;
    template <class S>
    explicit IMATH_CONSTEXPR14 Vec3 (const Vec4<S>& v, InfException);

    //----------------------
    // Compatibility with Sb
    //----------------------

    template <class S> IMATH_HOSTDEVICE void setValue (S a, S b, S c) noexcept;

    template <class S> IMATH_HOSTDEVICE void setValue (const Vec3<S>& v) noexcept;

    template <class S> IMATH_HOSTDEVICE void getValue (S& a, S& b, S& c) const noexcept;

    template <class S> IMATH_HOSTDEVICE void getValue (Vec3<S>& v) const noexcept;

    IMATH_HOSTDEVICE T* getValue() noexcept;
    IMATH_HOSTDEVICE const T* getValue() const noexcept;

    //---------
    // Equality
    //---------

    template <class S> IMATH_HOSTDEVICE constexpr bool operator== (const Vec3<S>& v) const noexcept;

    template <class S> IMATH_HOSTDEVICE constexpr bool operator!= (const Vec3<S>& v) const noexcept;

    //-----------------------------------------------------------------------
    // Compare two vectors and test if they are "approximately equal":
    //
    // equalWithAbsError (v, e)
    //
    //	    Returns true if the coefficients of this and v are the same with
    //	    an absolute error of no more than e, i.e., for all i
    //
    //      abs (this[i] - v[i]) <= e
    //
    // equalWithRelError (v, e)
    //
    //	    Returns true if the coefficients of this and v are the same with
    //	    a relative error of no more than e, i.e., for all i
    //
    //      abs (this[i] - v[i]) <= e * abs (this[i])
    //-----------------------------------------------------------------------

    IMATH_HOSTDEVICE IMATH_CONSTEXPR14 bool equalWithAbsError (const Vec3<T>& v, T e) const noexcept;
    IMATH_HOSTDEVICE IMATH_CONSTEXPR14 bool equalWithRelError (const Vec3<T>& v, T e) const noexcept;

    //------------
    // Dot product
    //------------

    IMATH_HOSTDEVICE constexpr T dot (const Vec3& v) const noexcept;
    IMATH_HOSTDEVICE constexpr T operator^ (const Vec3& v) const noexcept;

    //---------------------------
    // Right-handed cross product
    //---------------------------

    IMATH_HOSTDEVICE constexpr Vec3 cross (const Vec3& v) const noexcept;
    IMATH_HOSTDEVICE IMATH_CONSTEXPR14 const Vec3& operator%= (const Vec3& v) noexcept;
    IMATH_HOSTDEVICE constexpr Vec3 operator% (const Vec3& v) const noexcept;

    //------------------------
    // Component-wise addition
    //------------------------

    IMATH_HOSTDEVICE IMATH_CONSTEXPR14 const Vec3& operator+= (const Vec3& v) noexcept;
    IMATH_HOSTDEVICE constexpr Vec3 operator+ (const Vec3& v) const noexcept;

    //---------------------------
    // Component-wise subtraction
    //---------------------------

    IMATH_HOSTDEVICE IMATH_CONSTEXPR14 const Vec3& operator-= (const Vec3& v) noexcept;
    IMATH_HOSTDEVICE constexpr Vec3 operator- (const Vec3& v) const noexcept;

    //------------------------------------
    // Component-wise multiplication by -1
    //------------------------------------

    IMATH_HOSTDEVICE constexpr Vec3 operator-() const noexcept;
    IMATH_HOSTDEVICE IMATH_CONSTEXPR14 const Vec3& negate() noexcept;

    //------------------------------
    // Component-wise multiplication
    //------------------------------

    IMATH_HOSTDEVICE IMATH_CONSTEXPR14 const Vec3& operator*= (const Vec3& v) noexcept;
    IMATH_HOSTDEVICE IMATH_CONSTEXPR14 const Vec3& operator*= (T a) noexcept;
    IMATH_HOSTDEVICE constexpr Vec3 operator* (const Vec3& v) const noexcept;
    IMATH_HOSTDEVICE constexpr Vec3 operator* (T a) const noexcept;

    //------------------------
    // Component-wise division
    //------------------------

    IMATH_HOSTDEVICE IMATH_CONSTEXPR14 const Vec3& operator/= (const Vec3& v) noexcept;
    IMATH_HOSTDEVICE IMATH_CONSTEXPR14 const Vec3& operator/= (T a) noexcept;
    IMATH_HOSTDEVICE constexpr Vec3 operator/ (const Vec3& v) const noexcept;
    IMATH_HOSTDEVICE constexpr Vec3 operator/ (T a) const noexcept;

    //----------------------------------------------------------------
    // Length and normalization:  If v.length() is 0.0, v.normalize()
    // and v.normalized() produce a null vector; v.normalizeExc() and
    // v.normalizedExc() throw a std::domain_error.
    // v.normalizeNonNull() and v.normalizedNonNull() are slightly
    // faster than the other normalization routines, but if v.length()

    // is 0.0, the result is undefined.
    //----------------------------------------------------------------

    IMATH_HOSTDEVICE T length() const noexcept;
    IMATH_HOSTDEVICE constexpr T length2() const noexcept;

    IMATH_HOSTDEVICE const Vec3& normalize() noexcept; // modifies *this
    const Vec3& normalizeExc();
    IMATH_HOSTDEVICE const Vec3& normalizeNonNull() noexcept;

    IMATH_HOSTDEVICE Vec3<T> normalized() const noexcept; // does not modify *this
    Vec3<T> normalizedExc() const;
    IMATH_HOSTDEVICE Vec3<T> normalizedNonNull() const noexcept;

    //--------------------------------------------------------
    // Number of dimensions, i.e. number of elements in a Vec3
    //--------------------------------------------------------

    IMATH_HOSTDEVICE constexpr static unsigned int dimensions() noexcept { return 3; }

    //-------------------------------------------------
    // Limitations of type T (see also class limits<T>)
    //-------------------------------------------------

    IMATH_HOSTDEVICE constexpr static T baseTypeMin() noexcept { return limits<T>::min(); }
    IMATH_HOSTDEVICE constexpr static T baseTypeMax() noexcept { return limits<T>::max(); }
    IMATH_HOSTDEVICE constexpr static T baseTypeSmallest() noexcept { return limits<T>::smallest(); }
    IMATH_HOSTDEVICE constexpr static T baseTypeEpsilon() noexcept { return limits<T>::epsilon(); }

    //--------------------------------------------------------------
    // Base type -- in templates, which accept a parameter, V, which
    // could be either a Vec2<T>, a Vec3<T>, or a Vec4<T> you can
    // refer to T as V::BaseType
    //--------------------------------------------------------------

    typedef T BaseType;

  private:
    IMATH_HOSTDEVICE IMATH_CONSTEXPR14 T lengthTiny() const noexcept;
};

template <class T> class Vec4
{
  public:
    //-------------------
    // Access to elements
    //-------------------

    T x, y, z, w;

    IMATH_HOSTDEVICE IMATH_CONSTEXPR14 T& operator[] (int i) noexcept;
    IMATH_HOSTDEVICE constexpr const T& operator[] (int i) const noexcept;

    //-------------
    // Constructors
    //-------------

    IMATH_HOSTDEVICE constexpr Vec4() noexcept;                            // no initialization
    IMATH_HOSTDEVICE IMATH_CONSTEXPR14 explicit Vec4 (T a) noexcept;       // (a a a a)
    IMATH_HOSTDEVICE IMATH_CONSTEXPR14 Vec4 (T a, T b, T c, T d) noexcept; // (a b c d)

    //---------------------------------
    // Copy constructors and assignment
    //---------------------------------

    IMATH_HOSTDEVICE IMATH_CONSTEXPR14 Vec4 (const Vec4& v) noexcept;
    template <class S> IMATH_HOSTDEVICE IMATH_CONSTEXPR14 Vec4 (const Vec4<S>& v) noexcept;

    IMATH_HOSTDEVICE IMATH_CONSTEXPR14 const Vec4& operator= (const Vec4& v) noexcept;

    //-----------
    // Destructor
    //-----------

    ~Vec4() noexcept = default;

    //-------------------------------------
    // Vec3 to Vec4 conversion, sets w to 1
    //-------------------------------------

    template <class S> IMATH_HOSTDEVICE explicit IMATH_CONSTEXPR14 Vec4 (const Vec3<S>& v) noexcept;

    //---------
    // Equality
    //---------

    template <class S> IMATH_HOSTDEVICE constexpr bool operator== (const Vec4<S>& v) const noexcept;

    template <class S> IMATH_HOSTDEVICE constexpr bool operator!= (const Vec4<S>& v) const noexcept;

    //-----------------------------------------------------------------------
    // Compare two vectors and test if they are "approximately equal":
    //
    // equalWithAbsError (v, e)
    //
    //	    Returns true if the coefficients of this and v are the same with
    //	    an absolute error of no more than e, i.e., for all i
    //
    //      abs (this[i] - v[i]) <= e
    //
    // equalWithRelError (v, e)
    //
    //	    Returns true if the coefficients of this and v are the same with
    //	    a relative error of no more than e, i.e., for all i
    //
    //      abs (this[i] - v[i]) <= e * abs (this[i])
    //-----------------------------------------------------------------------

    IMATH_HOSTDEVICE IMATH_CONSTEXPR14 bool equalWithAbsError (const Vec4<T>& v, T e) const noexcept;
    IMATH_HOSTDEVICE IMATH_CONSTEXPR14 bool equalWithRelError (const Vec4<T>& v, T e) const noexcept;

    //------------
    // Dot product
    //------------

    IMATH_HOSTDEVICE constexpr T dot (const Vec4& v) const noexcept;
    IMATH_HOSTDEVICE constexpr T operator^ (const Vec4& v) const noexcept;

    //-----------------------------------
    // Cross product is not defined in 4D
    //-----------------------------------

    //------------------------
    // Component-wise addition
    //------------------------

    IMATH_HOSTDEVICE IMATH_CONSTEXPR14 const Vec4& operator+= (const Vec4& v) noexcept;
    IMATH_HOSTDEVICE constexpr Vec4 operator+ (const Vec4& v) const noexcept;

    //---------------------------
    // Component-wise subtraction
    //---------------------------

    IMATH_HOSTDEVICE IMATH_CONSTEXPR14 const Vec4& operator-= (const Vec4& v) noexcept;
    IMATH_HOSTDEVICE constexpr Vec4 operator- (const Vec4& v) const noexcept;

    //------------------------------------
    // Component-wise multiplication by -1
    //------------------------------------

    IMATH_HOSTDEVICE constexpr Vec4 operator-() const noexcept;
    IMATH_HOSTDEVICE IMATH_CONSTEXPR14 const Vec4& negate() noexcept;

    //------------------------------
    // Component-wise multiplication
    //------------------------------

    IMATH_HOSTDEVICE IMATH_CONSTEXPR14 const Vec4& operator*= (const Vec4& v) noexcept;
    IMATH_HOSTDEVICE IMATH_CONSTEXPR14 const Vec4& operator*= (T a) noexcept;
    IMATH_HOSTDEVICE constexpr Vec4 operator* (const Vec4& v) const noexcept;
    IMATH_HOSTDEVICE constexpr Vec4 operator* (T a) const noexcept;

    //------------------------
    // Component-wise division
    //------------------------

    IMATH_HOSTDEVICE IMATH_CONSTEXPR14 const Vec4& operator/= (const Vec4& v) noexcept;
    IMATH_HOSTDEVICE IMATH_CONSTEXPR14 const Vec4& operator/= (T a) noexcept;
    IMATH_HOSTDEVICE constexpr Vec4 operator/ (const Vec4& v) const noexcept;
    IMATH_HOSTDEVICE constexpr Vec4 operator/ (T a) const noexcept;

    //----------------------------------------------------------------
    // Length and normalization:  If v.length() is 0.0, v.normalize()
    // and v.normalized() produce a null vector; v.normalizeExc() and
    // v.normalizedExc() throw a std::domain_error.
    // v.normalizeNonNull() and v.normalizedNonNull() are slightly
    // faster than the other normalization routines, but if v.length()
    // is 0.0, the result is undefined.
    //----------------------------------------------------------------

    IMATH_HOSTDEVICE T length() const noexcept;
    IMATH_HOSTDEVICE constexpr T length2() const noexcept;

    IMATH_HOSTDEVICE const Vec4& normalize() noexcept; // modifies *this
    const Vec4& normalizeExc();
    IMATH_HOSTDEVICE const Vec4& normalizeNonNull() noexcept;

    IMATH_HOSTDEVICE Vec4<T> normalized() const noexcept; // does not modify *this
    Vec4<T> normalizedExc() const;
    IMATH_HOSTDEVICE Vec4<T> normalizedNonNull() const noexcept;

    //--------------------------------------------------------
    // Number of dimensions, i.e. number of elements in a Vec4
    //--------------------------------------------------------

    IMATH_HOSTDEVICE constexpr static unsigned int dimensions() noexcept { return 4; }

    //-------------------------------------------------
    // Limitations of type T (see also class limits<T>)
    //-------------------------------------------------

    IMATH_HOSTDEVICE constexpr static T baseTypeMin() noexcept { return limits<T>::min(); }
    IMATH_HOSTDEVICE constexpr static T baseTypeMax() noexcept { return limits<T>::max(); }
    IMATH_HOSTDEVICE constexpr static T baseTypeSmallest() noexcept { return limits<T>::smallest(); }
    IMATH_HOSTDEVICE constexpr static T baseTypeEpsilon() noexcept { return limits<T>::epsilon(); }

    //--------------------------------------------------------------
    // Base type -- in templates, which accept a parameter, V, which
    // could be either a Vec2<T>, a Vec3<T>, or a Vec4<T> you can
    // refer to T as V::BaseType
    //--------------------------------------------------------------

    typedef T BaseType;

  private:
    IMATH_HOSTDEVICE IMATH_CONSTEXPR14 T lengthTiny() const noexcept;
};

//--------------
// Stream output
//--------------

template <class T> std::ostream& operator<< (std::ostream& s, const Vec2<T>& v);

template <class T> std::ostream& operator<< (std::ostream& s, const Vec3<T>& v);

template <class T> std::ostream& operator<< (std::ostream& s, const Vec4<T>& v);

//----------------------------------------------------
// Reverse multiplication: S * Vec2<T> and S * Vec3<T>
//----------------------------------------------------

template <class T> IMATH_HOSTDEVICE constexpr Vec2<T> operator* (T a, const Vec2<T>& v) noexcept;
template <class T> IMATH_HOSTDEVICE constexpr Vec3<T> operator* (T a, const Vec3<T>& v) noexcept;
template <class T> IMATH_HOSTDEVICE constexpr Vec4<T> operator* (T a, const Vec4<T>& v) noexcept;

//-------------------------
// Typedefs for convenience
//-------------------------

typedef Vec2<short> V2s;
typedef Vec2<int> V2i;
typedef Vec2<float> V2f;
typedef Vec2<double> V2d;
typedef Vec3<short> V3s;
typedef Vec3<int> V3i;
typedef Vec3<float> V3f;
typedef Vec3<double> V3d;
typedef Vec4<short> V4s;
typedef Vec4<int> V4i;
typedef Vec4<float> V4f;
typedef Vec4<double> V4d;

//-------------------------------------------
// Specializations for VecN<short>, VecN<int>
// Normalize and length don't make sense for integer vectors, so disable them.
//-------------------------------------------

// Vec2<short>
template <> short Vec2<short>::length() const noexcept = delete;
template <> const Vec2<short>& Vec2<short>::normalize() noexcept = delete;
template <> const Vec2<short>& Vec2<short>::normalizeExc() = delete;
template <> const Vec2<short>& Vec2<short>::normalizeNonNull() noexcept = delete;
template <> Vec2<short> Vec2<short>::normalized() const noexcept = delete;
template <> Vec2<short> Vec2<short>::normalizedExc() const = delete;
template <> Vec2<short> Vec2<short>::normalizedNonNull() const noexcept = delete;

// Vec2<int>
template <> int Vec2<int>::length() const noexcept = delete;
template <> const Vec2<int>& Vec2<int>::normalize() noexcept = delete;
template <> const Vec2<int>& Vec2<int>::normalizeExc() = delete;
template <> const Vec2<int>& Vec2<int>::normalizeNonNull() noexcept = delete;
template <> Vec2<int> Vec2<int>::normalized() const noexcept = delete;
template <> Vec2<int> Vec2<int>::normalizedExc() const = delete;
template <> Vec2<int> Vec2<int>::normalizedNonNull() const noexcept = delete;

// Vec3<short>
template <> short Vec3<short>::length() const noexcept = delete;
template <> const Vec3<short>& Vec3<short>::normalize() noexcept = delete;
template <> const Vec3<short>& Vec3<short>::normalizeExc() = delete;
template <> const Vec3<short>& Vec3<short>::normalizeNonNull() noexcept = delete;
template <> Vec3<short> Vec3<short>::normalized() const noexcept = delete;
template <> Vec3<short> Vec3<short>::normalizedExc() const = delete;
template <> Vec3<short> Vec3<short>::normalizedNonNull() const noexcept = delete;

// Vec3<int>
template <> int Vec3<int>::length() const noexcept = delete;
template <> const Vec3<int>& Vec3<int>::normalize() noexcept = delete;
template <> const Vec3<int>& Vec3<int>::normalizeExc() = delete;
template <> const Vec3<int>& Vec3<int>::normalizeNonNull() noexcept = delete;
template <> Vec3<int> Vec3<int>::normalized() const noexcept = delete;
template <> Vec3<int> Vec3<int>::normalizedExc() const = delete;
template <> Vec3<int> Vec3<int>::normalizedNonNull() const noexcept = delete;

// Vec4<short>
template <> short Vec4<short>::length() const noexcept = delete;
template <> const Vec4<short>& Vec4<short>::normalize() noexcept = delete;
template <> const Vec4<short>& Vec4<short>::normalizeExc() = delete;
template <> const Vec4<short>& Vec4<short>::normalizeNonNull() noexcept = delete;
template <> Vec4<short> Vec4<short>::normalized() const noexcept = delete;
template <> Vec4<short> Vec4<short>::normalizedExc() const = delete;
template <> Vec4<short> Vec4<short>::normalizedNonNull() const noexcept = delete;

// Vec4<int>
template <> int Vec4<int>::length() const noexcept = delete;
template <> const Vec4<int>& Vec4<int>::normalize() noexcept = delete;
template <> const Vec4<int>& Vec4<int>::normalizeExc() = delete;
template <> const Vec4<int>& Vec4<int>::normalizeNonNull() noexcept = delete;
template <> Vec4<int> Vec4<int>::normalized() const noexcept = delete;
template <> Vec4<int> Vec4<int>::normalizedExc() const = delete;
template <> Vec4<int> Vec4<int>::normalizedNonNull() const noexcept = delete;

//------------------------
// Implementation of Vec2:
//------------------------

template <class T>
IMATH_CONSTEXPR14 inline T&
Vec2<T>::operator[] (int i) noexcept
{
    return (&x)[i]; // NOSONAR - suppress SonarCloud bug report.
}

template <class T>
constexpr inline const T&
Vec2<T>::operator[] (int i) const noexcept
{
    return (&x)[i]; // NOSONAR - suppress SonarCloud bug report.
}

template <class T> inline Vec2<T>::Vec2() noexcept
{
    // empty
}

template <class T> IMATH_CONSTEXPR14 inline Vec2<T>::Vec2 (T a) noexcept
{
    x = y = a;
}

template <class T> IMATH_CONSTEXPR14 inline Vec2<T>::Vec2 (T a, T b) noexcept
{
    x = a;
    y = b;
}

template <class T> IMATH_CONSTEXPR14 inline Vec2<T>::Vec2 (const Vec2& v) noexcept
{
    x = v.x;
    y = v.y;
}

template <class T> template <class S> IMATH_CONSTEXPR14 inline Vec2<T>::Vec2 (const Vec2<S>& v) noexcept
{
    x = T (v.x);
    y = T (v.y);
}

template <class T>
IMATH_CONSTEXPR14 inline const Vec2<T>&
Vec2<T>::operator= (const Vec2& v) noexcept
{
    x = v.x;
    y = v.y;
    return *this;
}

template <class T>
template <class S>
inline void
Vec2<T>::setValue (S a, S b) noexcept
{
    x = T (a);
    y = T (b);
}

template <class T>
template <class S>
inline void
Vec2<T>::setValue (const Vec2<S>& v) noexcept
{
    x = T (v.x);
    y = T (v.y);
}

template <class T>
template <class S>
inline void
Vec2<T>::getValue (S& a, S& b) const noexcept
{
    a = S (x);
    b = S (y);
}

template <class T>
template <class S>
inline void
Vec2<T>::getValue (Vec2<S>& v) const noexcept
{
    v.x = S (x);
    v.y = S (y);
}

template <class T>
inline T*
Vec2<T>::getValue() noexcept
{
    return (T*) &x;
}

template <class T>
inline const T*
Vec2<T>::getValue() const noexcept
{
    return (const T*) &x;
}

template <class T>
template <class S>
constexpr inline bool
Vec2<T>::operator== (const Vec2<S>& v) const noexcept
{
    return x == v.x && y == v.y;
}

template <class T>
template <class S>
constexpr inline bool
Vec2<T>::operator!= (const Vec2<S>& v) const noexcept
{
    return x != v.x || y != v.y;
}

template <class T>
IMATH_CONSTEXPR14 inline bool
Vec2<T>::equalWithAbsError (const Vec2<T>& v, T e) const noexcept
{
    for (int i = 0; i < 2; i++)
        if (!IMATH_INTERNAL_NAMESPACE::equalWithAbsError ((*this)[i], v[i], e))
            return false;

    return true;
}

template <class T>
IMATH_CONSTEXPR14 inline bool
Vec2<T>::equalWithRelError (const Vec2<T>& v, T e) const noexcept
{
    for (int i = 0; i < 2; i++)
        if (!IMATH_INTERNAL_NAMESPACE::equalWithRelError ((*this)[i], v[i], e))
            return false;

    return true;
}

template <class T>
constexpr inline T
Vec2<T>::dot (const Vec2& v) const noexcept
{
    return x * v.x + y * v.y;
}

template <class T>
constexpr inline T
Vec2<T>::operator^ (const Vec2& v) const noexcept
{
    return dot (v);
}

template <class T>
constexpr inline T
Vec2<T>::cross (const Vec2& v) const noexcept
{
    return x * v.y - y * v.x;
}

template <class T>
constexpr inline T
Vec2<T>::operator% (const Vec2& v) const noexcept
{
    return x * v.y - y * v.x;
}

template <class T>
IMATH_CONSTEXPR14 inline const Vec2<T>&
Vec2<T>::operator+= (const Vec2& v) noexcept
{
    x += v.x;
    y += v.y;
    return *this;
}

template <class T>
constexpr inline Vec2<T>
Vec2<T>::operator+ (const Vec2& v) const noexcept
{
    return Vec2 (x + v.x, y + v.y);
}

template <class T>
IMATH_CONSTEXPR14 inline const Vec2<T>&
Vec2<T>::operator-= (const Vec2& v) noexcept
{
    x -= v.x;
    y -= v.y;
    return *this;
}

template <class T>
constexpr inline Vec2<T>
Vec2<T>::operator- (const Vec2& v) const noexcept
{
    return Vec2 (x - v.x, y - v.y);
}

template <class T>
constexpr inline Vec2<T>
Vec2<T>::operator-() const noexcept
{
    return Vec2 (-x, -y);
}

template <class T>
IMATH_CONSTEXPR14 inline const Vec2<T>&
Vec2<T>::negate() noexcept
{
    x = -x;
    y = -y;
    return *this;
}

template <class T>
IMATH_CONSTEXPR14 inline const Vec2<T>&
Vec2<T>::operator*= (const Vec2& v) noexcept
{
    x *= v.x;
    y *= v.y;
    return *this;
}

template <class T>
IMATH_CONSTEXPR14 inline const Vec2<T>&
Vec2<T>::operator*= (T a) noexcept
{
    x *= a;
    y *= a;
    return *this;
}

template <class T>
constexpr inline Vec2<T>
Vec2<T>::operator* (const Vec2& v) const noexcept
{
    return Vec2 (x * v.x, y * v.y);
}

template <class T>
constexpr inline Vec2<T>
Vec2<T>::operator* (T a) const noexcept
{
    return Vec2 (x * a, y * a);
}

template <class T>
IMATH_CONSTEXPR14 inline const Vec2<T>&
Vec2<T>::operator/= (const Vec2& v) noexcept
{
    x /= v.x;
    y /= v.y;
    return *this;
}

template <class T>
IMATH_CONSTEXPR14 inline const Vec2<T>&
Vec2<T>::operator/= (T a) noexcept
{
    x /= a;
    y /= a;
    return *this;
}

template <class T>
constexpr inline Vec2<T>
Vec2<T>::operator/ (const Vec2& v) const noexcept
{
    return Vec2 (x / v.x, y / v.y);
}

template <class T>
constexpr inline Vec2<T>
Vec2<T>::operator/ (T a) const noexcept
{
    return Vec2 (x / a, y / a);
}

template <class T>
IMATH_CONSTEXPR14 inline T
Vec2<T>::lengthTiny() const noexcept
{
    T absX = std::abs(x);
    T absY = std::abs(y);

    T max = absX;

    if (max < absY)
        max = absY;

    if (IMATH_UNLIKELY(max == T (0)))
        return T (0);

    //
    // Do not replace the divisions by max with multiplications by 1/max.
    // Computing 1/max can overflow but the divisions below will always
    // produce results less than or equal to 1.
    //

    absX /= max;
    absY /= max;

    return max * std::sqrt (absX * absX + absY * absY);
}

template <class T>
inline T
Vec2<T>::length() const noexcept
{
    T length2 = dot (*this);

    if (IMATH_UNLIKELY(length2 < T (2) * limits<T>::smallest()))
        return lengthTiny();

    return std::sqrt (length2);
}

template <class T>
constexpr inline T
Vec2<T>::length2() const noexcept
{
    return dot (*this);
}

template <class T>
inline const Vec2<T>&
Vec2<T>::normalize() noexcept
{
    T l = length();

    if (IMATH_LIKELY(l != T (0)))
    {
        //
        // Do not replace the divisions by l with multiplications by 1/l.
        // Computing 1/l can overflow but the divisions below will always
        // produce results less than or equal to 1.
        //

        x /= l;
        y /= l;
    }

    return *this;
}

template <class T>
inline const Vec2<T>&
Vec2<T>::normalizeExc()
{
    T l = length();

    if (IMATH_UNLIKELY(l == T (0)))
        throw std::domain_error ("Cannot normalize null vector.");

    x /= l;
    y /= l;
    return *this;
}

template <class T>
inline const Vec2<T>&
Vec2<T>::normalizeNonNull() noexcept
{
    T l = length();
    x /= l;
    y /= l;
    return *this;
}

template <class T>
inline Vec2<T>
Vec2<T>::normalized() const noexcept
{
    T l = length();

    if (IMATH_UNLIKELY(l == T (0)))
        return Vec2 (T (0));

    return Vec2 (x / l, y / l);
}

template <class T>
inline Vec2<T>
Vec2<T>::normalizedExc() const
{
    T l = length();

    if (IMATH_UNLIKELY(l == T (0)))
        throw std::domain_error ("Cannot normalize null vector.");

    return Vec2 (x / l, y / l);
}

template <class T>
inline Vec2<T>
Vec2<T>::normalizedNonNull() const noexcept
{
    T l = length();
    return Vec2 (x / l, y / l);
}

//-----------------------
// Implementation of Vec3
//-----------------------

template <class T>
IMATH_CONSTEXPR14 inline T&
Vec3<T>::operator[] (int i) noexcept
{
    return (&x)[i]; // NOSONAR - suppress SonarCloud bug report.
}

template <class T>
constexpr inline const T&
Vec3<T>::operator[] (int i) const noexcept
{
    return (&x)[i]; // NOSONAR - suppress SonarCloud bug report.
}

template <class T> constexpr inline Vec3<T>::Vec3() noexcept
{
    // empty
}

template <class T> IMATH_CONSTEXPR14 inline Vec3<T>::Vec3 (T a) noexcept
{
    x = y = z = a;
}

template <class T> IMATH_CONSTEXPR14 inline Vec3<T>::Vec3 (T a, T b, T c) noexcept
{
    x = a;
    y = b;
    z = c;
}

template <class T> IMATH_CONSTEXPR14 inline Vec3<T>::Vec3 (const Vec3& v) noexcept
{
    x = v.x;
    y = v.y;
    z = v.z;
}

template <class T> template <class S> IMATH_CONSTEXPR14 inline Vec3<T>::Vec3 (const Vec3<S>& v) noexcept
{
    x = T (v.x);
    y = T (v.y);
    z = T (v.z);
}

template <class T>
IMATH_CONSTEXPR14 inline const Vec3<T>&
Vec3<T>::operator= (const Vec3& v) noexcept
{
    x = v.x;
    y = v.y;
    z = v.z;
    return *this;
}

template <class T> template <class S> IMATH_CONSTEXPR14 inline Vec3<T>::Vec3 (const Vec4<S>& v) noexcept
{
    x = T (v.x / v.w);
    y = T (v.y / v.w);
    z = T (v.z / v.w);
}

template <class T>
template <class S>
IMATH_CONSTEXPR14 inline Vec3<T>::Vec3 (const Vec4<S>& v, InfException)
{
    T vx = T (v.x);
    T vy = T (v.y);
    T vz = T (v.z);
    T vw = T (v.w);

    T absW = (vw >= T (0)) ? vw : -vw;

    if (absW < 1)
    {
        T m = baseTypeMax() * absW;

        if (vx <= -m || vx >= m || vy <= -m || vy >= m || vz <= -m || vz >= m)
            throw std::domain_error ("Cannot normalize point at infinity.");
    }

    x = vx / vw;
    y = vy / vw;
    z = vz / vw;
}

template <class T>
template <class S>
inline void
Vec3<T>::setValue (S a, S b, S c) noexcept
{
    x = T (a);
    y = T (b);
    z = T (c);
}

template <class T>
template <class S>
inline void
Vec3<T>::setValue (const Vec3<S>& v) noexcept
{
    x = T (v.x);
    y = T (v.y);
    z = T (v.z);
}

template <class T>
template <class S>
inline void
Vec3<T>::getValue (S& a, S& b, S& c) const noexcept
{
    a = S (x);
    b = S (y);
    c = S (z);
}

template <class T>
template <class S>
inline void
Vec3<T>::getValue (Vec3<S>& v) const noexcept
{
    v.x = S (x);
    v.y = S (y);
    v.z = S (z);
}

template <class T>
inline T*
Vec3<T>::getValue() noexcept
{
    return (T*) &x;
}

template <class T>
inline const T*
Vec3<T>::getValue() const noexcept
{
    return (const T*) &x;
}

template <class T>
template <class S>
constexpr inline bool
Vec3<T>::operator== (const Vec3<S>& v) const noexcept
{
    return x == v.x && y == v.y && z == v.z;
}

template <class T>
template <class S>
constexpr inline bool
Vec3<T>::operator!= (const Vec3<S>& v) const noexcept
{
    return x != v.x || y != v.y || z != v.z;
}

template <class T>
IMATH_CONSTEXPR14 inline bool
Vec3<T>::equalWithAbsError (const Vec3<T>& v, T e) const noexcept
{
    for (int i = 0; i < 3; i++)
        if (!IMATH_INTERNAL_NAMESPACE::equalWithAbsError ((*this)[i], v[i], e))
            return false;

    return true;
}

template <class T>
IMATH_CONSTEXPR14 inline bool
Vec3<T>::equalWithRelError (const Vec3<T>& v, T e) const noexcept
{
    for (int i = 0; i < 3; i++)
        if (!IMATH_INTERNAL_NAMESPACE::equalWithRelError ((*this)[i], v[i], e))
            return false;

    return true;
}

template <class T>
constexpr inline T
Vec3<T>::dot (const Vec3& v) const noexcept
{
    return x * v.x + y * v.y + z * v.z;
}

template <class T>
constexpr inline T
Vec3<T>::operator^ (const Vec3& v) const noexcept
{
    return dot (v);
}

template <class T>
constexpr inline Vec3<T>
Vec3<T>::cross (const Vec3& v) const noexcept
{
    return Vec3 (y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x);
}

template <class T>
IMATH_CONSTEXPR14 inline const Vec3<T>&
Vec3<T>::operator%= (const Vec3& v) noexcept
{
    T a = y * v.z - z * v.y;
    T b = z * v.x - x * v.z;
    T c = x * v.y - y * v.x;
    x   = a;
    y   = b;
    z   = c;
    return *this;
}

template <class T>
constexpr inline Vec3<T>
Vec3<T>::operator% (const Vec3& v) const noexcept
{
    return Vec3 (y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x);
}

template <class T>
IMATH_CONSTEXPR14 inline const Vec3<T>&
Vec3<T>::operator+= (const Vec3& v) noexcept
{
    x += v.x;
    y += v.y;
    z += v.z;
    return *this;
}

template <class T>
constexpr inline Vec3<T>
Vec3<T>::operator+ (const Vec3& v) const noexcept
{
    return Vec3 (x + v.x, y + v.y, z + v.z);
}

template <class T>
IMATH_CONSTEXPR14 inline const Vec3<T>&
Vec3<T>::operator-= (const Vec3& v) noexcept
{
    x -= v.x;
    y -= v.y;
    z -= v.z;
    return *this;
}

template <class T>
constexpr inline Vec3<T>
Vec3<T>::operator- (const Vec3& v) const noexcept
{
    return Vec3 (x - v.x, y - v.y, z - v.z);
}

template <class T>
constexpr inline Vec3<T>
Vec3<T>::operator-() const noexcept
{
    return Vec3 (-x, -y, -z);
}

template <class T>
IMATH_CONSTEXPR14 inline const Vec3<T>&
Vec3<T>::negate() noexcept
{
    x = -x;
    y = -y;
    z = -z;
    return *this;
}

template <class T>
IMATH_CONSTEXPR14 inline const Vec3<T>&
Vec3<T>::operator*= (const Vec3& v) noexcept
{
    x *= v.x;
    y *= v.y;
    z *= v.z;
    return *this;
}

template <class T>
IMATH_CONSTEXPR14 inline const Vec3<T>&
Vec3<T>::operator*= (T a) noexcept
{
    x *= a;
    y *= a;
    z *= a;
    return *this;
}

template <class T>
constexpr inline Vec3<T>
Vec3<T>::operator* (const Vec3& v) const noexcept
{
    return Vec3 (x * v.x, y * v.y, z * v.z);
}

template <class T>
constexpr inline Vec3<T>
Vec3<T>::operator* (T a) const noexcept
{
    return Vec3 (x * a, y * a, z * a);
}

template <class T>
IMATH_CONSTEXPR14 inline const Vec3<T>&
Vec3<T>::operator/= (const Vec3& v) noexcept
{
    x /= v.x;
    y /= v.y;
    z /= v.z;
    return *this;
}

template <class T>
IMATH_CONSTEXPR14 inline const Vec3<T>&
Vec3<T>::operator/= (T a) noexcept
{
    x /= a;
    y /= a;
    z /= a;
    return *this;
}

template <class T>
constexpr inline Vec3<T>
Vec3<T>::operator/ (const Vec3& v) const noexcept
{
    return Vec3 (x / v.x, y / v.y, z / v.z);
}

template <class T>
constexpr inline Vec3<T>
Vec3<T>::operator/ (T a) const noexcept
{
    return Vec3 (x / a, y / a, z / a);
}

template <class T>
IMATH_CONSTEXPR14 inline T
Vec3<T>::lengthTiny() const noexcept
{
    T absX = (x >= T (0)) ? x : -x;
    T absY = (y >= T (0)) ? y : -y;
    T absZ = (z >= T (0)) ? z : -z;

    T max = absX;

    if (max < absY)
        max = absY;

    if (max < absZ)
        max = absZ;

    if (IMATH_UNLIKELY(max == T (0)))
        return T (0);

    //
    // Do not replace the divisions by max with multiplications by 1/max.
    // Computing 1/max can overflow but the divisions below will always
    // produce results less than or equal to 1.
    //

    absX /= max;
    absY /= max;
    absZ /= max;

    return max * std::sqrt (absX * absX + absY * absY + absZ * absZ);
}

template <class T>
inline T
Vec3<T>::length() const noexcept
{
    T length2 = dot (*this);

    if (IMATH_UNLIKELY(length2 < T (2) * limits<T>::smallest()))
        return lengthTiny();

    return std::sqrt (length2);
}

template <class T>
constexpr inline T
Vec3<T>::length2() const noexcept
{
    return dot (*this);
}

template <class T>
inline const Vec3<T>&
Vec3<T>::normalize() noexcept
{
    T l = length();

    if (IMATH_LIKELY(l != T (0)))
    {
        //
        // Do not replace the divisions by l with multiplications by 1/l.
        // Computing 1/l can overflow but the divisions below will always
        // produce results less than or equal to 1.
        //

        x /= l;
        y /= l;
        z /= l;
    }

    return *this;
}

template <class T>
inline const Vec3<T>&
Vec3<T>::normalizeExc()
{
    T l = length();

    if (IMATH_UNLIKELY(l == T (0)))
        throw std::domain_error ("Cannot normalize null vector.");

    x /= l;
    y /= l;
    z /= l;
    return *this;
}

template <class T>
inline const Vec3<T>&
Vec3<T>::normalizeNonNull() noexcept
{
    T l = length();
    x /= l;
    y /= l;
    z /= l;
    return *this;
}

template <class T>
inline Vec3<T>
Vec3<T>::normalized() const noexcept
{
    T l = length();

    if (IMATH_UNLIKELY((l == T (0))))
        return Vec3 (T (0));

    return Vec3 (x / l, y / l, z / l);
}

template <class T>
inline Vec3<T>
Vec3<T>::normalizedExc() const
{
    T l = length();

    if (IMATH_UNLIKELY(l == T (0)))
        throw std::domain_error ("Cannot normalize null vector.");

    return Vec3 (x / l, y / l, z / l);
}

template <class T>
inline Vec3<T>
Vec3<T>::normalizedNonNull() const noexcept
{
    T l = length();
    return Vec3 (x / l, y / l, z / l);
}

//-----------------------
// Implementation of Vec4
//-----------------------

template <class T>
IMATH_CONSTEXPR14 inline T&
Vec4<T>::operator[] (int i) noexcept
{
    return (&x)[i]; // NOSONAR - suppress SonarCloud bug report.
}

template <class T>
constexpr inline const T&
Vec4<T>::operator[] (int i) const noexcept
{
    return (&x)[i]; // NOSONAR - suppress SonarCloud bug report.
}

template <class T> constexpr inline Vec4<T>::Vec4() noexcept
{
    // empty
}

template <class T> IMATH_CONSTEXPR14 inline Vec4<T>::Vec4 (T a) noexcept
{
    x = y = z = w = a;
}

template <class T> IMATH_CONSTEXPR14 inline Vec4<T>::Vec4 (T a, T b, T c, T d) noexcept
{
    x = a;
    y = b;
    z = c;
    w = d;
}

template <class T> IMATH_CONSTEXPR14 inline Vec4<T>::Vec4 (const Vec4& v) noexcept
{
    x = v.x;
    y = v.y;
    z = v.z;
    w = v.w;
}

template <class T> template <class S> IMATH_CONSTEXPR14 inline Vec4<T>::Vec4 (const Vec4<S>& v) noexcept
{
    x = T (v.x);
    y = T (v.y);
    z = T (v.z);
    w = T (v.w);
}

template <class T>
IMATH_CONSTEXPR14 inline const Vec4<T>&
Vec4<T>::operator= (const Vec4& v) noexcept
{
    x = v.x;
    y = v.y;
    z = v.z;
    w = v.w;
    return *this;
}

template <class T> template <class S> IMATH_CONSTEXPR14 inline Vec4<T>::Vec4 (const Vec3<S>& v) noexcept
{
    x = T (v.x);
    y = T (v.y);
    z = T (v.z);
    w = T (1);
}

template <class T>
template <class S>
constexpr inline bool
Vec4<T>::operator== (const Vec4<S>& v) const noexcept
{
    return x == v.x && y == v.y && z == v.z && w == v.w;
}

template <class T>
template <class S>
constexpr inline bool
Vec4<T>::operator!= (const Vec4<S>& v) const noexcept
{
    return x != v.x || y != v.y || z != v.z || w != v.w;
}

template <class T>
IMATH_CONSTEXPR14 inline bool
Vec4<T>::equalWithAbsError (const Vec4<T>& v, T e) const noexcept
{
    for (int i = 0; i < 4; i++)
        if (!IMATH_INTERNAL_NAMESPACE::equalWithAbsError ((*this)[i], v[i], e))
            return false;

    return true;
}

template <class T>
IMATH_CONSTEXPR14 inline bool
Vec4<T>::equalWithRelError (const Vec4<T>& v, T e) const noexcept
{
    for (int i = 0; i < 4; i++)
        if (!IMATH_INTERNAL_NAMESPACE::equalWithRelError ((*this)[i], v[i], e))
            return false;

    return true;
}

template <class T>
constexpr inline T
Vec4<T>::dot (const Vec4& v) const noexcept
{
    return x * v.x + y * v.y + z * v.z + w * v.w;
}

template <class T>
constexpr inline T
Vec4<T>::operator^ (const Vec4& v) const noexcept
{
    return dot (v);
}

template <class T>
IMATH_CONSTEXPR14 inline const Vec4<T>&
Vec4<T>::operator+= (const Vec4& v) noexcept
{
    x += v.x;
    y += v.y;
    z += v.z;
    w += v.w;
    return *this;
}

template <class T>
constexpr inline Vec4<T>
Vec4<T>::operator+ (const Vec4& v) const noexcept
{
    return Vec4 (x + v.x, y + v.y, z + v.z, w + v.w);
}

template <class T>
IMATH_CONSTEXPR14 inline const Vec4<T>&
Vec4<T>::operator-= (const Vec4& v) noexcept
{
    x -= v.x;
    y -= v.y;
    z -= v.z;
    w -= v.w;
    return *this;
}

template <class T>
constexpr inline Vec4<T>
Vec4<T>::operator- (const Vec4& v) const noexcept
{
    return Vec4 (x - v.x, y - v.y, z - v.z, w - v.w);
}

template <class T>
constexpr inline Vec4<T>
Vec4<T>::operator-() const noexcept
{
    return Vec4 (-x, -y, -z, -w);
}

template <class T>
IMATH_CONSTEXPR14 inline const Vec4<T>&
Vec4<T>::negate() noexcept
{
    x = -x;
    y = -y;
    z = -z;
    w = -w;
    return *this;
}

template <class T>
IMATH_CONSTEXPR14 inline const Vec4<T>&
Vec4<T>::operator*= (const Vec4& v) noexcept
{
    x *= v.x;
    y *= v.y;
    z *= v.z;
    w *= v.w;
    return *this;
}

template <class T>
IMATH_CONSTEXPR14 inline const Vec4<T>&
Vec4<T>::operator*= (T a) noexcept
{
    x *= a;
    y *= a;
    z *= a;
    w *= a;
    return *this;
}

template <class T>
constexpr inline Vec4<T>
Vec4<T>::operator* (const Vec4& v) const noexcept
{
    return Vec4 (x * v.x, y * v.y, z * v.z, w * v.w);
}

template <class T>
constexpr inline Vec4<T>
Vec4<T>::operator* (T a) const noexcept
{
    return Vec4 (x * a, y * a, z * a, w * a);
}

template <class T>
IMATH_CONSTEXPR14 inline const Vec4<T>&
Vec4<T>::operator/= (const Vec4& v) noexcept
{
    x /= v.x;
    y /= v.y;
    z /= v.z;
    w /= v.w;
    return *this;
}

template <class T>
IMATH_CONSTEXPR14 inline const Vec4<T>&
Vec4<T>::operator/= (T a) noexcept
{
    x /= a;
    y /= a;
    z /= a;
    w /= a;
    return *this;
}

template <class T>
constexpr inline Vec4<T>
Vec4<T>::operator/ (const Vec4& v) const noexcept
{
    return Vec4 (x / v.x, y / v.y, z / v.z, w / v.w);
}

template <class T>
constexpr inline Vec4<T>
Vec4<T>::operator/ (T a) const noexcept
{
    return Vec4 (x / a, y / a, z / a, w / a);
}

template <class T>
IMATH_CONSTEXPR14 inline T
Vec4<T>::lengthTiny() const noexcept
{
    T absX = (x >= T (0)) ? x : -x;
    T absY = (y >= T (0)) ? y : -y;
    T absZ = (z >= T (0)) ? z : -z;
    T absW = (w >= T (0)) ? w : -w;

    T max = absX;

    if (max < absY)
        max = absY;

    if (max < absZ)
        max = absZ;

    if (max < absW)
        max = absW;

    if (IMATH_UNLIKELY(max == T (0)))
        return T (0);

    //
    // Do not replace the divisions by max with multiplications by 1/max.
    // Computing 1/max can overflow but the divisions below will always
    // produce results less than or equal to 1.
    //

    absX /= max;
    absY /= max;
    absZ /= max;
    absW /= max;

    return max * std::sqrt (absX * absX + absY * absY + absZ * absZ + absW * absW);
}

template <class T>
inline T
Vec4<T>::length() const noexcept
{
    T length2 = dot (*this);

    if (IMATH_UNLIKELY(length2 < T (2) * limits<T>::smallest()))
        return lengthTiny();

    return std::sqrt (length2);
}

template <class T>
constexpr inline T
Vec4<T>::length2() const noexcept
{
    return dot (*this);
}

template <class T>
const inline Vec4<T>&
Vec4<T>::normalize() noexcept
{
    T l = length();

    if (IMATH_LIKELY(l != T (0)))
    {
        //
        // Do not replace the divisions by l with multiplications by 1/l.
        // Computing 1/l can overflow but the divisions below will always
        // produce results less than or equal to 1.
        //

        x /= l;
        y /= l;
        z /= l;
        w /= l;
    }

    return *this;
}

template <class T>
const inline Vec4<T>&
Vec4<T>::normalizeExc()
{
    T l = length();

    if (IMATH_UNLIKELY(l == T (0)))
        throw std::domain_error ("Cannot normalize null vector.");

    x /= l;
    y /= l;
    z /= l;
    w /= l;
    return *this;
}

template <class T>
inline const Vec4<T>&
Vec4<T>::normalizeNonNull() noexcept
{
    T l = length();
    x /= l;
    y /= l;
    z /= l;
    w /= l;
    return *this;
}

template <class T>
inline Vec4<T>
Vec4<T>::normalized() const noexcept
{
    T l = length();

    if (IMATH_UNLIKELY(l == T (0)))
        return Vec4 (T (0));

    return Vec4 (x / l, y / l, z / l, w / l);
}

template <class T>
inline Vec4<T>
Vec4<T>::normalizedExc() const
{
    T l = length();

    if (IMATH_UNLIKELY(l == T (0)))
        throw std::domain_error ("Cannot normalize null vector.");

    return Vec4 (x / l, y / l, z / l, w / l);
}

template <class T>
inline Vec4<T>
Vec4<T>::normalizedNonNull() const noexcept
{
    T l = length();
    return Vec4 (x / l, y / l, z / l, w / l);
}

//-----------------------------
// Stream output implementation
//-----------------------------

template <class T>
std::ostream&
operator<< (std::ostream& s, const Vec2<T>& v)
{
    return s << '(' << v.x << ' ' << v.y << ')';
}

template <class T>
std::ostream&
operator<< (std::ostream& s, const Vec3<T>& v)
{
    return s << '(' << v.x << ' ' << v.y << ' ' << v.z << ')';
}

template <class T>
std::ostream&
operator<< (std::ostream& s, const Vec4<T>& v)
{
    return s << '(' << v.x << ' ' << v.y << ' ' << v.z << ' ' << v.w << ')';
}

//-----------------------------------------
// Implementation of reverse multiplication
//-----------------------------------------

template <class T>
constexpr inline Vec2<T>
operator* (T a, const Vec2<T>& v) noexcept
{
    return Vec2<T> (a * v.x, a * v.y);
}

template <class T>
constexpr inline Vec3<T>
operator* (T a, const Vec3<T>& v) noexcept
{
    return Vec3<T> (a * v.x, a * v.y, a * v.z);
}

template <class T>
constexpr inline Vec4<T>
operator* (T a, const Vec4<T>& v) noexcept
{
    return Vec4<T> (a * v.x, a * v.y, a * v.z, a * v.w);
}

#if (defined _WIN32 || defined _WIN64) && defined _MSC_VER
#    pragma warning(pop)
#endif

IMATH_INTERNAL_NAMESPACE_HEADER_EXIT

#endif // INCLUDED_IMATHVEC_H
