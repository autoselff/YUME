#version 460 core
in vec2 vTexCoord;
in vec3 vColor;

out vec4 FragColor;
uniform sampler2D uTexture;

void main() {
    vec4 texColor = texture(uTexture, vTexCoord);
    FragColor = texColor * vec4(vColor, 1.0);
}
