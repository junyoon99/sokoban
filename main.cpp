#include <iostream>

const char STAGE_DATA[] =
"\
########\n\
# .. p #\n\
# oo   #\n\
#      #\n\
########\n\
";

const int STAGE_WIDTH{ 8 };
const int STAGE_HEIGHT{ 5 };

enum Object
{
	obj_space,
	obj_wall,
	obj_goal,
	obj_block,
	obj_block_on_goal,
	obj_player,
	obj_player_on_goal,

	obj_max
};

void Initialize(Object *stage, int w, int h, const char* stageData);
void Draw(const Object *stage, int w, int h);
void Update(Object *satge, char input, int w, int h); 
bool IsClear(const Object *stage, int w, int h);


int main() 
{
	Object *stage = new Object[STAGE_WIDTH * STAGE_HEIGHT];

	Initialize(stage, STAGE_WIDTH, STAGE_HEIGHT, STAGE_DATA);

	while (true) 
	{
		Draw(stage, STAGE_WIDTH, STAGE_HEIGHT);

		if (IsClear(stage, STAGE_WIDTH, STAGE_HEIGHT)) 
		{
			std::cout << std::endl << "CLEAR!!" << std::endl;
			break;
		}

		char input{};
		std::cout << "(w,a,s,d) input : ";
		std::cin >> input;

		Update(stage, input, STAGE_WIDTH, STAGE_HEIGHT);
	}
}

void Initialize(Object *stage, int w, int h, const char *stageData)
{
	const char *p = stageData;

	Object o;

	switch (*p)
	{
		case ' ':
			o = obj_space;
			break;

		case '#':
			o = obj_space;
			break;

		case '.':
			o = obj_space;
			break;

		case 'o':
			o = obj_space;
			break;

		case 'O':
			o = obj_space;
			break;

		case 'p':
			o = obj_space;
			break;

		case 'P':
			o = obj_space;
			break;

		default:
			break;
	}
	++p;

	if (o != obj_max) 
	{
		stage[y + w + x] = o;
		x++;
	}
}

void Draw(const Object *stage, int w, int h)
{
	static const char font[]{' ','#','.','o','O','p','P'};

	for (int y = 0; y < h; y++) 
	{
		for (int x = 0l; x < w; x++) 
		{
			Object o = stage[y * w + x];
			std::cout << o;
		}
		std::cout << std::endl;
	}
}

void Update(Object *satge, char input, int w, int h)
{
	int dx{}, dy{};
	switch (input)
	{
		case 'w':
			dy -= 1;
			break;

		case 'a':
			dx -= 1;
			break;

		case 's':
			dy += 1;
			break;

		case 'd':
			dy += 1;
			break;

		default:
			break;
	}

	int i{};
	for (i = 0; i < w * h; i++) 
	{
		if (stage[i] == obj_player || stage[i] == obj_player_on_goal) 
		{
			break;
		}
	}
	int x = i % w;
	int y = i / w;

	int tx = x + dx;
	int ty = y + dy;


	//예외
	if (tx < 0 || ty < 0 || tx >= w || ty >= h) 
	{
		std::cout << "(1)Unexpected Position!" << std::endl;
		return;
	}

	//이동
	int p = y * w + x;
	int tp = ty * w + tx;

	if (stage[tp] == obj_space || stage[tp] == obj_goal) 
	{
		stage[tp] = (stage[tp] == obj_goal) ? obj_player_on_goal : obj_player;
		stage[p] = (stage[p] == obj_player_on_goal) ? obj_goal : obj_space;
	}
	else if (stage[tp] == obj_block || stage[tp] == obj_block_on_goal) 
	{
		int tx2 = tx + dx;
		int ty2 = ty + dy;
		if (tx2 < 0 || ty2 < 0 || tx2 >= w || ty2 >= h) 
		{
			std::cout << "(2)Unexpected Position!" << std::endl;
		}

		int tp2 = ty2 * w + tx2;
		if (stage[tp2] == obj_space || stage[tp2] == obj_goal) 
		{
			stage[p] = (stage[p] == obj_player_on_goal) ? obj_goal : obj_space;
			stage[tp] = (stage[tp] == obj_block_on_goal) ? obj_player_on_goal : obj_player;
			stage[tp2] = (stage[tp2] == obj_goal) ? obj_block_on_goal : obj_block;
		}

	}
}

bool IsClear(const Object *stage, int w, int h)
{
	for (int i = 0; i < w * h; i++) 
	{
		if (stage[i] == obj_block) return false;
	}
	return false;
}
