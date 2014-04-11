using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace seedcoder
{
    class RegistryTree
    {
        //constructor function
        public RegistryTree(string str_root)
        {
            root = new Node(str_root);
        }
        //find port _key_ is the primary key
        public Node find(string _key_)
        {
            return find(root, _key_);
        }
        public Node find(Node xx ,string ss)
        {
            if (xx.Key == ss)
                return xx;
            if (xx.ChildList.Count != 0)
            {
                foreach (Node xch in xx.ChildList)
                {
                    if (xch.Key == ss)
                        return xch;
                }
                foreach (Node xxch in xx.ChildList)
                {
                    find(xxch, ss);
                }
                Node err = new Node("ERROR find two");
                return err;
            }
            else
            {
                Node err = new Node("ERROR find two");
                return err;
            }
        }
        //public int modify();
        //it could make nodes to tree,ref is reference
        public int insert(Node rootnode, ref Node subnode)
        {
            rootnode.ChildList.Add(subnode);
            //use ChildList establish tree.subnode in the ChildList of rootnode
            return 0;
 
        }
        //public int delete();


        public Node get_Root
        {
            get { return root; }
            //set { root = value; }
        }
        //root node
        private Node root;                       
    }
}
