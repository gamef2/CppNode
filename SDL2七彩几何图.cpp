//如果不是c4就注销这句#define C4DROID
//#define C4DROID
#ifdef C4DROID
#include <SDL2/SDL.h>

#else
#include <SDL.h>

#endif // !C4DROID
#include <SDL_image.h>
#include<map>
#include<vector>
#include<string>
#include<iostream>
#include<cassert>

using namespace std;


SDL_Window* gWin = NULL;
SDL_Renderer* gRenderer = NULL;
/* 循环单链表 */
class List
{
	typedef struct Link
	{
		vector<int> data;
		struct Link *next;
		Link(vector<int> d = vector<int>(0, 0), struct Link *n = NULL) :data(d), next(n)
		{
		}
	} LINK, *PLINK;
public:
	List() :size(0), head(NULL)
	{
		head = new LINK;
		tail = temp = head;
		head->next = head;
	}
	~List()
	{
		PLINK tmp = head->next;
		while (tmp != head)
		{
			head->next = tmp->next;
			delete tmp;
			tmp = head->next;
		}
		delete head;
	}

	void Push(vector<int>& data)
	{
		PLINK link = new LINK(data);
		assert(NULL != link);
		link->next = tail->next;
		tail->next = link;
		tail = link;
		++size;
	}
	bool Empty()
	{
		return size == 0;
	}
	bool Pop(vector<int> &data)
	{
		if (Empty())
			return false;
		PLINK tmp = head->next;
		data = head->next->data;
		head->next = head->next->next;
		delete tmp;
		--size;
		return true;
	}
	int length()
	{
		int len = 0;
		PLINK p = head->next;
		while (p != head)
		{
			++len;
			p = p->next;
		}
		return len;
	}
	vector<int>& boopNext()
	{
		if (temp == head)
			temp = temp->next;
		ivec = temp->data;
		temp = temp->next;
		return ivec;
	}
private:
	int size;
	PLINK head, tail, temp;
	vector<int> ivec;
};


int main(int argc, char* argv[])
{
	SDL_Init(SDL_INIT_VIDEO);

	/* 获取屏幕大小 */
	SDL_DisplayMode DM;
	SDL_GetCurrentDisplayMode(0, &DM);
	const int Width = DM.w, Height = DM.h;

	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");


	gWin = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED, Width, Height, SDL_WINDOW_SHOWN);

	gRenderer = SDL_CreateRenderer(gWin, -1, SDL_RENDERER_ACCELERATED);

	// IMG_Init(IMG_INIT_PNG);

	SDL_SetRenderDrawColor(gRenderer, 255, 255, 255, 255);

	SDL_RenderClear(gRenderer);

	vector<vector<int>> vvi =
	{
		{255,0,0},
		{255,165,0},
		{255,255,0},
		{0,255,0},
		{0,127,255},
		{0,0,255},
		{139,0,255},
	};

	vector<int> vvi1;
	List list;
	int Width_x = Width / 2 / 7, Height_y = Height / 2 / 7;
	vector<SDL_Rect> vdr;

	for (int i = 0; i < 7; ++i)
	{
		list.Push(vvi[i]);
		vdr.push_back({ Width_x*i,Height_y*i,Width_x*(7 - i) * 2,Height_y*(7 - i) * 2 });
	}

	bool quit = false;
	SDL_Event e;
	while (!quit)
	{
		while (SDL_PollEvent(&e))
		{
			if (e.type == SDL_QUIT || e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE)
				quit = true;
		}

		for (int i = 0; i < 7; ++i)
		{
			vvi1.clear();
			vvi1 = list.boopNext();
			SDL_SetRenderDrawColor(gRenderer, vvi1[0], vvi1[1], vvi1[2], 255);
			SDL_RenderFillRect(gRenderer, &vdr[i]);
		}
		list.boopNext();
		SDL_RenderPresent(gRenderer);
		SDL_Delay(300);
	}
	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWin);

	SDL_Quit();

	return 0;
}
