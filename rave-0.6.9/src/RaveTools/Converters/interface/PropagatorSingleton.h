#ifndef _PropagatorSingleton_H_
#define _PropagatorSingleton_H_

#include "TrackingTools/GeomPropagators/interface/Propagator.h"

class PropagatorSingleton
{
  /** singleton that provides the magnetic field.
   */
  public:
    void initialise();
    static PropagatorSingleton * Instance();
    void registry ( const Propagator & prop );
    const Propagator * propagator() const;

  private:
    PropagatorSingleton();
    PropagatorSingleton ( const PropagatorSingleton & );
    Propagator * thePropagator;
};

#endif
