// PathFinding.js翻译版 jps提取并翻译成c++
// by c_cpp 123
//来源PathFinding.js
#include <iostream>
#include <vector>
#include <cmath>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <queue>
#include <iomanip>
#include <string>
using namespace std;

typedef struct Location
{
	int x, y;
} Loc;

namespace std
{
	template <> struct hash <Location >
	{
		std::size_t operator() (const Location & a)const
		{
			return hash < int >() (a.x ^ (a.y << 4));
		}
	};
};
ostream& operator<<(ostream &os, const Location &a) {
	return os << "<" << a.x << "-" << a.y << ">";
}
bool operator ==(const Loc & a, const Loc & b)
{
	return a.x == b.x && a.y == b.y;
}

bool operator !=(const Loc & a, const Loc & b)
{
	return a.x != b.x || a.y != b.y;
}

bool operator <(const Loc & a, const Loc & b)
{
	return a.x < b.x && a.y < b.y;
}
Location NoneLoc = { -1, -1 };

double euclidean(const Location & a, const Location & b)
{
	double dx = abs(a.x - b.x);
	double dy = abs(a.y - b.y);
	return sqrt(dx * dx + dy * dy);
}

struct Grid
{
	int width, height;
	unordered_set < Location > walls;
	Grid(int w, int h, unordered_set < Location > walls_) :width(w), height(h), walls(walls_) {}

	int get_width()const {
		return width;
	}
	int get_height()const {
		return height;
	}
	int is_bounds(int x, int y) const
	{
		return (x >= 0 && x < width) && (y >= 0 && y < height);
	}
	int passable(int x, int y) const
	{
		return walls.find({ x,y }) == walls.end();
	}
	int isWalkableAt(int x, int y) const
	{
		return is_bounds(x, y) && passable(x, y);
	}
	int valid(const Location & a) const
	{
		return isWalkableAt(a.x, a.y);
	}
	vector < Location > getNeighbors(Location node) const;
	vector < Location > findNeighbors(const Location & node, const Location & parent) const;
};

vector<Location> reconstruct_path(
	const Location& start,
	const Location& goal,
	const unordered_map<Location, Location>& came_from)
{
	if (came_from.empty())
		return{};
	vector<Location> path{};
	Location current = goal;
	while (current != start) {
		path.push_back(current);
		if (came_from.count(current)) {
			current = came_from.at(current);
		}
		else {
			break;
		}
	}
	reverse(path.begin(), path.end());
	for (auto &i : path)
		cout << i << endl;
	return path;
}
void draw_grid(
	const Grid& grid,
	const unordered_map<Location, double>& distances,
	const unordered_map<Location, Location>& point_to,
	const vector<Location>& path,
	const unordered_map<Location, Location>& came_from,
	const Location& start,
	const Location& goal)
{
	const int field_width = 3;
	cout << string(field_width * grid.get_width(), '_') << '\n';
	for (int y = 0; y != grid.get_height(); ++y) {

		printf("%2d:", y);

		for (int x = 0; x != grid.get_width(); ++x) {
			const Location id{ x, y };
			if (grid.walls.find(id) != grid.walls.end()) {
				cout << "#";
			}
			else if (start != NoneLoc && id == start) {
				cout << "A";
			}
			else if (goal != NoneLoc && id == goal) {
				cout << "Z";
			}
			else if (!path.empty() && find(path.begin(), path.end(), id) != path.end()) {
				cout << "@";
			}
			else if (came_from.count(id)) {
				cout << "J";
			}
			else if (point_to.count(id)) {
				const auto next = point_to.at(id);
				if (next.x == x + 1) { cout << " > "; }
				else if (next.x == x - 1) { cout << " < "; }
				else if (next.y == y + 1) { cout << " v "; }
				else if (next.y == y - 1) { cout << " ^ "; }
				else { cout << "*"; }
			}
			else if (distances.count(id)) {
				cout << ' ' << left << setw(field_width - 1) << distances.at(id);
			}
			else {
				cout << ".";
			}
		}
		cout << '\n';
	}
	cout << string(field_width * grid.get_width(), '~') << '\n';
}
vector < Location > Grid::getNeighbors(Location node)
const
{
	int x = node.x, y = node.y;
	vector < Location > neighbors;
	int s0 = 0, d0 = 0, s1 = 0, d1 = 0, s2 = 0, d2 = 0, s3 = 0, d3 = 0;

	// ↑
	if (isWalkableAt(x, y - 1))
	{
		neighbors.push_back({ x, y - 1 });
		s0 = true;
	}
	// →
	if (isWalkableAt(x + 1, y))
	{
		neighbors.push_back({ x + 1, y });
		s1 = true;
	}
	// ↓
	if (isWalkableAt(x, y + 1))
	{
		neighbors.push_back({ x, y + 1 });
		s2 = true;
	}
	// ←
	if (isWalkableAt(x - 1, y))
	{
		neighbors.push_back({ x - 1, y });
		s3 = true;
	}


	d0 = s3 || s0;
	d1 = s0 || s1;
	d2 = s1 || s2;
	d3 = s2 || s3;


	// ↖
	if (d0 && isWalkableAt(x - 1, y - 1))
	{
		neighbors.push_back({ x - 1, y - 1 });
	}
	// ↗
	if (d1 && isWalkableAt(x + 1, y - 1))
	{
		neighbors.push_back({ x + 1, y - 1 });
	}
	// ↘
	if (d2 && isWalkableAt(x + 1, y + 1))
	{
		neighbors.push_back({ x + 1, y + 1 });
	}
	// ↙
	if (d3 && isWalkableAt(x - 1, y + 1))
	{
		neighbors.push_back({ x - 1, y + 1 });
	}

	return neighbors;
};


vector < Location > Grid::findNeighbors(const Location & node, const Location & parent)
const
{
	int x = node.x, y = node.y;

	int px, py,  dx, dy;
	vector < Location > neighbors;

	// directed pruning: can ignore most neighbors, unless forced.
	if (parent != NoneLoc)
	{
		px = parent.x;
		py = parent.y;
		// get the normalized direction of travel
		dx = (x - px) / max(abs(x - px), 1);
		dy = (y - py) / max(abs(y - py), 1);
		// cout<<dx<<" "<<dy<<endl;
		 // search diagonally
		if (dx != 0 && dy != 0)
		{
			if (isWalkableAt(x, y + dy))
			{
				neighbors.push_back({ x, y + dy });
			}
			if (isWalkableAt(x + dx, y))
			{
				neighbors.push_back({ x + dx, y });
			}
			/* 斜向两侧有一边能走,且斜前方要能通过 */
			if ((isWalkableAt(x, y + dy) || isWalkableAt(x + dx, y))&&isWalkableAt(x + dx, y + dy))
			{
				neighbors.push_back({ x + dx, y + dy });
			}
			if (!isWalkableAt(x - dx, y) && isWalkableAt(x, y + dy) && isWalkableAt(x - dx, y + dy))
			{
				neighbors.push_back({ x - dx, y + dy });
			}
			if (!isWalkableAt(x, y - dy) && isWalkableAt(x + dx, y) && isWalkableAt(x + dx, y - dy))
			{
				neighbors.push_back({ x + dx, y - dy });
			}
		}
		// search horizontally/vertically
		else
		{
			if (dx == 0)
			{
				if (isWalkableAt(x, y + dy))
				{
					neighbors.push_back({ x, y + dy });
					if (!isWalkableAt(x + 1, y) && isWalkableAt(x + 1, y + dy))
					{
						neighbors.push_back({ x + 1, y + dy });
					}
					if (!isWalkableAt(x - 1, y) && isWalkableAt(x - 1, y + dy))
					{
						neighbors.push_back({ x - 1, y + dy });
					}
				}
			}
			else
			{
				if (isWalkableAt(x + dx, y))
				{
					neighbors.push_back({ x + dx, y });
					if (!isWalkableAt(x, y + 1) && isWalkableAt(x + dx, y + 1))
					{
						neighbors.push_back({ x + dx, y + 1 });
					}
					if (!isWalkableAt(x, y - 1) && isWalkableAt(x + dx, y - 1))
					{
						neighbors.push_back({ x + dx, y - 1 });
					}
				}
			}
		}
	}
	// return all neighbors
	else
	{
		return getNeighbors(node);
	}

	return neighbors;
};

Location jump(const Grid & grid, Location  current, Location  parent,
	const Location & goal)
{
	int dx = current.x - parent.x, dy = current.y - parent.y;

	if (!grid.valid(current))
	{
		return NoneLoc;
	}

	if (current == goal)
	{
		return current;
	}

	// check for forced neighbors
	// along the diagonal
	if (dx != 0 && dy != 0)
	{
		if ((grid.isWalkableAt(current.x - dx, current.y + dy)
			&& !grid.isWalkableAt(current.x - dx, current.y))
			|| (grid.isWalkableAt(current.x + dx, current.y - dy)
				&& !grid.isWalkableAt(current.x, current.y - dy)))
		{
			return current;
		}
		// when moving diagonally, must check for vertical/horizontal jump
		// points
		if (jump(grid,
			{
			current.x + dx, current.y }
			, current, goal) != NoneLoc || jump(grid, { current.x, current.y + dy }, current, goal) != NoneLoc)
		{
			return current;
		}
	}
	// horizontally/vertically
	else
	{
		if (dx != 0)
		{						// moving along x
			if (grid.isWalkableAt(current.x + dx, current.y) && ((grid.isWalkableAt(current.x + dx, current.y + 1) && !grid.isWalkableAt(current.x, current.y + 1)) || (grid.isWalkableAt(current.x + dx, current.y - 1) && !grid.isWalkableAt(current.x, current.y - 1))))
			{
				return current;
			}
		}
		else
		{
			if (grid.isWalkableAt(current.x, current.y + dy) && ((grid.isWalkableAt(current.x + 1, current.y + dy) && !grid.isWalkableAt(current.x + 1, current.y)) || (grid.isWalkableAt(current.x - 1, current.y + dy) && !grid.isWalkableAt(current.x - 1, current.y))))
			{
				return current;
			}
		}
	}

	// moving diagonally, must make sure one of the vertical/horizontal
	// neighbors is open to allow the path
	if (grid.isWalkableAt(current.x + dx, current.y) || grid.isWalkableAt(current.x, current.y + dy))
	{
		return jump(grid, { current.x + dx, current.y + dy }, current, goal);
	}
	else
	{
		return NoneLoc;
	}
};



typedef pair < double, Location > PQElem;
typedef priority_queue < PQElem, vector < PQElem >, greater < PQElem >> PQLoc;
typedef double(*Heuristic_fn) (const Location &, const Location &);
unordered_map <Location, Location > jps(const Grid & grid, const Location & start, const Location & goal, Heuristic_fn euclidean)
{
	PQLoc openList;
	vector < Location > op_close_list;
	unordered_map < Location, Location > came_from;
	unordered_map < Location, double >cost_so_fa;

	openList.emplace(0, start);
	came_from[start] = start;
	cost_so_fa[start] = 0;
	Location parent = NoneLoc;


	// while the open list is not empty
	while (!openList.empty())
	{
		// pop the position of node which has the minimum `f` value.
		Location current = openList.top().second;
		op_close_list.push_back(current);

		if (current != start)
			parent = came_from[current];

		openList.pop();

		if (current == goal)
		{
			cout << "找到目标" << endl;
			return came_from;
		}

		vector < Location > neighbors = grid.findNeighbors(current, parent);
		for (int i = 0, l = neighbors.size(); i < l; ++i)
		{
			Location jumpPoint = jump(grid, neighbors[i], current, goal);
			if (jumpPoint != NoneLoc)
			{
				if (find(op_close_list.begin(), op_close_list.end(), jumpPoint) !=
					op_close_list.end())
				{
					continue;
				}
				double new_cost = cost_so_fa[current] + euclidean(current, jumpPoint);
				if (cost_so_fa.find(jumpPoint) == cost_so_fa.end() || new_cost < cost_so_fa[jumpPoint])
				{
					cout << "jumpPoint:" << jumpPoint << endl;
					cost_so_fa[jumpPoint] = new_cost;
					came_from[jumpPoint] = current;
					openList.emplace(new_cost + euclidean(jumpPoint, goal), jumpPoint);

				}
			}
		}
	}


	// fail to find the path
	return {};
}


int main()
{
	unordered_set<Location> walls{
		//		{0, 2},{2, 2}, {2, 1}, {2, 0},{2,5}};
			{12, 0},{11, 1},{10, 2},{9, 3},{8, 4},{7, 5},{6, 6},
			{5, 7},{4, 8},{3, 9},{2, 10},{1, 11},{1, 12},{1, 13},{2, 14},{2, 15},
			{5, 6},{0, 1},{1, 0},{2, 1},{3, 16} };
	Grid map{ 18, 18, walls };
	// Grid map{ 6, 6, walls };
	Location start{ 1, 1 };
	Location goal{ 17, 17 };
	//Location goal{ 4,2};
	auto came_from = jps(map, start, goal, euclidean);

	auto path = reconstruct_path(start, goal, came_from);

	draw_grid(map, {}, {}, path, came_from, start, goal);
}
