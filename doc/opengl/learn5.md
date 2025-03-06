---
title: opengl barycentric coordinate
description: |-
    Barycentric Coordinate 내부 점 확인방법
date: 2025-03-05 16:41:51
preview: 이미지 주소
draft: false
tags:
    - math
categories:
    - 카테고리없음
---
# Barycentric Coordinate

> [!NOTE]
> Barycentric coordinate는 주로 삼각형 내부의 한 점을 표현하는 데 사용되는 좌표 체계입니다.

## Barycentric Coordinate의 정의

Barycentric coordinates는 주어진 삼각형의 세 꼭짓점에 대해 각각 가중치(비율)를 부여하는 방법입니다. 
이 가중치들은 점이 삼각형의 각 꼭짓점으로부터 얼마나 멀리 있는지, 즉 점의 상대적 위치를 나타냅니다.
$$ A, B, C = 삼각형\ 꼭지점 \ P = 삼각형\ 내부의\ 점 $$

각 점은 아래와 같이 세 가지 비율

## Barycentric Coordinates 계산

삼각형 \( ABC \)의 세 점 
A(x<sub>1</sub>, y<sub>1</sub>),
B(x<sub>2</sub>, y<sub>2</sub>),
C(x<sub>3</sub>, y<sub>3</sub>),
와 점 
P(x, y),가 있을 때, 점 P의 Barycentric coordinates 
λ<sub>1</sub>, λ<sub>2</sub>, λ<sub>3</sub>는 다음과 같이 구할 수 있습니다.

### 1. 면적을 이용한 계산

Barycentric coordinates는 삼각형의 면적 비율을 이용하여 계산할 수 있습니다. 각 가중치는 점 \( P \)와 삼각형의 각 변에 의해 형성된 작은 삼각형들의 면적을 기준으로 구합니다.

$$
\lambda_1 = \frac{ \text{Area of triangle } PBC }{ \text{Area of triangle } ABC }
$$
$$
\lambda_2 = \frac{ \text{Area of triangle } PCA }{ \text{Area of triangle } ABC }
$$
$$
\lambda_3 = \frac{ \text{Area of triangle } PAB }{ \text{Area of triangle } ABC }
$$

### 2. 행렬식을 이용한 계산

행렬식 방법을 사용하여 Barycentric coordinates를 구할 수 있습니다. 이 방법은 삼각형의 세 꼭짓점 \( A \), \( B \), \( C \)와 점 \( P \)에 대한 좌표를 사용하여 계산합니다.

$$
\lambda_1 = \frac{ \text{det} \left( \begin{vmatrix} x & y & 1 \\ x_2 & y_2 & 1 \\ x_3 & y_3 & 1 \end{vmatrix} \right) }{ \text{det} \left( \begin{vmatrix} x_1 & y_1 & 1 \\ x_2 & y_2 & 1 \\ x_3 & y_3 & 1 \end{vmatrix} \right) }
$$

$$
\lambda_2 = \frac{ \text{det} \left( \begin{vmatrix} x_1 & y_1 & 1 \\ x & y & 1 \\ x_3 & y_3 & 1 \end{vmatrix} \right) }{ \text{det} \left( \begin{vmatrix} x_1 & y_1 & 1 \\ x_2 & y_2 & 1 \\ x_3 & y_3 & 1 \end{vmatrix} \right) }
$$

$$
\lambda_3 = \frac{ \text{det} \left( \begin{vmatrix} x_1 & y_1 & 1 \\ x_2 & y_2 & 1 \\ x & y & 1 \end{vmatrix} \right) }{ \text{det} \left( \begin{vmatrix} x_1 & y_1 & 1 \\ x_2 & y_2 & 1 \\ x_3 & y_3 & 1 \end{vmatrix} \right) }
$$

여기서 **det**는 **행렬식**을 나타내며, 이를 통해 점 P 의 Barycentric coordinates λ<sub>1</sub>, λ<sub>2</sub>, λ<sub>3</sub>를 계산할 수 있습니다.

## 사전에 알아야할 것

### 선형 보간(Linear Interpolation)

두 점 사이의 임의의 점을 계산할 때, 각 점에 가중치를 부여해 위치를 찾습니다.

2차원의 어떠한 선 A와 B 사이의 점 P는 다음과 같이 표현됩니다:
$$
P = A + t * (B - A)
$$
$$
0 ≤ t ≤ 1
$$

t = 0이면 P = A
t = 1이면 P = B
0 < t < 1이면 P는 A와 B 사이의 어딘가

바리센트릭 좌표에서는 이 개념을 3차원(삼각형)으로 확장합니다:
$$
P = A + v * (B - A) + w * (C - A)
$$

수학적 근거:

선형 변환의 기본 원리
볼록 조합(Convex Combination) 이론
선형 대수학의 벡터 보간 개념

이 표현은 점 P가 삼각형 내부의 어느 위치에 있는지를 A, B, C 꼭짓점의 가중치로 나타냅니다.
특징:

- v + w ≤ 1
- 0 ≤ v, w ≤ 1

이 조건을 만족하면 P는 삼각형 내부에 있음

여기서 용어는 다음과 같아 
| 이름 | 점 | 설명 |
| --- | --- |--- |
| A | A 시작점 | 기준점 |
| v | B - A 사이의 점 | B - A 방향으로의 가중치 |
| w | C - A 사이의 점 | C - A 방향으로의 가중치 |


실제로 이 방정식은 "A로부터 얼마나 멀어졌는지"를 v와 w로 표현하는 것입니다.
예를 들어:

v = 0, w = 0 이면 P = A (원점)\
v = 1, w = 0 이면 P = B\
v = 0, w = 1 이면 P = C\
v + w ≤ 1 이면 P는 삼각형 내부 라는것을 알 수 있다

### 전개

$$
P = A + v(B - A) + w(C - A)
$$
$$
P = A + vB - vA + wC - wA
$$

연립 방정식으로 표연하면

$$
Px = Ax + v(Bx - Ax) + w(Cx - Ax)
$$
$$
Py = Ay + v(By - Ay) + w(Cy - Ay)
$$
으로 나타넬 수 있고



$$
P = (1-v-w)A + vB + wC
$$
이를 보면 

| 값 | 식 | 가중치 |
| --- | --- | --- |
| u | 1-v-w | A의 가중치 |
| v | v | B의 가중치 |
| w | w | C의 가중치 |

$$
P = uA + vB + wC
$$

으로 u, v, w를 나타넬 수 있다.


### 행열 변환

그럼 다음과 같은 식은

$$
Px = Ax + v(Bx - Ax) + w(Cx - Ax)
$$
$$
Py = Ay + v(By - Ay) + w(Cy - Ay)
$$

행열 식을 다음과 같이 쓸 수 있고

$$
\begin{bmatrix}
P_x - A_x \\
P_y - A_y
\end{bmatrix}
=
\begin{bmatrix}
B_x - A_x & C_x - A_x \\
B_y - A_y & C_y - A_y
\end{bmatrix}
\begin{bmatrix}
v \\
w
\end{bmatrix}
$$
상위 x y 를 백터로 치완하면 
$$
\begin{bmatrix}
P_x - A_x \\
P_y - A_y
\end{bmatrix}
= V_{pa}
\ 
\begin{bmatrix}
B_x - A_x \\
B_y - A_y
\end{bmatrix}
= V_{ba}
\ 
\begin{bmatrix}
C_x - A_x \\
C_y - A_y
\end{bmatrix}
= V_{ca}
$$
$$
V_{pa}
=
\begin{bmatrix}
V_{ba} & V_{ca} 
\end{bmatrix}
\begin{bmatrix}
v \\
w
\end{bmatrix}
$$
로 볼 수 있다.

### w, v 에 대하여 정리

$$
\begin{bmatrix}
P_x - A_x \\
P_y - A_y
\end{bmatrix}
=
\begin{bmatrix}
B_x - A_x & C_x - A_x \\
B_y - A_y & C_y - A_y
\end{bmatrix}
\begin{bmatrix}
v \\
w
\end{bmatrix}
$$
를 v,w 에 대하여 정리하면

$$

\begin{bmatrix}
v \\
w
\end{bmatrix}
=
\begin{bmatrix}
B_x - A_x & C_x - A_x \\
B_y - A_y & C_y - A_y
\end{bmatrix}
^{-1}
\begin{bmatrix}
P_x - A_x \\
P_y - A_y
\end{bmatrix}
$$
역행열은 다음 식을 따름으로
$$
A^{-1} = \frac{1}{ad - bc} \begin{bmatrix} d & -b \\ -c & a \end{bmatrix}
$$
을 적용하면 다음과 같이 되는것을 볼 수 있다.
$$
\begin{bmatrix}
B_x - A_x & C_x - A_x \\
B_y - A_y & C_y - A_y
\end{bmatrix}
^{-1}
=
\frac{1}{(B_x - A_x)(C_y - A_y) - (B_y - A_y)(C_x - A_x)}
\begin{bmatrix}
C_y - A_y & -(C_x - A_x) \\
-(B_y - A_y) & B_x - A_x
\end{bmatrix}
$$

이것을 대입하면

$$
\begin{bmatrix}
v \\
w
\end{bmatrix}
=
\frac{1}{(B_x - A_x)(C_y - A_y) - (B_y - A_y)(C_x - A_x)}
\begin{bmatrix}
C_y - A_y & -(C_x - A_x) \\
-(B_y - A_y) & B_x - A_x
\end{bmatrix}
\begin{bmatrix}
P_x - A_x \\
P_y - A_y
\end{bmatrix}
$$

이제 외적 (cross product)식으로 치완하면

> [!NOTE]
> 2D 크로스 제품은 다음과 같이 정의됩니다
> $$ \mathbf{v} \times \mathbf{w} = v_x w_y - v_y w_x $$



$$
\begin{bmatrix}
v \\
w
\end{bmatrix}
=
\frac{1}{\mathbf{v}_{BA} \times \mathbf{v}_{CA}}
\begin{bmatrix}
\mathbf{v}_{CA} \times \mathbf{v}_{AP} \\
\mathbf{v}_{BA} \times \mathbf{v}_{AP}
\end{bmatrix}
$$

이와같이 간단하게 식을 추출할 수 있으며

## 코드

```glsl
float Triangle(vec2 a, vec2 b, vec2 c, vec2 p)
{
    float border = clamp(Line(a, b, p, 0.01) + Line(b, c, p, 0.01) + Line(c, a, p, 0.01), 0.0, 1.0);
    
    vec2 v_pa = p - a;
    vec2 v_ba = b - a;
    vec2 v_ca = c - a;

    // 분모 계산
    float denom = crossProduct2D(v_ba,v_ca);

    // 행렬을 곱한 결과 (Barycentric 좌표 계산)
    float v = crossProduct2D(v_pa, v_ca) / denom;
    float w = crossProduct2D(v_ba, v_pa) / denom;
    float u = 1.0 - v - w;

    // 삼각형 내부 체크
    float inside = (u >= 0.0 && v >= 0.0 && w >= 0.0) ? 1.0 : 0.0;

    return inside;
}
```

다음과 같은 코드로 작성하여 구분할 수 있다

## 참고 자료

- [Wikipedia - Barycentric Coordinate System](https://en.wikipedia.org/wiki/Barycentric_coordinate_system)
- [Scratchapixel - Barycentric Coordinates](https://www.scratchapixel.com/lessons/3d-basic-rendering/ray-tracing-rendering-a-triangle/barycentric-coordinates.html)
