
// 最大公約数を求める
// 計算量O(logn)
template<class T>
T gcd(T a, T b){
    if(b == 0) return a;
    return gcd(b, a%b);
}

// 最小公倍数を求める
// 計算量O(logn)
template<class T>
T lcm(T a, T b){
    return a/gcd(a,b)*b;
}

// 素数判定
// 計算量O(√n)
template<class T>
bool isPrime(T n){
    if(n < 2) return false;
    for(long long i = 2; i*i <= n; ++i) if(n % i == 0) return false;
    return true;
}

// 素数列挙
// nまでの素数をEratosthenesの篩で列挙する
// 計算量O(nloglogn)
template<class T>
vector<T> prime_list(T n){
    vector<T> ret;
    vector<T> isPrime(n+1,1);
    isPrime[0] = isPrime[1] = 0;
    for(long long i = 2; i <= n; ++i){
        if(isPrime[i] == 0) continue;
        ret.push_back(i);
        for(long long j = i*i; j <= n; j += i) isPrime[j] = 0;
    }
    return ret;
    // return isPrime;  // 状況によってはこっちを返す
}

// 素因数分解
// nを素因数分解してmapに記録
// 計算量O(√nlogn),必要ならmapではなくvectorにすると計算量を落とせる
template<class T>
map<T,int> prime_factor(T n){
    map<T,int> ret;
    if(n <= 0){
        cout << "Prime_factor Error" << "\n";
        return ret;
    }
    for(long long i = 2; i*i <= n; ++i){
        while(n%i== 0){
            ++ret[i];
            n /= i;
        }
    }
    if(n != 1) ret[n]++;
    return ret;
}


// 関数名：pow
// 概要：modつき指数関数
// 第一引数a：指数の底
// 第二引数b：指数
// 第三引数mod：法となる値
// 戻り値：a^b(m mod)
// 計算量O(log b)
template<class T>
T pow(T a, int b){
    if(b == 0) return 1;
    if(b%2){
        T ret = pow(a,(b-1)/2); 
        return ret*ret*a;
    }else{
        T ret = pow(a,b/2);
        return ret*ret;
    }
}

template<class T>
T pow(long long a, long long b, T mod){
    if(b == 0) return 1;
    if(b % 2 == 0){
        T d = pow(a,b/2,mod);
        return (d*d)%mod;
    }else return a%mod*pow(a,b-1,mod)%mod;
}

//関数名：comb
//概要：二項係数
//第一引数n：組み合わせの全体
//第二引数r：何個取り出すか
//第三引数mod：法となる値
//戻り値：nCr(m mod)
// 計算量O(r), 第三引数まで指定するとO(rlogmod)
template<class T>
T comb(T n, T r){
    if(r > n) return 0;
    if(n == r || r == 0) return 1;
    T ret = 1;
    for(T i = 1; i <= r; ++i){
        ret *= n--;
        ret /= i;
    }
    return ret;
}

template<class T>
T comb(long long n,long long r,T mod){
    if(r > n) return 0;
    if(n == r || r == 0) return 1;
    long long fact1 = 1,fact2 = 1;
    for(long long i = n; i >= n-r+1; --i) fact1 = fact1*i%mod;
    for(long long i = r; i >= 1; --i) fact2 = fact2*i%mod;
    return fact1*pow(fact2,mod-2,mod)%mod;
}
