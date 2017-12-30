#version 330

struct Material
{
	vec3  ambientColor;
	vec3  diffuseColor;
	vec3  specularColor;
	float transperancy;
	float specularExponent;
	vec3  emittedLight;
	vec3  transmissionFilter;
};

struct PointLight
{
	vec3 position;
    
	float quadratic; 
    float linear;
    float constant;

    vec3 diffuse;
    vec3 specular;
};

vec3 calculatePointLight(PointLight light,vec3 fragPos,vec3 normal);

struct DirectionalLight
{
	vec3 direction;
  
    vec3 diffuse;
    vec3 specular;
};

vec3 calculateDirectionalLight(DirectionalLight light,vec3 normal);

struct SpotLight
{
	vec3 position;
	vec3 direction;
	vec3 diffuse;
	vec3 specular;
	float innerCutOff;
	float outerCutOff;
	float quadratic;
	float linear;
	float constant;
};

vec3 calculateSpotLight(SpotLight light,vec3 fragPos,vec3 normal);

in vec3 vertexPositionOut;
in vec3 vertexNormalOut;
in vec2 vertexUVOut;

out vec4 fragColor;

#define NUM_POINT_LIGHTS 4
#define NUM_DIRECTIONAL_LIGHTS 1
#define NUM_SPOT_LIGHTS 1

#if NUM_POINT_LIGHTS > 0
uniform PointLight pointLights[NUM_POINT_LIGHTS];
#endif
#if NUM_DIRECTIONAL_LIGHTS > 0
uniform DirectionalLight directionalLights[NUM_DIRECTIONAL_LIGHTS];
#endif
#if NUM_SPOT_LIGHTS > 0
uniform SpotLight spotLights[NUM_SPOT_LIGHTS];
#endif
uniform vec4 ambientLight;
uniform vec3 eyePosition;
uniform Material material;

float ambientTransperancy;
float diffuseTransperancy;
float specularTransperancy;
vec4 ambientColor;
vec3 viewDir;

void calculateVariables();

void main()
{
	calculateVariables();
	
	vec4 resultingColor;

	#if NUM_POINT_LIGHTS > 0
	for(int i = 0;i<NUM_POINT_LIGHTS;i++)
		resultingColor += vec4(calculatePointLight(pointLights[i],vertexPositionOut,vertexNormalOut),1.0);
	#endif
	#if NUM_DIRECTIONAL_LIGHTS > 0
	for(int i = 0;i<NUM_DIRECTIONAL_LIGHTS;i++)
		resultingColor += vec4(calculateDirectionalLight(directionalLights[i],vertexNormalOut),1.0);
	#endif
	#if NUM_SPOT_LIGHTS > 0
	for(int i = 0;i<NUM_SPOT_LIGHTS;i++)
		resultingColor += vec4(calculateSpotLight(spotLights[i],vertexPositionOut,vertexNormalOut),1.0);
	#endif
	
	#if NUM_POINT_LIGHTS <= 0 && NUM_DIRECTIONAL_LIGHTS <= 0 && NUM_SPOT_LIGHTS <= 0

	resultingColor.xyz = ambientColor.xyz * ambientColor.w * eyePosition / eyePosition;

	#endif

	resultingColor.w = material.transperancy;

	fragColor = resultingColor;
}

void calculateVariables()
{
	// Calculate all variables
	ambientTransperancy = ambientLight.w;
	diffuseTransperancy = 1.0;
	specularTransperancy = 1.0;
	ambientColor = vec4(material.transmissionFilter * ambientLight.xyz * material.ambientColor,ambientTransperancy);
	viewDir = normalize(eyePosition-vertexPositionOut);
}

vec3 calculatePointLight(PointLight light,vec3 fragPos,vec3 normal)
{
	vec3 lightVector = light.position - fragPos;
	vec3 normalizedLightVector = normalize(lightVector);
	float distance = length(lightVector);
	float a = light.quadratic,b = light.linear,c = light.constant;

	// Diffuse Light
	float brightness = clamp(dot(normalizedLightVector,normal),0.0,1.0)/(a*distance*distance+b*distance+c);
	vec3 diffuseLight = vec3(brightness,brightness,brightness) * light.diffuse;

	// Specular Light
	vec3 reflectedLightVector = reflect(-normalizedLightVector,normal);
	float sBright = pow(clamp(dot(viewDir,reflectedLightVector),0.0,1.0),material.specularExponent)/(a*distance*distance+b*distance+c);
	vec3 specularLight = vec3(sBright,sBright,sBright) * light.specular;

	vec4 specularColor = vec4(material.transmissionFilter * specularLight * material.specularColor,specularTransperancy);
	vec4 diffuseColor = vec4(material.transmissionFilter * diffuseLight * material.diffuseColor,diffuseTransperancy);
	vec4 resultingColor;

	resultingColor = ambientColor * ambientTransperancy;
	resultingColor = diffuseColor * diffuseTransperancy + resultingColor;
	resultingColor = specularColor * specularTransperancy + resultingColor;

	return resultingColor.xyz;
}

vec3 calculateDirectionalLight(DirectionalLight light,vec3 normal)
{
	vec3 normalizedLightVector = normalize(-light.direction);

	// Diffuse Light
	float brightness = clamp(dot(normalizedLightVector,normal),0.0,1.0);
	vec3 diffuseLight = vec3(brightness,brightness,brightness) * light.diffuse;

	// Specular Light
	vec3 reflectedLightVector = reflect(-normalizedLightVector,normal);
	float sBright = pow(clamp(dot(viewDir,reflectedLightVector),0.0,1.0),material.specularExponent);
	vec3 specularLight = vec3(sBright,sBright,sBright) * light.specular;

	vec4 specularColor = vec4(material.transmissionFilter * specularLight * material.specularColor,specularTransperancy);
	vec4 diffuseColor = vec4(material.transmissionFilter * diffuseLight * material.diffuseColor,diffuseTransperancy);
	vec4 resultingColor;

	resultingColor = ambientColor * ambientTransperancy;
	resultingColor = diffuseColor * diffuseTransperancy + resultingColor;
	resultingColor = specularColor * specularTransperancy + resultingColor;

	return resultingColor.xyz;
}

vec3 calculateSpotLight(SpotLight light,vec3 fragPos,vec3 normal)
{
	vec3 lightVector = light.position - fragPos;
	vec3 normalizedLightVector = normalize(lightVector);
	float distance = length(lightVector);
	float a = light.quadratic,b = light.linear,c = light.constant;

	float theta = dot(normalizedLightVector,normalize(-light.direction));
	float epsilon = light.innerCutOff - light.outerCutOff;
	float intensity = clamp((theta - light.outerCutOff) / epsilon,0.0,1.0);

	// Diffuse Light
	float brightness = clamp(dot(normalizedLightVector,normal),0.0,1.0)/(a*distance*distance+b*distance+c);
	vec3 diffuseLight = vec3(brightness,brightness,brightness) * light.diffuse * intensity;

	// Specular Light
	vec3 reflectedLightVector = reflect(-normalizedLightVector,normal);
	float sBright = pow(clamp(dot(viewDir,reflectedLightVector),0.0,1.0),material.specularExponent)/(a*distance*distance+b*distance+c);
	vec3 specularLight = vec3(sBright,sBright,sBright) * light.specular * intensity;

	vec4 specularColor = vec4(material.transmissionFilter * specularLight * material.specularColor,specularTransperancy);
	vec4 diffuseColor = vec4(material.transmissionFilter * diffuseLight * material.diffuseColor,diffuseTransperancy);
	vec4 resultingColor;

	resultingColor = ambientColor * ambientTransperancy;
	resultingColor = diffuseColor * diffuseTransperancy + resultingColor;
	resultingColor = specularColor * specularTransperancy + resultingColor;

	return resultingColor.xyz;
}