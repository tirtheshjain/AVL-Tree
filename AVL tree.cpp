#include <bits/stdc++.h>
using namespace std;

struct Node
{
    int data, height;
    Node *left, *right;
    
    Node(int x)
    {
        data=x;
        left=right=NULL;
        height=1;
    }
};

void printInorder(Node* n)
{
	if(!n) return;
	printInorder(n->left);
	cout<< n->data << " ";
	printInorder(n->right);
}

int height(Node*p)
{
	int x=p&&p->left?p->left->height:0;
	int y=p&&p->right?p->right->height:0;
	return x>y?x+1:y+1;
}
int balance(Node*p)
{
	int l=p&&p->left?p->left->height:0;
	int r=p&&p->right?p->right->height:0;
	return l-r;
}
Node* LLrotation(Node*p)
{
	Node*pl=p->left;
	
	p->left=pl->right;
	pl->right=p;
	
	p->height=height(p);
	pl->height=height(pl);
	
	return pl;
}
Node* LRrotation(Node*p)
{
	Node*pl=p->left;
	Node*plr=pl->right;
	
	p->left=plr->right;
	pl->right=plr->left;
	plr->left=pl;
	plr->right=p;
	
	p->height=height(p);
	pl->height=height(pl);
	plr->height=height(plr);
	
	return plr;
}
Node* RLrotation(Node*p)
{
	Node*pr=p->right;
	Node*prl=pr->left;
	
	p->right=prl->left;
	pr->left=prl->right;
	prl->left=p;
	prl->right=pr;
	
	p->height=height(p);
	pr->height=height(pr);
	prl->height=height(prl);
	
	return prl;
}
Node* RRrotation(Node*p)
{
	Node*pr=p->right;
	
	p->right=pr->left;
	pr->left=p;
	
	p->height=height(p);
	pr->height=height(pr);
	
	return pr;
}

Node* insert(Node* root, int data)
{
    if(root==NULL)
		return new Node(data);
	if(data<root->data)
		root->left=insert(root->left,data);
	else if(data>root->data)
		root->right=insert(root->right,data);
	else
		return root;
	
	root->height=height(root);
	
	if(balance(root)==2&&balance(root->left)==1)
		return LLrotation(root);
	if(balance(root)==2&&balance(root->left)==-1)
		return LRrotation(root);
	if(balance(root)==-2&&balance(root->right)==1)
		return RLrotation(root);
	if(balance(root)==-2&&balance(root->right)==-1)
		return RRrotation(root);
	
	return root;
}

Node* deleteNode(Node* root, int data)
{
    if(root==NULL)
		return root;
		
	if(data<root->data)
		root->left=deleteNode(root->left,data);
		
	else if(data>root->data)
		root->right=deleteNode(root->right,data);
	else
	{
		if(root->left==NULL)
		{
			Node* temp=root;
			root=root->right;
			delete temp;
		}
		else if(root->right==NULL)
		{
			Node*temp=root;
			root=root->left;
			delete temp;
		}
		else
		{
		    Node *temp=root->right;
		    while(temp->left)
		    	temp=temp->left;
		    root->data=temp->data;
		    root->right=deleteNode(root->right,temp->data);		
		}
	}
	
	if(root==NULL)	return root; 
	
	root->height=height(root);
	
	if(balance(root)==2&&balance(root->left)>=0)
		return LLrotation(root);
	if(balance(root)==2&&balance(root->left)==-1)
		return LRrotation(root);
	if(balance(root)==-2&&balance(root->right)==1)
		return RLrotation(root);
	if(balance(root)==-2&&balance(root->right)<=0)
		return RRrotation(root);
	
	return root;	
}
int main()
{
	Node*root=NULL;
	root=insert(root,9);
	root=insert(root,6);
	root=insert(root,5);
	root=insert(root,8);
	root=insert(root,7);
	root=insert(root,10);
	root=insert(root,12);
	root=insert(root,22);
	root=insert(root,0);
	root=insert(root,3);
	root=insert(root,4);
	root=deleteNode(root,0);
	root=deleteNode(root,12);
	root=deleteNode(root,22);
	
	printInorder(root);
	return 0;
}
