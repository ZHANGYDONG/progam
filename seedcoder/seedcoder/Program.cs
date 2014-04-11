using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace seedcoder
{
    class Program
    {
        static void print(Node yy)
        {
            Console.WriteLine("***************Parent*******************");
            Console.WriteLine(yy.Key);
            Console.WriteLine("\n");
            foreach (Node tt in yy.ChildList)
            {
                Console.WriteLine("\t" + tt.Key);
            }           
        }

        static void Main(string[] args)
        {
            string[] lines = System.IO.File.ReadAllLines(".\\Registry");
            //初始化
            RegistryTree Tree = new RegistryTree("Registry");
            int k = 0;
            //获取树的根节点,初始化一个节点
            Node r = new Node("");
            
            //!!这里r就是引用(两种情况都是)
            //Node r = Tree.get_Root;
            //r = Tree.get_Root;
            //System.Console.WriteLine(Tree.get_Root.Key);
            //Tree.get_Root.Key = "sdfdf";
            //System.Console.WriteLine(r.Key);
            
            r.StrList.Clear();
            r.HexList.Clear();
            r.DwordList.Clear();
            r.ChildList.Clear();
            // Node rc = new Node("Registry");
            //存放读取的点
            //ArrayList point = new ArrayList();
            //point.Add(r);
            // Display the file contents by using a foreach loop.
            System.Console.WriteLine("*******************************************************");
            for (int i = 0; i != lines.Length; i++ )
            {
                string line = lines[i];
                WordInLine node = new WordInLine(line);
                node.recognise();
                // Use a tab to indent each line of the file.
                Console.WriteLine(line);
                if (line[0] == '[')
                {
                    //xindedian;
                    if (node.RKey != "Registry")
                    {
                        k = 0;
                        r = new Node(node.RKey);
                        //r.Key = node.RKey;
                        r.StrList.Clear();
                        r.HexList.Clear();
                        r.DwordList.Clear();
                        r.ChildList.Clear();
                        //加到父节点里
                        Node oo = Tree.find(node.Parentkey);
                        oo.add(r);
                        //把已经存在的点加进去
                        //int sl = r.StrList.Count;
                        //int hl = r.HexList.Count;
                        //int dl = r.DwordList.Count;
                        //if (sl != 0 || hl != 0 || dl != 0)
                        //{
                            //加进树
                           // Tree.find(node.Parentkey).add(r);
                        //}
                        // r = Tree.find(node.Parentkey);
                        //point.Add(r);
                    }
                    //Registry 节点初始化
                    else
                    {
                        k = 1;
                    }
                }
                else
                {
                    //Analysis of the line information
                    switch (node.Kind)
                    {
                        case "str":
                            Console.WriteLine("str 1");
                            Dictionary<string, string> _str = new Dictionary<string, string>();
                            _str.Add(node.LeftWord, node.RightWord);
                            if (k == 1) 
                                Tree.get_Root.add(_str);
                            else if (k == 0)
                            {
                                r.add(_str);
                                Tree.find(node.Parentkey).add(r);
                            }
                            else
                                Console.WriteLine("EORRO : i");
                            break;
                        case "hex":
                            Console.WriteLine("hex 2");
                            Dictionary<string, string> _hex = new Dictionary<string, string>();
                            _hex.Add(node.LeftWord, node.RightWord);
                            if (k == 1)
                                Tree.get_Root.add(_hex, 0);
                            else if (k == 0)
                            {
                                r.add(_hex, 0);
                                Tree.find(node.Parentkey).add(r);
                            }
                            else
                                Console.WriteLine("EORRO : i");
                            break;
                        case "dword":
                            Console.WriteLine("dword 3");
                            Dictionary<string, string> _dword = new Dictionary<string, string>();
                            _dword.Add(node.LeftWord, node.RightWord);
                            if (k == 1)
                                Tree.get_Root.add(_dword, 0, 0);
                            else if (k == 0)
                            {
                                r.add(_dword, 0, 0);
                                Tree.find(node.Parentkey).add(r);
                            }
                            else
                                Console.WriteLine("EORRO : i");
                            break;
                        default:
                            Console.WriteLine("Default case");
                            break;
                    }
                }
                    
                
            }
            print(Tree.get_Root);
            foreach (Node m in Tree.get_Root.ChildList)
            {
                print(m);
            }
            // Keep the console window open in debug mode.
            Console.WriteLine("Press any key to exit.");
            System.Console.ReadKey();

        }
    }
}

