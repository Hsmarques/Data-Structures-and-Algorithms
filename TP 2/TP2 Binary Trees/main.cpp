#include <iostream>
#include <stdio.h>
using namespace std;

struct node {

    string matricula;
    string status;
    int count;

    struct node* right;
    struct node* left;
};

bool found = false;
unsigned long long int nNodes=0;

struct node* addnode (struct node* anode, string matricula, string status) {

	nNodes++;

    if (anode == NULL) {
        struct node* temp = new struct node;

        temp->matricula = matricula;
        temp->status = status;
        temp->count = 1;
        temp->right = NULL;
        temp->left = NULL;

        return temp;
    }

    if (anode->matricula == matricula) { // exists
        anode->count++;
        anode->status=status;
    } else {

        if (anode->matricula>matricula) { // matricula < anode->matricula , go left
            anode->left = addnode((anode->left), matricula, status);
        }

        if (anode->matricula<matricula) { // matricula > anode->matricula , go right
            anode->right = addnode((anode->right), matricula, status);
        }
    }

    return anode;
}


void printall (struct node* anode) {

    if (anode == NULL) {
        return;
    } else {
        printall(anode->left);
        cout << anode->matricula << " " << anode->count << " " << anode->status << endl;
        printall(anode->right);
    }
}

void getStatus (struct node* anode, string matricula) {

	nNodes++;

    if (anode == NULL) {
        return;
    }

    if (anode->matricula == matricula) { // found
        found = true;
        cout << anode->matricula << " " << anode->count << " " << anode->status << endl;

    } else { // not found

        if (anode->matricula > matricula) { // finding to the left
            getStatus((anode->left), matricula);
        } else if (anode->matricula < matricula) { // finding to the right
            getStatus((anode->right), matricula);
        }
    }
}

void unflag (struct node* anode, string matricula) {

	nNodes++;

    if (anode == NULL) {
        return;
    }

    if (anode->matricula == matricula) { // found!
        found = true;
        anode->status = "R";
    } else {

        if (anode->matricula > matricula) { // finding to the left
            unflag((anode->left), matricula);
        } else if (anode->matricula < matricula) { // finding to the right
            unflag((anode->right), matricula);
        }
    }
}

int main() {

    string  input, matricula, status;
    struct node* head = NULL;

    
    while(cin >> input){
        if (input.compare("PASS") == 0) {
            cin >> matricula;
            cin >> status;
            head = addnode(head, matricula, status);
        } else if (input.compare("STATUS") == 0) {
            cin >> matricula;
            found = false;
            getStatus(head, matricula);
            if (!found) cout << matricula << " NO RECORD" << endl;
        } else if (input.compare("UNFLAG") == 0) {
            cin >> matricula;
            status="R";
            found = false;
            unflag(head, matricula);
        }
		//cout << "Nós percorridos: " << nNodes << endl;
		//printf("%llu\n", (long long unsigned int) nNodes );
    
    }

    printf("%llu\n", (long long unsigned int) nNodes );
    //printall(head);
    cout << "Nós percorridos2: " << nNodes << endl;

    return 0;
}
