#version 430  
  
in vec3 Position;  
in vec3 Normal;  
in vec2 TextCoord;

uniform sampler2D texture_diffuse0;
uniform sampler2D texture_specular0;

uniform int lightNum;
uniform vec3 lightPositions[8];  
uniform vec4 lightColors[8];
uniform float lightItensities[8];
uniform float lightDS[8];

layout( location = 0 ) out vec4 FragColor;  
  
void main() {  
	vec4 texd = texture2D(texture_diffuse0, TextCoord);
	vec4 texs = texture2D(texture_specular0, TextCoord);

	vec3 s = normalize(lightPositions[0]);
	vec3 v = normalize(vec3(-Position));  
	vec3 r = reflect( -s, Normal );
		
	float dF = max( dot(s, Normal), 0.0 ) * lightItensities[0];
	float sF = pow( max( dot(r,v), 0.0 ), 60 ) * lightItensities[0];
	

	for(int i = 1; i < lightNum; i++){
		vec3 delta = lightPositions[i] - Position;
		float DS = dot(delta,delta);
		s = normalize(delta);  
		v = normalize(vec3(-Position));  
		r = reflect( -s, Normal );

		float rate = max(1-DS/lightDS[i],0.0);
		dF += max( dot(s, Normal), 0.0 ) * lightItensities[i] * rate;
		sF += pow( max( dot(r,v), 0.0 ), 60 ) * lightItensities[i] * rate;
	}

	vec4 ambient = texd * 0.1;
	vec4 diffuse = texd * dF;
	vec4 specular = texs * sF;

    FragColor = ambient + diffuse + specular;
}  