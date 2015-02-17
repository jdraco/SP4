#include "Node.h"

CNode::CNode() {}
CNode::~CNode() {}
void CNode::Draw() {}

void CNode::ApplyTranslate(const float dx, const float dy, const float dz, bool local) {}
void CNode::ApplyRotate(const float angle, const float rx, const float ry, const float rz) {}
void CNode::ApplyScale(const float sx, const float sy, const float sz) {}