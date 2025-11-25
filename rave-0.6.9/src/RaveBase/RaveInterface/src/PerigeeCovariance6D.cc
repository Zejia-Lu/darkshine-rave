#include "RaveBase/RaveInterface/rave/PerigeeCovariance6D.h"

#include <iomanip>

namespace rave {

PerigeeCovariance6D::PerigeeCovariance6D(
  float drr, float drt, float drp, float dre, float drz, float drm,
  float dtt, float dtp, float dte, float dtz, float dtm, float dpp,
  float dpe, float dpz, float dpm, float dee, float dez, float dem,
  float dzz, float dzm, float dmm) :
    PerigeeCovariance5D(drr, drt, drp, dre, drz, dtt, dtp, dte, dtz, dpp,
                        dpe, dpz, dee, dez, dzz),
    thedrm(drm), thedtm(dtm), thedpm(dpm), thedem(dem), thedzm(dzm),
    thedmm(dmm)
{
}

PerigeeCovariance6D::PerigeeCovariance6D(
  const PerigeeCovariance5D & fiveError,
  float drm, float dtm, float dpm, float dem, float dzm, float dmm) :
    PerigeeCovariance5D(fiveError),
    thedrm(drm), thedtm(dtm), thedpm(dpm), thedem(dem), thedzm(dzm),
    thedmm(dmm)
{
}

PerigeeCovariance6D::PerigeeCovariance6D() :
    PerigeeCovariance5D(),
    thedrm(0.), thedtm(0.), thedpm(0.), thedem(0.), thedzm(0.), thedmm(0.)
{
}

float PerigeeCovariance6D::drm() const
{
  return thedrm;
}

float PerigeeCovariance6D::dtm() const
{
  return thedtm;
}

float PerigeeCovariance6D::dpm() const
{
  return thedpm;
}

float PerigeeCovariance6D::dem() const
{
  return thedem;
}

float PerigeeCovariance6D::dzm() const
{
  return thedzm;
}

float PerigeeCovariance6D::dmm() const
{
  return thedmm;
}

RaveDllExport std::ostream& operator<< (std::ostream& os, const rave::PerigeeCovariance6D & c )
{
  #define sep " "<<std::setw(12)
  os << std::setprecision(4) << std::scientific << std::right
     << "(" << sep << c.drr() << sep << c.drt() << sep << c.drp() << sep << c.dre() << sep << c.drz() << sep << c.drm() << std::endl
     << "(" << sep << c.drt() << sep << c.dtt() << sep << c.dtp() << sep << c.dte() << sep << c.dtz() << sep << c.dtm() << std::endl
     << "(" << sep << c.drp() << sep << c.dtp() << sep << c.dpp() << sep << c.dpe() << sep << c.dpz() << sep << c.dpm() << std::endl
     << "(" << sep << c.dre() << sep << c.dte() << sep << c.dpe() << sep << c.dee() << sep << c.dez() << sep << c.dem() << std::endl
     << "(" << sep << c.drz() << sep << c.dtz() << sep << c.dpz() << sep << c.dez() << sep << c.dzz() << sep << c.dzm() << std::endl
     << "(" << sep << c.drm() << sep << c.dtm() << sep << c.dpm() << sep << c.dem() << sep << c.dzm() << sep << c.dmm() << ")" << std::endl;
  return os;
}

} // namespace rave
