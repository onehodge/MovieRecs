#ifndef TREEMULTIMAP_INCLUDED
#define TREEMULTIMAP_INCLUDED

#include <vector>

template <typename KeyType, typename ValueType>
class TreeMultimap
{
  private:
    struct Node
    {
        Node(KeyType key, ValueType value): ID(key)
        {
            val.push_back(value);
            left=nullptr;
            right=nullptr;
        }
        KeyType ID;
        std::vector<ValueType> val;     //a key in multimap points to many values
        Node* left;
        Node* right;
    };
    Node* root;
    void clear(Node* cur)               //delete the whole tree recursively
    {
        if(cur==nullptr) return;
        clear(cur->left);
        clear(cur->right);
        delete cur;
    }
    
  public:
    class Iterator
    {
      public:
        Iterator()  {node=nullptr; nth_item=0;}
        Iterator(Node* p) {node=p; nth_item=0;}
        
        ValueType& get_value() const {return node->val[nth_item];}

        bool is_valid() const
        {
            if(node==nullptr)                   //no such node
                return false;
            if(nth_item >= node->val.size())    //already iterated through entire vector
                return false;
            return true;
        }

        void advance()  {nth_item++;}           //next item in the vector

      private:
        Node* node;
        int nth_item;           //current position in the val vector
        
    };

    TreeMultimap()  {root=nullptr;}
    ~TreeMultimap() {clear(root); root=nullptr;}

    void insert(const KeyType& key, const ValueType& value)
    {
        if(root==nullptr)               //first node: the root
        {
            root=new Node(key, value);
            return;
        }
        Node* cur=root;
        while(key!=cur->ID)             //searching
        {
            if(key < cur->ID)
            {
                if(cur->left != nullptr)    //keep searching
                    cur = cur->left;
                else                        //create a new leaf and return
                {
                    cur->left = new Node(key, value);
                    return;
                }
            }
            else if(key > cur->ID)
            {
                if(cur->right != nullptr)   //keep searching
                    cur = cur->right;
                else                        //create a new node and return
                {
                    cur->right = new Node(key, value);
                    return;
                }
            }
        }
        //found the key, node already exists: add a new value to vector
        cur->val.push_back(value);
    }

    Iterator find(const KeyType& key) const
    {
        Node* cur= root;
        while(cur!=nullptr)
        {
            if(cur->ID == key)      //found
                break;
            else if(key < cur->ID)
                cur=cur->left;
            else
                cur=cur->right;
        }
        Iterator it(cur);       //if not found, it.node would be nullptr
        return it;
    }
};

#endif // TREEMULTIMAP_INCLUDED
