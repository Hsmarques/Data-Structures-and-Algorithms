#include <iostream>

using namespace std;

struct node {

    string matricula;
    string status;
    int count;

    int balance;

    struct node* right;
    struct node* left;
};

bool found = false;
int flag = 0;

int nNodes = 0;
int nRot = 0;

struct node* singleleft (struct node* anode) {

    nRot++;

    struct node* temp = anode->left;

    anode->left = temp->right;
    temp->right = anode;

    return temp;
}

struct node* singleright (struct node* anode) {

    nRot++;

    struct node* temp = anode->right;

    anode->right = temp->left;
    temp->left = anode;

    return temp;
}

struct node* leftright (struct node* anode) {

    anode->left = singleright(anode->left);
    return singleleft(anode);
}

struct node* rightleft (struct node* anode) {

    anode->right = singleleft(anode->right);
    return singleright(anode);
}

void leftbalance (struct node* anode) {

    struct node* temp = anode->left;
    struct node* temp2 = temp->right;

    if (temp2->balance == 0) {
        anode->balance = 0;
        temp->balance = 0;
    } else if (temp2->balance == -1) {
        anode->balance = 1;
        temp->balance = 0;
    } else if (temp2->balance == 1) {
        anode->balance = 0;
        temp->balance = -1;
    }

    temp2->balance = 0;
}

void rightbalance (struct node* anode) { // rebalance the nodes

    struct node* temp = anode->right;
    struct node* temp2 = temp->left;

    if (temp2->balance == 0) {
        anode->balance = 0;
        temp->balance = 0;
    } else if (temp2->balance == 1) {
        anode->balance = -1;
        temp->balance = 0;
    } else if (temp2->balance == -1) {
        anode->balance = 0;
        temp->balance = 1;
    }

    temp2->balance = 0;
}

struct node* addnode (struct node* anode, string matricula, string status){

    nNodes++;

    
    if (anode == NULL) {
        struct node* temp = new struct node;

        temp->matricula = matricula;
        temp->status = status;
        temp->count = 1;
        temp->balance = 0;
        temp->right = NULL;
        temp->left = NULL;

        return temp;
    }

    if (anode->matricula == matricula) { // exists
        anode->count++;
        anode->status=status;
        flag = 1; // no node added, still balanced
    } else {

        if (anode->matricula>matricula) { // matricula < anode->matricula , go left
            anode->left = addnode((anode->left), matricula, status);

            if (flag == 0) { // node added, check if balanced

                anode->balance--;

                if (anode->balance == 0) { // balanced
                    flag = 1;
                } else if (anode->balance <= -2) { // not balanced. left too heavy

                    if (anode->left->balance == -1) { // left left rotation
                        anode->balance = 0;
                        anode->left->balance = 0;
                        anode = singleleft(anode);

                    } else if (anode->left->balance == 1) { // left right rotation
                        leftbalance(anode);
                        anode = leftright(anode);
                    }

                    flag = 1; // balanced after rotation
                }

            }
        }

        if (anode->matricula<matricula) { // matricula > anode->matricula , go right
            anode->right = addnode((anode->right), matricula, status);

            if (flag == 0) { // node added, check if balanced

                anode->balance++;

                if (anode->balance == 0) { // balanced
                    flag = 1;
                } else if (anode->balance >= 2) { // not balanced. right too heavy

                    if (anode->right->balance == 1) { // right right rotation
                        anode->balance = 0;
                        anode->right->balance = 0;
                        anode = singleright(anode);

                    } else if (anode->right->balance == -1) { // right left rotation
                        rightbalance(anode);
                        anode = rightleft(anode);
                    }

                    flag = 1; // balanced after rotation
                }
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
            flag=0;
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

/*  printall(head);*/
    //cout << "Nós percorridos: " << nNodes << endl;
    //cout << "Rotações: " << nRot << endl;

    return 0;
}
