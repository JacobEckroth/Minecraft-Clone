#version 330 compatibility
out vec2 vST; // texture coords
out vec3 vN; // normal vector
out vec3 vL; // vector from point to light
out vec3 vE; // vector from point to eye
uniform vec3 LIGHT1POSITION;
uniform vec3 CHUNKPOSITION;

void
main( )
{
	vec4 newPos = gl_Vertex + vec4(CHUNKPOSITION,1.);
	vST = gl_MultiTexCoord0.st;
	vec4 ECposition = gl_ModelViewMatrix * newPos;
	vN = normalize( gl_NormalMatrix * gl_Normal ); // normal vector
	vL = LIGHT1POSITION - ECposition.xyz; // vector from the point
	// to the light position
	vE = vec3( 0., 0., 0. ) - ECposition.xyz; // vector from the point
	// to the eye position
	gl_Position = gl_ModelViewProjectionMatrix * newPos;
}