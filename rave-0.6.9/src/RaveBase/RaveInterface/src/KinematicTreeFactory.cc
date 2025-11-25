#include "RaveBase/RaveInterface/rave/KinematicTreeFactory.h"

#include "FWCore/MessageLogger/interface/MessageLogger.h"
#include "RecoVertex/KinematicFit/interface/KinematicParticleVertexFitter.h"
#include "RecoVertex/KinematicFit/interface/KinematicConstrainedVertexFitter.h"
#include "RecoVertex/KinematicFit/interface/KinematicParticleFitter.h"
#include "RecoVertex/KinematicFit/interface/LagrangeParentParticleFitter.h"
#include "RecoVertex/KinematicFit/interface/LagrangeChildUpdator.h"
#include "RecoVertex/KinematicFitPrimitives/interface/KinematicConstraint.h"
#include "RecoVertex/KinematicFitPrimitives/interface/MultiTrackKinematicConstraint.h"
#include "DataFormats/GeometrySurface/interface/BlockWipedAllocator.h"

#include "RaveBase/Converters/interface/MagneticFieldWrapper.h"
#include "RaveBase/RaveEngine/interface/RaveBeamSpotSingleton.h"
#include "RaveBase/RaveEngine/interface/RaveParameterSetBuilder.h"
#include "RaveTools/Converters/interface/MagneticFieldSingleton.h"

#include "boost/bind.hpp"

namespace rave
{

void KinematicTreeFactory::wipe() const
{
  // blockWipedPool().wipe();
  // blockWipedPool().clear();
}

KinematicTreeFactory::KinematicTreeFactory (
  const rave::MagneticField & f, const rave::Propagator & p, int verbosity ) :
    theField ( f.copy() ), thePropagator ( p.copy() ),
    theVerbosity ( verbosity )
{
  setup();
}

rave::KinematicTreeFactory::KinematicTreeFactory (
  const rave::MagneticField & f, const rave::Propagator & p,
  const rave::Ellipsoid3D & beamspot, int verbosity ) :
    theField ( f.copy() ), thePropagator ( p.copy() ),
    theVerbosity ( verbosity )
{
  rave::BeamSpotSingleton::set ( beamspot );
  setup();
}

KinematicTreeFactory::~KinematicTreeFactory()
{}

void KinematicTreeFactory::setup()
{
  int rave_verbosity = theVerbosity;
  if (rave_verbosity < 0) rave_verbosity = 0;
  if (rave_verbosity > 4) rave_verbosity = 4;
  edm::setLogLevel(edm::Level(rave_verbosity));
  
  MagneticFieldSingleton::Instance()->registry ( new MagneticFieldWrapper ( *theField ) );

  edm::LogInfo ( "rave::KinematicTreeFactory" )
  << " magnetic field at (0,0,0) is "
  << MagneticFieldSingleton::Instance()->inTesla ( GlobalPoint ( 0., 0., 0. ) )
  << endl;
  
  BlockWipedPoolAllocated::usePool();
}

namespace
{
::RefCountedKinematicParticle doParticleCasting ( const boost::any & p )
{
  return boost::any_cast< ::RefCountedKinematicParticle > ( p );
}

::RefCountedKinematicTree doTreeCasting ( const boost::any & t )
{
  return boost::any_cast< ::RefCountedKinematicTree > ( t );
}
}

KinematicTree KinematicTreeFactory::useVertexFitter (
  std::vector< KinematicParticle > particles, std::string parameters ) const
{
  try {
    // The fitter we are going to use
    ::KinematicParticleVertexFitter fitter;

    // Create the input data field
    std::vector< ::RefCountedKinematicParticle > internalParticles;
    std::transform (
      particles.begin(),
      particles.end(),
      std::back_inserter( internalParticles ),
      boost::bind ( &doParticleCasting,
                    boost::bind( &BasicKinematicParticle::getInternal,
                                 boost::bind( &KinematicParticle::data, _1 ) ) ) );

    ::RefCountedKinematicTree internalTree;
    if ( particles.size() > 1 ) {
      // For multiple particles perform the fit
      // Do the fitting, this is where the real work is done
      internalTree = fitter.fit( internalParticles );
    } else {
      // For single particles, just add them to the tree
      KinematicVertexFactory kvfactory;
      internalTree = ReferenceCountingPointer< ::KinematicTree >( new ::KinematicTree() );
      internalTree->addParticle( kvfactory.vertex(), kvfactory.vertex(), internalParticles[0] );
    }

    // Now parse the tree into the interface format
    KinematicTree ret = rave::KinematicTree( BasicKinematicTree( internalTree, particles ) );
    wipe();
    return ret;

  } catch ( VertexException e ) {
    edm::LogError ( "rave::KinematicTreeFactory" ) << "VertexException saying """ << e.what() << """ occured.";
    wipe();
    return rave::KinematicTree();
  }
}

rave::KinematicTree KinematicTreeFactory::useVertexFitter (
  std::vector< rave::KinematicParticle > particles,
  rave::KinematicConstraint cs, std::string parameters ) const
{
  if (!cs.isValid()) {
    edm::LogWarning("rave::KinematicTreeFactory") 
      << "Called useVertexFitter with invalid constraint. "
      << "I will default to the non-constraint version.";
    return useVertexFitter( particles, parameters );
  }

  try {
    // The fitter we are going to use
    ::KinematicConstrainedVertexFitter fitter;

    // Create the input data field
    std::vector< ::RefCountedKinematicParticle > internalParticles;
    std::transform (
      particles.begin(),
      particles.end(),
      std::back_inserter ( internalParticles ),
      boost::bind ( &doParticleCasting,
                    boost::bind ( &BasicKinematicParticle::getInternal,
                                  boost::bind ( &KinematicParticle::data, _1 ) ) ) );

    // Unwrap the constraint
    MultiTrackKinematicConstraint * internalConstraint =
      boost::any_cast< boost::shared_ptr< ::MultiTrackKinematicConstraint > > (
        cs.data().getInternal() ).get();

    // Do the fitting, this is where the real work is done
    ::RefCountedKinematicTree internalTree = fitter.fit ( internalParticles, internalConstraint );

    // Now parse the tree into the interface format
    rave::KinematicTree tree = rave::KinematicTree ( BasicKinematicTree ( internalTree, particles ) );
    wipe();
    return tree;
  } catch ( VertexException e ) {
    edm::LogError ( "rave::KinematicTreeFactory" ) << "VertexException saying """ << e.what() << """ occured (2).";
    wipe();
    return rave::KinematicTree();
  }
}

std::vector< rave::KinematicTree > KinematicTreeFactory::useParticleFitter (
  std::vector< rave::KinematicTree > trees,
  rave::KinematicConstraint cs, std::string parameters ) const
{
  if (!cs.isValid()) {
    edm::LogError("rave::KinematicTreeFactory") 
      << "Called useParticleFitter with invalid constraint. "
      << "A non-constraint version does not exist.";
    return std::vector< rave::KinematicTree >();
  }

  try {
    // The fitter we are going to use
    ::KinematicParticleFitter fitter ( ParameterSetBuilder::create ( parameters ) );

    // Create the input data field
    std::vector< ::RefCountedKinematicTree > internalInputTrees;
    std::transform (
      trees.begin(),
      trees.end(),
      std::back_inserter ( internalInputTrees ),
      boost::bind ( &doTreeCasting,
                    boost::bind ( &BasicKinematicTree::getInternal,
                                  boost::bind ( &KinematicTree::data, _1 ) ) ) );

    // Unwrap the constraint
    ::KinematicConstraint * internalConstraint =
      boost::any_cast< boost::shared_ptr< ::KinematicConstraint > > (
        cs.data().getInternal() ).get();

    edm::LogInfo ( "KinematicTreeFactory" ) << "Using KinematicParticleFitter with "
    << internalInputTrees.size() << " input tree(s)";
    // Do the fitting, this is where the real work is done
    std::vector< ::RefCountedKinematicTree > internalOutputTrees =
      fitter.fit ( internalConstraint, internalInputTrees );

    // Create the output data field
    std::vector< rave::KinematicTree > outputTrees;
    for ( std::vector< ::RefCountedKinematicTree >::iterator i = internalOutputTrees.begin();
          i != internalOutputTrees.end();
          i++ )
    {
      outputTrees.push_back ( rave::KinematicTree ( rave::BasicKinematicTree ( *i ) ) );
    }

    wipe();
    return outputTrees;
  } catch ( VertexException e ) {
    edm::LogError ( "rave::KinematicTreeFactory" ) << "VertexException saying """ << e.what() << """ occured (1).";
    wipe();
    return std::vector< rave::KinematicTree >();
  }
}

std::vector< rave::KinematicParticle > KinematicTreeFactory::useParticleFitter (
  std::vector< rave::KinematicParticle > particles,
  rave::KinematicConstraint cs, std::string parameters ) const
{
  using namespace std;

  vector< KinematicTree > trees_uncs;
  for ( vector< KinematicParticle >::const_iterator particle =
        particles.begin(); particle != particles.end(); particle++ ) {
    vector< KinematicParticle > single_particle;
    single_particle.push_back( *particle );
    trees_uncs.push_back( useVertexFitter( single_particle ) );
  }

  vector< KinematicTree> trees_cs = useParticleFitter(trees_uncs, cs, parameters);

  vector< KinematicParticle> particles_cs;
  for (vector< KinematicTree >::iterator tree = trees_cs.begin(); 
       tree != trees_cs.end(); tree++) {
    if (tree->isValid()) particles_cs.push_back(tree->topParticle());
  }
  
  if (particles_cs.size() != particles.size()) {
    edm::LogWarning("rave::KinematicTreeFactory") << "useParticleFitter returned less particles than it took.";
  }
  
  wipe();
  return particles_cs;
}

const rave::Propagator & KinematicTreeFactory::getPropagator() const
{
  return *thePropagator;
}

const rave::MagneticField & KinematicTreeFactory::getMagneticField() const
{
  return *theField;
}

const rave::Ellipsoid3D & KinematicTreeFactory::getBeamspot() const
{
  return rave::BeamSpotSingleton::get();
}

bool KinematicTreeFactory::hasBeamspot() const
{
  return rave::BeamSpotSingleton::hasBeamSpot();
}

const int rave::KinematicTreeFactory::verbosity() const
{
  return theVerbosity;
}

}
