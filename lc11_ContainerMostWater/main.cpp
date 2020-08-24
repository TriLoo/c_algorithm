/**
 * \brief lc11 container with most water
 * 
 *  level Medium.
 *  Given n point cordinates (i, n_i).
 *  find two lines which together with x-axis forms a container, such that the container contain the most water.
 * 
 *  Main Thought
 *  (1) This is a search-based maximum problem which include two axis: x - distance, y - height
 *  (2) so we can: first maximum the distance, then search the height
 *  (3) this is also the greedy algorithm
 * 
 * \file main.cpp
 * \date 2020.08.24
 */

#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    /// solution 1: bruce solution, O(n^2)
    /// solution 2: from the furthest distance -> close, update the small height, O(n)
    int maxArea(vector<int>& height) {
        int left = 0, right = height.size() - 1;
        if (right == 1)
            return std::min(height[0], height[1]);
        
        int area = 0;
        while(left < right)
        {
            int h = std::min(height[left], height[right]);
            // calculate the area
            int curr_area = h * (right - left);
            if (curr_area > area)
                area = curr_area;
            // update the position
            if (height[left] < height[right])
                ++left;
            else
                --right;
        }

        return area;
    }
};

int main()
{
    vector<int> heights = {1,8,6,2,5,4,8,3,7};

    Solution sl;
    int res = sl.maxArea(heights);
    cout << "Max container: " << res << endl;

    return 0;
}
