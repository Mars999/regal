
in vec4 position;
in vec4 color;

out vec4 colorVarying;

uniform float translate;

void main()
{
    gl_Position = position;
    gl_Position.y += sin(translate) / 2.0;
    gl_Position.z = 0.9;

    colorVarying = color;
}
