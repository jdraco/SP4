#ifndef NODE_H
#define NODE_H

class CNode
{
public:
	CNode(void);
	virtual ~CNode();
	virtual void Draw();

	virtual void ApplyTranslate(const float dx, const float dy, const float dz, bool local = true);
	virtual void ApplyRotate(const float angle, const float rx, const float ry, const float rz);
	virtual void ApplyScale(const float sx, const float sy, const float sz);
};

#endif
