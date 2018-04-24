#include <bits/stdc++.h>
using namespace std;
#define MP make_pair
struct Point {
    long long x, y;
    Point (long long _x = 0, long long _y = 0) : x(_x), y(_y) {}
    bool operator < (const Point &p) const {
        return MP(x, y) < MP(p.x, p.y);
        // return atan2(y, x) < atan2(p.y, p.x);
    }
    Point operator + (const Point &p) const {
        return Point(x + p.x, y + p.y);
    }
    Point operator - (const Point &p) const {
        return Point(x - p.x, y - p.y);
    }
    Point operator * (const double &d) const {
        return Point(d * x, d * y);
    }
    long long operator * (const Point &p) const {
        return x * p.x + y * p.y;
    }
    long long operator % (const Point &p) const {
        return x * p.y - y * p.x;
    }
    friend long long abs2(const Point &p) {
        return p * p;
    }
    friend double abs(const Point &p) {
        return sqrt(abs2(p));
    }
};
vector<Point> ConvexHull(vector<Point> &p) {    // begin and end is same
    sort(p.begin(), p.end());
    vector<Point> ans; int m = 0;
    for (int i = 0 ; i < p.size() ; i++) {
        while (m >= 2 && (p[i] - ans[m - 2]) % (ans[m - 1] - ans[m - 2]) < 0) ans.pop_back(), m--;
        ans.push_back(p[i]), m++;
    }
    for (int i = p.size() - 2 ; i >= 0 ; i--) {
        while (m >= 2 && (p[i] - ans[m - 2]) % (ans[m - 1] - ans[m - 2]) < 0) ans.pop_back(), m--;
        ans.push_back(p[i]), m++;
    }
    return ans;
}
int main() {

}
