# opengl/glfw

### language : C

## build / run
```
cmake -S. -B build
cmake --build build
cd build 
./main
```

## 기능

- 윈도우 중앙에 파란색 포인트로 윈도우 중앙 표시
- 윈도우 중심을 기준으로 중심은 유지하고 크기는 윈도우 크기에따라 동적으로 변하는 빨간 사각형 생성

    - 빨간 사각형 클릭시 " Rectangle Clicked! " 로그 출력  
    <br/>
- 윈도우 우측 하단에 윈도우크기의 1/12 만큼 마진을 가지고 가로 세로는 크기는 윈도우 크기의 1/6인 파란 사각형 생성

    - 파란 사각형 클릭시 " Blue Rectangle Clicked! " 로그 출력
    - 파란 사각형 위로 마우스 hover시 초록색으로 변경됨
    