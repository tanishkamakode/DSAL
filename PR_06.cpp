#include <iostream>
#include <stack>
#include <queue>
#include <unordered_map>
using namespace std;

class node{
public:
	string data;
	node *next;
	node *down;

	node(){
		data = "";
		next = nullptr;
		down = nullptr;
	}
}*head;

class graphOperations{
public:
	node* createAdjacencyList(node *head);
	void displayAdjacencyList(node *head);
	void BFS_traversal(node *head);
};

node* graphOperations::createAdjacencyList(node *head){
	int headerNodes;
	cout << "How many locations you want to enter? Enter the number: ";
	cin >> headerNodes;

	for(int i = 0; i < headerNodes; i++){
		node *newnode1 = new node();
		cout << "Enter name of new location: ";
		cin >> newnode1->data;

		if(head == nullptr){
			head = newnode1;
		}
		else {
			node *temp = head;
			while(temp->down != nullptr){
				temp = temp->down;
			}
			temp->down = newnode1;
		}

		int adjacentNodes;
		cout << "How many locations you want to enter adjacent to it? Enter the number: ";
		cin >> adjacentNodes;

		for(int j = 0; j < adjacentNodes; j++){
			node *newnode2 = new node();
			cout << "Enter name of adjacent location: ";
			cin >> newnode2->data;

			if(newnode1->next == nullptr){
				newnode1->next = newnode2;
			}
			else {
				node *temp = newnode1;
				while(temp->next != nullptr){
					temp = temp->next;
				}
				temp->next = newnode2;
			}
		}
	}
	return head;
}

void graphOperations::displayAdjacencyList(node *head){
	if(head == nullptr){
		cout << "No locations entered" << endl;
	}
	else {
		node *temp1 = head;
		while(temp1){
			cout << temp1->data << "===>";
			node *temp2 = temp1->next;
			while(temp2){
				cout << temp2->data << "===>";
				temp2 = temp2->next;
			}
			cout << "NULL" << endl;
			temp1 = temp1->down;
		}
	}
}

void graphOperations::BFS_traversal(node *head){
	if(head == nullptr){
		cout << "Graph is empty" << endl;
		return;
	}

	unordered_map<string, bool> visited;
	queue<node*> q;

	q.push(head);
	visited[head->data] = true;

	while(!q.empty()){
		node *current = q.front();
		q.pop();
		cout << current->data << " ";

		node *temp = current->next;
		while(temp){
			if(!visited[temp->data]){
				node *adjacentNode = head;
				while(adjacentNode){
					if(adjacentNode->data == temp->data){
						break;
					}
					adjacentNode = adjacentNode->down;
				}
				if(adjacentNode){
					q.push(adjacentNode);
					visited[adjacentNode->data] = true;
				}
			}
			temp = temp->next;
		}
	}
	cout << endl;
}

int main() {
	head = nullptr;
	graphOperations graphhh;
	head = graphhh.createAdjacencyList(head);
	cout << "Adjacency List: " << endl;
	graphhh.displayAdjacencyList(head);
	graphhh.BFS_traversal(head);

	return 0;
}