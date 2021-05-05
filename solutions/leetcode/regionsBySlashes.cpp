// regionsBySlashes.cpp
// leetcode
//
// Created by  Song Ding on 6/1/19.
// Copyright © 2019 Song Ding. All rights reserved.
//
#include "common.h"
using namespace std;

namespace regionsBySlashes {
/*
// TODO: copy problem statement here
 959. Regions Cut By Slashes
 Medium
 
 266
 
 57
 
 Favorite
 
 Share
 In a N x N grid composed of 1 x 1 squares, each 1 x 1 square consists of a /, \, or blank space.  These characters divide the square into contiguous regions.
 
 (Note that backslash characters are escaped, so a \ is represented as "\\".)
 
 Return the number of regions.
 
 
 
 Example 1:
 
 Input:
 [
 " /",
 "/ "
 ]
 Output: 2
 Explanation: The 2x2 grid is as follows:
 
 Example 2:
 
 Input:
 [
 " /",
 "  "
 ]
 Output: 1
 Explanation: The 2x2 grid is as follows:
 
 Example 3:
 
 Input:
 [
 "\\/",
 "/\\"
 ]
 Output: 4
 Explanation: (Recall that because \ characters are escaped, "\\/" refers to \/, and "/\\" refers to /\.)
 The 2x2 grid is as follows:
 
 Example 4:
 
 Input:
 [
 "/\\",
 "\\/"
 ]
 Output: 5
 Explanation: (Recall that because \ characters are escaped, "/\\" refers to /\, and "\\/" refers to \/.)
 The 2x2 grid is as follows:
 
 Example 5:
 
 Input:
 [
 "//",
 "/ "
 ]
 Output: 3
 Explanation: The 2x2 grid is as follows:
 
 
 
 Note:
 
 1 <= grid.length == grid[0].length <= 30
 grid[i][j] is either '/', '\', or ' '.
 */

class Solution {
public:
    /**
     * Union-Find:
     *  a unit of the grid can be divided by '\' and '/' into 4 triangles,
     *  assign a markup id to each of them: left most = 0, upper most = 1, right
     *  most = 2, lower most = 3. Id of each triangle is base id of the cell
     *  plus the markup.
     *
     *  so, all such trianges inside grid can be assigned with an id.
     *  and connections can betweens triangles can be found out by '\' or '/'.
     *
     * triangles at the first row, last row, first column and last column
     * should be taken care of differently.
     */
    int regionsBySlashes(vector<string>& grid) {
        int n = grid.size();
        vector<int> group((n*n)<<2, 0);
        int id = 0;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j, id+=4) {
                if (grid[i][j] == ' ') {
                    group[id] = id;
                    group[id+1] = id;
                    group[id+2] = id;
                    group[id+3] = id;
                } else if (grid[i][j] == '\\') {
                    group[id] = id;
                    group[id+3] = id;
                    group[id+1] = id+1;
                    group[id+2] = id+1;
                } else {
                    group[id] = id;
                    group[id+1] = id;
                    group[id+2] = id+2;
                    group[id+3] = id+2;
                }
            }
        }
        
        id = 0;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j, id+=4) {
                char c = grid[i][j];
                if (i-1 >= 0) {
                    int nid = id + 3 - (n<<2);
                    int cid = id;
                    if (c == '\\') {
                        cid = id + 1;
                    } else if (c == '/') {
                        cid = id;
                    }
                    int pid = find(cid, group);
                    int npid = find(nid, group);
                    if (pid < npid) {
                        group[npid] = pid;
                    } else {
                        group[pid] = npid;
                    }
                }
                if (i+1 < n) {
                    int nid = id + 1 + (n << 2);
                    int cid = id;
                    if (c == '\\') {
                        cid = id;
                    } else if (c == '/') {
                        cid = id+2;
                    }
                    int pid = find(cid, group);
                    int npid = find(nid, group);
                    if (pid < npid) {
                        group[npid] = pid;
                    } else {
                        group[pid] = npid;
                    }
                }
                if (j-1>=0) {
                    int nid = id - 2;
                    int cid = id;
                    int pid = find(cid, group);
                    int npid = find(nid, group);
                    if (pid < npid) {
                        group[npid] = pid;
                    } else {
                        group[pid] = npid;
                    }
                }
                if (j+1 < n) {
                    int nid = id + 4;
                    int cid = id;
                    if (c == '\\') {
                        cid = id + 1;
                    } else if (c == '/') {
                        cid = id+2;
                    }
                    int pid = find(cid, group);
                    int npid = find(nid, group);
                    if (pid < npid) {
                        group[npid] = pid;
                    } else {
                        group[pid] = npid;
                    }
                }
            } // end column loop
        } // end row loop
        
        id = 0;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j, id+=4) {
                for (int k = 0; k < 4; ++k) {
                    find(id+k, group);
                }
            }
        }
        
        unordered_set<int> ug;
        id = 0;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j, id+=4) {
                for (int k = 0; k < 4; ++k) {
                    int pid = find(id+k, group);
                    ug.insert(pid);
                }
            }
        }
        return ug.size();
        
    }

private:
    int find(int id, vector<int>& group) {
        if (group[id] != id) {
            group[id] = find(group[id], group);
        }
        return group[id];
    }
};

}

/*/
int main() {
    // TODO: define parameter type here
    struct d {
        vector<string> grid;
    };
    // TODO: prepare parameters here
    vector<struct d> p {
        {{
            " /",
            "/ "
        }},
        {{
            " /",
            "  "
        }},
        {{
            "\\/",
            "/\\"
        }},
        {{
            "/\\",
            "\\/"
        }},
        {{
            "//",
            "/ "
        }},
        {{
            "    ",
            " /\\ ",
            " \\/ ",
            "    "
        }},
    };

    vector< int > answers {
        2,
        1,
        4,
        5,
        3,
        2
    };

    // TODO: update paramters.
    for (auto& dp : p) {
        cout << endl;
        clock_t tstart = clock();
        auto res = regionsBySlashes::Solution().regionsBySlashes(dp.grid);
        cout << clock() - tstart << endl;
        cout << res << endl;
    }
    return 0;
}
//*/
