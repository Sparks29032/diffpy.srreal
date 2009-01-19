/*****************************************************************************
*
* diffpy.srreal     by DANSE Diffraction group
*                   Simon J. L. Billinge
*                   (c) 2009 Trustees of the Columbia University
*                   in the City of New York.  All rights reserved.
*
* File coded by:    Pavol Juhas
*
* See AUTHORS.txt for a list of people who contributed.
* See LICENSE.txt for license information.
*
******************************************************************************
*
* class VR3Structure -- trivial structure representation.
* class VR3Adapter -- concrete StructureAdapter for VR3Structure
* class VR3BondIterator -- concrete BaseBondIterator for VR3Structure
*
* $Id$
*
*****************************************************************************/

#ifndef VR3STRUCTURE_HPP_INCLUDED
#define VR3STRUCTURE_HPP_INCLUDED

#include <vector>

#include "R3linalg.hpp"
#include "StructureAdapter.hpp"
#include "BaseBondIterator.hpp"

namespace diffpy {
namespace srreal {

typedef std::vector<R3::Vector> VR3Structure;


class VR3Adapter : public StructureAdapter
{
    friend class VR3BondIterator;
    public:

        // constructors
        VR3Adapter(const VR3Structure& vr3s);

        // methods
        virtual int countSites() const;
        virtual BaseBondIterator* createBondIterator() const;

    private:

        // data
        const VR3Structure* mvr3structure;
};


class VR3BondIterator : public BaseBondIterator
{
    public:

        // constructors
        VR3BondIterator(const VR3Adapter*);

        // methods
        virtual const R3::Vector& r0() const;
        virtual const R3::Vector& r1() const;

    private:
        // data
        const VR3Structure* mvr3structure;
};


//////////////////////////////////////////////////////////////////////////////
// Definitions
//////////////////////////////////////////////////////////////////////////////

// VR3Adapter - Constructor --------------------------------------------------

inline
VR3Adapter::VR3Adapter(const VR3Structure& vr3s)
{
    mvr3structure = &vr3s;
}

// VR3Adapter - Public Methods -----------------------------------------------

inline
int VR3Adapter::countSites() const
{
    return mvr3structure->size();
}


inline
BaseBondIterator* VR3Adapter::createBondIterator() const
{
    BaseBondIterator* bbi = new VR3BondIterator(this);
    return bbi;
}


// VR3BondIterator - Constructor ---------------------------------------------

inline
VR3BondIterator::VR3BondIterator(const VR3Adapter* adpt) :
    BaseBondIterator(adpt)
{
    mvr3structure = adpt->mvr3structure;
}

// VR3BondIterator - Public Methods ------------------------------------------

inline
const R3::Vector& VR3BondIterator::r0() const
{
    return mvr3structure->at(msite_anchor);
}


inline
const R3::Vector& VR3BondIterator::r1() const
{
    return mvr3structure->at(msite_current);
}

// Inline Routines -----------------------------------------------------------

inline
StructureAdapter* createPQAdapter(const VR3Structure& vr3stru)
{
    StructureAdapter* adapter = new VR3Adapter(vr3stru);
    return adapter;
}


}   // namespace srreal
}   // namespace diffpy

#endif  // VR3STRUCTURE_HPP_INCLUDED
