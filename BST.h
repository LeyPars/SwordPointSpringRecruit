#ifndef __BINARY_SEARCH_TREE_
#define __BINARY_SEARCH_TREE_


struct TreeNode
{
	int val;
	TreeNode* left,*right;
	TreeNode(int v):val(v),left(NULL),right(NULL){}
};

TreeNode* search(TreeNode* root,int target)
{

	//recursive
	if(root==NULL || root->val == target) return root;
	if(target < root->val) return search(root->left,target);
	else return search(root->right,target);


	//loop
	/*
	while(root!=NULL&&root->val!=target)
	{
		if(target < root->val) root=root->left;
		else root=root->right;
	}
	return root;
	*/
}

TreeNode* getMinNode()
{
	TreeNode* cur = root;
	while(cur->left!=NULL) cur = cur->left;
	return cur;
}

TreeNode* getMaxNode()
{
	TreeNode* cur = root;
	while(cur->right!=NULL) cur = cur->right;
	return cur;
}

void insert(TreeNode* root,int val)
{
	if(search(root,val)!=NULL) return;
	TreeNode* tra = root,*spot = NULL;
	while(tra!=NULL)
	{
		spot = tra;
		if(val < tra->val) tra =tra->left;
		else tra = tra->right;
	}
	if(spot==NULL)
	{
		root = new TreeNode(val);
	} else if(spot->val > val)
	{
		spot->left = new TreeNode(val);
	} else
	{
		spot->right	= new TreeNode(val);
	}
}

void remove(TreeNode* root,int val)
{
	
}



#endif
