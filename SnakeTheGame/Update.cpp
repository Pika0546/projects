#include "GameHeader.h"
#include "SoundHeader.h"

#pragma region Map
Map::Map()
{
	Level = 1;
	FoodEaten = 0;
	Timeleft = 0s;
	MapWall = nullptr;
	Portal = nullptr;
}

void Map::CreateMap()
{
	Portalable = true;
	Outable = true;
	Portal = nullptr;
	switch (Level % 5)
	{
	case 1:
		MapWall = nullptr;
		return;
	case 2:
		MapWall = Level_2;
		drawLevel_2();
		return;
	case 3:
		MapWall = Level_3;
		drawLevel_3();
		return;
	case 4:
		MapWall = Level_4;
		drawLevel_4();
		return;
	case 0:
		countdown(Timeleft, true);
		MapWall = nullptr;
		return;
	}
}
void Map::reset()
{
	Level = 1;
	FoodEaten = 0;
	Timeleft = 0s;
	BaseLength[0] = 4;
	MapWall = nullptr;
	Portal = nullptr;
}
void Map::resetbyPasslevel()
{
	Portalable = true;
	Outable = true;
	FoodEaten = 0;
	(Level % 5 == 0) ? (Timeleft = 30s) : (Timeleft = 0s);
	inPortal = { 0,0 };
	MapWall = nullptr;
	clearPortal();
}
void Map::deleteMap()
{
	if (MapWall != nullptr) MapWall = nullptr;
	if (Portal != nullptr)
	{
		delete[] Portal;
		Portal = nullptr;
	}
}

void Map::createPortal(Snake snake)
{
	Portalable = false;
	//Mới

	if (inPortal.x == 0 && inPortal.y == 0)
	{
		if (Level % 5 == 0)
		{
			sound.playTimeOff();
		}
		if (getRandBool())
		{
			//Mới
			inPortal.y = getRandAmong(vector<int>{InteractOrigin_y, InteractOrigin_y + GameHeight});
			do {
				inPortal.x = getRandNumber(InteractOrigin_x + 1, InteractOrigin_x + GameWidth - 1);
			} while (inPortal.x == InteractOrigin_x + 7 || inPortal.x == InteractOrigin_x + GameWidth - 8 || isSnakeArea(snake));
			//Cũ
			//inPortal.y = getRandAmong(vector<int>{InteractOrigin_y, InteractOrigin_y + GameHeight});

		}
		else
		{
			inPortal.x = getRandAmong(vector<int>{InteractOrigin_x, InteractOrigin_x + GameWidth});
			do
			{
				inPortal.y = getRandNumber(InteractOrigin_y + 1, InteractOrigin_y + GameHeight - 1);
			} while (inPortal.y == InteractOrigin_y + 5 || inPortal.y == InteractOrigin_y + GameWidth - 6 || isSnakeArea(snake));
		}
	}

	switch (facing(inPortal))
	{
	case Direction::Down:
		Portal = new Coordinate[6];
		Portal[0] = { inPortal.x - 1, inPortal.y };
		Portal[1] = { inPortal.x + 1, inPortal.y };
		Portal[2] = { inPortal.x - 1, inPortal.y + 1 };
		Portal[3] = { inPortal.x + 1, inPortal.y + 1 };
		Portal[4] = { inPortal.x - 1, inPortal.y + 2 };
		Portal[5] = { inPortal.x + 1, inPortal.y + 2 };


		break;
	case Direction::Up:
		Portal = new Coordinate[6];
		Portal[0] = { inPortal.x - 1, inPortal.y };
		Portal[1] = { inPortal.x + 1, inPortal.y };
		Portal[2] = { inPortal.x - 1, inPortal.y - 1 };
		Portal[3] = { inPortal.x + 1, inPortal.y - 1 };
		Portal[4] = { inPortal.x - 1, inPortal.y - 2 };
		Portal[5] = { inPortal.x + 1, inPortal.y - 2 };
		break;
	case Direction::Right:
		Portal = new Coordinate[6];
		Portal[0] = { inPortal.x	, inPortal.y - 1 };
		Portal[1] = { inPortal.x	, inPortal.y + 1 };
		Portal[2] = { inPortal.x + 1, inPortal.y - 1 };
		Portal[3] = { inPortal.x + 1, inPortal.y + 1 };
		Portal[4] = { inPortal.x + 2, inPortal.y - 1 };
		Portal[5] = { inPortal.x + 2, inPortal.y + 1 };
		break;
	case Direction::Left:
		Portal = new Coordinate[6];
		Portal[0] = { inPortal.x	, inPortal.y - 1 };
		Portal[1] = { inPortal.x	, inPortal.y + 1 };
		Portal[2] = { inPortal.x - 1, inPortal.y - 1 };
		Portal[3] = { inPortal.x - 1, inPortal.y + 1 };
		Portal[4] = { inPortal.x - 2, inPortal.y - 1 };
		Portal[5] = { inPortal.x - 2, inPortal.y + 1 };
		break;
	}
	drawPortal();
}
void Map::clearPortal()
{
	if (Portal != nullptr) delete[] Portal;
	Portal = nullptr;
}

bool Map::isHitMap(Coordinate Where)
{
	if (isMapWall(Where)) return true;
	if (isPortal(Where)) return true;
	return false;
}

bool Map::isMapWall(Coordinate Where)
{
	if (MapWall == nullptr) return false;
	for (int i = 0; i < TotalWall[(Level - 1) % 5]; i++)
		if (Where == MapWall[i]) return true;
	return false;
}
bool Map::isPortal(Coordinate Where)
{
	if (Portal == nullptr) return false;
	for (int i = 0; i < 6; i++)
		if (Where == Portal[i]) return true;
	return false;
}
bool Map::isEnough()
{
	if (Level % 5 != 0)
	{
		if (Level % 5 != 1)
			if (FoodEaten == 8) return true;
			else return false;
		else if (FoodEaten == 4) return true;
		else return false;
	}
	else
	{
		if (Timeleft <= 0s) return true;
		else return false;
	}
}
bool Map::isOutOfPortal(Snake snake)
{
	snake.length;
	int x = BaseLength[(Level - 1) % 5];
	return (snake.length >= BaseLength[(Level - 1) % 5]);
}
bool Map::isSnakeArea(Snake activeSnake)
{
	Direction portalDirection = facing(inPortal);
	Coordinate* checkArea = new Coordinate[9];

	if (portalDirection == Down)
	{
		for (int i = 1; i <= 3; i++)
		{
			checkArea[i - 1].x = inPortal.x - 1;
			checkArea[i - 1].y = inPortal.y + i;

			checkArea[i + 2].x = inPortal.x;
			checkArea[i + 2].y = inPortal.y + i;

			checkArea[i + 5].x = inPortal.x + 1;
			checkArea[i + 5].y = inPortal.y + i;
		}
	}
	else if (portalDirection == Up)
	{
		for (int i = 1; i <= 3; i++)
		{
			checkArea[i - 1].x = inPortal.x - 1;
			checkArea[i - 1].y = inPortal.y - i;

			checkArea[i + 2].x = inPortal.x;
			checkArea[i + 2].y = inPortal.y - i;

			checkArea[i + 5].x = inPortal.x + 1;
			checkArea[i + 5].y = inPortal.y - i;
		}
	}
	else if (portalDirection == Right)
	{
		for (int i = 1; i <= 3; i++)
		{
			checkArea[i - 1].x = inPortal.x + 1;
			checkArea[i - 1].y = inPortal.y - 2 + i;

			checkArea[i + 2].x = inPortal.x + 2;
			checkArea[i + 2].y = inPortal.y - 2 + i;

			checkArea[i + 5].x = inPortal.x + 3;
			checkArea[i + 5].y = inPortal.y - 2 + i;
		}
	}
	else if (portalDirection == Left)
	{
		for (int i = 1; i <= 3; i++)
		{
			checkArea[i - 1].x = inPortal.x - 1;
			checkArea[i - 1].y = inPortal.y - 2 + i;

			checkArea[i + 2].x = inPortal.x - 2;
			checkArea[i + 2].y = inPortal.y - 2 + i;

			checkArea[i + 5].x = inPortal.x - 3;
			checkArea[i + 5].y = inPortal.y - 2 + i;
		}
	}

	for (int i = 0; i < 9; i++)
		for (int j = 0; j < activeSnake.length; j++)
		{
			if (activeSnake.snake[j] == checkArea[i] || activeSnake.tail == checkArea[i])
			{
				delete[] checkArea;
				checkArea = nullptr;
				return true;
			}
		}

	delete[] checkArea;
	checkArea = nullptr;
	return false;
}

int Map::getBaseLength()
{
	return BaseLength[(Level - 1) % 5];
}
#pragma endregion

#pragma region Snake

Snake::Snake()
{
	Speed = 120ms;
	length = 1;
	value = 0;
	snake = new Coordinate[length];
	snake->x = OutPortal_x;
	snake->y = OutPortal_y;
	tail.x = OutPortal_x;
	tail.y = OutPortal_y;
	Death = false;
	direction = Right;
}

void Snake::eat(int addvalue)
{
	value += addvalue;
	if (value == 0) return;
	length++;
	value--;
	Coordinate* longersnake = new Coordinate[length];
	for (int i = 0; i < length - 1; i++) longersnake[i + 1] = snake[i];
	longersnake[0] = snake[0];
	delete[] snake;
	snake = longersnake;
}
void Snake::move()
{
	switch (direction)
	{
	case Up:
		tail = snake[length - 1];
		// Ăn & chỉ sửa đầu
		if (length > 1 && snake[0].x == snake[1].x && snake[0].y == snake[1].y)
		{
			snake[0].y--;
			return;
		}
		// Không ăn và sửa body
		for (int i = length - 1; i >= 1; i--)
			snake[i] = snake[i - 1];
		snake[0] = snake[1];
		snake[0].y--;
		break;
	case Down:
		tail = snake[length - 1];
		// Ăn & chỉ sửa đầu
		if (length > 1 && snake[0].x == snake[1].x && snake[0].y == snake[1].y)
		{
			snake[0].y++;
			return;
		}
		// Không ăn và sửa body
		for (int i = length - 1; i >= 1; i--)
			snake[i] = snake[i - 1];
		snake[0] = snake[1];
		snake[0].y++;
		break;
	case Left:
		tail = snake[length - 1];
		// Ăn & chỉ sửa đầu
		if (length > 1 && snake[0].x == snake[1].x && snake[0].y == snake[1].y)
		{
			snake[0].x--;
			return;
		}
		// Không ăn và sửa body
		for (int i = length - 1; i >= 1; i--)
			snake[i] = snake[i - 1];
		snake[0] = snake[1];
		snake[0].x--;
		break;
	case Right:
		tail = snake[length - 1];
		// Ăn & chỉ sửa đầu
		if (length > 1 && snake[0].x == snake[1].x && snake[0].y == snake[1].y)
		{
			snake[0].x++;
			return;
		}
		// Không ăn và sửa body
		for (int i = length - 1; i >= 1; i--)
			snake[i] = snake[i - 1];
		snake[0] = snake[1];
		snake[0].x++;
		break;
	}
}
void Snake::changeDirection(Direction nextdirection)
{
	switch (nextdirection)
	{
	case Up:
		if (direction == Down || direction == Up) return;
		direction = nextdirection;
		break;
	case Down:
		if (direction == Up || direction == Down) return;
		direction = nextdirection;
		break;
	case Left:
		if (direction == Right || direction == Left) return;
		direction = nextdirection;
		break;
	case Right:
		if (direction == Left || direction == Right) return;
		direction = nextdirection;
		break;
	}
}
void Snake::setBegin(Map map)
{
	if (value != 0) return;

	value = (map.BaseLength[(map.Level - 1) % 5] - length < 0) ? 0 : map.BaseLength[(map.Level - 1) % 5] - length;
	if (length < map.getBaseLength())
		sound.playStart();
}

bool Snake::isDeath(Object object, Map map)
{
	if (!isGrass(snake[0], object, map))
	{
		Death = true;
		deathAnimation(WhereisHit(object));
		return true;
	}
	return false;
}

bool Snake::isSnake(Coordinate Where)
{
	if (snake == nullptr) return false;
	for (int i = 0; i < length; i++)
		if (Where == snake[i]) return true;
	return false;
}
bool Snake::isSnakeBody(Coordinate Where)
{
	if (snake == nullptr) return false;
	for (int i = (value == 0) ? 1 : 2; i < length; i++)
		if (Where == snake[i]) return true;
	return false;
}
bool Snake::isGrass(Coordinate Where, Object object, Map map)
{
	if (isSnakeBody(Where))
	{

		return false;
	}
	if (!object.eatable && (object.isObject(snake[0]) || object.isObject(snake, length)))
	{

		return false;
	}
	if (isWall(Where))
	{

		return false;
	}
	if (map.isHitMap(Where)) {

		return 0;
	}
	return true;
}

Coordinate Snake::WhereisHit(Object object)
{
	for (int i = 0; i < object.total; i++)
	{
		for (int j = 0; j < length; j++)
		{
			if (object.object[i] == snake[j]) return object.object[i];
		}
	}
	return snake[0];
}

bool Snake::isInPortal(Map map)
{
	if (*snake == map.inPortal) return true;
	else return false;
}

void Snake::resetbyPasslevel()
{
	length = 1;
	delete[] snake;
	snake = new Coordinate[length];
	snake[0] = { OutPortal_x, OutPortal_y };
	tail = { OutPortal_x, OutPortal_y };

	direction = Direction::Right;

	if (Speed > 50ms) Speed = milliseconds(int(floor((Speed * 80 / 100).count())));
	else if (Speed > 30ms) Speed = milliseconds(int(floor((Speed * 90 / 100).count())));
	else if (Speed > 25ms) Speed--;
	if (Speed <= 25ms) Speed = 25ms;
}

void Snake::reset()
{
	if (snake == nullptr) return;
	delete[] snake;
	length = 0;
	value = 0;
	snake = nullptr;
	tail = { OutPortal_x, OutPortal_y };

	Speed = 120ms;
	Death = false;
	direction = Right;
}
void Snake::deleteSnake()
{
	if (snake == nullptr) return;
	delete[] snake;
	snake = nullptr;
}
#pragma endregion

#pragma region Food
Food::Food()
{
	total = 1;
	food = new Coordinate[total];
	food[0].x = 0;
	food[0].y = 0;
}

void Food::firstGenerate(Snake snake, Object object, Map map)
{
	Coordinate Where;
	if (map.Level % 5 != 0)
	{
		if (food == nullptr) return;
		else
		{
			if (food[0].x == 0 && food[0].y == 0)
			{
				do
				{
					Where.x = getRandNumber(InteractOrigin_x + 1, InteractOrigin_x + GameWidth - 1);
					Where.y = getRandNumber(InteractOrigin_y + 1, InteractOrigin_y + GameHeight - 1);
				} while (!isGround(Where, snake, object, map) || isFood(Where));
				food[0] = Where;
			}
		}
	}
	else
	{
		if (total == 1)
		{
			if (food == nullptr)
			{
				food = new Coordinate[10];
				total = 10;
			}
			else if (food != nullptr)
			{
				delete food;
				food = new Coordinate[10];
				total = 10;
			}
			for (int i = 0; i < 10; i++) food[i] = { -1,-1 };

			for (int i = 0; i < 10; i++)
			{
				do
				{
					Where.x = getRandNumber(InteractOrigin_x + 1, InteractOrigin_x + GameWidth - 1);
					Where.y = getRandNumber(InteractOrigin_y + 1, InteractOrigin_y + GameHeight - 1);
				} while (!isGround(Where, snake, object, map) || isFood(Where));
				food[i] = Where;
			}
		}
	}

	draw();
}

void Food::Generate(Snake snake, Object object, Map map, int num)
{
	Coordinate Where;
	do
	{
		Where.x = getRandNumber(InteractOrigin_x + 1, InteractOrigin_x + GameWidth - 1);
		Where.y = getRandNumber(InteractOrigin_y + 1, InteractOrigin_y + GameHeight - 1);
	} while (!isSpawnFood(Where, snake, object, map) || isFood(Where));
	food[num] = Where;
	draw(num);
}

void Food::timeGenerate(Snake snake, Object object, Map map)
{
	total++;
	Coordinate* food2 = new Coordinate[total];
	for (int i = 0; i < total; i++)
		food2[i] = food[i];
	do
	{
		food2[total - 1].x = getRandNumber(InteractOrigin_x + 1, InteractOrigin_x + GameWidth - 1);
		food2[total - 1].y = getRandNumber(InteractOrigin_y + 1, InteractOrigin_y + GameHeight - 1);
	} while (!isGround(food2[total - 1], snake, object, map) || isFood(food2[total - 1]));
	delete[] food;
	food = food2;
	draw(total - 1);
}

void Food::eaten(Snake snake, Object object, Map map, Coordinate Where)
{
	if (map.isEnough())
	{
		if (total == 1) delete food;
		else			delete[] food;
		total = 0;
		food = nullptr;
		return;
	}
	if (Where.x == -1) Generate(snake, object, map);
	for (int i = 0; i < total; i++)
	{
		if (Where == food[i])
		{
			Generate(snake, object, map, i);
		}
	}
}

bool Food::isFood(Coordinate Where)
{
	if (food == nullptr) return false;
	for (int i = 0; i < total; i++)
		if (Where == food[i]) return true;
	return false;
}

void Food::reset()
{
	if (food == nullptr) return;
	delete[] food;
	total = 0;
	food = nullptr;
}
void Food::resetbyPasslevel()
{
	total = 1;
	if (food == nullptr)
	{
		food = new Coordinate[total];
		food[0].x = 0;
		food[0].y = 0;
	}
}

void Food::deleteFood()
{
	if (food == nullptr) return;
	delete[] food;
	food = nullptr;
}

#pragma endregion

#pragma region Object
Object::Object()
{
	object = nullptr;
	Current = nullptr;
	eatable = false;
	total = 0;
}
Object::Object(Coordinate* CurrentPos, int total, bool eatable)
{
	this->eatable = eatable;
	this->total = total;
	this->object = new Coordinate[total];
	if (!eatable) this->Current = new int[total];
	for (int i = 0; i < this->total; i++)
	{
		this->object[i] = CurrentPos[i];
		if (!eatable)
		{
			this->Current[i] = locate(CurrentPos[i]);
		}
	}
}

void Object::setflag()
{
	if (flag.empty())
		for (int i = 0; i < total; i++)
		{
			flag.push_back(i % 2 == 0);
		}
	else flag.flip();
}
void Object::deleteflag()
{
	if (flag.empty()) return;
	flag.erase(flag.begin(), flag.end());
}

void Object::reGenerate(Snake snake, Food food, Map map, Coordinate Pos)
{
	Coordinate Where;
	do
	{
		Where.x = getRandNumber(InteractOrigin_x + 1, InteractOrigin_x + GameWidth - 1);
		Where.y = getRandNumber(InteractOrigin_y + 1, InteractOrigin_y + GameHeight - 1);
	} while (!isGround(Where, snake, food, map) || isObject(Where));

	if (Pos == Coordinate({ -1,-1 }))
	{
		object[0] = Where;
		return;
	}
	for (int i = 0; i < total; i++)
	{
		if (Pos == object[i])
		{
			object[i] = Where;
			return;
		}
	}

}
void Object::addTimeFood(Snake snake, Food food, Map map)
{
	total++;
	Coordinate* ObjectTimeFood = new Coordinate[total];
	for (int i = 0; i < total - 2; i++)
	{
		ObjectTimeFood[i + 1] = object[i];
	}
	ObjectTimeFood[0] = { -1,-1 };
	delete[] object;
	object = ObjectTimeFood;
	reGenerate(snake, food, map);
}

void Object::move(Snake snake, Food food, Map map)
{
	if (map.Level % 5 != 4 && map.Level % 5 != 0) return;
	if (!eatable)
	{
		if (!waitObject(snake.Speed * 3 / 2)) return;
		drawDelete();
		for (int i = 0; i < total; i++)
		{
			(Current[i] + 1 >= 132) ? Current[i] = 0 : Current[i]++;
			object[i] = Orbit_4[Current[i]];
		}
		draw();
	}
	else
	{
		if (!waitObject(snake.Speed * 4)) return;
		auto QuarDrant		= [](Snake snake, Coordinate Where) ->int
		{
			if (snake.snake[0].x == Where.x && snake.snake[0].y == Where.y)
				return 0;
			if (snake.snake[0].x == Where.x)
				if (snake.snake[0].y > Where.y)
					return 2;
				else return 6;
			if (snake.snake[0].y == Where.y)
				if (snake.snake[0].x > Where.x)
					return 4;
				else return 8;

			if (snake.snake[0].x <= InteractOrigin_x + floor(GameWidth / 6) && snake.snake[0].y <= InteractOrigin_y + floor(GameHeight / 6) && Where.x <= InteractOrigin_x + floor(GameWidth / 6) && Where.y <= InteractOrigin_y + floor(GameHeight / 6))
				return 10;
			if (snake.snake[0].x <= InteractOrigin_x + floor(GameWidth / 6) && snake.snake[0].y >= InteractOrigin_y + floor(GameHeight * 5 / 6) && Where.x <= InteractOrigin_x + floor(GameWidth / 6) && Where.y <= InteractOrigin_y + floor(GameHeight * 5 / 6))
				return 11;
			if (snake.snake[0].x >= InteractOrigin_x + floor(GameWidth * 5 / 6) && snake.snake[0].y <= InteractOrigin_y + floor(GameHeight / 6) && Where.x <= InteractOrigin_x + floor(GameWidth * 5 / 6) && Where.y <= InteractOrigin_y + floor(GameHeight / 6))
				return 9;
			if (snake.snake[0].x >= InteractOrigin_x + floor(GameWidth * 5 / 6) && snake.snake[0].y >= InteractOrigin_y + floor(GameHeight * 5 / 6) && Where.x >= InteractOrigin_x + floor(GameWidth * 5 / 6) && Where.y <= InteractOrigin_y + floor(GameHeight * 5 / 6))
				return 10;
			if (snake.snake[0].x <= InteractOrigin_x + floor(GameWidth / 6) && Where.x < snake.snake[0].x)
			{
				if (Where.y > snake.snake[0].y)
					return 7;
				if (Where.y < snake.snake[0].y)
					return 1;
			}
			if (snake.snake[0].x >= InteractOrigin_x + floor(GameWidth * 5 / 6) && Where.x > snake.snake[0].x)
			{
				if (Where.y > snake.snake[0].y)
					return 3;
				if (Where.y < snake.snake[0].y)
					return 5;
			}
			if (snake.snake[0].y <= InteractOrigin_y + floor(GameHeight / 6) && Where.y < snake.snake[0].y)
			{
				if (Where.x < snake.snake[0].x)
					return 5;
				if (Where.x > snake.snake[0].x)
					return 7;
			}
			if (snake.snake[0].y >= InteractOrigin_y + floor(GameHeight * 5 / 6) && Where.y > snake.snake[0].y)
			{
				if (Where.x < snake.snake[0].x)
					return 3;
				if (Where.x > snake.snake[0].x)
					return 1;
			}
			if (Where.x == snake.snake[0].x)
			{
				if (Where.y > snake.snake[0].y)
					return 6;
				else
					return 2;
			}
			else if (Where.x < snake.snake[0].x)
			{
				if (Where.y > snake.snake[0].y)
					return 5;
				else
					return 3;
			}
			else
			{
				if (Where.y > snake.snake[0].y)
					return 7;
				else
					return 1;
			}
		};
		auto toDirection	= [](int quarDrant, Snake snake) -> vector<Direction>
		{
			switch (quarDrant)
			{
			case 0: return vector<Direction>(Direction::All);
			case 1:
				if (snake.direction == Direction::Up || snake.direction == Direction::Right)
					return vector<Direction>({ Direction::Up, Direction::Right });
				else return vector<Direction>(Direction::All);
			case 2:
				if (snake.direction == Direction::Up) return vector<Direction>({ Direction::Up   , Direction::Left, Direction::Right });
				else if (snake.direction == Direction::Right) return vector<Direction>({ Direction::Left , Direction::Up });
				else if (snake.direction == Direction::Left) return vector<Direction>({ Direction::Right, Direction::Up });
				else return vector<Direction>(Direction::All);
			case 3:
				if (snake.direction == Direction::Up || snake.direction == Direction::Left)
					return vector<Direction>({ Direction::Up, Direction::Left });
				else return vector<Direction>(Direction::All);
			case 4:
				if (snake.direction == Direction::Left) return vector<Direction>({ Direction::Left, Direction::Up, Direction::Down });
				else if (snake.direction == Direction::Up) return vector<Direction>({ Direction::Down, Direction::Left });
				else if (snake.direction == Direction::Down) return vector<Direction>({ Direction::Up  , Direction::Left });
				else return vector<Direction>(Direction::All);
			case 5:
				if (snake.direction == Direction::Down || snake.direction == Direction::Left)
					return vector<Direction>({ Direction::Down, Direction::Left });
				else return vector<Direction>(Direction::All);
			case 6:
				if (snake.direction == Direction::Down) return vector<Direction>({ Direction::Down , Direction::Left, Direction::Right });
				else if (snake.direction == Direction::Right) return vector<Direction>({ Direction::Left , Direction::Down });
				else if (snake.direction == Direction::Left) return vector<Direction>({ Direction::Right, Direction::Down });
				else return vector<Direction>(Direction::All);
			case 7:
				if (snake.direction == Direction::Down || snake.direction == Direction::Right)
					return vector<Direction>({ Direction::Down, Direction::Right });
				else return vector<Direction>(Direction::All);
			case 8:
				if (snake.direction == Direction::Right) return vector<Direction>({ Direction::Right, Direction::Up, Direction::Down });
				else if (snake.direction == Direction::Up) return vector<Direction>({ Direction::Down , Direction::Right });
				else if (snake.direction == Direction::Left) return vector<Direction>({ Direction::Up   , Direction::Right });
				else return vector<Direction>(Direction::All);
			case 9:
				if (snake.direction == Direction::Up || snake.direction == Direction::Right)
					return vector<Direction>({ Direction::Down, Direction::Left });
				else return vector<Direction>(Direction::All);
			case 10:
				if (snake.direction == Direction::Up || snake.direction == Direction::Left)
					return vector<Direction>({ Direction::Down, Direction::Right });
				else return vector<Direction>(Direction::All);
			case 11:
				if (snake.direction == Direction::Down || snake.direction == Direction::Left)
					return vector<Direction>({ Direction::Up, Direction::Right });
				else return vector<Direction>(Direction::All);
			case 12:
				if (snake.direction == Direction::Down || snake.direction == Direction::Right)
					return vector<Direction>({ Direction::Up, Direction::Left });
				else return vector<Direction>(Direction::All);
			}
		};
		auto Moveable		= [](Coordinate Where, Direction& GoTo, Snake snake, Food food, Map map, Object object) -> bool
		{
		RandStart:
			switch (GoTo)
			{
			case Direction::Up:
				Where.y--;
				if (isMoveableGround(Where, snake, food, object, map)) return true;
				else return false;
			case Direction::Down:
				Where.y++;
				if (isMoveableGround(Where, snake, food, object, map)) return true;
				else return false;
			case Direction::Left:
				Where.x--;
				if (isMoveableGround(Where, snake, food, object, map)) return true;
				else return false;
			case Direction::Right:
				Where.x++;
				if (isMoveableGround(Where, snake, food, object, map)) return true;
				else return false;
			case Direction::All:
				GoTo = getRandAmong<Direction>({ Direction::Up , Direction::Down , Direction::Left , Direction::Right });
				goto RandStart;
			}
		};
		auto Moveto			= [](Coordinate& Where, Direction GoTo) -> void
		{
			switch (GoTo)
			{
			case Up: Where.y--; return;
			case Down: Where.y++; return;
			case Left: Where.x--; return;
			case Right: Where.x++; return;
			case All: return;
			}
		};
		auto NextCoordinate = [](Coordinate Where, Direction GoTo)->Coordinate
		{
			switch (GoTo)
			{
			case Direction::Up: Where.y--; return Where;
			case Direction::Down: Where.y++; return Where;
			case Direction::Left: Where.x--; return Where;
			case Direction::Right: Where.x++; return Where;
			}
		};

		drawDelete();
		for (int i = 0; i < total; i++)
		{
			Coordinate Where = object[i];
			Object CopyObject(object, total, true);
			vector<Direction> GoTo = toDirection(QuarDrant(snake, object[i]), snake);
			vector<int> MaxGo;
			Direction resultDirection = Direction::All;

			// Sort ngắn nhất và di chuyển được
			int max = 0;
			for (int j = 0; j < GoTo.size(); j++)
			{
				if (!Moveable(object[i], GoTo[j], snake, food, map, CopyObject))
				{
					GoTo.erase(GoTo.begin() + j);
					j--;
				}
				else
				{
					int distance = Distance(NextCoordinate(object[i], GoTo[j]), snake.snake[0]);
					MaxGo.push_back(distance);
					if (max < distance) max = distance;
				}
			}
			for (int j = 0; j < GoTo.size(); j++)
			{
				if (MaxGo[j] < max)
				{
					GoTo.erase(GoTo.begin() + j);
					j--;
				}
			}
			if (GoTo.size() != 0) resultDirection = getRandAmong(GoTo);
			Moveto(object[i], resultDirection);
		}
		draw();
	}
}

int Object::locate(Coordinate Where)
{
	for (int i = 0; i < 132; i++)
	{
		if (Where == Orbit_4[i]) return i;
	}
	return -1;
}

bool Object::isObject(Coordinate Where)
{
	for (int i = 0; i < total; i++)
	{
		if (object[i] == Where) return true;
		if (!eatable)
		{
			if (Orbit_4[(Current[i] - 1 < 0) ? 131 : Current[i] - 1] == Where) return true;
			if (Orbit_4[(Current[i] - 2 < 0) ? Current[i] - 2 + 132 : Current[i] - 2] == Where) return true;
		}
	}
	return false;
}
bool Object::isObject(Snake snake)
{
	if (object == nullptr) return false;
	for (int i = 0; i < total; i++)
	{
		if (eatable && snake.snake[0] == object[i]) return true;
		else
			for (int i = 0; i < snake.length; i++)
			{
				if (snake.snake[i] == object[i]) return true;
			}
	}
	return false;
}
bool Object::isObject(Coordinate* snakebody, int length)
{
	if (object == nullptr) return false;
	for (int i = 0; i < total; i++)
	{
		for (int j = 0; j < length; j++)
		{
			if (snakebody[j] == object[i]) return true;
		}
	}
	return false;
}
bool Object::isOrbit(Coordinate Where)
{
	for (int i = 0; i < 132; i++)
		if (Where == Orbit_4[i]) return true;
	return false;
}

bool Object::isTimeFood(Coordinate Where)
{
	if (!eatable) return false;
	for (int i = 0; i < total; i++)
	{
		if (object[i] == Where) return true;
	}
	return false;
}

bool Object::waitObject(milliseconds time)
{
	static steady_clock::time_point a = steady_clock::now();
	static steady_clock::time_point b = steady_clock::now();

	static bool reset = false;
	if (reset) a = steady_clock::now();
	b = steady_clock::now();
	if (duration_cast<milliseconds>(b - a) >= time) { reset = true; return true; }
	else { reset = false; return false; }
}

void Object::beginWithLevel(Snake snake, Food food, Map map)
{
	if (map.Level % 5 != 4 && map.Level % 5 != 0) return;
	else
	{
		if (map.Level % 5 == 4) // Màn 4
		{
			if (object == nullptr)
			{
				total = 2;
				object = new Coordinate[total];
				Current = new int[total];
				object[0] = { 31 , 10 }; Current[0] = 0;
				object[1] = { 87 , 20 }; Current[1] = 66;
			}
			else
			{
				for (int i = 0; i < 132; i++)
				{
					if (object[0] == Orbit_4[i])
					{
						Current = new int[total];
						Current[0] = i;
						Current[1] = (i + 66 >= 132) ? (i + 66 - 132) : (i + 66);
						break;
					}
				}
			}
			eatable = false;
		}
		else if (map.Level % 5 == 0) // Màn 5
		{
			if (object == nullptr)
			{
				total = 10;
				object = new Coordinate[total];
				for (int i = 0; i < total; i++)
				{
					do
					{
						object[i].x = getRandNumber(InteractOrigin_x + 1, InteractOrigin_x + GameWidth - 1);
						object[i].y = getRandNumber(InteractOrigin_y + 1, InteractOrigin_y + GameHeight - 1);
					} while (!isGround(object[0], snake, food, map));
				}
			}
			eatable = true;
		}
	}
}

void Object::reset()
{
	if (object != nullptr)
	{
		delete[] object;
		object = nullptr;
	}
	total = 0;
	if (Current != nullptr)
	{
		delete[] Current;
		Current = nullptr;
	}
	eatable = false;
	deleteflag();
}

void Object::deleteObject()
{
	if (object != nullptr)
	{
		delete[] object;
		object = nullptr;
	}

	if (Current != nullptr)
	{
		delete[] Current;
		Current = nullptr;
	}
	deleteflag();
}
#pragma endregion

#pragma region Screen
Screen Option(Screen& input, char MainKey)
{
	int Pos = ScrtoI(input);
	switch (MainKey)
	{
	case UP_:
		if (Pos > 1)
		{
			Pos--;
			drawSelectedOption(Pos);
		}
		input = ItoScr(Pos);
		return ItoScr(Pos);
	case DOWN_:
		if (Pos < 5)
		{
			Pos++;
			drawSelectedOption(Pos);
		}
		input = ItoScr(Pos);
		return ItoScr(Pos);
	default:
		return ItoScr(Pos);
	}
}
#pragma endregion