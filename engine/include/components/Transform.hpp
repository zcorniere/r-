#ifndef TRANSFORM_HPP
#define TRANSFORM_HPP

// Transform Component
class Transform {
    struct Dimensional {
        float x;
        float y;
    };
public:
    Dimensional location;
    Dimensional rotation;
    Dimensional scale;
public:
    Transform();
    Transform(Dimensional, Dimensional, Dimensional);
    Transform(Transform const &);
    ~Transform();
};

#endif
