/*! \file    Mixture.hpp
 *  \brief   Mixture class declaration
 *  \author  Shizhe Li
 *  \date    Oct/01/2021
 *
 *-----------------------------------------------------------------------------------
 *  Copyright (C) 2021--present by the OpenCAEPoro team. All rights reserved.
 *  Released under the terms of the GNU Lesser General Public License 3.0 or later.
 *-----------------------------------------------------------------------------------
 */

#ifndef __MIXTURE_HEADER__
#define __MIXTURE_HEADER__

// Standard header files
#include <iostream>
#include <vector>

// OpenCAEPoro header files
#include "OCPConst.hpp"
#include "ParamReservoir.hpp"

using namespace std;

/// Mixture is an abstract class, who contains all information used for flash
/// calculation including variables, functions. any properties of phases such as mass
/// density can calculated by it. it has the same data structure as the ones in bulks.
class Mixture
{
    friend class Bulk;
    friend class Well;
    friend class AllWells;

public:
    Mixture() = default;
    virtual ~Mixture(){};
    /// Allocate memory for common variables for basic class
    void Allocate()
    {
        Ni.resize(numCom);
        phaseExist.resize(numPhase);
        v.resize(numPhase);
        S.resize(numPhase);      
        xi.resize(numPhase);
        nj.resize(numPhase);
        xij.resize(numPhase * numCom);
        rho.resize(numPhase);
        mu.resize(numPhase);
        vfi.resize(numCom);
        vji.resize(numPhase);
        for (auto& v : vji) {
            v.resize(numCom, 0);
        }
        vjp.resize(numPhase, 0);
        // Derivatives for FIM
        rhoP.resize(numPhase);
        xiP.resize(numPhase);
        muP.resize(numPhase);
        rhoN.resize(numPhase * numCom);
        xiN.resize(numPhase * numCom);
        muN.resize(numPhase * numCom);
        rhox.resize(numPhase * numCom);
        xix.resize(numPhase * numCom);
        mux.resize(numPhase * numCom);
        dXsdXp.resize((numCom + 1) * (numPhase + numPhase * numCom));
        pEnumCom.resize(numPhase);
        res.resize(numPhase + numPhase * numCom + 1); // a precomputed value stored in last position
        // water not in hydrocarbon, hydrocarbon not in water
        keyDer.resize((numCom + 1) * ((numPhase - 1) * (numCom - 1) + 1));
        
    };
    virtual void SetPVTW(){};
    /// return type of mixture.
    USI GetType() const { return mixtureType; }
    /// Check whether Table PVDG is empty, it will only be used in black oil model.
    virtual bool IsEmpty_PVDG() const { return true; };
    /// flash calculation with saturation of phases.
    virtual void InitFlash(const OCP_DBL& Pin, const OCP_DBL& Pbbin, const OCP_DBL& Tin,
                          const OCP_DBL* Sjin, const OCP_DBL& Vpore,
                          const OCP_DBL* Ziin) = 0;
    virtual void InitFlashDer(const OCP_DBL& Pin, const OCP_DBL& Pbbin,
                              const OCP_DBL& Tin, const OCP_DBL* Sjin,
                              const OCP_DBL& Vpore, const OCP_DBL* Ziin) = 0;
    virtual void InitFlashDer_n(const OCP_DBL& Pin, const OCP_DBL& Pbbin,
                              const OCP_DBL& Tin, const OCP_DBL* Sjin,
                              const OCP_DBL& Vpore, const OCP_DBL* Ziin) = 0;
    /// Flash calculation with moles of components.
    virtual void Flash(const OCP_DBL& Pin, const OCP_DBL& Tin,
        const OCP_DBL* Niin, const USI& ftype, const USI& lastNP,
        const OCP_DBL* lastKs) = 0;
    /// Flash calculation with moles of components and Calculate the derivative
    virtual void FlashDeriv(const OCP_DBL& Pin, const OCP_DBL& Tin,
        const OCP_DBL* Niin, const USI& ftype, const USI& lastNP,
        const OCP_DBL* lastKs) = 0;
    virtual void FlashDeriv_n(const OCP_DBL& Pin, const OCP_DBL& Tin,
        const OCP_DBL* Niin, const OCP_DBL* Sjin, const OCP_DBL* xijin,
        const OCP_DBL* njin, const USI& ftype, const USI* phaseExistin, 
        const USI& lastNP, const OCP_DBL* lastKs) = 0;
    /// Return molar density of phase, it's used to calculate the molar density of
    /// injection fluids in injection wells.
    virtual OCP_DBL XiPhase(const OCP_DBL& Pin, const OCP_DBL& Tin,
                            const OCP_DBL* Ziin) = 0;

    /// return mass density of phase.
    virtual OCP_DBL RhoPhase(const OCP_DBL& Pin, const OCP_DBL& Tin,
                             const OCP_DBL* Ziin) = 0;

    /// return gamma of oil phase, gamma equals to mass density times gravity factor.
    virtual OCP_DBL GammaPhaseO(const OCP_DBL& Pin, const OCP_DBL& Pbbin) = 0;
    /// return gamma of water phase, gamma equals to mass density times gravity factor.
    virtual OCP_DBL GammaPhaseW(const OCP_DBL& Pin) = 0;
    /// return gamma of gas phase, gamma equals to mass density times gravity factor.
    virtual OCP_DBL GammaPhaseG(const OCP_DBL& Pin) = 0;
    /// return gamma of hydrocarbon mixture, gamma equals to mass density times gravity
    /// factor.
    virtual OCP_DBL GammaPhaseOG(const OCP_DBL& Pin, const OCP_DBL& Tin,
                                 const OCP_DBL* Ziin) = 0;

    /// check if Ni input from param is negative, it's used in debug mode to check
    /// Hidden trouble. actually, very small error in very short time may not make
    /// trouble.
    void CheckNi(const OCP_DBL* Ni)
    {
        bool flag = true;
        for (USI i = 0; i < numCom; i++) {
            if (Ni[i] < 0) {
                cout << "Ni[" << i << "] = " << Ni[i] << endl;
                flag = false;
                break; // skip the rest checks
            }
        }
        if (!flag) OCP_ABORT("Ni is negative!");
    }
    // used in Compositional Model
    virtual USI GetFtype() = 0;
    virtual OCP_SIN GetMinEigenSkip() = 0;
    virtual bool GetFlagSkip() = 0; 
    virtual OCP_DBL GetSurTen() = 0;

    virtual OCP_DBL GetErrorPEC() = 0;
    virtual OCP_ULL GetSSMSTAiters() = 0;
    virtual OCP_ULL GetNRSTAiters() = 0;
    virtual OCP_ULL GetSSMSPiters() = 0; 
    virtual OCP_ULL GetNRSPiters() = 0;
    virtual OCP_ULL GetRRiters() = 0;
    virtual OCP_ULL GetSSMSTAcounts() = 0;
    virtual OCP_ULL GetNRSTAcounts() = 0;
    virtual OCP_ULL GetSSMSPcounts() = 0;
    virtual OCP_ULL GetNRSPcounts() = 0;
    virtual OCP_ULL GetRRcounts() = 0;

protected:
    USI mixtureType; ///< indicates the type of mixture, black oil or compositional or
                     ///< others.

    USI     numPhase; ///< num of phases.
    USI     numCom;   ///< num of components.
    OCP_DBL P;        ///< pressure when flash calculation.
    OCP_DBL T;        ///< temperature when flash calculation.

    vector<OCP_DBL> Ni;         ///< moles of component: numCom
    vector<bool>    phaseExist; ///< existence of phase: numPhase
    vector<OCP_DBL> S;          ///< saturation of phase: numPhase
    vector<OCP_DBL> rho;        ///< mass density of phase: numPhase
    vector<OCP_DBL> xi;         ///< molar density of phase: numPhase
    vector<OCP_DBL> xij; ///< Nij / Nj: numPhase*numCom, Nij is the moles of component i
                         ///< in phase j, Nj is the moles of phase j.
    vector<OCP_DBL> nj;  ///< mole number of phase j
    vector<OCP_DBL> mu;  ///< viscosity of phase: numPhase
    vector<OCP_DBL> v;   ///< volume of phase: numPhase;

    OCP_DBL vf; ///< volume of total fluids.
    OCP_DBL Nt; ///< Total moles of Components.

    // Derivatives

    vector<vector<OCP_DBL>> vji; ///< dvj / dNi, used in 2 hydrocarbon phase in EOS; or dvj / dnij
    vector<OCP_DBL> vjp; ///< dvj / dp, used in 2 hydrocarbon phase in EOS

    OCP_DBL vfp; ///< dVf / dP, the derivative of volume of total fluids with respect to
                 ///< pressure.
    vector<OCP_DBL> vfi; ///< dVf / dNi: numCom  the derivative of volume of total
                         ///< fluids with respect to moles of components.

    vector<OCP_DBL> muP;  ///< d mu / dP: numPhase
    vector<OCP_DBL> xiP;  ///< d xi / dP: numphase
    vector<OCP_DBL> rhoP; ///< d rho / dP: numphase
    vector<OCP_DBL> muN;  ///< d mu[j] / d N[i]: numphase * numCom
    vector<OCP_DBL> xiN;  ///< d xi[j] / d N[i]: numphase * numCom
    vector<OCP_DBL> rhoN; ///< d rho[j] / d N[i]: numphase * numCom
    vector<OCP_DBL> mux;  ///< d mu[j] / d x[i][j]: numphase * numCom
    vector<OCP_DBL> xix;  ///< d xi[j] / d x[i][j]: numphase * numCom
    vector<OCP_DBL> rhox; ///< d rho[j] / d x[i][j]: numphase * numCom

    vector<OCP_DBL> dXsdXp; ///< the derivates of second variables wrt. primary variables
    vector<USI>     pEnumCom; ///< see pEnumCom in bulk
    vector<OCP_DBL> res;     ///< residual of a set of equations
    OCP_DBL         resPc;    ///< a precalculated value
    
    vector<OCP_DBL> keyDer; ///< d (xij*xi/mu) / dP or dNk
};

#endif /* end if __MIXTURE_HEADER__ */

/*----------------------------------------------------------------------------*/
/*  Brief Change History of This File                                         */
/*----------------------------------------------------------------------------*/
/*  Author              Date             Actions                              */
/*----------------------------------------------------------------------------*/
/*  Shizhe Li           Oct/01/2021      Create file                          */
/*  Chensong Zhang      Oct/15/2021      Format file                          */
/*----------------------------------------------------------------------------*/