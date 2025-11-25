#ifndef _RaveStreamers_H_
#define _RaveStreamers_H_

#include <rave/Point3D.h>
#include <rave/Vector3D.h>
#ifdef WITH_KINEMATICS
#include <rave/Vector4D.h>
#include <rave/Vector7D.h>
#endif
#include <rave/Vector6D.h>
#include <rave/Track.h>
#include <rave/Vertex.h>
#include <rave/Ellipsoid3D.h>
#include <rave/Covariance3D.h>
#include <rave/Covariance6D.h>

#include <ostream>

RaveDllExport std::ostream& operator<< (std::ostream& os, const rave::Point3D & );
RaveDllExport std::ostream& operator<< (std::ostream& os, const rave::Covariance3D & );
RaveDllExport std::ostream& operator<< (std::ostream& os, const rave::Covariance6D & );
RaveDllExport std::ostream& operator<< (std::ostream& os, const rave::Ellipsoid3D & );
RaveDllExport std::ostream& operator<< (std::ostream& os, const rave::Vector6D & );
#ifdef WITH_KINEMATICS
RaveDllExport std::ostream& operator<< (std::ostream& os, const rave::Vector4D & );
RaveDllExport std::ostream& operator<< (std::ostream& os, const rave::Vector7D & );
#endif
RaveDllExport std::ostream& operator<< (std::ostream& os, const rave::Track & );
RaveDllExport std::ostream& operator<< (std::ostream& os, const rave::Vertex & );

#endif
