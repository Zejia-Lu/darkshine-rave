
#include <iostream>
#include <sstream>

#include <rave/Version.h>
#include <rave/TransientTrackKinematicParticle.h>
#include "RaveBase/Converters/interface/RaveStreamers.h"
#include <rave/KinematicConstraintBuilder.h>
#include <rave/KinematicTreeFactory.h>

namespace {
  std::vector< rave::KinematicParticle > createParticles()
  {
    rave::Vector7D state1 ( 0.0005, -0.0004, 0.0021 , 44.4013, -105.9691, -30.3117 , 0.1057 );
    rave::Covariance7D cov1 (
                             8.50656e-07,  3.56427e-07,  9.62538e-15,
                             1.49344e-07,  4.03306e-15,
                             1.0696e-06,
                            -2.77976e-16, -1.16473e-16, -2.87083e-24,
                            -1.16473e-16, -4.88024e-17, -1.20289e-24,
                            -2.91787e-09, -1.22259e-09, -3.01346e-17,
                             0.0700778,   -0.165901,    -0.0474548,
                             0.396507,     0.113256,
                             0.032961,
                             0,   0,   0,   0,   0,   0,   6.22602 );
    rave::TransientTrackKinematicParticle particle1 (state1, cov1, -1, 100, 100);

    rave::Vector7D state2 ( 0.0010, 0.0002, 0.0007 , -6.6120, 15.7588, 4.5056 , 0.1057 );
    rave::Covariance7D cov2 (
                             8.50308e-07,  3.56769e-07,  7.17103e-15,
                             1.49692e-07,  3.00879e-15,
                             1.06951e-06,
                             1.95294e-17,  8.19406e-18,  8.98253e-26,
                             8.19406e-18,  3.43803e-18,  3.76885e-26,
                             2.91535e-09,  1.22321e-09,  1.34092e-17,
                             4.48856e-05, -7.71998e-05, -2.20724e-05,
                             0.000196489,  5.26065e-05,
                             2.75353e-05,
                             0,   0,   0,   0,   0,   0,   6.22602 );
    rave::TransientTrackKinematicParticle particle2 (state2, cov2, +1, 100, 100);

    std::vector< rave::KinematicParticle > particles;
    particles.push_back( particle1 );
    particles.push_back( particle2 );

    return particles;
  }

  std::string fit ()
  {
    std::ostringstream o;
    rave::ConstantMagneticField mfield(0.,0.,4.);
    rave::KinematicTreeFactory factory ( mfield, rave::VacuumPropagator() );
    rave::KinematicConstraint constraint =
        rave::KinematicConstraintBuilder().createTwoTrackMassKinematicConstraint( 91.1876 );
    std::vector < rave::KinematicParticle > input_particles = createParticles();
    rave::KinematicTree tree;
    try {
      tree = factory.useVertexFitter( input_particles );
    } catch ( ... ) {};
    if (!tree.isValid())
    {
      o << "The decay could not be reconstructed.";
    }
    else
    {
      rave::KinematicParticle topParticle = tree.topParticle();
      o << "The reconstructed mother particle is " << topParticle.fullstate();
    }
    return o.str();
  }

  std::string version()
  {
    std::ostringstream o;
    o << "Rave Version " << rave::Version();
    return o.str();
  }
}

int main(void)
{
  std::cout << "This is Rave Version " << rave::Version() << std::endl;
  std::cout << "Fitting says: " << fit() << std::endl;
  return 0;
}

