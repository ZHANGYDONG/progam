using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace seedcoder
{
    class Node
    {
        public Node(string _key)
        {
            key = _key;
        }
        //add data
        public void add(Dictionary<string, string> strlist)
        {
            try
            {
                this.StrList.Add(strlist);
            }
            catch (NotSupportedException)
            {
                Console.WriteLine("Add StrList ERROR.");
            }
        }
        public void add(Dictionary<string, string> hexlist, int a)
        {
            try
            {
                this.HexList.Add(hexlist);
            }
            catch (NotSupportedException)
            {
                Console.WriteLine("Add HexList ERROR.");
            }
        }
        public void add(Dictionary<string, string> dwlist, int a, int b)
        {
            try
            {
                this.DwordList.Add(dwlist);
            }
            catch (NotSupportedException)
            {
                Console.WriteLine("Add HexList ERROR.");
            }
        }
        public void add(Node chlist)
        {
            try
            {
                this.ChildList.Add(chlist);
            }
            catch (NotSupportedException)
            {
                Console.WriteLine("Add HexList ERROR.");
            }
        }
        public string Key
        {
            get
            {
                return key;
            }
            set
            {
                key = value;
            }
        }
        //as primary key for search,eg.Registry\Hardware\Monitor
        private string key;
        //string ArrayList
        public ArrayList StrList = new ArrayList();
        //hex ArrayList
        public ArrayList HexList = new ArrayList();
        //dword ArrayList
        public ArrayList DwordList = new ArrayList();
        //child ArrayList
        public ArrayList ChildList = new ArrayList();

    }
}
