using namespace std;

#include <iostream>
#include <cstring>
#include <cstdlib>
#include <vector>
#include <fstream>
#include <queue>
#include<cmath>
#include <queue>
#include <stack>

vector <long> range;
template <class T> class rbt_node
{
  private:

	bool if_red;
	rbt_node<T> *left_child, *right_child, *parent;

  public:
      T jobId;

long time;
long ttime;


	rbt_node(T jobId,long t)
	{
		left_child = NULL;
		right_child = NULL;
		this->if_red = true;
		this->jobId = jobId;
		parent = NULL;
		time=0;
        ttime=t;
	}

		bool isRed()
	{
		return if_red;
	}

	void Recolor()    //recolor node
	{
		if (this->if_red==false)
            this->if_red = true;
		else
		    this->if_red = false;
	}

	T GetjobId()    // return jobId of current node
	{
		return this->jobId;
	}

	long GetTime()     // return time of current node
	{
		return this->time;
	}

		rbt_node* get_parent() // return parent of current node
	{
		return this->parent;
	}

	rbt_node* find_left_child()   // return left child of current node
	{
		return this->left_child;
	}
	rbt_node* find_right_child()  // return right child of current node
	{
		return this->right_child;
	}

	void ClearParent()
	{
		this->parent = NULL;
	}
	void set_left(rbt_node* left_child)
	{
		this->left_child = left_child;
		if(left_child != NULL)
            left_child->parent = this;
	}
	void set_right(rbt_node* right_child)
	{
		this->right_child = right_child;
		if(right_child != NULL)
            right_child->parent = this;
	}
};

template <class T> class RBT
{
public:
	rbt_node<T>* root;
    long a[2];

	//the three basic functionalities (inner implementation)
	rbt_node<T>* AccessNode(rbt_node<T> *root, T jobId, long t)   // updates executed time of node after processing
	{
	    if(root==NULL)
            return NULL;
		if(root->GetjobId() == jobId)
		{
		    root->time=t;
			return root;
		}

		else if(root->GetjobId() <= jobId)
		{
			if(root->find_right_child() != NULL)
			{
				return this->AccessNode(root->find_right_child(), jobId, t);

			}
			else
			{

				return NULL;
			}
		}

		else //if(root->GetjobId() > jobId)
		{
			if(root->find_left_child() != NULL)
			{
				return this->AccessNode(root->find_left_child(), jobId,t);

			}
			else
			{
			    	return NULL;

			}
		}

	}




long* AccessNode1(rbt_node<T> *root, T jobId)    // returns executed time and total time of a given jobId
	{
	    if(root==NULL)
        {
   *(a+0)=-1;
   *(a+1)=-1;
   return a;
        }

		if(root->GetjobId() == jobId)
		{
		    a[0]=root->time;
		    a[1]=root->ttime;

			return a;
		}

		else if(root->GetjobId() <= jobId)
		{

			if(root->find_right_child() != NULL)
			{
				 this->AccessNode1(root->find_right_child(), jobId);

			}
			else{

                    *(a+0)=-1;
                    *(a+1)=-1;
                return a;
			}

		}
		else
		{

			if(root->find_left_child() != NULL)
			{

				 this->AccessNode1(root->find_left_child(), jobId);

			}
						else{
                    *(a+0)=-1;
                    *(a+1)=-1;
                return a;
			}

		}

	}




void print_inorder1(rbt_node<T> *root,T jobId1, T jobId2)  // returns elements from jobId1 to jobId2
{

  if (root == NULL){
          return ;
  }

     /* first print data of node */
     /* then recur on left sutree */
     if(root->GetjobId()<jobId1 && root->GetjobId()>jobId2 )
     {
         return;
     }
     else if(root->GetjobId()<jobId1  )
     {
           if(root->get_parent()!=NULL)

           {

            if((root->get_parent())->GetjobId() ==jobId1 )
            return ;
            else
              print_inorder1(root->find_right_child(), jobId1,  jobId2);
           }
           else{

              print_inorder1(root->find_right_child(), jobId1,  jobId2);}

     }
     else if( root->GetjobId()>jobId2 )
     {

           if(root->get_parent()!=NULL)

           {

            if((root->get_parent())->GetjobId() ==jobId2 )
            return ;

            else

         print_inorder1(root->find_left_child(), jobId1,  jobId2);
          }
          else
            {

print_inorder1(root->find_left_child(), jobId1,  jobId2);
            }
     }
     else if(root->GetjobId()>=jobId1 && root->GetjobId()<=jobId2 )
     {

          print_inorder1(root->find_left_child(), jobId1, jobId2);
          range.push_back(root->GetjobId());
          range.push_back(root->time);
          range.push_back(root->ttime);


          print_inorder1(root->find_right_child(), jobId1, jobId2);

     }


}



vector<long> Path(rbt_node<T> *root,vector<T> b,long jobId)
{

long c=0;
while(root !=NULL )
{

if(root->jobId <jobId )
  {
  b.push_back(root->jobId);
  root=root->find_right_child();

  }


else if(root->jobId >jobId)
  {
  b.push_back(root->jobId);
  root=root->find_left_child();

  }
 else if(root->jobId==jobId)
 {
      b.push_back(root->jobId);

  if(root->find_right_child()!=NULL)
    b.push_back((root->find_right_child())->jobId);

  if(root->find_left_child()!=NULL)
    b.push_back((root->find_left_child())->jobId);

c=1;
 }

if(c==1)
    break;
}

return b;

}




private:
	void insert_node(rbt_node<T> *root, T jobId,T t)
	{
		//regular BST insert
		rbt_node<T>* new_node = NULL;

		if(root->GetjobId() == jobId)
		{
			//skip
		}

		else if(root->GetjobId() <= jobId)
		{
			if(root->find_right_child() == NULL)
			{
				new_node = new rbt_node<T>(jobId,t);
				root->set_right(new_node);
			}
			else
			{
				this->insert_node(root->find_right_child(), jobId,t);
			}
		}

        else
		{
			if(root->find_left_child() == NULL)
			{
				new_node = new rbt_node<T>(jobId,t);
				root->set_left(new_node);
			}
			else
			{
				this->insert_node(root->find_left_child(), jobId,t);
			}
		}
		//restore uniform black height
		if (new_node == NULL) return;
		this->RR_fix(root);

		new_node = NULL;
	}
	void delete_node(rbt_node<T> *root, T jobId)
	{
		if(root->GetjobId() == jobId)
		{
			rbt_node<T> *left_childmostFromright_child;
			if (root->find_left_child() == NULL)
                left_childmostFromright_child = root->find_right_child();
			else if (root->find_left_child()->find_right_child() == NULL)
                left_childmostFromright_child = root->find_left_child();
	     else if (root->find_right_child() == NULL)
			    left_childmostFromright_child = root->find_left_child();
		    	else if (root->find_right_child()->find_left_child() == NULL)
			    left_childmostFromright_child = root->find_right_child();
			else
			{
				left_childmostFromright_child = root->find_right_child()->find_left_child();
				while (left_childmostFromright_child->find_left_child() != NULL)
				{
					left_childmostFromright_child = left_childmostFromright_child->find_left_child();
				}
			}
			if (left_childmostFromright_child == NULL)
			{
				if (root->find_left_child() != NULL)
                    root->find_left_child()->Recolor();
				else if (root->find_right_child() != NULL)
            root->find_right_child()->Recolor();
				//this case is possible only if (left_child mostFrom right_child != root->find_left_child() && root->find_left_child() != NULL)
				else if (!root->isRed())
                    height_change_reduce(root);
			}
			else
			{
				//left_child mostFrom right_child is always black and its single child is always red - first condition is possible because of the four exceptional cases
				 if (left_childmostFromright_child->find_right_child() != NULL)
				    left_childmostFromright_child->find_right_child()->Recolor();
				else if (left_childmostFromright_child->find_left_child() != NULL)
                    left_childmostFromright_child->find_left_child()->Recolor();

				//this case is possible only if (left_child most From right_child != root->find_left_child() && root->find_left_child() != NULL)
				else if (!left_childmostFromright_child->isRed())
                    height_change_reduce(left_childmostFromright_child);
            if (left_childmostFromright_child != root->find_left_child() && left_childmostFromright_child != root->find_right_child())
				  left_childmostFromright_child->get_parent()->set_left(left_childmostFromright_child->find_right_child());

				//replace with originally removed node
				//include the above cases where left_child most is child of the root
				if (left_childmostFromright_child != root->find_right_child() && root->find_right_child() != NULL)
				    left_childmostFromright_child->set_right(root->find_right_child());

				 if (left_childmostFromright_child != root->find_left_child() && root->find_left_child() != NULL)
                    left_childmostFromright_child->set_left(root->find_left_child());
				//recolor if necessary
            if (root->isRed() && !left_childmostFromright_child->isRed())
                left_childmostFromright_child->Recolor();
				if (!root->isRed() && left_childmostFromright_child->isRed())
                    left_childmostFromright_child->Recolor();
			}
			if (root->get_parent() != NULL)
			{
				if (root->get_parent()->find_left_child() == root) root->get_parent()->set_left(left_childmostFromright_child);
				else root->get_parent()->set_right(left_childmostFromright_child);
			}
			else
			{
				this->root = left_childmostFromright_child;
				if (this->root != NULL) this->root->ClearParent();
			}
			delete root;
		}
		else if(root->GetjobId() > jobId)
		{
			if(root->find_left_child() != NULL)
            {
				this->delete_node(root->find_left_child(), jobId);
			}
		}
		else
		{
			if(root->find_right_child() != NULL)
			{
				this->delete_node(root->find_right_child(), jobId);
			}
		}
	}


	void RR_fix(rbt_node<T> *root)
	{
		if (root->isRed() == false)
            return;
		//right_child rotate
		if (root == root->get_parent()->find_left_child())
		{
			if (root->get_parent()->find_right_child() == NULL || !root->get_parent()->find_right_child()->isRed())
                this->right_childRotate(root);
			else
			{
				root->Recolor();
				root->get_parent()->find_right_child()->Recolor();
				root->get_parent()->Recolor();
				//case real root is reached
				if (root->get_parent()->get_parent() == NULL)
				{
					root->get_parent()->Recolor();
					return;
				}
				//root is now black so check one level up
				RR_fix(root->get_parent()->get_parent());
			}
		}
		//left_child rotate
		else
		{
			if (root->get_parent()->find_left_child() == NULL || !root->get_parent()->find_left_child()->isRed())
                this->left_childRotate(root);
			else
			{
				root->Recolor();
				root->get_parent()->find_left_child()->Recolor();
				root->get_parent()->Recolor();
				//case real root is reached
				if (root->get_parent()->get_parent() == NULL)
				{
					root->get_parent()->Recolor();
					return;
				}
				//root is now black so check one level up
				RR_fix(root->get_parent()->get_parent());
			}
		}
	}
	void left_childRotate(rbt_node<T> *root)
	{
		rbt_node<T> *parent = root->get_parent();
		//avl similar case 2 for left_child rotation - double rotation
		if (root->find_left_child() != NULL && root->find_left_child()->isRed())
		{
			rbt_node<T> *misplace_child =NULL;
			misplace_child= root->find_left_child();
			root->set_left(misplace_child->find_right_child());
			misplace_child->set_right(root);
			parent->set_right(misplace_child);
			root = misplace_child;
		}
		root->Recolor();
		parent->Recolor();
		//parent's right_child -> root's left_child
		parent->set_right(root->find_left_child());
		//root -> parent
		if (parent->get_parent() != NULL)
		{
			//bind root to rest of the tree
			 if(parent->get_parent()->find_left_child() != parent)
			parent->get_parent()->set_right(root);
			else if (parent->get_parent()->find_left_child() == parent)
                parent->get_parent()->set_left(root);

		}
		else
		{
			//root is real root
			this->root = root;
			this->root->ClearParent();
			root = this->root;
		}
		//root's left_child -> parent
		root->set_left(parent);
	}
	void right_childRotate(rbt_node<T> *root)
	{
		rbt_node<T> *parent = root->get_parent();
		//avl similar case 2 for right_child rotation - double rotation
		if (root->find_right_child() != NULL && root->find_right_child()->isRed())
		{
			rbt_node<T> *misplace_child = root->find_right_child();
			root->set_right(misplace_child->find_left_child());
			misplace_child->set_left(root);
			parent->set_left(misplace_child);
			root = misplace_child;
		}
		root->Recolor();
		parent->Recolor();
		//parent's left_child -> root's right_child
		parent->set_left(root->find_right_child());
		//root -> parent
		if (parent->get_parent() != NULL)
		{
			//bind root to rest of the tree
			if (parent->get_parent()->find_left_child() == parent) parent->get_parent()->set_left(root);
			else parent->get_parent()->set_right(root);
		}
		else if (parent->get_parent() == NULL)
		{
			//root is real root
			this->root = root;
			this->root->ClearParent();
			root = this->root;
		}
		//root's right_child -> parent
		root->set_right(parent);
	}
	//balancing functionalities: reduced height problem and deletion
	void height_change_reduce(rbt_node<T> *root)
	{
		rbt_node<T>* parent = root->get_parent();
		if (parent == NULL)
            return;
		//double cases because of symmetries
		if (root == parent->find_left_child())
		{
			if (parent->isRed()==true)
			{
				//first two cases
				if ((parent->find_right_child()-> find_left_child() != NULL && parent -> find_right_child() ->find_left_child()->isRed())
					|| (parent->find_right_child()-> find_right_child() != NULL && parent->  find_right_child() ->find_right_child()->isRed()))
				{
					//case 1.1L
					L_rotate_1(parent->find_right_child());
				}
				else
				{
					//case 1.2L
					parent->find_right_child()->Recolor();
					parent->Recolor();
				}
			}
			else if(parent->isRed()==false)
			{
				if (parent->find_right_child()->isRed() ==true )
				{
					//middle two cases
					if ((parent->find_right_child()->find_left_child()->find_right_child() != NULL && parent->find_right_child()->find_left_child()->find_right_child()->isRed())
						|| (parent->find_right_child()->find_left_child()->find_left_child() != NULL && parent->find_right_child()->find_left_child()->find_left_child()->isRed()))
					{
						//case 2.1.1L
						L_rotate_2(parent->find_right_child());
					}
					else
					{
						//case 2.1.2L
						L_rotate_3(parent->find_right_child());
					}
				}
				else if((parent->find_right_child()->isRed() ==false ))
				{
					//last two cases
					if ((parent->find_right_child()->find_left_child() != NULL && parent->find_right_child()->find_left_child()->isRed())
						|| (parent->find_right_child()->find_right_child() != NULL && parent->find_right_child()->find_right_child()->isRed()))
					{
						//case 2.2.1L
						L_rotate_4(parent->find_right_child());
					}
					else
					{
						//case 2.2.2L
						parent->find_right_child()->Recolor();
						if (parent->get_parent() != NULL) height_change_reduce(parent);
						//otherwise overall black height reduced by 1
					}
				}
			}
		}
		else
		{
			 if (parent->isRed()==false)
			{
				if (parent->find_left_child()->isRed())
				{
					//middle two cases
					if ((parent->find_left_child()->find_right_child()->find_right_child() != NULL && parent->find_left_child()->find_right_child()->find_right_child()->isRed())
						|| (parent->find_left_child()->find_right_child()->find_left_child() != NULL && parent->find_left_child()->find_right_child()->find_left_child()->isRed()))
					{
						//case 2.1.1R
						R_rotate_2(parent->find_left_child());
					}
					else
					{
						//case 2.1.2R
						R_rotate_3(parent->find_left_child());
					}
				}
				else
				{
					//last two cases
					if ((parent->find_left_child()->find_left_child() != NULL && parent->find_left_child()->find_left_child()->isRed())
						|| (parent->find_left_child()->find_right_child() != NULL && parent->find_left_child()->find_right_child()->isRed()))
					{
						//case 2.2.1R
						R_rotate_4(parent->find_left_child());
					}
					else
					{
						//case 2.2.2R
						parent->find_left_child()->Recolor();
						if (parent->get_parent() != NULL) height_change_reduce(parent);
						//otherwise overall black height reduced by 1
					}
				}

			}
         else if (parent->isRed()==true)
			{
				//first two cases
				if ((parent->find_left_child()->find_left_child() != NULL && parent->find_left_child()->find_left_child()->isRed())
					|| (parent->find_left_child()->find_right_child() != NULL && parent->find_left_child()->find_right_child()->isRed()))
				{
					//case 1.1R
					R_rotate_1(parent->find_left_child());
				}
				else
				{
					//case 1.2R
					parent->find_left_child()->Recolor();
					parent->Recolor();
				}
			}

		}
	}
	void L_rotate_1(rbt_node<T> *root)
	{
		rbt_node<T> *parent =NULL;
		parent= root->get_parent();
		//avl similar case 2 for left_child rotation - double rotation
		if (root->find_left_child() != NULL && root->find_left_child()->isRed())
		{
			rbt_node<T> *misplace_child = root->find_left_child();
			root->set_left(misplace_child->find_right_child());
			misplace_child->set_right(root);

			parent->set_right(misplace_child);
			root = misplace_child;
			parent->Recolor();
		}
		else
		{
			root->find_right_child()->Recolor();
			parent->Recolor();

			root->Recolor();
		}
		parent->set_right(root->find_left_child());


		if (parent->get_parent() != NULL)
		{
			//bind root to rest of the tree
			if (parent->get_parent()->find_left_child() != parent)
                parent->get_parent()->set_right(root);
			else parent->get_parent()->set_left(root);
		}
		else
		{
			//root is real root
			this->root = root;
			this->root->ClearParent();
			root = this->root;
		}

		root->set_left(parent);
	}
	void L_rotate_2(rbt_node<T> *root)
	{
		rbt_node<T>* parent =NULL;
		parent= root->get_parent();
		rbt_node<T>* gParent = NULL;
		gParent=parent->get_parent();
		//make red child always on the right_child
		if (root->find_left_child()->find_left_child() != NULL && root->find_left_child()->find_left_child()->isRed())
		{
			rbt_node<T> *misplace_child = root->find_left_child()->find_left_child();
			root->find_left_child()->set_left(misplace_child->find_right_child());
			misplace_child->set_right(root->find_left_child());
			root->set_left(misplace_child);
			misplace_child->find_right_child()->Recolor();
			misplace_child->Recolor();
		}
		parent->set_right(root->find_left_child()->find_left_child());
		root->find_left_child()->set_left(parent);
		root->set_left(root->find_left_child()->find_right_child());
		root->find_left_child()->Recolor();
		parent->get_parent()->set_right(root);
		if (gParent != NULL)
		{
			//bind root to rest of the tree
			if (gParent->find_left_child() == parent) gParent->set_left(parent->get_parent());
			else gParent->set_right(parent->get_parent());
		}
		else
		{
			//parent is real root
			this->root = parent->get_parent();
			this->root->ClearParent();
		}
	}
	void L_rotate_3(rbt_node<T> *root)
	{
		rbt_node<T>* parent = root->get_parent();
		root->find_left_child()->Recolor();
		parent->set_right(root->find_left_child());
		root->Recolor();
		if (parent->get_parent() != NULL)
		{
			//bind root to rest of the tree
			if (parent->get_parent()->find_left_child() == parent)
                parent->get_parent()->set_left(root);
			else parent->get_parent()->set_right(root);
		}
		else
		{
			//parent is real root
			this->root = root;
			this->root->ClearParent();
		}
		root->set_left(parent);
	}
	void L_rotate_4(rbt_node<T> *root)
	{
		rbt_node<T> *parent = NULL;

		parent=root->get_parent();
		//similar case 2 for left_child rotation - double rotation

		if (root->find_left_child() != NULL && root->find_left_child()->isRed())
		{
			rbt_node<T> *misplace_child = root->find_left_child();
			root->set_left(misplace_child->find_right_child());

			misplace_child->set_right(root);
			parent->set_right(misplace_child);
			root = misplace_child;
			root->Recolor();
		}
		else
		{
			root->find_right_child()->Recolor();
		}
		parent->set_right(root->find_left_child());

		if (parent->get_parent() != NULL)
		{
			//bind root to rest of the tree
			if (parent->get_parent()->find_left_child() != parent)
                parent->get_parent()->set_right(root);
			else parent->get_parent()->set_left(root);
		}
		else if(parent->get_parent() ==NULL)
		{
			//root is real root
			this->root = root;
			this->root->ClearParent();
			root = this->root;
		}
		root->set_left(parent);
	}
	void R_rotate_1(rbt_node<T> *root)
	{
		rbt_node<T> *parent = NULL;

		parent= root->get_parent();
		//similar case 2 for left_child rotation - double rotation
		if (root->find_right_child() != NULL && root->find_right_child()->isRed())
		{
			rbt_node<T> *misplace_child = root->find_right_child();
			 root->set_right(misplace_child->find_left_child());

		 	misplace_child->set_left(root);
        parent->set_left(misplace_child);

          root = misplace_child;
			parent->Recolor();
		}
		else
		{
			root->find_left_child()->Recolor();

			parent->Recolor();
		root->Recolor();

		}
		parent->set_left(root->find_right_child());
		if (parent->get_parent() != NULL)
		{
			//bind root to rest of the tree
			if (parent->get_parent()->find_left_child() != parent)
                parent->get_parent()->set_right(root);
			else parent->get_parent()->set_left(root);
		}
		else
		{
			//root is real root
			this->root = root;
			this->root->ClearParent();
			root = this->root;
		}
		root->set_right(parent);
	}

	void R_rotate_2(rbt_node<T> *root)
	{
		rbt_node<T>* parent = NULL;
		 parent=root->get_parent();

		rbt_node<T>* gParent = NULL;
		  gParent=parent->get_parent();
		//make red child always on the right_child
		if (root->find_right_child()->find_right_child() != NULL && root->find_right_child()->find_right_child()->isRed())
		{
			rbt_node<T> *misplace_child = root->find_right_child()->find_right_child();

			root->find_right_child()->set_right(misplace_child->find_left_child());
			misplace_child->set_left(root->find_right_child());
        root->set_right(misplace_child);

			misplace_child->find_left_child()->Recolor();
        misplace_child->Recolor();
		}
		parent->set_left(root->find_right_child()->find_right_child());
		 root->find_right_child()->set_right(parent);
		 root->set_right(root->find_right_child()->find_left_child());
		root->find_right_child()->Recolor();
		 parent->get_parent()->set_left(root);

		 if(gParent==NULL)
		{
			//parent is real root
			this->root = parent->get_parent();
			this->root->ClearParent();
		}
		else if (gParent != NULL)
		{
			//bind root to rest of the tree
			if (gParent->find_left_child() == parent) gParent->set_left(parent->get_parent());
			else gParent->set_right(parent->get_parent());
		}
	}
	void R_rotate_3(rbt_node<T> *root)
	{
		rbt_node<T>* parent = NULL;
      parent= root->get_parent();

		root->find_right_child()->Recolor();
		parent->set_left(root->find_right_child());
		root->Recolor();

		if(parent->get_parent() == NULL)
		{
			//parent is real root
			this->root = root;
			this->root->ClearParent();
		}
		else if (parent->get_parent() != NULL)
		{
			//bind root to rest of the tree
			if (parent->get_parent()->find_left_child() == parent)
                parent->get_parent()->set_left(root);
			else parent->get_parent()->set_right(root);
		}

		root->set_right(parent);
	}
	void R_rotate_4(rbt_node<T> *root)
	{
		rbt_node<T> *parent = NULL;
		       parent=root->get_parent();
		//avl similar case 2 for left_child rotation - double rotation

		if (root->find_right_child() != NULL && root->find_right_child()->isRed())
		{
			rbt_node<T> *misplace_child = root->find_right_child();

			root->set_right(misplace_child->find_left_child());
			misplace_child->set_left(root);
			parent->set_left(misplace_child);

			root = misplace_child;
			root->Recolor();
		}
		else
		{

			root->find_left_child()->Recolor();
       }
		parent->set_left(root->find_right_child());

		if (parent->get_parent() != NULL)
		{
			//bind root to rest of the tree
			if (parent->get_parent()->find_left_child() != parent)
                parent->get_parent()->set_right(root);
			else parent->get_parent()->set_left(root);
		}
		else
		{
			//root is real root
			this->root = root;
			this->root->ClearParent();
			root = this->root;
		}

		root->set_right(parent);
	}
public:
	RBT()
	{
		this->root = NULL;
	}
	bool IsEmpty()
	{
		return root == NULL;
	}

	//the three basic functionalities
	rbt_node<T>* AccessNode(T jobId, long t)  // updates exec_time of a node
	{
          return  this->AccessNode(root, jobId,t);
	}

	long * AccessNode2(T jobId)  // returns exec_time and total time of a job
	{
         return   this->AccessNode1(root, jobId);
	}


	void delete_node(T jobId)
	{
		if (this->IsEmpty()) return;
		else
            this->delete_node(root, jobId);
	}



	void insert_node(T jobId,T time)
	{
		if (this->IsEmpty())
		{
			this->root = new rbt_node<T>(jobId,time);

			this->root->Recolor();
    }

		else this->insert_node(this->root, jobId,time);
	}
		//traversals


vector<long> print(T jobId1,T jobId2)
{
 print_inorder1(this->root, jobId1,jobId2);

 return range;

}


	long Next_or_Prev(T jobId, long f)  // finds next or previous job
	{

    if(f==1)
       {
	     vector<long> y;
         vector<long> z;
         size_t i;
         long maxm=jobId;


    z= Path(this->root,y,jobId);
    for(i=0;i<z.size();i++)
    {
        if(z[i]>jobId)
            maxm=z[i];

    }
    for(i=0;i<z.size();i++)
    {
     if(z[i]>jobId)
     {
         if(z[i]<maxm)
            maxm=z[i];
     }
    }

   if(maxm<=jobId)
        return -1;

      else
        return maxm;
       }
else if(f==0)
{

        vector<long> y;
        vector<long> z;
        size_t i;
        long maxm=jobId;


    z= Path(this->root,y,jobId);

  for(i=0;i<z.size();i++)
    {
        if(z[i]<jobId)
            maxm=z[i];
    }
    for(i=0;i<z.size();i++)
    {
     if(z[i]<jobId)
     {
         if(z[i]>maxm)
            maxm=z[i];
     }
    }

   if(maxm>=jobId || maxm ==-1)
        return -1;

      else
        return maxm;




}

return -1;

    }

	void level_traverse()    //levelwise traversal of tree
	{
		if (this->IsEmpty()) return;
		queue<rbt_node<T>*> traversalQ;

		cout << this->root->GetjobId() << "-";
		cout << this->root->GetTime()<<"-" << endl;

		traversalQ.push(this->root);
		traversalQ.push(NULL);
		while (true)
		{
			if (traversalQ.front() == NULL)
			{
				cout << "\n";
				traversalQ.push(NULL);
			}
			else
			{
				if (traversalQ.front()->find_left_child() != NULL)
				{
					//display in proper color
					if (traversalQ.front()->find_left_child()->isRed())
					{
					 	cout << traversalQ.front()->find_left_child()->GetjobId()<<"-";
					 	cout << traversalQ.front()->find_left_child()->GetTime()<<"R";
					}
					else{
                            cout << traversalQ.front()->find_left_child()->GetjobId()<<"-";
					        cout << traversalQ.front()->find_left_child()->GetTime();

					}
                        traversalQ.push(traversalQ.front()->find_left_child());
				}
				else
                    cout << "n";
//
				cout << " ";
				if (traversalQ.front()->find_right_child() != NULL)
				{
					//display in proper color
					if (traversalQ.front()->find_right_child()->isRed())
                    {

						cout << traversalQ.front()->find_right_child()->GetjobId()<<"-";
                    	cout << traversalQ.front()->find_right_child()->GetTime()<<"R";

                    }
					else{
                        cout << traversalQ.front()->find_right_child()->GetjobId()<<" -";
					    cout << traversalQ.front()->find_right_child()->GetTime();

					}
					traversalQ.push(traversalQ.front()->find_right_child());
				}
				else cout << "n";
				cout << "  ";
			}

			traversalQ.pop();
			if (traversalQ.back() == NULL && traversalQ.front() == NULL) break;
		}
		cout << "\n\n\n";

	}

};




////////////////////////////////////////

long update_id=0;
long update_time=0;

template <class T>

class min_heap {


  void swap(long child, long parent);

  long find_left_child(long parent);
  long find_right_child(long parent);

public:
  vector<T> time_array;
  vector<T> heap_jobid;
  vector<T> total_time;

  long polong;
  void rearrange(long condition);

  long find_parent(long child);
  min_heap();
  void insert_val(T,T );
  void remove();
  long get_size();
  void set_size(long x);
  long last_notnull();
  long dispatch( );
  long dispatch1( );

  void display();

};

template <class T>
min_heap<T> :: min_heap(){

}

template <class T>
long min_heap<T> :: get_size()
{

  return time_array.size();
}



template <class T>
void min_heap<T> :: set_size(long x)
{
time_array.resize(x);

}

template <class T>
long min_heap<T> :: last_notnull()
{
 size_t i;
 i=heap_jobid.size();
    return i;

}
template <class T>
void min_heap<T>::swap(long child, long parent)
{
  T temp;
  temp = time_array[child];
  time_array[child] = time_array[parent];
  time_array[parent] = temp;

  temp = heap_jobid[child];
  heap_jobid[child] = heap_jobid[parent];
  heap_jobid[parent] = temp;

  temp = total_time[child];
  total_time[child] = total_time[parent];
  total_time[parent] = temp;

}

template <class T>
long min_heap<T> :: find_parent(long child)
{
  if (child % 2 != 0)
	return child /2 ;
  else
	return (child/2)-1;

}


template <class T>
long min_heap<T> :: find_right_child(long parent)
{
    long y=0;
    y=2*parent+2;
  return y;
}


long f1=0;
   long m=0;
   bool flag=false;
  long counter=0;
  long t_id=0;
  long t_t=0;
  long t_tt=0;

template <class T>
long min_heap<T> :: dispatch1()    // dispatch job for processing
{

  if(heap_jobid.size()>0  )
  {

          if(time_array[0]<total_time[0])
             {
                 if(m==0)
                 {
                  t_id=heap_jobid[0];
                  t_t=time_array[0];
                  t_tt=total_time[0];
                 if(total_time[0]-time_array[0]<5)
                    m=total_time[0]-time_array[0];
                 else
                    m=5;
                flag=true;
                 }
              time_array[0]=time_array[0]+1;
              t_t=t_t+1;
              update_time=time_array[0];
              update_id=heap_jobid[0];

              m=m-1;
              if(m>0)
              return 1;

            }
            if( time_array[0]==total_time[0])
               {
                   m=0;
                   flag=false;
                 return 0;

               }
            if( m==0 && flag==true)
               {
                   m=0;
                   flag=false;
   int i=0;
   i=last_notnull();
   size_t j=0;
   if(heap_jobid.size()>1){
   if(f1==1){
   swap(0,i-1);
   f1=0;

            }
else
{

for( j=0;j<time_array.size()-1;j++){
    time_array[j]=time_array[j+1];
   }

for( j=0;j<heap_jobid.size()-1;j++){
    heap_jobid[j]=heap_jobid[j+1];
   }

for( j=0;j<total_time.size()-1;j++){
    total_time[j]=total_time[j+1];
}

}
  heap_jobid.pop_back();
  total_time.pop_back();

 rearrange(1);
  heap_jobid.push_back(t_id);
  total_time.push_back(t_tt);
  i=last_notnull();

  time_array[i-1]=t_t;

rearrange(1);

}


                   return 1;
               }

  }  else
    return 0;

return 0;
}

template <class T>
long min_heap<T> :: find_left_child(long parent)
{
    long y=0;
    y=2*parent+1;
  return y;
}

template <class T>
void min_heap<T> :: insert_val(T value,T value1) {
long i=0;
// initial value of executed time=total time

i=last_notnull();
time_array[i]=0;
total_time.push_back(value);
heap_jobid.push_back(value1);

f1=1;
if(flag==true && heap_jobid.size()>1)
{

size_t j=0;
for( j=0;j<time_array.size()-1;j++){
    time_array[j]=time_array[j+1];
   }

for( j=0;j<heap_jobid.size()-1;j++){
    heap_jobid[j]=heap_jobid[j+1];
   }

for( j=0;j<total_time.size()-1;j++){
    total_time[j]=total_time[j+1];
}

  heap_jobid.pop_back();
  total_time.pop_back();

 rearrange(1);
  heap_jobid.push_back(t_id);
  total_time.push_back(t_tt);
  time_array[i]=t_t;
swap(0,i);
}
else

    rearrange(1);
}


template <class T>
void min_heap<T> :: remove() {
  long child = 0,i=0;


i=last_notnull();
child=i-1;

swap(child, 0);

i=last_notnull();
size_t j;

for( j=i-1;j<time_array.size()-1;j++){
    time_array[j]=time_array[j+1];
   }

for( j=i-1;j<heap_jobid.size()-1;j++){
    heap_jobid[j]=heap_jobid[j+1];
   }

for( j=i-1;j<total_time.size()-1;j++){
    total_time[j]=total_time[j+1];
}

  time_array.pop_back();
  heap_jobid.pop_back();
  total_time.pop_back();


  rearrange(0);


}

template <class T>
void min_heap <T>:: rearrange(long condition) {          //  rebalances min heap (heapify)

if(condition==1)    // new element insert_value
    {
  long child =0;
  size_t i=0;
  i=last_notnull();
  long parent=0;
  child=i-1;
  parent = find_parent(child);
  while (time_array[child] < time_array[parent] && child >=0 && parent >= 0) {//////////////////////

	swap(child, parent);
	child = parent;
	parent = find_parent(child);
  }
    }


if(condition==0)  // min deleted
    {
  long parent = 0;
   while (1) {
        long left=0;
        long right=0;
        long length=0;
        long smallest=0;
	   left = find_left_child(parent);
	   right = find_right_child(parent);
	   length = time_array.size();
       smallest = parent;
       size_t i;
       i=last_notnull();
       length=i;
	  if (right < length && time_array[right] < time_array[smallest])///////
	   smallest = right;

	  if (left < length && time_array[left] < time_array[smallest])//////
	   smallest = left;

	  if (smallest != parent) {
	   swap(smallest, parent);
	   parent = smallest;
	}
	else
	  break;


  }
    }
}



template <class T>
void min_heap<T> :: display()  //displays min heap
{

    size_t i;
    for(i=0;i<heap_jobid.size();i++){
          cout<<" JobId: "<<heap_jobid[i]<<"  executed time: "<<time_array[i]<<"  total time: "<<total_time[i]<<"\n";
    }
    cout<<"\n";
}



int main ( int argc, char *argv[] ){

  long size=0;
  min_heap<long> min_heap;
  long num=0,num1=0,i=0;
  long pos1,pos2,pos3;
  long pos4=0,pos5=0,pos6=0,pos7=0,pos8=0;
  static long first_append=0;
  long arr_time=0;
  long line_no=0;
  long loop_count=0;
  long key_val = 0;
  long time_val = 0;
  long dig=0;

  vector<long>disp_t;
  vector<long>disp_tt;
  vector<long>disp_job;

  string filename;
  string line;

  RBT<long> *reb = new RBT<long>();
  queue<long> removalQ;

   filename=argv[1];
   string filename1=filename;
   filename="./"+filename;
   filename1="output_file.txt";

  ifstream myfile (filename.c_str());
  ofstream myfile1;
  myfile1.open (filename1.c_str());
  if (myfile.is_open())                     //  file opened
  {
    while ( getline (myfile,line) )
    {
        line_no=line.find(":");
        arr_time=0;
        for(i=0;i<line_no;i++)
            arr_time=arr_time*10+(line.at(i)-48);
        dig=0;
 //checking if new insert available
 while(counter<arr_time)
 {

long v=0;
v=min_heap.dispatch1();    //dispatch  job
if(v==1)
{
    reb->AccessNode(update_id,update_time);   // exec_time updated in RB tree

}
 if(v==0)
 {
if(min_heap.heap_jobid.size()>0)
  {
  if(m==false){
    	key_val=t_id;
		removalQ.pop();
		reb->delete_node(key_val);}
        min_heap.remove();


  }

 }


counter+=1;
 }
if(counter==arr_time)  //  arrival time of job matches global counter
{

    counter+=1;

 loop_count=loop_count+1; //  keep track of input data and arrival times
 pos1=0;
      pos1=line.find("Insert");
         if(size<loop_count && pos1>1)
         {
            if(size==0)
                size=1;
            else
             size=size*2;
            min_heap.set_size(size);
         }
      pos2=pos3=0;
      pos4=0;


   if(pos1>1)      // insert command
  {
    pos2=line.find(",");
    pos3=line.find(")");
    pos4=line.find("(");
    for(i=pos2+1;i<pos3;i++)
    num=num*10+(line.at(i)-48);

    for(i=pos4+1;i<pos2;i++)
    num1=num1*10+(line.at(i)-48);

 }


  if(pos1>1){      // insert command continued
   key_val=0;
   time_val=0;
   min_heap.insert_val(num,num1);    // node inserted in min heap
   key_val=num1;
   time_val=num;
   reb->insert_node(key_val,time_val);   // node inserted in RB Tree
   removalQ.push(key_val);

  }


    pos5=line.find("Print");
    pos6=line.find("Next");
    pos7=line.find("Prev");


    if(pos5>0)
    {
        pos8=line.find(",");
        if(pos8>0)//   printjob(jobid1,jobid2)
        {

       size_t q;
       long pos11=0;
       long pos12=0;
       long p=0;
       long dig1=0;
       disp_job.clear();
       disp_t.clear();
       disp_tt.clear();
       range.clear();
       pos11=line.find("(");
       pos12=line.find(")");

        for(p=pos11+1;p<pos8;p++)
         dig=dig*10+(line.at(p)-48);
        for(p=pos8+1;p<pos12;p++)
         dig1=dig1*10+(line.at(p)-48);

       reb->print(dig,dig1);
       size_t w=0;
       for(q=0;q<range.size();q=q+3)     // range vector has all jobId,executed time,total time in given range
       {

           disp_job.push_back(range[q]);
           disp_t.push_back(range[q+1]);
           disp_tt.push_back(range[q+2]);
           w=w+1;
       }
       w=w-1;
        if(disp_job.size()>0)
     {


         if(first_append!=0)
            myfile1<<"\n";

       for(q=0;q<disp_job.size();q++)
       {

            myfile1<<"(";
            myfile1<<disp_job[q];
            myfile1<<",";
            myfile1<<disp_t[q];
            myfile1<<",";
            myfile1<<disp_tt[q];
            myfile1<<")";
                if(q<w)
                myfile1<<",";

       }

  }
  else{
         if(first_append!=0)
            myfile1<<"\n";
   myfile1<<"(0,0,0)";

  }


first_append++;

        }
        else //printjob(jobid1)
        {

        long p=0;
        long *arr;
        long p1=0,p2=0;
        p1=line.find("(");
        p2=line.find(")");

    for(p=p1+1;p<p2;p++)
    dig=dig*10+(line.at(p)-48);
    arr=reb->AccessNode2(dig);
    if(*(arr+0)==-1)
    {



        if(first_append!=0)
            myfile1<<"\n";
    myfile1<<"(0,0,0)";
    }
    else
{
    if(first_append!=0)
    myfile1<<"\n";

    myfile1<<"(";
    myfile1<<dig;
    myfile1<<",";
    myfile1<<*(arr+0);
    myfile1<<",";
    myfile1<<*(arr+1);
    myfile1<<")";


}
        }
first_append+=1;
    }

    else if(pos6>0)//Nextjob(jobid1)
    {

        long p1=0,p2=0,dig=0,p=0,*arr1;
        p1=line.find("(");
        p2=line.find(")");
    for(p=p1+1;p<p2;p++)
    dig=dig*10+(line.at(p)-48);
    p=reb->Next_or_Prev(dig,1);


if(p>-1)   //  check if tree is not empty
   {

    arr1=reb->AccessNode2(p);

         if(*(arr1+0)==-1)
    {
        if(first_append!=0){
            myfile1<<"\n";}

            myfile1<<"(0,0,0)";



    }
    else
{

    if(first_append!=0)
    myfile1<<"\n";
    myfile1<<"(";
    myfile1<<p;
    myfile1<<",";
    myfile1<<*(arr1+0);
    myfile1<<",";
    myfile1<<*(arr1+1);
    myfile1<<")";


}

   }
   else if(p==-1)  //  search it in completed files
   {
            if(first_append!=0)
            myfile1<<"\n";
            myfile1<<"(0,0,0)";

   }
    first_append++;
}
else if(pos7>0)// prevJob
{
        long p1=0,p2=0,dig=0,p=0,*arr2;
        p1=line.find("(");
        p2=line.find(")");
    for(p=p1+1;p<p2;p++)
    dig=dig*10+(line.at(p)-48);

p=reb->Next_or_Prev(dig,0);

if(p>-1)   //  check if tree is not empty
   {
    arr2=reb->AccessNode2(p);

         if(*(arr2+0)==-1)
    {
        if(first_append!=0)
            myfile1<<"\n";

    myfile1<<"(0,0,0)";


    }
    else{
                 if(first_append!=0)
            myfile1<<"\n";

    myfile1<<"(";
    myfile1<<p;
    myfile1<<",";
    myfile1<<*(arr2+0);
    myfile1<<",";
    myfile1<<*(arr2+1);
    myfile1<<")";
  }

}


else if(p==-1)  //  search it in completed files
   {
            if(first_append!=0)
            myfile1<<"\n";
            myfile1<<"(0,0,0)";
   }

first_append+=1;

}

   num=0;
   num1=0;
   long v=0;

v=min_heap.dispatch1();   // dispatch job after executing a job from file

if(v==1)
{
    reb->AccessNode(update_id,update_time);  // update exec_time in RB Tree

}
 if(v==0)
 {
if(min_heap.heap_jobid.size()>0)
  {
   if(m==false){
    	key_val=t_id;
		removalQ.pop();
		reb->delete_node(key_val);}        //delete job from RB Tree
        min_heap.remove();  //remove job from min heap

  }

 }

    }
    }

long v=-1;

while(min_heap.heap_jobid.size()>(size_t)0)
{
counter+=1;
v=min_heap.dispatch1();  // dispatch jobs when file is completely read

if(v==1)
{
    reb->AccessNode(update_id,update_time);

}
 if(v==0)
 {
   if(m==false){
     	key_val=t_id;
		removalQ.pop();
		reb->delete_node(key_val);  //delete job from RB Tree

        min_heap.remove();   //remove job from min heap
 }
 }

}

  }
  else  // file does not exist
   {

    cout<<"File does not exist. Check filename again !\n";
   }
    myfile.close();
    myfile1.close();

}
