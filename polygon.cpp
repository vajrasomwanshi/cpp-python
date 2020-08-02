#include <iostream> 
using namespace std; 

// Define Infinite (Using INT_MAX caused overflow problems) 
#define INF 10000 

struct Point 
{ 
	float x; 
	float y; 
}; 

bool onSegment(Point p, Point q, Point r) 
{ 
	if (q.x <= max(p.x, r.x) && q.x >= min(p.x, r.x) && 
			q.y <= max(p.y, r.y) && q.y >= min(p.y, r.y)) 
		return true; 
	return false; 
} 

int orientation(Point p, Point q, Point r) 
{ 
	float val = (q.y - p.y) * (r.x - q.x) - 
			(q.x - p.x) * (r.y - q.y); 

	if (val == 0) return 0; // colinear 
	return (val > 0)? 1: 2; // clock or counterclock wise 
} 

bool doIntersect(Point p1, Point q1, Point p2, Point q2) 
{ 
	// Find the four orientations needed for general and 
	// special cases 
	float o1 = orientation(p1, q1, p2); 
	float o2 = orientation(p1, q1, q2); 
	float o3 = orientation(p2, q2, p1); 
	float o4 = orientation(p2, q2, q1); 

	// General case 
	if (o1 != o2 && o3 != o4) 
		return true; 

	// Special Cases 
	// p1, q1 and p2 are colinear and p2 lies on segment p1q1 
	if (o1 == 0 && onSegment(p1, p2, q1)) return true; 

	// p1, q1 and p2 are colinear and q2 lies on segment p1q1 
	if (o2 == 0 && onSegment(p1, q2, q1)) return true; 

	// p2, q2 and p1 are colinear and p1 lies on segment p2q2 
	if (o3 == 0 && onSegment(p2, p1, q2)) return true; 

	// p2, q2 and q1 are colinear and q1 lies on segment p2q2 
	if (o4 == 0 && onSegment(p2, q1, q2)) return true; 

	return false; // Doesn't fall in any of the above cases 
} 

// Returns true if the point p lies inside the polygon[] with n vertices 
bool isInside(Point polygon[], int n, Point p) 
{ 
	// There must be at least 3 vertices in polygon[] 
	if (n < 3) return false; 

	// Create a point for line segment from p to infinite 
	Point extreme = {INF, p.y}; 

	// Count intersections of the above line with sides of polygon 
	int count = 0, i = 0; 
	do
	{ 
		int next = (i+1)%n; 
		if (doIntersect(polygon[i], polygon[next], p, extreme)) 
		{ 
			if (orientation(polygon[i], p, polygon[next]) == 0) 
			return onSegment(polygon[i], p, polygon[next]); 

			count++; 
		} 
		i = next; 
	} while (i != 0);  
	return count&1;  
} 
 
int main() 
{ 	
	//CASE 1:
	Point polygon1[] = {{1,0}, {8,3}, {8,8},{1,5}}; 
	int n = sizeof(polygon1)/sizeof(polygon1[0]); 
	Point p = {3,5}; 
	isInside(polygon1, n, p)? cout << "CASE 1: True \n": cout << "CASE 1: False \n";
	 
	//CASE 2:
	Point polygon2[] = {{-3,2}, {-2,-0.8}, {0,1.2}, {2.2,0},{2,4.5}}; 
	n = sizeof(polygon2)/sizeof(polygon2[0]); 
	p = {0,0}; 
	isInside(polygon1, n, p)? cout << "CASE 2: True \n": cout << "CASE 2: False \n"; 


	return 0; 
}

