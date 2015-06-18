/*!
 * @file sc_map_cube_range.cpp
 * @author Christian Amstutz
 * @date June 17, 2015
 *
 * @brief
 *
 */

/*
 *  Copyright (c) 2015 by Christian Amstutz
 */

#include "sc_map_cube_range.hpp"

//******************************************************************************
sc_map_cube_range::sc_map_cube_range() :
        sc_map_regular_range(sc_map_cube_key(0,0,0), sc_map_cube_key(0,0,0)),
        Z_dir(UP),
        Y_dir(UP),
        X_dir(UP)
{}
    // todo:: this is basically not correct!

//******************************************************************************
sc_map_cube_range::sc_map_cube_range(const key_type& start_key,
        const key_type& end_key) :
        sc_map_regular_range(start_key, end_key)
{
    init(NULL, start_key, end_key);

    return;
}

//******************************************************************************
sc_map_cube_range::sc_map_cube_range(
        const sc_map_range<key_type>* base_range, const key_type& start_key,
        const key_type& end_key) :
        sc_map_regular_range(start_key, end_key)
{
    init(base_range, start_key, end_key);

    return;
}

//******************************************************************************
void sc_map_cube_range::init(const sc_map_range<key_type>* base_range,
        const key_type& start_key, const key_type& end_key)
{
    if (start_key.Z <= end_key.Z)
    {
        Z_dir = UP;
    }
    else
    {
        Z_dir = DOWN;
    }

    if (start_key.Y <= end_key.Y)
    {
        Y_dir = UP;
    }
    else
    {
        Y_dir = DOWN;
    }

    if (start_key.X <= end_key.X)
    {
        X_dir = UP;
    }
    else
    {
        X_dir = DOWN;
    }

    return;
}

//******************************************************************************
sc_map_cube_range* sc_map_cube_range::clone() const
{
  return new sc_map_cube_range(*this);
}

//******************************************************************************
bool sc_map_cube_range::next_key(key_type& key) const
{
    sc_map_cube_key* key_cube = dynamic_cast<sc_map_cube_key*>(&key);
    sc_map_cube_key new_key;

    if (*key_cube == end_key)
    {
        return false;
    }

    if (key_cube->X != end_key.X)
    {
        if (X_dir == UP)
        {
            new_key.X = key_cube->X + 1;
        }
        else if(X_dir == DOWN)
        {
            new_key.X = key_cube->X - 1;
        }

        new_key.Z = key_cube->Z;
        new_key.Y = key_cube->Y;
   }
   else if (key_cube->Y != end_key.Y)
   {
       if (Y_dir == UP)
       {
           new_key.Y = key_cube->Y + 1;
       }
       else if(Y_dir == DOWN)
       {
           new_key.Y = key_cube->Y - 1;
       }

       new_key.X = start_key.X;
       new_key.Z = key_cube->Z;
   }
   else
   {
       if (Z_dir == UP)
       {
           new_key.Z = key_cube->Z + 1;
       }
       else if(Z_dir == DOWN)
       {
           new_key.Z = key_cube->Z - 1;
       }

       new_key.Y = start_key.Y;
       new_key.X = start_key.X;
   }

    *key_cube = new_key;

    return true;
}
