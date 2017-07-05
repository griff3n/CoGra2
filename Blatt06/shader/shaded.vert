#version 150

in vec3 position;
in vec3 color;
in vec3 normal;

uniform mat4 mvp;
uniform mat3 nm;
uniform vec3 lightDirection;

out vec3 fragmentColor;

void main()
{
	vec3 n = normalize(nm * normal);
	float intensity = dot(n, lightDirection);

	fragmentColor = color * max(intensity, 0.1);
	gl_Position   = mvp * vec4(position,  1.0);
}