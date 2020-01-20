#include <bits/stdc++.h>

using namespace std;

/*
10 10
<a value = "GoodVal">
<b value = "BadVal" size = "10">
</b>
<c height = "auto">
<d size = "3">
<e strength = "2">
</e>
</d>
</c>
</a>
a~value
b~value
a.b~size
a.b~value
a.b.c~height
a.c~height
a.d.e~strength
a.c.d.e~strength
d~sze
a.c.d~size

GoodVal
Not Found!
10
BadVal
Not Found!
auto
Not Found!
2
Not Found!
3
*/

typedef struct tag{
    string name;
    map<string,string> hm;
    string hierarchy = "";
}TAG;

int main(){
    //ios_base::sync_with_stdio(false);
    //cin.tie(NULL);
    int n,q;
    cin >> n >> q;
    getchar();
    string s,t;
    TAG tag[n];
    int tag_len = 0;
    vector<string> parser;
    for(int i = 0; i < n; i++) {
        getline(cin,s,'>');
        stringstream ss(s.substr(1,s.size()));
        //cout << "-->" << s.substr(1,s.size()-1) << "\n";
        int  cnt= 0;
        bool iskey = true;
        bool incTC = true;
        string k;
        while(ss >> t){
            //ss >> t;
            if(cnt == 0 && t[0]=='/'){
                int l = parser.size();
                /*if(parser[l-1].compare(t.substr(1,t.length()-1))==0){
                    for(int p = 0; p < l; p++){
                        tag[tc-1].hierarchy += parser[p];
                        if(p!=l-1)
                            tag[tc-1].hierarchy += '.';
                    }
                    parser.pop_back();
                    tc--;
                }*/

                for(int j = 0; j < tag_len; j++){
                    if(tag[j].name.compare(t.substr(1,t.length()-1))==0){
                        for(int p = 0; p < l; p++){
                            tag[j].hierarchy += parser[p];
                            if(p!=l-1)
                                tag[j].hierarchy += '.';
                        }
                        break;
                    }
                }
                parser.pop_back();
                incTC = false;
            }else if(cnt == 0){
                tag[tag_len].name = t;
                parser.push_back(t);
            }else{
                if(t.compare("=")==0){
                    iskey = false;
                }else{
                    if(iskey)
                        k = t;
                    else{
                        tag[tag_len].hm.insert(make_pair(k,t));
                        iskey = true;    
                    }
                }
            }
            cnt++;
        }
        if(incTC){
            tag_len++;
        }
        getchar();
    }
    /*cout << "````````````````````````````````````````````````\n";
    cout << "TC: " << tag_len << "\n";
    for(int i = 0; i <tag_len; i++){
        cout << tag[i].name << "\n";
        map<string,string>::iterator it;
        for(it = tag[i].hm.begin();it!=tag[i].hm.end();it++)
            cout << it->first << "  " << it->second << "\n";
        cout << "HIERARCHY: " << tag[i].hierarchy << "\n";
        cout << "````````````````````````````````````````````````\n";
    }*/

    string attr;
    for(int i = 0; i < q; i++){
        cin >> s;

        int pos = s.find("~");
        t = s.substr(0,pos);
        attr = s.substr(pos+1,s.length()-pos-1);

        bool fail = true;
        for(int j = 0; j < tag_len; j++){
            if(t.compare(tag[j].hierarchy)==0 && tag[j].hm.find(attr)!=tag[j].hm.end()){
                cout << tag[j].hm[attr].substr(1,tag[j].hm[attr].length()-2) << "\n";
                fail = false;
                break;
            }
        }


        if(fail)
            cout << "Not Found!\n";
    }
    return 0;
}