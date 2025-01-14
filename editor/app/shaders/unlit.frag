#version 330 core

layout (location = 0) out vec4 color;

uniform vec4 col;

in DATA {
	vec4 pos;
	vec2 uv;
	float tid;
	vec4 color;
} fs_in;

uniform sampler2D textures[32];

void main() {
	vec4 texColor = fs_in.color;
	color = texColor;
}
