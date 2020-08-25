// corutil.

/* 二次元配列の補完 */
// c-arrtemplate<class T>
void extend2dArray(T* src, T* dst, int h, int w, T val){
    for(int i = 0; i < w+2; ++i){
        *(dst + i) = val;
        *(dst + (h+1)*(w+2) + i) = val;
    }
    for(int i = 0; i < h; ++i) for(int j = 0; j < w; ++j) *(dst + (i+1)*(w+2) + j+1) = *(src + i*w + j);
    for(int i = 0; i < h+2; ++i){
        *(dst + i*(w+2)) = val;
        *(dst + i*(w+2) + w+1) = val;
    }
}

// 2dVec
template<class T>
vector<vector<T>> extend2dArray(vector<vector<T>> &src, T val){
    int h = src.size(), w = src[0].size();
    vector<vector<T>> ret(h+2, vector<T>(w+2, val));
    for(int i = 0; i < h; ++i) for(int j = 0; j < w; ++j) ret[i+1][j+1] = src[i][j];
    return ret;
}

// string
vector<string> extend2dArray(vector<string> &src, char val){
    int h = src.size(), w = src[0].size();
    vector<string> ret(h+2, string(w+2, char(val)));
    for(int i = 0; i < h; ++i) for(int j = 0; j < w; ++j) ret[i+1][j+1] = src[i][j];
    return ret;
}
