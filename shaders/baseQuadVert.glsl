R"(
#version 430

const vec2 quad[4] = {
    vec2(0,0),
    vec2(1,0),
    vec2(1,1),
    vec2(0,1)
};
void main()
{
    gl_Position = vec4(quad[gl_VertexID], 0, 1);
}
)"