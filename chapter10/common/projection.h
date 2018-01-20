#ifndef PROJECTION_H
#define PROJECTION_H

#include "tools/rotation.h"

// camera : 9 dims array with
// [0-2] : angle-axis rotation
// [3-5] : translateion
// [6-8] : camera parameter, [6] focal length, [7-8] second and forth order radial distortion
// point : 3D location.
// predictions : 2D predictions with center of the image plane.

// See fig10-2 in page@246, SLAM十四讲
template<typename T>
inline bool CamProjectionWithDistortion(const T* camera, const T* point, T* predictions) {
    // Step 1: R, t
    T p[3];
    AngleAxisRotatePoint(camera, point, p);    // = Rp
    p[0] += camera[4];                         // = Rp + t
    p[1] += camera[5];
    p[2] += camera[6];

    T xp = -p[0] / p[2];
    T yp = -p[1] / p[2];

    // Step 2: Distortion
    const T& l1 = camera[7];
    const T& l2 = camera[8];

    T r2 = xp*xp + yp * yp;
    T distortion = T(1.0) + r2 * (l1 + l2 * r2);

    // Step 3 & 4
    const T& focal = camera[6];
    predictions[0] = focal * distortion * xp;
    predictions[1] = focal * distortion * yp;
}

#endif // projection.h