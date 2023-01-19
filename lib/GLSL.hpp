#ifndef FOG_GLSLRUN
#define FOG_GLSLRUN

#include "../lib/IncludeAll.hpp"

class GLSL
{
    private:
        int _NumAttrib;
        GLuint _ProgShaderID;
        GLuint _VertShaderID;
        GLuint _FragShaderID;
        void _Compile(const std::string&, GLuint);

    public:
        GLSL();
        ~GLSL();

        void CompileShaders(const std::string&, const std::string&);
        void LinkShaders();
        void Bind();
        void Unbind();
        void AddAttribute(const std::string&);
        GLint GetUniformLocation(const std::string&);
};
#endif// FOG_GLSLRUN