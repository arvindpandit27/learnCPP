using namespace std;

typedef enum {
	RED = 0,
	BLUE = 1,
	GREEN = 2,
	YELLOW = 3
}Colour_t;

typedef enum {
	RED0 = 0,
	RED1 = 1,
	RED2 = 2,
	RED3 = 3
}RedColour_t;



class Player {
public:
	string name;
	string colourName;
	Colour_t colour;
	float coins[4];
};

