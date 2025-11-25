#include "RaveTools/Converters/interface/PropagatorSingleton.h"
#include "RaveTools/Converters/interface/MagneticFieldSingleton.h"
#include "TrackingTools/GeomPropagators/interface/AnalyticalPropagator.h"

using namespace std;

PropagatorSingleton::PropagatorSingleton() : 
  thePropagator( 0 )
{}

void PropagatorSingleton::initialise()
{
  static bool init=true; // make sure we dont init twice
  if (init)
  {
    thePropagator = new AnalyticalPropagator( MagneticFieldSingleton::Instance() );
    init=false;
  }
}

PropagatorSingleton::PropagatorSingleton( const PropagatorSingleton & o )
{
  cout << "[PropagatorSingleton] Arrgh! Fatal!" << endl;
}

PropagatorSingleton * PropagatorSingleton::Instance()
{
  static PropagatorSingleton singleton;
  return &singleton;
}

void PropagatorSingleton::registry ( const Propagator & prop )
{
  delete thePropagator;
  thePropagator = prop.clone();
}

const Propagator * PropagatorSingleton::propagator() const
{
  return thePropagator;
}
