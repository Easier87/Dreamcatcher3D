#version 410 core
struct DirectLight{
  vec3 direction;

  vec3 ambient;
  vec3 diffuse;
  vec3 specular;
};

struct PointLight{
  vec3 position;

  float constant;
  float linear;
  float quadratic;

  vec3 ambient;
  vec3 diffuse;
  vec3 specular;
};

struct SpotLight{
  vec3 position;
  vec3 direction;
  float cutOff;
  float outerCutOff;

  float constant;
  float linear;
  float quadratic;

  vec3 ambient;
  vec3 diffuse;
  vec3 specular;
};

vec3 funcDirectLight(DirectLight light, vec3 normal, vec3 viewDir);
vec3 funcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir);
vec3 funcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir);

out vec4 FragColor;

in vec3 Normal;
in vec3 FragPos;
in vec2 TexCoords;

uniform vec3 viewPos;
uniform float shininess;
uniform sampler2D texture_diffuse1;
uniform sampler2D texture_specular1;

uniform DirectLight directLight;
uniform PointLight pointLight;
uniform SpotLight spotLight;



void main(){
  vec3 norm = normalize(Normal);
  vec3 viewDir = normalize(viewPos - FragPos);
  vec3 result = vec3(0.0);

  result += funcDirectLight(directLight, norm, viewDir);
  // result += funcPointLight(pointLight, norm, FragPos, viewDir);
  // result += funcSpotLight(spotLight, norm, FragPos, viewDir);

  FragColor = vec4(result, 1.0);
}




// Direct Light Function
vec3 funcDirectLight(DirectLight light, vec3 normal, vec3 viewDir)
{
  vec3 lightDir = normalize(-light.direction);
  float diff = max(dot(normal, lightDir), 0.0);

  vec3 reflectDir = reflect(-lightDir, normal);
  float spec = pow(max(dot(viewDir, reflectDir), 0.0), shininess);

  vec3 ambient = light.ambient * vec3(texture(texture_diffuse1, TexCoords));
  vec3 diffuse = light.diffuse * diff * vec3(texture(texture_diffuse1, TexCoords));
  vec3 specular = light.specular * spec * texture(texture_specular1, TexCoords).rgb;

  // return (ambient + diffuse + specular);
  return (ambient + diffuse);
}

// Point Light Function
vec3 funcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
  vec3 lightDir = normalize(light.position - fragPos);

  float diff = max(dot(normal, lightDir), 0.0);
  vec3 reflectDir = reflect(-lightDir, normal);
  float spec = pow(max(dot(viewDir, reflectDir), 0.0), shininess);
  float distance = length(light.position - fragPos);
  float attenuation = 1.0 / (light.constant + light.linear * distance +light.quadratic * pow(distance, 2.0));

  vec3 ambient = light.ambient * vec3(texture(texture_diffuse1, TexCoords));
  vec3 diffuse = light.diffuse * diff * vec3(texture(texture_diffuse1, TexCoords));
  vec3 specular = light.specular * spec * vec3(texture(texture_specular1, TexCoords));

  ambient *= attenuation;
  diffuse *= attenuation;
  specular *= attenuation;
  
  return (ambient + diffuse + specular);
}

// SpotLight Function
vec3 funcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
  vec3 lightDir = normalize(light.position - fragPos);
  vec3 color = texture(texture_diffuse1, TexCoords).rgb;

  float diff = max(dot(normal, lightDir), 0.0);
  vec3 reflectDir = reflect(-lightDir, normal);

  float spec = pow(max(dot(viewDir, reflectDir), 0.0), shininess);
  float distance = length(light.position - fragPos);
  float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * pow(distance, 2.0));

  float theta = dot(lightDir, normalize(-light.direction));
  float epsilon = light.cutOff - light.outerCutOff;
  float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);
 
  vec3 ambient = light.ambient * color;
  vec3 diffuse = light.diffuse * diff * color;
  vec3 specular = light.specular * spec * color;

  ambient *= attenuation * intensity;
  diffuse *= attenuation * intensity;
  specular *= attenuation * intensity;

  return(ambient + diffuse + specular);
}
