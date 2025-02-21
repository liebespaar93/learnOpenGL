// Line.hpp
#ifndef LINE_HPP
#define LINE_HPP

#include <OpenGL/gl3.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <vector>

class Line {
public:
    Line(glm::vec2 start, glm::vec2 end, float segments );
    ~Line();

    // 복사 생성자와 대입 연산자 삭제 (OpenGL 리소스의 안전한 관리를 위해)
    Line(const Line&) = delete;
    Line& operator=(const Line&) = delete;

    bool create();  // 생성 성공/실패 반환
    void render() const;  // const 멤버 함수로 변경
    
    // 선의 속성을 변경하는 메서드들 추가
    void setPointSize(float size);

    // 버텍스 데이터 접근자
    const std::vector<GLfloat>& getVertices() const { return vertices; }

private:
    void deleteLine();
    void updateVertexBuffer();  // 버텍스 데이터 업데이트

    GLuint lineVAO;
    GLuint lineVBO;
    float pointSize;
    std::vector<GLfloat> vertices;
    float segments;

    
    // 기본 색상 값
    struct {
        float r, g, b, a;
    } color;
};

#endif