#include <bits/stdc++.h>
using namespace std;

struct Node
{
    int data;
    Node *left;
    Node *right;
};

Node *newNode(int val)
{
    Node *temp = new Node;
    temp->data = val;
    temp->left = NULL;
    temp->right = NULL;
    return temp;
}

Node *buildTree(string str)
{
    if (str.length() == 0 || str[0] == 'N')
        return NULL;
    vector<string> ip;
    istringstream iss(str);
    for (string str; iss >> str;)
        ip.push_back(str);
    Node *root = newNode(stoi(ip[0]));
    queue<Node *> queue;
    queue.push(root);
    int i = 1;
    while (!queue.empty() && i < ip.size())
    {
        Node *currNode = queue.front();
        queue.pop();
        string currVal = ip[i];
        if (currVal != "N")
        {
            currNode->left = newNode(stoi(currVal));
            queue.push(currNode->left);
        }
        i++;
        if (i >= ip.size())
            break;
        currVal = ip[i];
        if (currVal != "N")
        {
            currNode->right = newNode(stoi(currVal));
            queue.push(currNode->right);
        }
        i++;
    }
    return root;
}

class Solution
{
    void add(Node *n, int d, int *s)
    {
        if (!n || d < 0)
            return;
        *s += n->data;
        add(n->left, d - 1, s);
        add(n->right, d - 1, s);
    }
    int traverse(Node *n, int target, int k, int *s)
    {
        if (!n)
            return -1;
        if (n->data == target)
        {
            add(n, k, s);
            return k - 1;
        }
        int d = traverse(n->left, target, k, s);
        if (d > -1)
        {
            *s += n->data;
            add(n->right, d - 1, s);
            return d - 1;
        }
        d = traverse(n->right, target, k, s);
        if (d > -1)
        {
            *s += n->data;
            add(n->left, d - 1, s);
            return d - 1;
        }
        return -1;
    }

public:
    int sum_at_distK(Node *root, int target, int k)
    {
        int s = 0;
        traverse(root, target, k, &s);
        return s;
    }
};

int main()
{
    int t;
    cin >> t;
    getchar();
    while (t--)
    {
        string s;
        getline(cin, s);
        Node *root = buildTree(s);
        int target, k;
        cin >> target >> k;
        getchar();
        Solution obj;
        cout << obj.sum_at_distK(root, target, k) << endl;
    }
    return 0;
}
