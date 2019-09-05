#version 330 core
out vec4 FragColor;


   uniform sampler2D texture_diffuse1; //only diffuse map, the ambient usually has the same color as the diffuse 
   uniform sampler2D texture_specular1;    
   uniform float shininess;

struct Light {
    vec3 position;
    vec3 diffuse; //the color of the light
};

in vec3 FragPos;  
in vec3 Normal;  
in vec2 TexCoords;
  
uniform vec3 viewPos;
uniform Light light;

void main()
{
    // ambient
    vec3 ambient = texture(texture_diffuse1, TexCoords).rgb;
  	
    // diffuse 
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(light.position - FragPos);
    float diff = max(dot(norm, lightDir), 0.0); //cos to light direction
    vec3 diffuse = light.diffuse * diff * texture(texture_diffuse1, TexCoords).rgb;
    
    // specular
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);  
	//cos to the power of shininess of angle between light reflected ray and view direction
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), shininess); 
    vec3 specular = spec * texture(texture_specular1, TexCoords).rgb;  
        
    vec3 result = ambient + diffuse + specular;
    FragColor = vec4(result, 1.0);
} 


