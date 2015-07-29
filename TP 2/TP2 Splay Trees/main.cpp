#include <iostream>


using namespace std;

struct node {

    string matricula;
    string status;
    int count;

    struct node* right;
    struct node* left;
};

bool found = false;

int nNodes = 0;
int nrot = 0;


void printall (struct node* anode) {

    if (anode == NULL) {
        return;
    } else {
        printall(anode->left);
        cout << anode->matricula << " " << anode->count << " " << anode->status << endl;
        printall(anode->right);
    }
}

struct node* splaytotop (struct node* anode, string matricula) { // splay to the top

    struct node temp;
    struct node* left;
    struct node* right;
    struct node* y;

    if (anode == NULL) {
        return anode;
    }

    temp.right = NULL;
    temp.left = NULL;
    left = right = &temp;

    while (true) { // splay untill end

        nNodes++;

        if (matricula < anode->matricula) {
            if (anode->left == NULL) {
                break;
            }
            if (matricula < anode->left->matricula) {
                nrot++;
                y = anode->left;
                anode->left = y->right;
                y->right = anode;
                anode = y;
                if (anode->left == NULL) {
                    break;
                }
            }
            nrot++;
            right->left = anode;
            right = anode;
            anode = anode->left;

        } else if (matricula > anode->matricula) {
            if (anode->right == NULL) {
                break;
            }
            if (matricula > anode->right->matricula) {
                nrot++;
                y = anode->right;
                anode->right = y->left;
                y->left = anode;
                anode = y;
                if (anode->right == NULL) {
                    break;
                }
            }
            nrot++;
            left->right = anode;
            left = anode;
            anode = anode->right;
        } else {
            break;
        }
    }

    left->right = anode->left;
    right->left = anode->right;
    nrot++;
    anode->left = temp.right;
    anode->right = temp.left;
    return anode;

}

struct node* addnode(struct node* anode, string matricula, string status) {

    struct node* temp = new struct node;

    temp->matricula = matricula;
    temp->status = status;
    temp->count = 1;

    if (anode == NULL) {
        temp->right = NULL;
        temp->left = NULL;
        return temp;
    }

    anode = splaytotop(anode, matricula);

    if (matricula == anode->matricula) {
        anode->count++;
        anode->status=status;
        delete temp;
        return anode;
    } else if (matricula < anode->matricula) {
        nrot++;
        temp->left = anode->left;
        temp->right = anode;
        anode->left = NULL;
        return temp;

    } else if (matricula > anode->matricula) {
        nrot++;
        temp->right = anode->right;
        temp->left = anode;
        anode->right = NULL;
        return temp;
    } else {
        return anode;
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
            found = false;
            unflag(head, matricula);
        }
    }
    //printall(temp);

    cout << "Nós percorridos: " << nNodes << endl;
    cout << "Rotações: " << nrot << endl;

    return 0;
}

