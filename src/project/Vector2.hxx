#include "Vector2.h"

#include <ostream>

/// \brief Creates a new two-dimensional vector at the origin.
template<typename T>
Vector2<T>::Vector2()
    : X(), Y()
{ }

/// \brief Creates a new two-dimensional vector from the given
/// coordinates.
template<typename T>
Vector2<T>::Vector2(T X, T Y)
    : X(X), Y(Y)
{ }


/// \brief Adds two vectors together.
template<typename T>
Vector2<T> Vector2<T>::operator+(Vector2<T> Other) const
{
    return Vector2<T>(this->X + Other.X, this->Y + Other.Y);
}

/// \brief Subtracts the given vector from this vector.
template<typename T>
Vector2<T> Vector2<T>::operator-(Vector2<T> Other) const
{
    return Vector2<T>(this->X - Other.X, this->Y - Other.Y);
}

/// \brief Multiplies this vector with a scalar.
template<typename T>
Vector2<T> Vector2<T>::operator*(T Scalar) const
{
    return Vector2<T>(this->X * Scalar, this->Y * Scalar);
}

/// \brief Checks if this vector equals the given vector.
template<typename T>
bool Vector2<T>::operator==(Vector2<T> Other) const
{
    return this->X == Other.X && this->Y == Other.Y;
}

/// \brief Checks if this vector is not equal to the given vector.
template<typename T>
bool Vector2<T>::operator!=(Vector2<T> Other) const
{
    return this->X != Other.X || this->Y != Other.Y;
}


/// \brief Writes a textual representation of the vector to the given
/// output stream.
template<typename T>
std::ostream& operator<<(std::ostream& Stream, Vector2<T> Value)
{
    return Stream << "(" << Value.X << ", " << Value.Y << ")";
}