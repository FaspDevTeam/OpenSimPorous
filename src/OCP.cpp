/*! \file    OCP.cpp
 *  \brief   OpenCAEPoro class definition
 *  \author  Shizhe Li
 *  \date    Oct/01/2021
 *
 *-----------------------------------------------------------------------------------
 *  Copyright (C) 2021--present by the OpenCAEPoro team. All rights reserved.
 *  Released under the terms of the GNU Lesser General Public License 3.0 or later.
 *-----------------------------------------------------------------------------------
 */

#include "OCP.hpp"

/// Read from input file and set control and output params.
void OpenCAEPoro::InputParam(ParamRead& param)
{
    reservoir.InputParam(param);
    control.InputParam(param.paramControl);
    output.InputParam(param.paramOutput);
}

/// Call setup procedures for reservoir, output, and linear solver.
void OpenCAEPoro::SetupSimulator(ParamRead&  param,
                                 const USI&  argc,
                                 const char* options[])
{
    GetWallTime timer;
    timer.Start();

    // Read parameters from input file
    InputParam(param);
    // Read Fast control
    control.SetupFastControl(argc, options);
    // Setup static infomation for reservoir
    reservoir.Setup();
    // Setup output for dynamic simulation
    output.Setup(reservoir, control);
    // Setup static information for solver
    solver.Setup(reservoir, control);

    cout << endl
         << "Setup simulation done. Wall time : " << fixed << setprecision(3)
         << timer.Stop() / 1000 << " Sec" << endl
         << endl;
    control.RecordTotalTime(timer.Stop() / 1000);
}

/// Initialize the reservoir class.
void OpenCAEPoro::InitReservoir()
{
    GetWallTime timer;
    timer.Start();

    solver.InitReservoir(reservoir);

    cout << endl
         << "Initialization done. Wall time : " << fixed << setprecision(3)
         << timer.Stop() / 1000 << " Sec" << endl;
    control.RecordTotalTime(timer.Stop() / 1000);
}

/// Call IMPEC, FIM, etc for dynamic simulation.
void OpenCAEPoro::RunSimulation()
{
    cout << "\n=========================================" << endl;
    switch (control.GetMethod()) {
        case IMPEC:
            cout << "Dynamic simulation with IMPEC";
            break;
        case FIM:
            cout << "Dynamic simulation with FIM";
            break;
        case FIMn:
            cout << "Dynamic simulation with FIMn";
            break;
        case AIMc:
            cout << "Dynamic simulation with AIMc";
            break;
        case AIMs:
            cout << "Dynamic simulation with AIMs";
            break;
        case AIMt:
            cout << "Dynamic simulation with AIMt";
            break;
        default:
            OCP_ABORT("Wrong method type is used!");
    }
    cout << "\n=========================================" << endl;

    solver.RunSimulation(reservoir, control, output);
}

/// Print summary information on screen and SUMMARY.out file.
void OpenCAEPoro::OutputResults() const
{
    cout << "=========================================" << endl;
    cout << "Final time:          " << control.current_time << " Days" << endl;
    cout << "Total time steps:    " << control.numTstep << endl;
    cout << "Total Newton steps:  " << control.iterNR_total << " (+"
         << control.wastedIterNR << " wasted steps)" << endl;
    cout << "Total linear steps:  " << control.iterLS_total << " (+"
         << control.wastedIterLS << " wasted steps)" << endl;
    cout << "Linear solve time:   " << control.totalLStime << "s"
         << " (" << 100.0 * control.totalLStime / control.totalSimTime << "%)" << endl;
    cout << "Simulation time:     " << control.totalSimTime << "s" << endl;
    output.PrintInfo();
}

/*----------------------------------------------------------------------------*/
/*  Brief Change History of This File                                         */
/*----------------------------------------------------------------------------*/
/*  Author              Date             Actions                              */
/*----------------------------------------------------------------------------*/
/*  Shizhe Li           Oct/01/2021      Create file                          */
/*  Chensong Zhang      Dec/05/2021      Format file                          */
/*----------------------------------------------------------------------------*/