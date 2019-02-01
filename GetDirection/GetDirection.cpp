#include <iostream>
#include <math.h>
using namespace std;

// 2차원 좌표 Point 클래스
class MyPoint {
public:
	MyPoint() { x = 0; y = 0; }
	MyPoint(float x, float y) { this->x = x; this->y = y; }
	MyPoint(MyPoint& pt) { *this = pt; }

	MyPoint& operator=(const MyPoint& other)
	{
		x = other.x;
		y = other.y;
		return *this;
	}
	MyPoint& operator-(const MyPoint& other)
	{
		x = x - other.x;
		y = y - other.y;
		return *this;
	}

	MyPoint& normalize() // 단위벡터화
	{
		MyPoint* result = new MyPoint();
		result->x = x / sqrtf(pow(x, 2) + pow(y, 2));
		result->y = y / sqrtf(pow(x, 2) + pow(y, 2));

		return *result;
	}

	float x;
	float y;
};

//위치 및 방향을 가진 액터 클래스
class Actor
{
public:
	Actor(MyPoint pos, MyPoint fwd)
	{
		Position = pos;
		Forward = fwd;
	}
	MyPoint Position;
	MyPoint Forward;
};


float getAngle(MyPoint PlayerFwd, MyPoint PtoM_Vector_norm);
int WhereisMonster(Actor Player, Actor Monster);

void main()
{
	//몬스터, 플레이어 액터에 지정할 위치 및 방향 설정
	MyPoint MonsterPos(1.0f, 6.0f);
	MyPoint MonsterFwd(0, 0);
	MyPoint PlayerPos(4.0f, 4.0f);
	MyPoint PlayerFwd(0, -1.0f);

	//몬스터 및 플레이어 위치 시각적 표현용
	for (int y = 0; y < 10; y++)
	{
		for (int x = 0; x < 10; x++)
		{
			if (x == MonsterPos.x && y == MonsterPos.y)
				printf("●");
			else if (x == PlayerPos.x && y == PlayerPos.y)
				printf("★");
			else printf("□");
		}
		printf("\n");
	}

	//액터 생성 및 위치와 방향 적용
	Actor Monster(MonsterPos, MonsterFwd);
	Actor Player(PlayerPos, PlayerFwd);

	int direction = WhereisMonster(Player, Monster);

	switch (direction)
	{
		case 0:
			printf("몬스터는 북쪽에 존재합니다.\n");
			break;

		case 1:
			printf("몬스터는 북서쪽에 존재합니다.\n");
			break;

		case 2:
			printf("몬스터는 북동쪽에 존재합니다.\n");
			break;

		case 3:
			printf("몬스터는 서쪽에 존재합니다.\n");
			break;

		case 4:
			printf("몬스터는 동쪽에 존재합니다.\n");
			break;

		case 5:
			printf("몬스터는 남서쪽에 존재합니다.\n");
			break;

		case 6:
			printf("몬스터는 남동쪽에 존재합니다.\n");
			break;

		case 7:
			printf("몬스터는 남쪽에 존재합니다.\n");
			break;

		default:
			printf("Error\n");
			break;
	}
}

// 내적으로 각도 구하기 0 ~ 180도
float getAngle(MyPoint PlayerFwd, MyPoint PtoM_Vector_norm)
{
	float cos = PlayerFwd.x * PtoM_Vector_norm.x + PlayerFwd.y * PtoM_Vector_norm.y;
	float angle = acosf(cos) / 3.1415927 * 180;
	return angle;
}

// 플레이어 기준 몬스터 위치 감별
int WhereisMonster(Actor Player, Actor Monster)
{
	MyPoint PtoM_Vector = MyPoint(Monster.Position - Player.Position).normalize();

	float angle = getAngle(Player.Forward, PtoM_Vector);
	printf("angle : %f\n", angle);

	bool IsClockwise = ((Player.Forward.x * PtoM_Vector.y - Player.Forward.y * PtoM_Vector.x) > 0) ? true : false; // 2차원 벡터 외적으로 각도 방향 탐지

	if (angle < 22.5f)
		return 0; // 북
	if (angle >= 22.5f && angle <= 67.5f)
		if (!IsClockwise) return 1; // 북서
		else return 2; // 북동
	if (angle > 67.5f && angle < 112.5f)
		if (!IsClockwise) return 3; // 서
		else return 4; // 동
	if (angle >= 112.5f && angle <= 157.5f)
		if (!IsClockwise) return 5; // 남서
		else return 6; // 남동
	if (angle > 157.5f)
		return 7; // 남
	else
		return 8; // error
}

