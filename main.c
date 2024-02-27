#include <GLFW/glfw3.h>
#include <stdio.h>
float rect_x, rect_y;
float rect_width, rect_height, blue_rect_y, blue_rect_x, blue_y, blue_x;

// 윈도우의 너비와 높이
int window_width = 800;
int window_height = 600;
// 사각형의 좌표와 크기
int is_hovering = 0; // 파란색 사각형 위에 마우스가 있는지 여부

// 클릭한 좌표가 사각형 내부에 있는지 확인하는 함수
int isInsideRect(float x, float y)
{
    if (x >= rect_x - rect_width / 2 && x <= rect_x + rect_width / 2 && y >= rect_y - rect_height / 2 && y <= rect_y + rect_height / 2)
    {
        return 1;
    }
    else if (x >= blue_rect_x && x <= blue_rect_x + blue_x && y >= blue_rect_y && y <= blue_rect_y + blue_y)
    {
        return 2;
    }
    return 0;
}

// 마우스 클릭 이벤트 콜백 함수
// 마우스 클릭 이벤트 콜백 함수
void mouse_button_callback(GLFWwindow *window, int button, int action, int mods)
{
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
    {
        int width, height;
        glfwGetFramebufferSize(window, &width, &height);
        double xpos, ypos;
        glfwGetCursorPos(window, &xpos, &ypos);

        printf("clicked pos x: %f, y: %f\n", xpos, ypos);
        // 윈도우 내의 좌표를 OpenGL 좌표로 변환
        ypos = height - ypos; // 윈도우 크기에 맞게 좌표 변환
        if (isInsideRect((float)xpos, (float)ypos) == 1)
        {
            printf("Rectangle Clicked!\n");
        }
        else if (isInsideRect((float)xpos, (float)ypos) == 2)
        {
            printf("Blue Rectangle Clicked!\n");
        }
    }
}
// void framebuffer_size_callback(GLFWwindow *window, int width, int height)
// {

// }
void cursor_pos_callback(GLFWwindow *window, double xpos, double ypos)
{
    // 윈도우 내의 좌표를 OpenGL 좌표로 변환
    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    ypos = height - ypos; // 윈도우 크기에 맞게 좌표 변환

    if (isInsideRect((float)xpos, (float)ypos) == 2)
    {
        is_hovering = 1;
    }
    else
    {
        is_hovering = 0;
    }
    printf("mouse pos x: %f, y: %f \n", xpos, ypos);
}

void init()
{
    int width, height;
    GLFWwindow *window = glfwGetCurrentContext();

    // 윈도우의 너비와 높이 가져오기
    glfwGetFramebufferSize(window, &width, &height);

    // 투영 행렬 설정
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, width, 0, height, 0, 1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    // 뷰포트를 윈도우 크기로 업데이트
    glViewport(0, 0, width, height);    // 뷰포트를 윈도우 크기로 업데이트
    glMatrixMode(GL_PROJECTION);        // 투영 행렬 모드로 전환
    glLoadIdentity();                   // 행렬 초기화
    glOrtho(0, width, 0, height, 0, 1); // 새로운 투영 행렬 설정
    glMatrixMode(GL_MODELVIEW);         // 모델-뷰 행렬 모드로 전환

    // 윈도우의 너비와 높이 업데이트
    printf("window x: %d ,  y: %d\n", width, height);
    // 사각형의 위치 업데이트
    rect_x = width / 2.0f;
    rect_y = height / 2.0f;

    // 사각형의 너비와 높이 업데이트 (윈도우의 너비와 높이의 1/3)
    rect_width = width / 3.0f;
    rect_height = height / 3.0f;

    blue_rect_x = width / 12.0;
    blue_rect_y = height / 12.0;

    blue_x = width / 6.0;
    blue_y = height / 6.0;
}

int main()
{
    GLFWwindow *window;

    // GLFW 초기화
    if (!glfwInit())
    {
        return -1;
    }

    // 윈도우 생성
    window = glfwCreateWindow(window_width, window_height, "Clickable Rectangle", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }
    // 컨텍스트를 현재 스레드로 설정
    glfwMakeContextCurrent(window);
    init();

    // 마우스 커서 이동 콜백 함수 등록
    glfwSetCursorPosCallback(window, cursor_pos_callback);

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    glfwSetMouseButtonCallback(window, mouse_button_callback);

    framebuffer_size_callback(window, window_width, window_height);
    // 렌더링 루프
    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);

        // 사각형 그리기
        glBegin(GL_QUADS);
        glColor3f(1.0f, 0.0f, 0.0f); // 빨간색
        glVertex2f(rect_x - rect_width / 2, rect_y - rect_height / 2);
        glVertex2f(rect_x + rect_width / 2, rect_y - rect_height / 2);
        glVertex2f(rect_x + rect_width / 2, rect_y + rect_height / 2);
        glVertex2f(rect_x - rect_width / 2, rect_y + rect_height / 2);
        glEnd();

        // 중심에 점 그리기
        glPointSize(10.0f); // 점의 크기 설정
        glBegin(GL_POINTS);
        glColor3f(0.0f, 0.0f, 1.0f); // 파란색
        glVertex2f(rect_x, rect_y);
        glEnd();

        if (is_hovering)
        {
            glColor3f(0.0f, 1.0f, 0.0f); // 초록색
        }
        else
        {
            glColor3f(0.0f, 0.0f, 1.0f); // 파란색
        }
        glBegin(GL_QUADS);
        glVertex2f(blue_rect_x, blue_rect_y);
        glVertex2f(blue_rect_x + blue_x, blue_rect_y);
        glVertex2f(blue_rect_x + blue_x, blue_rect_y + blue_y);
        glVertex2f(blue_rect_x, blue_rect_y + blue_y);
        glEnd();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
