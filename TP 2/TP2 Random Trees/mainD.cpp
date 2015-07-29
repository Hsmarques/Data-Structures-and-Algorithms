#include <iostream>
#include <algorithm>
#include <ctime>


using namespace std;


struct node {

    string matricula;
    string status;
    int count;

    int priority;

    struct node* right;
    struct node* left;
};

bool found = false;

int nNodes = 0;
int nrot = 0;
int size = 0;

int randomPriority(){
    srand(time(0));
    return (int)(rand()%size)+1;
}


struct node* addnode(struct node* anode, string matricula, string status) {

    nNodes++;

    if (anode == NULL) {
        struct node* temp = new struct node;

        temp->matricula = matricula;
        temp->status = status;
        temp->count = 1;
        size++;
        temp->priority=randomPriority(); // assign priority
        temp->right = NULL;
        temp->left = NULL;


        return temp;
    }


    if (anode->matricula == matricula) { // already exists
        anode->count++;
        anode->status=status;
    } else {

        if (anode->matricula>matricula) { // go left and rotatate if needed
            anode->left = addnode((anode->left), matricula, status);

            if (anode->priority < anode->left->priority) {
                nrot++;

                struct node* temp2 = anode->left;

                anode->left = temp2->right;
                temp2->right = anode;
                anode = temp2;
            }
        }

        if (anode->matricula<matricula) { // go right and rotate if needed
            anode->right = addnode((anode->right), matricula, status);

            if (anode->priority < anode->right->priority) {
                nrot++;

                struct node* temp2 = anode->right;

                anode->right = temp2->left;
                temp2->left = anode;
                anode = temp2;
            }
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
    }

//    printall(head);

    cout << "Nós percorridos: " << nNodes << endl;
    cout << "Rotações: " << nrot << endl;

    return 0;
}

