#ifndef HSD_SCENE_H
#define HSD_SCENE_H

struct HSD_Joint;
struct HSD_AnimJoint;
struct HSD_MatAnimJoint;
struct HSD_ShapeAnimJoint;

struct _HSD_SceneModelSet {
    struct HSD_Joint* joint;
    struct HSD_AnimJoint** animations;
    struct HSD_MatAnimJoint** materialAnimations;
    struct HSD_ShapeAnimJoint** shapeAnimations;
};

struct _HSD_SceneDesc {
    struct _HSD_SceneModelSet** models;
    void* cameras;
    void** lights;
    void** fogs;
};

#endif
