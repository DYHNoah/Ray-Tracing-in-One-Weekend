#ifndef HITTABLE_H
#define HITTABLE_H

#include "ray.h"

struct hit_record {
    vec3 p;             //射线与物体的交点
    vec3 normal;        // 法线
    double t;           //相交时间
    bool front_face;    //面法相的朝向

    inline void set_face_normal(const ray& r, const vec3& outward_normal) {
	front_face = dot(r.direction(), outward_normal) < 0;
	normal = front_face ? outward_normal : -outward_normal;
    }
};

class hittable {
    public:
        virtual bool hit(const ray& r, double t_min, double t_max, hit_record& rec) const = 0;
};

#endif
