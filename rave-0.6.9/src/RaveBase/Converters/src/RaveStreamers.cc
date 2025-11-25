#include "RaveBase/Converters/interface/RaveStreamers.h"
#include <iomanip>
#include <iostream>

using namespace std;

namespace
{
  bool isDiagonal ( const rave::Covariance3D & cov )
  {
    static const float min = 1.e-11;
    if ( fabs ( cov.dxy() ) > min ) return false;
    if ( fabs ( cov.dxz() ) > min ) return false;
    if ( fabs ( cov.dyz() ) > min ) return false;
    return true;
  }
}

ostream& operator<< ( ostream& os, const rave::Point3D & p )
{
  os << "(" << setprecision(4) << fixed << p.x() << ", " << p.y() << ", " << p.z() << ")";
  return os;
}

#ifdef WITH_KINEMATICS
ostream& operator<< ( ostream& os, const rave::Vector4D & p )
{
  os << "(" << setprecision(4) << fixed << p.x() << ", " << p.y() << ", " << p.z()
     << ", m=" << p.m() << ")";
  return os;
}

ostream & operator << ( ostream & os, const rave::Vector7D & p )
{
    #define sep ","<<setw(7)
    #define sep2 ","<<setw(10)
    os << setprecision(3) << fixed << right 
       << "(" << p.x()  << sep << p.y()  << sep << p.z() << sep2;
    os << setprecision(4)
       << p.px() << sep2 << p.py() << sep2 << p.pz() << sep2
       << setw(6) << setprecision(1) << p.m()  << ")";
    return os;
}
#endif

ostream& operator<< ( ostream& os, const rave::Covariance3D & p )
{
  #define sep3 " "<<setw(12)
  os << setprecision(4) << scientific << right
     << "(" << sep3 << p.dxx()  << sep3 << p.dxy()  << sep3 << p.dxz() << endl
     << "(" << sep3 << p.dxy()  << sep3 << p.dyy()  << sep3 << p.dyz() << endl
     << "(" << sep3 << p.dxz()  << sep3 << p.dyz()  << sep3 
     << p.dzz() << ")" << endl;
  return os;
}

ostream& operator<< ( ostream& os, const rave::Covariance6D & p )
{
  /*
  os << "(" << setprecision(7) << p.dxx() << endl
     << " " << p.dxy() << " " << p.dyy() << endl
     << " " << p.dxz() << " " << p.dyz() << " " << p.dzz() << ")" << endl;
  os << "(" << p.dpxpx() << endl
     << " " << p.dpxpy() << " " << p.dpypy() << endl
     << " " << p.dpxpz() << " " << p.dpypz() << " " << p.dpzpz() << ")" << endl;
  os << "(" << p.dxpx() << " " << p.dxpy() << " " << p.dxpz() << endl
     << " " << p.dypx() << " " << p.dypy() << " " << p.dypz() << endl
     << " " << p.dzpx() << " " << p.dzpy() << " " << p.dzpz() << ")" << endl;
     */
  os << "(" << setprecision(7) << scientific << p.dxx() << "     " << p.dxy() << "       " << p.dxz()
     << "       " << p.dxpx() << "      " << p.dxpy() << "      " << p.dxpz() << endl

     << "(" << p.dxy() << "        " << p.dyy() << "       " << p.dyz() << "       " << p.dypx()
     << "      " << p.dypy() << "      " << p.dypz() << endl

     << "(" << p.dxz() << "        " << p.dyz() << "       " << p.dzz() << "       " << p.dzpx()
     << "      " << p.dzpy() << "      " << p.dzpz() << endl

     << "(" << p.dxpx() << "       " << p.dypx() << "      " << p.dzpx() << "      " << p.dpxpx()
     << "     " << p.dpxpy() << "     " << p.dpxpz() << endl

     << "(" << p.dxpy() << "       " << p.dypy() << "      " << p.dzpy() << "      " << p.dpxpy()
     << "     " << p.dpypy() << "     " << p.dpypz() << endl

     << "(" << p.dxpz() << "       " << p.dypz() << "      " << p.dzpz() << "      " << p.dpxpz()
     << "     " << p.dpypz() << "     " << p.dpzpz() << ")" << endl;
  return os;
}

ostream& operator<< ( ostream& os, const rave::Ellipsoid3D & p )
{
  rave::Point3D pt = p.point();
  const rave::Covariance3D & cov = p.covariance();
  /*
  if ( isDiagonal ( cov ) )
  {
    os << "(" << setprecision(4) << fixed << pt.x() << "+/-" << sqrt ( cov.dxx() )
    << ", " << pt.y() << "+/-" << sqrt ( cov.dyy() )
    << ", " << pt.z() << "+/-" << sqrt ( cov.dzz() )
    << ")";
  }
  else*/
  {
    os << setprecision(4) << fixed << pt << endl << "Cov=" << endl << scientific << cov;
  }
  return os;
}


/*
ostream& operator<< (ostream& os, const rave::Vector3D & p )
{
  os << "(" << p.x() << ", " << p.y() << ", " << p.z() << ")";
  return os;
}*/

ostream& operator<< ( ostream& os, const rave::Vector6D & p )
{
  os << "(" << setprecision(6) << fixed << p.x() << ", " << p.y() << ", " << p.z() << " , "
  << p.px() << ", " << p.py() << ", " << p.pz() << ")";
  return os;
}

ostream& operator<< ( ostream& os, const rave::Track & t )
{
  os << t.state();
  return os;
}

ostream& operator<< ( ostream& os, const rave::Vertex & v )
{
  os << "id: " << v.id() << ", position: " << v.position();
  return os;
}
