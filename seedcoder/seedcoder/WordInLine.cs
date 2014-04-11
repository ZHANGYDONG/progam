using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace seedcoder
{
    class WordInLine
    {
        //声明为public
        public WordInLine(string _line) { lineOne = _line; }
        public void recognise()
        {
            //[ ]
            char[] charsToTrim1 = { '[', ']' };
            char[] charsToTrim2 = { '=' };
            char[] charsToTrim3 = { '"' };
            if (lineOne[0] == '[')
            {
                rkey = lineOne.Trim(charsToTrim1);
                int p = rkey.LastIndexOf('\\');
                if (p != -1)
                { 
                    parentkey = rkey.Remove(p); 
                }
                kind = "key";
            }
            // = 
            else
            {
                string[] words = lineOne.Split(charsToTrim2);
                leftWord = words[0];
                rightWord = words[1];
                // str
                if (rightWord[0] == '"')
                {
                    leftWord = leftWord.Trim(charsToTrim3);
                    rightWord = rightWord.Trim(charsToTrim3);
                    kind = "str";
                }
                else
                {
                    //hex
                    if (rightWord.StartsWith("hex"))
                    {
                        leftWord = leftWord.Trim(charsToTrim3);
                        rightWord = rightWord.Remove(0, 4);
                        kind = "hex";
                    }
                    //dword
                    else if (rightWord.StartsWith("dword"))
                    {
                        leftWord = leftWord.Trim(charsToTrim3);
                        rightWord = rightWord.Remove(0, 6);
                        kind = "dword";

                    }
                    else Console.WriteLine("DATA ERROR");

                }
            }
        }
        public string Parentkey
        {
            get
            {
                return parentkey;
            }
        }
        public string RKey
        {
            get
            {
                return rkey;
            }
        }
        public string LeftWord
        {
            get
            {
                return leftWord;
            }
        }
        public string RightWord
        {
            get
            {
                return rightWord;
            }
        }
        //key, str, hex, dword
        public string Kind
        {
            get
            {
                return kind;
            }
        }

        private string parentkey, kind, lineOne,rkey, leftWord,rightWord;
    }
}
