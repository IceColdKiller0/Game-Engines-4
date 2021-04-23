#include "CollisionDetection.h"
#include "Ray.h"
#include "../Core/MainEngine.h"
#include "CollisionHandler.h"


CollisionDetection::~CollisionDetection()
{
}

Ray CollisionDetection::MousePosToWorldRay(glm::vec2 mouseCoords_, float screenWidth_, float screenHeight_, Camera* camera_)
{
    glm::vec4 rayStartNDC((mouseCoords_.x / screenWidth_ - 0.5f) * 2.0f, (mouseCoords_.y / screenHeight_ - 0.5f) *
        2.0f, -1.0f, 1.0f);
    glm::vec4 rayEndNDC((mouseCoords_.x / screenWidth_ - 0.5f) * 2.0f, (mouseCoords_.y / screenHeight_ - 0.5f) * 2.0f,
        0.0f, 1.0f);

    glm::mat4 inverse = glm::inverse(camera_->GetPerspective() * camera_->GetView());

    glm::vec4 rayStartWorld = inverse * rayStartNDC;
    rayStartWorld /= rayStartWorld.w;

    glm::vec4 rayEndWorld = inverse * rayEndNDC;
    rayEndWorld /= rayEndWorld.w;

    glm::vec3 rayDirWorld(rayEndWorld - rayStartWorld);
    rayDirWorld = glm::normalize(rayDirWorld);

    return Ray(glm::vec3(rayStartWorld), rayDirWorld);
}

bool CollisionDetection::RayObbIntersection(Ray* ray_, BoundingBox* box_)
{
    glm::mat4 modelMatrix = box_->transform;
    glm::vec3 rayOrigin = ray_->origin;
    glm::vec3 rayDirection = ray_->direction;
    glm::vec3 boxMin = box_->minVert;
    glm::vec3 boxMax = box_->maxVert;

    float tMin = MainEngine::GetInstance()->GetCamera()->GetNearPlane();
    float tMax = MainEngine::GetInstance()->GetCamera()->GetFarPlane();

    glm::vec3 worldPos(modelMatrix[3].x, modelMatrix[3].y, modelMatrix[3].z);
    glm::vec3 delta = worldPos - rayOrigin;

    //X axis
    glm::vec3 xAxis(modelMatrix[0].x, modelMatrix[0].y, modelMatrix[0].z);
    float dotDelta = glm::dot(xAxis, delta);
    float dotDir = glm::dot(rayDirection, xAxis);
    if (fabs(dotDir) > 0.001f)
    {
        float t1 = (dotDelta + boxMin.x) / dotDir;
        float t2 = (dotDelta + boxMax.x) / dotDir;

        if (t1 > t2)
        {
            float w = t1;
            t1 = t2;
            t2 = w;
        }

        if (t2 < tMax)
        {
            tMax = t2;
        }

        if (t1 > tMin)
        {
            tMin = t1;
        }

        if (tMax < tMin)
        {
            return false;
        }
    }
    else
    {
        if (-dotDelta + boxMin.x > 0.0f || -dotDelta + boxMax.x < 0.0f)
        {
            return false;
        }
    }

    //Y axis
    glm::vec3 yAxis(modelMatrix[1].x, modelMatrix[1].y, modelMatrix[1].z);
    float dotDelta_y = glm::dot(yAxis, delta);
    float dotDir_y = glm::dot(rayDirection, yAxis);
    if (fabs(dotDir_y) > 0.001f)
    {
        float t1 = (dotDelta_y + boxMin.y) / dotDir_y;
        float t2 = (dotDelta_y + boxMax.y) / dotDir_y;

        if (t1 > t2)
        {
            float w = t1;
            t1 = t2;
            t2 = w;
        }

        if (t2 < tMax)
        {
            tMax = t2;
        }

        if (t1 > tMin)
        {
            tMin = t1;
        }

        if (tMax < tMin)
        {
            return false;
        }
    }
    else
    {
        if (-dotDelta_y + boxMin.y > 0.0f || -dotDelta_y + boxMax.y < 0.0f)
        {
            return false;
        }
    }

    //Z axis
    glm::vec3 zAxis(modelMatrix[2].x, modelMatrix[2].y, modelMatrix[2].z);
    float dotDelta_z = glm::dot(zAxis, delta);
    float dotDir_z = glm::dot(rayDirection, zAxis);
    if (fabs(dotDir_z) > 0.001f)
    {
        float t1 = (dotDelta_z + boxMin.z) / dotDir_z;
        float t2 = (dotDelta_z + boxMax.z) / dotDir_z;

        if (t1 > t2)
        {
            float w = t1;
            t1 = t2;
            t2 = w;
        }

        if (t2 < tMax)
        {
            tMax = t2;
        }

        if (t1 > tMin)
        {
            tMin = t1;
        }

        if (tMax < tMin)
        {
            return false;
        }
    }
    else
    {
        if (-dotDelta_z + boxMin.z > 0.0f || -dotDelta_z + boxMax.z < 0.0f)
        {
            return false;
        }
    }

    ray_->intersectionDist = tMin;
    return true;
}
