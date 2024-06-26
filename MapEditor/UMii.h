#pragma once

#include "Bfres.h"
#include "Camera.h"
#include "Shader.h"
#include "Vector3F.h"
#include <string>
#include <vector>

class UMii {
public:
    UMii(std::vector<unsigned char> BymlBytes);
    UMii() { }

    void Draw(Vector3F Translate, Vector3F Rotate, Vector3F Scale, Shader* Shader, bool Picking = false, Camera* CameraView = nullptr);

    std::string SexAge;
    std::string Type;
    std::string Number;
    std::string Race;

private:
    struct ModelElement {
        BfresFile* Model;
        Vector3F Translate;
        Vector3F Rotate;
        Vector3F Scale;
    };

    std::vector<ModelElement> m_ModelElements;
};
