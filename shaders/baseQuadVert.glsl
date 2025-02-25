R"(
#version 430

const vec2 quad[4] = {
    vec2(0,0),
    vec2(1,0),
    vec2(1,1),
    vec2(0,1)
};

layout(location = 0) uniform uvec2 windowSize;

vec2 pixelToScreenSpace(vec2 pixelPos)
{
    return (pixelPos / windowSize * 2.f + vec2(-1))*vec2(1,-1);
}

layout(location = 0) in uvec2 quadSize;
layout(location = 1) in ivec2 quadPos;
layout(location = 2) in vec4 quadColor;
layout(location = 3) in uint depth;

out vec4 fragCol;

void main()
{
    vec2 vertPos = quad[gl_VertexID] * quadSize + quadPos;
    gl_Position = vec4(pixelToScreenSpace(vertPos), 0, 1);
    fragCol = quadColor;
}
)"