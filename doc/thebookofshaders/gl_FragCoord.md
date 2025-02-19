---
title: gl_FragCoor 란?
description: |-
    thebookofshaders
date: 2025-02-11 17:15:40
preview: 이미지 주소
draft: false
tags:
    - thebookofshaders
    - gl_FragCoor
    - opengl
categories:
    - 카테고리없음
---

FragCoor는 생성된 화면상의 픽셀 위치를 알려주는데 내생각엔 공간에 대한 좌표를 알려주는거 같다

```glsl
vec4 fragCoord = gl_FragCoord;
float x = fragCoord.x; // 픽셀의 x 좌표
float y = fragCoord.y; // 픽셀의 y 좌표
float z = fragCoord.z; // 픽셀의 깊이 값
float w = fragCoord.w; // 위상 비율
```

다음과 같은 식으로 4차원 배열로 되어있으며 실제 생성된 공간상의 위치를 알려준다