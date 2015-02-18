#ifndef FUNCTION_H
#define FUNCTION_H		


#include <stdio.h>
#include <GL\glut.h>
#include <GL/glext.h>

#include <vector>
#include "vector3D.h"

#include "GameTime.h"
#include "LuaReading.h"

#include <fstream>

typedef struct {
float x, y, z, u, v;
} Vertex, Normal;

typedef struct {
float u, v;
} TexCoord;

typedef struct {
int * vIndices, * nIndices, * tcIndices;
int vCount;
} Face;

typedef struct _Mesh {
Vertex * vertices;
Normal * normals;
TexCoord * texCoords;
Face * faces;
int noVertices, noNormals, noTexCoords, noFaces;
} Mesh;

typedef struct {
	bool mLButtonUp;
	bool mRButtonUp;
	bool middleButtonUp; 
	int lastX, lastY; 
} theMouseInfo;

typedef struct												// Create A Structure
{
	GLubyte	*imageData;										// Image Data (Up To 32 Bits)
	GLuint	bpp;											// Image Color Depth In Bits Per Pixel.
	GLuint	width;											// Image Width
	GLuint	height;											// Image Height
	GLuint	texID;											// Texture ID Used To Select A Texture
} TextureImage;

typedef struct
{
	Vector3D Max;
	Vector3D Min;

}Region;


typedef struct {
	float current,
		max;
	int	no;
}STATE;

inline std::string GetStringFromLua(const char* LuaFile , const char* Variable  );
inline int GetIntFromLua(const char* LuaFile , const char* Variable  );


//LuaValue:

//inline to prevent mutliple init
inline bool LoadTGA(TextureImage *texture, char *filename){		// Loads A TGA File Into Memory
		   
		GLubyte		TGAheader[12]={0,0,2,0,0,0,0,0,0,0,0,0};	// Uncompressed TGA Header
		GLubyte		TGAcompare[12];								// Used To Compare TGA Header
		GLubyte		header[6];									// First 6 Useful Bytes From The Header
		GLuint		bytesPerPixel;								// Holds Number Of Bytes Per Pixel Used In The TGA File
		GLuint		imageSize;									// Used To Store The Image Size When Setting Aside Ram
		GLuint		temp;										// Temporary Variable
		GLuint		type=GL_RGBA;								// Set The Default GL Mode To RBGA (32 BPP)

		FILE *file = fopen(filename, "rb");						// Open The TGA File

		if(	file==NULL ||										// Does File Even Exist?
			fread(TGAcompare,1,sizeof(TGAcompare),file)!=sizeof(TGAcompare) ||	// Are There 12 Bytes To Read?
			memcmp(TGAheader,TGAcompare,sizeof(TGAheader))!=0				||	// Does The Header Match What We Want?
			fread(header,1,sizeof(header),file)!=sizeof(header))				// If So Read Next 6 Header Bytes
		{
			if (file == NULL)									// Did The File Even Exist? *Added Jim Strong*
				return false;									// Return False
			else
			{
				fclose(file);									// If Anything Failed, Close The File
				return false;									// Return False
			}
		}

		texture->width  = header[1] * 256 + header[0];			// Determine The TGA Width	(highbyte*256+lowbyte)
		texture->height = header[3] * 256 + header[2];			// Determine The TGA Height	(highbyte*256+lowbyte)

		if(	texture->width	<=0	||								// Is The Width Less Than Or Equal To Zero
			texture->height	<=0	||								// Is The Height Less Than Or Equal To Zero
			(header[4]!=24 && header[4]!=32))					// Is The TGA 24 or 32 Bit?
		{
			fclose(file);										// If Anything Failed, Close The File
			return false;										// Return False
		}

		texture->bpp	= header[4];							// Grab The TGA's Bits Per Pixel (24 or 32)
		bytesPerPixel	= texture->bpp/8;						// Divide By 8 To Get The Bytes Per Pixel
		imageSize		= texture->width*texture->height*bytesPerPixel;	// Calculate The Memory Required For The TGA Data

		texture->imageData=(GLubyte *)malloc(imageSize);		// Reserve Memory To Hold The TGA Data

		if(	texture->imageData==NULL ||							// Does The Storage Memory Exist?
			fread(texture->imageData, 1, imageSize, file)!=imageSize)	// Does The Image Size Match The Memory Reserved?
		{
			if(texture->imageData!=NULL)						// Was Image Data Loaded
				free(texture->imageData);						// If So, Release The Image Data

			fclose(file);										// Close The File
			return false;										// Return False
		}

		for(GLuint i=0; i<int(imageSize); i+=bytesPerPixel)		// Loop Through The Image Data
		{														// Swaps The 1st And 3rd Bytes ('R'ed and 'B'lue)
			temp=texture->imageData[i];							// Temporarily Store The Value At Image Data 'i'
			texture->imageData[i] = texture->imageData[i + 2];	// Set The 1st Byte To The Value Of The 3rd Byte
			texture->imageData[i + 2] = temp;					// Set The 3rd Byte To The Value In 'temp' (1st Byte Value)
		}

		fclose (file);											// Close The File

		// Build A Texture From The Data
		glGenTextures(1, &texture[0].texID);					// Generate OpenGL texture IDs

		glBindTexture(GL_TEXTURE_2D, texture[0].texID);			// Bind Our Texture
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);	// Linear Filtered
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);	// Linear Filtered

		if (texture[0].bpp==24)									// Was The TGA 24 Bits
		{
			type=GL_RGB;										// If So Set The 'type' To GL_RGB
		}

		glTexImage2D(GL_TEXTURE_2D, 0, type, texture[0].width, texture[0].height, 0, type, GL_UNSIGNED_BYTE, texture[0].imageData);

		return true;											// Texture Building Went Ok, Return True
	
}

inline void renderMesh (Mesh *cur)
{
	for (int i = 0; i < cur->noFaces; i ++) 
	{
		Face * pf = &cur->faces[i];
		glBegin (GL_POLYGON);
		for (int j = 0; j < pf->vCount; j ++) 
		{
			glTexCoord2f (cur->texCoords[ pf->tcIndices[j] ].u,
			cur->texCoords[ pf->tcIndices[j] ].v);
			glNormal3f (cur->normals[ pf->nIndices[j] ].x,
			cur->normals[ pf->nIndices[j] ].y,
			cur->normals[ pf->nIndices[j] ].z);
			glVertex3f (cur->vertices[ pf->vIndices[j] ].x,
			cur->vertices[ pf->vIndices[j] ].y,
			cur->vertices[ pf->vIndices[j] ].z);
		}
		glEnd ();
	}
}

inline Mesh * LoadObj(char *filename){

	int vc = 0, nc = 0, tc = 0, fc = 0;
	char buf [256];
	FILE * fp = fopen (filename, "r");
	Mesh * pMesh = (Mesh *) malloc (sizeof (Mesh));
	pMesh->noNormals = pMesh->noTexCoords = pMesh->noVertices = pMesh->noFaces = 
	0;

	// initialise values in (*pMesh)
	// Count elements

	while (!feof(fp)) {
		if (!fgets (buf, 256, fp)) break; // read one line
		if (!strncmp ("vn ", buf, 3)) pMesh->noNormals ++;
		else if (!strncmp ("vt ", buf, 3)) pMesh->noTexCoords ++;
		else if (!strncmp ("v ", buf, 2)) pMesh->noVertices ++;
		else if (!strncmp ("f ", buf, 2)) pMesh->noFaces ++;
	}

	pMesh->vertices = (Vertex *) malloc (pMesh->noVertices * sizeof 
	(Vertex));

	pMesh->normals = (Normal *) malloc (pMesh->noNormals * sizeof 
	(Normal));

	pMesh->texCoords = (TexCoord *) malloc (pMesh->noTexCoords * sizeof 
	(TexCoord));

	pMesh->faces = (Face *) malloc (pMesh->noFaces * sizeof 
	(Face));


	fseek (fp, 0, SEEK_SET); // reset file ptr to beginning
	while (!feof (fp)) {
	fgets (buf, 256, fp);

	if (!strncmp ("vn ", buf, 3)) {
	sscanf ((buf + 2), "%f%f%f",
	&pMesh->normals[nc].x,
	&pMesh->normals[nc].y,
	&pMesh->normals[nc].z);
	nc++;
	} // process vn

	else if (!strncmp ("vt ", buf, 3)) {
	sscanf ((buf + 2), "%f%f%f",
	&pMesh->texCoords[tc].u,
	&pMesh->texCoords[tc].v);
	tc++;} // process vt

	else if (!strncmp ("v ", buf, 2)) {
	sscanf ((buf + 2), "%f%f%f",
	&pMesh->vertices[vc].x,
	&pMesh->vertices[vc].y,
	&pMesh->vertices[vc].z);
	vc++;} // process v

	else if (!strncmp ("f ", buf, 2)) {
	char * pSp = NULL;
	int ii = 0;
	Face * pf = &pMesh->faces[fc]; // process f
	for (int i = 0; i < strlen (buf); i ++){
	if (buf[i] == '/') ii ++; // no of '/'
	pf->vCount = ii / 2; // no of vertices
	pf->vIndices = (int *) malloc (pf->vCount * sizeof (int));
	pf->nIndices = (int *) malloc (pf->vCount * sizeof (int));
	pf->tcIndices = (int *) malloc (pf->vCount * sizeof (int));
	}

	pSp = strtok ((buf + 2), " \t\n");
	for (int i = 0; pSp; pSp = strtok (NULL, " \t\n"), i ++) {
	sscanf (pSp, "%d/%d/%d",
	&pf->vIndices[i],
	&pf->tcIndices[i],
	&pf->nIndices[i]);
	pf->vIndices[i] --;
	pf->tcIndices[i] --;
	pf->nIndices[i] --;
	}
	fc ++;
	}
	}
	fclose (fp); // close file
	return pMesh;
}


#endif