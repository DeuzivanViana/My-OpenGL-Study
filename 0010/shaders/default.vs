#version 460 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;

uniform mat4 perspective;

out vec3 ourColor;

void main()
{
  gl_Position = perspective * vec4(aPos, 1.f);
  ourColor = aColor;
}