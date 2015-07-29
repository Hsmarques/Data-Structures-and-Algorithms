#include <iostream>

#define BLACK 0
#define RED 1

using namespace std;

struct node {

    string matricula;
    string status;
    int count;

    int colour;

    struct node* right;
    struct node* left;
};

bool found = false;

int nNodes = 0;
int nRot = 0;

struct node* singleleft (struct node* anode) {

    nRot++;

    struct node* temp = anode->left;

    anode->left = temp->right;
    temp->right = anode;

    anode->colour = RED;
    temp->colour = BLACK;

    return temp;
}

struct node* singleright (struct node* anode) {

    nRot++;

    struct node* temp = anode->right;

    anode->right = temp->left;
    temp->left = anode;

    anode->colour = RED;
    temp->colour = BLACK;

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

struct node* addnode (struct node* anode, string matricula, string status) {

    nNodes++;

    if (anode == NULL) {
        struct node* temp = new struct node;

        temp->matricula = matricula;
        temp->status = status;
        temp->count = 1;
        temp->colour = RED;
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

            if (anode->left != NULL && anode->right != NULL && anode->left->colour == RED && anode->right->colour == RED) {
                anode->left->colour = BLACK;
                anode->right->colour = BLACK;
                anode->colour = RED;
            }

            if (anode->left != NULL && anode->left->left != NULL && anode->left->colour == RED && anode->left->left->colour == RED) {
                anode = singleleft(anode);
            }

            if (anode->left != NULL && anode->left->right != NULL && anode->left->colour == RED && anode->left->right->colour == RED) {
                anode = leftright(anode);
            }
        }

        if (anode->matricula<matricula) { // matricula > anode->matricula , go right
            anode->right = addnode((anode->right), matricula, status);

            if (anode->left != NULL && anode->right != NULL && anode->left->colour == RED && anode->right->colour == RED) {
                anode->left->colour = BLACK;
                anode->right->colour = BLACK;
                anode->colour = RED;
            }

            if (anode->right != NULL && anode->right->right != NULL && anode->right->colour == RED && anode->right->right->colour == RED) {
                anode = singleright(anode);
            }

            if (anode->right != NULL && anode->right->left != NULL && anode->right->colour == RED && anode->right->left->colour == RED) {
                anode = rightleft(anode);
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
    }

    //printall(head);
    cout << "Nós percorridos: " << nNodes << endl;
    cout << "Rotações: " << nRot << endl;

    return 0;
}
