#include <iostream>
#include <string>
#include <assert.h>
using namespace std;

typedef string ItemType;

struct WordNode {
	ItemType m_data;
	int count = 0;
	WordNode *m_left;
	WordNode *m_right;
	// You may add additional data members and member functions in WordNode
};

class WordTree {

private:
	WordNode *root;
	
	void Insert(WordNode*& nodeptr, ItemType item)
	{
		if (depth_first_search(root, item) != nullptr)
		{
			addCount(root, item);
			return;
		}
		if (nodeptr == nullptr) {
			nodeptr = new WordNode;
			nodeptr->m_data = item;
			nodeptr->m_right = nullptr;
			nodeptr->m_left = nullptr;
			nodeptr->count++;
			return;
		}
		if (item < nodeptr->m_data)
			Insert(nodeptr->m_left, item);
		else
			Insert(nodeptr->m_right, item);
	}

	WordNode* depth_first_search(WordNode* node, const ItemType& item)
	{
		WordNode* result;
		if (node == nullptr || node->m_data == item) // short circuit evaluation important here
			return node;
		result = depth_first_search(node->m_left, item);
		if (result == nullptr)
			return depth_first_search(node->m_right, item);
		return result;
	}

	void addCount(WordNode*& nodeptr, ItemType v)
	{
		depth_first_search(root, v)->count++;
	}

	void Delete(WordNode *p)
	{
		if (p == nullptr)
			return;
		else
		{
			Delete(p->m_left);
			Delete(p->m_right);
			delete p;
		}
	}

	int countNum(WordNode *p, int count) const
	{
		if (p == nullptr)
			return count;
		if (p != NULL)
		{
			count = countNum(p->m_left, count);
			count++;
			count = countNum(p->m_right, count);
		}
	}

	int countTotalNum(WordNode *p, int count) const
	{
		if (p == nullptr)
			return count;
		if (p != NULL)
		{
			count = countTotalNum(p->m_left, count);
			count += p->count;
			count = countTotalNum(p->m_right, count);
		}
	}

	const void Print(ostream& out) const
	{
		printHelper(root, out);
	}

	const void printHelper(WordNode *p, ostream& out) const
	{
		if (p == nullptr)
			return;
		else
		{
			printHelper(p->m_left, out);
			out << p->m_data << " " << p->count << endl;
			printHelper(p->m_right, out);
		}
	}

	void Copy(WordNode* &new_root, WordNode* old_root) const
	{
		WordNode* cur = old_root;
		new_root = new WordNode;
		new_root->m_left = nullptr;
		new_root->m_right = nullptr;
		new_root->m_data = cur->m_data;
		new_root->count = cur->count;
		if (cur->m_left)
		{
			Copy(new_root->m_left, old_root->m_left);
		}
		if (cur->m_right)
		{
			Copy(new_root->m_right, old_root->m_right);
		}
	}

public:
	// default constructor            
	WordTree() : root(nullptr) { };

	// copy constructor
	WordTree(const WordTree& rhs)
	{
		WordNode* now;
		Copy(now, rhs.root);
		std::swap(now, this->root);
	}

	// assignment operator
	const WordTree& operator=(const WordTree& rhs)
	{
		WordTree temp(rhs);
		std::swap(temp.root, root);
		return *this;
	}

	// Inserts v into the WordTree    
	void add(ItemType v)
	{
		Insert(root, v);
	}

	// Returns the number of distince words / nodes   
	int distinctWords() const
	{
		int i = countNum(root, 0);
		return i;
	}

	// Returns the total number of words inserted, including duplicate
	// values    
	int totalWords() const
	{
		return countTotalNum(root, 0);
	}

	// Prints the LinkedList 
	friend ostream& operator<<(ostream &out, const WordTree& rhs)
	{
		rhs.Print(out);
		return out;
	}

	// Destroys all the dynamically allocated memory
	// in the tree.
	~WordTree()
	{
		Delete(root);
	}
};



int main()
{
	WordTree t;

	t.add("Skyler");
	t.add("Walter");
	t.add("Walter");
	t.add("Hank");
	t.add("Gus");
	t.add("Walter");
	t.add("Gus");


	 
	WordTree i(t);


	cout << t << endl;

	cout << i;
	system("pause");
}