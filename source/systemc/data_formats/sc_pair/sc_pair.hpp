/*!
 * @file sc_pair.hpp
 * @author Christian Amstutz
 * @date April 17, 2015
 *
 * @brief
 *
 */

/*
 *  Copyright (c) 2015 by Christian Amstutz
 */

#pragma once

#include <systemc.h>

#include <utility>

// *****************************************************************************
template <typename FIRST_T, typename SECOND_T>
class sc_pair;

template <typename FIRST_T, typename SECOND_T>
std::ostream& operator<< (std::ostream& stream, const sc_pair<FIRST_T,
        SECOND_T>& pair);

// *****************************************************************************
template <typename FIRST_T, typename SECOND_T>
class sc_pair : public std::pair<FIRST_T, SECOND_T>
{
public:
    sc_pair();
    sc_pair(FIRST_T _first, SECOND_T _second);

friend std::ostream& operator<< <> (std::ostream& stream, const sc_pair& pair);
//friend void sc_trace(sc_trace_file* tf, const sc_pair& v, const std::string& name);
};

// *****************************************************************************

// *****************************************************************************
template <typename FIRST_T, typename SECOND_T>
sc_pair<FIRST_T, SECOND_T>::sc_pair() : std::pair<FIRST_T, SECOND_T>(FIRST_T(),
        SECOND_T())
{}

// *****************************************************************************
template <typename FIRST_T, typename SECOND_T>
sc_pair<FIRST_T, SECOND_T>::sc_pair(FIRST_T _first, SECOND_T _second) :
        std::pair<FIRST_T, SECOND_T>(_first, _second)
{}

// *****************************************************************************
template <typename FIRST_T, typename SECOND_T>
std::ostream& operator<< (std::ostream& stream, const sc_pair<FIRST_T,
        SECOND_T>& pair)
{
    stream << "[";
    stream << pair.first;
    stream << ",";
    stream << pair.second;
    stream << "]";

    return stream;
}
