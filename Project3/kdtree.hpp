#include <tuple>
#include <vector>
#include <algorithm>
#include <cassert>
#include <stdexcept>
#include <stack>

/**
 * An abstract template base of the KDTree class
 */
template<typename...>
class KDTree;

/**
 * A partial template specialization of the KDTree class
 * The time complexity of functions are based on n and k
 * n is the size of the KDTree
 * k is the number of dimensions
 * @typedef Key         key type
 * @typedef Value       value type
 * @typedef Data        key-value pair
 * @static  KeySize     k (number of dimensions)
 */
template<typename ValueType, typename... KeyTypes>
class KDTree<std::tuple<KeyTypes...>, ValueType> {
public:
    typedef std::tuple<KeyTypes...> Key;
    typedef ValueType Value;
    typedef std::pair<const Key, Value> Data;
    static inline constexpr size_t KeySize = std::tuple_size<Key>::value;
    static_assert(KeySize > 0, "Can not construct KDTree with zero dimension");

    typedef std::vector<std::pair<Key, Value>> InitVec;

protected:
    struct Node {
        Data data;
        Node *parent;
        Node *left = nullptr;
        Node *right = nullptr;

        Node(const Key &key, const Value &value, Node *parent) : data(key, value), parent(parent) {}

        const Key &key() { return data.first; }

        Value &value() { return data.second; }
    };

public:
    /**
     * A bi-directional iterator for the KDTree
     * ! ONLY NEED TO MODIFY increment and decrement !
     */
    class Iterator {
    private:
        KDTree *tree;
        Node *node;

        Iterator(KDTree *tree, Node *node) : tree(tree), node(node) {}

        /**
         * Increment the iterator
         * Time complexity: O(log n)
         */
        void increment() {
            // TODO: implement this function
            if (node == nullptr) return;
            if (node->right == nullptr) {
                Node *last_node = nullptr;
                while (node != nullptr && node->right == last_node) {
                    last_node = node;
                    node = node->parent;
                }
            }
            else {
                node = node->right;
                while (node->left != nullptr)
                    node = node->left;
            }
        }

        /**
         * Decrement the iterator
         * Time complexity: O(log n)
         */
        void decrement() {
            // TODO: implement this function
            if (node == nullptr) return;
            if (node->right == nullptr) {
                Node *last_node = nullptr;
                while (node != nullptr && node->left == last_node) {
                    last_node = node;
                    node = node->parent;
                }
            }
            else {
                node = node->left;
                while (node->right != nullptr)
                    node = node->right;
            }
        }

    public:
        friend class KDTree;

        Iterator() = delete;

        Iterator(const Iterator &) = default;

        Iterator &operator=(const Iterator &) = default;

        Iterator &operator++() {
            increment();
            return *this;
        }

        Iterator operator++(int) {
            Iterator temp = *this;
            increment();
            return temp;
        }

        Iterator &operator--() {
            decrement();
            return *this;
        }

        Iterator operator--(int) {
            Iterator temp = *this;
            decrement();
            return temp;
        }

        bool operator==(const Iterator &that) const {
            return node == that.node;
        }

        bool operator!=(const Iterator &that) const {
            return node != that.node;
        }

        Data *operator->() {
            return &(node->data);
        }

        Data &operator*() {
            return node->data;
        }
    };

protected:                      // DO NOT USE private HERE!
    Node *root = nullptr;       // root of the tree
    size_t treeSize = 0;        // size of the tree

    /**
     * Find the node with key
     * Time Complexity: O(k log n)
     * @tparam DIM current dimension of node
     * @param key
     * @param node
     * @return the node with key, or nullptr if not found
     */
    template<size_t DIM>
    Node *find(const Key &key, Node *node) {
        constexpr size_t DIM_NEXT = (DIM + 1) % KeySize;
        // TODO: implement this function
        if (node == nullptr) return nullptr;
        if (key == node->key()) return node;
        if (std::get<DIM>(key) < std::get<DIM>(node->key())) 
            return find<DIM_NEXT>(key, node->left);
        else
            return find<DIM_NEXT>(key, node->right);
    }

    /**
     * Insert the key-value pair, if the key already exists, replace the value only
     * Time Complexity: O(k log n)
     * @tparam DIM current dimension of node
     * @param key
     * @param value
     * @param node
     * @param parent
     * @return whether insertion took place (return false if the key already exists)
     */
    template<size_t DIM>
    bool insert(const Key &key, const Value &value, Node *&node, Node *parent) {
        constexpr size_t DIM_NEXT = (DIM + 1) % KeySize;
        // TODO: implement this function
        if (node == nullptr) {
            node = new Node(key, value, parent);
            ++treeSize;
            return true;
        }
        if (key == node->key()) {
            node->value() = value;
            return false;
        }
        if (std::get<DIM>(key) < std::get<DIM>(node->key())) {
            return insert<DIM_NEXT>(key, value, node->left, node);
        }
        else {
            return insert<DIM_NEXT>(key, value, node->right, node);
        }
    }

    /**
     * Compare two keys on a dimension
     * Time Complexity: O(1)
     * @tparam DIM comparison dimension
     * @tparam Compare
     * @param a
     * @param b
     * @param compare
     * @return relationship of two keys on a dimension with the compare function
     */
    template<size_t DIM, typename Compare>
    static bool compareKey(const Key &a, const Key &b, Compare compare = Compare()) {
        if (std::get<DIM>(a) != std::get<DIM>(b)){
            return compare(std::get<DIM>(a), std::get<DIM>(b));
        }
        return compare(a, b);
    }

    /**
     * Compare two nodes on a dimension
     * Time Complexity: O(1)
     * @tparam DIM comparison dimension
     * @tparam Compare
     * @param a
     * @param b
     * @param compare
     * @return the minimum / maximum of two nodes
     */
    template<size_t DIM, typename Compare>
    static Node *compareNode(Node *a, Node *b, Compare compare = Compare()) {
        if (!a) return b;
        if (!b) return a;
        return compareKey<DIM, Compare>(a->key(), b->key(), compare) ? a : b;
    }

    /**
     * Find the minimum node on a dimension
     * Time Complexity: ?
     * @tparam DIM_CMP comparison dimension
     * @tparam DIM current dimension of node
     * @param node
     * @return the minimum node on a dimension
     */
    template<size_t DIM_CMP, size_t DIM>
    Node *findMin(Node *node) {
        constexpr size_t DIM_NEXT = (DIM + 1) % KeySize;
        // TODO: implement this function
        if (node == nullptr) return nullptr;
        Node *lmin = findMin<DIM_CMP, DIM_NEXT>(node->left);
        // Node *res = lmin == nullptr || std::get<DIM_CMP>(node->key()) < std::get<DIM_CMP>(lmin->key()) ? node : lmin;
        Node *res = lmin;
        if (DIM_CMP != DIM) {
            Node *rmin = findMin<DIM_CMP, DIM_NEXT>(node->right);
            // res = rmin == nullptr || std::get<DIM_CMP>(res->key()) < std::get<DIM_CMP>(rmin->key()) ? res : rmin;
            res = compareNode<DIM_CMP, std::less<>>(res, rmin);
        }
        res = compareNode<DIM_CMP, std::less<>>(res, node);
        return res;
    }

    /**
     * Find the maximum node on a dimension
     * Time Complexity: ?
     * @tparam DIM_CMP comparison dimension
     * @tparam DIM current dimension of node
     * @param node
     * @return the maximum node on a dimension
     */
    template<size_t DIM_CMP, size_t DIM>
    Node *findMax(Node *node) {
        constexpr size_t DIM_NEXT = (DIM + 1) % KeySize;
        // TODO: implement this function
        if (node == nullptr) return nullptr;
        Node *rmax = findMax<DIM_CMP, DIM_NEXT>(node->right);
        // Node *res = rmax == nullptr || std::get<DIM_CMP>(node->key()) > std::get<DIM_CMP>(rmax->key()) ? node : rmax;
        Node *res = rmax;
        if (DIM_CMP != DIM) {
            Node *lmax = findMax<DIM_CMP, DIM_NEXT>(node->left);
            // res = lmax == nullptr || std::get<DIM_CMP>(res->key()) > std::get<DIM_CMP>(lmax->key()) ? res : lmax;
            res = compareNode<DIM_CMP, std::greater<>>(res, lmax);
        }
        res = compareNode<DIM_CMP, std::greater<>>(res, node);
        return res;
    }

    template<size_t DIM>
    Node *findMinDynamic(size_t dim) {
        constexpr size_t DIM_NEXT = (DIM + 1) % KeySize;
        if (dim >= KeySize) {
            dim %= KeySize;
        }
        if (dim == DIM) return findMin<DIM, 0>(root);
        return findMinDynamic<DIM_NEXT>(dim);
    }

    template<size_t DIM>
    Node *findMaxDynamic(size_t dim) {
        constexpr size_t DIM_NEXT = (DIM + 1) % KeySize;
        if (dim >= KeySize) {
            dim %= KeySize;
        }
        if (dim == DIM) return findMax<DIM, 0>(root);
        return findMaxDynamic<DIM_NEXT>(dim);
    }

    /**
     * Erase a node with key (check the pseudocode in project description)
     * Time Complexity: max{O(k log n), O(findMin)}
     * @tparam DIM current dimension of node
     * @param node
     * @param key
     * @return nullptr if node is erased, else the (probably) replaced node
     */
    template<size_t DIM>
    Node *erase(Node *node, const Key &key) {
        constexpr size_t DIM_NEXT = (DIM + 1) % KeySize;
        // TODO: implement this function
        if (node == nullptr) return nullptr;
        if (key == node->key()) {
            if (node->left == nullptr && node->right == nullptr) {
                delete node;
                --treeSize;
                return nullptr;
            }
            else if (node->right != nullptr) {
                Node *minNode = findMin<DIM, DIM_NEXT>(node->right);
                auto &temp = const_cast<Key &>(node->key());
                temp = minNode->key();
                node->value() = minNode->value();
                node->right = erase<DIM_NEXT>(node->right, minNode->key());
            }
            else {
                Node *maxNode = findMax<DIM, DIM_NEXT>(node->left);
                auto &temp = const_cast<Key &>(node->key());
                temp = maxNode->key();
                node->value() = maxNode->value();
                node->left = erase<DIM_NEXT>(node->left, maxNode->key());
            }
        }
        else {
            if (std::get<DIM>(key) < std::get<DIM>(node->key())) {
                node->left = erase<DIM_NEXT>(node->left, key);
            }
            else {
                node->right = erase<DIM_NEXT>(node->right, key);
            }
        }
        return node;
    }

    template<size_t DIM>
    Node *eraseDynamic(Node *node, size_t dim) {
        constexpr size_t DIM_NEXT = (DIM + 1) % KeySize;
        if (dim >= KeySize) {
            dim %= KeySize;
        }
        if (dim == DIM) return erase<DIM>(node, node->key());
        return eraseDynamic<DIM_NEXT>(node, dim);
    }

    // TODO: define your helper functions here if necessary

    template<size_t DIM>
    Node *buildTree(typename InitVec::iterator l, typename InitVec::iterator r, Node *parent) {
        constexpr size_t DIM_NEXT = (DIM + 1) % KeySize;
        if (l == r) return nullptr;
        std::sort(l, r, [](auto &a, auto &b) {
            return std::get<DIM>(a.first) < std::get<DIM>(b.first);
        });
        typename InitVec::iterator mid = l + (r - l) / 2;
        Node *node = new Node(mid->first, mid->second, parent);
        node->left = buildTree<DIM_NEXT>(l, mid, node);
        node->right = buildTree<DIM_NEXT>(mid + 1, r, node);
        return node;
    }

    Node *copyTree(Node *u, Node *parent) {
        if (u == nullptr) return nullptr;
        Node *node = new Node(u->key(), u->value(), parent);
        node->left = copyTree(u->left, node);
        node->right = copyTree(u->right, node);
        return node;
    }

    void deleteTree(Node *node) {
        if (node == nullptr) return;
        deleteTree(node->left);
        deleteTree(node->right);
        delete node;
    }

public:
    KDTree() = default;

    /**
     * Time complexity: O(kn log n)
     * @param v we pass by value here because v need to be modified
     */
    explicit KDTree(std::vector<std::pair<Key, Value>> v) {
        // TODO: implement this function
        std::stable_sort(v.begin(), v.end());
        std::reverse(v.begin(), v.end());
        auto last = std::unique(v.begin(), v.end(), [](auto &a, auto &b) {
            return a.first == b.first;
        });
        v.erase(last, v.end());
        root = buildTree<0>(v.begin(), v.end(), nullptr);
        treeSize = v.size();
    }

    /**
     * Time complexity: O(n)
     */
    KDTree(const KDTree &that) {
        // TODO: implement this function
        if (this == &that) return;
        deleteTree(root);
        root = copyTree(that.root, nullptr);
        treeSize = that.treeSize;
    }

    /**
     * Time complexity: O(n)
     */
    KDTree &operator=(const KDTree &that) {
        // TODO: implement this function
        if (this == &that) return *this;
        deleteTree(root);
        root = copyTree(that.root, nullptr);
        treeSize = that.treeSize;
        return *this;
    }

    /**
     * Time complexity: O(n)
     */
    ~KDTree() {
        // TODO: implement this function
        deleteTree(root);
    }

    Iterator begin() {
        if (!root) return end();
        auto node = root;
        while (node->left) node = node->left;
        return Iterator(this, node);
    }

    Iterator end() {
        return Iterator(this, nullptr);
    }

    Iterator find(const Key &key) {
        return Iterator(this, find<0>(key, root));
    }

    void insert(const Key &key, const Value &value) {
        insert<0>(key, value, root, nullptr);
    }

    template<size_t DIM>
    Iterator findMin() {
        return Iterator(this, findMin<DIM, 0>(root));
    }

    Iterator findMin(size_t dim) {
        return Iterator(this, findMinDynamic<0>(dim));
    }

    template<size_t DIM>
    Iterator findMax() {
        return Iterator(this, findMax<DIM, 0>(root));
    }

    Iterator findMax(size_t dim) {
        return Iterator(this, findMaxDynamic<0>(dim));
    }

    bool erase(const Key &key) {
        auto prevSize = treeSize;
        // erase<0>(root, key); 
        root = erase<0>(root, key); // XXX: 私以為這樣更合理
        return prevSize > treeSize;
    }

    Iterator erase(Iterator it) {
        if (it == end()) return it;
        auto node = it.node;
        if (!it.node->left && !it.node->right) {
            it.node = it.node->parent;
        }
        size_t depth = 0;
        auto temp = node->parent;
        while (temp) {
            temp = temp->parent;
            ++depth;
        }
        eraseDynamic<0>(node, depth % KeySize);
        return it;
    }

    size_t size() const { return treeSize; }
};
