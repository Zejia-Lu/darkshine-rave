#include "RaveBase/RaveInterface/rave/BasicVertex.h"
#include "RaveBase/RaveEngine/interface/RaveId.h"

using namespace rave;
using namespace std;

BasicVertex::BasicVertex( const Point3D & p, const Covariance3D & e,
      const vector < pair < float, Track > > & tracks, float ndf, float chi2 ) :
  thePoint ( p ), theError ( e ), theTracks ( tracks ), theNdf ( ndf ), theChi2 (chi2 ),
  theId ( RaveId::uniqueId() ), theValid ( true )
{}

BasicVertex::BasicVertex( const Point3D & p, const Covariance3D & e,
      const vector < pair < float, Track > > & tracks,
      const vector < pair < float, Track > > & ftracks, float ndf, float chi2 ) :
  thePoint ( p ), theError ( e ), theTracks ( tracks ), theFittedTracks ( ftracks),
  theNdf ( ndf ), theChi2 (chi2 ), theId ( RaveId::uniqueId() ), theValid ( true )
{}

BasicVertex::BasicVertex( const Point3D & p, const Covariance3D & e,
      const vector < Track > & tracks, float ndf, float chi2 ) :
  thePoint ( p ), theError ( e ), theNdf ( ndf ), theChi2 (chi2 ),
             theId ( RaveId::uniqueId() ), theValid ( true )
{
  for ( vector< Track >::const_iterator i=tracks.begin(); i!=tracks.end() ; ++i )
  {
    theTracks.push_back ( pair < float, Track > ( 1., *i ) );
  }
}

BasicVertex::BasicVertex( const Point3D & p, const Covariance3D & e,
      const vector < Track > & tracks, const vector < Track > & ftracks, 
      float ndf, float chi2 ) :
  thePoint ( p ), theError ( e ), theNdf ( ndf ), theChi2 (chi2 ),
             theId ( RaveId::uniqueId() ), theValid ( true )
{
  for ( vector< Track >::const_iterator i=tracks.begin(); i!=tracks.end() ; ++i )
  {
    theTracks.push_back ( pair < float, Track > ( 1., *i ) );
  }
  for ( vector< Track >::const_iterator i=ftracks.begin(); i!=ftracks.end() ; ++i )
  {
    theFittedTracks.push_back ( pair < float, Track > ( 1., *i ) );
  }
}

BasicVertex::BasicVertex() : theValid ( false )
{}

const Point3D & BasicVertex::position() const
{
  return thePoint;
}

const Covariance3D & BasicVertex::error() const
{
  return theError;
}

int BasicVertex::id() const
{
  return theId;
}


const vector < pair < float, Track > > & BasicVertex::weightedTracks() const
{
  return theTracks;
}

const vector < pair < float, Track > > & BasicVertex::weightedRefittedTracks() const
{
  return theFittedTracks;
}

vector < Track > BasicVertex::tracks() const
{
  vector < Track > ret;
  for ( vector< pair < float, Track > >::const_iterator i = theTracks.begin(); 
        i!=theTracks.end() ; ++i )
  {
    ret.push_back ( i->second );
  }
  return ret;
}

vector < Track > BasicVertex::refittedTracks() const
{
  vector < Track > ret;
  for ( vector< pair < float, Track > >::const_iterator i = theFittedTracks.begin(); 
        i!=theFittedTracks.end() ; ++i )
  {
    ret.push_back ( i->second );
  }
  return ret;
}

float BasicVertex::ndf() const
{
  return theNdf;
}

float BasicVertex::chiSquared() const
{
  return theChi2;
}

/*
std::vector < BasicVertex > BasicVertex::components() const
{
  return theComponents;
}*/

bool BasicVertex::hasRefittedTracks() const
{
  return (theFittedTracks.size()>0);
}

bool BasicVertex::isValid() const
{
  return theValid;
}

Track BasicVertex::refittedTrack ( const Track & orig ) const
{
  int ctr=0;
  for ( vector< std::pair < float, Track > >::const_iterator i=theTracks.begin(); 
        i!=theTracks.end() ; ++i )
  {
    if ( i->second == orig && theFittedTracks.size() == theTracks.size() )
    {
      return theFittedTracks[ctr].second;
    }
    ctr++;
  }
  return Track();
}
