#version 330 core
out vec4 FragColor;

in vec3 ourColor;
in vec2 texCoord;  // texture coordaniate

uniform sampler2D texture1; // texture sampler
uniform sampler2D texture2;

void main()
{
    // fragment can access to texture object
    // linearly interpolate between both textures (80% container, 20% awesomeface)
    FragColor = mix(texture(texture1, texCoord), texture(texture2, texCoord), 0.2);
}