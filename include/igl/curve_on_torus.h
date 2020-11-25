// This file is part of libigl, a simple c++ geometry processing library.
//
// Copyright (C) 2020 Olga Diamanti <olga.diam@gmail.com>
//
// This Source Code Form is subject to the terms of the Mozilla Public License
// v. 2.0. If a copy of the MPL was not distributed with this file, You can
// obtain one at http://mozilla.org/MPL/2.0/.
#ifndef CURVE_ON_TORUS_H
#define CURVE_ON_TORUS_H
#include "igl_inline.h"
#include <Eigen/Dense>

namespace igl
{
  // Function to generate discrete curves on a torus
  // Proceeds by first generating a discrete curve on the fundamental domain of the torus in the plane, then maps it to 3D via the equations of the torus of revolution.
  // The parameters a1/a2 control the number of times the curve "turns around" the torus in its two generating directions. The parameter Nc controls the number of points in the curve.
  // Inputs:
  //   r  small radius of torus (double)
  //   R big radius of torus (double)
  //   a1 resolution in the horizontal direction of the unit square / fundamental domain of the torus (integer). The length of horizontal"step" is 1/a1. It controls the number of times the curve turns around
  //   a2 resolution in the vertical direction  (integer). The length of vertical "step" is 1/a2.
  //   Nc number of points that will be generated from every edge segment of the (low resolution) flat curve on the fundamental domain. (integer, optional, default is 50)
  //   p0 starting point of the curve inside the unit square / fundamental domain of the torus (optional, default is randomly set).
  //
  // Outputs:
  //   gamma          the 3D curve on the torus, an #pts x 3 Eigen Matrix
  //   gamma2D        the 2D curve on the unit square / fundamental domain
  //   gamma2D_split  the 2D curve on the unit square / fundamental domain, but split at the boundaries of the fundamental domain and continued toroidally. Has more edge segments than gamma2D, its edge segments are unequal in length, and that is the one used to generate gamma
  //
  template <typename T>
  IGL_INLINE void curve_on_torus(
    const double r,
    const double R,
    const int a1,
    const int a2,
    Eigen::Matrix<T,Eigen::Dynamic,3> &gamma,
    Eigen::Matrix<T,Eigen::Dynamic,2> & gamma2D,
    std::vector<Eigen::Matrix<T,Eigen::Dynamic,2> > &gamma2D_split,
    const int Nc = 50,
    const Eigen::Matrix<T,1,2> & p0 = Eigen::RowVector2d::Random());

    template <typename T>
    IGL_INLINE void curve_on_torus(
      const double r,
      const double R,
      const int a1,
      const int a2,
      Eigen::Matrix<T,Eigen::Dynamic,3> &gamma,
      const int Nc = 50,
      const Eigen::Matrix<T,1,2> & p0 = Eigen::RowVector2d::Random());


}

#ifndef IGL_STATIC_LIBRARY
#  include "curve_on_torus.cpp"
#endif

#endif
