#pragma once
#ifndef _Container_HPP_
#define _Container_HPP_

#include <engine/Iterator.hpp>

#include <vector>

namespace engine
{

    /// \class Container
    /// \brief Class that represents the collection (data) and provides several methods for retrieving
    /// fresh iterator instances.
    template <class T>
    class Container
    {
        friend class Iterator<T, Container>; /*!< The Iterator class as a friend class. */

    private:
        std::vector<T> m_data; /*!< The vector of data (type of T). */

    public:
        /// \brief Adds a value to the container.
        /// \param a : The value to add to the container.
        inline void add(T a) { m_data.push_back(a); };

        /// \brief Overloads the brackets to Get/Set an element at position/index i.
        /// \return The element at position/index i.
        inline T &operator[](unsigned int i) { return m_data[i]; };

        /// \brief Returns the size/length of the container.
        /// \return The size/length of the container.
        inline int size() const { return m_data.size(); };

        /// \brief Returns the value hold by the container at a given index.
        /// \return The value at a given index.
        inline T at(unsigned int index) { return m_data.at(index); };

        /// \brief Returns a pointer to the first element in the array used internally by the container.
        /// \return A pointer to the first element in the array used internally by the container.
        inline const T *data() const { return m_data.data(); };

        /// \brief Creates a new Iterator based on the container.
        /// \return A new iterator for the container.
        inline Iterator<T, Container> *CreateIterator() { return new Iterator<T, Container>(this); };
    };

} // namespace engine

#endif /* _Container_HPP_ */