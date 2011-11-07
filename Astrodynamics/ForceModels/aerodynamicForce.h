/*! \file aerodynamicForce.h
*    This header file contains the aerodynamic forces model included in Tudat.
*
*    Path              : /Astrodynamics/ForceModels/
*    Version           : 2
*    Check status      : Checked
*
*    Checker           : F. M. Engelen
*    Affiliation       : Delft University of Technology
*    E-mail address    : F.M.Engelen@student.tudelft.nl
*
*    Checker           : D. Dirkx
*    Affiliation       : Delft University of Technology
*    E-mail address    : D..Dirkx@tudelft.nl
*
*    Date created      : 17 May, 2011
*    Last modified     : 22 August, 2011
*
*    References
*
*    Notes
*
*    Copyright (c) 2010-2011 Delft University of Technology.
*
*    This software is protected by national and international copyright.
*    Any unauthorized use, reproduction or modification is unlawful and
*    will be prosecuted. Commercial and non-private application of the
*    software in any form is strictly prohibited unless otherwise granted
*    by the authors.
*
*    The code is provided without any warranty; without even the implied
*    warranty of merchantibility or fitness for a particular purpose.
*
*    Changelog
*      YYMMDD    Author            Comment
*      110617    F.M. Engelen      First creation of code.
*      110822    D. Dirkx          Removed pointer to double member, minor changes.
*/

#ifndef AERODYNAMICFORCE_H
#define AERODYNAMICFORCE_H

// Macros.
#define TUDAT_UNUSED_PARAMETER( unusedParameter ) { ( void ) unusedParameter; }

// Include statements.
#include <iostream>
#include "Astrodynamics/ForceModels/forceModel.h"
#include "Astrodynamics/ForceModels/aerodynamicCoefficientInterface.h"

//! Tudat library namespace.
/*!
 * The Tudat library namespace.
 */
namespace tudat
{

//! Aerodynamic force model.
/*!
 * Calculates the aerodynamic force based on C_D C_S and C_L, a reference lenght or area, the
 * local velocity and the local density.
 */
class AerodynamicForce : public ForceModel
{
public:

    //! Default constructor.
    /*!
     * Default constructor.
     */
    AerodynamicForce( ) : pointerToAerodynamicCoefficientInterface_( NULL ),
        dynamicPressure_( -0.0 ) { }

    //! Set aerodynamic coefficient interface.
    /*!
     * Sets the aerodynamic coefficient interface.
     * \param pointerToAerodynamicCoefficientInterface Aerodynamic coefficient interface
     *          used to retrieve aerodynamic coefficients.
     */
    void setAerodynamicCoefficientInterface(
            AerodynamicCoefficientInterface* pointerToAerodynamicCoefficientInterface )
    { pointerToAerodynamicCoefficientInterface_ = pointerToAerodynamicCoefficientInterface; }

    //! Get aerodynamic coefficient interface.
    /*!
     * Returns the pointer to the AerodynamicCoefficientInterface object.
     * \return Aerodynamic coefficient interface used to retrieve aerodynamic coefficients.
     */
    AerodynamicCoefficientInterface* getAerodynamicCoefficientInterface( )
    { return pointerToAerodynamicCoefficientInterface_; }

    //! Set dynamic pressure.
    /*!
     * Sets the dynamic pressure.
     * \param dynamicPressure Dynamic pressure.
     */
    void setDynamicPressure( const double& dynamicPressure )
    { dynamicPressure_ = dynamicPressure; }

    //! Get dynamic pressure.
    /*!
     * Returns the dynamic pressure.
     * \return Dynamic pressure.
     */
    double& getDynamicPressure( ) { return dynamicPressure_; }

    //! Compute aerodynamic force.
    /*!
     * Computes the aerodynamic force.
     * \param pointerToState Pointer to state.
     */
    void computeForce( State* pointerToState )
    {
        TUDAT_UNUSED_PARAMETER( pointerToState );
        force_ = dynamicPressure_ * pointerToAerodynamicCoefficientInterface_->getReferenceArea( )
                * pointerToAerodynamicCoefficientInterface_->getCurrentForceCoefficients( );
    }

protected:

private:

    //! Pointer to aerodynamic coefficient interface.
    /*!
     * Pointer to an aerodynamic coefficient interface.
     */
    AerodynamicCoefficientInterface* pointerToAerodynamicCoefficientInterface_;

    //! The dynamic pressure.
    /*!
     * The dynamic pressure.
     */
    double dynamicPressure_;
};

}

#endif // AERODYNAMICFORCE_H

// End of file.