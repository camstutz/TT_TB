/*!
 * @file sc_map_4d_range.cpp
 * @author Christian Amstutz
 * @date June 18, 2015
 *
 * @brief
 *
 */

/*
 *  Copyright (c) 2015 by Christian Amstutz
 */

#include "sc_map_4d_range.hpp"

//******************************************************************************
sc_map_4d_range::sc_map_4d_range() :
        sc_map_regular_range(sc_map_4d_key(0,0,0,0), sc_map_4d_key(0,0,0,0)),
        Z_dir(UP),
        Y_dir(UP),
        X_dir(UP),
        W_dir(UP)
{}
    // todo:: this is basically not correct!

//******************************************************************************
sc_map_4d_range::sc_map_4d_range(const key_type& start_key,
        const key_type& end_key) :
        sc_map_regular_range(start_key, end_key)
{
    init(NULL, start_key, end_key);

    return;
}

//******************************************************************************
sc_map_4d_range::sc_map_4d_range(
        const sc_map_range<key_type>* base_range, const key_type& start_key,
        const key_type& end_key) :
        sc_map_regular_range(start_key, end_key)
{
    init(base_range, start_key, end_key);

    return;
}

//******************************************************************************
void sc_map_4d_range::init(const sc_map_range<key_type>* base_range,
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

    if (start_key.W <= end_key.W)
    {
        W_dir = UP;
    }
    else
    {
        W_dir = DOWN;
    }

    return;
}

//******************************************************************************
sc_map_4d_range* sc_map_4d_range::clone() const
{
  return new sc_map_4d_range(*this);
}

//******************************************************************************
bool sc_map_4d_range::next_key(key_type& key) const
{
    sc_map_4d_key* key_4d = dynamic_cast<sc_map_4d_key*>(&key);
    sc_map_4d_key new_key;

    if (*key_4d == end_key)
    {
        return false;
    }

    if (key_4d->W != end_key.W)
    {
        if (W_dir == UP)
        {
            new_key.W = key_4d->W + 1;
        }
        else if(W_dir == DOWN)
        {
            new_key.W = key_4d->W - 1;
        }

        new_key.Z = key_4d->Z;
        new_key.Y = key_4d->Y;
        new_key.X = key_4d->X;
    }
    else if (key_4d->X != end_key.X)
    {
        if (X_dir == UP)
        {
            new_key.X = key_4d->X + 1;
        }
        else if(X_dir == DOWN)
        {
            new_key.X = key_4d->X - 1;
        }

        new_key.Z = key_4d->Z;
        new_key.Y = key_4d->Y;
        new_key.W = start_key.W;
   }
   else if (key_4d->Y != end_key.Y)
   {
       if (Y_dir == UP)
       {
           new_key.Y = key_4d->Y + 1;
       }
       else if(Y_dir == DOWN)
       {
           new_key.Y = key_4d->Y - 1;
       }

       new_key.Z = key_4d->Z;
       new_key.X = start_key.X;
       new_key.W = start_key.W;
   }
   else
   {
       if (Z_dir == UP)
       {
           new_key.Z = key_4d->Z + 1;
       }
       else if(Z_dir == DOWN)
       {
           new_key.Z = key_4d->Z - 1;
       }

       new_key.Y = start_key.Y;
       new_key.X = start_key.X;
       new_key.W = start_key.W;
   }

    *key_4d = new_key;

    return true;
}
