
// segment-tree
// Tはモノイドの台集合
template<typename T>
class segment_tree{
private:
    using F = function<T(T,T)>;
    int leafnum;             // 葉の数
    const T m1;                 // 単位元
    F f;
    vector<T> seg; // ノードの値を持つ配列
    int bilower(int x){
        int ret = 1;
        while(ret < x) ret <<= 1;
        return ret;
    }

    T _query(int a, int b, int k, int l, int r){
        // [a, b)の区間に対するクエリについて
        // ノード k （区間 [l, r) 担当）が答える
        if (r <= a || b <= l) return m1; // 区間が被らない場合は 単位元 を返す
        if (a <= l && r <= b) return seg[k]; // ノード k の担当範囲がクエリ区間 [a, b)
        else{ // に完全に含まれる
            T r1 = _query(a, b, 2 * k + 1, l, (l + r) / 2); // 左の子に値を聞く
            T r2 = _query(a, b, 2 * k + 2, (l + r) / 2, r); // 右の子に値を聞く
            return f(r1, r2); // 左右の子の値の f を取る
        }
    }

public:
    
    //constructor
    //nodenumは配列の要素数、 はモノイドの単位元
    segment_tree(int nodenum, const T m):m1(m){
        leafnum = bilower(nodenum);
        seg = vector<T> (2*leafnum, m);

        // 二項演算の実装
        f = [](T a, T b){
            return ;
        };
    }

    // i 番目の葉の値を x に変える
    void update(int i, T x){    
        i += leafnum - 1; // i 番目の葉のノード番号
        seg[i] = x;
        while (i > 0) {
            i = (i - 1) / 2; // ノード i の親ノードの番号に変える
            seg[i] = f(seg[i * 2 + 1], seg[i * 2 + 2]); // 左右の子の f を計算しなおす
        }
    }

    //引数a,bで指定した半開区間[a,b)の要素について計算する
    //_query(a,b,0,0,leafnum)として呼び出す、最期の引数に注意（leafnumはメンバ変数になっているのでそれを呼び出せばよい）
    T query(int a, int b){
        return _query(a, b, 0, 0, leafnum);
    }
    
    // i番目の値を答える
    T node(int i){
        return seg[i+2*leafnum];
    }
};


//unionfind
//init: union_find name(size)

class union_find{
private:
    //根にはグループの要素数に-1をかけたもの、それ以外には根の値
    //初期値は-1
    vector<int> uni;
    int _group_num;
public:
    //Constructer
    //uniを必要なサイズで初期化する、初期値は―1
    union_find(int unisize) : uni(unisize,-1){
        _group_num = unisize;
    }

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
        if(a == b) return false; // 同じグループの場合
        if(uni[a] > uni[b]) swap(a,b); //bの方を大きいものにする
        uni[a] += uni[b];
        uni[b] = a; //大きい方のグループに属するものの親を小さいものの根にする(rootが高速で動くようになる)
        _group_num--;
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
    //グループ数を調べる
    int group_num(void){
        return _group_num;
    }
};
