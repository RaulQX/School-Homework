#include <iostream>
#include <queue>

using namespace std;

#define N 5
#define CAPACITY 7

typedef struct item {

    int cost;
    int weight;

}items;

int main () {
    
    items sack[5] = { {2,3}, {2,1}, {4,3}, {5,4}, {3,2} };

    int memMatrix[N + 1][CAPACITY + 1] = {{0}};

    int cap = CAPACITY;

    queue<int> selectedItems;

    for (int i = 1; i <= N; i++) {
        
        int v = sack[i-1].cost;
        int w = sack[i-1].weight;

        for (int j = 1; j <= CAPACITY; j++) {

            memMatrix[i][j] = memMatrix[i-1][j];

            if (j >= w && memMatrix[i-1][j-w] + v > memMatrix[i][j])
                memMatrix[i][j] = memMatrix[i-1][j-w] + v;

        }
    }

    for (int i = N; i > 0; i--) {
        if (memMatrix[i][cap] != memMatrix[i - 1][cap]) {

            selectedItems.push(i);
            cap = cap - sack[i - 1].weight;
            
        }
    }

    cout << "Matrix: \n";
    
    for (size_t i = 0; i < N + 1; i++) {

        for (size_t j = 0; j < CAPACITY + 1; j++) {

            cout << memMatrix[i][j] << " ";
        }
        cout << endl;
    }

    cout << "\nItems selected:\n";

    while (!selectedItems.empty()) {
        cout << selectedItems.front() << ' ';
        selectedItems.pop();
    }

    cout << "\n";

    return 0;
}