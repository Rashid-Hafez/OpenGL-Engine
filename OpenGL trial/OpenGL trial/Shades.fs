#version 410 core
#define NUM_LIGHTS 4

out vec4 frag; //send the output back to the program.

in vec2 texCoord0;
in vec4 normal0; //normal should be vec 4
in vec4 FragPos; //Catching the fragment from the Vertex shader, now we can calculate this fragment's position. VEC3 OR VEC4?

uniform sampler2D myTexture; //sampler to map texture to obj

uniform vec4 lightPos; //the position of the light source is defined in the main program, we can get it here because it is a global var.
uniform vec4 lightPosD; //the position of the light source is defined in the main program, we can get it here because it is a global var.

uniform vec4 viewPos; //camera
//
//uniform vec4 ia;        // Ambient colour
//uniform float ka;        // Ambient constant (strength)
//uniform float kd;        // Diffuse constant
//uniform vec4 id;        //diffuse colour
//uniform vec4 is;        // specular colour
//uniform float ks;        // specular constant
//uniform float shininess;// shininess constant

//uniform vec4 strD; //strength vector for material diffuse
//uniform vec4 strS; //Strength vector for material specular

//When multiplying these strength vectors, use ".XYZ" to only get 3 points, because we cant calculate vec4*vec3//
struct Material {
    
    vec3 ia; //ambient RGB for MATERIAL
    vec3 id; //diffuse RGB for MATERIAL
    vec3 is; // specular RGB for MATERIAL
    
    float shininess;
    
    sampler2D diffuseMap; //later
    sampler2D specularMap; //later
    sampler2D reflectMap;   //LAAAATER
};

struct DirLight{
    vec4 lightPos; //Direction

    float ka; // aimbient LIGHT intensity..
    float kd; //diffuse intensity
    float ks;//specular intensity
};

struct PointLight{

    vec4 position;
    vec3 colour; //the colour of PLight in RGB.
    
    float constant;
    float linear;
    float quadratic;
        
    vec3 ia;
    vec3 id;
    vec3 is;
};

uniform Material material;
uniform DirLight sun;
uniform PointLight pLight;

vec3 TheSun(DirLight light);
vec3 Lamp(PointLight plight, vec4 FragPos);

void main(){
    
    vec3 sun = TheSun(sun);
    vec3 point = Lamp(pLight, FragPos);
    
    
    frag = vec4(sun+point,1.0)*texture(myTexture,texCoord0);
}

//calculate the colour of this fragment using the sun's colour for a piece of the calculation.
vec3 TheSun(DirLight sun){
    
    vec3 ambient = sun.ka * material.ia.rgb; //diffuse colour * ambient colour * ambient constant
    
    //diffuse, we only care about light direction.
    vec4 lightDir = normalize(-sun.lightPos); //normalize returns a vector with the same direction as its parameter, v, but with length 1.
    float diff = max(dot(normalize(normal0), lightDir), 0.0);
    vec3 diffuse = diff * material.id.rgb *sun.kd; //diff * diffuse colour * strength
    // Specular
    vec4 viewDir = normalize(viewPos - FragPos); //vector with direction towards object. ViewPos is the camera matrix transposed
    vec4 reflectDir = reflect(-lightDir, normalize(normal0)); //vector directed towards eyes.
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess); //calculate dot product of both
    vec3 specV = sun.ks* material.is.rgb *spec;
    
    vec3 sunFragment = (ambient + diffuse + specV);
    
    return sunFragment;
}

vec3 Lamp(PointLight plight, vec4 fragPos){
    
    vec4 viewDir = normalize(viewPos - fragPos);
    
    vec4 lightDir = normalize(plight.position - fragPos); //plight.position is not -plight because we calculate from the object to the light
    // diffuse shading
    float diff = max(dot(normalize(normal0), lightDir), 0.0);
    // specular shading
    vec4 reflectDir = reflect(-lightDir, normalize(normal0));
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    // attenuation
    float distance = length(plight.position - fragPos);
    float attenuation = 1.0 / (plight.constant + plight.linear * distance + plight.quadratic * (distance * distance));
    // combine results
    vec3 ambient = plight.ia.rgb * material.ia.rgb;
    vec3 diffuse = plight.id.rgb * diff * material.id.rgb;
    vec3 specular = plight.is.rgb * spec * material.is.rgb;
    ambient *= attenuation;
    diffuse *= attenuation;
    specular *= attenuation;
    
    vec3 lamp = (ambient + diffuse + specular);
    return lamp;
}

//ambient   +      d i f f u s e        +   s p e c u l a r        *    t e x t u r e
//frag = vec4(ka * ia.rgb + kd * id.rgb * diffuse.rgb + ks * is.rgb * spec, 1.0) * texture(myTexture,texCoord0); //professor's code


/*
 Directional light is calculated by taking the inverse of the LIGHTPOS, therefore we can do calculations of how the light travels FROM
 the source TO the object, instead of calculating FROM the object TO the Light source.
 
 calcDirLight(){
 vec3 ambient = light.ka * material.ia.rgb;
 vec4 lightDir = normalize(-light.lightPos); //normalize returns a vector with the same direction as its parameter, v, but with length 1.
 float diff = max(dot(normalize(normal0), lightDir), 0.0);
 vec3 diffuse = diff * material.id.rgb *strD.xyz; //diff * diffuse colour * strength
}
 */
