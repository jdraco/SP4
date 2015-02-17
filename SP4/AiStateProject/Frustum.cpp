#include "Frustum.h"

CFrustum::CFrustum(void)
{

}

CFrustum::~CFrustum(void)
{
}

void CFrustum::SelfInit(){
	up.Set(0,1,0);
	angle = 0;

	rotationAngle = 0;
	rotation = Vector3D(0,1,0);
	
	farDist = 15;
	nearDist = 0.1f;

	fPosition = Vector3D(0,0,-5);
	fDirection = Vector3D(0,0,3.14159f);
	fUp = Vector3D(0,1,0);

	Scale = 1.0f; //Default 1:1 Scale
	Color.Set();

	changeX = changeZ = false;

}

// Update the frustum
bool CFrustum::Update(void)
{
	//if(rotationAngle <
	//rotationAngle +=1;


	heightNear = 2 * tan(FOVY*0.5f) * nearDist * Scale;
	heightFar  = 2 * tan(FOVY*0.5f) * farDist * Scale;

	widthNear = heightNear* ASPECT_RATIO;
	widthFar  = heightFar * ASPECT_RATIO;

	farC = fPosition + (fDirection.normalized() * farDist* Scale);
	nearC = fPosition + (fDirection.normalized() * nearDist* Scale);

	right = (fDirection.normalized()).crossVector3D( up );

	ftl = farC + up * (heightFar*0.5f) - right * (widthFar * 0.5f) ;
	ftr = farC + up * (heightFar*0.5f) + right * (widthFar * 0.5f);
	fbl = farC - up * (heightFar*0.5f) - right * (widthFar * 0.5f);
	fbr = farC - up * (heightFar*0.5f) + right * (widthFar * 0.5f);

	ntl = nearC + up * (heightNear*0.5f) - right * (widthNear * 0.5f);
	ntr = nearC + up * (heightNear*0.5f) + right * (widthNear * 0.5f);
	nbl = nearC - up * (heightNear*0.5f) - right * (widthNear * 0.5f);
	nbr = nearC - up * (heightNear*0.5f) + right * (widthNear * 0.5f);

	Vector3D vector1,vector2;

	//updating farplane Vector
	vector1 = fbl - ftl;
	vector2 = ftr - ftl;
	farV = vector1.crossVector3D( vector2 );
	farV.normalizeVector3D();
	

	//updating nearplane Vector
	vector1 = nbl - ntl;
	vector2 = ntr - ntl;
	nearV = vector1.crossVector3D( vector2 );
	nearV.normalizeVector3D();

	//updating btmplane Vector
	vector1 = nbl - fbl;
	vector2 = fbr - fbl;
	btmV = vector1.crossVector3D( vector2 );
	btmV.normalizeVector3D();

	//updating topplane Vector
	vector1 = ntl - ftl;
	vector2 = ftr - ftl;
	topV = vector1.crossVector3D( vector2 );
	topV.normalizeVector3D();

	//updating leftPlane Vector
	vector1 = nbl - ntl;
	vector2 = ftl - ntl;
	leftV = vector1.crossVector3D( vector2 );
	leftV.normalizeVector3D();

	//updating rightPlaneVector
	vector1 = ftr - ntr;
	vector2 = nbr - ntr;
	rightV = vector1.crossVector3D( vector2 );
	rightV.normalizeVector3D();

	return true;
}

// Draw the frustum
void CFrustum::Render(void)
{
//	glPushMatrix();
	glPushAttrib(GL_ENABLE_BIT);
		glEnable( GL_BLEND );
		//glTranslatef(fPosition.x, fPosition.y, fPosition.z);
		glRotatef(rotationAngle,rotation.x,rotation.y,rotation.z);
		glBlendFunc( GL_SRC_ALPHA , GL_ONE_MINUS_SRC_ALPHA );
		glColor4f( Color.x, Color.y, Color.z, 0.6f);
		glBegin( GL_QUADS );
			glVertex3f(nbl.x, nbl.y, nbl.z);
			glVertex3f(ntl.x, ntl.y, ntl.z);

			glVertex3f(ntl.x, ntl.y, ntl.z);
			glVertex3f(ftl.x, ftl.y, ftl.z);
			
			glVertex3f(ftl.x, ftl.y, ftl.z);
			glVertex3f(fbl.x, fbl.y, fbl.z);
			
			glVertex3f(fbl.x, fbl.y, fbl.z);
			glVertex3f(nbl.x, nbl.y, nbl.z);

			
			glVertex3f(nbr.x, nbr.y, nbr.z);
			glVertex3f(ntr.x, ntr.y, ntr.z);

			glVertex3f(ntr.x, ntr.y, ntr.z);
			glVertex3f(ftr.x, ftr.y, ftr.z);
			
			glVertex3f(ftr.x, ftr.y, ftr.z);
			glVertex3f(fbr.x, fbr.y, fbr.z);
			
			glVertex3f(fbr.x, fbr.y, fbr.z);
			glVertex3f(nbr.x, nbr.y, nbr.z);


			glVertex3f(ftl.x, ftl.y, ftl.z);
			glVertex3f(ftr.x, ftr.y, ftr.z);

			glVertex3f(ftr.x, ftr.y, ftr.z);
			glVertex3f(fbr.x, fbr.y, fbr.z);

			glVertex3f(fbr.x, fbr.y, fbr.z);
			glVertex3f(fbl.x, fbl.y, fbl.z);

			glVertex3f(fbl.x, fbl.y, fbl.z);
			glVertex3f(ftl.x, ftl.y, ftl.z);

			
			glVertex3f(ntl.x, ntl.y, ntl.z);
			glVertex3f(ntr.x, ntr.y, ntr.z);
			
			glVertex3f(ntr.x, ntr.y, ntr.z);
			glVertex3f(ftr.x, ftr.y, ftr.z);
			
			glVertex3f(ftr.x, ftr.y, ftr.z);
			glVertex3f(ftl.x, ftl.y, ftl.z);
			
			glVertex3f(ftl.x, ftl.y, ftl.z);
			glVertex3f(ntl.x, ntl.y, ntl.z);

			
			glVertex3f(nbl.x, nbl.y, nbl.z);
			glVertex3f(nbr.x, nbr.y, nbr.z);
			
			glVertex3f(nbr.x, nbr.y, nbr.z);
			glVertex3f(fbr.x, fbr.y, fbr.z);
			
			glVertex3f(fbr.x, fbr.y, fbr.z);
			glVertex3f(fbl.x, fbl.y, fbl.z);
			
			glVertex3f(fbl.x, fbl.y, fbl.z);
			glVertex3f(nbl.x, nbl.y, nbl.z);
			
		glEnd();
		glDisable( GL_BLEND );
	glPopAttrib();

		// Draw the lines of the Frustum
		glColor3f(1.0f, 1.0f, 1.0f);
		glLineWidth(10);
		glBegin( GL_LINES );
			glVertex3f(ntl.x, ntl.y, ntl.z);
			glVertex3f(ntr.x, ntr.y, ntr.z);

			glVertex3f(ntr.x, ntr.y, ntr.z);
			glVertex3f(nbr.x, nbr.y, nbr.z);

			glVertex3f(nbr.x, nbr.y, nbr.z);
			glVertex3f(nbl.x, nbl.y, nbl.z);

			glVertex3f(nbl.x, nbl.y, nbl.z);
			glVertex3f(ntl.x, ntl.y, ntl.z);

			
			glVertex3f(ftl.x, ftl.y, ftl.z);
			glVertex3f(ftr.x, ftr.y, ftr.z);

			glVertex3f(ftr.x, ftr.y, ftr.z);
			glVertex3f(fbr.x, fbr.y, fbr.z);

			glVertex3f(fbr.x, fbr.y, fbr.z);
			glVertex3f(fbl.x, fbl.y, fbl.z);

			glVertex3f(fbl.x, fbl.y, fbl.z);
			glVertex3f(ftl.x, ftl.y, ftl.z);


			glVertex3f(ntl.x, ntl.y, ntl.z);
			glVertex3f(ftl.x, ftl.y, ftl.z);
			
			glVertex3f(ntr.x, ntr.y, ntr.z);
			glVertex3f(ftr.x, ftr.y, ftr.z);

			glVertex3f(nbl.x, nbl.y, nbl.z);
			glVertex3f(fbl.x, fbl.y, fbl.z);

			glVertex3f(nbr.x, nbr.y, nbr.z);
			glVertex3f(fbr.x, fbr.y, fbr.z);
		glEnd();
		glLineWidth(1);
//	glPopMatrix();
}
void CFrustum::RotateY(float angle)
{
	float theta = Math::DegreeToRadian(angle);

	//Alter X Dir
	if (!changeX)
		fDirection.x -= theta;
	else
		fDirection.x += theta;
	if (fDirection.x >= 1.0f)
		changeX = false;
	else if (fDirection.x <= -1.0f)
		changeX = true;

	//Alter Z Dir
	if (!changeZ)
		fDirection.z -= theta;
	else
		fDirection.z += theta;
	if (fDirection.z >= 1.0f)
		changeZ = false;
	else if (fDirection.z <= -1.0f)
		changeZ = true;
}


// Perform containment check for a position with respect to the Frustum
bool CFrustum::ContainmentCheck(const Vector3D position)
{
	Vector3D pointToPos;
	float angle;

	//checking against far plane
	pointToPos = position - ftl;
	angle = (pointToPos.normalized()).dotVector3D( farV );
	
	if (angle < 0)
	{
		return false;
	}

	//checking against near plane
	pointToPos = position - ntl;
	angle = (pointToPos.normalized()).dotVector3D( nearV );

	if (angle > 0)
	{
		return false;
	}

	//checking against btm plane
	pointToPos = position - fbl;
	angle = (pointToPos.normalized()).dotVector3D( btmV );

	if (angle < 0)
	{
		return false;
	}

	//checking against top plane
	pointToPos = position - ftl;
	angle = (pointToPos.normalized()).dotVector3D( topV );

	if (angle > 0)
	{
		return false;
	}

	//checking against left plane
	pointToPos = position - ntl;
	angle = (pointToPos.normalized()).dotVector3D( leftV );

	if (angle < 0)
	{
		return false;
	}
	
	//checking against right plane
	pointToPos = position - ntr;
	angle = (pointToPos.normalized()).dotVector3D( rightV );

	if (angle < 0)
	{
		return false;
	}
	return true;
}
