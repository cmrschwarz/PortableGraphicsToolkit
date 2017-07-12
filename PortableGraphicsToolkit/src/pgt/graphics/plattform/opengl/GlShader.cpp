#include "GlShader.h"
#include <GL/glew.h>
#include <vector>
#include <pgt/io/logger/logger.h>
namespace pgt {
    namespace plattform {
        GlShader::GlShader(IStreamReader& vss, IStreamReader& fss)
        {
            _shader_id = glCreateProgram();
            GLuint vertex_shader = load(GL_VERTEX_SHADER, vss);
            GLuint fragment_shader = load(GL_FRAGMENT_SHADER, fss);
            glAttachShader(_shader_id, vertex_shader);
            glAttachShader(_shader_id, fragment_shader);
            glLinkProgram(_shader_id);
            glValidateProgram(_shader_id);
            glDeleteShader(vertex_shader);
            glDeleteShader(fragment_shader);
            PGT_LOG_INFO("Successfully loaded Shader");
            enable();
        }

        GlShader::~GlShader()
        {
            glDeleteProgram(_shader_id);
        }

        GLuint GlShader::load(const int shaderType, IStreamReader& sr)
        {
            GLuint shader = glCreateShader(shaderType);
            char* tex_buff;
            size_t len = sr.readToEnd((void**)&tex_buff);  // TODO: fix
            std::string shader_src(tex_buff, len);
            delete tex_buff;
            const char* source_char_p = shader_src.c_str();
            glShaderSource(shader, 1, &source_char_p, NULL);
            glCompileShader(shader);
            GLint result;
            glGetShaderiv(shader, GL_COMPILE_STATUS, &result);
            if (result == GL_FALSE) {
                GLint length;
                glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);
                char* errorLog = new char[length];
                glGetShaderInfoLog(shader, length, NULL, &errorLog[0]);
                PGT_ASSERT(
                    result, "GLSL Compiler Error in %sShader: \n%s",
                    (shaderType == GL_VERTEX_SHADER) ? "Vertex" : "Fragment",
                    errorLog);
                delete[] errorLog;
                int err = glGetError();
                PGT_ASSERT(err == GL_NO_ERROR, "GL_ERROR: %i", err);
            }
            return shader;
        }
        void GlShader::enable() const
        {
            glUseProgram(_shader_id);
        }
        void GlShader::disable() const
        {
            glUseProgram(0);
        }
        int GlShader::getUniformLocation(const char* name)
        {
            return glGetUniformLocation(_shader_id, name);
        }
        void GlShader::setUniform1i(const char* name, int i)
        {
            glUniform1i(getUniformLocation(name), i);
        }
        void GlShader::setUniform1iv(const char* name, int* value, int count)
        {
            glUniform1iv(getUniformLocation(name), count, value);
        }
        void GlShader::setUniform1f(const char* name, float f)
        {
            glUniform1f(getUniformLocation(name), f);
        }
        void GlShader::setUniform1fv(const char* name, float* value, int count)
        {
            glUniform1fv(getUniformLocation(name), count, value);
        }
        void GlShader::setUniform2f(const char* name, const vec2& vector)
        {
            glUniform2f(getUniformLocation(name), vector.x, vector.y);
        }
        void GlShader::setUniform3f(const char* name, const vec3& vector)
        {
            glUniform3f(getUniformLocation(name), vector.x, vector.y, vector.z);
        }
        void GlShader::setUniform4f(const char* name, const vec4& vector)
        {
            glUniform4f(getUniformLocation(name), vector.x, vector.y, vector.z,
                        vector.w);
        }
        void GlShader::setUniformMat4(const char* name, const mat4& matrix)
        {
            glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE,
                               matrix.elements);
        }

        void GlShader::setUniformMat3(const char* name, const mat3& matrix)
        {
            glUniformMatrix3fv(getUniformLocation(name), 1, GL_FALSE,
                               matrix.elements);
        }
    }
}