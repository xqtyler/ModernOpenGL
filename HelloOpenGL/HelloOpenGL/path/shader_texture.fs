#version 330 core
out vec4 FragColor;

in vec3 ourColor;
in vec2 texCoord;  // texture coordaniate

uniform sampler2D ourTexture; // texture sampler

void main()
{
    // fragment can access to texture object
    FragColor = texture(ourTexture, texCoord) * vec4(ourColor, 1.0);
}