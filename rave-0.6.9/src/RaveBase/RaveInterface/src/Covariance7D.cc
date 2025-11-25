#include "RaveBase/RaveInterface/rave/Covariance7D.h"

#include <iomanip>

namespace rave
{

Covariance7D::Covariance7D ( float dxx, float dxy, float dxz,
                             float dyy, float dyz, float dzz,
                             float dxpx, float dxpy, float dxpz,
                             float dypx, float dypy, float dypz,
                             float dzpx, float dzpy, float dzpz,
                             float dpxpx, float dpxpy, float dpxpz,
                             float dpypy, float dpypz, float dpzpz,
                             float dxm, float dym, float dzm,
                             float dpxm, float dpym, float dpzm,
                             float dmm ) :
    Covariance6D ( dxx, dxy, dxz, dyy, dyz, dzz,
                   dxpx, dxpy, dxpz, dypx, dypy, dypz, dzpx, dzpy, dzpz,
                   dpxpx, dpxpy, dpxpz, dpypy, dpypz, dpzpz ),
    thedxm ( dxm ), thedym ( dym ), thedzm ( dzm ),
    thedpxm ( dpxm ), thedpym ( dpym ), thedpzm ( dpzm ), thedmm ( dmm )
{}

Covariance7D::Covariance7D ( Covariance6D space_error,
                             float dxm, float dym, float dzm,
                             float dpxm, float dpym, float dpzm,
                             float dmm ) :
    Covariance6D ( space_error ),
    thedxm ( dxm ), thedym ( dym ), thedzm ( dzm ),
    thedpxm ( dpxm ), thedpym ( dpym ), thedpzm ( dpzm ), thedmm ( dmm )
{}

Covariance7D::Covariance7D() :

    Covariance6D(), thedxm ( 0. ), thedym ( 0. ), thedzm ( 0. ),
    thedpxm ( 0. ), thedpym ( 0. ), thedpzm ( 0. ), thedmm ( 0. )
{}

float Covariance7D::dxm() const
{
  return thedxm;
}

float Covariance7D::dym() const

{
  return thedym;
}

float Covariance7D::dzm() const

{
  return thedzm;
}

float Covariance7D::dpxm() const

{
  return thedpxm;
}

float Covariance7D::dpym() const

{
  return thedpym;
}

float Covariance7D::dpzm() const

{
  return thedpzm;
}

float Covariance7D::dmm() const

{
  return thedmm;
}

bool Covariance7D::equal ( const Covariance7D & other ) const

{
  return Covariance6D::equal ( other ) &&
         ( dxm() == other.dxm() ) &&
         ( dym() == other.dym() ) &&
         ( dzm() == other.dzm() ) &&
         ( dpxm() == other.dpxm() ) &&
         ( dpym() == other.dpym() ) &&
         ( dpzm() == other.dpzm() ) &&
         ( dmm() == other.dmm() );
}

bool operator== ( const rave::Covariance7D & lhs, const rave::Covariance7D & rhs )
{
  return lhs.equal ( rhs );
}

std::ostream & operator << ( std::ostream & os, const rave::Covariance7D & p )
{
  #define sep " "<<std::setw(12)
  os << std::setprecision(4) << std::scientific << std::right
      << "(" << sep << p.dxx()  << sep << p.dxy()  << sep << p.dxz()  << sep << p.dxpx()  << sep << p.dxpy()  << sep << p.dxpz()  << sep << p.dxm()  << std::endl
      << "(" << sep << p.dxy()  << sep << p.dyy()  << sep << p.dyz()  << sep << p.dypx()  << sep << p.dypy()  << sep << p.dypz()  << sep << p.dym()  << std::endl
      << "(" << sep << p.dxz()  << sep << p.dyz()  << sep << p.dzz()  << sep << p.dzpx()  << sep << p.dzpy()  << sep << p.dzpz()  << sep << p.dzm()  << std::endl
      << "(" << sep << p.dxpx() << sep << p.dypx() << sep << p.dzpx() << sep << p.dpxpx() << sep << p.dpxpy() << sep << p.dpxpz() << sep << p.dpxm() << std::endl
      << "(" << sep << p.dxpy() << sep << p.dypy() << sep << p.dzpy() << sep << p.dpxpy() << sep << p.dpypy() << sep << p.dpypz() << sep << p.dpym() << std::endl
      << "(" << sep << p.dxpz() << sep << p.dypz() << sep << p.dzpz() << sep << p.dpxpz() << sep << p.dpypz() << sep << p.dpzpz() << sep << p.dpzm() << std::endl
      << "(" << sep << p.dxm()  << sep << p.dym()  << sep << p.dzm()  << sep << p.dpxm()  << sep << p.dpym()  << sep << p.dpzm()  << sep << p.dmm()  << ")" << std::endl;
  return os;
}

} // namespace rave
