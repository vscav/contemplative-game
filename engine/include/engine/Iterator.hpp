#pragma once
#ifndef _Iterator_HPP_
#define _Iterator_HPP_

#include <vector>

namespace engine
{

    /// \class Iterator
    /// \brief Class which can use iterators to move through the contents of its container.
    template <typename T, typename U>
    class Iterator
    {
    public:
        typedef typename std::vector<T>::iterator iter_type;
        /// \brief Constructor.
        explicit Iterator(U *p_data, bool reverse = false) : m_data(p_data) {
            m_it = m_data->m_data.begin();
        };

        /// \brief Sets the iterator to point to the first element in the vector.
        inline void first() { m_it = m_data->m_data.begin(); };

        /// \brief Sets the iterator to the next element in the vector.
        inline void next() { m_it++; };

        /// \brief Sets the iterator to the element past the end of the sequence.
        /// \return A boolean telling if the iterator is pointing to next to last element of the container.
        inline bool isDone() { return (m_it == m_data->m_data.end()); };

        /// \brief Returns the current element.
        /// \return The current element pointed in the container.
        inline iter_type current() { return m_it; };

    private:
        U *m_data; /*!< A pointer to the data of the container. */

        iter_type m_it; /*!< The vector iterator. */
    };

} // namespace engine

#endif /* _Iterator_HPP_ */