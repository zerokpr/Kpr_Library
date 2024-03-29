
// corbeau sword
template<class T>
class AATree {
    struct node {
        T value;
        int level;
        int size;
        node *left;
        node *right;
        explicit node(T val, int lv, node* l, node* r) : value(val), level(lv), size(1), left(l), right(r) {}
    };

private:

    node* root;
    int _size;
    
    node* skew(node *t) {
        if (t == nullptr) return nullptr;
        else if(t->left == nullptr) return t;
        else if (level(t->left) == level(t)) {
            node* l = t->left;
            t->left = l->right;
            l->right = t;
            t->size = size(t->left) + size(t->right)+1;
            return l;
        } else {
            t->size = size(t->left) + size(t->right)+1;
            return t;
        }
    }

    node* split(node* t) {
        if (t == nullptr) return nullptr;
        else if (t->right == nullptr || t->right->right == nullptr) return t;
        else if (level(t) == level(t->right->right)) {
            node* r = t->right;
            t->right = r->left;
            r->left = t;
            ++(r->level);
            t->size = size(t->left) + size(t->right)+1;
            return r;
        } else {
            t->size = size(t->left) + size(t->right)+1;
            return t;
        }
    }

    node* insert(const T &x, node* t) {
        if (t == nullptr) {
            ++(this->_size);
            return (new node(x, 1, nullptr, nullptr));
        } else if (x < t->value) t->left = insert(x, t->left);
        else if (x > t->value) t->right = insert(x, t->right);
        
        t = skew(t);
        t = split(t);
        t->size = size(t->left) + size(t->right) + 1;

        return t;
    }

    node* remove(const T &x, node* t) {
        
        if (t == nullptr) return t;
        else if (x > t->value) t->right = remove(x, t->right);
        else if (x < t->value) t->left = remove(x, t->left);
        else {
            if (is_leaf(t)) {
                delete t;
                --(this->_size);
                return nullptr;
            } else if (t->left == nullptr) {
                node* s = successor(t);
                t->value = s->value;
                t->right = remove(s->value, t->right);
            } else {
                node* p = predecessor(t);
                t->value = p->value;
                t->left = remove(p->value, t->left);
            }
        }

        t = decrease_level(t);
        t = skew(t);
        t->right = skew(t->right);
        if (t->right != nullptr) t->right->right = skew(t->right->right);
        t = split(t);
        t->right = split(t->right);
        t->size = size(t->left) + size(t->right) + 1;
        return t;
    }

    bool find(const T &x, node* t) {
        if (t == nullptr) return false;
        if (x < t->value) return find(x, t->left);
        else if(x > t->value) return find(x, t->right);
        else return true;
    }

    inline int size(node *t) {
        if(t == nullptr) return 0;
        else return t->size;
    }


    inline int level(node *t) {
        if (t == nullptr) return 0;
        else return t->level;
    }

    inline bool is_leaf(node* t) {
        return t->left == nullptr && t->right == nullptr;
    }

    node* successor(node* t) {
        node* ret = t->right;
        while (ret->left != nullptr) ret = ret->left;
        return ret;
    }

    node* predecessor(node* t) {
        node* ret = t->left;
        while (ret->right != nullptr) ret = ret->right;
        return ret;
    }

    node* decrease_level(node* t) {
        int should_be = min(level(t->left), level(t->right)) + 1;

        if (should_be < level(t)) {
            t->level = should_be;
            if(should_be < level(t->right)) t->right->level = should_be;
        }
        return t;
    }

public:

    AATree() {
        this->root = nullptr;
        this->_size = 0;
    }

    void insert(const T &x) {
        this->root = insert(x, this->root);
    }

    void remove(const T &x) {
        this->root = remove(x, this->root);
    }

    bool find(const T &x) {
        return find(x, this->root);
    }

    int size() {
        return size(this->root);
    }

    T get(int k, node* t) {
        if(t == nullptr) {
            std::cout << "Error in AATree::get\n";
            return "";
        }
        if (k == size(t->left)) return t->value;
        if (k < size(t->left)) {
            return get(k, t->left);
        } else {
            return get(k-size(t->left)-1, t->right);
        }
    }
    // get k-th element
    T get(int k) {
        if(size(this->root) < k) {
            return 0;
        };
        return get(k, this->root);
    }

};
