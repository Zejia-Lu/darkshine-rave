#include "rave/MultipleKinematicConstraint.h"

#include "RecoVertex/KinematicFitPrimitives/interface/MultipleKinematicConstraint.h"

#include "boost/cast.hpp"

namespace rave
{

namespace
{
typedef boost::shared_ptr< ::MultipleKinematicConstraint > InternalMultipleKinematicContraint;
}

void BasicMultipleKinematicConstraint::addConstraint ( KinematicConstraint constraint ) const
{
  ::KinematicConstraint* internalConstraint =
    boost::any_cast< boost::shared_ptr< ::KinematicConstraint > > ( constraint.data().getInternal() ).get();
  boost::shared_polymorphic_cast< ::MultipleKinematicConstraint > (
    boost::any_cast< boost::shared_ptr< ::KinematicConstraint > > ( getInternal() ) )->addConstraint (
      internalConstraint );

  constraints.push_back ( constraint );
}

BasicMultipleKinematicConstraint::BasicMultipleKinematicConstraint (
  boost::any constraint ) :
    BasicKinematicConstraint ( constraint )
{
  BOOST_ASSERT ( typeid ( boost::shared_ptr< ::MultipleKinematicConstraint > ) == constraint.type() );
}

BasicMultipleKinematicConstraint::~BasicMultipleKinematicConstraint()
{}

BasicMultipleKinematicConstraint * BasicMultipleKinematicConstraint::clone() const
{
  return new BasicMultipleKinematicConstraint( *this );
}

}
