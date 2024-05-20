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