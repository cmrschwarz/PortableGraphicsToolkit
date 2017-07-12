#pragma once
#include <string>
#include <pgt/maths\maths.h>
#include <pgt/utils/primitives.h>
#include <pgt/io/vfs/VirtualFileSystem.h>
namespace pgt {
    namespace plattform {
        // refactor all this to a shader hirarchy which stores uniform loactions
        class GlShader {
          private:
            GLuint _shader_id;

          private:
            static GLuint load(const int shaderType, IStreamReader& stream);

          public:
            GlShader(IStreamReader& vertex_shader,
                     IStreamReader& fragment_shader);
            GlShader(IStreamReader&& vertex_shader,
                     IStreamReader&& fragment_shader) : GlShader(vertex_shader, fragment_shader){}
            ~GlShader();
            void enable() const;
            void disable() const;
            void setUniform1i(const char* name, int i);
            void setUniform1iv(const char* name, int* value, int count);
            void setUniform1f(const char* name, float f);
            void setUniform1fv(const char* name, float* value, int count);
            void setUniform2f(const char* name, const vec2& vector);
            void setUniform3f(const char* name, const vec3& vector);
            void setUniform4f(const char* name, const vec4& vector);
            void setUniformMat4(const char* name, const mat4& matrix);
            void setUniformMat3(const char* name, const mat3& matrix);

          private:
            int getUniformLocation(const char* name);
        };
    }
}
