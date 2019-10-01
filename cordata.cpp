
//segment-tree
template<typename T>
class segment_tree{
private:
    vector<T> value; // ノードの値を持つ配列
public:
    int leafnum;             // 葉の数
    T m_val;                 // 最大値
    int bilower(int x){
        int ans = 1;
        while(ans < x) ans <<= 1;
        return ans;
    }

    //constructor
    //nodenumは配列の要素数、maxvalは最初に渡しておく最大値
    segment_tree(int nodenum, T maxval){
        leafnum = bilower(nodenum);
        value = vector<T> (2*leafnum, maxval);
        m_val = maxval;
    }
    void update(int i, T x){
        // i 番目の葉の値を x に変える
        i += leafnum - 1; // i 番目の葉のノード番号
        value[i] = x;
        while (i > 0) {
            i = (i - 1) / 2; // ノード i の親ノードの番号に変える
            value[i] = min(value[i * 2 + 1], value[i * 2 + 2]); // 左右の子の min を計算しなおす
        }
    }

    //指定した区間の最小値を求める関数query
    //引数a,bで指定した半開区間[a,b)の中の最小値を求める
    //query(a,b,0,0,leafnum)として呼び出す、最期の引数に注意（leafnumはメンバ変数になっているのでそれを呼び出せばよい）
    T query(int a, int b, int k, int l, int r){
        // [a, b)の区間に対するクエリについて
        // ノード k （区間 [l, r) 担当）が答える
        if (r <= a || b <= l) return m_val; // 区間が被らない場合は 最大値 を返す
        if (a <= l && r <= b) return value[k]; // ノード k の担当範囲がクエリ区間 [a, b)             
        else{ //に完全に含まれる
            T r1 = query(a, b, 2 * k + 1, l, (l + r) / 2); // 左の子に値を聞く
            T r2 = query(a, b, 2 * k + 2, (l + r) / 2, r); // 右の子に値を聞く
            return min(r1, r2); // 左右の子の値の min を取る
        }
    }
};


//unionfind
//init: union_find name(size)

class union_find{
private:
    //根にはグループの要素数に―1をかけたもの、それ以外には根の値
    //初期値は-1
    vector<int> uni;
public:
    //Constructer
    //uniを必要なサイズで初期化する、初期値は―1
    union_find(int unisize) : uni(unisize,-1){}

    //引数aの根を求める、なければaを根として返す
    int root(int a){
        if(uni[a] < 0) return a;
        return uni[a] = root(uni[a]);  
    }

    //頂点aとbを繋ぐ関数unite
    //戻り値：
    //  元々同じグループであればfalse
    //  連結に成功すればtrue
    bool unite(int a, int b){
        //a, bにそれぞれが属するグループの根を入れる
        //uni[a], uni[b]がa, bがそれぞれが属するグループのサイズになる
        a = root(a);
        b = root(b);
        if(a == b) return false;
        if(uni[a] > uni[b]) swap(a,b); //bの方を大きいものにする
        uni[a] += uni[b];
        uni[b] = a; //大きい方のグループに属するものの親を小さいものの根にする(rootが高速で動くようになる)
        return true;
    }
    //頂点aとbが同じグループかを調べる
    bool isConnected(int a, int b){
        return root(a) == root(b);
    }
    //頂点aを含むグループの頂点数を調べる
    int unisize(int a){
        return -uni[root(a)];
    }
};
