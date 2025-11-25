#ifndef _RaveVertex_H_
#define _RaveVertex_H_

#include <rave/Track.h>
#include <rave/Point3D.h>
#include <rave/Covariance3D.h>
#include <rave/BasicVertex.h>
#include <utility>
#include <vector>

namespace rave 
{

class RaveDllExport Vertex : private rave::BasicVertex::Proxy
{
  typedef rave::BasicVertex::Proxy Base;
  /**
   *  The output of the rave library: a reconstructed vertex.
   *  A position in 3d space, plus its error.
   *  Along with the (refitted!!) tracks and
   *  the association probabilities of tracks belonging to this vertex.
   *  also a (fractional) number of degrees of freedom (ndf)
   *  and chi-squared.
   */
  public:
    Vertex(); //< default constructor, creating invalid vertex. 
    Vertex( const rave::BasicVertex & );
    
    const rave::Point3D & position() const; //< The vertex position
    const rave::Covariance3D & error() const; //< The position's error

    /**
     *  the tracks plus the track weights
     */
    const std::vector < std::pair < float, rave::Track > > & weightedTracks() const;

    std::vector < rave::Track > tracks() const; //< the original tracks
    std::vector < rave::Track > refittedTracks() const; //< the refitted tracks
    /**
     *  the refitted tracks, with the weights
     */
    const std::vector < std::pair < float, rave::Track > > & weightedRefittedTracks() const;
    float ndf() const; //< number of degrees of freedom (may be fractional)
    float chiSquared() const; //< the total vertex fit chi squared.
    int id() const; // the vertex "id"
    bool isValid() const;
    bool hasRefittedTracks() const; //< do we have a collection of smoothed tracks?
    bool operator< ( const rave::Vertex & ) const;
    bool operator== ( const rave::Vertex & ) const;

    rave::Track refittedTrack ( const rave::Track & orig ) const;

    /**
     *  The vertex components - only used in the Gaussian
     *  algorithm.
     */
    std::vector < std::pair < float, rave::Vertex > > components() const;

    Vertex( const rave::Point3D &, const rave::Covariance3D &,
            const std::vector < std::pair < float, rave::Track > > & tracks, float ndf, float chi2,
            const std::vector < std::pair < float, rave::Vertex > > & components );
    Vertex( const rave::Point3D &, const rave::Covariance3D &,
            const std::vector < rave::Track > & tracks, float ndf, float chi2,
            const std::vector < std::pair < float, rave::Vertex > > & components );
    Vertex( const rave::Point3D &, const rave::Covariance3D &,
            const std::vector < std::pair < float, rave::Track > > & tracks, 
            const std::vector < std::pair < float, rave::Track > > & smoothedtracks, float ndf, float chi2,
            const std::vector < std::pair < float, rave::Vertex > > & components );
    Vertex( const rave::Point3D &, const rave::Covariance3D &,
            const std::vector < rave::Track > & tracks,
            const std::vector < rave::Track > & smoothedtracks, float ndf, float chi2,
            const std::vector < std::pair < float, rave::Vertex > > & components );
  private:
    std::vector < std::pair < float, rave::Vertex > > theComponents;

};

}

#endif
