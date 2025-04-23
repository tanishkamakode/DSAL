#include <iostream>
using namespace std;

class Graph{
public:
	int adjMat[10][10];
	int size;

	Graph(int s){
		size = s;
		for(int i = 0; i < s; i++){
			for(int j = 0; j < s; j++){
				adjMat[i][j] = 0;
			}
		}
	}

	void create_graph(){
		for(int i = 0; i < size; i++){
			for(int j = 0; j < size; j++){

				if(i == j){
					continue;
				}

				char ans;
				cout << "\nIs there any leasing wire connection to be made between office " << i + 1 << " to " << j + 1 << "?(Y/N)";
				cin >> ans;

				if(ans == 'Y' || ans == 'y'){
					int temp;
					cout << "Enter cost for leasing wire from office " << i + 1 << " to " << j + 1 << " : ";
					cin >> temp;
					adjMat[i][j] = temp;
					adjMat[j][i] = temp;
				}
			}
		}
	}

	void display_graph(){
		cout << "Adjacency matrix: " << endl;
		for(int i = 0; i < size; i++){
			for(int j = 0; j < size; j++){
				cout << adjMat[i][j] << "\t";
			}
			cout << endl;
		}
	}

	void find_shortpath(){
		int selected[10] = {0};
		int total_cost = 0;

		selected[0] = 1;

		for(int edge = 0; edge < size - 1; edge++){
			int min = 99999;
			int r = 0, c = 0;

			for(int i = 0; i < size; i++){
				if(selected[i]){
					for(int j = 0; j < size; j++){
						if(!selected[j] && adjMat[i][j]){
							if(adjMat[i][j] < min){
								min = adjMat[i][j];
								r = i;
								c = j;
							}
						}
					}
				}
			}

			selected[c] = 1;
			cout << "Edge " << r+1 << " - " << c+1 << " : " << " cost = " << adjMat[r][c] << endl;
			total_cost = total_cost + adjMat[r][c];
		}

		cout << "Total cost of Minimum Spanning Tree: " << total_cost << endl;
	}

};


int main() {
	int size;
	cout << "Enter number of offices: ";
	cin >> size;

	Graph graph(size);
	graph.create_graph();
	graph.display_graph();
	graph.find_shortpath();
	return 0;
}