#version 330 core
out vec4 FragColor;

in vec3 crntPos;
in vec3 Normal;
in vec3 color;
in vec2 texCoord;


uniform sampler2D diffuse0;
uniform sampler2D specular0;

uniform vec4 lightColor;

uniform vec3 lightPos;
uniform vec3 camPos;

vec4 pointLight() 
{
	vec3 lightVec = lightPos - crntPos;
	float dist = length(lightVec);
	float a = 3.0;
	float b = 0.7;
	float inten = 1.0f / (a * dist * dist + b * dist + 1.0f);

	float ambient = 0.20f;

	vec3 normal = normalize(Normal);
	vec3 lightDirection = normalize(lightVec);

	float diffuse = max(dot(normal, lightDirection), 0.0f);

	float specularLight = 0.50f;
	vec3 viewDirection = normalize(camPos - crntPos);
	vec3 reflectionDirection = reflect(-lightDirection, normal);
	float specAmount = pow(max(dot(viewDirection, reflectionDirection), 0.0f), 16);
	float specular = specAmount * specularLight;

	return (texture(diffuse0, texCoord) * (diffuse * inten + ambient) + texture(specular0, texCoord).r * specular * inten) * lightColor;
}

vec4 directLight()
{
	float ambient = 0.20f;

	vec3 normal = normalize(Normal);
	vec3 lightDirection = normalize(vec3(1.0f, 1.0f, 0.0f));

	float diffuse = max(abs(dot(normal, lightDirection)), 0.0f);

	float specularLight = 0.50f;
	vec3 viewDirection = normalize(camPos - crntPos);
	vec3 reflectionDirection = reflect(-lightDirection, normal);
	float specAmount = pow(max(dot(viewDirection, reflectionDirection), 0.0f), 16);
	float specular = specAmount * specularLight;

	if(texture(diffuse0, texCoord).a < 0.1)
		discard;

	return (texture(diffuse0, texCoord) * (diffuse + ambient) + texture(specular0, texCoord).r * specular) * lightColor;
}

vec4 spotLight() 
{
	//angles of inner and outer cones
	float outerCone = 0.9f;
	float innerCone = 0.95f;
	
	//light's ambient value
	float ambient = 0.20f;

	//get's the normal and light direction
	vec3 normal = normalize(Normal);
	vec3 lightDirection = normalize(lightPos - crntPos);

	//get's diffuse
	float diffuse = max(dot(normal, lightDirection), 0.0f);

	//get's specualr
	float specularLight = 0.50f;
	vec3 viewDirection = normalize(camPos - crntPos);
	vec3 reflectionDirection = reflect(-lightDirection, normal);
	float specAmount = pow(max(dot(viewDirection, reflectionDirection), 0.0f), 16);
	float specular = specAmount * specularLight;

	//get's the intensity of the area between the innter and outer cones
	float angle = dot(vec3(0.0f, -1.0f, 0.0f), -lightDirection);
	float inten = clamp((angle - outerCone) / (innerCone - outerCone), 0.0f, 1.0f);

	//returns color
	return (texture(diffuse0, texCoord) * (diffuse * inten + ambient) + texture(specular0, texCoord).r * specular * inten) * lightColor;
}

float near = 0.1f;
float far = 100.0f;

float linearizeDepth(float depth) 
{
	return (2.0 * near * far) / (far + near - (depth * 2.0 - 1.0) * (far - near));
}

float logisticDepth(float depth, float steepness = 0.5f, float offset = 5.0f) 
{
	float zVal = linearizeDepth(depth);
	return (1 / (1 + exp(-steepness * (zVal - offset))));
}

//For a fog like affect put this in main:
//	float depth = logisticDepth(gl_FragCoord.z);
//  FragColor = directLight() * (0.6f - depth) + vec4(depth * vec3(0.85f, 0.85f, 0.90f), 1.0f);
// Make sure gl clear color = 0.85f, 0.85f, 0.9f, 1.0f

void main()
{
		FragColor = directLight();
}