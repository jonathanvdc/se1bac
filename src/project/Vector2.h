#pragma once
#include <memory>
#include <ostream>

/// \brief Represents a generic two-dimensional vector.
template<typename T>
struct Vector2
{
    /// \brief Creates a new two-dimensional vector at the origin.
    Vector2();
    /// \brief Creates a new two-dimensional vector from the given
    /// coordinates.
    Vector2(T X, T Y);


    /// \brief Adds two vectors together.
    Vector2<T> operator+(Vector2<T> Other) const;

    /// \brief Subtracts the given vector from this vector.
    Vector2<T> operator-(Vector2<T> Other) const;

    /// \brief Multiplies this vector with a scalar.
    Vector2<T> operator*(T Scalar) const;

    /// \brief Checks if this vector equals the given vector.
    bool operator==(Vector2<T> Other) const;

    /// \brief Checks if this vector is not equal to the given vector.
    bool operator!=(Vector2<T> Other) const;

    /// \brief Gets or sets the vector's x-coordinate.
    T X;
    /// \brief Gets or sets the vector's y-coordinate.
    T Y;
};
/// \brief Writes a textual representation of the vector to the given
/// output stream.
template<typename T>
std::ostream& operator<<(std::ostream& Stream, Vector2<T> Value);

#include "Vector2.hxx"