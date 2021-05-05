#include <iostream>
#include <stack>

using namespace std;
//used course algorithm
#define N 4

bool city[N][N] = {{0, 0, 0, 1}, {0, 0, 0, 1}, {0, 0, 0, 1}, {0, 0, 0, 0}};

bool knows (int i, int j) {

    if (city[i][j])
        return true;

    return false;
}

int celeb() {

    stack<int> st;

    for (int i = 0; i < N; i++)
        st.push(i);

    int stays;
    
    while (st.size() > 1) { //more than 1 person
        
        int i = st.top();
        st.pop();

        int j = st.top();
        st.pop();

        if (knows(i,j))
            stays = j;
        else stays = i;

        st.push(stays);

    }

    int p = st.top();
    st.pop();

    for (int i = 0; i < N; i++) {
        if ( (i != p) && (knows(p, i) || !knows(i, p)) )
            return -1;
    }

    return p;

}

int main() {

    printf("Celebrity is: %d (index starts from 0)\n", celeb());

    return 0;
}