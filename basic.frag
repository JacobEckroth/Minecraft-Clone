#version 330 compatibility
uniform float uKa, uKd, uKs; // coefficients of each type of lighting

uniform vec3 uSpecularColor; // light color
uniform float uShininess; // specular exponent

in vec2 vST; // texture cords
in vec3 vN; // normal vector
in vec3 vL; // vector from point to light
in vec3 vE; // vector from point to eye

uniform sampler2D uTexUnit;
void
main( )
{

	vec3 uColor = texture(uTexUnit,vST).rgb;
	//vec3 uColor = vec3(1,0,0);
	vec3 Normal = normalize(vN);
	vec3 Light = normalize(vL);
	vec3 Eye = normalize(vE);
	vec3 ambient = uKa * uColor;
	float d = max( dot(Normal,Light), 0. ); // only do diffuse if the light can see the point
	vec3 diffuse = uKd * d * uColor;
	float s = 0.;
	if( dot(Normal,Light) > 0. ) // only do specular if the light can see the point
	{
	vec3 ref = normalize( reflect( -Light, Normal ) );
	s = pow( max( dot(Eye,ref),0. ), uShininess );
	}
	vec3 specular = uKs * s * uSpecularColor;
	gl_FragColor = vec4( ambient + diffuse + specular, 1. );
}