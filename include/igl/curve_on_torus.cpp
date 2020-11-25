// This file is part of libigl, a simple c++ geometry processing library.
//
// Copyright (C) 2020 Olga Diamanti <olga.diam@gmail.com>
//
// This Source Code Form is subject to the terms of the Mozilla Public License
// v. 2.0. If a copy of the MPL was not distributed with this file, You can
// obtain one at http://mozilla.org/MPL/2.0/.
#include "curve_on_torus.h"
#include <iostream>
#include <cmath>
using namespace std;

int gcd(int a,int b){
  if(b==0)return a;
  else return gcd(b,a%b);
}

int lcm(int a,int b){
  return a*b/gcd(a,b);
}

template <typename T>
IGL_INLINE void igl::curve_on_torus(
  const double r,
  const double R,
  const int a1,
  const int a2,
  Eigen::Matrix<T,Eigen::Dynamic,3> &gamma,
  Eigen::Matrix<T,Eigen::Dynamic,2> & gamma2D,
  std::vector<Eigen::Matrix<T,Eigen::Dynamic,2> > &gamma2D_split,
  const int Nc,
  const Eigen::Matrix<T,1,2> & p0_)
{
  Eigen::Matrix<T,1,2> p0 = p0_;

  assert((p0[0]<=1) & (p0[1]<=1));
  double m = 1./a1;
  double n = 1./a2;

  int N = lcm(a2, a1);
  Eigen::Matrix<T,1,2> t(m,n);

  //construct 2D curves
  gamma2D.resize(N+1,2);
  gamma2D.row(0) = p0;

  int ng = 0;
  gamma2D_split.resize(0);
  gamma2D_split.push_back(p0);

  Eigen::Matrix<T,1,2> pnew;
  for (int segi=0; segi<N; ++segi)
  {
    pnew = p0+t;

    // coordinate that is most 'outside'
    Eigen::Matrix<T,1,2> ll = (1-p0.array())/t.array();

    if (pnew[0]>=1 | pnew[1]>=1)
    {
      // coordinate that will first ste 'outside'
      int ii0;
      double ll0 = ll.minCoeff(&ii0);
      // the other coordinate
      int ii1 = 1-ii0;

      pnew = p0+ll0*t;
      // gamma2D_split{ng}(end+1,:) = pnew;
      gamma2D_split[ng].conservativeResize(gamma2D_split[ng].rows()+1,Eigen::NoChange);
      gamma2D_split[ng].bottomRows(1) = pnew;

      p0 = pnew;
      p0(ii0) = 0;
      ng = ng+1;
      gamma2D_split.push_back(p0);

      pnew = p0+(1-ll0)*t;
      assert(pnew(ii0)<=1);
      if (pnew(ii1)>=1)
      {
        // coordinate that is most 'outside'
        double ll = (1.-p0(ii1))/t(ii1);

        pnew = p0+ll*t;
        // gamma2D_split{ng}(end+1,:) = pnew;
        gamma2D_split[ng].conservativeResize(gamma2D_split[ng].rows()+1,Eigen::NoChange);
        gamma2D_split[ng].bottomRows(1) = pnew;

        p0 = pnew;
        p0(ii1) = 0;
        ng = ng+1;
        gamma2D_split.push_back(p0);

        pnew = p0+(1-ll0-ll)*t;
      }
    }
    assert((pnew[0]<=1) & (pnew[1]<=1));
    // gamma2D_split{ng}(end+1,:) = pnew;
    gamma2D_split[ng].conservativeResize(gamma2D_split[ng].rows()+1,Eigen::NoChange);
    gamma2D_split[ng].bottomRows(1) = pnew;

    gamma2D.row(segi+1) = pnew;
    p0 = pnew;
  }

  //construct 3D curve
  Eigen::VectorXd gtheta, gphi;
  gtheta.resize(0,1);
  gphi.resize(0,1);
  for (int i = 0; i<gamma2D_split.size(); ++i)
  {
    int nc = gamma2D_split[i].rows();
    Eigen::Matrix<T,1,2> p0 = gamma2D_split[i].row(0);
    Eigen::Matrix<T,1,2> p1 = gamma2D_split[i].row(nc-1);
    T edge_length = (p1 - p0).norm();
    int Ns = round(edge_length*Nc);
    Eigen::VectorXd tt_ = Eigen::VectorXd::LinSpaced(Ns+1, p0(0),p1(0));
    Eigen::VectorXd pp_ = Eigen::VectorXd::LinSpaced(Ns+1, p0(1),p1(1));
    gtheta.conservativeResize(gtheta.rows()+Ns);
    gphi.conservativeResize(gphi.rows()+Ns);
    gtheta.tail(Ns) = 2*M_PI*tt_.head(Ns).array();
    gphi.tail(Ns) = 2*M_PI*pp_.head(Ns).array();
  }
  Eigen::VectorXd gx, gy, gz;
  gx = (R+r*gtheta.array().cos())*gphi.array().cos();
  gy = (R+r*gtheta.array().cos())*gphi.array().sin();
  gz = r*gtheta.array().sin();

  gamma.resize(gx.rows(),3);
  gamma<<gx, gy, gz;
};


template <typename T>
IGL_INLINE void igl::curve_on_torus(
  const double r,
  const double R,
  const int a1,
  const int a2,
  Eigen::Matrix<T,Eigen::Dynamic,3> &gamma,
  const int Nc,
  const Eigen::Matrix<T,1,2> & p0)
{
  Eigen::Matrix<T,Eigen::Dynamic,2> gamma2D;
  std::vector<Eigen::Matrix<T,Eigen::Dynamic,2> > gamma2D_split;

  curve_on_torus(r, R, a1, a2, gamma, gamma2D, gamma2D_split, Nc, p0);

}

#ifdef IGL_STATIC_LIBRARY
    // Explicit template instantiation
    // generated by autoexplicit.sh
    template void igl::curve_on_torus<double>(double, double, int, int, Eigen::Matrix<double, -1, 3, 0, -1, 3>&, int, Eigen::Matrix<double, 1, 2, 1, 1, 2> const&);
#endif
