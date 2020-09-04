#pragma once

#define PI 3.14159f
#define PI2 PI * 2

#define FLOAT_EPSILON 0.001f	//�Ǽ��� ���� ���� ������ ��Ī�ϴ� �׸���� ���Ƿ�
#define FLOAT_EQUAL(f1, f2) (fabs(f1, f2) <= FLOAT_EPSILON)	//�� �Ǽ��� ������ �� ����
#define FLOAT_TO_INT(f1) static_cast<int>(f1 + FLOAT_EPSILON) //�Ǽ����� ����������

namespace TTYONE_UTIL
{
	float getDistance(float startX, float startY, float endX, float endY);

	float getAngle(float x1, float y1, float x2, float y2);
}