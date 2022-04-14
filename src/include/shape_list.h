#ifndef SHAPE_LIST_H
#define SHAPE_LIST_H

#include "shape.h"

#include <iostream>
#include <memory>
#include <vector>

using std::shared_ptr;
using std::make_shared;

class ShapeList : public Shape
{
    public:
        ShapeList() {}
        ShapeList(shared_ptr<Shape> object) { add(object); }

        void clear() { objects.clear(); }
        void add(shared_ptr<Shape> object) { objects.push_back(object); }

        virtual bool hit(const ray& r, double t_min, double t_max, hit_record& rec) const override;

    public: 
        std::vector<shared_ptr<Shape> > objects;

};

bool ShapeList::hit(const ray& r, double t_min, double t_max, hit_record& rec) const
{
    hit_record temp_rec;
    bool hit_anything = false;
    double closest = t_max;
    for (const auto& object : objects)
    {
        if (object->hit(r, t_min, closest, temp_rec)) 
        {
            hit_anything = true;
            closest = temp_rec.t;
            rec = temp_rec;
        }
    }

    return hit_anything;
}

#endif